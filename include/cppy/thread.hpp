#pragma once

#include <condition_variable> //condition_variable
#include <future>             //packaged_task
#include <mutex>              //unique_lock
#include <queue>              //queue
#include <thread>             //thread
#include <type_traits>        //invoke_result, enable_if, is_invocable
#include <vector>             //vector

CPPY_API class ThreadPoolExecutor {
public:
	CPPY_API ThreadPoolExecutor(size_t max_workers = std::thread::hardware_concurrency());
	CPPY_API ~ThreadPoolExecutor();

	ThreadPoolExecutor(const ThreadPoolExecutor& other) = delete;
	ThreadPoolExecutor& operator=(const ThreadPoolExecutor&) = delete;

	template <typename F, typename... Args,
		std::enable_if_t<std::is_invocable_v<F&&, Args &&...>, int> = 0>
	auto submit(F&&, Args &&...);

	CPPY_API void shutdown();

private:
	//_task_container_base and _task_container exist simply as a wrapper around a
	//  MoveConstructible - but not CopyConstructible - Callable object. Since an
	//  std::function requires a given Callable to be CopyConstructible, we
	//  cannot construct one from a lambda function that captures a
	//  non-CopyConstructible object (such as the packaged_task declared in
	//  execute) - because a lambda capturing a non-CopyConstructible object is
	//  not CopyConstructible.

	//_task_container_base exists only to serve as an abstract base for
	//  _task_container.
	class _task_container_base {
	public:
		virtual ~_task_container_base() {};

		virtual void operator()() = 0;
	};
	using _task_ptr = std::unique_ptr<_task_container_base>;

	//_task_container takes a typename F, which must be Callable and
	// MoveConstructible.
	//  Furthermore, F must be callable with no arguments; it can, for example,
	//  be a bind object with no placeholders. F may or may not be
	//  CopyConstructible.
	template <typename F, std::enable_if_t<std::is_invocable_v<F&&>, int> = 0>
	class _task_container : public _task_container_base {
	public:
		// here, std::forward is needed because we need the construction of _f not
		//  to bind an lvalue reference - it is not a guarantee that an object of
		//  type F is CopyConstructible, only that it is MoveConstructible.
		_task_container(F&& func) : _f(std::forward<F>(func)) {}

		void operator()() override { _f(); }

	private:
		F _f;
	};

	template <typename F> _task_container(F) -> _task_container<std::decay<F>>;

	std::vector<std::thread> _threads;
	std::queue<_task_ptr> _tasks;
	std::mutex _task_mutex;
	std::condition_variable _task_cv;
	bool _stop_threads = false;
};

template <typename F, typename... Args,
	std::enable_if_t<std::is_invocable_v<F&&, Args &&...>, int>>
	auto ThreadPoolExecutor::submit(F&& function, Args &&...args) {
	std::unique_lock<std::mutex> queue_lock(_task_mutex, std::defer_lock);
	std::packaged_task<std::invoke_result_t<F, Args...>()> task_pkg(
		// in C++20, this could be:
		// [..., _fargs = std::forward<Args>(args)...]
		[_f = std::move(function),
		_fargs = std::make_tuple(std::forward<Args>(args)...)]() mutable {
			return std::apply(std::move(_f), std::move(_fargs));
		});
	std::future<std::invoke_result_t<F, Args...>> future = task_pkg.get_future();

	queue_lock.lock();
	// this lambda move-captures the packaged_task declared above. Since the
	//  packaged_task type is not CopyConstructible, the function is not
	//  CopyConstructible either - hence the need for a _task_container to wrap
	//  around it.
	_tasks.emplace(_task_ptr(
		new _task_container([task(std::move(task_pkg))]() mutable { task(); })));

	queue_lock.unlock();

	_task_cv.notify_one();

	return std::move(future);
}

CPPY_API ThreadPoolExecutor::ThreadPoolExecutor(size_t max_workers) {
	for (size_t i = 0; i < max_workers; ++i) {
		// start waiting threads. Workers listen for changes through
		//  the thread_pool member condition_variable
		_threads.emplace_back(std::thread([&]() {
			std::unique_lock<std::mutex> queue_lock(_task_mutex, std::defer_lock);

			while (true) {
				queue_lock.lock();
				_task_cv.wait(queue_lock, [&]() -> bool {
					return !_tasks.empty() || _stop_threads;
					});

				// used by dtor to stop all threads without having to
				//  unceremoniously stop tasks. The tasks must all be
				//  finished, lest we break a promise and risk a `future`
				//  object throwing an exception.
				if (_stop_threads && _tasks.empty())
					return;

				// to initialize temp_task, we must move the unique_ptr
				//  from the queue to the local stack. Since a unique_ptr
				//  cannot be copied (obviously), it must be explicitly
				//  moved. This transfers ownership of the pointed-to
				//  object to *this, as specified in 20.11.1.2.1
				//  [unique.ptr.single.ctor].
				auto temp_task = std::move(_tasks.front());

				_tasks.pop();
				queue_lock.unlock();

				(*temp_task)();
			}
			}));
	}
}

CPPY_API void ThreadPoolExecutor::shutdown() {
	_stop_threads = true;
	_task_cv.notify_all();

	for (std::thread& thread : _threads) {
		thread.join();
	}
}

CPPY_API ThreadPoolExecutor::~ThreadPoolExecutor() {
	shutdown();
}
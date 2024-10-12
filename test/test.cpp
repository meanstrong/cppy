#include "cppy/str.h"

int main()
{
	cppy::PyStr a("{}X{}Y{}");
	auto b = a.split(" ");
	for (size_t i = 0; i < b.size(); i++)
	{
		std::cout << i << std::endl;
		std::cout << b[i].toString() << std::endl;
	}

	std::cout << a.format("A", "B", 12345678).toString() << std::endl;
	return 0;
}

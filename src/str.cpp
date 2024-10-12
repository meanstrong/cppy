#include <string_view>
#include <iomanip>
#include<sstream>
#include <algorithm>

#include "cppy/str.h"


namespace cppy
{
	PyStr::PyStr(const char* chars) :m_str(chars) {
	}

	PyStr::PyStr(const std::string& s) :m_str(s) {}

	PyStr::PyStr(int i) {
		m_str = std::to_string(i);
	}

	PyStr::PyStr(double d, int precision) {
		std::ostringstream ss;
		std::string nstr{""}, estr{ "" };
		if ((d > -1.0e15 && d < -1.0e-5) || (d > 1.0e-5 && d < 1.0e15))
		{
			ss << std::fixed << std::setprecision(precision) << d;
			nstr = ss.str();
		}
		else
		{
			ss << std::scientific << std::setprecision(precision) << d;
			nstr = ss.str();
			size_t position = nstr.find('e');
			if (position != std::string::npos)
			{
				estr = nstr.substr(position);
				nstr = nstr.substr(0, position);
			}
		}
		if (nstr.find('.') != std::string::npos)
		{
			size_t found = nstr.find_last_not_of('0');
			if (found != std::string::npos)
			{
				nstr.erase(found + 1);
			}
			if (*(nstr.end() - 1) == '.')
			{
				nstr.erase(nstr.size() - 1);
			}
		}
		size_t found = estr.find_last_not_of('0');
		if (found != std::string::npos && found == 1)
		{
			m_str = nstr;
		}
		else
		{
			m_str = nstr + estr;
		}
	}

	std::string PyStr::toString() const {
		return m_str;
	}

	int PyStr::toInt() const {
		return std::atoi(m_str.c_str());
	}

	double PyStr::toDouble() const {
		return std::stod(m_str);
	}

	int PyStr::length() const {
		return int(m_str.size());
	}

	int PyStr::count(const std::string& sub, int start, int end) const {
		int nummatches = 0;
		int cursor = start;

		while (1)
		{
			cursor = find(sub, cursor, end);

			if (cursor < 0) break;

			cursor += (int)sub.size();
			nummatches += 1;
		}

		return nummatches;
	}

	std::array<PyStr, 3> PyStr::partition(const std::string& sep) const {
		std::array<PyStr, 3> result;
		int index = find(sep);
		if (index < 0)
		{
			result[0] = PyStr(m_str);
			result[1] = PyStr();
			result[2] = PyStr();
		}
		else
		{
			result[0] = PyStr(m_str.substr(0, index));
			result[1] = PyStr(sep);
			result[2] = PyStr(m_str.substr(index + sep.size(), m_str.size()));
		}
		return result;
	}

	std::array<PyStr, 3> PyStr::rpartition(const std::string& sep) const {
		std::array<PyStr, 3> result;
		int index = rfind(sep);
		if (index < 0)
		{
			result[0] = PyStr();
			result[1] = PyStr();
			result[2] = PyStr(m_str);
		}
		else
		{
			result[0] = PyStr(m_str.substr(0, index));
			result[1] = PyStr(sep);
			result[2] = PyStr(m_str.substr(index + sep.size(), m_str.size()));
		}
		return result;
	}

	bool PyStr::startswith(const std::string& prefix) const
	{
		size_t pos = m_str.rfind(prefix, 0);
		return pos == 0;
	}

	bool PyStr::endswith(const std::string& suffix) const
	{
		if (suffix.size() > m_str.size())
			return false;
		return m_str.compare(m_str.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	int PyStr::find(const std::string& sub, int start, int end) const
	{
		int len = length();

		if (end > len) end = len;
		else if (end < 0) {
			end += len;
			if (end < 0) end = 0;
		}
		if (start < 0)
		{
			start += len;
			if (start < 0) start = 0;
		}

		std::string::size_type result = m_str.find(sub, start);

		if (result == std::string::npos ||
			(result + sub.size() > (std::string::size_type)end))
		{
			return -1;
		}

		return (int)result;
	}

	int PyStr::index(const std::string& sub, int start, int end) const {
		return find(sub, start, end);
	}

	int PyStr::rfind(const std::string& sub, int start, int end) const
	{
		int len = length();

		if (end > len) end = len;
		else if (end < 0) {
			end += len;
			if (end < 0) end = 0;
		}
		if (start < 0)
		{
			start += len;
			if (start < 0) start = 0;
		}

		std::string::size_type result = m_str.rfind(sub, end);

		if (result == std::string::npos ||
			result < (std::string::size_type)start ||
			(result + sub.size() > (std::string::size_type)end))
			return -1;

		return (int)result;
	}

	int PyStr::rindex(const std::string& sub, int start, int end) const {
		return rfind(sub, start, end);
	}

	PyStr PyStr::strip(const signed char& ch) const
	{
		int start = 0;
		int end = int(m_str.size()) - 1;
		while ((ch == -1 ? m_str.at(start) <= 0x20 : m_str.at(start) == ch))
		{
			if (++start > end)
			{
				return PyStr();
			}
		}

		while (ch == -1 ? m_str.at(end) <= 0x20 : m_str.at(end) == ch)
		{
			if (--end < start)
			{
				return PyStr();
			}
		}

		return PyStr(m_str.substr(start, end + 1));
	}

	PyStr PyStr::strip(const std::string& ch) const {
		int len = length(), i, j, chlen = (int)ch.size();

		if (chlen == 0)
		{
			i = 0;
			while (i < len && ::isspace(m_str[i]))
			{
				i++;
			}

			j = len;
			do
			{
				j--;
			} while (j >= i && ::isspace(m_str[j]));

			j++;
		}
		else
		{
			const char* sep = ch.c_str();

			i = 0;
			while (i < len && memchr(sep, m_str[i], chlen))
			{
				i++;
			}

			j = len;
			do
			{
				j--;
			} while (j >= i && memchr(sep, m_str[j], chlen));
			j++;
		}

		if (i == 0 && j == len)
		{
			return PyStr(m_str);
		}
		else
		{
			return PyStr(m_str.substr(i, j - i));
		}
	}

	PyStr PyStr::slice(int start, int stop, int step) const
	{
		int len = length();

		if (stop > len) stop = len;
		else if (stop < 0) {
			stop += len;
			if (stop < 0) stop = 0;
		}
		if (start < 0)
		{
			start += len;
			if (start < 0) start = 0;
		}

		if (start >= stop) return PyStr();
		return PyStr(m_str.substr(start, stop - start));
	}

	PyStr PyStr::join(const std::vector<std::string>& iterable) const {
		std::vector< std::string >::size_type len = iterable.size(), i;

		if (len == 0) return PyStr();
		if (len == 1) return PyStr(iterable[0]);

		std::string result(iterable[0]);
		for (i = 1; i < len; ++i)
		{
			result += m_str + iterable[i];
		}
		return PyStr(result);
	}

	std::vector<PyStr> PyStr::split(const std::string& sep, int maxsplit) const
	{
		std::vector<PyStr> result;

		if (maxsplit < 0) maxsplit = INT_MAX;

		// split on any whitespace character
		if (sep.size() == 0)
		{
			std::string::size_type i, j, len = m_str.size();
			for (i = j = 0; i < len; )
			{

				while (i < len && ::isspace(m_str[i])) i++;
				j = i;

				while (i < len && !::isspace(m_str[i])) i++;



				if (j < i)
				{
					if (maxsplit-- <= 0) break;

					result.push_back(PyStr(m_str.substr(j, i - j)));

					while (i < len && ::isspace(m_str[i])) i++;
					j = i;
				}
			}
			if (j < len)
			{
				result.push_back(PyStr(m_str.substr(j, len - j)));
			}
		}
		else {
			std::string::size_type i, j, len = m_str.size(), n = sep.size();

			i = j = 0;

			while (i + n <= len)
			{
				if (m_str[i] == sep[0] && m_str.substr(i, n) == sep)
				{
					if (maxsplit-- <= 0) break;

					result.push_back(PyStr(m_str.substr(j, i - j)));
					i = j = i + n;
				}
				else
				{
					i++;
				}
			}
			result.push_back(PyStr(m_str.substr(j, len - j)));
		}

		return result;
	}

	PyStr PyStr::replace(const std::string& old_str, const std::string& new_str, int count) const {
		std::string result = m_str;
		std::string::size_type start_pos = 0;
		if (count < 0) count = INT_MAX;
		int finded = 0;
		while (finded++ < count && (start_pos = result.find(old_str, start_pos)) != std::string::npos) {
			result.replace(start_pos, old_str.length(), new_str);
			start_pos += new_str.length();
		}
		return PyStr(result);
	}

	PyStr PyStr::lower() const {
		std::string result(m_str);
		std::string::size_type len = result.size(), i;

		for (i = 0; i < len; ++i)
		{
			if (::isupper(result[i])) result[i] = (char) ::tolower(result[i]);
		}

		return PyStr(result);
	}

	PyStr PyStr::upper() const {
		std::string result(m_str);
		std::string::size_type len = result.size(), i;

		for (i = 0; i < len; ++i)
		{
			if (::islower(result[i])) result[i] = (char) ::toupper(result[i]);
		}

		return PyStr(result);
	}

	PyStr PyStr::swapcase() const {
		std::string result(m_str);
		std::string::size_type len = result.size(), i;

		for (i = 0; i < len; ++i)
		{
			if (::islower(result[i])) result[i] = (char) ::toupper(result[i]);
			else if (::isupper(result[i])) result[i] = (char) ::tolower(result[i]);
		}

		return PyStr(result);
	}

	PyStr PyStr::title() const {
		std::string result(m_str);
		std::string::size_type len = result.size(), i;
		bool previous_is_cased = false;

		for (i = 0; i < len; ++i)
		{
			int c = result[i];
			if (::islower(c))
			{
				if (!previous_is_cased)
				{
					result[i] = (char) ::toupper(c);
				}
				previous_is_cased = true;
			}
			else if (::isupper(c))
			{
				if (previous_is_cased)
				{
					result[i] = (char) ::tolower(c);
				}
				previous_is_cased = true;
			}
			else
			{
				previous_is_cased = false;
			}
		}

		return PyStr(result);
	}

	PyStr PyStr::expandtabs(int tabsize) const {
		std::string result(m_str);

		std::string::size_type len = m_str.size(), i = 0;
		int offset = 0;

		int j = 0;

		for (i = 0; i < len; ++i)
		{
			if (m_str[i] == '\t')
			{
				if (tabsize > 0)
				{
					int fillsize = tabsize - (j % tabsize);
					j += fillsize;
					result.replace(i + offset, 1, std::string(fillsize, ' '));
					offset += fillsize - 1;
				}
				else
				{
					result.replace(i + offset, 1, "");
					offset -= 1;
				}
			}
			else
			{
				j++;
				if (m_str[i] == '\n' || m_str[i] == '\r')
				{
					j = 0;
				}
			}
		}

		return PyStr(result);
	}

	std::vector<PyStr> PyStr::splitlines(bool keepends) const {
		std::vector<PyStr> result;
		std::string::size_type len = m_str.size(), i, j, eol;

		for (i = j = 0; i < len; )
		{
			while (i < len && m_str[i] != '\n' && m_str[i] != '\r') i++;

			eol = i;
			if (i < len)
			{
				if (m_str[i] == '\r' && i + 1 < len && m_str[i + 1] == '\n')
				{
					i += 2;
				}
				else
				{
					i++;
				}
				if (keepends)
					eol = i;

			}

			result.push_back(PyStr(m_str.substr(j, eol - j)));
			j = i;

		}

		if (j < len)
		{
			result.push_back(PyStr(m_str.substr(j, len - j)));
		}
		return result;
	}

	PyStr PyStr::removeprefix(const std::string& prefix) const {
		if (startswith(prefix))
		{
			return PyStr(m_str.substr(prefix.length()));
		}

		return PyStr(m_str);
	}

	PyStr PyStr::removesuffix(const std::string& suffix) const {
		if (endswith(suffix))
		{
			return PyStr(m_str.substr(0, m_str.length() - suffix.length()));
		}

		return PyStr(m_str);
	}

	PyStr PyStr::zfill(int width) const {
		int len = length();

		if (len >= width)
		{
			return PyStr(m_str);
		}

		std::string result(m_str);

		int fill = width - len;

		result = std::string(fill, '0') + result;


		if (result[fill] == '+' || result[fill] == '-')
		{
			result[0] = result[fill];
			result[fill] = '0';
		}

		return PyStr(result);
	}

	PyStr PyStr::ljust(int width, char fillchar) const {
		std::string::size_type len = m_str.size();
		if (((int)len) >= width) return PyStr(m_str);
		return PyStr(m_str + std::string(width - len, fillchar));
	}

	PyStr PyStr::rjust(int width, char fillchar) const {
		std::string::size_type len = m_str.size();
		if (((int)len) >= width) return PyStr(m_str);
		return PyStr(std::string(width - len, ' ') + m_str);
	}

	PyStr PyStr::center(int width, char fillchar) const {
		int len = length();
		int marg, left;

		if (len >= width) return PyStr(m_str);

		marg = width - len;
		left = marg / 2 + (marg & width & 1);

		return PyStr(std::string(left, ' ') + m_str + std::string(marg - left, ' '));
	}

	PyStr PyStr::capitalize() const {
		std::string result(m_str);
		std::string::size_type len = result.size(), i;

		if (len > 0)
		{
			if (::islower(result[0])) result[0] = (char) ::toupper(result[0]);
		}

		for (i = 1; i < len; ++i)
		{
			if (::isupper(result[i])) result[i] = (char) ::tolower(result[i]);
		}

		return PyStr(result);
	}

	bool PyStr::isspace() const
	{
		std::string::size_type len = m_str.size(), i;
		if (len == 0) return false;
		if (len == 1) return ::isspace(m_str[0]);

		for (i = 0; i < len; ++i)
		{
			if (!::isspace(m_str[i])) return false;
		}
		return true;
	}

	bool PyStr::isalnum() const
	{
		std::string::size_type len = m_str.size(), i;
		if (len == 0) return false;


		if (len == 1)
		{
			return ::isalnum(m_str[0]);
		}

		for (i = 0; i < len; ++i)
		{
			if (!::isalnum(m_str[i])) return false;
		}
		return true;
	}

	bool PyStr::isalpha() const
	{
		std::string::size_type len = m_str.size(), i;
		if (len == 0) return false;
		if (len == 1) return ::isalpha((int)m_str[0]);

		for (i = 0; i < len; ++i)
		{
			if (!::isalpha((int)m_str[i])) return false;
		}
		return true;
	}

	bool PyStr::isdigit() const
	{
		std::string::size_type len = m_str.size(), i;
		if (len == 0) return false;
		if (len == 1) return ::isdigit(m_str[0]);

		for (i = 0; i < len; ++i)
		{
			if (!::isdigit(m_str[i])) return false;
		}
		return true;
	}

	bool PyStr::islower() const
	{
		std::string::size_type len = m_str.size(), i;
		if (len == 0) return false;
		if (len == 1) return ::islower(m_str[0]);

		for (i = 0; i < len; ++i)
		{
			if (!::islower(m_str[i])) return false;
		}
		return true;
	}

	bool PyStr::isupper() const
	{
		std::string::size_type len = m_str.size(), i;
		if (len == 0) return false;
		if (len == 1) return ::isupper(m_str[0]);

		for (i = 0; i < len; ++i)
		{
			if (!::isupper(m_str[i])) return false;
		}
		return true;
	}

	bool PyStr::istitle() const
	{
		std::string::size_type len = m_str.size(), i;

		if (len == 0) return false;
		if (len == 1) return ::isupper(m_str[0]);

		bool cased = false, previous_is_cased = false;

		for (i = 0; i < len; ++i)
		{
			if (::isupper(m_str[i]))
			{
				if (previous_is_cased)
				{
					return false;
				}

				previous_is_cased = true;
				cased = true;
			}
			else if (::islower(m_str[i]))
			{
				if (!previous_is_cased)
				{
					return false;
				}

				previous_is_cased = true;
				cased = true;

			}
			else
			{
				previous_is_cased = false;
			}
		}

		return cased;
	}

	bool PyStr::contains(const std::string& other) const {
		return m_str.find(other) != std::string::npos;
	}

	char PyStr::at(int index) const {
		return m_str.at(index >= 0 ? index : index + length());
	}

	char PyStr::operator[](int index) const {
		return at(index);
	}

	bool PyStr::equal(const std::string& other) const {
		return m_str == other;
	}

	bool PyStr::operator==(const std::string& other) const {
		return equal(other);
	}

	PyStr PyStr::mul(int n) const {
		if (n <= 0) return PyStr();
		if (n == 1) return PyStr(m_str);

		std::ostringstream os;
		for (int i = 0; i < n; ++i)
		{
			os << m_str;
		}
		return PyStr(os.str());
	}
}

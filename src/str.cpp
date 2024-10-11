#include <string_view>
#include <iomanip>
#include<sstream>
#include <algorithm>

#include "cppy/str.h"


namespace cppy
{
	str::str(const char* chars) :m_str(chars) {
	}

	str::str(const std::string& s) :m_str(s) {}

	str::str(int i) {
		m_str = std::to_string(i);
	}

	str::str(double d, int precision) {
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

	std::string str::toString() const {
		return m_str;
	}

	int str::toInt() const {
		return std::atoi(m_str.c_str());
	}

	double str::toDouble() const {
		return std::stod(m_str);
	}

	int str::length() const {
		return int(m_str.size());
	}

	bool str::startswith(const std::string& prefix) const
	{
		size_t pos = m_str.rfind(prefix, 0);
		return pos == 0;
	}

	bool str::endswith(const std::string& suffix) const
	{
		if (suffix.size() > m_str.size())
			return false;
		return m_str.compare(m_str.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	int str::find(const std::string& sub, int start, int end) const
	{
		if (start > length())
		{
			return -1;
		}

		end = end > length() ? length() : end;
		std::string_view view(m_str.data() + start, end - start);
		auto pos = view.find(sub.data());

		return pos == std::string::npos ? -1 : start + int(pos);
	}

	str str::strip(const signed char& ch) const
	{
		std::string buffer = m_str;

		int i = 0;
		while (i < int(buffer.size()) && (ch == -1 ? buffer[i] <= 0x20 : buffer[i] == ch))
		{
			++i;
		}
		buffer.erase(buffer.begin(), buffer.begin() + i);

		i = int(buffer.size()) - 1;
		while (ch == -1 ? buffer[i] <= 0x20 : buffer[i] == ch)
		{
			if (--i < 0)
			{
				break;
			}
		}

		return str(buffer.substr(0, i + 1));
	}

	str str::slice(int start, int stop, int step) const
	{
		start = start < 0 ? start + length() : start;
		stop = stop < 0 ? stop + length() : stop;

		std::string buffer;
		for (int i = start; (step > 0) ? (i < stop) : (i > stop); i += step)
		{
			buffer += m_str[i];
		}

		return str(buffer);
	}

	std::vector<str> str::split(const std::string& sep) const
	{
		std::vector<str> result;
		if (sep.size() == 0)
		{
			return result;
		}

		int start = 0;
		for (int index = 0; (index = find(sep, start)) != -1; start = index + int(sep.size()))
		{
			result.push_back(str(m_str.substr(start, index - start)));
		}
		if (start != m_str.size())
		{
			result.push_back(str(m_str.substr(start)));
		}

		return result;
	}

	str str::replace(const std::string& old_str, const std::string& new_str) const {
		std::string result = m_str;
		size_t start_pos = 0;
		while ((start_pos = result.find(old_str, start_pos)) != std::string::npos) {
			result.replace(start_pos, old_str.length(), new_str);
			start_pos += new_str.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
		return str(result);
	}

	str str::lower() const {
		std::string result = m_str;
		size_t start_pos = 0;
		std::for_each(result.begin(), result.end(), [](char& c)
			{ c |= 0b0010'0000; });
		return str(result);
	}

	str str::upper() const {
		std::string result = m_str;
		size_t start_pos = 0;
		std::for_each(result.begin(), result.end(), [](char& c)
			{ c &= 0b1101'1111; });
		return str(result);
	}

	bool str::contains(const std::string& other) const {
		return m_str.find(other) != std::string::npos;
	}

	char str::operator[](int index) const {
		return m_str.at(index >= 0 ? index : index + length());
	}

	bool str::operator==(const str& that) const {
		return m_str == that.toString();
	}
}

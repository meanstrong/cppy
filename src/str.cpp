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
		if (start > length())
		{
			return -1;
		}

		end = end > length() ? length() : end;
		std::string_view view(m_str.c_str() + start, end - start);
		auto pos = view.find(sub.c_str());

		return pos == std::string::npos ? -1 : start + int(pos);
	}

	PyStr PyStr::strip(const signed char& ch) const
	{
		int start = 0;
		int end = int(m_str.size()) - 1;
		while ((ch == -1 ? m_str.at(start) <= 0x20 : m_str.at(start) == ch))
		{
			if (++start > end)
			{
				return PyStr("");
			}
		}

		while (ch == -1 ? m_str.at(end) <= 0x20 : m_str.at(end) == ch)
		{
			if (--end < start)
			{
				return PyStr("");
			}
		}

		return PyStr(m_str.substr(start, end + 1));
	}

	PyStr PyStr::strip(const std::string& ch) const {
		int start = 0;
		int end = int(m_str.size()) - 1;
		while (ch.find(m_str.at(start++)) != std::string::npos)
		{
			if (start > end)
			{
				return PyStr("");
			}
		}

		while (ch.find(m_str.at(end--)) != std::string::npos)
		{
			if (end < start)
			{
				return PyStr("");
			}
		}
		return PyStr(m_str.substr(start, end + 1));
	}

	PyStr PyStr::slice(int start, int stop, int step) const
	{
		start = start < 0 ? start + length() : start;
		stop = stop < 0 ? stop + length() : stop;

		std::string buffer;
		for (int i = start; (step > 0) ? (i < stop) : (i > stop); i += step)
		{
			buffer += m_str[i];
		}

		return PyStr(buffer);
	}

	std::vector<PyStr> PyStr::split(const std::string& sep) const
	{
		std::vector<PyStr> result;
		if (sep.size() == 0)
		{
			return result;
		}

		int start = 0;
		for (int index = 0; (index = find(sep, start)) != -1; start = index + int(sep.size()))
		{
			result.push_back(PyStr(m_str.substr(start, index - start)));
		}
		if (start != m_str.size())
		{
			result.push_back(PyStr(m_str.substr(start)));
		}

		return result;
	}

	PyStr PyStr::replace(const std::string& old_str, const std::string& new_str, int count) const {
		std::string result = m_str;
		size_t start_pos = 0;
		count = count < 0 ? INT_MAX : count;
		int finded = 0;
		while (finded++ < count && (start_pos = result.find(old_str, start_pos)) != std::string::npos) {
			result.replace(start_pos, old_str.length(), new_str);
			start_pos += new_str.length();
		}
		return PyStr(result);
	}

	PyStr PyStr::lower() const {
		std::string result = m_str;
		size_t start_pos = 0;
		std::for_each(result.begin(), result.end(), [](char& c)
			{ c |= 0b0010'0000; });
		return PyStr(result);
	}

	PyStr PyStr::upper() const {
		std::string result = m_str;
		size_t start_pos = 0;
		std::for_each(result.begin(), result.end(), [](char& c)
			{ c &= 0b1101'1111; });
		return PyStr(result);
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
}

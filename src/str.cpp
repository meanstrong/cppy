#include <string_view>
#include <iomanip>
#include<sstream>
#include <algorithm>

#include "cppy/str.h"


CPPY_API PyException CPPY_STR_init(const char* chars, std::string* const result) {
	*result = chars;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_init(int i, std::string* const result) {
	*result = std::to_string(i);
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_init(double d, int precision, std::string* const result) {
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
		*result = nstr;
	}
	else
	{
		*result = nstr + estr;
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_length(const std::string& str, int* result) {
	*result = (int)str.size();
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_count(const std::string& str, const std::string& sub, int* const result) {
	return CPPY_STR_count(str, sub, 0, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_count(const std::string& str, const std::string& sub, int start, int* const result) {
	return CPPY_STR_count(str, sub, start, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_count(const std::string& str, const std::string& sub, int start, int end, int* const result) {
	*result = 0;
	int cursor = start;

	while (1)
	{
		CPPY_STR_find(str, sub, cursor, end, &cursor);

		if (cursor < 0) break;

		cursor += (int)sub.size();
		*result += 1;
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_partition(const std::string& str, const std::string& sep, std::string** const result) {
	int index = 0;
	CPPY_STR_find(str, sep, &index);
	if (index < 0)
	{
		*(result[0]) = str;
		*(result[1]) = "";
		*(result[2]) = "";
	}
	else
	{
		*(result[0]) = str.substr(0, index);
		*(result[1]) = sep;
		*(result[2]) = str.substr(index + sep.size(), str.size());
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_rpartition(const std::string& str, const std::string& sep, std::string** const result) {
	int index = 0;
	CPPY_STR_rfind(str, sep, &index);
	if (index < 0)
	{
		*(result[0]) = "";
		*(result[1]) = "";
		*(result[2]) = str;
	}
	else
	{
		*(result[0]) = str.substr(0, index);
		*(result[1]) = sep;
		*(result[2]) = str.substr(index + sep.size(), str.size());
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_startswith(const std::string& str, const std::string& prefix, bool* const result)
{
	size_t pos = str.rfind(prefix, 0);
	*result = pos == 0;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_endswith(const std::string& str, const std::string& suffix, bool* const result)
{
	if (suffix.size() > str.size())
		*result = false;
	else
	{
		*result = str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_find(const std::string& str, const std::string& sub, int* const result) {
	return CPPY_STR_find(str, sub, 0, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_find(const std::string& str, const std::string& sub, int start, int* const result) {
	return CPPY_STR_find(str, sub, start, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_find(const std::string& str, const std::string& sub, int start, int end, int* const result)
{
	int len = (int)str.length();

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

	std::string::size_type position = str.find(sub, start);

	if (position == std::string::npos ||
		(position + sub.size() > (std::string::size_type)end))
	{
		*result = -1;
	}

	*result = (int)position;

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_index(const std::string& str, const std::string& sub, int* const result) {
	return CPPY_STR_index(str, sub, 0, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_index(const std::string& str, const std::string& sub, int start, int* const result) {
	return CPPY_STR_index(str, sub, start, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_index(const std::string& str, const std::string& sub, int start, int end, int* const result) {
	CPPY_STR_find(str, sub, start, end, result);
	if (*result < 0) return PyException::ValueError;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_rfind(const std::string& str, const std::string& sub, int* const result) {
	return CPPY_STR_rfind(str, sub, 0, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_rfind(const std::string& str, const std::string& sub, int start, int* const result) {
	return CPPY_STR_rfind(str, sub, start, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_rfind(const std::string& str, const std::string& sub, int start, int end, int* const result)
{
	int len = (int)str.length();

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

	std::string::size_type position = str.rfind(sub, end);

	if (position == std::string::npos ||
		position < (std::string::size_type)start ||
		(position + sub.size() > (std::string::size_type)end))
		*result = -1;

	*result = (int)position;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_rindex(const std::string& str, const std::string& sub, int* const result) {
	return CPPY_STR_rindex(str, sub, 0, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_rindex(const std::string& str, const std::string& sub, int start, int* const result) {
	return CPPY_STR_rindex(str, sub, start, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_rindex(const std::string& str, const std::string& sub, int start, int end, int* const result) {
	CPPY_STR_rfind(str, sub, start, end, result);
	if (*result < 0) return PyException::ValueError;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_strip(const std::string& str, std::string* const result) {
	int len = (int)str.length();
	int i = 0, j = len;

	while (i < len && ::isspace(str[i]))
	{
		i++;
	}

	do
	{
		j--;
	} while (j >= i && ::isspace(str[j]));

	j++;

	if (i == 0 && j == len)
	{
		*result = str;
	}
	else
	{
		*result = str.substr(i, j - i);
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_strip(const std::string& str, const std::string& ch, std::string* const result) {
	int chlen = (int)ch.size();

	if (chlen == 0)
	{
		return CPPY_STR_strip(str, result);
	}

	int len = (int)str.length();
	int i = 0, j = len;
	const char* sep = ch.c_str();

	while (i < len && memchr(sep, str[i], chlen))
	{
		i++;
	}

	do
	{
		j--;
	} while (j >= i && memchr(sep, str[j], chlen));
	j++;


	if (i == 0 && j == len)
	{
		*result = str;
	}
	else
	{
		*result = str.substr(i, j - i);
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_slice(const std::string& str, int start, int stop, std::string* const result) {
	return CPPY_STR_slice(str, start, stop, 1, result);
}

CPPY_API PyException CPPY_STR_slice(const std::string& str, int start, int stop, int step, std::string* const result)
{
	int len = (int)str.length();

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

	if (start >= stop) *result = "";
	*result = str.substr(start, stop - start);
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_join(const std::string& str, int n_iterables, const std::string iterable[], std::string* const result) {
	if (n_iterables <= 0) {
		*result = "";
		return PyException::Ok;
	}
	if (n_iterables == 1) {
		*result = iterable[0];
		return PyException::Ok;
	}

	*result = iterable[0];
	for (int i = 1; i < n_iterables; ++i)
	{
		*result += str + iterable[i];
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_split(const std::string& str, std::vector<std::string>* const result) {
	return CPPY_STR_split(str, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_split(const std::string& str, int maxsplit, std::vector<std::string>* const result) {
	if (maxsplit < 0) maxsplit = INT_MAX;
	std::string::size_type i, j, len = str.size();
	for (i = j = 0; i < len; )
	{

		while (i < len && ::isspace(str[i])) i++;
		j = i;

		while (i < len && !::isspace(str[i])) i++;



		if (j < i)
		{
			if (maxsplit-- <= 0) break;

			result->push_back(str.substr(j, i - j));

			while (i < len && ::isspace(str[i])) i++;
			j = i;
		}
	}
	if (j < len)
	{
		result->push_back(str.substr(j, len - j));
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_split(const std::string& str, const std::string& sep, std::vector<std::string>* const result) {
	return CPPY_STR_split(str, sep, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_split(const std::string& str, const std::string& sep, int maxsplit, std::vector<std::string>* const result)
{
	if (maxsplit < 0) maxsplit = INT_MAX;

	// split on any whitespace character
	if (sep.size() == 0)
	{
		CPPY_STR_split(str, maxsplit, result);
	}
	else {
		std::string::size_type i, j, len = str.size(), n = sep.size();

		i = j = 0;

		while (i + n <= len)
		{
			if (str[i] == sep[0] && str.substr(i, n) == sep)
			{
				if (maxsplit-- <= 0) break;

				result->push_back(str.substr(j, i - j));
				i = j = i + n;
			}
			else
			{
				i++;
			}
		}
		result->push_back(str.substr(j, len - j));
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_replace(const std::string& str, const std::string& old_str, const std::string& new_str, std::string* const result) {
	return CPPY_STR_replace(str, old_str, new_str, INT_MAX, result);
}

CPPY_API PyException CPPY_STR_replace(const std::string& str, const std::string& old_str, const std::string& new_str, int count, std::string* const result) {
	*result = str;
	std::string::size_type start_pos = 0;
	if (count < 0) count = INT_MAX;
	int finded = 0;
	while (finded++ < count && (start_pos = result->find(old_str, start_pos)) != std::string::npos) {
		result->replace(start_pos, old_str.length(), new_str);
		start_pos += new_str.length();
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_lower(const std::string& str, std::string* const result) {
	*result = str;
	std::string::size_type len = str.size(), i;

	for (i = 0; i < len; ++i)
	{
		if (::isupper(str[i])) (*result)[i] = (char) ::tolower(str[i]);
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_upper(const std::string& str, std::string* const result) {
	*result = str;
	std::string::size_type len = str.size(), i;

	for (i = 0; i < len; ++i)
	{
		if (::islower(str[i])) (*result)[i] = (char) ::toupper(str[i]);
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_swapcase(const std::string& str, std::string* const result) {
	*result = str;
	std::string::size_type len = str.size(), i;

	for (i = 0; i < len; ++i)
	{
		if (::islower(str[i])) (*result)[i] = (char) ::toupper(str[i]);
		else if (::isupper(str[i])) (*result)[i] = (char) ::tolower(str[i]);
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_title(const std::string& str, std::string* const result) {
	*result = str;
	std::string::size_type len = str.size(), i;
	bool previous_is_cased = false;

	for (i = 0; i < len; ++i)
	{
		int c = str[i];
		if (::islower(c))
		{
			if (!previous_is_cased)
			{
				(*result)[i] = (char) ::toupper(c);
			}
			previous_is_cased = true;
		}
		else if (::isupper(c))
		{
			if (previous_is_cased)
			{
				(*result)[i] = (char) ::tolower(c);
			}
			previous_is_cased = true;
		}
		else
		{
			previous_is_cased = false;
		}
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_expandtabs(const std::string& str, std::string* const result) {
	return CPPY_STR_expandtabs(str, 8, result);
}

CPPY_API PyException CPPY_STR_expandtabs(const std::string& str, int tabsize, std::string* const result) {
	*result = str;

	std::string::size_type len = str.size(), i = 0;
	int offset = 0;

	int j = 0;

	for (i = 0; i < len; ++i)
	{
		if (str[i] == '\t')
		{
			if (tabsize > 0)
			{
				int fillsize = tabsize - (j % tabsize);
				j += fillsize;
				result->replace(i + offset, 1, std::string(fillsize, ' '));
				offset += fillsize - 1;
			}
			else
			{
				result->replace(i + offset, 1, "");
				offset -= 1;
			}
		}
		else
		{
			j++;
			if (str[i] == '\n' || str[i] == '\r')
			{
				j = 0;
			}
		}
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_splitlines(const std::string& str, std::vector<std::string>* const result) {
	return CPPY_STR_splitlines(str, false, result);
}

CPPY_API PyException CPPY_STR_splitlines(const std::string& str, bool keepends, std::vector<std::string>* const result) {
	std::string::size_type len = str.size(), i, j, eol;

	for (i = j = 0; i < len; )
	{
		while (i < len && str[i] != '\n' && str[i] != '\r') i++;

		eol = i;
		if (i < len)
		{
			if (str[i] == '\r' && i + 1 < len && str[i + 1] == '\n')
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

		result->push_back(str.substr(j, eol - j));
		j = i;

	}

	if (j < len)
	{
		result->push_back(str.substr(j, len - j));
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_removeprefix(const std::string& str, const std::string& prefix, std::string* const result) {
	bool whether;
	CPPY_STR_startswith(str, prefix, &whether);
	if (whether)
	{
		*result = str.substr(prefix.length());
	}
	else {
		*result = str;
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_removesuffix(const std::string& str, const std::string& suffix, std::string* const result) {
	bool whether;
	CPPY_STR_endswith(str, suffix, &whether);
	if (whether)
	{
		*result = str.substr(0, str.length() - suffix.length());
	}
	else
	{
		*result = str;
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_zfill(const std::string& str, int width, std::string* const result) {
	int len = (int)str.length();
	if (len >= width)
	{
		*result = str;
		return PyException::Ok;
	}

	int fill = width - len;

	*result = std::string(fill, '0') + str;


	if ((*result)[fill] == '+' || (*result)[fill] == '-')
	{
		(*result)[0] = (*result)[fill];
		(*result)[fill] = '0';
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_ljust(const std::string& str, int width, std::string* const result) {
	return CPPY_STR_ljust(str, width, ' ', result);
}

CPPY_API PyException CPPY_STR_ljust(const std::string& str, int width, char fillchar, std::string* const result) {
	std::string::size_type len = str.size();
	if (((int)len) >= width) {
		*result = str;
	}
	else
	{
		*result = str + std::string(width - len, fillchar);
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_rjust(const std::string& str, int width, std::string* const result) {
	return CPPY_STR_rjust(str, width, ' ', result);
}

CPPY_API PyException CPPY_STR_rjust(const std::string& str, int width, char fillchar, std::string* const result) {
	std::string::size_type len = str.size();
	if (((int)len) >= width) {
		*result = str;
	}
	else
	{
		*result = std::string(width - len, ' ') + str;
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_center(const std::string& str, int width, std::string* const result) {
	return CPPY_STR_center(str, width, ' ', result);
}

CPPY_API PyException CPPY_STR_center(const std::string& str, int width, char fillchar, std::string* const result) {
	int len = (int)str.length();
	if (len >= width) {
		*result = str;
		return PyException::Ok;
	}
	int marg, left;
	marg = width - len;
	left = marg / 2 + (marg & width & 1);

	*result = std::string(left, ' ') + str + std::string(marg - left, ' ');
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_capitalize(const std::string& str, std::string* const result) {
	*result = str;
	std::string::size_type len = str.size(), i;

	if (len > 0)
	{
		if (::islower(str[0])) (*result)[0] = (char) ::toupper(str[0]);
	}

	for (i = 1; i < len; ++i)
	{
		if (::isupper(str[i])) (*result)[i] = (char) ::tolower(str[i]);
	}

	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_isspace(const std::string& str, bool* const result)
{
	std::string::size_type len = str.size(), i;
	if (len == 0) {
		*result = false;
		return PyException::Ok;
	}
	if (len == 1) {
		*result = ::isspace(str[0]);
		return PyException::Ok;
	}

	for (i = 0; i < len; ++i)
	{
		if (!::isspace(str[i])) {
			*result = false;
			return PyException::Ok;
		}
	}
	*result = true;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_isalnum(const std::string& str, bool* const result)
{
	std::string::size_type len = str.size(), i;
	if (len == 0) {
		*result = false;
		return PyException::Ok;
	}
	if (len == 1)
	{
		*result = ::isalnum(str[0]);
		return PyException::Ok;
	}

	for (i = 0; i < len; ++i)
	{
		if (!::isalnum(str[i])) {
			*result = false;
			return PyException::Ok;
		}
	}
	*result = true;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_isalpha(const std::string& str, bool* const result)
{
	std::string::size_type len = str.size(), i;
	if (len == 0) {
		*result = false;
		return PyException::Ok;
	}
	if (len == 1) {
		*result = ::isalpha((int)str[0]);
		return PyException::Ok;
	}

	for (i = 0; i < len; ++i)
	{
		if (!::isalpha((int)str[i])) {
			*result = false;
			return PyException::Ok;
		}
	}
	*result = true;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_isdigit(const std::string& str, bool* const result)
{
	std::string::size_type len = str.size(), i;
	if (len == 0) {
		*result = false;
		return PyException::Ok;
	}
	if (len == 1) {
		*result = ::isdigit(str[0]);
		return PyException::Ok;
	}

	for (i = 0; i < len; ++i)
	{
		if (!::isdigit(str[i])) {
			*result = false;
			return PyException::Ok;
		}
	}
	*result = true;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_islower(const std::string& str, bool* const result)
{
	std::string::size_type len = str.size(), i;
	if (len == 0) {
		*result = false;
		return PyException::Ok;
	}
	if (len == 1) {
		*result = ::islower(str[0]);
		return PyException::Ok;
	}

	for (i = 0; i < len; ++i)
	{
		if (!::islower(str[i])) {
			*result = false;
			return PyException::Ok;
		}
	}
	*result = true;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_isupper(const std::string& str, bool* const result)
{
	std::string::size_type len = str.size(), i;
	if (len == 0) {
		*result = false;
		return PyException::Ok;
	}
	if (len == 1) {
		*result = ::isupper(str[0]);
		return PyException::Ok;
	}

	for (i = 0; i < len; ++i)
	{
		if (!::isupper(str[i])) {
			*result = false;
			return PyException::Ok;
		}
	}
	*result = true;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_istitle(const std::string& str, bool* const result)
{
	std::string::size_type len = str.size(), i;

	if (len == 0) {
		*result = false;
		return PyException::Ok;
	}
	if (len == 1) {
		*result = ::isupper(str[0]);
		return PyException::Ok;
	}

	bool cased = false, previous_is_cased = false;

	for (i = 0; i < len; ++i)
	{
		if (::isupper(str[i]))
		{
			if (previous_is_cased)
			{
				*result = false;
				return PyException::Ok;
			}

			previous_is_cased = true;
			cased = true;
		}
		else if (::islower(str[i]))
		{
			if (!previous_is_cased)
			{
				*result = false;
				return PyException::Ok;
			}

			previous_is_cased = true;
			cased = true;

		}
		else
		{
			previous_is_cased = false;
		}
	}

	*result = cased;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_contains(const std::string& str, const std::string& other, bool* const result) {
	*result = str.find(other) != std::string::npos;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_at(const std::string& str, int index, char* const result) {
	*result = str.at(index >= 0 ? index : index + str.length());
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_equal(const std::string& str, const std::string& other, bool* const result) {
	*result = str == other;
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_mul(const std::string& str, int n, std::string* const result) {
	if (n <= 0) {
		*result = "";
		return PyException::Ok;
	}
	if (n == 1) {
		*result = str;
		return PyException::Ok;
	}

	std::ostringstream os;
	for (int i = 0; i < n; ++i)
	{
		os << str;
	}
	*result = os.str();
	return PyException::Ok;
}


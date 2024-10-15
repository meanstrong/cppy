#ifndef CPPY_STR_H
#define CPPY_STR_H
#include <iostream>
#include <sstream> 
#include <vector>
#include <string>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"


CPPY_API PyException CPPY_STR_init(const char* chars, std::string* const result);

CPPY_API PyException CPPY_STR_init(int i, std::string* const result);

CPPY_API PyException CPPY_STR_init(double d, std::string* const result);
CPPY_API PyException CPPY_STR_init(double d, int precision, std::string* const result);

CPPY_API PyException CPPY_STR_length(const std::string& str, int* result);

/* S.count(sub[, start[, end]]) -> int
*
*  Return the number of non-overlapping occurrences of substring sub in
*  string S[start:end].  Optional arguments start and end are
*  interpreted as in slice notation.
*/
CPPY_API PyException CPPY_STR_count(const std::string& str, const std::string& sub, int* const result);
CPPY_API PyException CPPY_STR_count(const std::string& str, const std::string& sub, int start, int* const result);
CPPY_API PyException CPPY_STR_count(const std::string& str, const std::string& sub, int start, int end, int* const result);

/* Partition the string into three parts using the given separator.
*
*  This will search for the separator in the string.  If the separator is found,
*  returns a 3-tuple containing the part before the separator, the separator
*  itself, and the part after it.
*
*  If the separator is not found, returns a 3-tuple containing the original string
*  and two empty strings.
*/
CPPY_API PyException CPPY_STR_partition(const std::string& str, const std::string& sep, std::string** const result);

/* Partition the string into three parts using the given separator.
*
*  This will search for the separator in the string, starting at the end. If
*  the separator is found, returns a 3-tuple containing the part before the
*  separator, the separator itself, and the part after it.
*
*  If the separator is not found, returns a 3-tuple containing two empty strings
*  and the original string.
*/
CPPY_API PyException CPPY_STR_rpartition(const std::string& str, const std::string& sep, std::string** const result);

/* S.startswith(prefix[, start[, end]]) -> bool
*
*  Return True if S starts with the specified prefix, False otherwise.
*  With optional start, test S beginning at that position.
*  With optional end, stop comparing S at that position.
*  prefix can also be a tuple of strings to try.
*/
CPPY_API PyException CPPY_STR_startswith(const std::string& str, const std::string& prefix, bool* const result);

/* S.endswith(suffix[, start[, end]]) -> bool
*  Return True if S ends with the specified suffix, False otherwise.
*  With optional start, test S beginning at that position.
*  With optional end, stop comparing S at that position.
*  suffix can also be a tuple of strings to try.
*/
CPPY_API PyException CPPY_STR_endswith(const std::string& str, const std::string& suffix, bool* const result);

/* S.find(sub[, start[, end]]) -> int
*
*  Return the lowest index in S where substring sub is found,
*  such that sub is contained within S[start:end].  Optional
*  arguments start and end are interpreted as in slice notation.
*
*  Return -1 on failure.
*/
CPPY_API PyException CPPY_STR_find(const std::string& str, const std::string& sub, int* const result);
CPPY_API PyException CPPY_STR_find(const std::string& str, const std::string& sub, int start, int* const result);
CPPY_API PyException CPPY_STR_find(const std::string& str, const std::string& sub, int start, int end, int* const result);

/* S.index(sub[, start[, end]]) -> int
*
*  Return the lowest index in S where substring sub is found,
*  such that sub is contained within S[start:end].  Optional
*  arguments start and end are interpreted as in slice notation.
*
*  Return ValueError when the substring is not found.
*/
CPPY_API PyException CPPY_STR_index(const std::string& str, const std::string& sub, int* const result);
CPPY_API PyException CPPY_STR_index(const std::string& str, const std::string& sub, int start, int* const result);
CPPY_API PyException CPPY_STR_index(const std::string& str, const std::string& sub, int start, int end, int* const result);

/* S.rfind(sub[, start[, end]]) -> int
*
*  Return the highest index in S where substring sub is found,
*  such that sub is contained within S[start:end].  Optional
*  arguments start and end are interpreted as in slice notation.
*
*  Return -1 on failure.
*/
CPPY_API PyException CPPY_STR_rfind(const std::string& str, const std::string& sub, int* const result);
CPPY_API PyException CPPY_STR_rfind(const std::string& str, const std::string& sub, int start, int* const result);
CPPY_API PyException CPPY_STR_rfind(const std::string& str, const std::string& sub, int start, int end, int* const result);

/* S.rindex(sub[, start[, end]]) -> int
*
*  Return the highest index in S where substring sub is found,
*  such that sub is contained within S[start:end].  Optional
*  arguments start and end are interpreted as in slice notation.
*
*  Return ValueError when the substring is not found.
*/
CPPY_API PyException CPPY_STR_rindex(const std::string& str, const std::string& sub, int* const result);
CPPY_API PyException CPPY_STR_rindex(const std::string& str, const std::string& sub, int start, int* const result);
CPPY_API PyException CPPY_STR_rindex(const std::string& str, const std::string& sub, int start, int end, int* const result);

/* Return a copy of the string with leading and trailing whitespace removed.
*
*  If chars is given and not None, remove characters in chars instead.
*/
CPPY_API PyException CPPY_STR_strip(const std::string& str, std::string* const result);
CPPY_API PyException CPPY_STR_strip(const std::string& str, const std::string& ch, std::string* const result);

/* slice(start, stop[, step])
*
*  sub-string from the given string by slicing it respectively from start to end.
*/
CPPY_API PyException CPPY_STR_slice(const std::string& str, int start, int stop, std::string* const result);
CPPY_API PyException CPPY_STR_slice(const std::string& str, int start, int stop, int step, std::string* const result);

/* Concatenate any number of strings.
*
*  The string whose method is called is inserted in between each given string.
*  The result is returned as a new string.
*
*  Example: '.'.join(['ab', 'pq', 'rs']) -> 'ab.pq.rs'
*/
CPPY_API PyException CPPY_STR_join(const std::string& str, int n_iterables, const std::string iterable[], std::string* const result);

/* Return a list of the substrings in the string, using sep as the separator string.
*
*  sep
*    The separator used to split the string.
*    When set to None (the default value), will split on any whitespace
*    character (including \\n \\r \\t \\f and spaces) and will discard
*    empty strings from the result.
*
*  maxsplit
*    Maximum number of splits (starting from the left).
*    -1 (the default value) means no limit.
*
*  Note, str.split() is mainly useful for data that has been intentionally
*  delimited.  With natural text that includes punctuation, consider using
*  the regular expression module.
*/
CPPY_API PyException CPPY_STR_split(const std::string& str, std::vector<std::string>* const result);
CPPY_API PyException CPPY_STR_split(const std::string& str, const std::string& sep, std::vector<std::string>* const result);
CPPY_API PyException CPPY_STR_split(const std::string& str, int maxsplit, std::vector<std::string>* const result);
CPPY_API PyException CPPY_STR_split(const std::string& str, const std::string& sep, int maxsplit, std::vector<std::string>* const result);

/* Return a copy with all occurrences of substring old replaced by new.
*
*  count
*    Maximum number of occurrences to replace. -1 (the default value) means replace all occurrences.
*
*  If the optional argument count is given, only the first count occurrences are replaced.
*/
CPPY_API PyException CPPY_STR_replace(const std::string& str, const std::string& old_str, const std::string& new_str, std::string* const result);
CPPY_API PyException CPPY_STR_replace(const std::string& str, const std::string& old_str, const std::string& new_str, int count, std::string* const result);

/* Return a copy of the string converted to lowercase.
*/
CPPY_API PyException CPPY_STR_lower(const std::string& str, std::string* const result);

/* Return a copy of the string converted to uppercase.
*/
CPPY_API PyException CPPY_STR_upper(const std::string& str, std::string* const result);

/* Convert uppercase characters to lowercase and lowercase characters to uppercase.
*/
CPPY_API PyException CPPY_STR_swapcase(const std::string& str, std::string* const result);

/* Return a version of the string where each word is titlecased.
*
*  More specifically, words start with uppercased characters and all remaining
*  cased characters have lower case.
*/
CPPY_API PyException CPPY_STR_title(const std::string& str, std::string* const result);

/* Return a copy where all tab characters are expanded using spaces.
*
*  If tabsize is not given, a tab size of 8 characters is assumed.
*/
CPPY_API PyException CPPY_STR_expandtabs(const std::string& str, std::string* const result);
CPPY_API PyException CPPY_STR_expandtabs(const std::string& str, int tabsize, std::string* const result);

/* Return a list of the lines in the string, breaking at line boundaries.
*
*  Line breaks are not included in the resulting list unless keepends is given and
*  true
*/
CPPY_API PyException CPPY_STR_splitlines(const std::string& str, std::vector<std::string>* const result);
CPPY_API PyException CPPY_STR_splitlines(const std::string& str, bool keepends, std::vector<std::string>* const result);

/* Return a str with the given prefix string removed if present.
*
*  If the string starts with the prefix string, return string[len(prefix):].
*  Otherwise, return a copy of the original string.
*/
CPPY_API PyException CPPY_STR_removeprefix(const std::string& str, const std::string& prefix, std::string* const result);

/* Return a str with the given suffix string removed if present.
*
*  If the string ends with the suffix string and that suffix is not empty,
*  return string[:-len(suffix)]. Otherwise, return a copy of the original
*  string.
*/
CPPY_API PyException CPPY_STR_removesuffix(const std::string& str, const std::string& suffix, std::string* const result);

/* Pad a numeric string with zeros on the left, to fill a field of the given width.
*
*  The string is never truncated.
*/
CPPY_API PyException CPPY_STR_zfill(const std::string& str, int width, std::string* const result);

/* Return a left-justified string of length width.
*
*  Padding is done using the specified fill character (default is a space).
*/
CPPY_API PyException CPPY_STR_ljust(const std::string& str, int width, std::string* const result);
CPPY_API PyException CPPY_STR_ljust(const std::string& str, int width, char fillchar, std::string* const result);

/* Return a right-justified string of length width.
*
*  Padding is done using the specified fill character (default is a space).
*/
CPPY_API PyException CPPY_STR_rjust(const std::string& str, int width, std::string* const result);
CPPY_API PyException CPPY_STR_rjust(const std::string& str, int width, char fillchar, std::string* const result);

/* Return a centered string of length width.
*
*  Padding is done using the specified fill character (default is a space).
*/
CPPY_API PyException CPPY_STR_center(const std::string& str, int width, std::string* const result);
CPPY_API PyException CPPY_STR_center(const std::string& str, int width, char fillchar, std::string* const result);

/* Return a capitalized version of the string.
*
*  More specifically, make the first character have upper case and the rest lower
*  case.
*/
CPPY_API PyException CPPY_STR_capitalize(const std::string& str, std::string* const result);

/* Return True if the string is a whitespace string, False otherwise.
*
*  A string is whitespace if all characters in the string are whitespace and there
*  is at least one character in the string.
*/
CPPY_API PyException CPPY_STR_isspace(const std::string& str, bool* const result);

/* Return True if the string is an alpha-numeric string, False otherwise.
*
*  A string is alpha-numeric if all characters in the string are alpha-numeric and
*  there is at least one character in the string.
*/
CPPY_API PyException CPPY_STR_isalnum(const std::string& str, bool* const result);

/* Return True if the string is an alphabetic string, False otherwise.
*
*  A string is alphabetic if all characters in the string are alphabetic and there
*  is at least one character in the string.
*/
CPPY_API PyException CPPY_STR_isalpha(const std::string& str, bool* const result);

/* Return True if the string is a digit string, False otherwise.
*
*  A string is a digit string if all characters in the string are digits and there
*  is at least one character in the string.
*/
CPPY_API PyException CPPY_STR_isdigit(const std::string& str, bool* const result);

/* Return True if the string is a lowercase string, False otherwise.
*
*  A string is lowercase if all cased characters in the string are lowercase and
*  there is at least one cased character in the string.
*/
CPPY_API PyException CPPY_STR_islower(const std::string& str, bool* const result);

/* Return True if the string is an uppercase string, False otherwise.
*
*  A string is uppercase if all cased characters in the string are uppercase and
*  there is at least one cased character in the string.
*/
CPPY_API PyException CPPY_STR_isupper(const std::string& str, bool* const result);

/* Return True if the string is a title-cased string, False otherwise.
*
*  In a title-cased string, upper- and title-case characters may only
*  follow uncased characters and lowercase characters only cased ones.
*/
CPPY_API PyException CPPY_STR_istitle(const std::string& str, bool* const result);

/* S.format(*args, **kwargs) -> str
*
*  Return a formatted version of S, using substitutions from args and kwargs.
*  The substitutions are identified by braces ('{' and '}').
*/
template <typename... Args>
PyException CPPY_STR_format(const std::string& str, std::string* result, const Args&... args) {
	std::ostringstream oss;
	std::string_view view(str);
	(cppy::internal::format_helper(oss, view, args), ...);
	oss << view;
	*result = oss.str();
	return PyException::Ok;
}

CPPY_API PyException CPPY_STR_contains(const std::string& str, const std::string& other, bool* const result);

CPPY_API PyException CPPY_STR_at(const std::string& str, int index, char* const result);
// char operator[](int index) const;

CPPY_API PyException CPPY_STR_equal(const std::string& str, const std::string& other, bool* const result);
//bool operator==(const std::string& other) const;

CPPY_API PyException CPPY_STR_mul(const std::string& str, int n, std::string* const result);

namespace cppy {
	namespace internal {
		// https://codereview.stackexchange.com/questions/269425/implementing-stdformat
		template <typename T>
		static void format_helper(std::ostringstream& oss, std::string_view& str, const T& value)
		{
			std::size_t open_bracket = str.find('{');
			std::size_t close_bracket = str.find('}', open_bracket + 1);
			if (open_bracket == std::string::npos || close_bracket == std::string::npos)
			{
				return;
			}
			oss << str.substr(0, open_bracket) << value;
			str = str.substr(close_bracket + 1);
		}
	}
}
#endif // CPPY_STR_H

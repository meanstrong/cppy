#ifndef CPPY_STR_H
#define CPPY_STR_H
#include <iostream>
#include <sstream> 
#include <vector>
#include <string>
#include <array>

namespace cppy {

	class PyStr {
	private:
		std::string m_str;

	public:
		PyStr() = default;
		explicit PyStr(const char* chars);
		explicit PyStr(const std::string& s);
		explicit PyStr(int i);
		explicit PyStr(double d, int precision = 15);

		std::string toString() const;

		int toInt() const;
		double toDouble() const;

		int length() const;

		/* S.count(sub[, start[, end]]) -> int
		*
		*  Return the number of non-overlapping occurrences of substring sub in
		*  string S[start:end].  Optional arguments start and end are
		*  interpreted as in slice notation.
		*/
		int count(const std::string& sub, int start = 0, int end = INT_MAX) const;

		/* Partition the string into three parts using the given separator.
		*
		*  This will search for the separator in the string.  If the separator is found,
		*  returns a 3-tuple containing the part before the separator, the separator
		*  itself, and the part after it.
		*
		*  If the separator is not found, returns a 3-tuple containing the original string
		*  and two empty strings.
		*/
		std::array<PyStr, 3> partition(const std::string& sep) const;

		/* Partition the string into three parts using the given separator.
		*
		*  This will search for the separator in the string, starting at the end. If
		*  the separator is found, returns a 3-tuple containing the part before the
		*  separator, the separator itself, and the part after it.
		*
		*  If the separator is not found, returns a 3-tuple containing two empty strings
		*  and the original string.
		*/
		std::array<PyStr, 3> rpartition(const std::string& sep) const;

		/* S.startswith(prefix[, start[, end]]) -> bool
		*
		*  Return True if S starts with the specified prefix, False otherwise.
		*  With optional start, test S beginning at that position.
		*  With optional end, stop comparing S at that position.
		*  prefix can also be a tuple of strings to try.
		*/
		bool startswith(const std::string& prefix) const;

		/* S.endswith(suffix[, start[, end]]) -> bool
		*  Return True if S ends with the specified suffix, False otherwise.
		*  With optional start, test S beginning at that position.
		*  With optional end, stop comparing S at that position.
		*  suffix can also be a tuple of strings to try.
		*/
		bool endswith(const std::string& suffix) const;

		/* S.find(sub[, start[, end]]) -> int
		*
		*  Return the lowest index in S where substring sub is found,
		*  such that sub is contained within S[start:end].  Optional
		*  arguments start and end are interpreted as in slice notation.
		*
		*  Return -1 on failure.
		*/
		int find(const std::string& sub, int start = 0, int end = INT_MAX) const;

		/* S.index(sub[, start[, end]]) -> int
		*
		*  Return the lowest index in S where substring sub is found,
		*  such that sub is contained within S[start:end].  Optional
		*  arguments start and end are interpreted as in slice notation.
		*
		*  Return -1 on failure.
		*/
		int index(const std::string& sub, int start = 0, int end = INT_MAX) const;

		/* S.rfind(sub[, start[, end]]) -> int
		*
		*  Return the highest index in S where substring sub is found,
		*  such that sub is contained within S[start:end].  Optional
		*  arguments start and end are interpreted as in slice notation.
		*
		*  Return -1 on failure.
		*/
		int rfind(const std::string& sub, int start = 0, int end = INT_MAX) const;

		/* S.rindex(sub[, start[, end]]) -> int
		*
		*  Return the highest index in S where substring sub is found,
		*  such that sub is contained within S[start:end].  Optional
		*  arguments start and end are interpreted as in slice notation.
		*
		*  Return -1 on failure.
		*/
		int rindex(const std::string& sub, int start = 0, int end = INT_MAX) const;

		/* Return a copy of the string with leading and trailing whitespace removed.
		*
		*  If chars is given and not None, remove characters in chars instead.
		*/
		PyStr strip(const signed char& ch = -1) const;
		PyStr strip(const std::string& ch) const;

		/* slice(start, stop[, step])
		*
		*  sub-string from the given string by slicing it respectively from start to end.
		*/
		PyStr slice(int start, int stop, int step = 1) const;

		/* Concatenate any number of strings.
		*
		*  The string whose method is called is inserted in between each given string.
		*  The result is returned as a new string.
		*
		*  Example: '.'.join(['ab', 'pq', 'rs']) -> 'ab.pq.rs'
		*/
		PyStr join(const std::vector<std::string>& iterable) const;

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
		std::vector<PyStr> split(const std::string& sep = "", int maxsplit = -1) const;

		/* Return a copy with all occurrences of substring old replaced by new.
		*
		*  count
		*    Maximum number of occurrences to replace. -1 (the default value) means replace all occurrences.
		*
		*  If the optional argument count is given, only the first count occurrences are replaced.
		*/
		PyStr replace(const std::string& old_str, const std::string& new_str, int count = -1) const;

		/* Return a copy of the string converted to lowercase.
		*/
		PyStr lower() const;

		/* Return a copy of the string converted to uppercase.
		*/
		PyStr upper() const;

		/* Convert uppercase characters to lowercase and lowercase characters to uppercase.
		*/
		PyStr swapcase() const;

		/* Return a version of the string where each word is titlecased.
		*
		*  More specifically, words start with uppercased characters and all remaining
		*  cased characters have lower case.
		*/
		PyStr title() const;

		/* Return a copy where all tab characters are expanded using spaces.
		*
		*  If tabsize is not given, a tab size of 8 characters is assumed.
		*/
		PyStr expandtabs(int tabsize = 8) const;

		/* Return a list of the lines in the string, breaking at line boundaries.
		*
		*  Line breaks are not included in the resulting list unless keepends is given and
		*  true
		*/
		std::vector<PyStr> splitlines(bool keepends = false) const;

		/* Return a str with the given prefix string removed if present.
		*
		*  If the string starts with the prefix string, return string[len(prefix):].
		*  Otherwise, return a copy of the original string.
		*/
		PyStr removeprefix(const std::string& prefix) const;

		/* Return a str with the given suffix string removed if present.
		*
		*  If the string ends with the suffix string and that suffix is not empty,
		*  return string[:-len(suffix)]. Otherwise, return a copy of the original
		*  string.
		*/
		PyStr removesuffix(const std::string& suffix) const;

		/* Pad a numeric string with zeros on the left, to fill a field of the given width.
		*
		*  The string is never truncated.
		*/
		PyStr zfill(int width) const;

		/* Return a left-justified string of length width.
		*
		*  Padding is done using the specified fill character (default is a space).
		*/
		PyStr ljust(int width, char fillchar = ' ') const;

		/* Return a right-justified string of length width.
		*
		*  Padding is done using the specified fill character (default is a space).
		*/
		PyStr rjust(int width, char fillchar = ' ') const;

		/* Return a centered string of length width.
		*
		*  Padding is done using the specified fill character (default is a space).
		*/
		PyStr center(int width, char fillchar = ' ') const;

		/* Return a capitalized version of the string.
		*
		*  More specifically, make the first character have upper case and the rest lower
		*  case.
		*/
		PyStr capitalize() const;

		/* Return True if the string is a whitespace string, False otherwise.
		*
		*  A string is whitespace if all characters in the string are whitespace and there
		*  is at least one character in the string.
		*/
		bool isspace() const;

		/* Return True if the string is an alpha-numeric string, False otherwise.
		*
		*  A string is alpha-numeric if all characters in the string are alpha-numeric and
		*  there is at least one character in the string.
		*/
		bool isalnum() const;

		/* Return True if the string is an alphabetic string, False otherwise.
		*
		*  A string is alphabetic if all characters in the string are alphabetic and there
		*  is at least one character in the string.
		*/
		bool isalpha() const;

		/* Return True if the string is a digit string, False otherwise.
		*
		*  A string is a digit string if all characters in the string are digits and there
		*  is at least one character in the string.
		*/
		bool isdigit() const;

		/* Return True if the string is a lowercase string, False otherwise.
		*
		*  A string is lowercase if all cased characters in the string are lowercase and
		*  there is at least one cased character in the string.
		*/
		bool islower() const;

		/* Return True if the string is an uppercase string, False otherwise.
		*
		*  A string is uppercase if all cased characters in the string are uppercase and
		*  there is at least one cased character in the string.
		*/
		bool isupper() const;

		/* Return True if the string is a title-cased string, False otherwise.
		*
		*  In a title-cased string, upper- and title-case characters may only
		*  follow uncased characters and lowercase characters only cased ones.
		*/
		bool istitle() const;

		/* S.format(*args, **kwargs) -> str
		*
		*  Return a formatted version of S, using substitutions from args and kwargs.
		*  The substitutions are identified by braces ('{' and '}').
		*/
		template <typename... Args>
		PyStr format(const Args&... args) const {
			std::ostringstream oss;
			std::string_view str(m_str);
			(internal::format_helper(oss, str, args), ...);
			oss << str;
			return PyStr(oss.str());
		}

		bool contains(const std::string& other) const;

		char at(int index) const;
		char operator[](int index) const;

		bool equal(const std::string& other) const;
		bool operator==(const std::string& other) const;

		PyStr mul(int n) const;
	};

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
} // namespace cppy
#endif // CPPY_STR_H

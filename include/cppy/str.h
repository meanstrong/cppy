#ifndef CPPY_STR_H
#define CPPY_STR_H
#include <iostream>
#include <vector>
#include <string>

namespace cppy {

	class str {
	private:
		std::string m_str;

	public:
		str() = default;
		explicit str(const char* chars);
		explicit str(const std::string& s);
		explicit str(int i);
		explicit str(double d, int precision = 15);

		std::string toString() const;

		int toInt() const;
		double toDouble() const;

		int length() const;

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

		/* Return a copy of the string with leading and trailing whitespace removed.
		*
		*  If chars is given and not None, remove characters in chars instead.
		*/
		str strip(const signed char& ch = -1) const;

		/* slice(start, stop[, step])
		*
		*  sub-string from the given string by slicing it respectively from start to end.
		*/
		str slice(int start, int stop, int step = 1) const;

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
		std::vector<str> split(const std::string& sep = " ") const;

		/* Return a copy with all occurrences of substring old replaced by new.
		*
		*  count
		*    Maximum number of occurrences to replace. -1 (the default value) means replace all occurrences.
		*
		*  If the optional argument count is given, only the first count occurrences are replaced.
		*/
		str replace(const std::string& old_str, const std::string& new_str) const;

		/* Return a copy of the string converted to lowercase.
		*/
		str lower() const;

		/* Return a copy of the string converted to uppercase.
		*/
		str upper() const;

		bool contains(const std::string& other) const;

		char operator[](int index) const;
		bool operator==(const str& that) const;
	};
} // namespace cppy
#endif // CPPY_STR_H

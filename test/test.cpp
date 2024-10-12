#include "cppy/str.h"

int main()
{
	cppy::PyStr a("ABCDDDEFG");
	std::cout << a.replace("D", "O", -1).toString() << std::endl;
	std::cout << a.toString() << std::endl;
	return 0;
}

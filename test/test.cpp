#include "cppy/str.h"

int main()
{
	cppy::str str("ABCDxyz");
	std::cout << str.lower().toString() << std::endl;
	return 0;
}

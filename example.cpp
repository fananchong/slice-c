#include "slice.h"
#include <iostream>

int main()
{
	// 1. construction
	slice<char> a = { '0','1','2','3','4','5','6' };
	slice<char> b = a[1i - 4i];

	std::cout << "a:" << a << std::endl;
	std::cout << "b:" << b << std::endl << std::endl;


	// 2. append
	b = append(b, { 'a','b' });
	b = append(b, slice<char>{'c', 'd', 'e', 'f'});
	b = append(b, b);

	std::cout << "a:" << a << std::endl;
	std::cout << "b:" << b << std::endl << std::endl;


	// 3. remove
	b = remove(b, 3i);
	std::cout << "a:" << a << std::endl;
	std::cout << "b:" << b << std::endl << std::endl;

	b = remove(b, 3i, 5i);
	std::cout << "a:" << a << std::endl;
	std::cout << "b:" << b << std::endl << std::endl;

	return 0;
}
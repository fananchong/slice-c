# slice-c
slice for c++


## 例子

```c++
#include "slice.h"
#include <iostream>

int main()
{
	// 1. construction
	slice<char> a = { '0','1','2','3','4','5','6' };
	slice<char> b = a[1i - 4i];
	slice<char> c = a[{1, 4}];

	size_t i = 1;
	size_t j = 4;
	slice<char> d = a[{i, j}];

	std::cout << "a:" << a << std::endl;
	std::cout << "b:" << b << std::endl << std::endl;


	// 2. append
	b = append(b, { 'a','b' });
	b = append(b, slice<char>{'c', 'd', 'e', 'f'});
	b = append(b, b);

	std::cout << "a:" << a << std::endl;
	std::cout << "b:" << b << std::endl << std::endl;


	// 3. remove
	b = remove(b, 3);
	std::cout << "a:" << a << std::endl;
	std::cout << "b:" << b << std::endl << std::endl;

	b = remove(b, 3, 5);
	std::cout << "a:" << a << std::endl;
	std::cout << "b:" << b << std::endl << std::endl;

	return 0;
}
```

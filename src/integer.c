#include "../includes/libconfx.h"

size_t	convert_base(char *based, uint8_t base){
	int	idx = 0;
	int	power = 0;
	size_t	result = 0;
	char	offset = '0';

	// base lower than 2 or greater than 12 are not allowed
	if (base > 16 || base < 2){
		#ifdef DEBUG
			warn("line %zu : Base %d not allowed", cline, base);
		#endif
	}
	// detecting the length of the integer
	while (memchr(BASET, based[idx], base) != NULL && based[idx] != 0){
		idx++;
	}
	// TODO : handle integer overflow here
	while (--idx > -1){			// iterating until the start
		// to handle bases more than 10
		offset = '0';
		if (isalpha(based[idx]) != 0){
			offset = 'a' - 10;
		}
		result += (tolower(based[idx]) - offset) * (pow(base, power));
		power++;
	}
	return (result);
}

int detect_base(char *based){
	switch (based[1]){
		case ('x'):
			return (16);
		case ('b'):
			return (2);
		case ('o'):
			return (8);
		default :
			return (10);
	}
}


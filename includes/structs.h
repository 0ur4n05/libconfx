#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum conf_types {
	STRING_C,
	INT_C,
	FLOAT_C,
	BOOL_C,
} conf_types;

typedef struct conf {
	char		*key;
	void		*value;
	struct conf	*next;
} conf;

#endif

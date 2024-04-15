#include "../includes/libconfx.h"

size_t cline = 0;

conf *parse_config(char *config){
	conf *head =  malloc(sizeof(conf));
	conf *current = head;
	while (*config != '\0'){
		while (strchr(" \t", *config) != NULL && *config != '\0')
			config++;
		if (*config == '\0')
			return (head);
		if (*config == '#') {
			while (*config != '\n' && *config != '\0')
				config++;
			if (*config == '\0')
				return (head);
		}
		current->key = parse_string(config, "= \t\n");
		if (current->key != NULL){
			while (*config != '='){
				config++;
			}
			config++;
			while (strchr(" \t", *config) != NULL && *config != '\0')
				config++;
			current->value = parse_string(config, " \t\n");
			puts(current->key);
			puts(current->value);
		}
		while (*(config) != '\n'){
			config++;
		}
		config++;
	}
	
	puts(parse_string(config, " ="));
	return (head);
}

#include "../includes/libconfx.h"

// TODO :
// 	expand backslashed [\t,\n,...]

// TODO : escape unicode
char expand_escape_seq(char key){
	char corresponding[] = {0x8, 0xa, 0x5c, 0x9, 0xc, 0x22, 0xd};
	char keys[] = {'b', 'n', '\\', 't', 'f', '"', 'r'};
	int i = -1;
	while (++i < 7){
		if (keys[i] == key){
			return (corresponding[i]);
		}
	}
	return (0);
}

char *process_string(char *str, int len, char *delims){
	char	*pstr;
	int	idx = 0;
	int	i = 0;

	if (len < 1)
		return (NULL);
	pstr = (char *) malloc(len + 1);
	while (str[idx] != '\0' && strchr("\t \n", str[idx]) == NULL) {
		if (delims != NULL &&  strchr(delims, str[idx]) != NULL)
			break;
		if ((str[idx] == '\'' || str[idx] == '"') && str[idx - 1]  != '\\') {
			idx++;
			continue;
		} else if (str[idx] == '\\') {
			idx++;
			pstr[i] = expand_escape_seq(str[idx]);
			if (pstr[i] == '\0'){
				#ifdef DEBUG
					warn("line %zu: unknown espace sequence \\%c\n", cline, str[idx]);
				#endif
				return (pstr);
			}
			i++;
		} else {
			pstr[i++] = str[idx];
		}
		idx++;
	}
	return (pstr);
}

char *parse_string(char *str, char *delims){
	int	idx = 0;
	char	qtype;
	int	dc = 0;		// length that we dont want it to be counted

	// skipping spaces
	while (strchr("\t ", *str) != NULL && *str != '\0')
		str++;
	// empty line 
	if (*str == '\0')
		return (NULL);
	while (str[idx] != '\0' && strchr("\t \n", str[idx]) == NULL) {
		if (delims != NULL &&  strchr(delims, str[idx]) != NULL)
			break;
		if ((str[idx] == '\'' || str[idx] == '"') && str[idx - 1]  != '\\') {
			qtype = str[idx++];
			dc--;
			while (str[idx] != qtype && str[idx - 1] != '\\' && str[idx] != '\0') {		// getting the quoted stuff
				idx++;
			}
			if (str[idx + 1] == '\0'){
				#ifdef DEBUG
					warn("line %zu: unterminated quote %c\n", cline, qtype);
				#endif
			} else if (str[idx] == qtype){
				dc--;
				idx++;
			}
		} else
			idx++;
	}
	idx += dc;
	return (process_string(str, idx, delims));
}

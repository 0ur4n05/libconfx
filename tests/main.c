#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include "../includes/libconfx.h"

int main(int argc, char **argv){
	if (argc < 2)
		return (0);
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	char *file = mmap(0, 10000, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
	puts(file);
	parse_config(file);
}

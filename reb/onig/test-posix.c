#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "onigposix.h"

#define BUF_SIZE 0x10000

int main(int argc, char *argv[])
{
	regex_t r;
	regmatch_t match[10];
	char *buf, *q;
	int l = 0;
	if (argc == 1) {
		fprintf(stderr, "Usage: cat in.file | %s <regexp>\n", argv[0]);
		return 0;
	}
	regcomp(&r, argv[1], REG_EXTENDED);
	buf = calloc(BUF_SIZE, 1);
	while (fgets(buf, BUF_SIZE - 1, stdin)) {
		++l;
		for (q = buf; *q; ++q); if (q > buf) *(q-1) = 0;
		if (regexec(&r, buf, 10, match, 0) != REG_NOMATCH)
			printf("%d:%s\n", l, buf);
	}
	free(buf);
	return 0;
}

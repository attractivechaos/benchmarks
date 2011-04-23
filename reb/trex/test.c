#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#undef _UNICODE
#include "trex.h"

#define BUF_SIZE 0x10000

int main(int argc, char *argv[])
{
	TRex *r;
	char *buf, *err = 0, *beg, *end, *q;
	int l = 0;
	if (argc == 1) {
		fprintf(stderr, "Usage: cat in.file | %s <regexp>\n", argv[0]);
		return 0;
	}
	r = trex_compile(argv[1], &err);
	buf = calloc(BUF_SIZE, 1);
	while (fgets(buf, BUF_SIZE - 1, stdin)) {
		++l;
		for (q = buf; *q; ++q); if (q > buf) *(q-1) = 0;
		if (trex_search(r, buf, &beg, &end) == TRex_True)
			printf("%d:%s\n", l, buf);
	}
	free(buf);
	return 0;
}

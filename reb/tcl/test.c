#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcl.h>

#define BUF_SIZE 0x10000

// modifed from: http://shootout.alioth.debian.org/u32/program.php?test=regexdna&lang=gcc&id=1
int main(int argc, char *argv[])
{
	char *buf, *q;
	int l = 0;
	Tcl_RegExp r;

	if (argc == 1) {
		fprintf(stderr, "Usage: cat in.file | %s <regexp>\n", argv[0]);
		return 0;
	}
	Tcl_FindExecutable(argv[0]);
	r = Tcl_RegExpCompile(0, argv[1]);
	buf = calloc(BUF_SIZE, 1);
	while (fgets(buf, BUF_SIZE - 1, stdin)) {
		++l;
		for (q = buf; *q; ++q); if (q > buf) *--q = 0;
		if (Tcl_RegExpExec(0, r, buf, 0))
			printf("%d:%s\n", l, buf);
	}
	free(buf);
	return 0;
}

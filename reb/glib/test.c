#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#define BUF_SIZE 0x10000

int main(int argc, char *argv[])
{
	GRegex *r;
	GMatchInfo *info;
	char *buf, *q;
	int l = 0;
	if (argc == 1) {
		fprintf(stderr, "Usage: cat in.file | %s <regexp>\n", argv[0]);
		return 0;
	}
	r = g_regex_new(argv[1], G_REGEX_OPTIMIZE, 0, 0);
	buf = calloc(BUF_SIZE, 1);
	while (fgets(buf, BUF_SIZE - 1, stdin)) {
		++l;
		for (q = buf; *q; ++q); if (q > buf) *(q-1) = 0;
		if (g_regex_match(r, buf, 0, &info) == TRUE)
			printf("%d:%s\n", l, buf);
		g_match_info_free(info);
	}
	free(buf);
	return 0;
}

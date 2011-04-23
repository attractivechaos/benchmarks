#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <boost/regex.hpp>

#define BUF_SIZE 0x10000

int main(int argc, char *argv[])
{
	char *buf, *q;
	int l = 0;
	if (argc == 1) {
		fprintf(stderr, "Usage: cat in.file | %s <regexp>\n", argv[0]);
		return 0;
	}
	boost::regex p(argv[1]);
	boost::smatch what;
	buf = (char*)calloc(BUF_SIZE, 1);
	while (fgets(buf, BUF_SIZE - 1, stdin)) {
		++l;
		for (q = buf; *q; ++q); if (q > buf) *(q-1) = 0;
		std::string s(buf);
		if (boost::regex_search(s, what, p))
			printf("%d:%s\n", l, buf);
	}
	free(buf);
	return 0;
}

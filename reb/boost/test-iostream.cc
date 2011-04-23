#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <boost/regex.hpp>

#define BUF_SIZE 0x10000

int main(int argc, char *argv[])
{
	int l = 0;
	std::string s;
	if (argc == 1) {
		fprintf(stderr, "Usage: cat in.file | %s <regexp>\n", argv[0]);
		return 0;
	}
	boost::regex p(argv[1]);
	boost::smatch what;
	while (!std::getline(std::cin, s).eof()) {
		++l;
		if (boost::regex_search(s, what, p))
			std::cout<<s<<'\n';
	}
	return 0;
}

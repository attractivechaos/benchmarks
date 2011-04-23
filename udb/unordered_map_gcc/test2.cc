#include "benchmark.h"
#include <utility>
#include <string.h>
#include <unordered_map>

using namespace std;

struct eqstr {
	inline bool operator()(const char *s1, const char *s2) const {
		return strcmp(s1, s2) == 0;
    }
};

namespace std {
	template<>
	struct hash<const char *> : public std::unary_function<const char *, size_t> {
		size_t operator()(const char *s) const
		{ 
			size_t h = *s;
			if (h) for (++s ; *s; ++s) h = (h << 5) - h + *s;
		return h;
		}
	};
}

typedef unordered_map<unsigned, int, hash<unsigned> > inthash;
typedef unordered_map<const char*, int, hash<const char*>, eqstr> strhash;

int test_int(int N, const unsigned *data)
{
	int i, ret;
	inthash *h = new inthash;
	for (i = 0; i < N; ++i) {
		pair<inthash::iterator, bool> p = h->insert(pair<unsigned, int>(data[i], i));
		if (p.second == false) h->erase(p.first);
	}
	ret = h->size();
	delete h;
	return ret;
}

int test_str(int N, char * const *data)
{
	int i, ret;
	strhash *h = new strhash;
	for (i = 0; i < N; ++i) {
		pair<strhash::iterator, bool> p = h->insert(pair<const char*, int>(data[i], i));
		if (p.second == false) h->erase(p.first);
	}
	ret = h->size();
	delete h;
	return ret;
}

int main(int argc, char *argv[])
{
	return udb_benchmark(argc, argv, test_int, test_str);
}

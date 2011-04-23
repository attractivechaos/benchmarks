#include "benchmark.h"
#include <string.h>
#include <utility>
#include <google/sparse_hash_map>

using namespace std;

struct myhash {
	inline size_t operator()(const char *s) const
	{ 
		size_t h = *s;
		if (h) for (++s ; *s; ++s) h = (h << 5) - h + *s;
		return h;
	}
};
struct eqstr {
	inline bool operator()(const char *s1, const char *s2) const {
		return strcmp(s1, s2) == 0;
    }
};

typedef google::sparse_hash_map<unsigned, int> inthash;
typedef google::sparse_hash_map<const char*, int, myhash, eqstr> strhash;

int test_int(int N, const unsigned *data)
{
	int i, ret;
	inthash *h = new inthash;
	h->set_deleted_key(0xfffffffeu);
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
	h->set_deleted_key("");
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

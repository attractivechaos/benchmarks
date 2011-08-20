#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <zlib.h>
#include <time.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

#define kroundup32(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, (x)|=(x)>>8, (x)|=(x)>>16, ++(x))

int ksa_sa(const unsigned char *T, int *SA, int n, int k);
int sais2_int(const int *T, int *SA, int n, int k);
void suffixsort(int *x, int *p, int n, int k, int l);

unsigned char seq_nt6_table[128];
void seq_char2nt6(int l, unsigned char *s);
void seq_revcomp6(int l, unsigned char *s);
uint32_t SA_checksum(int l, const int *s);

int main(int argc, char *argv[])
{
	kseq_t *seq;
	gzFile fp;
	int *SA, l = 0, max = 0, algo = 0, n_sentinels = 0;
	uint8_t *s = 0;
	clock_t t = clock();

	if (argc == 1) {
		fprintf(stderr, "Usage: mssac input.fasta [ ksa | sais | qsufsort ]\n");
		return 1;
	}
	if (argc > 2) {
		if (strcmp(argv[2], "ksa") == 0) algo = 0;
		else if (strcmp(argv[2], "qsufsort") == 0) algo = 1;
		else if (strcmp(argv[2], "sais") == 0) algo = 2;
		else {
			fprintf(stderr, "(EE) Unknown algorithm.\n");
			return 1;
		}
	}

	fp = gzopen(argv[1], "r");
	seq = kseq_init(fp);
	while (kseq_read(seq) >= 0) {
		if (l + (seq->seq.l + 1) * 2 >= max) {
			max = l + (seq->seq.l + 1) * 2 + 1;
			kroundup32(max);
			s = realloc(s, max);
		}
		seq_char2nt6(seq->seq.l, (uint8_t*)seq->seq.s);
		memcpy(s + l, seq->seq.s, seq->seq.l + 1);
		l += seq->seq.l + 1;
		seq_revcomp6(seq->seq.l, (uint8_t*)seq->seq.s);
		memcpy(s + l, seq->seq.s, seq->seq.l + 1);
		l += seq->seq.l + 1;
		n_sentinels += 2;
	}
	kseq_destroy(seq);
	gzclose(fp);
	fprintf(stderr, "(MM) Read %d symbols in %.3f seconds.\n", l, (double)(clock() - t) / CLOCKS_PER_SEC);

	t = clock();
	if (algo == 0) {
		SA = (int*)malloc(sizeof(int) * l);
		ksa_sa(s, SA, l, 6);
		SA_checksum(l, SA);
		free(SA); free(s);
	} else if (algo == 1 || algo == 2) {
		int i, *tmp, k = 0;
		tmp = (int*)malloc(sizeof(int) * (l + 1));
		for (i = 0; i < l; ++i)
			tmp[i] = s[i]? n_sentinels + s[i] : ++k;
		free(s);
		SA = (int*)malloc(sizeof(int) * (l + 1));
		if (algo == 1) {
			suffixsort(tmp, SA, l, n_sentinels + 6, 1);
			SA_checksum(l, SA + 1);
		} else if (algo == 2) { // algo == 2
			sais2_int(tmp, SA, l, n_sentinels + 6);
			SA_checksum(l, SA);
		}
		free(SA); free(tmp);
	}
	fprintf(stderr, "(MM) Constructed suffix array in %.3f seconds.\n", (double)(clock() - t) / CLOCKS_PER_SEC);

	return 0;
}

unsigned char seq_nt6_table[128] = {
    0, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,
    5, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,
    5, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,
    5, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,
    5, 1, 5, 2,  5, 5, 5, 3,  5, 5, 5, 5,  5, 5, 5, 5,
    5, 5, 5, 5,  4, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5,
    5, 1, 5, 2,  5, 5, 5, 3,  5, 5, 5, 5,  5, 5, 5, 5,
    5, 5, 5, 5,  4, 5, 5, 5,  5, 5, 5, 5,  5, 5, 5, 5
};

void seq_char2nt6(int l, unsigned char *s)
{
	int i;
	for (i = 0; i < l; ++i)
		s[i] = s[i] < 128? seq_nt6_table[s[i]] : 5;
}

void seq_revcomp6(int l, unsigned char *s)
{
	int i;
	for (i = 0; i < l>>1; ++i) {
		int tmp = s[l-1-i];
		tmp = (tmp >= 1 && tmp <= 4)? 5 - tmp : tmp;
		s[l-1-i] = (s[i] >= 1 && s[i] <= 4)? 5 - s[i] : s[i];
		s[i] = tmp;
	}
	if (l&1) s[i] = (s[i] >= 1 && s[i] <= 4)? 5 - s[i] : s[i];
}

uint32_t SA_checksum(int l, const int *s)
{
	uint32_t h = *s;
	const int *end = s + l;
	clock_t t = clock();
	for (; s < end; ++s) h = (h << 5) - h + *s;
	fprintf(stderr, "(MM) Computed SA X31 checksum in %.3f seconds (checksum = %x)\n", (double)(clock() - t) / CLOCKS_PER_SEC, h);
	return h;
}

/*
dft - playing with dft and radix-2 fft
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include "dft.h"
#include "kahan.h"

void do_kahan_dft(struct dft *dft, complex *out, complex *in)
{
	for (int n = 0; n < dft->N; n++) {
		struct kahan sum;
		init_kahan(&sum);
		for (int k = 0; k < dft->N; k++) {
			complex w = dft->z[(k * n) & (dft->N - 1)];
			add_kahan(&sum, in[k] * w);
		}
		out[n] = get_kahan(&sum);
	}
}

void do_dft(struct dft *dft, complex *out, complex *in)
{
	for (int n = 0; n < dft->N; n++) {
		complex sum = 0.0;
		for (int k = 0; k < dft->N; k++) {
			complex w = dft->z[(k * n) & (dft->N - 1)];
			sum += in[k] * w;
		}
		out[n] = sum;
	}
}

void normalize_dft(struct dft *dft, complex *io)
{
	double factor = 1.0 / dft->N;
	for (int n = 0; n < dft->N; n++)
		io[n] *= factor;
}

struct dft *alloc_dft(int N, int dir)
{
	struct dft *dft = malloc(sizeof(struct dft));
	dft->z = malloc(sizeof(complex) * N);
	for (int n = 0; n < N; n++)
		dft->z[n] = cexp(dir * I * n * 2.0 * M_PI / N);
	dft->N = N;
	return dft;
}

void free_dft(struct dft *dft)
{
	free(dft->z);
	free(dft);
}


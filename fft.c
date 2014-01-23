/*
dft - playing with dft and radix-2 fft
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include "fft.h"

void radix2(complex *out, complex *in, complex *z, int N, int S, int L)
{
	if (1 == N) {
		out[0] = in[0];
		return;
	} else if (2 == N) {
		out[0] = in[0] + in[S];
		out[1] = in[0] - in[S];
		return;
	} else if (4 == N) {
		complex w = z[1 << L];
		out[0] = in[0] + in[S] + in[2 * S] + in[3 * S];
		out[1] = in[0] + w * in[S] - in[2 * S] - w * in[3 * S];
		out[2] = in[0] - in[S] + in[2 * S] - in[3 * S];
		out[3] = in[0] - w * in[S] - in[2 * S] + w * in[3 * S];
		return;
	}
	radix2(out, in, z, N / 2, 2 * S, L + 1);
	radix2(out + N / 2, in + S, z, N / 2, 2 * S, L + 1);
	for (int k = 0; k < N / 2; k++) {
		int ke = k;
		int ko = k + N / 2;
		complex even = out[ke];
		complex odd = out[ko];
		complex w = z[k << L];
		out[ke] = even + w * odd;
		out[ko] = even - w * odd;
	}
}

void do_fft(struct fft *fft, complex *out, complex *in)
{
	radix2(out, in, fft->z, fft->N, 1, 0);
}

void normalize_fft(struct fft *fft, complex *io)
{
	double factor = 1.0 / fft->N;
	for (int n = 0; n < fft->N; n++)
		io[n] *= factor;
}

struct fft *alloc_fft(int N, int dir)
{
	struct fft *fft = malloc(sizeof(struct fft));
	fft->z = malloc(sizeof(complex) * (N / 2));
	for (int n = 0; n < N / 2; n++)
		fft->z[n] = cexp(dir * I * n * 2.0 * M_PI / N);
	fft->N = N;
	return fft;
}

void free_fft(struct fft *fft)
{
	free(fft->z);
	free(fft);
}


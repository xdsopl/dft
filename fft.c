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

static inline void dft2(complex *out0, complex *out1, complex in0, complex in1)
{
	*out0 = in0 + in1;
	*out1 = in0 - in1;
}

void radix2(complex *out, complex *in, complex *z, int N, int S)
{
	switch (N) {
		case 1:
			out[0] = in[0];
			return;
		case 2:
			dft2(out, out + 1, in[0], in[S]);
			return;
		case 4:
			out[0] = in[0] + in[S] + in[2 * S] + in[3 * S];
			out[1] = in[0] + z[S] * in[S] - in[2 * S] - z[S] * in[3 * S];
			out[2] = in[0] - in[S] + in[2 * S] - in[3 * S];
			out[3] = in[0] - z[S] * in[S] - in[2 * S] + z[S] * in[3 * S];
			return;
	}
	radix2(out, in, z, N / 2, 2 * S);
	radix2(out + N / 2, in + S, z, N / 2, 2 * S);
	for (int k0 = 0, k1 = N / 2; k0 < N / 2; ++k0, ++k1)
		dft2(out + k0, out + k1, out[k0], z[k0 * S] * out[k1]);
}

void do_fft(struct fft *fft, complex *out, complex *in)
{
	radix2(out, in, fft->z, fft->N, 1);
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


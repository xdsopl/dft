/*
dft - playing with dft and radix-2 fft
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "stopwatch.h"
#include "dft.h"
#include "fft.h"

int main(int argc, char **argv)
{
	struct stopwatch *sw = alloc_sw();

	int N;
	if (argc != 2 || !(N = atoi(argv[1])) || N & (N-1)) {
		fprintf(stderr, "usage: %s N (N must be power of 2)\n", argv[0]);
		return 1;
	}

	int CALC = 300000000;
	int DFTS = CALC / N / N;
	int FFTS = CALC / N / log2(N);

	DFTS = (DFTS & ~1) + 2;
	FFTS = (FFTS & ~1) + 2;

	complex double a[N], b[N], c[N];
	srand(time(0));
	for (int i = 0; i < N; i++)
		a[i] = 1.0 + I - 2.0 * (rand() + I * rand()) / RAND_MAX;

	restart_sw(sw);
	struct dft *dft_fw = alloc_dft(N, -1);
	struct dft *dft_bw = alloc_dft(N, +1);
	stop_sw(sw);
	fprintf(stderr, "dft setup took %g seconds\n", elapsed_sw(sw));

	restart_sw(sw);
	struct fft *fft_fw = alloc_fft(N, -1);
	struct fft *fft_bw = alloc_fft(N, +1);
	stop_sw(sw);
	fprintf(stderr, "fft setup took %g seconds\n", elapsed_sw(sw));

	do_dft(dft_fw, b, a);
	do_dft(dft_bw, c, b);
	normalize_dft(dft_bw, c);

	double dft_error = 0.0;
	for (int i = 0; i < N; i++)
		dft_error = fmax(dft_error, cabs(a[i] - c[i]));
	fprintf(stderr, "dft max error is: %g\n", dft_error);

	do_fft(fft_fw, b, a);
	do_fft(fft_bw, c, b);
	normalize_fft(fft_bw, c);

	double fft_error = 0.0;
	for (int i = 0; i < N; i++)
		fft_error = fmax(fft_error, cabs(a[i] - c[i]));
	fprintf(stderr, "fft max error is: %g, dft/fft error factor: %g\n", fft_error, dft_error / fft_error);

	do_kahan_dft(dft_fw, b, a);
	do_kahan_dft(dft_bw, c, b);
	normalize_dft(dft_bw, c);

	double kahan_dft_error = 0.0;
	for (int i = 0; i < N; i++)
		kahan_dft_error = fmax(kahan_dft_error, cabs(a[i] - c[i]));
	fprintf(stderr, "kahan_dft max error is: %g, kahan_dft/fft error factor: %g\n", kahan_dft_error, kahan_dft_error / fft_error);

	do_fft(fft_fw, c, a);

	double kahan_dft_fft_error = 0.0;
	for (int i = 0; i < N; i++)
		kahan_dft_fft_error = fmax(kahan_dft_fft_error, cabs(c[i] - b[i]));
	fprintf(stderr, "(kahan_dft-fft) max error is: %g\n", kahan_dft_fft_error);

	restart_sw(sw);
	do_dft(dft_fw, b, a);
	for (int i = 2; i < DFTS; i += 2) {
		do_dft(dft_bw, c, b);
		normalize_dft(dft_bw, c);
		do_dft(dft_fw, b, c);
	}
	do_dft(dft_bw, c, b);
	normalize_dft(dft_bw, c);
	stop_sw(sw);
	double dft_time = elapsed_sw(sw);

	fprintf(stderr, "%d dfts took %g seconds, thats %g dfts/second\n", DFTS, dft_time, DFTS / dft_time);

	restart_sw(sw);
	do_fft(fft_fw, b, a);
	for (int i = 2; i < FFTS; i += 2) {
		do_fft(fft_bw, c, b);
		normalize_fft(fft_bw, c);
		do_fft(fft_fw, b, c);
	}
	do_fft(fft_bw, c, b);
	normalize_fft(fft_bw, c);
	stop_sw(sw);
	double fft_time = elapsed_sw(sw);

	fprintf(stderr, "%d ffts took %g seconds, thats %g ffts/second\n", FFTS, fft_time, FFTS / fft_time);

	fprintf(stderr, "fft/dft speedup: %g, N = %d, N/log2(N) = %g\n", (FFTS * dft_time) / (DFTS * fft_time), N, N / log2(N));

#if 0
	for (int i = 0; i < N; i++)
		printf("%g %g %g %g\n", creal(a[i]), cimag(a[i]), cabs(a[i]), carg(a[i]));
#else
	printf("%d %g %g %g %g %g\n", N, FFTS / fft_time, DFTS / dft_time, fft_error, dft_error, kahan_dft_error);
#endif

	return 0;
}


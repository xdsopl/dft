/*
dft - playing with dft and radix-2 fft
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef FFT_H
#define FFT_H

#include <complex.h>

struct fft {
	complex double *z;
	int N;
};

void do_fft(struct fft *fft, complex double *out, complex double *in);
void normalize_fft(struct fft *fft, complex double *io);
struct fft *alloc_fft(int N, int dir);
void free_fft(struct fft *fft);

#endif


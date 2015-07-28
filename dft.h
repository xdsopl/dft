/*
dft - playing with dft and radix-2 fft
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef DFT_H
#define DFT_H

#include <complex.h>

struct dft {
	complex double *z;
	int N;
};

void do_kahan_dft(struct dft *dft, complex double *out, complex double *in);
void do_dft(struct dft *dft, complex double *out, complex double *in);
void normalize_dft(struct dft *dft, complex double *io);
struct dft *alloc_dft(int N, int dir);
void free_dft(struct dft *dft);

#endif


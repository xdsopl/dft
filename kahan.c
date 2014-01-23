/*
dft - playing with dft and radix-2 fft
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include "kahan.h"

void init_kahan(struct kahan *k)
{
	k->sum = 0.0;
	k->err = 0.0;
}

void add_kahan(struct kahan *k, complex a)
{
	complex tmp = a - k->err;
	complex sum = k->sum + tmp;
	k->err = (sum - k->sum) - tmp;
	k->sum = sum;
}

complex get_kahan(struct kahan *k)
{
	return k->sum;
}


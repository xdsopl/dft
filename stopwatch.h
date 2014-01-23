/*
dft - playing with dft and radix-2 fft
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <time.h>

struct stopwatch {
	struct timespec start, stop;
};
struct stopwatch *alloc_sw();
void restart_sw(struct stopwatch *sw);
void stop_sw(struct stopwatch *sw);
double elapsed_sw(struct stopwatch *sw);
void free_sw(struct stopwatch *sw);

#endif


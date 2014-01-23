/*
dft - playing with dft and radix-2 fft
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include <stdlib.h>
#include <time.h>
#include "stopwatch.h"

struct stopwatch *alloc_sw()
{
	return malloc(sizeof(struct stopwatch));
}

void free_sw(struct stopwatch *sw)
{
	free(sw);
}

void restart_sw(struct stopwatch *sw)
{
	clock_gettime(CLOCK_MONOTONIC, &sw->start);
}

void stop_sw(struct stopwatch *sw)
{
	clock_gettime(CLOCK_MONOTONIC, &sw->stop);
}

double elapsed_sw(struct stopwatch *sw)
{
	return (sw->stop.tv_sec - sw->start.tv_sec) + (sw->stop.tv_nsec - sw->start.tv_nsec) / 1000000000.0;
}


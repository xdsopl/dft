set logscale xy
set format x "%g"
set format y "%g"
plot "blah.dat" u 1:4 w p t "fft", "blah.dat" u 1:5 w p t "dft", "blah.dat" u 1:6 w p t "kahan dft"

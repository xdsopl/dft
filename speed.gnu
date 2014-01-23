set logscale xy
set format x "%g"
set format y "%g"
fft(x) = a / (x * log(x))
dft(x) = b / (x * x)
fit fft(x) "blah.dat" u 1:2 via a
fit dft(x) "blah.dat" u 1:3 via b
plot "blah.dat" u 1:2 w p t "fft/s", fft(x) w l t "a/(n*log(n))", "blah.dat" u 1:3 w p t "dft/s", dft(x) w l t "b/(n*n)"

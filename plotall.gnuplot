#!/usr/bin/gnuplot
set terminal pdf enhanced
set datafile separator ';'
set logscale xy
set format xy "10^{%T}" # %.0t⋅
set xlabel "{/Symbol D}t / {/Symbol t}"
set ylabel "<{/Symbol d}H^2>^{1/2} / H_0"
set key below
set yrange [*:1]
set mxtics 1
set mytics 1
set grid

me = system("perl -le '$e=1; $e/=2 while $e/2+1>1; print $e'")

names = "Euler Verlet VerletLeapFrog VelocityVerlet RK4"

set output 'pdfs/err-ct.pdf'
set title 'Constant total time = 10 {/Symbol t}'
set xrange [1e-8:1e-1]
plot for [name in names] "data-ct/".name.".dat" t name w p,\
    2*me t "2{/Symbol e}_m" w l ls 0 lw 7 lc rgb "#00aaff"

set output 'pdfs/err-ci.pdf'
set title 'Constant iteration number = 10^7'
set xrange [1e-8:1e-1]
plot for [name in names] "data-ci/".name.".dat" t name w p,\
    2*me t "2{/Symbol e}_m" w l ls 0 lw 7 lc rgb "#00aaff"

###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###
reset
set terminal pdf enhanced
set output 'pdfs/speed.pdf'
set title "Speed of used algorithms"
set datafile separator ';'
unset key
set boxwidth 0.5
set style fill solid
set yrange [0:*]
set ylabel "Millions of iterations per second"
set decimalsign ','
set grid
plot "data-ci/times.dat" using 0:(1e10/$2):xtic(1) w boxes

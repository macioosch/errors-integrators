#!/usr/bin/gnuplot
set terminal pdf enhanced size 3,5
set datafile separator ';'
set logscale xy
set format xy "10^{%T}" # %.0t⋅
set xlabel "{/Symbol d}t / {/Symbol t}"
set key below
set xrange [1e-5:1e-1]
set yrange [1e-14:1e0]
set mxtics 1
set mytics 1
set grid

names = "Euler Verlet VerletLeapFrog VelocityVerlet RK4"

###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###

set ylabel "<{/Symbol d}H^2>^{1/2} / H_0"
set title 'Energy, constant total time = 10 {/Symbol t}'
set output 'pdfs/err-E-ct.pdf'
plot for [name in names] "data-ct/".name.".dat" u ($1/(2.0*pi)):2 t name w p

set title 'Energy, constant iteration number = 10^6'
set output 'pdfs/err-E-ci.pdf'
plot for [name in names] "data-ci/".name.".dat" u ($1/(2.0*pi)):2 t name w p

set ylabel "<{/Symbol d}x^2>^{1/2}"
set title 'Position, constant total time = 10 {/Symbol t}'
set output 'pdfs/err-X-ct.pdf'
plot for [name in names] "data-ct/".name.".dat" u ($1/(2.0*pi)):3 t name w p

set title 'Position, constant iteration number = 10^6'
set output 'pdfs/err-X-ci.pdf'
plot for [name in names] "data-ci/".name.".dat" u ($1/(2.0*pi)):3 t name w p

set ylabel "<{/Symbol d}v^2>^{1/2}"
set title 'Velocity, constant total time = 10 {/Symbol t}'
set output 'pdfs/err-V-ct.pdf'
plot for [name in names] "data-ct/".name.".dat" u ($1/(2.0*pi)):4 t name w p

set title 'Velocity, constant iteration number = 10^6'
set output 'pdfs/err-V-ci.pdf'
plot for [name in names] "data-ci/".name.".dat" u ($1/(2.0*pi)):4 t name w p

###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###

set terminal pdf enhanced size 5.2cm,7.4cm font "DejaVu Serif,11"
b = "0,0"
titleEnd = ", brak tłumienia."

set ylabel "<{/Symbol d}H^2>^{1/2} / H_0"
set title "Energia".titleEnd
set output "publishing/err-E-".b.".pdf"
plot for [name in names] "data-ct-".b."/".name.".dat" u ($1/(2.0*pi)):2 t name w p

set ylabel "<{/Symbol d}x^2>^{1/2}"
set title "Położenie".titleEnd
set output "publishing/err-X-".b.".pdf"
plot for [name in names] "data-ct-".b."/".name.".dat" u ($1/(2.0*pi)):3 t name w p

set ylabel "<{/Symbol d}v^2>^{1/2}"
set title "Prędkość".titleEnd
set output "publishing/err-V-".b.".pdf"
plot for [name in names] "data-ct-".b."/".name.".dat" u ($1/(2.0*pi)):4 t name w p

unset key
set terminal pdf enhanced size 5.2cm,5.9cm font "DejaVu Serif,11"
b = "0,1"
titleEnd = ", tłumienie: b = ".b."."

set ylabel "<{/Symbol d}H^2>^{1/2} / H_0"
set title "Energia".titleEnd
set output "publishing/err-E-".b.".pdf"
plot for [name in names] "data-ct-".b."/".name.".dat" u ($1/(2.0*pi)):2 t name w p

set ylabel "<{/Symbol d}x^2>^{1/2}"
set title "Położenie".titleEnd
set output "publishing/err-X-".b.".pdf"
plot for [name in names] "data-ct-".b."/".name.".dat" u ($1/(2.0*pi)):3 t name w p

set ylabel "<{/Symbol d}v^2>^{1/2}"
set title "Prędkość".titleEnd
set output "publishing/err-V-".b.".pdf"
plot for [name in names] "data-ct-".b."/".name.".dat" u ($1/(2.0*pi)):4 t name w p

###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###  ###

reset
set terminal pdf enhanced size 5,3
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
plot "data-ci/times.dat" using 0:(1e9/$2):xtic(1) w boxes

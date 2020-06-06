set term pngcairo enhanced font "Times,24" size 1200,800
set xlabel "Number of threads"
set ylabel "Speedup"
set output "speedup.png"
set key inside top left nobox

set border lw 3
set grid lw 2.5
set pointsize 3.0

plot "sspeedupFloyd" using 1:2 \
     ti "speedup" \
with lp lw 4 pt 2 lc rgb '#017BCC'

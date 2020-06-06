set term pngcairo enhanced font "Times,12" size 860,640
set xlabel "Number of threads"
set ylabel "Speedup"
set output "speedup_example.png"
set key inside top left nobox

set border lw 3
set grid lw 2.5
set pointsize 3.0

plot "speedup_example" using 1:2 \
     ti "speedup_example" \
with lp lw 4 pt 2 lc rgb '#0017BCC'

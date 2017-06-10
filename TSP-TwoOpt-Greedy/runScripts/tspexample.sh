#! /bin/bash
file8="tsp_example_1.txt.tour"
file9="tsp_example_2.txt.tour"
file10="tsp_example_3.txt.tour"
file8best=$(head -n 1 /home/adam/Desktop/saved/$file8)
file9best=$(head -n 1 /home/adam/Desktop/saved/$file9)
file10best=$(head -n 1 /home/adam/Desktop/saved/$file10)

while [ $(date "+%H") -lt 11 ]; do

./mytsp tsp_example_1.txt 2400
line8=$(head -n 1 $file8)
if [ $line8 -ge $file8best ]; then
   rm -f $file8
else
   file8best=$line8
   mv -f $file8 /home/adam/Desktop/saved
fi

./mytsp tsp_example_2.txt 2400
line9=$(head -n 1 $file9)
if [ $line9 -ge $file9best ]; then
   rm -f $file9
else
   file9best=$line9
   mv -f $file9 /home/adam/Desktop/saved
fi

./mytsp tsp_example_3.txt 2400
line10=$(head -n 1 $file10)
if [ $line10 -ge $file10best ]; then
   rm -f $file10
else
   file10best=$line10
   mv -f $file10 /home/adam/Desktop/saved
fi

done



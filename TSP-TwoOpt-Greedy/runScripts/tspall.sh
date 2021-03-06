#! /bin/bash
file1="test-input-1.txt.tour"
file2="test-input-2.txt.tour"
file3="test-input-3.txt.tour"
file4="test-input-4.txt.tour"
file5="test-input-5.txt.tour"
file6="test-input-6.txt.tour"
file7="test-input-7.txt.tour"
file8="tsp_example_1.txt.tour"
file9="tsp_example_2.txt.tour"
file10="tsp_example_3.txt.tour"
file1best=$(head -n 1 /home/adam/Desktop/saved/$file1)
file2best=$(head -n 1 /home/adam/Desktop/saved/$file2)
file3best=$(head -n 1 /home/adam/Desktop/saved/$file3)
file4best=$(head -n 1 /home/adam/Desktop/saved/$file4)
file5best=$(head -n 1 /home/adam/Desktop/saved/$file5)
file6best=$(head -n 1 /home/adam/Desktop/saved/$file6)
file7best=$(head -n 1 /home/adam/Desktop/saved/$file7)
file8best=$(head -n 1 /home/adam/Desktop/saved/$file8)
file9best=$(head -n 1 /home/adam/Desktop/saved/$file9)
file10best=$(head -n 1 /home/adam/Desktop/saved/$file10)

while [ $(date "+%H") -lt $2 ]; do

./$1 test-input-1.txt
line1=$(head -n 1 $file1)
if [ $line1 -ge $file1best ]; then
   rm -f $file1
else
   file1best=$line1
   mv -f $file1 /home/adam/Desktop/saved
fi

./$1 test-input-2.txt
line2=$(head -n 1 $file2)
if [ $line2 -ge $file2best ]; then
   rm -f $file2
else
   file2best=$line2
   mv -f $file2 /home/adam/Desktop/saved
fi

./$1 test-input-3.txt
line3=$(head -n 1 $file3)
if [ $line3 -ge $file3best ]; then
   rm -f $file3
else
   file3best=$line3
   mv -f $file3 /home/adam/Desktop/saved
fi

./$1 test-input-4.txt
line4=$(head -n 1 $file4)
if [ $line4 -ge $file4best ]; then
   rm -f $file4
else
   file4best=$line4
   mv -f $file4 /home/adam/Desktop/saved
fi

./$1 test-input-5.txt
line5=$(head -n 1 $file5)
if [ $line5 -ge $file5best ]; then
   rm -f $file5
else
   file5best=$line5
   mv -f $file5 /home/adam/Desktop/saved
fi

./$1 test-input-6.txt
line6=$(head -n 1 $file6)
if [ $line6 -ge $file6best ]; then
   rm -f $file6
else
   file6best=$line6
   mv -f $file6 /home/adam/Desktop/saved
fi

./$1 test-input-7.txt
line7=$(head -n 1 $file7)
if [ $line7 -ge $file7best ]; then
   rm -f $file7
else
   file7best=$line7
   mv -f $file7 /home/adam/Desktop/saved
fi

./$1 tsp_example_1.txt
line8=$(head -n 1 $file8)
if [ $line8 -ge $file8best ]; then
   rm -f $file8
else
   file8best=$line8
   mv -f $file8 /home/adam/Desktop/saved
fi

./$1 tsp_example_2.txt
line9=$(head -n 1 $file9)
if [ $line9 -ge $file9best ]; then
   rm -f $file9
else
   file9best=$line9
   mv -f $file9 /home/adam/Desktop/saved
fi

./$1 tsp_example_3.txt
line10=$(head -n 1 $file10)
if [ $line10 -ge $file10best ]; then
   rm -f $file10
else
   file10best=$line10
   mv -f $file10 /home/adam/Desktop/saved
fi

done



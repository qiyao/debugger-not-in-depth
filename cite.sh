#!/bin/sh
INPUT=$1
if [ $# -eq 1 ];then
OUTPUT=$1.tex
else
OUTPUT=$2
fi
#echo $INPUT
#echo $OUTPUT
echo "\\renewcommand\\baselinestretch{0.5}\\selectfont" > $OUTPUT
echo "\\begin{verbatim}" >> $OUTPUT
cat $INPUT >> $OUTPUT
echo "\\end{verbatim}" >> $OUTPUT
echo "\\par" >> $OUTPUT


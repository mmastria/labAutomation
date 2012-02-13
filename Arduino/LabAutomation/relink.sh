#!/bin/bash
p=$(pwd)
for i in $(find $p/* -type d)
do
  cd $i
  pwd
  for j in $(find * -type f -name "*[h,cpp]")
  do
    echo $j
    mv $j ..
    ln -s ../$j
  done
  ls -lah
  echo .
  echo . ...............................
  echo .
  cd $p
done


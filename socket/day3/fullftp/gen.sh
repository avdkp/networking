#!/bin/bash

for((i=$1; i<= $2; i++))
do
   #dd if=/dev/zero of=data/files$i bs=1024 count=1024
   for((j=0;j<100;j++))
   do
	echo "this is file no "$i>>data/files$i

   done
done



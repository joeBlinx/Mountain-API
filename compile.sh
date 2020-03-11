#!/bin/bash

list=`ls $1`

for a in $list
do
	name=`cut -d . -f 1 <<< $a`
	ext=`cut -d . -f 2 <<< $a`
	glslangValidator -V $1/$a
	echo "move $ext.spv to $2/$name$ext.spv"
	mv $ext.spv $2/$name$ext.spv
	
done
	


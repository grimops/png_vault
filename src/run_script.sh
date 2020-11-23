#!/bin/bash
make
if [ $? -eq 0 ]
then
	./png_vault example0.png example1.png
	if [ $? -eq 0 ]
	then
		display example1.png
	fi
fi

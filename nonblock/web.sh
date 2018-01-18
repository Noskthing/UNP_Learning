#!/bin/sh

case $# in
1) break ;;
*) echo "one argument (#simultaneous connections) required" 1>&2
   exit 1;;
esac

time ./web $1 www.foobar.com / \
	image1.gif image2.gif image3.gif \
	image4.gif image5.gif image6.gif \
	image7.gif

#!/usr/bin/env bash
num=1
for ((i=0;i<$1;i += 1, num <<= 1)); do
	hyperfine --warmup 3 "./cmake-build-release/circle_detection points4.txt $num 1"
done


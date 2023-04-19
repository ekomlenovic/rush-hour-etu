#!/bin/bash

cd ./export/BFS_Initial_MAP

variable=$(ls -v *.svg)
i=0
for f in $variable;do
    convert -crop 350x350+0+0 -resize 350x350 "$f" "Initial_MAP_Soluce_$(printf '%03d' "$i").jpg"
    let i=i+1
done
convert -delay 100 -loop 0 *.jpg animated.gif

rm *.jpg
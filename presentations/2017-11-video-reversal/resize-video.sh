#!/usr/bin/env bash
videos="$(find -type f -iname '*.mp4')"
target_res="640:340"

for video in $videos; do
    ffmpeg -i "$video" -vf scale="$target_res" "${video%%.mp4}_small.mp4"
done

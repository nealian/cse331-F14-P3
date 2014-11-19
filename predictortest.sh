#!/bin/sh

echo "gshare predictor:"
(bunzip2 -c -k $1 | ./predictorg)

echo #newline
echo "Alpha 21264 predictor:"
(bunzip2 -c -k $1 | ./predictor21264)

exit 0

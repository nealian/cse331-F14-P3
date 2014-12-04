#!/bin/sh
## Used to test both predictors at once with the same trace.
## Usage: ./predictortest.sh </path/to/tracefile.bz2> OR ./predictortest.sh </path/to/binary/tracefile>

echo "gshare predictor:"
if echo $1 | grep -qE 'bz2$'; then
    (bunzip2 -c -k $1 | ./predictorg)
else
    (./predictorg $1)
fi

echo #newline
echo "Alpha 21264 predictor:"
if echo $1 | grep -qE 'bz2$'; then
    (bunzip2 -c -k $1 | ./predictor21264)
else
    (./predictor21264 $1)
fi

exit 0

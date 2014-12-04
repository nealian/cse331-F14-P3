CC=g++
OPTS=-g

all: predictorg predictor21264

# Use the same main file for each predictor.
predictorg: traceread.h predictorg.cpp traceread.cpp main.cpp
	$(CC) $(OPTS) -lm -o predictorg main.cpp traceread.cpp predictorg.cpp -DPREDICTORG

predictor21264: traceread.h predictor21264.cpp traceread.cpp main.cpp
	$(CC) $(OPTS) -lm -o predictor21264 main.cpp traceread.cpp predictor21264.cpp -DPREDICTOR21264

clean:
	rm -f predictorg predictor21264;

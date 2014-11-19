CC=g++
OPTS=-g

all:

predictorg: traceread.h predictorg.o traceread.o
	$(CC) $(OPTS) -lm -o predictor main.cpp traceread.o predictorg.o -DPREDICTORG

predictor21264: traceread.h predictor21264.o traceread.o
	$(CC) $(OPTS) -lm -o predictor main.cpp traceread.o predictor21264.o -DPREDICTOR21264

traceread.o: traceread.h traceread.cpp
	$(CC) $(OPTS) -c traceread.cpp

predictorg.o: predictorg.h predictorg.cpp
	$(CC) $(OPTS) -c predictorg.cpp

predictor21264.o: predictor21264.h predictor21264.cpp
	$(CC) $(OPTS) -c predictor21264.cpp

clean:
	rm -f *.o predictor;

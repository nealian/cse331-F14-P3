PREDICTOR ?= g
CC=g++

ifeq "$(PREDICTOR)" "g"
  OPTS=-g -DPREDICTORG
else
  OPTS=-g -DPREDICTOR21264
endif 

all: predictor

predictor: traceread.h predictor$(PREDICTOR).o traceread.o
	$(CC) $(OPTS) -lm -o predictor main.cpp traceread.o predictor$(PREDICTOR).o

traceread.o: traceread.h traceread.cpp
	$(CC) $(OPTS) -c traceread.cpp

predictorg.o: predictorg.h predictorg.cpp
	$(CC) $(OPTS) -c predictorg.cpp

predictor21264.o: predictor21264.h predictor21264.cpp
	$(CC) $(OPTS) -c predictor21264.cpp

clean:
	rm -f *.o predictor;

CC=g++
OPTS=-g

all: main.o traceread.o predictor.o
	$(CC) $(OPTS) -lm -o predictor main.o traceread.o predictor.o

main.o: main.cpp traceread.h predictor.h
	$(CC) $(OPTS) -c main.cpp

traceread.o: traceread.h traceread.cpp
	$(CC) $(OPTS) -c traceread.cpp

predictor.o: predictor.h predictor.cpp
	$(CC) $(OPTS) -c predictor.cpp

clean:
	rm -f *.o predictor;

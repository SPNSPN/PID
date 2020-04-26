SRC := src
INC := include
BLD := build

GCC := g++ -std=c++14 -Wall -O2
CFLAGS := -I$(INC)

$(BLD)/main: $(BLD)/main.o $(BLD)/PID.o
	$(GCC) $(CFLAGS) -o $@ $^

$(BLD)/PID.o: $(SRC)/PID.cpp $(INC)/PID.h
	$(GCC) $(CFLAGS) -c -o $@ $<

$(BLD)/main.o: $(SRC)/main.cpp $(INC)/PID.h
	$(GCC) $(CFLAGS) -c -o $@ $<

.PHONY: clean run
clean:
	rm $(BLD)/*

run: $(BLD)/main
	$<

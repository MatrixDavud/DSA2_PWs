# -*- Makefile -*-

FLAGS = -Wall -g
LIBS=

OBJS = heap-main.o heap.o
EXE = heap-main
all : $(EXE)


heap-main: $(OBJS)
	@echo "Building $@"
	@$(CC) -o $@ $(OBJS) $(LIBS) $(FLAGS)

heap-main.o : heap-main.c heap.h
	@echo "Building $@"
	@$(CC) $(FLAGS) -c  heap-main.c 

heap.o : heap.c heap.h 
	@echo "Building $@"
	@$(CC) $(FLAGS)  -c heap.c


clean:
	rm -rf $(EXE) *.o *.dSYM *~



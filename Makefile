PROG = maze
CC = g++
CPPFLAGS = -Wall -ggdb -std=c++11
LDFLAGS = -lpng 
OBJS = main.o Parser.o Square.o Maze.o Node.o Path.o Writer.o

all: $(PROG) .depend

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.depend:
	-@$(CC) $(CPPFLAGS) -MM $(OBJS:.o=.cpp) > $@ 2> /dev/null

-include .depend

clean:
	rm -f *stackdump $(PROG) $(OBJS)
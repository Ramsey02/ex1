CC=gcc
OBJS= RLEList.o tool/AsciiArtTool.o tool/main.o
EXEC=AsciiArtTool
DEBUG_FLAG = # now empty, assign -g for debug 
COMP_FLAG=-std=c99 -Wall -Werror -pedantic-errors $(DEBUG_FLAG)

$(EXEC):	$(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
RLEList.o:	RLEList.c	RLEList.h
	$(CC) -c	$(DEBUG_FLAG) $(COMP_FLAG) $*.c

tool/AsciiArtTool.o:	RLEList.h	tool/AsciiArtTool.h	tool/AsciiArtTool.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $@ 

tool/main.o:	tool/AsciiArtTool.h	RLEList.h	tool/main.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $@  

clean:
	rm -f $(OBJS) $(EXEC)

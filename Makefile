LIBS	= lib/libmsgpackc.a
OBJS	= main.o base64.o
SOURCE	= main.c base64.c
HEADER	= 
OUT	= main
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -Iinclude

all: $(OBJS) $(LIBS)
	$(CC) -g $(OBJS) $(LIBS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) $(LFLAGS) $^

base64.o: base64.c
	$(CC) $(FLAGS) $(LFLAGS) $^ 


clean:
	rm -f $(OBJS) $(OUT)

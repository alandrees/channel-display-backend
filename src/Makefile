#Copyright 2015 Alan Drees
#
#Hand-spun makefile for channel_display program
CC=g++

CFLAGS=-Wall -std=c++11

LIBS=-lrtmidi -lwiringPi

INCLUDE_DIRS=-I~/include

LIB_DIRS=-L~/lib

midi: main

#main application
main: channel_display.o lcd_output.o output.o midi_input.o input.o lcd_backend.o
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(LIB_DIRS)  channel_display.o lcd_output.o lcd_backend.o output.o midi_input.o input.o main.cpp -o channel_display $(LIBS)

#application object
channel_display.o: lcd_output.o output.o midi_input.o input.o lcd_backend.o
	$(CC) $(CFLAGS) -c channel_display.cpp -o channel_display.o

midi_input.o: input.o output.o
	$(CC) $(CFLAGS) -c midi_input.cpp -o midi_input.o

lcd_backend.o:
	$(CC) $(CFLAGS) -c lcd_backend.cpp -o lcd_backend.o

lcd_output.o: output.o
	$(CC) $(CFLAGS) -c lcd_output.cpp -o lcd_output.o

output.o: output.cpp
	$(CC) $(CFLAGS) -c output.cpp -o output.o

input.o: input.cpp
	$(CC) $(CFLAGS) -c input.cpp -o input.o

clean:
	rm *.o channel_display

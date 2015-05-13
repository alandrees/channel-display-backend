#Copyright 2015 Alan Drees
#
#Hand-spun makefile for channel_display program
CC=g++

CFLAGS=-Wall -std=c++11

midi: main

#main application
main: channel_display.o lcd_output.o output.o midi_input.o input.o
	$(CC) $(CFLAGS) channel_display.o lcd_output.o output.o midi_input.o input.o -o channel_display -lrtmidi

#application object
channel_display.o: lcd_output.o output.o midi_input.o input.o
	$(CC) $(CFLAGS) -c lcd_output.o output.o midi_input.o input.o channel_display.cpp -o channel_display.o

midi_input.o: input.o output.o
	$(CC) $(CFLAGS) -c midi_input.cpp -o midi_input.o

lcd_output.o: output.o
	$(CC) $(CFLAGS) -c lcd_output.cpp -o lcd_output.o

output.o: output.cpp
	$(CC) $(CFLAGS) -c output.cpp -o output.o

input.o: input.cpp
	$(CC) $(CFLAGS) -c input.cpp -o input.o

clean:
	rm *.o channel_display
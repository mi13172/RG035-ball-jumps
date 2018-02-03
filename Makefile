PROGRAM   = ball_jump
CC        = gcc
CFLAGS    = -g 
LDFLAGS   = -lGL -lGLU -lglut -lm

$(PROGRAM): ball_jump.o
	$(CC) -o $(PROGRAM) ball_jump.o $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)



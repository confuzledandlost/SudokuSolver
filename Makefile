CFLAGS=-g
LDFLAGS=-lpthread
CC=gcc

all: sudoku.x

sudoku.x: sudoku.c mission.h checker.h rowGrabber.h columnGrabber.h
	${CC} -o $@ ${CFLAGS} ${LDFLAGS} $<

check: sudoku.x
	for t in tests/*; do ./sudoku.x < $$t; done
	for t in tests/*; do ./sudoku.x --fork < $$t; done

clean:
	rm -f sudoku.x


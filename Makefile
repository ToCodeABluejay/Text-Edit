LIBS = -lcurses -lm

edit:
	cc  -o $@ *.c ${LIBS}

clean:
	rm edit

install:
	cp edit /bin/edit

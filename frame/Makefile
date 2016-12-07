all: figure

EPS = unwind_frame.eps gdb_frame.eps
figure: figure.mp $(EPS)
	mpost figure.mp

clean:
	-rm -rf figure.1 figure.log
	-rm -rf *.eps

%.eps:%.dia
	dia -e $@ $<

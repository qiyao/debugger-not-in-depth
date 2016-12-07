%.o: %.c
	gcc -g3 -c $< -o $@

all: simple-debugger hellodebugger simple-debugger-output

hellodebugger: hellodebugger.o
	gcc -g3 $< -o $@

simple-debugger: simple-debugger.o
	gcc -g3 $< -o $@

simple-debugger-output: simple-debugger hellodebugger
	./simple-debugger >  $@


clean:
	-rm *.o
	-rm simple-break int3
	-rm *.tex
	-rm *.aux

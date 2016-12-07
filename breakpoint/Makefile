%.o: %.c
	gcc -g3 -c $< -o $@

all: simple-break-output break-ops-output break dis-int3

dis-int3: int3
	objdump -d int3 | grep "<main>" -A 8 > dis-int3

int3: int3.o
	gcc -g3 $< -o $@

simple-break: simple-break.o
	gcc -g3 $< -o $@

break-ops: break-ops.o
	gcc -g3 $< -o $@

break-ops-output: break-ops
	./break-ops > $@

simple-break-output: simple-break int3
	./simple-break >  $@

break: break.mp
	mpost break.mp
clean:
	-rm *.o
	-rm simple-break int3
	-rm *.tex
	-rm *.aux
	-rm break.1 break.2 break.3 break.4 break.4 break.5 break.6

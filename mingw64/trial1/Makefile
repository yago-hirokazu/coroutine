
trail1.exe: main.o trampoline.o
	gcc -O0 -g main.c trampoline.o -o trial1.exe

trampoline.o: trampoline.S
	gcc -c trampoline.S -o trampoline.o

clean:
	rm -rf *.o *.exe


trail2.exe: coroutine_start.o coroutine_transit.o coroutine.o coroutine_test1.o
	gcc -O0 -g coroutine_test1.c coroutine.o coroutine_start.o coroutine_transit.o -o trial2.exe

coroutine_start.o:
	gcc -c coroutine_start.S -o coroutine_start.o

coroutine_issue.o:
	gcc -c coroutine_issue.S -o coroutine_issue.o

coroutine.o:
	gcc -c coroutine.c -o coroutine.o

clean:
	rm -rf *.o *.exe

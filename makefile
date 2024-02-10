TARGET = proc

proc : processor.o checking.o stack.o commands.o bin-file.o ram.o
	gcc processor.o checking.o stack.o commands.o bin-file.o ram.o -o proc

processor.o : processor.c
	gcc -c processor.c -o processor.o

checking.o : checking.c
	gcc -c checking.c -o checking.o

stack.o : stack.c
	gcc -c stack.c -o stack.o

commands.o : commands.c
	gcc -c commands.c -o commands.o

bin-file.o : bin-file.c
	gcc -c bin-file.c -o bin-file.o

ram.o : ram.c
	gcc -c ram.c -o ram.o

.PHONY : clean
clean :
	del *.o $(TARGET).exe -rf

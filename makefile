TARGET = Project

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))


$(TARGET) : $(OBJ)
	gcc $(OBJ) -o $(TARGET)

%.o : %.c
	gcc -c $< -o $@


.PHONY : clean
clean :
	del *.o $(TARGET).exe -rf

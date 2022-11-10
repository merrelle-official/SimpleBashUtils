#Compilation сommand
CC=gcc -Wall -Werror -Wextra -o

#The name of the executable file
EXE_NAME=cat.exe

#The name of the file to compile
C_NAME=cat.c

#Launch сommand
START=./$(EXE_NAME)

all:
	$(CC) $(EXE_NAME) $(C_NAME)
	$(START) -e a.txt

rebuild:
	rm -rf $(EXE_NAME)
	$(CC) $(EXE_NAME) $(C_NAME)

clean:
	rm -rf $(EXE_NAME)

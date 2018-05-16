TARGET= ball-jump
CC= gcc -std=c99 -Wall -Wextra -g
SRC= $(shell find ./ -name *.c)

$(TARGET): $(SRC)
	gcc $^ -o $@ -lGL -lGLU -lglut

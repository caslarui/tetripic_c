CXX = gcc
FLAGS = -Werror -Wall -Wextra
INC_PATH = ./includes/
OBJ_PATH = ./obj/
FILE_NAME = tetripic

SRC := $(wildcard ./sources/*.c)
OBJS := $(SRC:.c=.o)


.PHONY : all clean

all: build

build: $(FILE_NAME) 

%.o: %.c
	@$(CXX) $(FLAGS) -c $< -o $@ -I$(INC_PATH)

$(FILE_NAME) : $(OBJS)
	@$(CXX) $(FLAGS) $(OBJS) -o $@  -lm
	@mkdir -p $(OBJ_PATH)
	@mv ./sources/*.o $(OBJ_PATH)
	@echo "BUILD DONE"


run_task1:
	@./$(FILE_NAME) "1"

run_task2:
	@./$(FILE_NAME) 2

run_task3:
	@./$(FILE_NAME) 3

run_task4:
	@./$(FILE_NAME) 4

clean:
	@rm -rf $(OBJ_PATH) $(FILE_NAME)
	@rm *.bmp
	@echo "CLEAN DONE"

re: clean
	build
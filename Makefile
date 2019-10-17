#OBJS specifies which files to compile as part of the project 
OBJS = game.c bird.c engine.c pipe.c text.c inteligence.c genann.c genetics.c
#CC specifies which compiler we're using 
CC = clang 
#COMPILER_FLAGS specifies the additional compilation options we're using 
COMPILER_FLAGS =  -Wall -Wextra -ggdb -std=c11 -Wl,-rpath -Wl,./dep/lib
#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -I./dep/include -L./dep/lib -lSDL2 -lSDL2_image -lSDL2_ttf  -lpng -ldl -lm
#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = flappyBird 
#This is the target that compiles our executable 
all : $(OBJS) 
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

OBJS = Setup.cpp main.cpp Texture.cpp Game.cpp SdlWindow.cpp TextGenerator.cpp Level.cpp Letter.cpp
OBJ_NAME = typer

CC = g++

COMPILER_FLAGS = -Wall -Werror -w -g

LINKER_FLAGS = -lX11 -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf 

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o  $(OBJ_NAME)

run: 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o  $(OBJ_NAME)
	./typer

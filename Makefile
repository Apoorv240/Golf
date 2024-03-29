#OBJS specifies which files to compile as part of the project
OBJS = src/main.c src/window.c src/texture.c src/golfball.c src/util.c src/hole.c src/game.c src/guide.c src/collision.c src/collisionDetector.c

#CC specifies which compiler we're using
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\mingwlibs\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\mingwlibs\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = 

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Golf

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
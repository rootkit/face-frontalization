# particle-system Makefile

EXE = face_frontalization
OBJ_DIR = bin

CFLAGS = -g -w
# CXXFLAGS = -w -Wall -Wextra -g -std=c++0x
# LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm

dummy_build_folder := $(shell mkdir -p $(OBJ_DIR))

 # c++ source files of the project
 # change the location of source.cpp according to your dlib setup
CXXFILES = $(shell find src -type f -name '*.cpp') \
			/usr/include/dlib-18.18/dlib/all/source.cpp
CXXOBJ = $(patsubst src/%.cpp,bin/%.o,$(CXXFILES))

INCLUDE = -I/usr/include/dlib-18.18
LIBS = `pkg-config --libs opencv`
CXXFLAGS = `pkg-config --cflags opencv` -w -Wall -Wextra -g -std=c++0x
LDFLAGS = -lpthread -lcurl -lGL -lGLU -lglut -lX11
CFLAGS = `pkg-config --cflags opencv` -g -w

MKDIR = mkdir -p

ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

###################################################################
# This is a Makefile progress indicator.
# BUILD is initially undefined

ifndef BUILD

# max equals 256 x's
sixteen := x x x x x x x x x x x x x x x x
MAX := $(foreach x,$(sixteen),$(sixteen))

# T estimates how many targets we are building by replacing BUILD with
# a special string
T := $(shell $(MAKE) -nrRf $(firstword $(MAKEFILE_LIST)) $(MAKECMDGOALS) \
            BUILD="COUNTTHIS" | grep -c "COUNTTHIS")

# N is the number of pending targets in base 1, well in fact, base x
# :-)
N := $(wordlist 1,$T,$(MAX))

# auto-decrementing counter that returns the number of pending targets
# in base 10
counter = $(words $N)$(eval N := $(wordlist 2,$(words $N),$N))

# BUILD is now defined to show the progress, this also avoids
# redefining T in loop
BUILD = @echo $(counter) of $(T)
endif
###################################################################

# .PHONY: directories all
#
# directories: ${OUT_DIR}
# ${OUT_DIR}:
# 	${MKDIR} ${OUT_DIR}


all: $(EXE)
	# build successful


$(EXE): $(CXXOBJ)
	$(CXX) $(CXXOBJ) -o $(EXE) $(LIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX)  $(INCLUDE) $< -c -o $@ $(CXXFLAGS)
	$(BUILD)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

run: all
	./$(EXE)

clean:
	# Cleaning...
	-rm -f $(EXE) $(CXXOBJ)
	rmdir bin/

# Generates full documentation for the project
dox:
	doxygen Doxyfile
	# Documentation generated!

doxclean:
	rm -rf doc/html
	# Documentation cleaned!

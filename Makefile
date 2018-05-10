#Directories
SRCDIR	:= src/
HDRDIR	:= $(SRCDIR)include/
LIBDIR  := lib/
INCDIR  := include/
OBJDIR	:= obj/
SUBDIRS := $(OBJDIR)entities $(OBJDIR)entities/characters $(OBJDIR)entities/items $(OBJDIR)managers $(OBJDIR)AI $(OBJDIR)states $(OBJDIR)menu_screens $(OBJDIR)ChaoticEngine $(OBJDIR)ChaoticEngine/manager $(OBJDIR)ChaoticEngine/fachada

#Files
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(subst $(SRCDIR),$(OBJDIR),$(SOURCES:%.cpp=%.o))
BINARY 	:= 3KSC

#Compiler set-up
CC		:= g++
LDFLAGS := -Wl,-rpath=$(LIBDIR)

INCLUDE := -I$(HDRDIR) -I$(INCDIR) -I$(INCDIR)ChaoticEngine -I$(INCDIR)irrlicht -I$(INCDIR)sfml -I$(INCDIR)box2D -I$(INCDIR)nlohmann -I$(INCDIR)raknet/raknet -I$(INCDIR)fmod -I$(INCDIR)OpenGL -I$(INCDIR)glm
LIBS	:= -L$(LIBDIR) -lIrrlicht -lGL -lGLEW -lglfw -lassimp -lXxf86vm -lXext -lX11 -lXcursor -lsfml-graphics -lsfml-window -lsfml-system -lBox2D -lraknet -lRakNetLibStatic -lfmod -lfmodL -lfmodstudio -lfmodstudioL -lassimp
FAST	:= -j4

#Make binary
$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(INCLUDE) $(LIBS)

#Make objects
$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(MAKE) setup
	$(CC) -o $@ -c $^ $(INCLUDE)

#Create object directories
setup:
	mkdir -p $(SUBDIRS)

#Deletes object files
clean:
	rm -R -f $(OBJDIR)
	rm -f $(BINARY)
	rm -f $(BINARY).exe

#Makes binary (previous clean)
cleanc:
	$(MAKE) clean
	$(MAKE) $(FAST)

#Runs after compiling
run:
	$(MAKE) $(FAST)
	./$(BINARY)

#Cleans, compiles and runs
cleanr:
	$(MAKE) cleanc
	./$(BINARY)

#Compile the program with 4 threads
fast:
	$(MAKE) $(FAST)

#Prints sources, objects and headers lists
info:
	$(info $(BINARY))
	$(info $(OBJECTS))
	$(info $(SOURCES))
	$(info $(INCLUDE))
	$(info $(LIBS))
	$(info $(MAKE))

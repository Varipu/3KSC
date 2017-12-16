#Directories
SRCDIR	:= src/
OBJDIR	:= obj/
HDRDIR	:= src/headers/
SUBDIRS := $(OBJDIR)entities $(OBJDIR)managers

#Files
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(subst $(SRCDIR),$(OBJDIR),$(SOURCES:%.cpp=%.o))
BINARY 	:= 3KSC

#Compiler set-up
CC		:= g++
INCLUDE := -I$(HDRDIR) -I$(SRCDIR)irrlicht/include -I$(SRCDIR)sfml/include -I$(SRCDIR)box2D/include
LIBS	:= -L$(SRCDIR)irrlicht/lib/Linux -lIrrlicht -L$(SRCDIR)lib -lGL -lXxf86vm -lXext -lX11 -lXcursor -L$(SRCDIR)sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -L$(SRCDIR)box2D/lib -lbox2d

#Make binary
$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDE) $(LIBS)

#Make objects
$(OBJDIR)%.o: $(SRCDIR)%.cpp
	make setup
	$(CC) -o $@ -c $^ $(INCLUDE)

#Create object directories
setup:
	mkdir -p $(SUBDIRS)

#Deletes object files
clean:
	rm -R -f $(OBJDIR)
	rm -f 3KSC
	rm -f 3KSC.exe

#Makes binary (previous clean)
cleanc:
	make clean
	make

#Runs after compiling
run:
	make
	./3KSC

#Cleans, compiles and runs
cleanr:
	make clean
	make
	./3KSC

#Prints sources, objects and headers lists
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))
	$(info $(INCLUDE))
	$(info $(LIBS))
# Example 05
EXE=ex05

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lglew32 -lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
ex05.o: ex05.c CSCIx239.h
fatal.o: fatal.c CSCIx239.h
loadtexbmp.o: loadtexbmp.c CSCIx239.h
print.o: print.c CSCIx239.h
project.o: project.c CSCIx239.h
errcheck.o: errcheck.c CSCIx239.h
object.o: object.c CSCIx239.h
fps.o: fps.c CSCIx239.h
elapsed.o: elapsed.c CSCIx239.h
shader.o: shader.c CSCIx239.h
noise.o: noise.c CSCIx239.h
bicycle.o: bicycle.c CSCIx239.h
sidewalk.o: sidewalk.c CSCIx239.h
trash.o: trash.c CSCIx239.h
lightpost.o: lightpost.c CSCIx239.h
car.o: car.c CSCIx239.h
fireHydrant.o: fireHydrant.c CSCIx239.h
building.o: building.c CSCIx239.h
door.o: door.c CSCIx239.h
window.o: window.c CSCIx239.h
skyBox.o: skyBox.c CSCIx239.h
#  Create archive
CSCIx239.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o fps.o elapsed.o shader.o noise.o bicycle.o sidewalk.o trash.o lightpost.o car.o fireHydrant.o building.o door.o window.o skyBox.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
ex05:ex05.o CSCIx239.a
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)

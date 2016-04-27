# Example 05
EXE=final

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
final.o: final.c final.h
fatal.o: fatal.c final.h
loadtexbmp.o: loadtexbmp.c final.h
print.o: print.c final.h
project.o: project.c final.h
errcheck.o: errcheck.c final.h
object.o: object.c final.h
fps.o: fps.c final.h
elapsed.o: elapsed.c final.h
shader.o: shader.c final.h
noise.o: noise.c final.h
bicycle.o: bicycle.c final.h
sidewalk.o: sidewalk.c final.h
trash.o: trash.c final.h
lightpost.o: lightpost.c final.h
car.o: car.c final.h
fireHydrant.o: fireHydrant.c final.h
building.o: building.c final.h
door.o: door.c final.h
window.o: window.c final.h
skyBox.o: skyBox.c final.h
#  Create archive
final.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o fps.o elapsed.o shader.o noise.o bicycle.o sidewalk.o trash.o lightpost.o car.o fireHydrant.o building.o door.o window.o skyBox.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
final:final.o final.a
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)

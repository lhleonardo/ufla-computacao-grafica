# Linux Makefile for VART Example "Texture"
# (C) Bruno de Oliveira Schneider - May 2014

# This Makefile requires a local directory "vart" with
# source code for the V-ART framework. Create a symbolic
# link to the real directory and you'll be OK.

APPLICATION = textureExample
CXXFLAGS = -Wall -I. -DVART_OGL -DIL_LIB -std=c++11
LDFLAGS = -L/usr/X11R6/lib
LDLIBS = -lGL -lglut -lGLU -lIL

OBJECTS = sgpath.o snlocator.o scenenode.o boundingbox.o\
          material.o texture.o color.o light.o\
          dof.o graphicobj.o file.o joint.o meshobject.o transform.o\
          picknamelocator.o mesh.o memoryobj.o modifier.o bezier.o\
          sphere.o point4d.o\
          scene.o camera.o mousecontrol.o viewerglutogl.o

%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.o: vart/source/%.cpp vart/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: vart/contrib/source/%.cpp vart/contrib/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(APPLICATION): $(OBJECTS) main.o
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f *.o *~ $(APPLICATION)

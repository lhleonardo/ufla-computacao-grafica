# Linux Makefile for VART Example "Vigilance Camera"
# (C) Bruno de Oliveira Schneider - APR/22/2008

# This Makefile requires a local directory "vart" with
# source code for the V-ART framework. Create a symbolic
# link to the real directory and you'll be OK.

APPLICATION = camera
CXXFLAGS = -Wall -I. -DVART_OGL -DIL_LIB -std=c++11
LDFLAGS = -L/usr/X11R6/lib
LDLIBS = -lGL -lglut -lGLU -lIL

OBJECTS =  color.o sgpath.o snlocator.o scenenode.o\
scene.o texture.o material.o\
boundingbox.o memoryobj.o graphicobj.o cylinder.o light.o\
picknamelocator.o mesh.o meshobject.o point4d.o curve.o bezier.o\
transform.o sphere.o camera.o mousecontrol.o file.o\
modifier.o dof.o joint.o biaxialjoint.o viewerglutogl.o\
vigilancecamera.o

$(APPLICATION): $(OBJECTS) main.o
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f *.o *~ camera

%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.o: vart/source/%.cpp vart/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: vart/contrib/source/%.cpp vart/contrib/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<


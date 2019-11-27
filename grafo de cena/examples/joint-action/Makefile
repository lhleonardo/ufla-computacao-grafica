# Linux Makefile for VART Example "Transform Animation"
# (C) Bruno de Oliveira Schneider - May 2014

# This Makefile requires a local directory "vart" with
# source code for the V-ART framework. Create a symbolic
# link to the real directory and you'll be OK.

CXXFLAGS = -Wall -I. -DVART_OGL -DIL_LIB -std=c++11
LDFLAGS = -L/usr/X11R6/lib
LDLIBS = -lGL -lglut -lGLU -lIL
TARGET = jointanimation
TARGETSRC = main.o

OBJECTS = color.o sgpath.o snlocator.o scenenode.o scene.o texture.o material.o\
boundingbox.o memoryobj.o graphicobj.o cylinder.o light.o\
mesh.o meshobject.o box.o point4d.o curve.o bezier.o camera.o\
transform.o sphere.o mousecontrol.o file.o\
linearinterpolator.o sineinterpolator.o\
modifier.o dof.o joint.o uniaxialjoint.o viewerglutogl.o\
dofmover.o noisydofmover.o jointmover.o\
time.o baseaction.o transformaction.o translationaction.o\
jointaction.o scaleaction.o rotationaction.o shearaction.o\
picknamelocator.o $(TARGETSRC)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f *.o *~ $(TARGET)

# Try to compile from project ...
%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

# ... then try from V-ART Core ...
%.o: vart/source/%.cpp vart/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

# ... then try from V-ART Contrib.
%.o: vart/contrib/source/%.cpp vart/contrib/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<


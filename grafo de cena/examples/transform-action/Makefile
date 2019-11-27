# Linux Makefile for VART Example "Transform Action"
# (C) Bruno de Oliveira Schneider - May 2014

# This Makefile requires a local directory "vart" with
# source code for the V-ART framework. Create a symbolic
# link to the real directory and you'll be OK.

APPLICATION = transformAnimation
CXXFLAGS = -Wall -I. -DVART_OGL -DIL_LIB -std=c++11
LDFLAGS = -L/usr/X11R6/lib
LDLIBS = -lGL -lglut -lGLU -lIL

OBJECTS = color.o scenenode.o scene.o texture.o material.o\
boundingbox.o memoryobj.o graphicobj.o cylinder.o light.o\
mesh.o meshobject.o point4d.o curve.o bezier.o camera.o\
transform.o sphere.o mousecontrol.o file.o\
modifier.o dof.o joint.o biaxialjoint.o viewerglutogl.o\
sineinterpolator.o dofmover.o noisydofmover.o jointmover.o\
time.o baseaction.o transformaction.o translationaction.o\
jointaction.o scaleaction.o rotationaction.o shearaction.o\
sgpath.o snlocator.o picknamelocator.o

$(APPLICATION): $(OBJECTS) main.o
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f *.o *~ $(APPLICATION)

# Try to compile from project ...
%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

# ... then try from V-ART Core ...
%.o: vart/source/%.cpp vart/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

# ... then try from V-ART Contrib.
%.o: vart/contrib/source/%.cpp vart/contrib/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<


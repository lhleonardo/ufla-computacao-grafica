// main.cpp - transform animation example

// V-ART example: Moving objects with an idle handler

// This application shows how to use ViewerGlutOGL's idle handler to animate objects.

// Changelog
// Jun 17, 2008 - Bruno de Oliveira Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/light.h>
#include <vart/sphere.h>
#include <vart/transform.h>
#include <vart/contrib/viewerglutogl.h>

#include <iostream>

using namespace std;

class MyIHClass : public VART::ViewerGlutOGL::IdleHandler
{
    public:
        MyIHClass() : redRadians(0), greenRadians(0) {}
        virtual ~MyIHClass() {}
        virtual void OnIdle() {
            redRadians += 0.001;
            redRotPtr->MakeZRotation(redRadians);
            greenRadians += 0.001;
            greenRotPtr->MakeYRotation(greenRadians);
            viewerPtr->PostRedisplay();
        }
    //protected:
        VART::Transform* redRotPtr;
        VART::Transform* greenRotPtr;
    private:
        float redRadians;
        float greenRadians;
};

// The application itself:
int main(int argc, char* argv[])
{
    VART::ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)

    // create a camera (scene observer)
    VART::Camera camera(VART::Point4D(0,0,6),VART::Point4D(0,0,0),VART::Point4D(0,1,0,0));
    // create some objects
    VART::Transform redSphereTranslation;
    VART::Transform redSphereRotation;
    VART::Sphere redSphere;
    VART::Transform greenSphereRotation;
    VART::Sphere greenSphere;
    MyIHClass idleHandler;

    // Initialize scene objects
    redSphereTranslation.MakeTranslation(-2,0,0);
    redSphere.SetMaterial(VART::Material::PLASTIC_RED());
    greenSphereRotation.MakeIdentity();
    greenSphere.SetMaterial(VART::Material::PLASTIC_GREEN());

    // Build up the scene
    redSphereRotation.AddChild(redSphereTranslation);
    redSphereTranslation.AddChild(redSphere);
    greenSphereRotation.AddChild(greenSphere);
    scene.AddObject(&redSphereRotation);
    scene.AddObject(&greenSphereRotation);
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);

    // Set up the Idle Handler
    idleHandler.redRotPtr = &redSphereRotation;
    idleHandler.greenRotPtr = &greenSphereRotation;

    // Set up the viewer
    viewer.SetTitle("V-ART Glut idle handler example");
    viewer.SetScene(scene); // attach the scene
    viewer.SetIdleHandler(&idleHandler); // attach the idle handler to the viewer

    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}

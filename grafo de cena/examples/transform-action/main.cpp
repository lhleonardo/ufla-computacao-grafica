// main.cpp - Test application for TransformActions

// This application shows how to make simple animation using the classes TranslationAction,
// RotationAction, ScaleAction and ShearAction.

// Changelog
// Jul 09, 2008 - Bruno Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/transform.h>
#include <vart/baseaction.h>
#include <vart/translationaction.h>
#include <vart/rotationaction.h>
#include <vart/scaleaction.h>
#include <vart/shearaction.h>
#include <vart/light.h>
#include <vart/sphere.h>
#include <vart/callback.h>
#include <vart/meshobject.h>
#include <vart/contrib/viewerglutogl.h>

#include <iostream>

using namespace std;

class MyIHClass : public VART::ViewerGlutOGL::IdleHandler
{
    public:
        MyIHClass(){}
        virtual ~MyIHClass() {}
        virtual void OnIdle() {
            VART::BaseAction::MoveAllActive();
            viewerPtr->PostRedisplay();
        }
        VART::Transform* rotationPtr;
        VART::Transform* translationPtr;
    protected:
    private:
};

class ActionManager : public VART::CallBack
{
    public:
        ActionManager() : counter(0) {}
        virtual void Activate() {
            switch (counter) {
                case 0:
                    translationActionPtr->Activate();
                    break;
                case 1:
                    scaleActionPtr->Activate();
                    break;
                case 2:
                    rotationActionPtr->Activate();
                    break;
            }
            ++counter;
        }
        unsigned int counter;
        VART::TranslationAction* translationActionPtr;
        VART::RotationAction* rotationActionPtr;
        VART::ScaleAction* scaleActionPtr;
        VART::Sphere* finishSpherePtr;
};

using VART::Point4D;

// The application itself:
int main(int argc, char* argv[])
{
    VART::ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)
    // create a camera (scene observer)
    VART::Camera camera(Point4D(0,0,-10,1), Point4D(0,0,0,1), Point4D(0,-1,0,0));
    MyIHClass idleHandler;

    // Build up the scene -- begin
    VART::MeshObject refBox;
    refBox.MakeBox(-1,1,-1,1,-1,1);
    refBox.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());
    scene.AddObject(&refBox);
    // scene -> targetShear -> box
    VART::Transform targetShear;
    targetShear.MakeIdentity();
    scene.AddObject(&targetShear);  // scene -> targetShear
    VART::MeshObject box;
    box.MakeBox(-1,1,-1,1,-1,1);
    box.SetMaterial(VART::Material::PLASTIC_GREEN());
    //~ box.Hide();
    targetShear.AddChild(box); // targetShear -> box

    VART::Transform finishSphereTransform;
    finishSphereTransform.MakeTranslation(4,0,0);
    scene.AddObject(&finishSphereTransform);
    VART::Sphere finishSphere;
    finishSphere.SetMaterial(VART::Material::PLASTIC_RED());
    finishSphere.SetRadius(0.99);
    finishSphereTransform.AddChild(finishSphere);

    // scene -> targetRotation -> targetTranslation -> targetScale -> movingSphere
    VART::Transform targetRotation;
    targetRotation.MakeIdentity();
    scene.AddObject(&targetRotation); // scene -> targetRotation
    VART::Transform targetTranslation;
    targetRotation.AddChild(targetTranslation); // targetRotation -> targetTranslation
    VART::Transform targetScale;
    targetScale.MakeIdentity();
    targetTranslation.AddChild(targetScale); // targetTranslation -> targetScale
    VART::Sphere movingSphere;
    movingSphere.SetMaterial(VART::Material::PLASTIC_BLUE());
    targetScale.AddChild(movingSphere); // targetScale -> movingSphere

    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);
    // Build up the scene -- end

    // Set up actions -- begin
    VART::TranslationAction translationAction;
    translationAction.SetTarget(&targetTranslation);
    translationAction.SetTranslation(4,0,0);
    translationAction.SetDuration(3);

    VART::RotationAction rotationAction;
    rotationAction.SetTarget(&targetRotation);
    rotationAction.SetZRotation(2*3.1415926535897932384626433832795);
    rotationAction.SetDuration(6);
    rotationAction.SetCyclic(true);

    VART::ScaleAction scaleAction;
    scaleAction.SetTarget(&targetScale);
    scaleAction.SetScale(3,3,3);
    scaleAction.SetDuration(3);

    VART::ShearAction shearAction;
    shearAction.SetTarget(&targetShear);
    shearAction.SetShear(2,2);
    shearAction.SetDuration(6);

    // // Set up actions -- end

    // // Set up handlers, managers ,etc.
    ActionManager actionChainer;
    actionChainer.rotationActionPtr = &rotationAction;
    actionChainer.scaleActionPtr = &scaleAction;
    actionChainer.finishSpherePtr = &finishSphere;
    actionChainer.translationActionPtr = &translationAction;
    translationAction.callbackPtr = &actionChainer;
    scaleAction.callbackPtr = &actionChainer;
    shearAction.callbackPtr = &actionChainer;
    idleHandler.rotationPtr = &targetRotation;
    idleHandler.translationPtr = &targetTranslation;

    // Set up the viewer
    viewer.SetTitle("V-ART TransformAction example");
    viewer.SetScene(scene); // attach the scene
    viewer.SetIdleHandler(&idleHandler); // attach the idle handler to the viewer

    // Run application
    shearAction.Activate();
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}

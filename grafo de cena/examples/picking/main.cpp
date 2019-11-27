// main.cpp - object picker application

// V-ART example: Picking objects with a mouse.

// This application shows how to pick objects with the mouse inside a V-ART application.

// Changelog
// May 09, 2014 - Bruno de Oliveira Schneider
// - No longer using deprecated MeshObject::MakeBox()
// Oct 19, 2012 - Bruno de Oliveira Schneider
// - Adapted to new keyboard handler methods.
// Aug 28, 2006 - Bruno de Oliveira Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/cylinder.h>
#include <vart/light.h>
#include <vart/meshobject.h>
#include <vart/sphere.h>
#include <vart/box.h>
#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>

#include <iostream>

using namespace std;

// Define the keyboard handler
class KeyboardHandler : public VART::ViewerGlutOGL::KbHandler
{
    public:
        KeyboardHandler() {
        }
        virtual void OnKeyDown(int key) {
            switch (key)
            {
                case 'j':
                    break;
                case 'l':
                    break;
                case 'i':
                    break;
                case 'k':
                    break;
            }
        }
    private:
};

class ClickHandlerClass : public VART::MouseControl::ClickHandler
{
    public:
        ClickHandlerClass() {
        }
        virtual ~ClickHandlerClass() {};
        virtual void OnClick() {
            if (mouseCtrlPtr->LastClickIsDown()) {
                VART::MouseControl::ButtonID lastButton = mouseCtrlPtr->GetLastClickButton();

                if (lastButton == VART::MouseControl::LEFT) {
                    scenePtr->Pick(mouseCtrlPtr->GetClickXPosition(),
                                   mouseCtrlPtr->GetClickYPosition(), &pickList);
                    if (!pickList.empty()) {
                        cout << "Selected objects are: ";
                        while (!pickList.empty()) {
                            cout << pickList.front()->GetDescription() << " ";
                            pickList.pop_front();
                        }
                        cout << endl;
                    }
                }
                
            }
        }
        list<VART::GraphicObj*> pickList;
        VART::Scene* scenePtr;
};

// The application itself:
int main(int argc, char* argv[])
{
    VART::ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)

    KeyboardHandler kbh; // create a keyboard handler
    // create a camera (scene observer)
    VART::Camera camera(VART::Point4D(0,0,6),VART::Point4D(0,0,0),VART::Point4D(0,1,0,0));
    // create some objects
    VART::Transform sphereTrans;
    VART::Sphere sphere;
    VART::Transform cylinderTrans;
    VART::Cylinder cylinder;
    VART::Box box;
    VART::Transform monkeyTrans;
    VART::MeshObject* monkeyPtr;
    VART::Transform tempTransform;
    list<VART::MeshObject*> objects;
    ClickHandlerClass clickHandler;

    clickHandler.scenePtr = &scene;

    // Initialize scene objects
    sphereTrans.MakeTranslation(-1,1,0);
    sphere.SetMaterial(VART::Material::PLASTIC_RED());
    sphere.SetDescription("sphere");
    cylinderTrans.MakeXRotation(1.570796327);
    tempTransform.MakeTranslation(1,2,0);
    cylinderTrans = tempTransform * cylinderTrans;
    cylinder.SetHeight(2.0);
    cylinder.SetTopRadius(0.4);
    cylinder.SetBottomRadius(1.0);
    cylinder.SetPartsVisibility(VART::Cylinder::ALL);
    cylinder.SetMaterial(VART::Material::PLASTIC_GREEN());
    cylinder.SetDescription("cylinder");
    box.MakeBox(0.2,1.8,-1.8,-0.2,-1,1);
    box.SetMaterial(VART::Material::PLASTIC_BLUE());
    box.SetDescription("box");
    VART::MeshObject::ReadFromOBJ("monkey.obj", &objects);
    monkeyPtr = objects.front();
    monkeyPtr->SetDescription("monkey");
    monkeyTrans.MakeTranslation(-1,-1,0);
    tempTransform.MakeScale(0.8,0.8,0.8);
    monkeyTrans = monkeyTrans * tempTransform;

    // Build up the scene
    sphereTrans.AddChild(sphere);
    scene.AddObject(&sphereTrans);
    cylinderTrans.AddChild(cylinder);
    monkeyTrans.AddChild(*monkeyPtr);
    scene.AddObject(&cylinderTrans);
    scene.AddObject(&box);
    scene.AddObject(&monkeyTrans);
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);

    // Set up the viewer
    viewer.SetTitle("V-ART pick example");
    viewer.SetScene(scene); // attach the scene
    viewer.SetKbHandler(&kbh); // attach the keyboard handler
    viewer.SetClickHandler(&clickHandler);

    // Run application
    //~ cout << "Sphere ID: " << reinterpret_cast<unsigned int>(&sphere)
         //~ << " cylinder ID: " << reinterpret_cast<unsigned int>(&cylinder)
         //~ << " box ID: " << reinterpret_cast<unsigned int>(&box)
         //~ << " monkey ID: " << reinterpret_cast<unsigned int>(monkeyPtr) << endl;
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}

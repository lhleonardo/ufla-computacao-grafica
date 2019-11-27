// main.cpp - Wavefront OBJ viewer application

// V-ART example: Load and Display a OBJ file.

// This application shows how to create an object from a Wavefront OBJ file.

// Made from picker example, keeps the piking code.

// Changelog
// Oct 19, 2012 - Bruno de Oliveira Schneider
// - Adapted to new keyboard handler methods.
// Sep 26, 2012 - Bruno de Oliveira Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/box.h>
#include <vart/cylinder.h>
#include <vart/light.h>
#include <vart/meshobject.h>
#include <vart/sphere.h>
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
                        cout << pickList.size() << " selected objects: ";
                        while (!pickList.empty()) {
                            cout << pickList.front()->GetDescription() << ":\n";
#ifdef DEBUG
                            VART::MeshObject* ptObj = dynamic_cast<VART::MeshObject*>(pickList.front());
                            if (ptObj)
                                cout << *ptObj << "\n";
#endif
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

    if (argc < 2) {
        cerr << "Fatal error: No filename given.\nUsage: " << argv[0] << " filename\n"
             << "Where 'filename' is a Wavefront OBJ file.\n";
        return 1;
    }

    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)

    KeyboardHandler kbh; // create a keyboard handler
    // create a camera (scene observer)
    VART::Camera camera(VART::Point4D(0,0,6),VART::Point4D(0,0,0),VART::Point4D(0,1,0,0));
    // create some objects
    list<VART::MeshObject*> objects;
    ClickHandlerClass clickHandler;

    clickHandler.scenePtr = &scene;

    // Initialize scene objects
    VART::MeshObject::ReadFromOBJ(argv[1], &objects);

    // Build up the scene
    list<VART::MeshObject*>::iterator iter = objects.begin();
    for (; iter != objects.end(); ++iter) {
        scene.AddObject(*iter);
    }

    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);
    scene.MakeCameraViewAll();

    // Set up the viewer
    viewer.SetTitle("V-ART OBJ Viewer");
    viewer.SetScene(scene); // attach the scene
    viewer.SetKbHandler(&kbh); // attach the keyboard handler
    viewer.SetClickHandler(&clickHandler);

    // Run application
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}

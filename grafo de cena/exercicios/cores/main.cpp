#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>
#include <vart/scene.h>
#include <vart/box.h>
#include <vart/meshobject.h>
#include <vart/sphere.h>
#include <vart/texture.h>
#include <vart/transform.h>

using namespace std;

int main(int argc, char *argv[]) {
    VART::ViewerGlutOGL::Init(&argc, argv);
    static VART::ViewerGlutOGL viewer;
    static VART::Scene scene;
    
    //Add a camera to a scene and configure it.
    VART::Camera camera(VART::Point4D(0, 0, 20), VART::Point4D(0, 0, 0), VART::Point4D(0, 1, 0, 0));
	
    VART::Box caixa;
    caixa.MakeBox(0, 1, 0, 1, 0, 1);
    caixa.SetMaterial(VART::Material(VART::Color(255,165,0)));

    scene.AddObject(&caixa);

    // Add lights and cameras to the scene
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);
    
    // Set up the viewer
    viewer.SetTitle("V-ART Glut idle handler example");
    viewer.SetScene(scene); // attach the scene

    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    
    return 0;
}

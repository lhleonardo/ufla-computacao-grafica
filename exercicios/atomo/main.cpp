#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>
#include <vart/scene.h>
#include <vart/meshobject.h>
#include <vart/sphere.h>
#include <vart/texture.h>
#include <vart/transform.h>

using namespace VART;
using namespace std;

float conversor(float grau){
    float radiano=(grau/180)*M_PI;
    return radiano;
}

class IdleHandler : public VART::ViewerGlutOGL::IdleHandler {
    public:
        IdleHandler(VART::Transform* proton, VART::Transform* eletron): angulo(0) {
            protonTransform = proton;
            eletronTransform = eletron;
        }
        virtual ~IdleHandler() {}
        virtual void OnIdle() {
            eletronTransform->MakeYRotation(conversor(angulo));
            protonTransform->MakeXRotation(conversor(angulo));

            angulo += 1;

            viewerPtr->PostRedisplay();
        }
    private:
        VART::Transform* protonTransform;
        VART::Transform* eletronTransform;
        unsigned angulo;
};



int main(int argc, char *argv[]) {
    VART::ViewerGlutOGL::Init(&argc, argv);
    static VART::ViewerGlutOGL viewer;
    static VART::Scene scene;
    
    //Add a camera to a scene and configure it.
    VART::Camera camera(Point4D(0, 0, 20), Point4D(0, 0, 0), Point4D(0, 1, 0, 0));
	
    VART::Sphere proton, neutron, eletron;

    neutron.SetRadius(1);
    proton.SetRadius(0.2);
    eletron.SetRadius(0.2);

    neutron.SetMaterial(VART::Material::PLASTIC_RED());
    proton.SetMaterial(VART::Material::PLASTIC_GREEN());
    eletron.SetMaterial(VART::Material::PLASTIC_WHITE());

    VART::Transform eletronRotation, protonRotation, eletronTranslate, protonTranslate;

    eletronRotation.AddChild(eletronTranslate);
    protonRotation.AddChild(protonTranslate);

    eletronTranslate.MakeTranslation(3, 0, 0);
    protonTranslate.MakeTranslation(0, 0, 3);

    eletronTranslate.AddChild(eletron);
    protonTranslate.AddChild(proton);

    IdleHandler handler(&protonRotation, &eletronRotation);

    scene.AddObject(&neutron);
    scene.AddObject(&protonRotation);
    scene.AddObject(&eletronRotation);

    // Add lights and cameras to the scene
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);
    
    // Set up the viewer
    viewer.SetTitle("V-ART Glut idle handler example");
    viewer.SetScene(scene); // attach the scene
    viewer.SetIdleHandler(&handler);

    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    
    return 0;
}

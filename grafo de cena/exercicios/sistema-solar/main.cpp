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

class MyIHClass : public VART::ViewerGlutOGL::IdleHandler {
    public:
        MyIHClass(): anguloTerra(0), anguloLua(0){}
        virtual ~MyIHClass() {}
        virtual void OnIdle() {
            rotacaoTerra->MakeXRotation(conversor(anguloTerra));
            anguloTerra+= 0.2;

            rotacaoLua->MakeXRotation(conversor(anguloLua));
            anguloLua += 0.8;

            viewerPtr->PostRedisplay();
            
        }
        VART::Transform* rotacaoPropriaLua;
        VART::Transform* rotacaoLua;
        VART::Transform* rotacaoTerra;
    private:
        float anguloTerra;
        float anguloLua;
};

void applyTexture(VART::Sphere* object, string file) {
    VART::Texture texture;
    if (texture.LoadFromFile(file)) {
        VART::Material material;
        material.SetTexture(texture);
        object->SetMaterial(material);

    } else {
        cout << "Could not open texture file. Check if the image format is supported, "
             << "if it is in the correct path, and if V-Art was compiled with OpenGL "
             << "support and an image reader library." << std::endl;
    }
}

int main(int argc, char *argv[]) {
    VART::ViewerGlutOGL::Init(&argc, argv);
    static VART::ViewerGlutOGL viewer;
    static VART::Scene scene;
    
    //Add a camera to a scene and configure it.
    VART::Camera camera(Point4D(0, 50, 0), Point4D(0, 0, 0), Point4D(2, 0, 0, 0));
	
    MyIHClass idle;
    VART::Sphere earth, sun, moon;
    
    sun.SetRadius(5);
    earth.SetRadius(2);
    moon.SetRadius(1.5);

    applyTexture(&earth, "earth.jpg");
    applyTexture(&sun, "sun.gif");
    applyTexture(&moon, "moon.png");
	
    VART::Transform earthRotation, earthTranslation, moonTranslate, moonRotation, moonItselfRotation;

    earthRotation.AddChild(earthTranslation);

    earthTranslation.AddChild(earth);
    earthTranslation.AddChild(moonRotation);
    earthTranslation.MakeTranslation(0, 0, 14);

    moonRotation.AddChild(moonTranslate);
    
    moonTranslate.AddChild(moon);
    moonTranslate.MakeTranslation(0, 0,6);

    idle.rotacaoTerra = &earthRotation;
    idle.rotacaoLua = &moonRotation;

    moonItselfRotation.AddChild(moon);


    scene.AddObject(&sun);
    scene.AddObject(&earthRotation);

    // Add lights and cameras to the scene
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);
    
    // Set up the viewer
    viewer.SetTitle("V-ART Glut idle handler example");
    viewer.SetScene(scene); // attach the scene
    viewer.SetIdleHandler(&idle);
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    
    return 0;
}

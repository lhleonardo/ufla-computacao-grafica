#include <vart/scene.h>
#include <vart/box.h>
#include <vart/cylinder.h>
#include <vart/light.h>
#include <vart/meshobject.h>
#include <vart/sphere.h>
#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>

#include <iostream>
#include <cmath>

using namespace std;

class IdleHandler : public VART::ViewerGlutOGL::IdleHandler {
    public:
        IdleHandler(): degree(0), index(1) {}
        virtual ~IdleHandler() {}
        virtual void OnIdle() {
            for (VART::Transform* transform : *chairsTransform) {
                float a = 70*cos(radiansConversion(36*index + degree));
                float b = 70*sin(radiansConversion(36*index + degree));
                transform->MakeTranslation(0, b, a);
                incrementIndex();
            }
            wheelRotation->MakeXRotation(radiansConversion(-degree));
            
            degree += 0.1;

            viewerPtr->PostRedisplay();
        }

        VART::Transform* wheelRotation;
        std::list<VART::Transform*>* chairsTransform;
    private:
        float degree;
        unsigned index;

        float radiansConversion(float degree) {
            float radiano=(degree/180)*M_PI;
            return radiano;
        }

        void incrementIndex() {
            index++;
            if (index > 10) index = 1;
        }
};

int main(int argc, char* argv[]) {
    VART::ViewerGlutOGL::Init(&argc, argv); 

    static VART::Scene scene; 
    static VART::ViewerGlutOGL viewer; 
    
    VART::Camera camera(VART::Point4D(400,0,-1),VART::Point4D(0,0,0),VART::Point4D(0,1,0,0));
    camera.SetFarPlaneDistance(700);
    
    VART::Transform wheelRotation;
    std::list<VART::Transform*> transforms;
    
    list<VART::MeshObject*> readObjects;
    VART::MeshObject::ReadFromOBJ(argv[1], &readObjects);

    for (VART::MeshObject* current : readObjects) {
        if (current->GetDescription() == "chair") {
            VART::Transform* transform = new VART::Transform;
            transform->AddChild(*current);
            transforms.push_back(transform);
            scene.AddObject(transform);

            for (unsigned i = 0; i < 9; i++) {
                transform = new VART::Transform;
                transform->AddChild(*dynamic_cast<VART::MeshObject*>(current->Copy()));
                transforms.push_back(transform);
                scene.AddObject(transform);
            }
        } else if (current->GetDescription() == "wheel") {
            wheelRotation.AddChild(*current);
        } else {
            scene.AddObject(current);
        }
    }

    IdleHandler idleHandler;
    idleHandler.chairsTransform = &transforms;
    idleHandler.wheelRotation = &wheelRotation;

    scene.AddObject(&wheelRotation);

    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);
    
    viewer.SetIdleHandler(&idleHandler);

    viewer.SetTitle("V-ART OBJ Viewer");
    viewer.SetScene(scene); 

    scene.DrawLightsOGL(); 
    VART::ViewerGlutOGL::MainLoop(); 
    return 0;
}

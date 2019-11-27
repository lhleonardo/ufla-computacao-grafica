// main.cpp - Test application for JointAction

// This application shows how to make simple animation using the class JointAction.

// Changelog
// Oct 19, 2012 - Bruno de Oliveira Schneider
// - Adapted to new keyboard handler methods.
// Jul 15, 2008 - Bruno Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/transform.h>
#include <vart/joint.h>
#include <vart/jointmover.h>
#include <vart/uniaxialjoint.h>
#include <vart/baseaction.h>
#include <vart/jointaction.h>
#include <vart/light.h>
#include <vart/sphere.h>
#include <vart/callback.h>
#include <vart/meshobject.h>
#include <vart/box.h>
#include <vart/linearinterpolator.h>
#include <vart/contrib/viewerglutogl.h>

#include <iostream>

using namespace std;

class KeyboardHandler : public VART::ViewerGlutOGL::KbHandler
{
    public:
        KeyboardHandler() {
        }
        virtual void OnKeyDown(int key) {
            switch (key)
            {
                case ' ':
                    actionPtr1->Activate();
                    break;
                case '1':
                    selectedDofPtr = dofPtrVec[0];
                    break;
                case '2':
                    selectedDofPtr = dofPtrVec[1];
                    break;
                case '3':
                    selectedDofPtr = dofPtrVec[2];
                    break;
                case ',':
                    selectedDofPtr->Move(-0.02);
                    break;
                case '.':
                    selectedDofPtr->Move(0.02);
                    break;
            }
            viewerPtr->PostRedisplay();
        }
        VART::Dof* dofPtrVec[3];
        VART::Dof* selectedDofPtr;
        VART::BaseAction* actionPtr1;
    private:
};

class MyIHClass : public VART::ViewerGlutOGL::IdleHandler
{
    public:
        MyIHClass(){}
        virtual ~MyIHClass() {}
        virtual void OnIdle() {
            VART::BaseAction::MoveAllActive();
            viewerPtr->PostRedisplay();
        }
    protected:
    private:
};

using VART::Point4D;

// The application itself:
int main(int argc, char* argv[])
{
    VART::ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)

    cout << "This application shows hot to use JointAction.\n"
         << "Keyboard commands:\n"
         << "1) Selects the base joint\n"
         << "2) Selects the middle joint\n"
         << "3) Selects the top joint\n"
         << ",) Moves selected joint towards minimal flexion\n"
         << ".) Moves selected joint towards maximal flexion\n"
         << " ) The [SPACE] key activates the action that moves the robotic arm to its "
         << "'rest position' within four seconds\n"
         << "q) Quits\n\n";
    // create a camera (scene observer)
    VART::Camera camera(Point4D(0,2,-5), Point4D::ORIGIN(), Point4D::Y());
    MyIHClass idleHandler;

    // Build up the scene -- begin =======================================================
    // scene -> base
    VART::Box base;
    base.MakeBox(-1,1,-0.1,0.1,-1,1);
    base.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());
    scene.AddObject(&base);
    
    VART::UniaxialJoint baseJoint;
    VART::Dof* dofPtr1 = baseJoint.AddDof(Point4D::Y(), Point4D::ORIGIN(), -3.141592654, 3.141592654);
    base.AddChild(baseJoint);
    
    // base -> arm1
    VART::Box arm1;
    arm1.MakeBox(-0.1,0.1, 0,0.5, -0.1,0.1);
    arm1.SetMaterial(VART::Material::PLASTIC_GREEN());
    baseJoint.AddChild(arm1);
    
    VART::UniaxialJoint joint12; // joint from arm1 to arm2
    VART::Dof* dofPtr2 = joint12.AddDof(Point4D::Z(), Point4D(0,0.5,0), -1.570796327, 1.570796327);
    dofPtr2->MoveTo(0.4);
    arm1.AddChild(joint12);
    
    // joint12 -> arm2
    VART::Box arm2;
    arm2.MakeBox(-0.1,0.1, 0.5,1, -0.1,0.1);
    arm2.SetMaterial(VART::Material::PLASTIC_GREEN());
    joint12.AddChild(arm2);
    
    VART::UniaxialJoint joint23; // joint from arm2 to arm3
    VART::Dof* dofPtr3 = joint23.AddDof(Point4D::Z(), Point4D(0,1,0), -1.570796327, 1.570796327);
    dofPtr3->MoveTo(0.4);
    arm2.AddChild(joint23);
    
    // joint23 -> arm3
    VART::Box arm3;
    arm3.MakeBox(-0.1,0.1, 1,1.5, -0.1,0.1);
    arm3.SetMaterial(VART::Material::PLASTIC_GREEN());
    joint23.AddChild(arm3);

    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);
    // Build up the scene -- end =========================================================


    // Set up actions -- begin
    VART::JointAction mover;
    VART::LinearInterpolator interpolator;
    VART::JointMover* baseMoverPtr = mover.AddJointMover(&baseJoint, 4, interpolator);
    baseMoverPtr->AddDofMover(VART::Joint::FLEXION, 0, 1, 1);
    VART::JointMover* middleMoverPtr = mover.AddJointMover(&joint12, 2, interpolator);
    middleMoverPtr->AddDofMover(VART::Joint::FLEXION, 0, 1, 1);
    VART::JointMover* topMoverPtr = mover.AddJointMover(&joint23, 2, interpolator);
    topMoverPtr->AddDofMover(VART::Joint::FLEXION, 0, 1, 1);
    // Set up actions -- end


    // Set up handlers, managers ,etc.
    KeyboardHandler kbh;
    kbh.selectedDofPtr = dofPtr1;
    kbh.dofPtrVec[0] = dofPtr1;
    kbh.dofPtrVec[1] = dofPtr2;
    kbh.dofPtrVec[2] = dofPtr3;
    kbh.actionPtr1 = &mover;

    // Set up the viewer
    viewer.SetScene(scene); // attach the scene
    viewer.SetKbHandler(&kbh);
    viewer.SetIdleHandler(&idleHandler); // attach the idle handler to the viewer
    viewer.SetTitle("JointAction Example");

    //mover.Activate();

    // Run application
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}

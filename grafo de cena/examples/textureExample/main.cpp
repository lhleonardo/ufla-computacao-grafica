// main.cpp - VART Texture example

// This application shows how to add a texture to an object. It also loads a OBJ file that
// has texture mapping.

// Changelog
// May 09, 2014 - Bruno de Oliveira Schneider
// - It is now the earth over a table.
// ?
// Mar 05, 2007 - Leonardo Garcia Fischer
// - Application created.

#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>
#include <vart/scene.h>
#include <vart/meshobject.h>
#include <vart/sphere.h>
#include <vart/texture.h>
#include <vart/transform.h>

using namespace VART;
using namespace std;

const char fileName[] = "table/table.obj";

int main(int argc, char* argv[])
{
    VART::ViewerGlutOGL::Init(&argc, argv);
    static VART::ViewerGlutOGL viewer;
    static VART::Scene scene;

    VART::Material material;
    VART::Texture texture;
    VART::Sphere earth;
    VART::Transform sphereTransform;

    std::list<VART::MeshObject*> objData;
    std::list<VART::MeshObject*>::iterator it;
    VART::Transform tableTransform;

    // Load a texture from a image file, apply it to a material, and then, apply the
    // material to a sphere.
    if(texture.LoadFromFile("earth.jpg")) {
        material.SetTexture( texture );
        earth.SetMaterial( material );

        //Other sphere configs.
        earth.SetDescription("earth");
        sphereTransform.MakeScale(9, 9, 9);
        sphereTransform.AddChild( earth );
    } else {
        cout << "Could not open texture file. Check if the image format is supported, "
             << "if it is in the correct path, and if V-Art was compiled with OpenGL "
             << "support and an image reader library." << std::endl;
    }

    // Load a object from a ".obj" file. Note that the object refers to a material
    // library, that refers to two other textures.
    if( VART::MeshObject::ReadFromOBJ(fileName, &objData))
    {
        // Here, we add the object data to a transform, setup the data and the transform.
        for(it = objData.begin(); it != objData.end(); ++it)
        {
            (*it)->autoDelete = true;
            tableTransform.AddChild( **it );
            // std::cout << (*it)->GetDescription() << std::endl;
        }
        tableTransform.MakeTranslation( VART::Point4D(0,0,-21) );
    }
    else
        std::cout << "Could not read '" << fileName << "' for object data." << std::endl;

    //Add the earth and the object to a scene.
    scene.AddObject( &sphereTransform );
    scene.AddObject( &tableTransform );

    //Add a camera to a scene and configure it.
    VART::Camera camera (Point4D(-40,0,-1), Point4D(0,0,-6), Point4D::Z());
    camera.SetDescription( "camera" );
    scene.AddCamera( &camera );

    //Add a light to the scene.
    scene.AddLight( Light::BRIGHT_AMBIENT() );
    scene.DrawLightsOGL();

    //Setup the viewer.
    viewer.SetTitle("V-ART texture example");
    viewer.SetScene(scene);

    //Enable texture in OpenGL
    glEnable( GL_TEXTURE_2D );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );

    //Enter the main loop
    VART::ViewerGlutOGL::MainLoop();
    return 0;
}

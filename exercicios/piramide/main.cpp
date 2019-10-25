#include <vart/scene.h>
#include <vart/light.h>
#include <vart/meshobject.h>
#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    VART::ViewerGlutOGL::Init(&argc, argv); 

    if (argc < 2) {
        cerr << "Fatal error: No filename given.\nUsage: " << argv[0] << " filename\n"
             << "Where 'filename' is a Pyramid mapping.\n";
        return 1;
    }

    static VART::Scene scene; 
    static VART::ViewerGlutOGL viewer; 

    VART::Camera camera(VART::Point4D(0,0,6),VART::Point4D(0,0,0),VART::Point4D(0,1,0,0));
    VART::MeshObject object;

    ifstream arquivo(argv[1]);
    unsigned repeat;

    if (not arquivo) {
        cerr << "File " << argv[1] << " not found or is not valid." << endl;
        return 1;
    }

    // num de vértices
    arquivo >> repeat;

    vector<VART::Point4D> pontos;
    for (unsigned i = 0; i < repeat; i++) {
        double x, y, z;
        arquivo >> x >> y >> z;

        pontos.push_back(VART::Point4D(x, y, z));
    }

    object.SetVertices(pontos);
    cout << "Vértices definidos" << endl;

    // num de faces
    arquivo >> repeat;
    string read;
    for (unsigned i = 0; i < repeat; i++) {
        string face = "";
        do {
            arquivo >> read;
            if (read != "-1")
                face += " " + read;
        } while (read != "-1");

        cout << "Face: " << face << endl;
        object.AddFace(face.c_str());
    }

    object.ComputeVertexNormals();

    object.SetMaterial(VART::Material::PLASTIC_RED());

    scene.AddObject(&object);
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);

    viewer.SetTitle("V-ART OBJ Viewer");
    viewer.SetScene(scene);

    scene.DrawLightsOGL(); 
    VART::ViewerGlutOGL::MainLoop(); 
    return 0;
}

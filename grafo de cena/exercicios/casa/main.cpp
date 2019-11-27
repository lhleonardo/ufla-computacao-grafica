#include <vart/scene.h>
#include <vart/light.h>
#include <vart/meshobject.h>
#include <vart/box.h>
#include <vart/texture.h>
#include <vart/material.h>
#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>

#include <iostream>
#include <fstream>
#include <cmath>

#include <vector>

using namespace std;

VART::MeshObject criaCasa() {
    VART::MeshObject casa;

    return casa;
}

VART::Material getTexture(string file) {
    VART::Texture textura;
    VART::Material material;

    if (textura.LoadFromFile(file)) {
        material.SetTexture(textura);
    } else {
        cout << "Erro ao ler textura" << endl;

    }
    return material;
}

int main(int argc, char* argv[]) {
    VART::ViewerGlutOGL::Init(&argc, argv); 

    static VART::Scene scene; 
    static VART::ViewerGlutOGL viewer; 

    VART::Box base;
    base.MakeBox(0, 8, 0, 7, -14, 0);
    base.SetMaterial(getTexture("parede.jpg"));

    VART::Box porta;
    porta.MakeBox(0, 2.5, 0, 4, 0, 0.05);
    porta.SetMaterial(VART::Material::PLASTIC_BLACK());

    VART::Transform transladaPorta;
    transladaPorta.AddChild(porta);
    transladaPorta.MakeTranslation(2.5, 0, 0);

    VART::MeshObject telhado;
    std::vector<VART::Point4D> vertices;

    VART::Point4D 
        v0(-1, 7.01, -14),
        v1(9, 7.01, -14),
        v2(4, 11, -14),
        v3(-1, 7.01, 0),
        v4(9, 7.01, 0),
        v5(4, 11, 0);

    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);

    telhado.SetVertices(vertices);
    telhado.AddFace("1 2 0");
    telhado.AddFace("2 1 4 5");
    telhado.AddFace("3 5 4");
    telhado.AddFace("3 4 1 0");
    telhado.AddFace("0 2 5 3");


    telhado.ComputeVertexNormals();
    // telhado.SetMaterial(VART::Material::PLASTIC_GREEN());

    telhado.SetMaterial(getTexture("telhado.jpg"));


    scene.AddObject(&base);
    scene.AddObject(&transladaPorta);
    scene.AddObject(&telhado);

    VART::Camera camera(VART::Point4D(-30,5,-4),VART::Point4D(4,5,0),VART::Point4D(0,1,0));
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);

    viewer.SetTitle("V-ART OBJ Viewer");
    viewer.SetScene(scene);

    scene.DrawLightsOGL(); 
    VART::ViewerGlutOGL::MainLoop(); 
    return 0;
}

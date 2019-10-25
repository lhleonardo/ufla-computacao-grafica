/// \file vigilancecamera.cpp
/// \brief Example class for VPAT (implementation)
/// \version $Revision: 1.1 $

// ChangeLog
// Jul 07, 2008 - Bruno de Oliveira Schneider
// - Added clVigilanceCamera::Copy() because it was added at SceneNode.
// Jun 01, 2006 - Bruno de Oliveira Schneider
// - General renaming to account for project rename (VPAT->V-ART).
// Mar 17, 2006 - Bruno de Oliveira Schneider
// - Uses new method VPCylinder::SetPartsVisibility.
// Mar 21, 2005 - Bruno de Oliveira Schneider
// - Added ComputeBoundingBox.

#include "vigilancecamera.h"

#include <iostream>
using namespace std;

clVigilanceCamera::clVigilanceCamera()
{
    VART::Material lGreyPlastic(VART::Color(204,204,220));
    VART::Material dGreyPlastic(VART::Color(127,127,127));
    base.SetHeight(1);
    base.SetRadius(1.5);
    base.SetDescription("base");
    base.SetMaterial(dGreyPlastic);
    base.SetPartsVisibility(VART::Cylinder::ALL);
    globeTrans.MakeTranslation(0,0,1.5001);
    globeTrans.SetDescription("globeTrans");
    base.AddChild(globeTrans);
    flexion.Set(VART::Point4D::Z(), VART::Point4D::ORIGIN(), -3.14159265358979, 3.14159265358979);
    flexion.SetDescription("flexion");
    aduction.Set(VART::Point4D::X(), VART::Point4D::ORIGIN(), 0, 1.5707963267949);
    aduction.SetDescription("aduction");
    joint.AddDof(&flexion);
    joint.AddDof(&aduction);
    joint.SetDescription("joint");
    globeTrans.AddChild(joint);
    globe.SetRadius(1.5);
    globe.SetMaterial(lGreyPlastic);
    joint.AddChild(globe);
    lensTrans.MakeTranslation(0,0,1.4);
    joint.AddChild(lensTrans);
    lens.SetHeight(0.2);
    lens.SetRadius(0.4);
    lens.SetPartsVisibility(VART::Cylinder::NO_BOTTOM);
    lens.SetDescription("lens");
    lens.SetMaterial(lGreyPlastic);
    lensTrans.AddChild(lens);
    lensTrans.SetDescription("lensTrans");
}

clVigilanceCamera* clVigilanceCamera::Copy()
{
    clVigilanceCamera* resultPtr = new clVigilanceCamera;
    resultPtr->flexion = flexion;
    resultPtr->aduction = aduction;
    return resultPtr;
}

void clVigilanceCamera::Flex(float variance)
{
    flexion.Move(variance);
}
void clVigilanceCamera::Adduct(float variance)
{
    aduction.Move(variance);
}

bool clVigilanceCamera::DrawInstanceOGL() const
{
    base.DrawOGL();
    return true;
}

void clVigilanceCamera::ComputeBoundingBox() {
    //FixMe: Computing the bbox according to the current joint state would be better.
    bBox.SetBoundingBox(-1.5, -1.5, 0, 1.5, 1.5, 3.1);
}

/// \file vigilancecamera.h
/// \brief Example class for VPAT (headers)
/// \version $Revision: 1.1 $

// ChangeLog is at the implementation file

#ifndef VIGILANCECAMERA_H
#define VIGILANCECAMERA_H

#include <vart/graphicobj.h>
#include <vart/cylinder.h>
#include <vart/sphere.h>
#include <vart/biaxialjoint.h>

class clVigilanceCamera : public VART::GraphicObj
{
    public:
        clVigilanceCamera();
        void Flex(float variance);
        void Adduct(float variance);
        /// Computes the bounding box.
        virtual void ComputeBoundingBox();
        virtual clVigilanceCamera* Copy();
    private:
    // PRIVATE METHODS
        virtual bool DrawInstanceOGL() const;
    // PRIVATE ATTRIBUTES
        VART::Cylinder base;
        VART::Sphere globe;
        VART::Transform globeTrans;
        VART::Cylinder lens;
        VART::Transform lensTrans;

        // First DOF is along the Z axis, passing by the center of the globe, ranging
        // from -PI to PI. Z axis is relative to the vigilance camera, and will probably
        // be the Y axis on world coordinates. Therefore, the vigilance camera has full
        // 360 degrees of freedom to look around
        VART::Dof flexion;
        // Second DOF is along the X axis, passing by the center of the globe, ranging from
        // 0 to PI/2. The local X axis will probably be horizontal in world coordinates
        // therefore the vigilance camera may turn directly to the floor (0 degrees), or
        // aim at the horizon (90 degrees).
        VART::Dof aduction;
        VART::BiaxialJoint joint;
};

#endif

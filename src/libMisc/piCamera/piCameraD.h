#pragma once

#include "../../libMath/piVecTypes.h"

namespace piLibs {

class piCameraD
{
public:
    piCameraD();
    ~piCameraD();

    void Set(const vec3d & pos, const vec3d & dir, const double roll);
    void SetPos(const vec3d & pos);

    void   GlobalMove(const vec3d &);
    void   LocalMove(const vec3d &);
    void   RotateXY(const double x, const double y);

    const mat4x4d & GetMatrix( void ) const;
    const mat4x4d & GetMatrixInverse( void ) const;
    void SetMatrix(const mat4x4d & mat );

    vec3d GetPos(void) const;
    vec3d GetDir(void) const;


public:
    mat4x4d mMatrix;
    mat4x4d mMatrixInv;
};



} // namespace piLibs
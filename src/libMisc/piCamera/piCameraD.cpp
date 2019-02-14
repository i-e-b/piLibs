#include <math.h>
#include "../../libMath/piVecTypes.h"
#include "piCameraD.h"

namespace piLibs {

piCameraD::piCameraD()
{
    mMatrix    = mat4x4d::identity();
    mMatrixInv = mat4x4d::identity();
}

piCameraD::~piCameraD()
{
}

void piCameraD::Set(const vec3d & pos, const vec3d & dir, const double roll)
{
    mMatrix    = setLookat( pos, pos + dir, vec3d(std::sin(roll), std::cos(roll), std::sin(roll) ));
    mMatrixInv = invert(mMatrix);
}

void piCameraD::SetPos(const vec3d & pos)
{
    mMatrix[ 3] = -(mMatrix[0] * pos[0] + mMatrix[1] * pos[1] + mMatrix[ 2] * pos[2]);
    mMatrix[ 7] = -(mMatrix[4] * pos[0] + mMatrix[5] * pos[1] + mMatrix[ 6] * pos[2]);
    mMatrix[11] = -(mMatrix[8] * pos[0] + mMatrix[9] * pos[1] + mMatrix[10] * pos[2]);
}

vec3d piCameraD::GetPos( void ) const
{
    return (mMatrixInv * vec4d(0.0, 0.0, 0.0, 1.0)).xyz();
}

vec3d piCameraD::GetDir(void) const
{
    return normalize((mMatrixInv * vec4d(0.0, 0.0, -1.0, 0.0)).xyz());
}

const mat4x4d & piCameraD::GetMatrix(void) const
{
    return mMatrix;
}

const mat4x4d & piCameraD::GetMatrixInverse(void) const
{
    return mMatrixInv;
}

void piCameraD::SetMatrix(const mat4x4d & mat)
{   
    mMatrix = mat;
    mMatrixInv = invert(mMatrix);
}

void piCameraD::LocalMove( const vec3d & pos )
{
    mMatrix[ 3] -= pos.x;
    mMatrix[ 7] -= pos.y;
    mMatrix[11] -= pos.z;
    mMatrixInv = invert(mMatrix);
}

void piCameraD::GlobalMove(const vec3d & pos)
{
    mMatrix[ 3] -= (mMatrix[0] * pos[0] + mMatrix[1] * pos[1] + mMatrix[ 2] * pos[2]);
    mMatrix[ 7] -= (mMatrix[4] * pos[0] + mMatrix[5] * pos[1] + mMatrix[ 6] * pos[2]);
    mMatrix[11] -= (mMatrix[8] * pos[0] + mMatrix[9] * pos[1] + mMatrix[10] * pos[2]);
    mMatrixInv = invert(mMatrix);
}

void piCameraD::RotateXY(const double x, const double y )
{
    mMatrix = setRotationY(x) * mMatrix;
    mMatrixInv = invert(mMatrix);
}

}
#pragma once

#include "../piMesh.h"

namespace piLibs {

bool piMesh_GeneratePlane( piMesh *me, const piMeshVertexFormat *vertexFormat, int gx, int gy );
bool piMesh_GenerateCube( piMesh *me, const piMeshVertexFormat *vertexFormat );
bool piMesh_GenerateCubePlanes(piMesh *me, const piMeshVertexFormat *vertexFormat);
bool piMesh_GenerateTorus(piMesh *me, const piMeshVertexFormat *vertexFormat, int gy, int gx, float ry, float rx);
bool piMesh_PatchedSphere(piMesh *me, const piMeshVertexFormat *vertexFormat, int n);
bool piMesh_GenerateRevolution(piMesh *me, const piMeshVertexFormat *vertexFormat, const vec2 *cv, int numCVs, int numRevs);

} // namespace piLibs
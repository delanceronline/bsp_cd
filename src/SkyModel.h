// SkyModel.h: interface for the SkyModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYMODEL_H__BD73A48A_8EA3_4FA2_A0C3_3EB2D94DD751__INCLUDED_)
#define AFX_SKYMODEL_H__BD73A48A_8EA3_4FA2_A0C3_3EB2D94DD751__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mesh.h"
#include "Material.h"
#include "MeshVBInfo.h"
#include "Matrix.h"
#include "UV.h"
#include "Vector3D.h"
#include <stdio.h>
#include <string.h>

class SkyModel  
{
public:
	bool LinkJoints(void);
	bool LoadASCIIFile(char *filename);
	SkyModel();
	Mesh *pSolidMesh, *pAlphaMesh;
	Material *pMaterial;
	MeshVBInfo *pMeshVBInfo;
	int numMeshes, numSolidMeshes, numAlphaMeshes, numMaterials, numVertices, numTriangles;
	FILE *m_file;
	float BoundingRadius, MaxX, MinX, MaxY, MinY, MaxZ, MinZ, ViewOffset;
	float Cx, Cy, Cz;
	char TextureFile[256];
	float VAngle;
	int *pSolidMesh_nVB, *pAlphaMesh_nVB;

	virtual ~SkyModel();

};

#endif // !defined(AFX_SKYMODEL_H__BD73A48A_8EA3_4FA2_A0C3_3EB2D94DD751__INCLUDED_)

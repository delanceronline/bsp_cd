// Mesh.h: interface for the Mesh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESH_H__A0BB53ED_EE42_420A_8C37_C23347E6C265__INCLUDED_)
#define AFX_MESH_H__A0BB53ED_EE42_420A_8C37_C23347E6C265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Normal.h"
#include "Vertice.h"
#include "Index.h"
#include "UV.h"
#include "Triangle.h"

class Mesh  
{
public:
	Mesh();
	virtual ~Mesh();

	int nMaterial, numVertices, numNormals, numTriangles, numUVs, nVB;
	int IsTransparent;
	char Name[256];
	Vertice *pVertice;
	Normal *pNormal;
	Index *pIndex;
	Triangle *pTriangle;
	UV *pUV;

};

#endif // !defined(AFX_MESH_H__A0BB53ED_EE42_420A_8C37_C23347E6C265__INCLUDED_)

// Mesh.cpp: implementation of the Mesh class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mesh.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mesh::Mesh()
{
	strcpy(Name, "");
	numNormals = 0;
	numTriangles = 0;
	numVertices = 0;
	numUVs = 0;
	nMaterial = 0;
	nVB = 0;

	pUV = NULL;
	pNormal = NULL;
	pIndex = NULL;
	pVertice = NULL;
	pTriangle = NULL;
}

Mesh::~Mesh()
{
	if(pUV != NULL)
		delete[] pUV;

	if(pNormal != NULL)
		delete[] pNormal;

	if(pIndex != NULL)
		delete[] pIndex;

	if(pVertice != NULL)
		delete[] pVertice;

	if(pTriangle != NULL)
		delete[] pTriangle;
}

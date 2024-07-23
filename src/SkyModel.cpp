// SkyModel.cpp: implementation of the SkyModel class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SkyModel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SkyModel::SkyModel()
{
	pSolidMesh = NULL;
	pAlphaMesh = NULL;
	pMaterial = NULL;
	pSolidMesh_nVB = NULL;
	pAlphaMesh_nVB = NULL;

	numMeshes = 0;
	numSolidMeshes = 0;
	numAlphaMeshes = 0;
	numVertices = 0;
	numTriangles = 0;
	BoundingRadius = 0.0f;
	Cx = 0.0f; Cy = 0.0f; Cz = 0.0f;
	VAngle = 3.1415f * 0.25f;
}

SkyModel::~SkyModel()
{
	if(pSolidMesh != NULL)
	{
		delete[] pSolidMesh;
		pSolidMesh = NULL;
	}

	if(pAlphaMesh != NULL)
	{
		delete[] pAlphaMesh;
		pAlphaMesh = NULL;
	}

	if(pMaterial != NULL)
	{
		if(numMaterials != 0)
			delete[] pMaterial;

		pMaterial = NULL;
	}

	if(pSolidMesh_nVB != NULL)
	{
		delete[] pSolidMesh_nVB;
		pSolidMesh_nVB = NULL;
	}

	if(pAlphaMesh_nVB != NULL)
	{
		delete[] pAlphaMesh_nVB;
		pAlphaMesh_nVB = NULL;
	}
}

bool SkyModel::LoadASCIIFile(char *filename)
{
	char szLine[512];
	int i, j;
	//int num_shapes, num_vertices, num_normals, num_triangles, num_materials, num_joints;
	
	m_file = fopen (filename, "rt");

	if (!m_file)
		return false;

	// Read version.
	fgets(szLine, 512, m_file);
	if(strcmp(szLine, "Sky 3D Version 2.0\n") != 0)
		return false;

	if(!fgets(szLine, 512, m_file))
		return false;
	if(sscanf(szLine, "NumMeshes: %d\n", &numMeshes) != 1)
		return false;

	if(!fgets(szLine, 512, m_file))
		return false;
	if(sscanf(szLine, "NumOpaqueMeshes: %d\n", &numSolidMeshes) != 1)
		return false;

	if(!fgets(szLine, 512, m_file))
		return false;
	if(sscanf(szLine, "NumTransparentMeshes: %d\n", &numAlphaMeshes) != 1)
		return false;

	if(numSolidMeshes != 0)
		pSolidMesh = new Mesh[numSolidMeshes];
	if(numAlphaMeshes != 0)
		pAlphaMesh = new Mesh[numAlphaMeshes];

	// Read all non-transparent meshes first.
	for(i = 0; i < numSolidMeshes; i++)
	{
		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "MeshName: \"%[^\"]\"\n", pSolidMesh[i].Name) != 1)
			return false;

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "nMaterial: %d\n", &pSolidMesh[i].nMaterial) != 1)
			return false;

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "IsTransparent: %d\n", &pSolidMesh[i].IsTransparent) != 1)
			return false;

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "NumVertices: %d\n", &pSolidMesh[i].numVertices) != 1)
			return false;

		if(pSolidMesh[i].numVertices != 0)
			pSolidMesh[i].pVertice = new Vertice[pSolidMesh[i].numVertices];

		for(j = 0; j < pSolidMesh[i].numVertices; j++)
		{
			if(!fgets(szLine, 512, m_file))
				return false;
			if(sscanf(szLine, "%f %f %f\n", &pSolidMesh[i].pVertice[j].x, &pSolidMesh[i].pVertice[j].y, &pSolidMesh[i].pVertice[j].z) != 3)
				return false;
		}

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "NumUVs: %d\n", &pSolidMesh[i].numUVs) != 1)
			return false;

		if(pSolidMesh->numUVs != 0)
			pSolidMesh[i].pUV = new UV[pSolidMesh[i].numUVs];

		for(j = 0; j < pSolidMesh[i].numUVs; j++)
		{
			if(!fgets(szLine, 512, m_file))
				return false;
			if(sscanf(szLine, "%f %f\n", &pSolidMesh[i].pUV[j].u, &pSolidMesh[i].pUV[j].v) != 2)
				return false;
		}

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "NumTriangles: %d\n", &pSolidMesh[i].numTriangles) != 1)
			return false;

		if(pSolidMesh[i].numTriangles != 0)
		{
			pSolidMesh[i].pNormal = new Normal[pSolidMesh[i].numTriangles];
			pSolidMesh[i].pIndex = new Index[pSolidMesh[i].numTriangles];
			pSolidMesh[i].pTriangle = new Triangle[pSolidMesh[i].numTriangles];
		}

		for(j = 0; j < pSolidMesh[i].numTriangles; j++)
		{
			if(!fgets(szLine, 512, m_file))
				return false;
			if(sscanf(szLine, "%d %d %d %d %d %d %f %f %f %d\n", 
				&pSolidMesh[i].pIndex[j].v[0], &pSolidMesh[i].pIndex[j].uv[0], &pSolidMesh[i].pIndex[j].v[1], &pSolidMesh[i].pIndex[j].uv[1], &pSolidMesh[i].pIndex[j].v[2], &pSolidMesh[i].pIndex[j].uv[2],
				&pSolidMesh[i].pNormal[j].x, &pSolidMesh[i].pNormal[j].y, &pSolidMesh[i].pNormal[j].z, &pSolidMesh[i].pTriangle[j].SmoothingGroup) != 10)
				return false;
		}
	}

	// Read all transparent meshes.
	for(i = 0; i < numAlphaMeshes; i++)
	{
		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "MeshName: \"%[^\"]\"\n", pAlphaMesh[i].Name) != 1)
			return false;

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "nMaterial: %d\n", &pAlphaMesh[i].nMaterial) != 1)
			return false;

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "IsTransparent: %d\n", &pAlphaMesh[i].IsTransparent) != 1)
			return false;

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "NumVertices: %d\n", &pAlphaMesh[i].numVertices) != 1)
			return false;

		if(pAlphaMesh[i].numVertices != 0)
			pAlphaMesh[i].pVertice = new Vertice[pAlphaMesh[i].numVertices];

		for(j = 0; j < pAlphaMesh[i].numVertices; j++)
		{
			if(!fgets(szLine, 512, m_file))
				return false;
			if(sscanf(szLine, "%f %f %f\n", &pAlphaMesh[i].pVertice[j].x, &pAlphaMesh[i].pVertice[j].y, &pAlphaMesh[i].pVertice[j].z) != 3)
				return false;
		}

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "NumUVs: %d\n", &pAlphaMesh[i].numUVs) != 1)
			return false;

		if(pAlphaMesh[i].numUVs != 0)
			pAlphaMesh[i].pUV = new UV[pAlphaMesh[i].numUVs];

		for(j = 0; j < pAlphaMesh[i].numUVs; j++)
		{
			if(!fgets(szLine, 512, m_file))
				return false;
			if(sscanf(szLine, "%f %f\n", &pAlphaMesh[i].pUV[j].u, &pAlphaMesh[i].pUV[j].v) != 2)
				return false;
		}

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "NumTriangles: %d\n", &pAlphaMesh[i].numTriangles) != 1)
			return false;

		if(pAlphaMesh[i].numTriangles != 0)
		{
			pAlphaMesh[i].pNormal = new Normal[pAlphaMesh[i].numTriangles];
			pAlphaMesh[i].pIndex = new Index[pAlphaMesh[i].numTriangles];
			pAlphaMesh[i].pTriangle = new Triangle[pAlphaMesh[i].numTriangles];
		}

		for(j = 0; j < pAlphaMesh[i].numTriangles; j++)
		{
			if(!fgets(szLine, 512, m_file))
				return false;
			if(sscanf(szLine, "%d %d %d %d %d %d %f %f %f %d\n", 
				&pAlphaMesh[i].pIndex[j].v[0], &pAlphaMesh[i].pIndex[j].uv[0], &pAlphaMesh[i].pIndex[j].v[1], &pAlphaMesh[i].pIndex[j].uv[1], &pAlphaMesh[i].pIndex[j].v[2], &pAlphaMesh[i].pIndex[j].uv[2],
				&pAlphaMesh[i].pNormal[j].x, &pAlphaMesh[i].pNormal[j].y, &pAlphaMesh[i].pNormal[j].z, &pAlphaMesh[i].pTriangle[j].SmoothingGroup) != 10)
				return false;
		}
	}

	// Read all materials.
	if(!fgets(szLine, 512, m_file))
		return false;
	if(sscanf(szLine, "NumMaterials: %d\n", &numMaterials) != 1)
		return false;

	if(numMaterials != 0)
		pMaterial = new Material[numMaterials];

	for(i = 0; i < numMaterials; i++)
	{
		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "MaterialName: \"%[^\"]\"\n", pMaterial[i].Name) != 1)
			return false;

		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "%f %f %f %f\n", &pMaterial[i].Ambient[0], &pMaterial[i].Ambient[1], &pMaterial[i].Ambient[2], &pMaterial[i].Ambient[3]) != 4)
			return false;
		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "%f %f %f %f\n", &pMaterial[i].Diffuse[0], &pMaterial[i].Diffuse[1], &pMaterial[i].Diffuse[2], &pMaterial[i].Diffuse[3]) != 4)
			return false;
		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "%f %f %f %f\n", &pMaterial[i].Specular[0], &pMaterial[i].Specular[1], &pMaterial[i].Specular[2], &pMaterial[i].Specular[3]) != 4)
			return false;
		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "%f %f %f %f\n", &pMaterial[i].Emissive[0], &pMaterial[i].Emissive[1], &pMaterial[i].Emissive[2], &pMaterial[i].Emissive[3]) != 4)
			return false;
		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "%f\n", &pMaterial[i].Shininess) != 1)
			return false;
		if(!fgets(szLine, 512, m_file))
			return false;
		if(sscanf(szLine, "%f\n", &pMaterial[i].Transparency) != 1)
			return false;
		
		if(!fgets(szLine, 512, m_file))
			return false;
		sscanf(szLine, "DiffuseTexture: \"%[^\"]\" %f\n", pMaterial[i].DiffuseTexture, &pMaterial[i].DT_Amount);
	
		if(strcmp(pMaterial[i].DiffuseTexture, "") == 0)
			pMaterial[i].hasDiffuseTexture = false;
		else
			pMaterial[i].hasDiffuseTexture = true;

		if(!fgets(szLine, 512, m_file))
			return false;
		sscanf(szLine, "AlphaTexture: \"%[^\"]\" %f\n", pMaterial[i].AlphaTexture, &pMaterial[i].AT_Amount);

		if(strcmp(pMaterial[i].AlphaTexture, "") == 0)
			pMaterial[i].hasAlphaTexture = false;
		else
			pMaterial[i].hasAlphaTexture = true;
	}

	fclose(m_file);

	for(i = 0; i < numSolidMeshes; i++)
	{
		for(j = 0; j < pSolidMesh[i].numTriangles; j++)
		{
			pSolidMesh[i].pTriangle[j].v[0] = pSolidMesh[i].pVertice[pSolidMesh[i].pIndex[j].v[0]];
			pSolidMesh[i].pTriangle[j].v[1] = pSolidMesh[i].pVertice[pSolidMesh[i].pIndex[j].v[1]];
			pSolidMesh[i].pTriangle[j].v[2] = pSolidMesh[i].pVertice[pSolidMesh[i].pIndex[j].v[2]];

			pSolidMesh[i].pTriangle[j].v[0].u = pSolidMesh[i].pUV[pSolidMesh[i].pIndex[j].uv[0]].u;
			pSolidMesh[i].pTriangle[j].v[0].v = pSolidMesh[i].pUV[pSolidMesh[i].pIndex[j].uv[0]].v;
			pSolidMesh[i].pTriangle[j].v[1].u = pSolidMesh[i].pUV[pSolidMesh[i].pIndex[j].uv[1]].u;
			pSolidMesh[i].pTriangle[j].v[1].v = pSolidMesh[i].pUV[pSolidMesh[i].pIndex[j].uv[1]].v;
			pSolidMesh[i].pTriangle[j].v[2].u = pSolidMesh[i].pUV[pSolidMesh[i].pIndex[j].uv[2]].u;
			pSolidMesh[i].pTriangle[j].v[2].v = pSolidMesh[i].pUV[pSolidMesh[i].pIndex[j].uv[2]].v;

			pSolidMesh[i].pTriangle[j].n = pSolidMesh[i].pNormal[j];
		}
		numTriangles += pSolidMesh[i].numTriangles;
	}

	for(i = 0; i < numAlphaMeshes; i++)
	{
		for(j = 0; j < pAlphaMesh[i].numTriangles; j++)
		{
			pAlphaMesh[i].pTriangle[j].v[0] = pAlphaMesh[i].pVertice[pAlphaMesh[i].pIndex[j].v[0]];
			pAlphaMesh[i].pTriangle[j].v[1] = pAlphaMesh[i].pVertice[pAlphaMesh[i].pIndex[j].v[1]];
			pAlphaMesh[i].pTriangle[j].v[2] = pAlphaMesh[i].pVertice[pAlphaMesh[i].pIndex[j].v[2]];

			pAlphaMesh[i].pTriangle[j].v[0].u = pAlphaMesh[i].pUV[pAlphaMesh[i].pIndex[j].uv[0]].u;
			pAlphaMesh[i].pTriangle[j].v[0].v = pAlphaMesh[i].pUV[pAlphaMesh[i].pIndex[j].uv[0]].v;
			pAlphaMesh[i].pTriangle[j].v[1].u = pAlphaMesh[i].pUV[pAlphaMesh[i].pIndex[j].uv[1]].u;
			pAlphaMesh[i].pTriangle[j].v[1].v = pAlphaMesh[i].pUV[pAlphaMesh[i].pIndex[j].uv[1]].v;
			pAlphaMesh[i].pTriangle[j].v[2].u = pAlphaMesh[i].pUV[pAlphaMesh[i].pIndex[j].uv[2]].u;
			pAlphaMesh[i].pTriangle[j].v[2].v = pAlphaMesh[i].pUV[pAlphaMesh[i].pIndex[j].uv[2]].v;

			pAlphaMesh[i].pTriangle[j].n = pAlphaMesh[i].pNormal[j];
		}
		numTriangles += pAlphaMesh[i].numTriangles;
	}

	/*
	pMeshVBInfo = new MeshVBInfo[numMeshes];
			
	m_MaxX = 0.0f; m_MinX = 0.0f; m_MaxY = 0.0f; m_MinY = 0.0f; m_MaxZ = 0.0f; m_MinZ = 0.0f;

	float var1, var2, var3, var;

	int count = 0;
	//Find bounding sphere radius.			 
	for(i = 0; i < m_num_meshes; i++)
	{
		meshvbinfo[i].StartIndex = count;
		meshvbinfo[i].num_Triangles = mesh[i].num_triangles;

		for(j = 0; j < mesh[i].num_triangles; j++)
		{
			for(k = 0; k < 3; k++)
			{						
				if(mesh[i].vertice[mesh[i].index[j].v[k]].x > m_MaxX)
					m_MaxX = mesh[i].vertice[mesh[i].index[j].v[k]].x;
				if(mesh[i].vertice[mesh[i].index[j].v[k]].x < m_MinX)
					m_MinX = mesh[i].vertice[mesh[i].index[j].v[k]].x;

				if(mesh[i].vertice[mesh[i].index[j].v[k]].y > m_MaxY)
					m_MaxY = mesh[i].vertice[mesh[i].index[j].v[k]].y;
				if(mesh[i].vertice[mesh[i].index[j].v[k]].y < m_MinY)
					m_MinY = mesh[i].vertice[mesh[i].index[j].v[k]].y;

				if(mesh[i].vertice[mesh[i].index[j].v[k]].z > m_MaxZ)
					m_MaxZ = mesh[i].vertice[mesh[i].index[j].v[k]].z;
				if(mesh[i].vertice[mesh[i].index[j].v[k]].z < m_MinZ)
					m_MinZ = mesh[i].vertice[mesh[i].index[j].v[k]].z;

				count++;
			}
		}
	}

	Cx = (m_MaxX + m_MinX) * 0.5f;
	Cy = (m_MaxY + m_MinY) * 0.5f;
	Cz = (m_MaxZ + m_MinZ) * 0.5f;

	for(i = 0; i < m_num_meshes; i++)
	{
		for(j = 0; j < mesh[i].num_triangles; j++)
		{
			for(k = 0; k < 3; k++)
			{
				//var1 = (mesh[i].vertice[mesh[i].index[j].v[k]].x - Cx) * (mesh[i].vertice[mesh[i].index[j].v[k]].x - Cx);
				//var2 = (mesh[i].vertice[mesh[i].index[j].v[k]].y - Cy) * (mesh[i].vertice[mesh[i].index[j].v[k]].y - Cy);
				//var3 = (mesh[i].vertice[mesh[i].index[j].v[k]].z - Cz) * (mesh[i].vertice[mesh[i].index[j].v[k]].z - Cz);

				var1 = (mesh[i].vertice[mesh[i].index[j].v[k]].x) * (mesh[i].vertice[mesh[i].index[j].v[k]].x);
				var2 = (mesh[i].vertice[mesh[i].index[j].v[k]].y) * (mesh[i].vertice[mesh[i].index[j].v[k]].y);
				var3 = (mesh[i].vertice[mesh[i].index[j].v[k]].z) * (mesh[i].vertice[mesh[i].index[j].v[k]].z);

				var = powf(var1 + var2 + var3, 0.5f);

				if(var > m_BoundingRadius)
					m_BoundingRadius = var;
			}
		}
	}
	m_ViewOffset = m_BoundingRadius / (float)tan(VAngle * 0.5f);
*/

	return true;
}

bool SkyModel::LinkJoints()
{

	
	return true;
}

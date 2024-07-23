// CollisionDetection.cpp: implementation of the CollisionDetection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CollisionDetection.h"
#include "MyMaths.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CollisionDetection::CollisionDetection()
{

}

CollisionDetection::~CollisionDetection()
{

}

bool CollisionDetection::IsCollided(OBB *pOBB, BSP_Node *pNode)
{
	//If this is leaf node, directly check all triangles in this leaf.
	if(pNode->IsLeaf)
	{
		int i;
		Triangle tri;

		tri.v[0] = pNode->v[0];
		tri.v[1] = pNode->v[1];
		tri.v[2] = pNode->v[2];
		tri.n.x = pNode->normal.x;
		tri.n.y = pNode->normal.y;
		tri.n.z = pNode->normal.z;

		//Check for node's triangle.
		if(CheckCollision(&tri, pOBB))
			return true;

		//Check for threshold triangle(s).
		for(i = 0; i < pNode->numTriangles; i++)
		{
			if(CheckCollision(&pNode->tri[i], pOBB))
				return true;
		}

		//Check for coplanar triangle(s).
		for(i = 0; i < pNode->numConTri; i++)
		{
			if(CheckCollision(&pNode->pCoplanarTriangle[i], pOBB))
				return true;
		}

		return false;
	}

	//This is not leaf node, so tranverse BSP tree.
	//Check for 8 vertices of OBB.
	float w[8], var;

	var = pNode->v[0].x * pNode->normal.x + pNode->v[0].y * pNode->normal.y + pNode->v[0].z * pNode->normal.z;
	w[0] = (pOBB->v[0] * pNode->normal) - var;
	w[1] = (pOBB->v[1] * pNode->normal) - var;
	w[2] = (pOBB->v[2] * pNode->normal) - var;
	w[3] = (pOBB->v[3] * pNode->normal) - var;
	w[4] = (pOBB->v[4] * pNode->normal) - var;
	w[5] = (pOBB->v[5] * pNode->normal) - var;
	w[6] = (pOBB->v[6] * pNode->normal) - var;
	w[7] = (pOBB->v[7] * pNode->normal) - var;

	//If OBB is located at positive side, check all nodes in positive side.
	if(w[0] >= 0.0f && w[1] >= 0.0f && w[2] >= 0.0f && w[3] >= 0.0f && w[4] >= 0.0f && w[5] >= 0.0f && w[6] >= 0.0f && w[7] >= 0.0f)
	{
		if(pNode->Pos_Child != NULL)
		{
			if(IsCollided(pOBB, pNode->Pos_Child))
				return true;
		}
		else
			return false;
	}
	else
	{
		//If OBB is located at negative side, check all nodes in negative side.
		if(w[0] < 0.0f && w[1] < 0.0f && w[2] < 0.0f && w[3] < 0.0f && w[4] < 0.0f && w[5] < 0.0f && w[6] < 0.0f && w[7] < 0.0f)
		{
			if(pNode->Neg_Child != NULL)
			{
				if(IsCollided(pOBB, pNode->Neg_Child))
					return true;
			}
			else
				return false;
		}
		else
		{

			//OBB is intersecting with node's plane, so check for collision between node's triangle and OBB.
			/////////////////////////////////////////////////////////
			int i;
			Triangle tri;

			tri.v[0] = pNode->v[0];
			tri.v[1] = pNode->v[1];
			tri.v[2] = pNode->v[2];
			tri.n.x = pNode->normal.x;
			tri.n.y = pNode->normal.y;
			tri.n.z = pNode->normal.z;

			//Check for node's triangle.
			if(CheckCollision(&tri, pOBB))
				return true;

			//Check for threshold triangle(s).
			for(i = 0; i < pNode->numTriangles; i++)
			{
				if(CheckCollision(&pNode->tri[i], pOBB))
					return true;
			}

			//Check for coplanar triangle(s).
			for(i = 0; i < pNode->numConTri; i++)
			{
				if(CheckCollision(&pNode->pCoplanarTriangle[i], pOBB))
					return true;
			}
			////////////////////////////////////////////////////////

			//No collision between OBB and node's triangle, so check for all nodes in positive side.
			if(pNode->Pos_Child != NULL)
			{
				if(IsCollided(pOBB, pNode->Pos_Child))
					return true;
			}

			//Still no collision, thus check for all nodes in negative side.
			if(pNode->Neg_Child != NULL)
			{
				if(IsCollided(pOBB, pNode->Neg_Child))
					return true;
			}
		}
	}

	return false;
}

bool CollisionDetection::CheckCollision(Triangle *pTri, OBB *pOBB)
{
	int index;
	float pValTri[3], pValOBB[8];
	float MaxOBB, MinOBB, MaxTri, MinTri;

	//Projection axis: normal 1 of OBB
	CalculateProject(pTri, pOBB->Nx, pValTri);
	MaxProjVal(3, pValTri, &index, &MaxTri);
	MinProjVal(3, pValTri, &index, &MinTri);

	CalculateProjection(pOBB, pOBB->Nx, pValOBB);
	MaxProjVal(8, pValOBB, &index, &MaxOBB);
	MinProjVal(8, pValOBB, &index, &MinOBB);

	if(MaxTri < MinOBB || MinTri > MaxOBB)
		return false;

	//Projection axis: normal 2 of OBB
	CalculateProject(pTri, pOBB->Ny, pValTri);
	MaxProjVal(3, pValTri, &index, &MaxTri);
	MinProjVal(3, pValTri, &index, &MinTri);

	CalculateProjection(pOBB, pOBB->Ny, pValOBB);
	MaxProjVal(8, pValOBB, &index, &MaxOBB);
	MinProjVal(8, pValOBB, &index, &MinOBB);

	if(MaxTri < MinOBB || MinTri > MaxOBB)
		return false;

	//Projection axis: normal 3 of OBB
	CalculateProject(pTri, pOBB->Nz, pValTri);
	MaxProjVal(3, pValTri, &index, &MaxTri);
	MinProjVal(3, pValTri, &index, &MinTri);

	CalculateProjection(pOBB, pOBB->Nz, pValOBB);
	MaxProjVal(8, pValOBB, &index, &MaxOBB);
	MinProjVal(8, pValOBB, &index, &MinOBB);

	if(MaxTri < MinOBB || MinTri > MaxOBB)
		return false;

	//Projection axis: triangle's normal of OBB
	CalculateProject(pTri, pTri->n, pValTri);
	MaxProjVal(3, pValTri, &index, &MaxTri);
	MinProjVal(3, pValTri, &index, &MinTri);

	CalculateProjection(pOBB, pTri->n, pValOBB);
	MaxProjVal(8, pValOBB, &index, &MaxOBB);
	MinProjVal(8, pValOBB, &index, &MinOBB);

	if(MaxTri < MinOBB || MinTri > MaxOBB)
		return false;

	//Projection axis: cross product of triangle's normal and normal 1 of OBB
	CalculateProject(pTri, CrossProduct((*pTri).n, pOBB->Nx), pValTri);
	MaxProjVal(3, pValTri, &index, &MaxTri);
	MinProjVal(3, pValTri, &index, &MinTri);

	CalculateProjection(pOBB, CrossProduct((*pTri).n, pOBB->Nx), pValOBB);
	MaxProjVal(8, pValOBB, &index, &MaxOBB);
	MinProjVal(8, pValOBB, &index, &MinOBB);

	if(MaxTri < MinOBB || MinTri > MaxOBB)
		return false;

	//Projection axis: cross product of triangle's normal and normal 2 of OBB
	CalculateProject(pTri, CrossProduct((*pTri).n, pOBB->Ny), pValTri);
	MaxProjVal(3, pValTri, &index, &MaxTri);
	MinProjVal(3, pValTri, &index, &MinTri);

	CalculateProjection(pOBB, CrossProduct((*pTri).n, pOBB->Ny), pValOBB);
	MaxProjVal(8, pValOBB, &index, &MaxOBB);
	MinProjVal(8, pValOBB, &index, &MinOBB);

	if(MaxTri < MinOBB || MinTri > MaxOBB)
		return false;

	//Projection axis: cross product of triangle's normal and normal 3 of OBB
	CalculateProject(pTri, CrossProduct((*pTri).n, pOBB->Nz), pValTri);
	MaxProjVal(3, pValTri, &index, &MaxTri);
	MinProjVal(3, pValTri, &index, &MinTri);

	CalculateProjection(pOBB, CrossProduct((*pTri).n, pOBB->Nz), pValOBB);
	MaxProjVal(8, pValOBB, &index, &MaxOBB);
	MinProjVal(8, pValOBB, &index, &MinOBB);

	if(MaxTri < MinOBB || MinTri > MaxOBB)
		return false;

	return true;
}

void CollisionDetection::CalculateProjection(OBB *pOBB, Vector3D normal, float *pVal)
{
	pVal[0] = normal * pOBB->v[0];
	pVal[1] = normal * pOBB->v[1];
	pVal[2] = normal * pOBB->v[2];
	pVal[3] = normal * pOBB->v[3];
	pVal[4] = normal * pOBB->v[4];
	pVal[5] = normal * pOBB->v[5];
	pVal[6] = normal * pOBB->v[6];
	pVal[7] = normal * pOBB->v[7];
}

void CollisionDetection::CalculateProject(Triangle *pTri, Vector3D normal, float *pVal)
{
	Vector3D Vec;

	Vec = Vector3D(pTri->v[0].x, pTri->v[0].y, pTri->v[0].z);
	pVal[0] = normal * Vec;

	Vec = Vector3D(pTri->v[1].x, pTri->v[1].y, pTri->v[1].z);
	pVal[1] = normal * Vec;

	Vec = Vector3D(pTri->v[2].x, pTri->v[2].y, pTri->v[2].z);
	pVal[2] = normal * Vec;
}

void CollisionDetection::MinProjVal(int n, float *pVal, int *min_nVal, float *min_proj_val)
{
	*min_nVal = 0;
	*min_proj_val = pVal[0];
	
	for(int i = 1; i < n; i++)
	{
		if(pVal[i] < *min_proj_val)
		{
			*min_proj_val = pVal[i];
			*min_nVal = i;
		}
	}
}

void CollisionDetection::MaxProjVal(int n, float *pVal, int *max_nVal, float *max_proj_val)
{
	*max_nVal = 0;
	*max_proj_val = pVal[0];
	
	for(int i = 1; i < n; i++)
	{
		if(pVal[i] > *max_proj_val)
		{
			*max_proj_val = pVal[i];
			*max_nVal = i;
		}
	}
}

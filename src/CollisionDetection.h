// CollisionDetection.h: interface for the CollisionDetection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLISIONDETECTION_H__D5C1EEBB_2B3E_4BDA_93E0_50A9152EB990__INCLUDED_)
#define AFX_COLLISIONDETECTION_H__D5C1EEBB_2B3E_4BDA_93E0_50A9152EB990__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OBB.h"
#include "BSP_Node.h"

class CollisionDetection  
{
public:
	void MaxProjVal(int n, float *pVal, int *max_nVal, float *max_proj_val);
	void MinProjVal(int n, float *pVal, int *min_nVal, float *min_proj_val);
	void CalculateProject(Triangle *pTri, Vector3D normal, float *pVal);
	void CalculateProjection(OBB *pOBB, Vector3D normal, float *pVal);
	bool CheckCollision(Triangle *pTri, OBB *pOBB);
	bool IsCollided(OBB *pOBB, BSP_Node *pNode);
	CollisionDetection();
	virtual ~CollisionDetection();
};

#endif // !defined(AFX_COLLISIONDETECTION_H__D5C1EEBB_2B3E_4BDA_93E0_50A9152EB990__INCLUDED_)

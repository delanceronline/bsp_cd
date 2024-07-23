// ViewFrustum.cpp: implementation of the ViewFrustum class.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include "stdafx.h"
#include "ViewFrustum.h"
#include "Vector3D.h"
#include "MyMaths.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ViewFrustum::ViewFrustum()
{
	//tan_half_fov = tanf(fov * 0.5f);
	//UpdateNormals();
}

ViewFrustum::~ViewFrustum()
{

}

void ViewFrustum::Update(Vector3D vp, float *Rot_mat)
{
	Vector3D var;

	ViewPoint = vp;

	MultiMatrix3x1(Rot_mat, Vector3D(-AspectRatio * height, -height, zf), &var);
	LowerLeft = ViewPoint + var;

	MultiMatrix3x1(Rot_mat, Vector3D(AspectRatio * height, -height, zf), &var);
	LowerRight = ViewPoint + var;

	MultiMatrix3x1(Rot_mat, Vector3D(-AspectRatio * height, height, zf), &var);
	UpperLeft = ViewPoint + var;

	MultiMatrix3x1(Rot_mat, Vector3D(AspectRatio * height, height, zf), &var);
	UpperRight = ViewPoint + var;

	//Rotate looking direction vector by rotational matrix.
	MultiMatrix3x1(Rot_mat, Vector3D(0.0f, 0.0f, 1.0f), &LookDir);
	LookPoint = ViewPoint + LookDir;

	UpdateNormals();
}

void ViewFrustum::UpdateNormals()
{
	FP_Normal = ToUnit(CrossProduct(UpperLeft - UpperRight, LowerRight - UpperRight));
	LP_Normal = ToUnit(CrossProduct(LowerLeft - ViewPoint, UpperLeft - ViewPoint));
	RP_Normal = ToUnit(CrossProduct(UpperRight - ViewPoint, LowerRight - ViewPoint));
	UP_Normal = ToUnit(CrossProduct(UpperLeft - ViewPoint, UpperRight - ViewPoint));
	BP_Normal = ToUnit(CrossProduct(LowerRight - ViewPoint, LowerLeft - ViewPoint));
}

void ViewFrustum::SetFOV(float _fov)
{
	fov = _fov;
	tan_half_fov = tanf(fov * 0.5f);
	height = zf * tan_half_fov;
}

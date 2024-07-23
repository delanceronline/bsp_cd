// SceneObject.h: interface for the SceneObject class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_SCENEOBJECT_H__47660504_B627_4E9C_A887_5D59999A1CF9__INCLUDED_)
#define AFX_SCENEOBJECT_H__47660504_B627_4E9C_A887_5D59999A1CF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "CollisionList.h"
#include "Vector3D.h"
#include "OBB.h"
#include <windows.h>

class SceneObject  
{
public:
	void RestoreStates(void);
	void BackupStates(void);
	void SimpleInitialize(float mass);
	void UpdateBoundBox(void);
	void InitializeKinematics(Vector3D Extp_in, Vector3D Extn_in);
	void AdvanceKinematics(float delta_t);
	//CollisionList CDList;
	SceneObject();
	virtual ~SceneObject();

	Vector3D lin_r, ang_r, lin_v, ang_v, lin_a, ang_a;
	Vector3D lin_mom, ang_mom;
	Vector3D lin_imp, ang_imp;
	Vector3D cm_pos;
	float Rot_mat[9];
	float I_inv_mat[9];
	float I_body_inv_mat[9];
	OBB obb;

	Vector3D lin_r_copy, ang_r_copy, lin_v_copy, ang_v_copy, lin_a_copy, ang_a_copy;
	Vector3D lin_mom_copy, ang_mom_copy;
	Vector3D lin_imp_copy, ang_imp_copy;
	Vector3D cm_pos_copy;
	float Rot_mat_copy[9];
	float I_inv_mat_copy[9];
	float I_body_inv_mat_copy[9];
	OBB obb_copy;
	
	int nVB, numTriangles;
	float one_over_box_mass;
	float BoundingRadius;
	SceneObject *m_previous, *m_next;
	Vector3D lin_mom_local;
	float attacking_power, life_value;
	bool IsAttacked;
};

#endif // !defined(AFX_SCENEOBJECT_H__47660504_B627_4E9C_A887_5D59999A1CF9__INCLUDED_)

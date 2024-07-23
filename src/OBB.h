// OBB.h: interface for the OBB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBB_H__F4DBD61D_0D28_47A7_8398_73E043CB1DD8__INCLUDED_)
#define AFX_OBB_H__F4DBD61D_0D28_47A7_8398_73E043CB1DD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector3D.h"

class OBB  
{
public:
	OBB();
	virtual ~OBB();
	void Initialize(void);
	OBB& operator =(const OBB& obb_in);
	Vector3D Ax, Ay, Az, v[8], Nx, Ny, Nz, Extp, Extn, r;		//Ax, Ay and Az must be unit vertors.
};

#endif // !defined(AFX_OBB_H__F4DBD61D_0D28_47A7_8398_73E043CB1DD8__INCLUDED_)

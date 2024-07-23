// OBB.cpp: implementation of the OBB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OBB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OBB::OBB()
{
	Ax = Vector3D(1.0f, 0.0f, 0.0f);
	Ay = Vector3D(0.0f, 1.0f, 0.0f);
	Az = Vector3D(0.0f, 0.0f, 1.0f);
}

OBB::~OBB()
{

}

void OBB::Initialize()
{
	r = (Extp + Extn) * 0.5f;
}

OBB& OBB::operator =(const OBB& obb_in)
{
	if(&obb_in == this)
		return *this;

	this->Ax = obb_in.Ax;
	this->Ay = obb_in.Ay;
	this->Az = obb_in.Az;
	this->Extp = obb_in.Extp;
	this->Extn = obb_in.Extn;
	this->Nx = obb_in.Nx;
	this->Ny = obb_in.Ny;
	this->Nz = obb_in.Nz;
	this->r = obb_in.r;

	for(int i = 0; i < 8; i++)
		this->v[i] = obb_in.v[i];
	
	return *this;
}
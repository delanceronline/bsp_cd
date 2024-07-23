// Triangle.h: interface for the Triangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLE_H__AECD8B60_A45F_4286_B404_011C68C8E116__INCLUDED_)
#define AFX_TRIANGLE_H__AECD8B60_A45F_4286_B404_011C68C8E116__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vertice.h"
#include "Normal.h"

class Triangle  
{
public:
	Triangle();
	virtual ~Triangle();

	Vertice v[3];
	Normal n;
	int SmoothingGroup;
};

#endif // !defined(AFX_TRIANGLE_H__AECD8B60_A45F_4286_B404_011C68C8E116__INCLUDED_)

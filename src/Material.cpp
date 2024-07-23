// Material.cpp: implementation of the Material class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Material.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Material::Material()
{
	g_pTexture = NULL;
	g_pAlphaTexture = NULL;

	strcpy(DiffuseTexture, "");
	strcpy(AlphaTexture, "");
}

Material::~Material()
{
    if( g_pTexture != NULL )
		g_pTexture->Release();

    if( g_pAlphaTexture != NULL )
		g_pAlphaTexture->Release();
}

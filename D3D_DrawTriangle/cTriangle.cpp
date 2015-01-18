#include "stdafx.h"
#include "cTriangle.h"


cTriangle::cTriangle()
	:m_pVB(nullptr)
	/*:m_vUp(0, 0, 1)
	, m_vLeft(-1, 0, 0)
	, m_vRight(0, 0, 1)*/
{
	
}

cTriangle::~cTriangle()
{
	SAFE_RELEASE(m_pVB);
}

void cTriangle::Setup()
{
	ST_RHWC_VERTEX v;
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR4(320.0f, 50.0f, 0.5f, 1.0f);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR4(520.0f, 400.0f, 0.5f, 1.0f);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR4(120.0f, 400.0f, 0.5f, 1.0f);
	m_vecVertex.push_back(v);
	HRESULT hr;

	int nPrimitiveCount = sizeof(ST_RHWC_VERTEX)*m_vecVertex.size();
	hr = g_pD3DDevice->CreateVertexBuffer(
		nPrimitiveCount, 0, ST_RHWC_VERTEX::FVF, D3DPOOL_MANAGED, &m_pVB, 0);
	
	ST_RHWC_VERTEX* pV;
	hr = m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	{
		memcpy(pV, &m_vecVertex[0], nPrimitiveCount);
	}
	hr = m_pVB->Unlock();

}

void cTriangle::Update()
{

}

void cTriangle::Render()
{
	g_pD3DDevice->SetFVF(ST_RHWC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, nullptr);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_RHWC_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_vecVertex.size() / 3);

	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_RHWC_VERTEX));
}

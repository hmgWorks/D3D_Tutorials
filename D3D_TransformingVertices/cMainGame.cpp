#include "StdAfx.h"
#include "cMainGame.h"


cMainGame::cMainGame(void)
	:m_pVB(NULL)
	, m_vEye(0.0f, 0.0f, 10.0f)
	, m_vAt(0.0f, 0.0f, 0.0f)
	, m_vUp(0.0f, 1.0f, 0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cMainGame::~cMainGame(void)
{
	if (m_pVB)
		m_pVB->Release();

	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();	
}

void cMainGame::Setup()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);


	CUSTOMVERTEX v;
	v = { 2.5f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0) };
	m_vecVertex.push_back(v);
	v = { 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0) };
	m_vecVertex.push_back(v);
	v = { -2.5f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255) };
	m_vecVertex.push_back(v);

	int vertex_size = m_vecVertex.size()*sizeof(CUSTOMVERTEX);

	g_pD3DDevice->CreateVertexBuffer(
		vertex_size, 0, CUSTOMVERTEX::FVF, D3DPOOL_MANAGED, &m_pVB, 0);

	CUSTOMVERTEX* vp;
	m_pVB->Lock(0, 0, (LPVOID*)&vp, 0);
	{
		memcpy(vp, &m_vecVertex[0], vertex_size);
	}
	m_pVB->Unlock();		
}

void cMainGame::Update()
{
	static float fPosZ = 10.0f;
	if (g_pInputManager->GetKeyDownOnce('A'))
	{
		fPosZ += 10;
	}
	if (g_pInputManager->GetKeyDownOnce('D'))
	{
		fPosZ -= 10;
	}
	m_vEye = { 0.0f, 0.0f, fPosZ };
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(
		NULL, NULL,	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,	D3DCOLOR_XRGB(33, 40, 48),1.0f, 0);

	g_pD3DDevice->BeginScene();
	// 그림을 그린다.
	g_pD3DDevice->SetFVF(CUSTOMVERTEX::FVF);	
	D3DXMATRIXA16 matRY;
	static float index = 0.0f;
	//index -= 0.05f;
	D3DXMatrixRotationY(&matRY, index);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matRY);

	D3DXMATRIXA16 matView;
	/*m_vEye = { 0.0f, 0.0f, 10.0f };
	m_vAt = { 0.0f, 0.0f, 0.0f };
	m_vUp = { 0.0f, 1.0f, 0.0f };*/
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matTran;
	//인자 순서: 메트릭스 포인터, 시각, 화면비율, 가까운거리, 먼거리
	D3DXMatrixPerspectiveFovLH(&matTran, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 100.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matTran);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_vecVertex.size() / 3);

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void  cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_pInputManager)
	{
		g_pInputManager->WndProc(hWnd, message, wParam, lParam);
	}
}
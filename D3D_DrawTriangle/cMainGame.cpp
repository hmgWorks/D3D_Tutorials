#include "StdAfx.h"
#include "cMainGame.h"
#include "cTriangle.h"

cMainGame::cMainGame(void)
	:m_spTriangle(nullptr)
{
}

cMainGame::~cMainGame(void)
{	
	//SAFE_DELETE(m_spTriangle);
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();	
}

void cMainGame::Setup()
{
	m_spTriangle = std::make_unique<cTriangle>();
	m_spTriangle->Setup();
	//m_spTriangle = new cTriangle;
	//m_spTriangle->Setup();
}

void cMainGame::Update()
{
	
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(
		NULL, NULL,	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,	D3DCOLOR_XRGB(0, 40, 100),1.0f, 0);

	g_pD3DDevice->BeginScene();
	// 그림을 그린다.
	m_spTriangle->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
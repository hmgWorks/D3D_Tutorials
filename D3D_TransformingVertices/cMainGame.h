#pragma once

class cMainGame
{
private:
	struct CUSTOMVERTEX
	{
		float x, y, z;
		DWORD color;
		enum{ FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	};

	std::vector<CUSTOMVERTEX>	m_vecVertex;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	D3DXMATRIXA16				m_matWorld;

	D3DXVECTOR3				m_vEye, m_vAt, m_vUp;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();

	void  WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


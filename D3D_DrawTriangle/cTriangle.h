#pragma once
class cTriangle
{
public:
	cTriangle();
	~cTriangle();

private:
	std::vector<ST_RHWC_VERTEX> m_vecVertex;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	D3DXVECTOR4	m_vUp;
	D3DXVECTOR4	m_vLeft;
	D3DXVECTOR4	m_vRight;
public:
	void Setup();
	void Update();
	void Render();
};


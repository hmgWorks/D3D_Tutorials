#pragma once
class cTriangle;

class cMainGame
{
private:
	std::unique_ptr<cTriangle> m_spTriangle;
	//cTriangle*	m_spTriangle;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
};


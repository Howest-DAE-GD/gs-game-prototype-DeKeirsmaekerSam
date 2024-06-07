#include "pch.h"
#include "Game.h"
#include "utils.h"
Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pPlayer = new Player{ Rectf{ 400, 1500, 40, 80 }, Point2f{ 0,0 }, Point2f{ GetViewPort().width, GetViewPort().height } };
	m_pForeground = new Foreground();
	m_Boxes.push_back(new Box(Rectf{ 800, 1500, 150, 150 }, Point2f{ 0, 0 }, Color4f{ 1.f,1.f,1.f,1.f }));
	m_Boxes.push_back(new Box(Rectf{ 1000, 1500, 170, 170 }, Point2f{ 0, 0 }, Color4f{ 1.f,1.f,1.f,1.f }));
	m_Boxes.push_back(new Box(Rectf{ 1200, 1500, 160, 160 }, Point2f{ 0, 0 }, Color4f{ 1.f,1.f,1.f,1.f }));
	m_Boxes.push_back(new Box(Rectf{ 1400, 1500, 160, 160 }, Point2f{ 0, 0 }, Color4f{ 1.f,1.f,1.f,1.f }));
	m_Boxes.push_back(new Box(Rectf{ 1200, 300, 180, 180 }, Point2f{ 0, 0 }, Color4f{ 1.f,1.f,1.f,1.f }));
	m_Boxes.push_back(new Box(Rectf{ 1400, 300, 160, 160 }, Point2f{ 0, 0 }, Color4f{ 1.f,1.f,1.f,1.f }));
	m_Boxes.push_back(new Box(Rectf{ 1000, 600, 110, 110 }, Point2f{ 0, 0 }, Color4f{ 1.f,1.f,1.f,1.f }));
	m_ColorBoxes.push_back(new ColorBox(Rectf{ 2500, 1500, 80, 80 }, Point2f{ 0, 0 }, Color4f{ 1.f,0.f,0.f,1.f }));
	m_ColorBoxes.push_back(new ColorBox(Rectf{ 2700, 1500, 80, 80 }, Point2f{ 0, 0 }, Color4f{ 0.f,1.f,0.f,1.f }));
	m_ColorBoxes.push_back(new ColorBox(Rectf{ 2900, 1500, 80, 80 }, Point2f{ 0, 0 }, Color4f{ 0.f,0.f,1.f,1.f }));
	m_Wall1 = new Wall{ Rectf{3345, 1060, 335, 100}, GetRandColorWall1() };
	m_Wall2 = new Wall{ Rectf{1950, 170, 100, 220}, GetRandColorWall2() };
	m_ColorSwitches.push_back(new ColorSwitch{ Rectf{ 2500, 350, 80, 80 }, Color4f{ 1.f, 0.f, 0.f, 1.f} });
	m_ColorSwitches.push_back(new ColorSwitch{ Rectf{ 2700, 350, 80, 80 }, Color4f{ 0.f, 1.f, 0.f, 1.f} });
	m_ColorSwitches.push_back(new ColorSwitch{ Rectf{ 2900, 350, 80, 80 }, Color4f{ 0.f, 0.f, 1.f, 1.f} });
}

void Game::Cleanup( )
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pForeground;
	m_pForeground = nullptr;
	for(int i{}; i < m_Boxes.size(); ++i)
	{
		delete m_Boxes[i];
		m_Boxes[i] = nullptr;
	}
	delete m_Wall1;
	m_Wall1 = nullptr;
	delete m_Wall2;
	m_Wall2 = nullptr;
	for (int i{}; i < m_ColorBoxes.size(); ++i)
	{
		delete m_ColorBoxes[i];
		m_ColorBoxes[i] = nullptr;
	}
	for (int i{}; i < m_ColorSwitches.size(); ++i)
	{
		delete m_ColorSwitches[i];
		m_ColorSwitches[i] = nullptr;
	}
	m_Boxes.clear();
	m_ColorBoxes.clear();
	m_ColorSwitches.clear();
}

void Game::Update(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	for (int i{}; i < m_Boxes.size(); ++i)
	{
		m_pPlayer->Update(m_pForeground->GetVertices(), elapsedSec, m_Boxes[i]->GetRect());
	}
	
	//WASD USERS

	if (pStates[SDL_SCANCODE_D] && !pStates[SDL_SCANCODE_LSHIFT] && !pStates[SDL_SCANCODE_RIGHT]) m_pPlayer->MovementWalk(elapsedSec, true);
	//if (pStates[SDL_SCANCODE_D] && pStates[SDL_SCANCODE_LSHIFT] && !pStates[SDL_SCANCODE_RIGHT]) m_pPlayer->MovementRun(elapsedSec, true);
	if (pStates[SDL_SCANCODE_SPACE] && !m_pPlayer->GetIsJumping())
	{
		m_pPlayer->SetIsJumping(true);
		m_Height = m_pPlayer->GetPosition().y;
	}
	if (m_pPlayer->GetIsJumping()) m_pPlayer->Jump(elapsedSec, m_Height);
	if (pStates[SDL_SCANCODE_A] && !pStates[SDL_SCANCODE_LSHIFT] && !pStates[SDL_SCANCODE_LEFT]) m_pPlayer->MovementWalk(elapsedSec, false);
	//if (pStates[SDL_SCANCODE_A] && pStates[SDL_SCANCODE_LSHIFT] && !pStates[SDL_SCANCODE_LEFT]) m_pPlayer->MovementRun(elapsedSec, false);
	if (pStates[SDL_SCANCODE_E] && !pStates[SDL_SCANCODE_UP])
	{
		if(!m_pPlayer->GetIsHolding() && !m_pPlayer->GetIsHoldingColor())
		{
			for (int i{}; i < m_Boxes.size(); ++i)
			{
				if (m_pPlayer->PickUpBox(m_Boxes[i]->GetRect()))
				{
					m_Boxes[i]->PickUp();
					m_PickedUpIdx = i;
				}
			}

			for (int i{}; i < m_ColorBoxes.size(); ++i)
			{
				if (m_pPlayer->PickUpColorBox(m_ColorBoxes[i]->GetRect()))
				{
					m_ColorBoxes[i]->PickUp();
					m_PickedUpIdx2 = i;
				}
			}
		}
	}
	if (pStates[SDL_SCANCODE_Q] && !pStates[SDL_SCANCODE_DOWN])
	{
		m_pPlayer->DropBox();
		m_Boxes[m_PickedUpIdx]->Drop();
		m_pPlayer->DropColorBox();
		m_ColorBoxes[m_PickedUpIdx2]->Drop();
	}

	//ARROW USERS

	if (pStates[SDL_SCANCODE_RIGHT] && !pStates[SDL_SCANCODE_LSHIFT] && !pStates[SDL_SCANCODE_D]) m_pPlayer->MovementWalk(elapsedSec, true);
	//if (pStates[SDL_SCANCODE_RIGHT] && pStates[SDL_SCANCODE_LSHIFT] && !pStates[SDL_SCANCODE_D]) m_pPlayer->MovementRun(elapsedSec, true);
	if (pStates[SDL_SCANCODE_LEFT] && !pStates[SDL_SCANCODE_LSHIFT] && !pStates[SDL_SCANCODE_A]) m_pPlayer->MovementWalk(elapsedSec, false);
	//if (pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_LSHIFT] && !pStates[SDL_SCANCODE_A]) m_pPlayer->MovementRun(elapsedSec, false);
	if (pStates[SDL_SCANCODE_UP] && !pStates[SDL_SCANCODE_E])
	{
		if (!m_pPlayer->GetIsHolding() && !m_pPlayer->GetIsHoldingColor())
		{
			for (int i{}; i < m_Boxes.size(); ++i)
			{
				if (m_pPlayer->PickUpBox(m_Boxes[i]->GetRect()))
				{
					m_Boxes[i]->PickUp();
					m_PickedUpIdx = i;
				}
			}

			for (int i{}; i < m_ColorBoxes.size(); ++i)
			{
				if (m_pPlayer->PickUpColorBox(m_ColorBoxes[i]->GetRect()))
				{
					m_ColorBoxes[i]->PickUp();
					m_PickedUpIdx2 = i;
				}
			}
		}
	}
	if (pStates[SDL_SCANCODE_DOWN] && !pStates[SDL_SCANCODE_Q])
	{
		m_pPlayer->DropBox();
		m_Boxes[m_PickedUpIdx]->Drop();
		m_pPlayer->DropColorBox();
		m_ColorBoxes[m_PickedUpIdx2]->Drop();
	}

	if (pStates[SDL_SCANCODE_R])
	{
		Cleanup();
		Initialize();
	}

	if(m_pPlayer->GetRect().left < 0)
	{
		m_pPlayer->SetPosition(Point2f{ 2000, 2800 });
	}

	for (int i{}; i < m_Boxes.size(); ++i)
	{
		if (!m_Boxes[i]->GetIsHolding())
		{
			m_Boxes[i]->UpdateCollisions(m_pForeground->GetVertices(), elapsedSec);
			//if (!m_Boxes[i]->GetCollision()) m_Boxes[i]->MoveBox(m_pPlayer->GetRect(), elapsedSec, m_pPlayer->GetVelocityX());
			for (int j{}; j < m_Boxes.size(); ++j)
			{
				if (j != i && !m_pPlayer->GetIsHolding())
				{
					if (m_Boxes[i]->FuseBox(m_Boxes[j]->GetRect()))
					{
						m_Boxes[i]->BigBox();
						m_Boxes[j]->SetPosition(Point2f{ -200,-200 });
					}
					else m_Boxes[i]->UpdateYCollision(m_Boxes[j]->GetRect());
				}
			}
		}
	}
	if (m_pPlayer->GetIsHolding())
	{
		m_pPlayer->PickedUpBox(m_Boxes[m_PickedUpIdx]->GetRect());
	}

	for (int i{}; i < m_ColorBoxes.size(); ++i)
	{
		if (!m_ColorBoxes[i]->GetIsHolding())
		{
			m_ColorBoxes[i]->UpdateCollisions(m_pForeground->GetVertices(), elapsedSec);
			//if (!m_ColorBoxes[i]->GetCollision()) m_ColorBoxes[i]->MoveBox(m_pPlayer->GetRect(), elapsedSec, m_pPlayer->GetVelocityX());
			for (int j{}; j < m_ColorBoxes.size(); ++j)
			{
				if (j != i && !m_pPlayer->GetIsHoldingColor())
				{
					if (m_ColorBoxes[i]->FuseBox(m_ColorBoxes[j]->GetRect()))
					{
						m_ColorBoxes[i]->BigBox(m_ColorBoxes[j]->GetColor());
						m_ColorBoxes[j]->SetPosition(Point2f{ -200,-200 });
					}
					else m_ColorBoxes[i]->UpdateYCollision(m_ColorBoxes[j]->GetRect());
				}
			}
		}
	}
	if (m_pPlayer->GetIsHoldingColor())
	{
		m_pPlayer->PickedUpColorBox(m_ColorBoxes[m_PickedUpIdx2]->GetRect());
	}

	m_pPlayer->Update(m_pForeground->GetVertices(), elapsedSec, m_Wall1->GetRect());

	for (int i{}; i < m_ColorBoxes.size(); ++i)
	{
		if (m_Wall1->CheckColor(m_ColorBoxes[i]->GetColor(), m_ColorBoxes[i]->GetRect()))
		{
			m_Wall1->SetPosition(Point2f{ -200,-200 });
		}
	}

	m_pPlayer->UpdateCollisionWall(m_Wall2->GetRect(), elapsedSec);
	if(m_Wall2->CheckColor(m_pPlayer->GetColor(), m_pPlayer->GetRect()))
	{
		m_Wall2->SetPosition(Point2f{ -200,-200 });
	}

	for (int i{}; i < m_ColorSwitches.size(); ++i)
	{
		if (m_ColorSwitches[i]->CheckCollision(m_pPlayer->GetRect())) m_pPlayer->SwitchColor(m_ColorSwitches[i]->GetColor());
	}
}

void Game::Draw( ) const
{
	ClearBackground();

	glPushMatrix();

	m_pForeground->FollowPlayerX(m_pPlayer->GetPosition());
	m_pForeground->Draw();
	for (int i{}; i < m_Boxes.size(); ++i) 
	{
		m_Boxes[i]->Draw();
	}
	for (int i{}; i < m_ColorBoxes.size(); ++i)
	{
		m_ColorBoxes[i]->Draw();
	}
	for (int i{}; i < m_ColorSwitches.size(); ++i)
	{
		m_ColorSwitches[i]->Draw();
	}
	m_pPlayer->Draw();
	m_Wall1->Draw();
	m_Wall2->Draw();

	text1.Draw(Point2f{ 400, 1500 });
	text2.Draw(Point2f{ 320, 1450 });
	text3.Draw(Point2f{ 300, 1400 });
	text4.Draw(Point2f{ 380, 1350 });
	text5.Draw(Point2f{ 380, 1300 });
	text6.Draw(Point2f{ 1200, 1600 });
	text7.Draw(Point2f{ 2200, 1300 });
	text8.Draw(Point2f{ 3200, 1500 });
	text9.Draw(Point2f{ 3200, 300 });
	text10.Draw(Point2f{ 800, 500 });
	text11.Draw(Point2f{ 1800, 2800 });
	text12.Draw(Point2f{ 2000, 2650 });
	text13.Draw(Point2f{ 1200, 1550 });

	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

Color4f Game::GetRandColorWall1()
{
	int randNum{ rand() % 4 };
	Color4f randColor{};
	switch (randNum)
	{
	case 0:
		randColor = Color4f{ 0.f, 1.f, 1.f, 1.f };
		break;
	case 1:
		randColor = Color4f{ 1.f, 0.f, 1.f, 1.f };
		break;
	case 2:
		randColor = Color4f{ 1.f, 1.f, 0.f, 1.f };
		break;
	case 3:
		randColor = Color4f{ 1.f, 1.f, 1.f, 1.f };
		break;
	}
	return randColor;
}

Color4f Game::GetRandColorWall2()
{
	int randNum{ rand() % 3 };
	Color4f randColor{};
	switch (randNum)
	{
	case 0:
		randColor = Color4f{ 0.f, 0.f, 1.f, 1.f };
		break;
	case 1:
		randColor = Color4f{ 0.f, 1.f, 0.f, 1.f };
		break;
	case 2:
		randColor = Color4f{ 1.f, 0.f, 0.f, 1.f };
		break;
	}
	return randColor;
}

#pragma once
#include "BaseGame.h"
#include "Player.h"
#include "Foreground.h"
#include "Box.h"
#include "Wall.h"
#include "ColorBox.h"
#include "ColorSwitch.h"
#include <string>

class Player;
class Foreground;
class Box;
class Wall;
class ColorBox;
class ColorSwitch;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	// DATA
	Player* m_pPlayer;
	Foreground* m_pForeground;
	std::vector<Box*> m_Boxes;
	std::vector<ColorBox*> m_ColorBoxes;
	std::vector<ColorSwitch*> m_ColorSwitches;
	Wall* m_Wall1;
	Wall* m_Wall2;
	float m_Height{ 0.f };
	int m_PickedUpIdx{};
	int m_PickedUpIdx2{};

	Texture text1{ "Hello Welcome to FUSION", "KingsmanDemo-1GVgg.ttf", 20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text2{ "You can walk with A and D for LEFT or RIGHT" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text3{ "or you can walk with arrow LEFT and arrow RIGHT" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text4{ "To pick up boxes use E or arrow UP" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text5{ "To drop boxes use Q or arrow DOWN" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text6{ "Only boxes of the same value can be FUSED" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text7{ "Try fusing colors" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text8{ "If you messed up click R and start all the way over" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text9{ "Try fusing yourself with a color" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text10{ "U can jump while you are falling" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };
	Texture text11{ "Congrats you did it!" ,"KingsmanDemo-1GVgg.ttf",120, Color4f{1.f,1.f,1.f,1.f} };
	Texture text12{ "Click R to replay" ,"KingsmanDemo-1GVgg.ttf",80, Color4f{1.f,1.f,1.f,1.f} };
	Texture text13{ "Click SPACE to jump" ,"KingsmanDemo-1GVgg.ttf",20, Color4f{0.f,0.f,0.f,1.f} };

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	Color4f GetRandColorWall1();
	Color4f GetRandColorWall2();
};
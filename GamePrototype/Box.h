#pragma once
#include "utils.h"
#include "Texture.h"
class Box
{
public:
	Box(Rectf rect, Point2f pos, Color4f color);
	void Draw() const;
	void UpdateCollisions(std::vector<std::vector<Point2f>> vertices, float elapsedSec);
	void MoveBox(Rectf playerRect, float elapsedSec, float playerSpeed);
	bool FuseBox(Rectf boxRect);
	void BigBox();
	Rectf& GetRect();
	bool GetCollision();
	void PickUp();
	void Drop();
	bool GetIsHolding();
	void UpdateYCollision(const Rectf& boxRect);
	void SetPosition(Point2f value);
	void SetRectWH(Point2f wh);
private:
	
	Rectf m_Rect;
	Point2f m_Position;
	Color4f m_Color;
	Vector2f m_Velocity;

	bool m_Collision;
	bool m_IsHolding;
	utils::HitInfo m_LeftHit;
	utils::HitInfo m_RightHit;
	utils::HitInfo m_LeftBottomHit;
	utils::HitInfo m_RightBottomHit;

	Texture m_Text;
};


#pragma once
#include "utils.h"

class ColorBox
{
public:
	ColorBox(Rectf rect, Point2f pos, Color4f color);
	void Draw() const;
	void UpdateCollisions(std::vector<std::vector<Point2f>> vertices, float elapsedSec);
	void MoveBox(Rectf playerRect, float elapsedSec, float playerSpeed);
	bool FuseBox(Rectf boxRect);
	void BigBox(Color4f color);
	Rectf& GetRect();
	bool GetCollision();
	void PickUp();
	void Drop();
	bool GetIsHolding();
	void UpdateYCollision(const Rectf& boxRect);
	Color4f GetColor();
	void SetPosition(Point2f value);
	void SetColor(Color4f color);
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
};
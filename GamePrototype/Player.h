#pragma once
#include "utils.h"
class Player
{
public:
	Player(Rectf rect, Point2f velocity, Point2f viewport);
	void Draw() const;
	void Update(std::vector<std::vector<Point2f>> vertices, float elapsedSec, Rectf boxRect);
	void UpdateCollissions(std::vector<std::vector<Point2f>> vertices, float elapsedSec, Rectf boxRect);
	void UpdateCollisionWall(Rectf wallRect, float elapsedSec);
	void MovementWalk(float elapsedSeconds, bool isLookingR);
	void MovementRun(float elapsedSeconds, bool isLookingR);
	void Jump(float elapsedSeconds, float heightStanding);
	bool GetIsJumping();
	void SetIsJumping(bool value = false);
	Point2f GetPosition();
	Rectf GetRect();
	float GetVelocityX();
	bool PickUpBox(Rectf boxRect);
	void PickedUpBox(Rectf& boxRect);
	void DropBox();
	bool PickUpColorBox(Rectf boxRect);
	void PickedUpColorBox(Rectf& boxRect);
	void DropColorBox();
	bool GetIsHolding() const;
	bool GetIsHoldingColor();
	void SwitchColor(Color4f color);
	Color4f GetColor();
	void SetPosition(Point2f pos);
private:
	Rectf m_Rect;
	Vector2f m_Velocity;
	Vector2f m_MaxWalkVelocity;
	Vector2f m_MaxRunVelocity;
	Point2f m_Viewport;
	Color4f m_Color;
	bool m_IsJumping;
	float m_Jump{ 0 };
	bool m_IsLookingR;
	bool m_HitJump;
	float m_HeightStanding;
	bool m_HoldingBox;
	bool m_HoldingColorBox;
	utils::HitInfo m_LeftHit;
	utils::HitInfo m_RightHit;
	utils::HitInfo m_LeftBottomHit;
	utils::HitInfo m_RightBottomHit;
	utils::HitInfo m_LeftTopHit;
	utils::HitInfo m_RightTopHit;
};


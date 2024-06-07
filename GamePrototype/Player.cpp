#include "pch.h"
#include "Player.h"
#include "utils.h"

Player::Player(Rectf rect, Point2f velocity, Point2f viewport)
	: m_Rect{ rect }
	, m_Velocity{ velocity }
	, m_Viewport{ viewport }
{
	m_IsLookingR = true;
	m_HitJump = false;
	m_IsJumping = false;
	m_HeightStanding = 150.f;
	m_MaxWalkVelocity.x = 480.f;
	m_MaxRunVelocity.x = 960.f;
	m_HoldingBox = false;
	m_HoldingColorBox = false;
	m_Color = Color4f{ 0.5f, 0.5f, 0.5f, 1.f };
}

void Player::Draw() const
{
	utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
	utils::DrawRect(m_Rect, 5.f);
	utils::SetColor(m_Color);
	utils::FillRect(m_Rect);
}

void Player::Update(std::vector<std::vector<Point2f>> vertices, float elapsedSec, Rectf boxRect)
{
	UpdateCollissions(vertices, elapsedSec, boxRect);
}

void Player::UpdateCollissions(std::vector<std::vector<Point2f>> vertices, float elapsedSec, Rectf boxRect)
{
	bool fall{true};

	for (int idx{}; idx < vertices.size(); ++idx) {
		if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left, m_Rect.bottom + 10.f }, Point2f{ m_Rect.left, m_Rect.bottom - 1 }, m_LeftBottomHit)
			&& (m_Jump > 1.f || m_Jump == 0.f))
		{
			m_Velocity.y = 0.f;
			m_Rect.left = m_LeftBottomHit.intersectPoint.x;
			m_Rect.bottom = m_LeftBottomHit.intersectPoint.y;
			m_IsJumping = false;
			m_Jump = 0.f;

			if (!fall)fall = false;

		}
		else if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left + m_Rect.width, m_Rect.bottom + 10.f }, Point2f{ m_Rect.left + m_Rect.width, m_Rect.bottom - 1 }, m_RightBottomHit)
			&& (m_Jump > 1.f || m_Jump == 0.f))
		{
			m_Velocity.y = 0.f;
			m_Rect.left = m_RightBottomHit.intersectPoint.x - m_Rect.width;
			m_Rect.bottom = m_RightBottomHit.intersectPoint.y;
			m_IsJumping = false;
			m_Jump = 0.f;

			if (!fall)fall = false;
		}

		if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left, m_Rect.bottom + 10.f }, Point2f{ m_Rect.left + m_Rect.width - 20.f,m_Rect.bottom + 10.f }, m_LeftHit))
		{
			m_Velocity.x = 0.f;
			m_Rect.left = m_LeftHit.intersectPoint.x;
		}
		else if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left + m_Rect.width, m_Rect.bottom + 10.f }, Point2f{ m_Rect.left + m_Rect.width / 2, m_Rect.bottom + 10.f }, m_RightHit))
		{
			m_Velocity.x = 0.f;
			m_Rect.left = m_RightHit.intersectPoint.x - m_Rect.width;
		}

		if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left + 2, m_Rect.bottom + m_Rect.height + 2 }, Point2f{ m_Rect.left - 2,m_Rect.bottom + m_Rect.height - 2 }, m_LeftTopHit))
		{
			m_Rect.bottom = m_LeftTopHit.intersectPoint.y - m_Rect.height;
			m_Jump = 2.f;
			m_IsJumping = false;
		}
	}

	if (utils::IsOverlapping(m_Rect, boxRect) && (m_Jump > 1.f || m_Jump == 0.f) && m_Velocity.y < 0 && m_Rect.bottom - (boxRect.bottom + boxRect.height) > -10)
	{
		m_Velocity.y = 0.f;
		m_Rect.bottom = boxRect.bottom + boxRect.height;
		m_IsJumping = false;
		m_Jump = 0.f;
		if (!fall)fall = false;
	}

	if (fall)m_Velocity.y -= 1.f;
	m_Rect.bottom += m_Velocity.y * elapsedSec;
}

void Player::UpdateCollisionWall(Rectf wallRect, float elapsedSec)
{
	if (utils::IsOverlapping(m_Rect, wallRect)) m_Rect.left = wallRect.left + wallRect.width;
}

void Player::MovementWalk(float elapsedSeconds, bool isLookingR)
{
	m_IsLookingR = isLookingR;
	if (m_IsLookingR == true)
	{
		m_Rect.left += m_MaxWalkVelocity.x * elapsedSeconds;
		m_Velocity.x = m_MaxWalkVelocity.x;
	}
	else
	{
		m_Rect.left -= m_MaxWalkVelocity.x * elapsedSeconds;
		m_Velocity.x = -m_MaxWalkVelocity.x;
	}
}

void Player::MovementRun(float elapsedSeconds, bool isLookingR)
{
	m_IsLookingR = isLookingR;
	if (m_IsLookingR == true)
	{
		m_Rect.left += m_MaxRunVelocity.x * elapsedSeconds;
		m_Velocity.x = m_MaxRunVelocity.x;
	}
	else
	{
		m_Rect.left -= m_MaxRunVelocity.x * elapsedSeconds;
		m_Velocity.x = -m_MaxRunVelocity.x;
	}
}

void Player::Jump(float elapsedSeconds, float heightStanding)
{
	m_HeightStanding = heightStanding;
	m_Rect.bottom = (-((m_Jump * 1.f - 1) * (m_Jump * 1.f - 1)) + 1) * 200 + m_HeightStanding;

	m_Jump += 0.01f;
	if (m_Jump >= 3.f)
	{
		m_Jump = 0;
		m_IsJumping = false;
	}
}

bool Player::GetIsJumping()
{
	return m_IsJumping;
}

void Player::SetIsJumping(bool value)
{
	m_IsJumping = value;
}

Point2f Player::GetPosition()
{
	return Point2f{ m_Rect.left, m_Rect.bottom };
}

Rectf Player::GetRect()
{
	return m_Rect;
}

float Player::GetVelocityX()
{
	return m_Velocity.x;
}

bool Player::PickUpBox(Rectf boxRect)
{
	if (utils::IsOverlapping(m_Rect, boxRect)) 
	{
		m_HoldingBox = true;
		return true;
	}
	return false;
}

void Player::PickedUpBox(Rectf& boxRect)
{
	if(m_IsLookingR)
	{
		boxRect.left = m_Rect.left + m_Rect.width;
		boxRect.bottom = m_Rect.bottom;
	}
	else
	{
		boxRect.left = m_Rect.left - boxRect.width;
		boxRect.bottom = m_Rect.bottom;
	}
}

void Player::DropBox()
{
	m_HoldingBox = false;
}

bool Player::PickUpColorBox(Rectf boxRect)
{
	if (utils::IsOverlapping(m_Rect, boxRect))
	{
		m_HoldingColorBox = true;
		return true;
	}
	return false;
}

void Player::PickedUpColorBox(Rectf& boxRect)
{
	if (m_IsLookingR)
	{
		boxRect.left = m_Rect.left + m_Rect.width;
		boxRect.bottom = m_Rect.bottom;
	}
	else
	{
		boxRect.left = m_Rect.left - boxRect.width;
		boxRect.bottom = m_Rect.bottom;
	}
}

void Player::DropColorBox()
{
	m_HoldingColorBox = false;
}

bool Player::GetIsHolding() const
{
	return m_HoldingBox;
}

bool Player::GetIsHoldingColor()
{
	return m_HoldingColorBox;
}

void Player::SwitchColor(Color4f color)
{
	m_Color.r = color.r;
	m_Color.g = color.g;
	m_Color.b = color.b;
}

Color4f Player::GetColor()
{
	return m_Color;
}

void Player::SetPosition(Point2f pos)
{
	m_Rect.left = pos.x;
	m_Rect.bottom = pos.y;
}

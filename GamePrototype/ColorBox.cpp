#include "pch.h"
#include "ColorBox.h"
#include "utils.h"

ColorBox::ColorBox(Rectf rect, Point2f pos, Color4f color)
	: m_Rect{ rect }
	, m_Position{ pos }
	, m_Color{ color }
{
	m_Velocity = Vector2f{ 0,0 };
	m_Collision = false;
	m_IsHolding = false;
}

void ColorBox::Draw() const
{
	utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
	utils::DrawRect(m_Rect, 5.f);
	utils::SetColor(m_Color);
	utils::FillRect(m_Rect);
}

void ColorBox::UpdateCollisions(std::vector<std::vector<Point2f>> vertices, float elapsedSec)
{
	bool Collision{ false };

	for (int idx{}; idx < vertices.size(); ++idx) {
		if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left, m_Rect.bottom + 10.f }, Point2f{ m_Rect.left, m_Rect.bottom - 1 }, m_LeftBottomHit))
		{
			m_Velocity.y = 0.f;
			m_Rect.left = m_LeftBottomHit.intersectPoint.x;
			m_Rect.bottom = m_LeftBottomHit.intersectPoint.y;
		}
		else if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left + m_Rect.width, m_Rect.bottom + 10.f }, Point2f{ m_Rect.left + m_Rect.width, m_Rect.bottom - 1 }, m_RightBottomHit))
		{
			m_Velocity.y = 0.f;
			m_Rect.left = m_RightBottomHit.intersectPoint.x - m_Rect.width;
			m_Rect.bottom = m_RightBottomHit.intersectPoint.y;
		}
		else
		{
			m_Velocity.y += (-1.f);
		}

		if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left, m_Rect.bottom + 10.f }, Point2f{ m_Rect.left + m_Rect.width - 20.f,m_Rect.bottom + 10.f }, m_LeftHit))
		{
			m_Velocity.x = 0.f;
			//m_Rect.left = m_LeftHit.intersectPoint.x;
			if (!Collision) Collision = true;
		}
		else if (utils::Raycast(vertices[idx], Point2f{ m_Rect.left + m_Rect.width, m_Rect.bottom + 10.f }, Point2f{ m_Rect.left + m_Rect.width / 2, m_Rect.bottom + 10.f }, m_RightHit))
		{
			m_Velocity.x = 0.f;
			//m_Rect.left = m_RightHit.intersectPoint.x - m_Rect.width;
			if (!Collision) Collision = true;
		}
	}
	m_Rect.bottom += m_Velocity.y * elapsedSec;
	m_Collision = Collision;
}

void ColorBox::MoveBox(Rectf playerRect, float elapsedSec, float playerSpeed)
{
	m_Velocity.x = playerSpeed;
	if (utils::IsOverlapping(Rectf{ m_Rect.left, m_Rect.bottom, m_Rect.width, m_Rect.height - 10.f }, playerRect))
	{
		if (m_Velocity.x > 0) m_Rect.left = playerRect.left + playerRect.width;
		else if (m_Velocity.x < 0) m_Rect.left = playerRect.left - m_Rect.width;
	}
}

bool ColorBox::FuseBox(Rectf boxRect)
{
	if (utils::IsOverlapping(m_Rect, boxRect) && m_Rect.width == boxRect.width) return true;
	return false;
}

void ColorBox::BigBox(Color4f color)
{
	m_Color.r += color.r;
	m_Color.g += color.g;
	m_Color.b += color.b;
}

Rectf& ColorBox::GetRect()
{
	return m_Rect;
}

bool ColorBox::GetCollision()
{
	return m_Collision;
}

void ColorBox::PickUp()
{
	m_IsHolding = true;
}

void ColorBox::Drop()
{
	if(this != nullptr)
		m_IsHolding = false;
}

bool ColorBox::GetIsHolding()
{
	return m_IsHolding;
}

void ColorBox::UpdateYCollision(const Rectf& boxRect)
{
	if (m_Velocity.y >= 0) return;
	if (utils::IsOverlapping(m_Rect, boxRect) && m_Rect.bottom - (boxRect.bottom + boxRect.height) > -10)
	{
		m_Rect.bottom = boxRect.bottom + boxRect.height;
		m_Velocity.y = 0;
	}
}

Color4f ColorBox::GetColor()
{
	return m_Color;
}

void ColorBox::SetPosition(Point2f value)
{
	m_Rect.left = value.x;
	m_Rect.bottom = value.y;
}

void ColorBox::SetColor(Color4f color)
{
	m_Color = color;
}

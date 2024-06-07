#include "pch.h"
#include "Wall.h"
#include "utils.h"

Wall::Wall(Rectf wallRect, Color4f wallColor)
	: m_Rect{ wallRect }
	, m_Color{ wallColor }
{
}

void Wall::Draw() const
{
	utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
	utils::DrawRect(m_Rect, 5.f);
	utils::SetColor(m_Color);
	utils::FillRect(m_Rect);
}

bool Wall::CheckColor(Color4f color, Rectf rect)
{
	if(utils::IsOverlapping(m_Rect, rect))
	{
		if (m_Color.r == color.r && m_Color.g == color.g && m_Color.b == color.b) return true;
	}
	return false;
}

Rectf Wall::GetRect()
{
	return m_Rect;
}

void Wall::SetPosition(Point2f value)
{
	m_Rect.left = value.x;
	m_Rect.bottom = value.y;
}

#include "pch.h"
#include "ColorSwitch.h"
#include "utils.h"

ColorSwitch::ColorSwitch(Rectf rect, Color4f color)
	: m_Rect{ rect }
	, m_Color{ color }
{

}

void ColorSwitch::Draw() const
{
	utils::SetColor(m_Color);
	utils::FillRect(m_Rect);
}

bool ColorSwitch::CheckCollision(Rectf rect)
{
	if(utils::IsOverlapping(m_Rect, rect)) return true;
	return false;
}

Color4f ColorSwitch::GetColor()
{
	return m_Color;
}
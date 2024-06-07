#pragma once

class ColorSwitch
{
public:
	ColorSwitch(Rectf rect, Color4f color);
	void Draw() const;
	bool CheckCollision(Rectf rect);
	Color4f GetColor();
private:
	Rectf m_Rect;
	Color4f m_Color;
};


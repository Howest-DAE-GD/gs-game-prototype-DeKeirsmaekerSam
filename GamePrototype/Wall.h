#pragma once
class Wall
{
public:
	Wall(Rectf wallRect, Color4f wallColor);
	void Draw() const;
	bool CheckColor(Color4f color, Rectf rect);
	Rectf GetRect();
	void SetPosition(Point2f value);
private:
	Rectf m_Rect;
	Color4f m_Color;
};


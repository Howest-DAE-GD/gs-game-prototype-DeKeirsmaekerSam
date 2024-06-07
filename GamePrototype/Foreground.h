#pragma once
#include "Texture.h"
#include "SVGParser.h"
#include <vector>
class Foreground
{
public:
	Foreground();
	~Foreground();
	void Draw();
	void FollowPlayerX(Point2f pos);
	std::vector<std::vector<Point2f>> GetVertices();

private:
	Texture* m_pForeground;
	std::vector<std::vector<Point2f>> m_Vertices;

	Rectf m_DstRect;
	Rectf m_SrcRect;

	Rectf m_CameraRect;
	Rectf m_PlayerRect;
};


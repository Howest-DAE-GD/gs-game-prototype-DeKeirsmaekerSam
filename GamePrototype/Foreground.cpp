#include "pch.h"
#include "Foreground.h"
#include "Texture.h"
#include "utils.h"

Foreground::Foreground()
{
	m_pForeground = new Texture{ "LEVEL.png" };
	SVGParser::GetVerticesFromSvgFile("LEVEL.svg", m_Vertices);
	m_DstRect = Rectf{ 0, 0, 3840, 2160 };
	m_SrcRect = Rectf{ 0,0, m_pForeground->GetWidth(), m_pForeground->GetHeight() };

	m_CameraRect = Rectf{ 0,0, 1152.f , 672.f };
	m_PlayerRect = Rectf{ m_CameraRect.left +  m_CameraRect.width / 3,50, 400 , 400 };
}

Foreground::~Foreground()
{
	delete m_pForeground;
	m_pForeground = nullptr;
}

void Foreground::Draw()
{
	m_pForeground->Draw(m_DstRect, m_SrcRect);

	/*utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	for (std::vector<Point2f> ptr : m_Vertices)
	{
		utils::DrawPolygon(ptr, true, 1.f);
	}*/


}

void Foreground::FollowPlayerX(Point2f pos)
{
	if (pos.x < m_PlayerRect.left)
	{
		float cameraOffset{ m_PlayerRect.left - pos.x };

		m_CameraRect.left -= cameraOffset;
		m_PlayerRect.left -= cameraOffset;
	}
	else if (pos.x > m_PlayerRect.left + m_PlayerRect.width)
	{
		float cameraOffset{ pos.x - m_PlayerRect.left - m_PlayerRect.width };

		m_CameraRect.left += cameraOffset;
		m_PlayerRect.left += cameraOffset;
	}

	if (pos.y < m_PlayerRect.bottom)
	{
		float cameraOffset{ m_PlayerRect.bottom - pos.y };

		m_CameraRect.bottom -= cameraOffset;
		m_PlayerRect.bottom -= cameraOffset;
	}
	else if (pos.y > m_PlayerRect.bottom + m_PlayerRect.height)
	{
		float cameraOffset{ pos.y - m_PlayerRect.bottom - m_PlayerRect.height };

		m_CameraRect.bottom += cameraOffset;
		m_PlayerRect.bottom += cameraOffset;
	}

	glTranslated(-m_CameraRect.left, -m_CameraRect.bottom, 0.f);
}

std::vector<std::vector<Point2f>> Foreground::GetVertices()
{
	return m_Vertices;
}

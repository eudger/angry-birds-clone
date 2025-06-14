#pragma once
#ifndef __WALL_H__
#define __WALL_H__

#include "Dependencies\Box2D\include\Box2D\Box2D.h"

class Wall
{
public:
	Wall();
	~Wall() { /* Do Nothing */ };

	void CreateWall(b2World*, float _posX, float _posY);
	void ConvertPixelsToMeters(float&, float&);

private:
	float m_WallSalar;
	float m_WallWidth;
	float m_WallHeight;
};

#endif // !__WALL_H__
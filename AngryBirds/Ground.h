#pragma once
#ifndef __GROUND_H__
#define __GROUND_H__

#include "Dependencies\Box2D\include\Box2D\Box2D.h"
#include "utils.h"

class Ground
{
public:
	Ground();
	~Ground() { /* Do Nothing */ };

	void CreateGround(b2World*, float _posX, float _posY, char* _texturePath);
	void Render(sf::RenderWindow& _window);
private: 
	float m_GroundSalar;
	float m_GroundWidth;
	float m_GroundHeight;

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
};

#endif // !__GROUND_H__
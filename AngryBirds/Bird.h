#pragma once
#ifndef __BIRD_H__
#define __BIRD_H__

#include "QueryCallback.h"
#include "utils.h"
#include "Dependencies\SFML\include\SFML\Audio.hpp"
#include <cstdlib>
#include <ctime>

class Bird
{
public:
	Bird();
	~Bird() { /* Do Nothing */ };
	
	void Init(b2World*, char* _texturePath, float _scaleX, float _scaleY);

	void CreateBird(b2World*, float, float, float _density = 3.0f, float _restitution = 0.5f, float _friction = 0.5f, float _strength = 50.0f);

	void MouseDown(b2World* _theBox2DWorld, const b2Vec2& _MouseCoord);
	void MouseMove(const b2Vec2& _MouseCoord);
	void MouseUp(b2World* _theBox2DWorld, const b2Vec2& _MouseCoord);
	void UpdateBirdPosition(b2Body*);
	void SwitchDynamic(bool _physicsType);
	inline b2Vec2 GetBirdPos() { return m_BirdPos; };

	inline b2Body* GetBody() { return m_TheBirdBody; }
	inline sf::Sprite GetSprite() const { return m_Sprite; }
	void Render(sf::RenderWindow& _gameWindow);
	void Update();
	void Reset(float _x, float _y);

	float* GetVelocityPtr() { return &m_velocity; }
	void YellowBird(b2Vec2& _mousePos);
	void WhiteBird();
	bool OutOfBounds() const;
	
	sf::VertexArray GetLine() { return m_theLine; }

	void SetSpecialAbility(bool _bEnableSpecial) { m_specialAbility = _bEnableSpecial; }

private:
	float m_BirdWidth;
	float m_BirdHeight;
	float m_velocity;
	float m_Strength;
	int m_clickCount;
	bool m_released;
	bool m_specialAbility;

	b2MouseJoint* m_MouseJoint = nullptr;
	b2Body* m_TheBirdBody = nullptr, *m_Groundbody = nullptr;
	b2Vec2 m_BirdPos;
	b2Vec2 m_StartPoint, m_MouseMoveCoord;

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
	sf::SoundBuffer m_soundBuffer[2];
	sf::Sound m_flingSounds[2];
	sf::VertexArray m_theLine;
	sf::RectangleShape m_line;
	sf::Vertex m_LineStartVertices, m_LineEndVertices;
	
	float m_counter;
	float m_startX, m_startY, m_endX, m_endY;
	int m_randomNum;
};

#endif // !__BIRD_H__
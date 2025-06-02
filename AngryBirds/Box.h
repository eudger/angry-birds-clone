#pragma once
#ifndef __BOX_H__
#define __BOX_H__

#include "Dependencies\Box2D\include\Box2D\Box2D.h"
#include "Dependencies\SFML\include\SFML\Audio.hpp"
#include "utils.h"

class Box
{
public:
	Box();
	~Box() { /* Do Nothing */ };

	void CreateBox(b2World*, float, float);

	void BeginContact() { m_collision = true; };
	void EndContact() { m_collision = false; };
	
	void SetCollisionStatus(bool _collisionStatusReset) { m_collision = _collisionStatusReset; };
	inline bool GetCollisionStatus() { return m_collision; };

	inline float GetVelocity() const { return m_velocity; };

	Box* GetMemoryLoc() { return m_pPointer; };

	void Update();
	void Reset(float _x, float _y);

	void SetPlayOnce(bool _bPlayOnce) { m_playOnce = _bPlayOnce; }

private:
	Box* m_pPointer;
	float m_BoxScalingFactor;
	float m_BoxWidth;
	float m_BoxHeight;
	float m_velocity;
	b2Body* TheBoxBody;
	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_boxShatterSound;

	bool m_collision = false;
	bool m_playOnce = true;
};

#endif // !__BOX_H__
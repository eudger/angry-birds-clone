#pragma once
#ifndef __CHAIN_H__
#define __CHAIN_H__

#include "Dependencies\SFML\include\SFML\Graphics.hpp"
#include "Dependencies\Box2D\include\Box2D\Box2D.h"

typedef unsigned short int uShort;

class Chain
{
public:
	Chain();
	~Chain() { /* Do Nothing */ };

	void InitChain(b2World*);
	void CreateChain(b2World*, float, float);
	void ConvertPixelsToMeters(float&, float&);

private:
	float m_ChainScalingFactor;
	float m_ChainWidth;
	float m_ChainHeight;
	
	b2Body *m_Groundbody = nullptr;
	b2Body* link;
};
#endif // !__CHAIN_H__

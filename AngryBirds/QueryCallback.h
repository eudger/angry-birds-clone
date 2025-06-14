#pragma once
#ifndef __QUERYCALLBACK_H__
#define __QUERYCALLBACK_H__

#include "Dependencies\Box2D\include\Box2D\Box2D.h"

class QueryCallback : public b2QueryCallback
{
public:
	QueryCallback(const b2Vec2& point)
	{
		m_point = point;
		m_fixture = NULL;
	}

	bool ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();

		if (body->GetType() == b2_staticBody)
		{
			bool inside = fixture->TestPoint(m_point);
			if (inside)
			{
				m_fixture = fixture;
				return false;
			}
		}

		return true;
	}

	b2Vec2 m_point;
	b2Fixture* m_fixture;
};

#endif // !__QUERYCALLBACK_H__
#include "Wall.h"

Wall::Wall()
{
	m_WallWidth = 60.0f;
	m_WallHeight = 1000.0f;
	m_WallSalar = 25.0f;
}

void Wall::CreateWall(b2World* TheWorld, float PosX, float PosY)
{
	b2BodyDef wallBodyDef;
	ConvertPixelsToMeters(PosX, PosY);
	wallBodyDef.position.Set(PosX, PosY);
	wallBodyDef.type = b2_staticBody;
	b2Body* wall = TheWorld->CreateBody(&wallBodyDef);
	wall->SetUserData("Wall");

	b2PolygonShape wallShape;
	float GroundWidth = m_WallWidth / 2.0f;
	float GroundHeight = m_WallHeight / 2.0f;
	ConvertPixelsToMeters(GroundWidth, GroundHeight);
	wallShape.SetAsBox(GroundWidth, GroundHeight);

	b2FixtureDef Fixture;
	Fixture.shape = &wallShape;
	Fixture.density = 0.0f;
	Fixture.friction = 10.0f;
	Fixture.restitution = 0.5f;

	wall->CreateFixture(&Fixture);
}

void Wall::ConvertPixelsToMeters(float& a, float& b)
{
	a /= m_WallSalar;
	b /= m_WallSalar;
}
#include "Platform.h"

Platform::Platform()
{
	m_platformScalingFactor = 25.0f;
	m_platformHeight = 20.0f;
	m_platformWidth = 100.0f;
}

void Platform::CreatePlatform(b2World* _world, float _posX, float _posY)
{
	b2BodyDef platformBodyDef;
	ConvertPixelsToMeters(_posX, _posY);
	platformBodyDef.position.Set(_posX, _posY);
	platformBodyDef.type = b2_kinematicBody;
	b2Body* platformBody = _world->CreateBody(&platformBodyDef);
	b2Body* platformBody2 = _world->CreateBody(&platformBodyDef);
	platformBody2->SetTransform(b2Vec2(platformBody->GetPosition().x, platformBody->GetPosition().y - 10.0f), 0.0f);

	platformBody->SetUserData("lowerPlatform");
	platformBody2->SetUserData("upperPlatform");

	b2PolygonShape Shape;
	Shape.SetAsBox(1.7f, 0.3f);

	b2FixtureDef Fixture;
	Fixture.shape = &Shape;
	Fixture.density = 1.0f;
	Fixture.friction = 0.3f;
	Fixture.restitution = 0.3f;

	platformBody->CreateFixture(&Fixture);
	platformBody2->CreateFixture(&Fixture);

	b2PrismaticJointDef pDef;
	pDef.bodyA = platformBody;
	pDef.bodyB = platformBody2;
	_world->CreateJoint(&pDef);
}
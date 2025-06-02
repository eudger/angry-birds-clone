#include "CollisionDetector.h"
#include "Ground.h"

CollisionDetector::CollisionDetector()
{
}

CollisionDetector::~CollisionDetector()
{
}

void CollisionDetector::BeginContact(b2Contact* _contact)
{
	auto bodyUserDataOne = _contact->GetFixtureA()->GetBody()->GetUserData();
	auto bodyUserDataTwo = _contact->GetFixtureB()->GetBody()->GetUserData();
	
	if (bodyUserDataOne && bodyUserDataTwo == "Ground")
	{
		if (bodyUserDataOne != "Plank")
			static_cast<Box*>(bodyUserDataOne)->BeginContact();
	}
	if (bodyUserDataOne == "Player" && bodyUserDataTwo)
	{
		if (bodyUserDataTwo != "Player")
			static_cast<Enemy*>(bodyUserDataTwo)->PlayerCollision();
	}
	if (bodyUserDataOne == "Ground" && bodyUserDataTwo)
	{
		if (bodyUserDataTwo != "Player")
			static_cast<Enemy*>(bodyUserDataTwo)->GroundCollision();
	}
}

void CollisionDetector::EndContact(b2Contact* _contact)
{
	auto bodyUserDataOne = _contact->GetFixtureA()->GetBody()->GetUserData();
	auto bodyUserDataTwo = _contact->GetFixtureB()->GetBody()->GetUserData();
}
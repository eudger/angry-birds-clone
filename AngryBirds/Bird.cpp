#include "Bird.h"
#include <thread>
#include <iostream> 

Bird::Bird() :
	m_clickCount(0),
	m_released(false),
	m_randomNum(0),
	m_specialAbility(true)
{
	m_BirdWidth = 60.0f;
	m_BirdHeight = 60.0f;
	m_theLine.resize(2);

	srand(static_cast<unsigned int>(time(NULL)));
}

void Bird::Init(b2World* TheWorld, char* _texturePath, float _scaleX, float _scaleY)
{
	m_Texture.loadFromFile(_texturePath);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setScale(_scaleX, _scaleY);
	m_Sprite.setOrigin(15.0f, 15.0f);

	if (!m_soundBuffer[0].loadFromFile("Assets/Sounds/Flinged.wav") || (!m_soundBuffer[1].loadFromFile("Assets/Sounds/Flinged2.wav")))
	{
		std::cerr << "ERROR: Unable to load sounds.\n";
	}

	m_flingSounds[0].setBuffer(m_soundBuffer[0]);
	m_flingSounds[1].setBuffer(m_soundBuffer[1]);

	b2BodyDef bodyDef;
	m_Groundbody = TheWorld->CreateBody(&bodyDef);
	b2Vec2 tmp(100.0f, 100.0f);
	m_Groundbody->SetTransform(tmp, 80.0f);  
}

void Bird::CreateBird(b2World* TheWorld, float PosX, float PosY, float _density, float _restitution, float _friction, float _strength)
{
	b2BodyDef BirdBodyDef;
	ConvertPixelsToMeters(PosX, PosY);
	m_BirdPos.Set(PosX, PosY);
	BirdBodyDef.position.Set(PosX, PosY);
	BirdBodyDef.type = b2_staticBody;
	m_TheBirdBody = TheWorld->CreateBody(&BirdBodyDef);
	m_TheBirdBody->SetUserData("Player");

	b2CircleShape BirdShape;
	float BirdWidth = m_BirdWidth / 2.0f;
	float BirdHeight = m_BirdHeight / 2.0f;
	ConvertPixelsToMeters(BirdWidth, BirdHeight);
	BirdShape.m_p.Set(BirdWidth, BirdHeight);
	BirdShape.m_radius = 1.0;

	b2FixtureDef Fixture;
	Fixture.shape = &BirdShape;
	Fixture.density = _density;
	Fixture.friction = _friction;	 
	Fixture.restitution = _restitution;	 
	m_TheBirdBody->CreateFixture(&Fixture);

	m_Strength = _strength;
}

void Bird::MouseMove(const b2Vec2& _MouseCoord)
{
	m_MouseMoveCoord = _MouseCoord;

	if (m_MouseJoint != nullptr)
	{
		// Always convert to box2d coordinates 
		ConvertPixelsToMeters(m_MouseMoveCoord.x, m_MouseMoveCoord.y);
		m_MouseJoint->SetTarget(m_MouseMoveCoord);

		b2Vec2 pos = m_MouseMoveCoord;

		if (pos.x < 13 && pos.x > 5 && pos.y > 16.0f && pos.y < 26.0f)
		{
			pos.x = pos.x - 1.0f;
			m_LineEndVertices.position.x = _MouseCoord.x;
			m_LineEndVertices.position.y = _MouseCoord.y;

			m_theLine.setPrimitiveType(sf::Lines);
			m_theLine[0].position = m_LineStartVertices.position;
			m_theLine[0].color = sf::Color::Blue;
			m_theLine[1].position = m_LineEndVertices.position;
			m_theLine[1].color = sf::Color::Blue;

			m_TheBirdBody->SetTransform(pos, 0);
		}
	}
}

void Bird::MouseDown(b2World* TheWorld, const b2Vec2& _mousePos)
{
	m_StartPoint = _mousePos;

	b2AABB aabb;
	b2Vec2 d;

	ConvertPixelsToMeters(m_StartPoint.x, m_StartPoint.y);
	m_StartPoint.Set(m_StartPoint.x, m_StartPoint.y);

	d.Set(0.001f, 0.001f);
	aabb.lowerBound = m_StartPoint - d;
	aabb.upperBound = m_StartPoint + d;

	QueryCallback callback(m_StartPoint);
	TheWorld->QueryAABB(&callback, aabb);
	
	if (callback.m_fixture)
	{
		b2Body* body = callback.m_fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = m_Groundbody;
		md.bodyB = body;
		md.target = m_StartPoint;
		md.maxForce = 1000.0f * body->GetMass();
		m_MouseJoint = (b2MouseJoint*)TheWorld->CreateJoint(&md);
		body->SetAwake(true);
		m_startX = _mousePos.x;
		m_startY = _mousePos.y;
		m_LineStartVertices.position = sf::Vector2f(m_startX, m_startY);
	}
}

void Bird::MouseUp(b2World* TheWorld, const b2Vec2& p)
{
	if (m_MouseJoint != nullptr)
	{
		m_randomNum = (rand() % 2) + 1;

		if (m_randomNum == 1)
		{
			m_flingSounds[0].setVolume(60.0f);
			m_flingSounds[0].play();
		}
		else if (m_randomNum == 2)
		{
			m_flingSounds[1].setVolume(60.0f);
			m_flingSounds[1].play();
		}

		TheWorld->DestroyJoint(m_MouseJoint);
		m_MouseJoint = nullptr;

		int x = m_MouseMoveCoord.x;
		int y = m_MouseMoveCoord.y;

		b2Vec2 BirdStartPos = b2Vec2(m_StartPoint.x, m_StartPoint.y);
		b2Vec2 BirdSlingshotPos = b2Vec2(x, y);
		b2Vec2 birdVelocity = BirdStartPos - BirdSlingshotPos;
		birdVelocity *= m_Strength;

		SwitchDynamic(true);
		m_TheBirdBody->ApplyLinearImpulse(birdVelocity, BirdStartPos, true);
		m_released = true;

		m_theLine.clear();
		m_theLine.resize(2);
	}
}

void Bird::UpdateBirdPosition(b2Body* Pos)
{
	m_BirdPos.Set(Pos->GetPosition().x, Pos->GetPosition().y);
}

void Bird::SwitchDynamic(bool _bSwitch)
{
	if (_bSwitch)
	{
		m_TheBirdBody->SetType(b2_dynamicBody);
	}
	else
	{
		m_TheBirdBody->SetType(b2_staticBody);
	}
}

void Bird::Render(sf::RenderWindow& _gameWindow)
{
	m_Sprite.setPosition(m_BirdPos.x * SCALE, m_BirdPos.y * SCALE);
	m_Sprite.setRotation(m_TheBirdBody->GetAngle() * 180 / b2_pi);
	_gameWindow.draw(m_Sprite);
}

void Bird::Update()
{
	UpdateBirdPosition(m_TheBirdBody);
	m_velocity = sqrtf((m_TheBirdBody->GetLinearVelocity().x * m_TheBirdBody->GetLinearVelocity().x) + (m_TheBirdBody->GetLinearVelocity().y * m_TheBirdBody->GetLinearVelocity().y));
}

void Bird::Reset(float _x, float _y)
{
	m_released = false;
	m_clickCount = 0;
	SwitchDynamic(false);
	m_TheBirdBody->SetTransform(b2Vec2(_x, _y), b2_pi * 2);
}

void Bird::YellowBird(b2Vec2& _mousePos)
{
	if (m_released)
	{
		if (m_clickCount >= 1 && m_specialAbility)
		{
			this->m_specialAbility = false;
			ConvertPixelsToMeters(_mousePos.x, _mousePos.y);

			b2Vec2 birdVelocity = _mousePos - m_BirdPos;
			birdVelocity *= 100.0f;
			m_TheBirdBody->ApplyLinearImpulse(birdVelocity, _mousePos, true);
		}	
	}

	m_clickCount++;
}

void Bird::WhiteBird()
{
	if (m_released)
	{
		if (m_clickCount >= 1 && m_specialAbility)
		{
			this->m_specialAbility = false;
			b2Vec2 ground = m_BirdPos;
			ground.y = 40.0f;

			b2Vec2 birdVelocity = ground - m_BirdPos;
			birdVelocity *= 100.0f;
			m_TheBirdBody->ApplyLinearImpulse(birdVelocity, ground, true);
		}
	}
		m_clickCount++;
}

bool Bird::OutOfBounds() const
{
	if (m_BirdPos.x < -10.0f || m_BirdPos.x > 60.0f || m_BirdPos.y <= 30.0f && m_BirdPos.y >= 29.0f || m_BirdPos.y >= 70.0f)
		return true;
	else
		return false;
}
#include "Enemy.h"

Enemy::Enemy()
	: m_destroyed(false)
	, m_dead(false)
{
	m_EnemyWidth = 60.0f;
	m_EnemyHeight = 60.0f;
	m_pPointer = nullptr;
}

void Enemy::Init(b2World* TheWorld, char* _texturePath, int* _score, int* _enemyCount, float* _playerVel)
{
	m_score = _score;
	m_enemyCount = _enemyCount;
	m_playerVel = _playerVel;
	*m_enemyCount += 1;

	m_Texture.loadFromFile(_texturePath);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_Sprite.setOrigin(30.0f, 54.0f);

	b2BodyDef bodyDef;
	m_Groundbody = TheWorld->CreateBody(&bodyDef);
	b2Vec2 tmp(100.0f, 100.0f);
	m_Groundbody->SetTransform(tmp, 80.0f); // Set it far away from camera space
}

void Enemy::CreateEnemy(b2World * TheWorld, float PosX, float PosY)
{
	b2BodyDef EnemyBodyDef;
	ConvertPixelsToMeters(PosX, PosY);
	m_EnemyPos.Set(PosX, PosY);
	EnemyBodyDef.position.Set(PosX, PosY);
	EnemyBodyDef.type = b2_dynamicBody;
	m_TheEnemyBody = TheWorld->CreateBody(&EnemyBodyDef);
	this->m_pPointer = this;
	m_TheEnemyBody->SetUserData(this);

	b2CircleShape BirdShape;
	float BirdWidth = m_EnemyWidth / 2.0f;
	float BirdHeight = m_EnemyHeight / 2.0f;
	ConvertPixelsToMeters(BirdWidth, BirdHeight);
	BirdShape.m_p.Set(BirdWidth, BirdHeight);
	BirdShape.m_radius = 1.25f;

	b2FixtureDef Fixture;
	Fixture.shape = &BirdShape;
	Fixture.density = 1.0f;
	Fixture.friction = 0.3f;
	Fixture.restitution = 0.3f;
	m_TheEnemyBody->CreateFixture(&Fixture);
}

void Enemy::UpdateEnemyPosition(b2Body* Pos)
{
	m_EnemyPos.Set(Pos->GetPosition().x, Pos->GetPosition().y);
}

void Enemy::SetDestroyed(bool _destroyed)
{
	m_destroyed = _destroyed; 
}

void Enemy::SetEnemyPos(float _x, float _y)
{
	ConvertPixelsToMeters(_x, _y);
	m_EnemyPos.Set(_x, _y);
	m_TheEnemyBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	m_TheEnemyBody->SetAngularVelocity(0.0f);
	m_TheEnemyBody->SetTransform(m_EnemyPos, 0);
}

void Enemy::GroundCollision()
{
	if (m_velocity > 3.0f)
		m_destroyed = true;
}

void Enemy::PlayerCollision()
{
	if (*m_playerVel >= 15.0f)
		m_destroyed = true;
}

void Enemy::Render(sf::RenderWindow& _gameWindow)
{
	m_Sprite.setPosition(m_EnemyPos.x * SCALE, m_EnemyPos.y * SCALE);
	m_Sprite.setRotation(m_TheEnemyBody->GetAngle() * 180 / b2_pi);
	_gameWindow.draw(m_Sprite);
}

void Enemy::Update()
{
	m_velocity = sqrtf((m_TheEnemyBody->GetLinearVelocity().x * m_TheEnemyBody->GetLinearVelocity().x) + (m_TheEnemyBody->GetLinearVelocity().y + m_TheEnemyBody->GetLinearVelocity().y));
	UpdateEnemyPosition(m_TheEnemyBody);

	if (m_destroyed)
	{
		m_dead = true;
		*m_score += 2500;
		*m_enemyCount -= 1;
		m_TheEnemyBody->SetTransform(b2Vec2(100.0f, 100.0f), 0.0f);	// teleport off screen
		m_destroyed = false;
	}
}

void Enemy::Reset(float _x, float _y)
{
	if (m_dead)
	{
		m_dead = false;
		*m_enemyCount += 1;
	}

	SetEnemyPos(_x, _y);
}
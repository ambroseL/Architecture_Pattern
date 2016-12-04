#include "PhysicsComponent.h" // class implemented
#include "cocos2d.h"
#include "Box2D/Box2D.h"

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

PhysicsComponent::PhysicsComponent():body(nullptr)
{
}// PhysicsComponent


PhysicsComponent::PhysicsComponent(b2Body* phyBody) : body(phyBody)
{
}// PhysicsComponent

PhysicsComponent::PhysicsComponent(PhysicsComponent& physicsComponent)
{
	this->body = physicsComponent.body;
}// PhysicsComponent

PhysicsComponent::~PhysicsComponent()
{
}// ~PhysicsComponent


PhysicsComponent* PhysicsComponent::Clone()
{
	return new PhysicsComponent(copyBody(this->body));
}


//==============��Ĳ��� =====================

void PhysicsComponent::setSize(float fWidth, float fHeight)
{
	b2Fixture* fixture = body->GetFixtureList();
	b2Filter p_filter = fixture->GetFilterData();
	body->DestroyFixture(fixture);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(fWidth / pixToMeter, fHeight / pixToMeter);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1000.0f;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 1;
	fixtureDef.filter = p_filter;
	body->CreateFixture(&fixtureDef);



}


//==============���Դ�ȡ =====================

const b2Vec2 PhysicsComponent::getSpeed() 
{
	b2Vec2 vec2(0, 0);
	vec2 = body->GetLinearVelocity();
	return vec2;
}

void PhysicsComponent::setSpeed(b2Vec2 fSpeed)
{
	body->SetLinearVelocity(fSpeed);
}


void PhysicsComponent::setBody(b2Body* phyBody)
{
	this->body = phyBody;
}

b2Body* PhysicsComponent::getBody()
{
	return this->body;
}


void PhysicsComponent::setPosition(b2Vec2 pos)
{
	body->SetTransform(b2Vec2(pos.x / pixToMeter, pos.y / pixToMeter), 0);
}


b2Vec2 PhysicsComponent::getPosition()
{
	return body->GetPosition();
}

void PhysicsComponent::setFilterData(b2Filter filter)
{
	body->GetFixtureList()->SetFilterData(filter);
}

float32 PhysicsComponent::getMass() const
{
	return body->GetMass();
}

b2Vec2 PhysicsComponent::getWorldCenter() const
{
	return body->GetWorldCenter();
}

//==============��������==============

b2Body* createBody(int type, int shape, std::string* id, b2World* world, float* data, float density, float friction, 
	float restitution, int groupIndex, int categoryBits, int maskBits)
{
	b2BodyDef bodyDef;                                                          //������������
	if (type == 1)                                                              //��̬����
		bodyDef.type = b2_dynamicBody;
	else                                                                        //��̬����
		bodyDef.type = b2_staticBody;
	bodyDef.position.Set(data[0] / pixToMeter, data[1] / pixToMeter);           //���ø���λ��
	b2Body* body = world->CreateBody(&bodyDef);                                 //�����������
	body->SetUserData(id);                                                      //��¼��Ӧ�İ�װ����ָ��
	b2FixtureDef fixtureDef;                                                    //������������
	b2PolygonShape dynamicBox;                                                  //�������ζ���
	b2CircleShape dynamicCirecle;                                               //����Բ�ζ���
	if (shape == 1)													            //�����Ǿ���
	{
		dynamicBox.SetAsBox(data[2] / pixToMeter, data[3] / pixToMeter);        //���ð����
		fixtureDef.shape = &dynamicBox;                                         //������״
	}
	else                                                                        //������Բ��
	{
		dynamicCirecle.m_radius = data[2] / pixToMeter;                         //���ð뾶
		fixtureDef.shape = &dynamicCirecle;                                     //������״
	}
	fixtureDef.density = density;                                               //�����ܶ�
	fixtureDef.friction = friction;                                             //����Ħ��ϵ��
	fixtureDef.restitution = restitution;                                       //���ûָ�ϵ��
	fixtureDef.filter.groupIndex = groupIndex;
	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits = maskBits;
	body->CreateFixture(&fixtureDef);                                           //�������������
	body->SetLinearDamping(-0.0f);                                              //������
	return body;
}

b2Body* copyBody(b2Body* phyBody)
{
	b2BodyDef bodyDef;       //������������
	bodyDef.type = phyBody->GetType();
	b2World* world = phyBody->GetWorld();
	bodyDef.position = phyBody->GetPosition(); //���ø���λ��	
	b2Body* body = world->CreateBody(&bodyDef);//�����������
	body->SetUserData(phyBody->GetUserData());//��¼��Ӧ�İ�װ����ָ��
	b2Fixture* fixture = phyBody->GetFixtureList();
	if(fixture != NULL)
	{
		b2FixtureDef fixtureDef;
		b2Fixture tmp = *fixture;
		fixtureDef.shape = tmp.GetShape();
		fixtureDef.density = tmp.GetDensity();
		fixtureDef.friction = tmp.GetFriction();
		fixtureDef.restitution = tmp.GetRestitution();
		fixtureDef.filter = tmp.GetFilterData();
		body->CreateFixture(&fixtureDef);                              //�������������
		body->SetLinearDamping(-0.0f);                                 //������
	}
	return body;
}

b2Body* createWallBody(int index,  std::string* id, b2World* world, float* data, float density, float friction, float restitution)
{
	//�������Ը���
	b2BodyDef bodyDef;	//������������
	float positionX = (data[0] + data[2]) / 2;//�����������λ�õ�X����
	float positionY = (data[1] + data[3]) / 2;//�����������λ�õ�Y����
	bodyDef.position.Set(positionX / pixToMeter, positionY / pixToMeter);//���ø���λ��
	b2EdgeShape shape;//�����������������
	shape.Set(b2Vec2((data[0] - positionX) / pixToMeter, (data[1] - positionY) / pixToMeter), b2Vec2((data[2] - positionX) / pixToMeter, (data[3] - positionY) / pixToMeter));//����λ��
	b2FixtureDef fixtureDef;//����������������
	fixtureDef.shape = &shape;//������״
	fixtureDef.density = density;//�����ܶ�
	fixtureDef.friction = friction;//����Ħ��ϵ��
	fixtureDef.restitution = restitution;//���ûָ�ϵ��
	if (index == 1)
	{
		fixtureDef.filter.categoryBits = 0;
	}
	else
	{
		fixtureDef.filter.groupIndex = 1;
		fixtureDef.filter.categoryBits = 2;
		fixtureDef.filter.maskBits = 4;
	}
	b2Body* body = world->CreateBody(&bodyDef);//�����������
	body->SetUserData(id);//�ڸ����м�¼��Ӧ�İ�װ����ָ��
	body->CreateFixture(&fixtureDef);//�����������������
	body->SetLinearDamping(0);
	return body;
}
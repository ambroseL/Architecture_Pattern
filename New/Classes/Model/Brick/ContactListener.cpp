#include "ContactListener.h"
#include "cocos2d.h"

#define BALL_TO_WALL 1
#define BALL_TO_BRICK 2
#define PADDLE_TO_PACK 3
#define PADDLE_TO_WALL 4
#define PADDLE_TO_BALL 5


void ContactListener::BeginContact(b2Contact* contact)
{
	//��ײ��ʼʱ�Ļص�����
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL)
	{
		std::string* aid = (std::string*)bodyA->GetUserData();
		std::string* bid = (std::string*)bodyB->GetUserData();

		char preFixA = aid->at(0);
		char preFixB = bid->at(0);
		EventHandler *newEvent = NULL;
		bool isPermeat = objManager->getBallPermeat();
		if (isPermeat)
			ballVec = objManager->getBallSpeed();
		if ((preFixA == 'Q' || preFixB == 'Q') && (preFixA == 'W' || preFixB == 'W'))//����ǽ����ײ
			newEvent = Strategy(BALL_TO_WALL, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'Q' || preFixB == 'Q') && (preFixA == 'B' || preFixB == 'B'))//����ש�����ײ
			newEvent = Strategy(BALL_TO_BRICK, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'A' || preFixB == 'A'))//�������������ײ
			newEvent = Strategy(PADDLE_TO_PACK, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'W' || preFixB == 'W'))//������ǽ����ײ
			newEvent = Strategy(PADDLE_TO_WALL, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'Q' || preFixB == 'Q'))//�����������ײ
			newEvent = Strategy(PADDLE_TO_BALL, bodyA, bodyB, contact, thisLayer, objManager);

		newEvent->doStrategy();
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	if (objManager->getBallPermeat())
	{
		objManager->setBallSpeed(ballVec);
	}
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}


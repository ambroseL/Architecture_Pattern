#include "ContactListener.h"
#include "cocos2d.h"

#define BALL_TO_WALL 1
#define BALL_TO_BRICK 2
#define PADDLE_TO_PACK 3
#define PADDLE_TO_WALL 4
#define PADDLE_TO_BALL 5


void ContactListener::BeginContact(b2Contact* contact)
{
	//碰撞开始时的回调方法
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
		if ((preFixA == 'Q' || preFixB == 'Q') && (preFixA == 'W' || preFixB == 'W'))//球与墙的碰撞
			newEvent = Strategy(BALL_TO_WALL, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'Q' || preFixB == 'Q') && (preFixA == 'B' || preFixB == 'B'))//球与砖块的碰撞
			newEvent = Strategy(BALL_TO_BRICK, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'A' || preFixB == 'A'))//挡板与包裹的碰撞
			newEvent = Strategy(PADDLE_TO_PACK, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'W' || preFixB == 'W'))//挡板与墙的碰撞
			newEvent = Strategy(PADDLE_TO_WALL, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'Q' || preFixB == 'Q'))//挡板与球的碰撞
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


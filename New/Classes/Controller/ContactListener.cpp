#include "ContactListener.h"

#define BALL_TO_WALL 1
#define BALL_TO_BRICK 2
#define PADDLE_TO_PACK 3
#define PADDLE_TO_WALL 4
#define PADDLE_TO_BALL 5

EventHandler* ContactListener::createStrategy(int EventType, b2Body* bodyA, b2Body* bodyB, b2Contact* _contact, GameLayer* _thisLayer, ObjManager* objManager)
{
	EventHandler *newStrategy = NULL;
	switch (EventType)
	{
	case 1:
		newStrategy = new BallToWall(bodyA, bodyB, _contact, _thisLayer, objManager);
		break;
	case 2:
		newStrategy = new BallToBrick(bodyA, bodyB, _contact, _thisLayer, objManager);
		break;
	case 3:
		newStrategy = new PaddleToPack(bodyA, bodyB, _contact, _thisLayer, objManager);
		break;
	case 4:
		newStrategy = new PaddleToWall(bodyA, bodyB, _contact, _thisLayer, objManager);
		break;
	case 5:
		newStrategy = new PaddleToBall(bodyA, bodyB, _contact, _thisLayer, objManager);
		break;
	}
	return newStrategy;
}

void ContactListener::BeginContact(b2Contact* contact)
{
	isBrick = false;
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
			newEvent = createStrategy(BALL_TO_WALL, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'Q' || preFixB == 'Q') && (preFixA == 'B' || preFixB == 'B'))//球与砖块的碰撞
		{
			isBrick = true;
			newEvent = createStrategy(BALL_TO_BRICK, bodyA, bodyB, contact, thisLayer, objManager);
		}

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'A' || preFixB == 'A'))//挡板与包裹的碰撞
			newEvent = createStrategy(PADDLE_TO_PACK, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'W' || preFixB == 'W'))//挡板与墙的碰撞
			newEvent = createStrategy(PADDLE_TO_WALL, bodyA, bodyB, contact, thisLayer, objManager);

		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'Q' || preFixB == 'Q'))//挡板与球的碰撞
			newEvent = createStrategy(PADDLE_TO_BALL, bodyA, bodyB, contact, thisLayer, objManager);

		newEvent->doStrategy();
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	if (objManager->getBallPermeat()&&isBrick)
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


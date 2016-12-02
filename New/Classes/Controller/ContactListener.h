#ifndef  _ContactController_H_
#define  _ContactController_H_
#include "cocos2d.h"
#include "Beginlayer.h"
#include "EventHandler.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

class ContactListener : public b2ContactListener
{
public:
	EventHandler *Strategy(int EventType, b2Body* bodyA, b2Body* bodyB, b2Contact* _contact, Beginlayer* _thisLayer, BallObj* _ball, PaddleObj* _paddle);  //创建策略

	Beginlayer*  thisLayer;
	BallObj* ball;
	PaddleObj* paddle;
	b2Vec2 ballVec;
	void setBall(BallObj* _ball)
	{
		ball = _ball;
	}
	ContactController(Beginlayer*  _thisLayer, BallObj* _ball, PaddleObj* _paddle)
	{
		thisLayer = _thisLayer;
		ball = _ball;
		paddle = _paddle;
	}
	b2WorldManifold* pos;//记录碰撞点的指针

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

EventHandler* ContactListener::Strategy(int EventType, b2Body* bodyA, b2Body* bodyB, b2Contact* _contact, Beginlayer* _thisLayer, BallObj* _ball, PaddleObj* _paddle)
{
	EventHandler *newStrategy = NULL;
	switch (EventType)
	{
	case 1:
		newStrategy = new BallToWall(bodyA, bodyB, _contact, _thisLayer, _ball, _paddle);
		break;
	case 2:
		newStrategy = new BallToBrick(bodyA, bodyB, _contact, _thisLayer, _ball, _paddle);
		break;
	case 3:
		newStrategy = new PaddleToPack(bodyA, bodyB, _contact, _thisLayer, _ball, _paddle);
		break;
	case 4:
		newStrategy = new PaddleToWall(bodyA, bodyB, _contact, _thisLayer, _ball, _paddle);
		break;
	case 5:
		newStrategy = new PaddleToBall(bodyA, bodyB, _contact, _thisLayer, _ball, _paddle);
		break;
	}
	return newStrategy;
}
#endif

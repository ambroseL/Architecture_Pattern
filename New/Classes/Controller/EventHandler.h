#ifndef  _EventHandler_H_
#define  _EventHandler_H_
#include "cocos2d.h"
#include "Beginlayer.h"
#include <Box2D/Box2D.h>

#define PACK 1
#define BRICK 2
#define SOUND 3

using namespace cocos2d;

struct eventObj
{
	eventObj(int eventtype, int hp, std::string id)
	{
		eventType = eventtype;
		HP = hp;
		Id = id;
	}
	int eventType;
	int HP;
	std::string Id;
};
class EventHandler
{
public:
	virtual void doStrategy() {};
	EventHandler(b2Body* body_A, b2Body* body_B, b2Contact* _contact, Beginlayer* _thisLayer, BallObj* _ball, PaddleObj* _paddle)
	{
		bodyA = body_A;
		bodyB = body_B;
		contact = _contact;
		thisLayer = _thisLayer;
		ball = _ball;
		paddle = _paddle;
	}
	static std::vector<eventObj*> eventQueue;
protected:
	BallObj* ball;
	PaddleObj* paddle;
	b2Body* bodyA;
	b2Body* bodyB;
	b2Contact* contact;
	Beginlayer*  thisLayer;


};

class BallToBrick : public EventHandler  //球与砖块的策略类
{
public:
	virtual void doStrategy();
	BallToBrick(b2Body* body_A, b2Body* body_B, b2Contact* _contact, Beginlayer* _thisLayer, BallObj* _ball, PaddleObj* _paddle)
		: EventHandler(body_A, body_B, _contact, _thisLayer, _ball, _paddle) {};

};

class BallToWall : public EventHandler  //球与墙的策略类
{
public:
	virtual void doStrategy();
	BallToWall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, Beginlayer* _thisLayer, BallObj* _ball, PaddleObj* _paddle)
		: EventHandler(body_A, body_B, _contact, _thisLayer, _ball, _paddle) {};

};

class PaddleToPack : public EventHandler  //挡板与包裹的策略类
{
public:
	virtual void doStrategy();
	PaddleToPack(b2Body* body_A, b2Body* body_B, b2Contact* _contact, Beginlayer* _thisLayer, BallObj* _ball, PaddleObj* _paddle)
		: EventHandler(body_A, body_B, _contact, _thisLayer, _ball, _paddle) {};

};

class PaddleToWall : public EventHandler  //挡板与墙的策略类
{
public:
	virtual void doStrategy();
	PaddleToWall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, Beginlayer* _thisLayer, BallObj* _ball, PaddleObj* _paddle)
		: EventHandler(body_A, body_B, _contact, _thisLayer, _ball, _paddle) {};

};

class PaddleToBall : public EventHandler  //挡板与球的策略类
{
public:
	virtual void doStrategy();
	PaddleToBall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, Beginlayer* _thisLayer, BallObj* _ball, PaddleObj* _paddle)
		: EventHandler(body_A, body_B, _contact, _thisLayer, _ball, _paddle) {};

};
#endif

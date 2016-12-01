#ifndef  _EventHandler_H_
#define  _EventHandler_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h""
#include "GameLayer.h"
#include "ObjManager.h"

using namespace cocos2d;

#define PACK 1
#define BRICK 2
#define SOUND 3

using namespace cocos2d;
using namespace std;


class EventHandler
{
public:
	virtual void doStrategy() {};
	EventHandler(b2Body* body_A, b2Body* body_B, b2Contact* _contact, GameLayer* _thisLayer, ObjManager* objManager):
	bodyA(body_A),bodyB(body_B),contact(_contact),thisLayer(_thisLayer),objManager(objManager){}
	

protected:
	
	b2Body* bodyA;
	b2Body* bodyB;
	b2Contact* contact;
	GameLayer*  thisLayer;
	ObjManager* objManager;
};



class BallToBrick : public EventHandler  //球与砖块的策略类
{
public:
	virtual void doStrategy();
	BallToBrick(b2Body* body_A, b2Body* body_B, b2Contact* _contact, GameLayer* _thisLayer, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, _thisLayer,objManager) {};

};

class BallToWall : public EventHandler  //球与墙的策略类
{
public:
	virtual void doStrategy();
	BallToWall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, GameLayer* _thisLayer, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, _thisLayer, objManager) {};

};

class PaddleToPack : public EventHandler  //挡板与包裹的策略类
{
public:
	virtual void doStrategy();
	PaddleToPack(b2Body* body_A, b2Body* body_B, b2Contact* _contact, GameLayer* _thisLayer, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, _thisLayer, objManager) {};

};

class PaddleToWall : public EventHandler  //挡板与墙的策略类
{
public:
	virtual void doStrategy();
	PaddleToWall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, GameLayer* _thisLayer, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, _thisLayer, objManager) {};

};

class PaddleToBall : public EventHandler  //挡板与球的策略类
{
public:
	virtual void doStrategy();
	PaddleToBall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, GameLayer* _thisLayer, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, _thisLayer, objManager) {};

};
#endif

#ifndef  _EventHandler_H_
#define  _EventHandler_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h""
#include "GameLayer.h"
#include "ObjManager.h"

using namespace cocos2d;
using namespace std;

/**
* 碰撞事件类
*
*#include "cocos2d.h" <BR>
*#include "GameLayer.h"
*#include "ObjManager.h"
*-llib
*
* 碰撞策略类的基类，包括碰撞时的物理部件
*
* @seesomething
*/
class EventHandler
{
public:
	/**
	*执行策略函数
	*/
	virtual void doStrategy() {};
	EventHandler(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager):
	bodyA(body_A),bodyB(body_B),contact(_contact),thisLayer(_thisLayer),objManager(objManager){}
	

protected:

	b2Body* bodyA;				/* 碰撞刚体A */

	b2Body* bodyB;				/* 碰撞刚体B */

	b2Contact* contact;			/* 碰撞点 */

	ObjManager* objManager;		/* 物体管理器 */
};


/**
* 碰撞策略类
*
*
* EventHandler类的派生类
* 碰撞发生时对不同类型碰撞的处理
*
* @seesomething
*/

/**
*球与砖块的策略类
*/
class BallToBrick : public EventHandler
{
public:
	virtual void doStrategy();
	BallToBrick(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};

/**
*球与墙的策略类
*/
class BallToWall : public EventHandler
{
public:
	virtual void doStrategy();
	BallToWall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};

/**
*挡板与包裹的策略类
*/
class PaddleToPack : public EventHandler
{
public:
	virtual void doStrategy();
	PaddleToPack(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};

/**
*挡板与墙的策略类
*/
class PaddleToWall : public EventHandler
{
public:
	virtual void doStrategy();
	PaddleToWall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};

/**
*挡板与球的策略类
*/
class PaddleToBall : public EventHandler
{
public:
	virtual void doStrategy();
	PaddleToBall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};
#endif

#ifndef  _ContactController_H_
#define  _ContactController_H_
#include "cocos2d.h"
#include "EventHandler.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;
/**
* 碰撞监听类
*
*#include "cocos2d.h" <BR>
*#include "EventHandler.h"
*-llib
*
* 监听碰撞的发生，包括创建策略函数、开始碰撞函数和结束碰撞函数
* 创建策略函数，对不同的碰撞类型创建不同的策略
* 开始碰撞函数，碰撞开始时的方法
* 开始碰撞函数，碰撞结束时的方法
*
* @seesomething
*/
class ContactListener : public b2ContactListener
{
public:
	/**
	*创建策略函数
	*/
	EventHandler* createStrategy(int EventType, b2Body* bodyA, b2Body* bodyB, b2Contact* _contact, ObjManager* objManager);  //创建策略

	/**
	*构造函数
	*/
	ContactListener(ObjManager* objManager):objManager(objManager)
	{
		
	}
	b2WorldManifold* pos;//记录碰撞点的指针

	/**
	*开始碰撞函数
	*/
	void BeginContact(b2Contact* contact);

	/**
	*结束碰撞函数
	*/
	void EndContact(b2Contact* contact);

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private:

	bool isBrick;					/* 球是否碰撞到砖块的指示器 */

	ObjManager* objManager;			/* 物体管理器 */

	b2Vec2 ballVec;					/* 球的方向 */
};
#endif

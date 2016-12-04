#ifndef  _ContactController_H_
#define  _ContactController_H_
#include "cocos2d.h"
#include "EventHandler.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

class ContactListener : public b2ContactListener
{
	GameLayer*  thisLayer;
	ObjManager* objManager;
	b2Vec2 ballVec;

public:

	EventHandler* createStrategy(int EventType, b2Body* bodyA, b2Body* bodyB, b2Contact* _contact, GameLayer* _thisLayer, ObjManager* objManager);  //创建策略


	ContactListener(GameLayer* _thisLayer, ObjManager* objManager):thisLayer(_thisLayer),objManager(objManager)
	{
		
	}
	b2WorldManifold* pos;//记录碰撞点的指针

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private:
	bool isBrick;
};
#endif

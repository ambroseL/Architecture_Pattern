#ifndef  _MyContactListener_H_
#define  _MyContactListener_H_
#include "cocos2d.h"
#include "Beginlayer.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

class MyContactListener : public b2ContactListener
{
public:
	Beginlayer*  hl;
	MyContactListener(Beginlayer*  hlIn)
	{
		hl = hlIn;
	}
	b2WorldManifold* pos;//记录碰撞点的指针
	static bool isChange;
	static bool isFast;
	static b2Body* body;
	static b2Vec2 body_vec;
	static b2Body* ball_body;
	static b2Vec2 ball_vec;
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};


#endif

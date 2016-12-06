#ifndef  _EventHandler_H_
#define  _EventHandler_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h""
#include "GameLayer.h"
#include "ObjManager.h"

using namespace cocos2d;
using namespace std;

/**
* ��ײ�¼���
*
*#include "cocos2d.h" <BR>
*#include "GameLayer.h"
*#include "ObjManager.h"
*-llib
*
* ��ײ������Ļ��࣬������ײʱ��������
*
* @seesomething
*/
class EventHandler
{
public:
	/**
	*ִ�в��Ժ���
	*/
	virtual void doStrategy() {};
	EventHandler(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager):
	bodyA(body_A),bodyB(body_B),contact(_contact),thisLayer(_thisLayer),objManager(objManager){}
	

protected:

	b2Body* bodyA;				/* ��ײ����A */

	b2Body* bodyB;				/* ��ײ����B */

	b2Contact* contact;			/* ��ײ�� */

	ObjManager* objManager;		/* ��������� */
};


/**
* ��ײ������
*
*
* EventHandler���������
* ��ײ����ʱ�Բ�ͬ������ײ�Ĵ���
*
* @seesomething
*/

/**
*����ש��Ĳ�����
*/
class BallToBrick : public EventHandler
{
public:
	virtual void doStrategy();
	BallToBrick(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};

/**
*����ǽ�Ĳ�����
*/
class BallToWall : public EventHandler
{
public:
	virtual void doStrategy();
	BallToWall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};

/**
*����������Ĳ�����
*/
class PaddleToPack : public EventHandler
{
public:
	virtual void doStrategy();
	PaddleToPack(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};

/**
*������ǽ�Ĳ�����
*/
class PaddleToWall : public EventHandler
{
public:
	virtual void doStrategy();
	PaddleToWall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};

/**
*��������Ĳ�����
*/
class PaddleToBall : public EventHandler
{
public:
	virtual void doStrategy();
	PaddleToBall(b2Body* body_A, b2Body* body_B, b2Contact* _contact, ObjManager* objManager)
		: EventHandler(body_A, body_B, _contact, objManager) {};

};
#endif

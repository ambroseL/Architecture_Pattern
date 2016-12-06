#ifndef  _ContactController_H_
#define  _ContactController_H_
#include "cocos2d.h"
#include "EventHandler.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;
/**
* ��ײ������
*
*#include "cocos2d.h" <BR>
*#include "EventHandler.h"
*-llib
*
* ������ײ�ķ����������������Ժ�������ʼ��ײ�����ͽ�����ײ����
* �������Ժ������Բ�ͬ����ײ���ʹ�����ͬ�Ĳ���
* ��ʼ��ײ��������ײ��ʼʱ�ķ���
* ��ʼ��ײ��������ײ����ʱ�ķ���
*
* @seesomething
*/
class ContactListener : public b2ContactListener
{
public:
	/**
	*�������Ժ���
	*/
	EventHandler* createStrategy(int EventType, b2Body* bodyA, b2Body* bodyB, b2Contact* _contact, ObjManager* objManager);  //��������

	/**
	*���캯��
	*/
	ContactListener(ObjManager* objManager):objManager(objManager)
	{
		
	}
	b2WorldManifold* pos;//��¼��ײ���ָ��

	/**
	*��ʼ��ײ����
	*/
	void BeginContact(b2Contact* contact);

	/**
	*������ײ����
	*/
	void EndContact(b2Contact* contact);

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private:

	bool isBrick;					/* ���Ƿ���ײ��ש���ָʾ�� */

	ObjManager* objManager;			/* ��������� */

	b2Vec2 ballVec;					/* ��ķ��� */
};
#endif

#ifndef _PhysicsComponent_H_
#define _PhysicsComponent_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

/**
* ��������
*
*#include "cocos2d.h" <BR>
*#include "Box2D/Box2D.h"
*
*-llib
*
* EntityObj����ɲ���
* ����������ײ���ٶȱ仯�������¼�������������
* @seesomething
*/


#define pixToMeter 5     //���弸������Ϊ1��

class PhysicsComponent 
{
	b2Body* body;	/* ���� */

public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	PhysicsComponent();

	/**
	*���ι��캯��
	*
	*@param phyBody ����
	*/
	PhysicsComponent(b2Body* phyBody);

	/**
	*�������캯��
	*@param physicsComponent
	*/
	PhysicsComponent(PhysicsComponent& physicsComponent);

	/**
	*��������
	*/
	~PhysicsComponent();

	/**
	*��¡���������
	*/
	PhysicsComponent* Clone();

	//�����

	void setSize(float fWidth, float fHeight); //���ø�������ű�

	//�����Դ�ȡ

	/**
	*��ȡ��������
	*/
	b2Body* getBody();

	/**
	*���ò�������
	*@param phyBody ����
	*/
	void setBody(b2Body* phyBody);
	
	/**
	*��ȡ�����ٶ�
	*/
	const b2Vec2 getSpeed();

	/**
	*���ò����ٶ�
	*@param fSpeed �ٶ�
	*/
	void setSpeed(b2Vec2 fSpeed);

};


//��������

/**
*��������
*@param type ��������
*@param shape ��״
*@param id ID
*@param world ������������
*@param data ��ȸ߶ȵȹ�������
*@param density �ܶ�
*@param friction Ħ��ϵ��
*@param restitution �ָ�ϵ��
*@param groupIndex ��������Ϊ����ʱ��ͬ�����岻������ײ��Ϊ����ʱ��������ײ
*@param categoryBits ��ײ���˻��Ʊ���,���ڶ����Լ���������ײ����,����Ϊ2�ı���
*@param maskBits ��ײ���˻��Ʊ���������,ָ����ײ����,ֵΪָ����ײ�����body��categoryBits֮��
*/
b2Body* createBody(int type, int shape, std::string* id, b2World* world, float* data, float density, float friction, float restitution, int groupIndex, int categoryBits, int maskBits);

/**
*���ò����ٶ�
*@param phyBody ����
*/
b2Body* copyBody(b2Body* phyBody);
#endif

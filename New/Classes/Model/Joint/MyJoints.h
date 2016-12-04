#ifndef _MyJoints_H_
#define _MyJoints_H_

#include "EntityObj.h"
#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;
/**
* ���ؽ���
*
*#include "EntityObj.h"
*#include "cocos2d.h"
*#include <Box2D/Box2D.h>
*
* �ṩ��겿����ģ��
*
* @seesomething
*/
class MyMouseJoint
{
	b2MouseJoint* mJoint;
	b2World* mWorld;
public:
	
	// ����������ڿ��ƺ������������������	

		MyMouseJoint():mJoint(nullptr),mWorld(nullptr){}

	  /**
	  *���ι��캯��
	  *@id �ؽ�id
	  *@world ����������������
	  *@collideConnected ���������
	  *@poA �������A
	  *@poB �������B
	  *@target ��ʼ��Ŀ��ê�㣨 poB����ĸ����ê�㣩
	  *@maxForce Լ������ʩ�Ӹ��ƶ���ѡ��������
	  *@frequencyHz ��Ӧ���ٶ�5.0f
	  *@dampingRatio ����	0-10.7f
	  */
	MyMouseJoint
	(
		std::string* id,								
		b2World* world,									
		EntityObj* poA,
		EntityObj* poB,
		b2Vec2 target,									
		float32 maxForce,								
		float32 frequencyHz,							
		float32 dampingRatio,
		bool collideConnected = true
	);

	
	/**
	*��������
	*/
	~MyMouseJoint();

	b2MouseJoint* getMouseJoint() const { return this->mJoint; };

};

/**
* ƽ�ƹؽ���
*
*#include "EntityObj.h"
*#include "cocos2d.h"
*#include <Box2D/Box2D.h>
*
* �ṩƽ�ƹؽڲ�����ģ��
*
* @seesomething
*/
class MyPrismaticJoint
{
	b2PrismaticJoint* mJoint;
	b2World* mWorld;
public:
	// ����������ڿ��ƺ������������������	

	/**
	*���ι��캯��
	*@world ����������������
	*@collideConnected ���������
	*@poA �������A
	*@poB �������B
	*@anchor ê��
	*@localAxisA ����
	*@referenceAngle Լ���Ƕ�
	*@enableLimit �Ƿ�������
	*@lowerTranslation ��С�任
	*@upperTranslation ���任
	*@enableMotor �Ƿ������
	*@motorSpeed ����ٶ�
	*@maxMotorForce �����,ע���������ʼ�����õ�
	*/
	MyPrismaticJoint
	(
		b2World* world,									
		bool collideConnected,
		EntityObj* poA,
		EntityObj* poB,
		b2Vec2 anchor,
		b2Vec2 localAxisA,								
		float32 referenceAngle,							
		bool enableLimit,								
		float32 lowerTranslation,						
		float32 upperTranslation,						
		bool enableMotor,								
		float32 motorSpeed,								
		float32 maxMotorForce							
	);

	/**
	*��������
	*/
	~MyPrismaticJoint();
};
#endif

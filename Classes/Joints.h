#ifndef _Joints_H_
#define _Joints_H_

#include "PhyObject.h"
#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

//���ؽ���
class MouseJoint
{
  public:
	b2MouseJoint* mJoint;
	b2World* mWorld;
	MouseJoint
	(
		std::string* id,//�ؽ�id
		b2World* world,//����������������
		bool collideConnected,
		PhyObject* poA,
		PhyObject* poB,
		b2Vec2 target,//��ʼ��Ŀ��ê�㣨 poB����ĸ����ê�㣩
		float32 maxForce,//Լ������ʩ�Ӹ��ƶ���ѡ��������
		float32 frequencyHz,//��Ӧ���ٶ�			5.0f
		float32 dampingRatio//����	0-1			0.7f
    );
	~MouseJoint();
};

//ƽ�ƹؽ���
class PrismaticJoint
{
public:
	b2PrismaticJoint* mJoint;
	b2World* mWorld;
	PrismaticJoint
		(
		b2World* world,//����������������
		bool collideConnected,
		PhyObject* poA,
		PhyObject* poB,
		b2Vec2 anchor,
		b2Vec2 localAxisA,//����
		float32 referenceAngle,//Լ���Ƕ�
		bool enableLimit,//�Ƿ�������
		float32 lowerTranslation,//��С�任
		float32 upperTranslation,//���任
		bool enableMotor,//�Ƿ������
		float32 motorSpeed,//����ٶ�
		float32 maxMotorForce//���  ��   	ע�⣬�������ʼ�����õġ�
		);
	~PrismaticJoint();
};
#endif

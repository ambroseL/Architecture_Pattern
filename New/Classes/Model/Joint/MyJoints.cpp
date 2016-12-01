#include "MyJoints.h"


MyMouseJoint::MyMouseJoint
(
	std::string* id,
	b2World* world,
	EntityObj* poA,
	EntityObj* poB,
	b2Vec2 target,
	float32 maxForce,
	float32 frequencyHz,
	float32 dampingRatio,
	bool collideConnected
)
{
	this->mWorld = world;
	b2MouseJointDef mjd;//�����ؽ�
	mjd.userData = id;//�����û�����
	mjd.collideConnected = collideConnected;
	mjd.bodyA = poA->getPhysicsComponent()->getBody();
	mjd.bodyB = poB->getPhysicsComponent()->getBody();

	//	target.x=target.x / pixToMeter;
	//	target.y=target.y / pixToMeter;
	mjd.target = target;

	mjd.maxForce = maxForce;
	mjd.frequencyHz = frequencyHz;
	mjd.dampingRatio = dampingRatio;

	mJoint = (b2MouseJoint*)world->CreateJoint(&mjd);//��������������������ؽ�
}

MyMouseJoint::~MyMouseJoint()
{
	if (mJoint != NULL)
	{
		mWorld->DestroyJoint(mJoint);
		mJoint = NULL;
	}
}

MyPrismaticJoint::MyPrismaticJoint
(
	b2World* world,//����������������

	bool collideConnected,

	EntityObj* poA,
	EntityObj* poB,
	b2Vec2 anchor,
	b2Vec2 localAxisA,//����
	float32 referenceAngle,//Լ���Ƕ�

	bool enableLimit,//�Ƿ�������
	float32 lowerTranslation,//��С�任
	float32 upperTranslation,//���任
	bool enableMotor,//�Ƿ������
	float32 motorSpeed,//����ٶ�
	float32 maxMotorForce//���  ��
)
{
	this->mWorld = world;

	b2PrismaticJointDef pjd;//�����ƶ��ؽ�

	pjd.collideConnected = collideConnected;

	anchor.x = anchor.x / pixToMeter;
	anchor.y = anchor.y / pixToMeter;
	localAxisA.Normalize();
	pjd.Initialize(poA->getPhysicsComponent()->getBody(), poB->getPhysicsComponent()->getBody(), anchor, localAxisA);//��ʼ��

	pjd.localAxisA = localAxisA;
	pjd.referenceAngle = referenceAngle;

	pjd.enableLimit = enableLimit;//�Ƿ�������
	pjd.lowerTranslation = lowerTranslation / pixToMeter;//��С
	pjd.upperTranslation = upperTranslation / pixToMeter;//���

	pjd.enableMotor = enableMotor;//�Ƿ������
	pjd.motorSpeed = motorSpeed;//����ٶ�
	pjd.maxMotorForce = maxMotorForce;//ʩ����

	mJoint = (b2PrismaticJoint*)world->CreateJoint(&pjd);//��������������������ؽ�
}

MyPrismaticJoint::~MyPrismaticJoint()
{
	if (mJoint != NULL)
	{
		mWorld->DestroyJoint(mJoint);
		mJoint = NULL;
	}
}


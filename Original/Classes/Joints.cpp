#include "Joints.h"


MouseJoint::MouseJoint
(
		std::string* id,//�ؽ�id
		b2World* world,//����������������
		bool collideConnected,

		PhyObject* poA,
		PhyObject* poB,
		b2Vec2 target,//��ʼ��Ŀ��ê�㣨 poB����ĸ����ê�㣩
		float32 maxForce,//Լ������ʩ�Ӹ��ƶ���ѡ��������
		float32 frequencyHz,//��Ӧ���ٶ�   	
		float32 dampingRatio//����	0-1		
)
{
	this->mWorld=world;
	b2MouseJointDef mjd;//�����ؽ�
	mjd.userData=id;//�����û�����
	mjd.collideConnected=collideConnected;
	mjd.bodyA=poA->body;
	mjd.bodyB=poB->body;

//	target.x=target.x / pixToMeter;
//	target.y=target.y / pixToMeter;
	mjd.target=target;

	mjd.maxForce=maxForce;
	mjd.frequencyHz=frequencyHz;
	mjd.dampingRatio=dampingRatio;

	mJoint=(b2MouseJoint*)world->CreateJoint(&mjd);//��������������������ؽ�
}

MouseJoint::~MouseJoint()
{
	if(mJoint!=NULL)
	{
		mWorld->DestroyJoint(mJoint);
		mJoint=NULL;
	}
}

PrismaticJoint::PrismaticJoint
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
float32 maxMotorForce//���  ��
)
{
	this->mWorld = world;

	b2PrismaticJointDef pjd;//�����ƶ��ؽ�

	pjd.collideConnected = collideConnected;

	anchor.x = anchor.x / pixToMeter;
	anchor.y = anchor.y / pixToMeter;
	localAxisA.Normalize();
	pjd.Initialize(poA->body, poB->body, anchor, localAxisA);//��ʼ��

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

PrismaticJoint::~PrismaticJoint()
{
	if (mJoint != NULL)
	{
		mWorld->DestroyJoint(mJoint);
		mJoint = NULL;
	}
}

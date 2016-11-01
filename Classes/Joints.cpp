#include "Joints.h"


MouseJoint::MouseJoint
(
		std::string* id,//关节id
		b2World* world,//物理层里的物理世界
		bool collideConnected,

		PhyObject* poA,
		PhyObject* poB,
		b2Vec2 target,//初始化目标锚点（ poB物体的刚体的锚点）
		float32 maxForce,//约束可以施加给移动候选体的最大力
		float32 frequencyHz,//响应的速度   	
		float32 dampingRatio//阻尼	0-1		
)
{
	this->mWorld=world;
	b2MouseJointDef mjd;//创建关节
	mjd.userData=id;//设置用户数据
	mjd.collideConnected=collideConnected;
	mjd.bodyA=poA->body;
	mjd.bodyB=poB->body;

//	target.x=target.x / pixToMeter;
//	target.y=target.y / pixToMeter;
	mjd.target=target;

	mjd.maxForce=maxForce;
	mjd.frequencyHz=frequencyHz;
	mjd.dampingRatio=dampingRatio;

	mJoint=(b2MouseJoint*)world->CreateJoint(&mjd);//在物理世界里增添这个关节
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
b2World* world,//物理层里的物理世界

bool collideConnected,

PhyObject* poA,
PhyObject* poB,
b2Vec2 anchor,
b2Vec2 localAxisA,//方向
float32 referenceAngle,//约束角度

bool enableLimit,//是否开启限制
float32 lowerTranslation,//最小变换
float32 upperTranslation,//最大变换
bool enableMotor,//是否开启马达
float32 motorSpeed,//马达速度
float32 maxMotorForce//马达  力
)
{
	this->mWorld = world;

	b2PrismaticJointDef pjd;//创建移动关节

	pjd.collideConnected = collideConnected;

	anchor.x = anchor.x / pixToMeter;
	anchor.y = anchor.y / pixToMeter;
	localAxisA.Normalize();
	pjd.Initialize(poA->body, poB->body, anchor, localAxisA);//初始化

	pjd.localAxisA = localAxisA;
	pjd.referenceAngle = referenceAngle;

	pjd.enableLimit = enableLimit;//是否开启限制
	pjd.lowerTranslation = lowerTranslation / pixToMeter;//最小
	pjd.upperTranslation = upperTranslation / pixToMeter;//最大

	pjd.enableMotor = enableMotor;//是否开启马达
	pjd.motorSpeed = motorSpeed;//马达速度
	pjd.maxMotorForce = maxMotorForce;//施加力

	mJoint = (b2PrismaticJoint*)world->CreateJoint(&pjd);//在物理世界里增添这个关节
}

PrismaticJoint::~PrismaticJoint()
{
	if (mJoint != NULL)
	{
		mWorld->DestroyJoint(mJoint);
		mJoint = NULL;
	}
}

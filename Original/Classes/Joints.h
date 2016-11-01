#ifndef _Joints_H_
#define _Joints_H_

#include "PhyObject.h"
#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

//鼠标关节类
class MouseJoint
{
  public:
	b2MouseJoint* mJoint;
	b2World* mWorld;
	MouseJoint
	(
		std::string* id,//关节id
		b2World* world,//物理层里的物理世界
		bool collideConnected,
		PhyObject* poA,
		PhyObject* poB,
		b2Vec2 target,//初始化目标锚点（ poB物体的刚体的锚点）
		float32 maxForce,//约束可以施加给移动候选体的最大力
		float32 frequencyHz,//响应的速度			5.0f
		float32 dampingRatio//阻尼	0-1			0.7f
    );
	~MouseJoint();
};

//平移关节类
class PrismaticJoint
{
public:
	b2PrismaticJoint* mJoint;
	b2World* mWorld;
	PrismaticJoint
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
		float32 maxMotorForce//马达  力   	注意，这个力是始终作用的。
		);
	~PrismaticJoint();
};
#endif

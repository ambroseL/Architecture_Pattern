#ifndef _MyJoints_H_
#define _MyJoints_H_

#include "EntityObj.h"
#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;
/**
* 鼠标关节类
*
*#include "EntityObj.h"
*#include "cocos2d.h"
*#include <Box2D/Box2D.h>
*
* 提供鼠标部件的模拟
*
* @seesomething
*/
class MyMouseJoint
{
	b2MouseJoint* mJoint;
	b2World* mWorld;
public:
	
	// 类的生命周期控制函数，包括构造和析构	

		MyMouseJoint():mJoint(nullptr),mWorld(nullptr){}

	  /**
	  *含参构造函数
	  *@id 关节id
	  *@world 物理层里的物理世界
	  *@collideConnected 关联标记量
	  *@poA 相关物体A
	  *@poB 相关物体B
	  *@target 初始化目标锚点（ poB物体的刚体的锚点）
	  *@maxForce 约束可以施加给移动候选体的最大力
	  *@frequencyHz 响应的速度5.0f
	  *@dampingRatio 阻尼	0-10.7f
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
	*析构函数
	*/
	~MyMouseJoint();

	b2MouseJoint* getMouseJoint() const { return this->mJoint; };

};

/**
* 平移关节类
*
*#include "EntityObj.h"
*#include "cocos2d.h"
*#include <Box2D/Box2D.h>
*
* 提供平移关节部件的模拟
*
* @seesomething
*/
class MyPrismaticJoint
{
	b2PrismaticJoint* mJoint;
	b2World* mWorld;
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*含参构造函数
	*@world 物理层里的物理世界
	*@collideConnected 关联标记量
	*@poA 相关物体A
	*@poB 相关物体B
	*@anchor 锚点
	*@localAxisA 方向
	*@referenceAngle 约束角度
	*@enableLimit 是否开启限制
	*@lowerTranslation 最小变换
	*@upperTranslation 最大变换
	*@enableMotor 是否开启马达
	*@motorSpeed 马达速度
	*@maxMotorForce 马达力,注意这个力是始终作用的
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
	*析构函数
	*/
	~MyPrismaticJoint();
};
#endif

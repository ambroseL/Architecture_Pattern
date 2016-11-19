#ifndef _PhysicsComponent_H_
#define _PhysicsComponent_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

/**
* 物理部件类
*
*#include "cocos2d.h" <BR>
*#include "Box2D/Box2D.h"
*
*-llib
*
* EntityObj的组成部分
* 负责物体碰撞，速度变化等物理事件和物理量管理
* @seesomething
*/


#define pixToMeter 5     //定义几个像素为1米

class PhysicsComponent 
{
	b2Body* body;	/* 刚体 */

public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	PhysicsComponent();

	/**
	*含参构造函数
	*
	*@param phyBody 刚体
	*/
	PhysicsComponent(b2Body* phyBody);

	/**
	*拷贝构造函数
	*@param physicsComponent
	*/
	PhysicsComponent(PhysicsComponent& physicsComponent);

	/**
	*析构函数
	*/
	~PhysicsComponent();

	/**
	*克隆函数，深拷贝
	*/
	PhysicsComponent* Clone();

	//类操作

	void setSize(float fWidth, float fHeight); //设置刚体的缩放比

	//类属性存取

	/**
	*获取部件刚体
	*/
	b2Body* getBody();

	/**
	*设置部件刚体
	*@param phyBody 刚体
	*/
	void setBody(b2Body* phyBody);
	
	/**
	*获取部件速度
	*/
	const b2Vec2 getSpeed();

	/**
	*设置部件速度
	*@param fSpeed 速度
	*/
	void setSpeed(b2Vec2 fSpeed);

};


//辅助函数

/**
*创建刚体
*@param type 刚体类型
*@param shape 形状
*@param id ID
*@param world 所在物理世界
*@param data 宽度高度等构造数据
*@param density 密度
*@param friction 摩擦系数
*@param restitution 恢复系数
*@param groupIndex 组索引，为正数时，同组物体不发生碰撞；为负数时，发生碰撞
*@param categoryBits 碰撞过滤机制变量,用于定义自己所属的碰撞种类,必须为2的倍数
*@param maskBits 碰撞过滤机制变量，掩码,指定碰撞种类,值为指定碰撞种类的body的categoryBits之和
*/
b2Body* createBody(int type, int shape, std::string* id, b2World* world, float* data, float density, float friction, float restitution, int groupIndex, int categoryBits, int maskBits);

/**
*设置部件速度
*@param phyBody 刚体
*/
b2Body* copyBody(b2Body* phyBody);
#endif

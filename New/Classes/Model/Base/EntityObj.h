#ifndef _EntityObj_H_
#define _EntityObj_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
using namespace cocos2d;
/**
* 实体物件类
*
*#include "cocos2d.h" <BR>
*#include "PhysicsComponent.h"
*#include "GraphicsComponent.h"
*-llib
*
* 所有model类的基类，存储物体的基本数据信息，包括物理部件和图像部件
* 物理部件负责物体碰撞，速度变化等物理事件和物理量管理
* 图像部件负责物体显示，大小图像等与渲染相关的事务管理
*
* @seesomething
*/
class EntityObj
{

public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	EntityObj();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/
	EntityObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*拷贝构造函数
	*@param entityObj 实体物件
	*/
	EntityObj(const EntityObj& entityObj);

	/**
	*析构函数
	*/
	virtual ~EntityObj();

	/**
	*克隆函数，深拷贝
	*/
	virtual EntityObj* Clone();

	//类操作

	/**
	*更新实体内容
	*/
	virtual void Update();

	//类属性存取

	/**
	*获取图像部件
	*/
	GraphicsComponent* getGraphicsComponent();

	/**
	*获取物理部件
	*/
	PhysicsComponent* getPhysicsComponent();

	/**
	*获取物体高度
	*图像部件和物理部件需分别设置
	*/
	const float getHeight();

	/**
	*获取物体宽度
	*图像部件和物理部件需分别设置
	*/
	const float getWidth();

	/**
	*设置物体高度
	*图像部件和物理部件需分别设置
	*@param fHeight 待设置的物体高度
	*/
	void setHeight(float fHeight);

	/**
	*设置物体宽度
	*图像部件和物理部件需分别设置
	*@param fWidth 待设置的物体宽度
	*/
	void setWidth(float fWidth);

	/**
	*获取物体实时速度
	*由物理部件实现
	*/
	const b2Vec2 getSpeed();

	/**
	*设置物体实时速度
	*由物理部件实现
	*@param fSpeed 待设置的物体速度
	*/
	void setSpeed(b2Vec2 fSpeed);

	/**
	*设置物体粒子
	*由图像部件实现
	*@param cps 待设置的粒子
	*/
	void setParticle(ParticleSystem* cps);

	/**
	*获取物体粒子
	*由图像部件实现
	*/
	ParticleSystem* getParticle();

	/**
	*获取物体ID
	*/
	const std::string* getID();

	/**
	*设置物体ID
	*/
	void setID(std::string* id);

	/**
	*设置物体位置
	*/
	void setPosition(b2Vec2 pos);

	/**
	*获取物体位置
	*/
	b2Vec2 getPosition();


	/**
	*设置贴图
	*@param texture 待设置的贴图
	*/
	void setTexture(CCTexture2D* texture);

protected:

	PhysicsComponent* physicsComponent;				/* 物理部件 */

	GraphicsComponent* graphicsComponent;			/* 图像部件 */

	std::string* id;								/* 物体id值 */
};

#endif
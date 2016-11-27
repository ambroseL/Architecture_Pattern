#ifndef _BrickObj_H_
#define _BrickObj_H_

#include "EntityObj.h"

/**
* 砖块实体类
*
*#include "cocos2d.h" <BR>
*include "PhysicsComponent.h" <BR>
*"GraphicsComponent.h" <BR>
*-llib
*
* 所有brick类的基类，存储砖块的基本数据信息，包括生命值
*
* @seesomething
*/
class BrickObj :
	public EntityObj
{
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	BrickObj();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体id
	*@param iHP 待设置的砖块生命值，默认为1
	*/
	BrickObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*析构函数
	*/
	~BrickObj();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;

	//类属性存取

	/**
	*获取砖块生命值
	*/
	const int getHP();

	/**
	*设置砖块生命值
	*/
	void setHP(int iHP);

protected:

	int HP;			/* 砖块生命值 */
};

#endif
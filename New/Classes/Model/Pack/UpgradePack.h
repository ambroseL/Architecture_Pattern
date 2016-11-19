#ifndef _UpgradePack_H_
#define _UpgradePack_H_

#include "PackObj.h"

/**
* 升级包裹类
*
*#include "PackObj.h" <BR>
*-llib
*
* 包裹实体类的子类，被挡板接住后，短时间内使球体攻击力上升一等级
*
* @seesomething
*/
class UpgradePack :public PackObj
{
public:

	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	UpgradePack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/
	UpgradePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*析构函数
	*/
	~UpgradePack();
};
#endif

#ifndef _PermeatPack_H_
#define _PermeatPack_H_

#include "PackObj.h"

/**
* 穿透包裹类
*
*#include "PackObj.h" <BR>
*-llib
*
* 包裹实体类的子类，被挡板接住后，将使球体短时间内处于无敌状态，
* 即破坏所有碰撞的砖块，且不发生反弹
*
* @seesomething
*/

class PermeatPack :public PackObj
{
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	PermeatPack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/
	PermeatPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*析构函数
	*/
	~PermeatPack();
};
#endif

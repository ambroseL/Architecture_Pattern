#ifndef _StickyPack_H_
#define _StickyPack_H_

#include "PackObj.h"

/**
* 粘黏包裹类
*
*#include "PackObj.h" <BR>
*-llib
*
* 包裹实体类的子类，被挡板接住后，将使球粘黏在挡板上，等待重新发射
*
* @seesomething
*/
class StickyPack :public PackObj
{
public:

	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	StickyPack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/
	StickyPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*析构函数
	*/
	~StickyPack();
};
#endif

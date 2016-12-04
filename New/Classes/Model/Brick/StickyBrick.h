#ifndef _StickyBrick_H_
#define _StickyBrick_H_

#include "BrickObj.h"

/**
* 粘黏砖块类
*
*#include "BrickObj.h" <BR>
*-llib
*
* 砖块实体类的子类，被击碎后产生穿透包裹
*
* @seesomething
*/
class StickyBrick: public BrickObj
{
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	StickyBrick();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param iHP 砖块生命值，默认为1
	*/
	StickyBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*析构函数
	*/
	~StickyBrick();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;
};
#endif

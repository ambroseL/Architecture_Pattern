#ifndef _LengthenPack_H_
#define _LengthenPack_H_

#include "PackObj.h"

/**
* 长度包裹类
*
*#include "PackObj.h" <BR>
*-llib
*
* 包裹实体类的子类，被挡板接住后，将使挡板增长或缩短
*
* @seesomething
*/
class LengthenPack :public PackObj
{
public:

	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	LengthenPack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param isLengthen 包裹长度属性值，默认为true
	*/
	LengthenPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*析构函数
	*/
	~LengthenPack();

	
};
#endif

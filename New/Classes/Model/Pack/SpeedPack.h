#ifndef _SpeedPack_H_
#define _SpeedPack_H_

#include "PackObj.h"

/**
* 速度包裹类
*
*#include "PackObj.h" <BR>
*-llib
*
* 包裹实体类的子类，被挡板接住后，将使球体短时间内加速或减速
*
* @seesomething
*/


class SpeedPack :public PackObj
{
	bool isFasten;	/* 速度属性值，为true表示加速包裹，否则为减速包裹 */
public:

	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	SpeedPack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param isFasten 待设置的包裹速度属性值，默认为true
	*/
	SpeedPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool isFasten=true);
	
	/**
	*析构函数
	*/
	~SpeedPack();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;

	//类属性存取

	/**
	*获取包裹速度属性值
	*/
	const bool getFasten();

	/**
	*设置包裹速度属性值
	*/
	void setFasten(bool isFasten);
};
#endif

#ifndef _LengthPack_H_
#define _LengthPack_H_

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
class LengthPack :public PackObj
{
	bool isLengthen;	/* 长度属性值，为true表示增长包裹，否则为缩短包裹 */
public:

	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	LengthPack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param isLengthen 包裹长度属性值，默认为true
	*/
	LengthPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool isLengthen = true);
	
	/**
	*析构函数
	*/
	~LengthPack();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;
	
	//类属性存取

	/**
	*获取包裹长度属性值
	*/
	const bool getLengthen();

	/**
	*设置包裹长度属性值
	*/
	void setLengthen(bool isLengthen);
};
#endif

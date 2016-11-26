#ifndef _ShortenPack_H_
#define _ShortenPack_H_
#include "PackObj.h"

/**
* 缩短包裹类
*
*#include "PackObj.h" <BR>
*-llib
*
* 包裹实体类的子类，被挡板接住后，将使挡板增长或缩短
*
* @seesomething
*/
class ShortenPack :public PackObj
{
public:// 类的生命周期控制函数，包括构造和析构	

	/**
    *默认构造函数	   
    *
	*/
	ShortenPack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/
	ShortenPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);


	/**
	*析构函数
	*/
	~ShortenPack();
};
#endif


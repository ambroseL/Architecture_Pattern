#ifndef _PaddleObj_H_
#define _PaddleObj_H_

#include "EntityObj.h"

/**
* 挡板实体类
*
*#include "cocos2d.h" <BR>
*include "PhysicsComponent.h" <BR>
*"GraphicsComponent.h" <BR>
*-llib
*
* 存储挡板的基本数据信息，包括各类状态属性值
*
* @seesomething
*/
class PaddleObj :public EntityObj
{
	bool isSticky;				/* 粘黏状态值 */
	bool isImage;				/* 镜像状态值 */
	bool isReversal;			/* 颠倒状态值 */
	float sHeight;				/* 挡板的初始半高度 */
	float sWidth;				/* 挡板的初始半宽度 */

public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	PaddleObj();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param bSticky 粘黏状态值，默认为false
	*@param bImage 镜像状态值，默认为false
	*@param bReversal 颠倒状态值，默认为false
	*/
	PaddleObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool bSticky = false, bool bImage = false, bool bReversal = false);
	
	/**
	*析构函数
	*/
	~PaddleObj();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;


	//类操作

	/**
	*重置函数，将挡板的所有属性值还原为默认值
	*/
	void Reset();

	//类属性存取

	/**
	*获取粘黏状态值
	*/
	const bool getSticky();

	/**
	*获取镜像状态值
	*/
	const bool getImage();

	/**
	*获取颠倒状态值
	*/
	const bool getReversal();

	/**
	*设置粘黏状态值
	*/
	void setSticky(bool bSticky);

	/**
	*设置镜像状态值
	*/
	void setImage(bool bImage);

	/**
	*设置镜像状态值
	*/
	void setReversal(bool bReversal);

	/**
	*获取初始高度
	*/
	const float getInitialHeight();

	/**
	*获取初始宽度
	*/
	const float getInitialWidth();
	
};

#endif
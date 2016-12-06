#ifndef  _UIController_H_
#define  _UIController_H_
#include "GameLayer.h"


/**
* UI控制类
*
*#include "GameLayer.h"
*-llib
*
* 控制场景中的UI逻辑，如生命值显示，音乐播放等
*
* @saysomething
*/
class UIController
{
	GameLayer* layer;						/* 控制的场景类 */

public:

	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	UIController();

	/**
	*析构函数
	*/
	~UIController();

	//类操作

	/**
	*播放音效
	*/
	void playYX();

	/**
	*更新生命显示精灵
	*/
	void updateLifeSprite(int HP);

	//类属性存取

	/**
	*设置场景
	*@parameter layer 待设置的场景
	*/
	void setLayer(GameLayer* layer);	
};

#endif

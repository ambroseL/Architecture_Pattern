#ifndef __MyHelpLayer_H__
#define __MyHelpLayer_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "StartLayer.h"
using namespace cocos2d;

/**
* 帮助场景类
*
*#include "cocos2d.h" <BR>
*#include "cocos2d.h"
*#include "SceneManager.h"
*#include "StartLayer.h"
*-llib
*
* 帮助场景显示游戏的玩法说明
*
* @seesomething
*/

class MyHelpLayer :public cocos2d::Layer
{
	SceneManager* gsm;
	Sprite* bgSprite;						/*  指向背景精灵的指针  */
	int currIntroIndex = 0;					/* 当前显示的索引 */
	StartLayer* wl;							/*  欢迎界面的指针  */

public:
	// 类的生命周期控制函数

	/**
	*初始化的方法，在create时会自动调用
	*cocos2dx机制
	*/
	bool init() override;
	CREATE_FUNC(MyHelpLayer);

	
	// 类操作

	/**
	*返回菜单的回调方法
	*@parameter pSender 回调函数自带默认参数
	*/
	void menueBack(cocos2d::Ref*  pSender);

	// 类属性存取
	/**
	*设置场景管理类
	*@parameter sceneManager 待设置的场景管理类
	*/
	void setSceneManager(SceneManager* sceneManager) { this->gsm = sceneManager; }
};
#endif

#ifndef  _SceneManager_H_
#define  _SceneManager_H_
#include "cocos2d.h"
using namespace cocos2d;
/**
* 场景管理类
*
* #include "cocos2d.h"
* -llib
* 管理场景间的创建，切换
* 纯策略类
*
* @seesomething
*/

class SceneManager
{
public:
	//类操作

	/**
	 *创建场景对象的方法
	 */
	void createScene();

	/**
	*去游戏场景的方法
	*/
	void gogameScene();

	/**
	 *去第二关的方法
	 */
	void goRound2Scene();

	/**
	 *去第三关的方法
	 */
	void goRound3Scene();

	/**
	 *第一关重新开始的方法
	 */
	void reStart();

	/**
	 *第二关重新开始的方法
	 */
	void reStart2();

	/**
	 *第三关重新开始的方法
	 */
	void reStart3();

	/**
	 *回欢迎场景的方法
	 */
	void goStartScene();

	/**
	 *去帮助场景
	 */
	void goHelpScene();;
};
#endif

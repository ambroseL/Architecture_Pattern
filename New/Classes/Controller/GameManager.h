#ifndef _GameManager_H_
#define _GameManager_H_
#include "cocos2d.h"
#include "GameLayer.h"
#include "SceneManager.h"
#include "UIController.h"
#include "MyJoints.h"
#include "ObjManager.h"
#include "globalObj.h"

/**
* 游戏管理类
*
* #include "GameManager.h"
* #include "SceneManager.h"
* #include "GameLayer.h"
* -llib
*
* 管理游戏运行时的总体逻辑，处理用户输入，场景更新
* 协调组合各控制类处理综合业务
*
* @seesomething
*/

class GameManager
{
	ObjManager* objManager;					/* model控制类 */
	
	SceneManager* sceneManager;			/* 场景控制类 */

	UIController* UIcontroller;				/* UI控制类 */

	int HP;									/* 玩家生命值 */

	bool isWin = false;						/* 本关卡是否胜利 */
	
	bool isPausable = false;				/* 暂停菜单能不能用 */

	bool isPause = false;					/* 是否暂停的标记 */			

	bool keyright = false;					/* 右键是否被按住 */

	bool keyleft = false;					/* 左键是否被按住 */

	MyMouseJoint* mj;						/* 鼠标关节 */

	GameLayer* layer;						/* 管理的当前layer */

public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	GameManager();

	/**
	*析构函数
	*/
	~GameManager();

	//类操作

	/**
	 *初始化各成员
	 */
	void init();									

	/**
	*初始化制指定场景和物理世界
	*@parameter layer 待初始化的场景
	*@parameter world 待初始化的物理世界
	*/
	void initLayer(GameLayer* layer, b2World* world);	//创建场景中的球与挡板

	/**
	 *创建指定场景的砖块
	 *@parameter layer 待创建砖块的场景
	 *@parameter world 待创建砖块的物理世界
	 */
	void createLayerBricks(GameLayer* layer, b2World* world) const; //创建场景中的砖块

	/**
	 *鼠标事件函数
	 *@parameter touch 触控类
	 *@parameter event 触控事件
	 */
	bool myOnTouchBegan(Touch *touch, Event *event); //开始触控事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event); //触控移动事件的处理方法
	void myOnTouchEnded(Touch *touch, Event *event); //触控结束事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event); //触控终止事件的处理方法

	/**
	 *键盘事件函数
	 *@parameter keycode 键盘按键
	 *@parameter event 键盘事件
	 */
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//按下键盘时的处理方法
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//松开键盘时的处理方法

	/**
	 *暂停游戏
	 */
	void toPause();

	/**
	*菜单暂停
	*/
	void menuePause();

	/**
	*进入下一游戏关卡
	*/
	void goNext();

	/**
	*菜单重设
	*/
	void menueReset();

	/**
	*作弊方法，强制切换至下一游戏关卡
	*/
	void toNext();

	/**
	*菜单返回
	*/
	void menueBack();

	/**
	*菜单继续
	*/
	void menueContinue();

	/**
	*菜单前往下一关
	*/
	void menueNext();

	/**
	*重玩游戏
	*/
	void restartGame();

	/**
	*游戏更新
	*/
	void Update();

	/**
	*播放声音
	*/
	void playSound();

	/**
	*清理待还原包裹列表
	*/
	void clearResetPack(char sid);

	/**
	*处理事件队列
	*/
	void handelEventQueue();

	/**
	*各类型包裹还原函数，delegate给objManger完成
	*/
	void resetAcceleratePack();

	void resetDeacceleratePack();

	void resetImagePack();

	void resetLengthenPack();

	void resetPermeatPack();

	void resetReversalPack();

	void resetShortenPack();

	void resetUpgradePack();

	//类属性存取

	/**
	 *获取物体管理类
	 */
	ObjManager* getObjManager() const { return this->objManager; }//创建场景中的砖块

	/**
	 *设置场景管理类
	 *@parameter manager 待设置的场景管理类
	 */
	void setSceneManager(SceneManager* manager);//创建场景中的砖块

	/**
	 *获取挡板精灵，delegate给objManager处理
	 */
	Sprite* getPaddelSprite() const;
};
#endif


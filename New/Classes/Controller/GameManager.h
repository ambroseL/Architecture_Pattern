#ifndef _GameManager_H_
#define _GameManager_H_
#include "cocos2d.h"
#include "GameLayer.h"
#include "SceneManager.h"
#include "UIController.h"
#include "MyJoints.h"
#include "ObjManager.h"
#include "globalObj.h"

class GameLayer;

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
	GameManager();
	~GameManager();

	void init();									//初始化各成员

	void initLayer(GameLayer* layer, b2World* world);	//创建场景中的球与挡板

	void createLayerBricks(GameLayer* layer, b2World* world) const; //创建场景中的砖块

	ObjManager* getObjManager() const { return this->objManager; }//创建场景中的砖块

	void setSceneManager(SceneManager* manager);//创建场景中的砖块

	//鼠标事件函数
	bool myOnTouchBegan(Touch *touch, Event *event); //开始触控事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event); //触控移动事件的处理方法
	void myOnTouchEnded(Touch *touch, Event *event); //触控结束事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event); //触控终止事件的处理方法

	//键盘事件函数
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//按下键盘时的处理方法
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//松开键盘时的处理方法

	void toPause();

	void menuePause();

	void goNext();

	void menueReset();

	void toNext();

	void menueBack();

	void menueContinue();

	void menueNext();

	void restartGame();

	void Update();

	void playSound();

	void clearResetPack(char sid);

	void handelEventQueue();

	//包裹还原函数，delegate给objManger完成
	void resetAcceleratePack();

	void resetDeacceleratePack();

	void resetImagePack();

	void resetLengthenPack();

	void resetPermeatPack();

	void resetReversalPack();

	void resetShortenPack();

	void resetUpgradePack();

	Sprite* getPaddelSprite() const;
};
#endif


#ifndef _GameManager_H_
#define _GameManager_H_
#include "cocos2d.h"
#include "ObjManager.h"
#include "GameSceneManager.h"
#include "Joints.h"

class GameManager
{
	ObjManager* objManager;
	
	GameSceneManager* sceneManager;
	int HP;									/* 玩家生命值 */

	int brickcount;							/* 需要打碎的砖块数量 */
	
	float speed;							/* 球的速度等级 */

	//std::vector<ObjEvent*> eventQueue;	/* 事件队列 */

	bool isWin = false;						/* 本关卡是否胜利 */

	static int level;						/* 关卡数 */

	bool isPause = false;					/* 是否暂停的标记 */

	bool isPauseEnble = true;				/* 暂停菜单能不能用 */

	bool keyright = false;					/* 右键是否被按住 */

	bool keyleft = false;					/* 左键是否被按住 */

	MouseJoint* mj;							/* 鼠标关节 */

public:
	GameManager();
	~GameManager();

	//鼠标事件函数
	bool myOnTouchBegan(Touch *touch, Event *event); //开始触控事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event); //触控移动事件的处理方法
	void myOnTouchEnded(Touch *touch, Event *event); //触控结束事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event); //触控终止事件的处理方法

	//键盘事件函数
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//按下键盘时的处理方法
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//松开键盘时的处理方法

	void Update(float delta);

};
#endif


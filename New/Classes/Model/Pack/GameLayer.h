#ifndef  _GameLayer_H_
#define  _GameLayer_H_

#include "cocos2d.h"
#include "Box2D/Dynamics/b2World.h"
#include "Joints.h"
#include "SceneManager.h"

using namespace cocos2d;
/**
* 主游戏场景类
*
*#include "cocos2d.h"
*#include "Box2D/Dynamics/b2World.h"
*#include "Joints.h"
*#include "SceneManager.h"
*-llib
*
*游戏的主场景，所有按钮及物体均为layer的child
*场景将定时调用更新函数以渲染游戏画面
*与逻辑相关的操作均以delegate的形式交给场景控制类处理
*
* @seesomething
*/
extern class GameManager;

class GameLayer: public Layer
{	
	GameManager* gameManager;
	SceneManager* sceneManager;
	
	b2World* world;//物理世界

	Sprite* lifeSp; //生命精灵
	Sprite* transparentBackgroundSp;//透明背景精灵
	Sprite* PauseSp;//暂停时弹出的木板

	int level;

	public:
	
	//更新数据
	void update(float delta);

	//初始化的方法
	bool init() override;

	//获取生命精灵
	Sprite* getLifeSprite() const;

	//物理模拟方法
	void step();

	void setBackgroundSprite(Sprite* dSp);

	void setPauseSprite(Sprite* dSp);

	void removePauseSprite();

	//鼠标事件函数
	bool myOnTouchBegan(Touch *touch, Event *event); //开始触控事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event); //触控移动事件的处理方法
	void myOnTouchEnded(Touch *touch, Event *event); //触控结束事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event); //触控终止事件的处理方法

	//键盘事件函数
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//按下键盘时的处理方法
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//松开键盘时的处理方法

	void toPause();

	//暂停菜单回调方法
	void menuePause(cocos2d::Ref*  pSender);

	//重来菜单回调方法
	void menueReset(cocos2d::Ref*  pSender);

	//回欢迎界面菜单回调方法
	void menueBack(cocos2d::Ref*  pSender);

	//继续菜单回调方法
	void menueContinue(cocos2d::Ref*  pSender);

	//下一关菜单回调方法
	void menueNext(cocos2d::Ref*  pSender);

	//过关时的方法
	void goNext();

	// 使用作弊键后去下一关的方法
	void toNext();

	void restartGame();

	//处理还原包裹
	void resetPack(float32 delta);

	//检查待还原队列
	void checkResetList();

	//播放碰撞时的音效
	void playSound();

	//获取当前关卡等级
	int getLevel() const { return level; }

	//设置当前关卡等级
	void setLevel(const int& level)  { this->level = level; }

	//设置当前的场景控制管理类
	void setSceneManager(SceneManager* sceneManager) { this->sceneManager = sceneManager; }

	//获取当前的场景控制管理类
	SceneManager* getSceneManager() const { return this->sceneManager; }
																	 
	CREATE_FUNC(GameLayer);//Cocos2d-x中定义的一个宏，创建指定类型的对象,并做好相应的初始化与释放工作
};
#endif

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
	
	b2World* world;//物理世界

	Sprite* lifeSp; //生命精灵
	Sprite* transparentBackgroundSp;//透明背景精灵
	Sprite* PauseSp;//暂停时弹出的木板

	int level = 1;

public:
	// 类的生命周期控制函数

	/**
	 *初始化的方法，在create时会自动调用
	 *cocos2dx机制
	 */
	bool init() override;

	/**
	*Cocos2d-x中定义的一个宏，创建指定类型的对象,并做好相应的初始化与释放工作
	*/
	CREATE_FUNC(GameLayer);

	//类操作
	
	/**
	*更新渲染场景
	*@parameter delta 更新间隔
	 */
	void update(float delta);

	/**
	*物理模拟方法
	*/
	void step();

	/**
	*鼠标事件函数
	*@parameter touch 触摸信息
	*@parameter event 触摸事件
	*/
	bool myOnTouchBegan(Touch *touch, Event *event); //开始触控事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event); //触控移动事件的处理方法
	void myOnTouchEnded(Touch *touch, Event *event); //触控结束事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event); //触控终止事件的处理方法

	/**
	*键盘事件函数
	*@parameter keycode 按键信息
	*@parameter event 键盘事件
	*/
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//按下键盘时的处理方法
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//松开键盘时的处理方法

	/**
	*暂停游戏
	*/
	void toPause();

	/**
	*暂停菜单回调方法
	*@pSender 回调函数自带默认参数
	*/
	void menuePause(cocos2d::Ref*  pSender);

	/**
	*重来菜单回调方法
	*@pSender 回调函数自带默认参数
	*/
	void menueReset(cocos2d::Ref*  pSender);

	/**
	*回欢迎界面菜单回调方法
	*@pSender 回调函数自带默认参数
	*/
	void menueBack(cocos2d::Ref*  pSender);

	/**
	*继续菜单回调方法
	*@pSender 回调函数自带默认参数
	*/
	void menueContinue(cocos2d::Ref*  pSender);

	/**
	*下一关菜单回调方法
	*@pSender 回调函数自带默认参数
	*/
	void menueNext(cocos2d::Ref*  pSender);

	/**
	*过关时的方法
	*/
	void goNext();

	/**
	*使用作弊键后去下一关的方法
	*/
	void toNext();

	/**
	*重启游戏
	*/
	void restartGame();

	/**
	*播放音乐
	*/
	void playSound();

	/**
	*delegate给gamemanager的包裹还原函数
	*@parameter delta 更新频率
	*/
	void resetLengthenPack(float delta);
	void resetShortenPack(float delta);
	void resetAcceleratePack(float delta);
	void resetDeacceleratePack(float delta);
	void resetReversalPack(float delta);
	void resetImagePack(float delta);
	void resetPermeatPack(float delta);
	void resetUpgradePack(float delta);

	//类属性存取

	/**
	*获取生命精灵
	*/
	Sprite* getLifeSprite() const;

	/**
	*移除暂停精灵
	*/
	void removePauseSprite();

	/**
	*获取当前关卡等级
	*/
	int getLevel() const { return level; }

	/**
	*设置当前关卡等级
	*/
	void setLevel(const int& level) { this->level = level; }

	/**
	*设置当前的场景控制管理类
	*@parameter sceneManager 待设置的场景管理类
	*/
	void setSceneManager(SceneManager* sceneManager) const;

	/**
	*设置包裹还原函数的定时器
	*@parameter sid 包裹类型
	*/
	void setPackresetschedule(char sid);

	/**
	*获取当前关卡等级
	*/
	void createBricks();

	/**
	*设置背景精灵
	*@parameter dSp 待设置的背景精灵
	*/
	void setBackgroundSprite(Sprite* dSp);

	/**
	*设置生命值显示精灵
	*@parameter dSp 待设置的生命值显示精灵
	*/
	void setPauseSprite(Sprite* dSp);
};
#endif

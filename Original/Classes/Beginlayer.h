#ifndef _Beginlayer_H_
#define _Beginlayer_H_
#include "cocos2d.h"
#include "Joints.h"
#include "Box2D/Box2D.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"
#include <vector>
using namespace cocos2d;
class Beginlayer : public Layer
{
public:
	b2World* world;//物理世界
	Size visibleSize;//可见区域尺寸
	Point origin;//原点坐标
	Sprite* backgroundsp;//背景精灵
	bool isWin = false;//本关卡是否胜利
	bool isPauseEnble = true;//暂停菜单能不能用
	GameSceneManager* gsm;//场景管理者的指针
	Welcomelayer* wl;//欢迎布景指针

	Sprite* lifeSp;//表示剩余次数
	Sprite* toumingBgSp;//透明背景精灵
	bool isPause = false;//是否暂停的标记
	Sprite* PauseSp;//暂停时弹出的木板
	void playYX();//播放音效的方法
	void toNext();//使用作弊键后去下一关的方法
	void setLevel(int cnt) { level = cnt; }
	static int level;//关卡数
	
	bool keyright = false;//右键是否被按住
	bool keyleft = false;//左键是否被按住

	//删除列表
	std::vector<ParticleFire*> listForFire;    //存需要删除的粒子效果
	std::vector<b2Body*> listDestroy;        //要销毁的刚体列表
	std::vector<std::string> listForDel;    //存需要删除的刚体ID

	//每个列表分类储存需要还原的包裹
	std::vector<std::string> listForPackL;//增长
	std::vector<std::string> listForPackB;//缩短
	std::vector<std::string> listForPackR;//颠倒
	std::vector<std::string> listForPackI;//镜像
	std::vector<std::string> listForPackA;//加速
	std::vector<std::string> listForPackD;//减速
	std::vector<std::string> listForPackU;//升级
	std::vector<std::string> listForPackF;//穿透

	std::map<std::string, PhyObject*> pom;   //存在物理世界里还存在的刚体ID和具体对象
	
	Paddle* paddle;//挡板的指针

	Ball* ball;//球的指针

	PhyObject* package;//包裹的指针

	Menu* pauseMenu;//暂停菜单的指针

	void toPause();

	int index;

	void judgePack(char sid, std::string* ids);//让包裹进入还原分类列表的方法
	//还原包裹效果的方法
	void L_Reset(float delta);
	void B_Reset(float delta);
	void R_Reset(float delta);
	void I_Reset(float delta);
	void A_Reset(float delta);
	void D_Reset(float delta);
	void U_Reset(float delta);
	void F_Reset(float delta);

	void Cut(float delta);//消除粒子的方法

	void RestartGame();

	//物理世界模拟
	void step();
	PhyObject* ground;

	//更新数据
	void update(float delta);

	//初始化的方法
	virtual bool init();

	//关闭菜单回调方法
	void menuClose(cocos2d::Ref*  pSender);

	//暂停菜单回调方法
	void menuPause(cocos2d::Ref*  pSender);

	//重来菜单回调方法
	void menuReset(cocos2d::Ref*  pSender);

	//继续菜单回调方法
	void menuContinue(cocos2d::Ref*  pSender);

	//回欢迎界面菜单回调方法
	void menuBack(cocos2d::Ref*  pSender);

	//下一关菜单回调方法
	void menuNext(cocos2d::Ref*  pSender);

	//过关时的方法
	void goNext();
	
	MouseJoint* mj;

	//鼠标事件函数
	bool myOnTouchBegan(Touch *touch, Event *event); //开始触控事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event); //触控移动事件的处理方法
	void myOnTouchEnded(Touch *touch, Event *event); //触控结束事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event); //触控终止事件的处理方法

	//键盘事件函数
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//按下键盘时的处理方法
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//松开键盘时的处理方法
	//~Beginlayer();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(Beginlayer);
};
#endif

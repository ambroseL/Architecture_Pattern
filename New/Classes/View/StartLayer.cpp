#include "StartLayer.h"
#include "SimpleAudioEngine.h"

StartLayer::~StartLayer()
{
}

//实现WelcomeLayer类中的init方法，初始化布景
bool StartLayer::init()
{
	//调用父类的初始化
	if (!Layer::init())
	{
		return false;
	}
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto titleSp = Sprite::create("Image/title.png");
	titleSp->setPosition(Point(visibleSize.width + origin.x - 300, visibleSize.height + origin.y - 270));
	titleSp->setScale(1.3f);
	this->addChild(titleSp, 1);
	//创建开始菜单项
	auto startItem = MenuItemImage::create
	(
		"Image/start1.png",	//平时的图片
		"Image/start2.png",	//选中时的图片
		CC_CALLBACK_1(StartLayer::menueStart, this) //点击时执行的回调方法
	);
	//设置开始菜单项的位置
	startItem->setPosition(
		Point(
			origin.x + visibleSize.width / 2 + 225,//X坐标
			origin.y + visibleSize.height / 2 - 120//Y坐标
		)
	);

	//创建菜单对象
	auto startMenu = Menu::create(startItem, NULL);
	//设置菜单位置
	startMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(startMenu, 1);

	//创建帮助菜单项
	auto helpItem = MenuItemImage::create
	(
		"Image/help1.png",	//平时的图片
		"Image/help2.png",	//选中时的图片
		CC_CALLBACK_1(StartLayer::menueHelp, this) //点击时执行的回调方法
	);

	//设置帮助菜单项的位置
	helpItem->setPosition(
		Point(
			origin.x + visibleSize.width / 2 + 225,	//X坐标
			origin.y + visibleSize.height / 2 - 200	//Y坐标
		)
	);
	//创建菜单对象
	auto helpMenu = Menu::create(helpItem, NULL);
	//设置菜单位置
	helpMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(helpMenu, 1);

	//创建退出菜单项
	auto exitItem = MenuItemImage::create
	(
		"Image/exit1.png",
		"Image/exit2.png",
		CC_CALLBACK_1(StartLayer::menueExit, this) //点击时执行的回调方法
	);
	exitItem->setPosition(
		Point(
			origin.x + visibleSize.width / 2 + 225,	//X坐标
			origin.y + visibleSize.height / 2 - 280		//Y坐标
		)
	);
	//创建菜单对象
	auto exitMenu = Menu::create(exitItem, NULL);
	//设置菜单位置
	exitMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(exitMenu, 1);

	//创建一个精灵对象，包含background.png图片
	auto bgSprite = Sprite::create("Image/background.png");
	//设置精灵对象的位置
	bgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//将精灵添加到布景中
	this->addChild(bgSprite, 0);

	// 预加载背景音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sound/bgm.mp3");
	//开始播放背景音乐，true表示循环
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/bgm.mp3", true);
	//设置音量0.0-1.0
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);

	return true;
}

void StartLayer::menueStart(cocos2d::Ref* pSender)
{
	gsm->gogameScene();
}

void StartLayer::menueHelp(cocos2d::Ref* pSender)
{
	gsm->goHelpScene();

}

void StartLayer::menueExit(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();//游戏结束
}


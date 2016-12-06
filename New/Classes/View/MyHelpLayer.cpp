#include "MyHelpLayer.h"// class implemented

/////////////// PUBLIC///////////////////////

bool MyHelpLayer::init()
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

	//创建返回菜单项
	auto backItem = MenuItemImage::create
	(
		"Image/back.png",	//平时的图片
		"Image/back1.png",	//选中时的图片
		CC_CALLBACK_1(MyHelpLayer::menueBack, this) //点击时执行的回调方法
	);
	//设置返回菜单项的位置
	backItem->setPosition(
		Point(
			origin.x + visibleSize.width - 40,	//X坐标
			origin.y + visibleSize.height - 40	//Y坐标
		)
	);
	backItem->setScale(0.25f);
	//创建菜单对象
	auto backMenu = Menu::create(backItem, NULL);
	//设置菜单位置
	backMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(backMenu, 1);

	//创建一个精灵对象，包含background.png图片
	auto bgSprite = Sprite::create("Image/backgroundhelp.png");
	//设置精灵对象的位置
	bgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//将精灵添加到布景中
	this->addChild(bgSprite, 0);

	return true;
}

//==============类的操作 =====================

void MyHelpLayer::menueBack(cocos2d::Ref*  pSender)
{
	gsm->goStartScene();
}

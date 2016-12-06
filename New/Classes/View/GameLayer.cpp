#include "GameLayer.h"
#include "SimpleAudioEngine.h"
//#include "ContactListener.h""
//#include "GameSceneManager.h"
#include "GameManager.h"
#include "ContactListener.h"

bool GameLayer::init()
{
	//调用父类的初始化
	if (!Layer::init())
	{
		return false;
	}

	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建背景精灵对象，包含background2.png图片
	auto bgSprite = Sprite::create("Image/background2.png");
	//设置精灵对象的位置
	bgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//将精灵添加到布景中
	this->addChild(bgSprite, -20);

	//创建暂停菜单项
	auto pauseItem = MenuItemImage::create
	(
		"Image/zanting_a.png",	//平时的图片
		"Image/zanting_b.png",	//选中时的图片
		CC_CALLBACK_1(GameLayer::menuePause, this) //点击时执行的回调方法
	);
	//设置暂停菜单项的位置
	pauseItem->setPosition
	(
		Point
		(
			origin.x + visibleSize.width - 40,	//X坐标
			origin.y + visibleSize.height - 40	//Y坐标
		)
	);

	//创建菜单对象
	auto pauseMenue = Menu::create(pauseItem, NULL);
	pauseMenue->setScale(1.0f);//设置菜单对象的缩放比
							  //设置菜单位置
	pauseMenue->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(pauseMenue, 2);

	auto hpSp = Sprite::create("Image/HP.png");
	//设置精灵对象的位置
	hpSp->setPosition(Point(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 40));
	hpSp->setScale(0.5f);
	//将精灵添加到布景中
	this->addChild(hpSp, 0);

	lifeSp = Sprite::create("Image/HP2.png");
	//设置精灵对象的位置
	lifeSp->setPosition(Point(origin.x + visibleSize.width - 130, origin.y + visibleSize.height - 40));
	lifeSp->setScale(0.6f);
	//将精灵添加到布景中
	this->addChild(lifeSp, 0);

	//预加载音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/eatprops.wav");

	//初始化物理世界
	//创建重力加速度向量
	b2Vec2 gravity(0.0f, 0.0f);
	//创建物理世界
	world = new b2World(gravity);
	//允许静止物体休眠
	world->SetAllowSleeping(true);
	
	gameManager = new GameManager();
	//初始化控制类
	gameManager->init();

	//创建挡板球体等物体
	gameManager->initLayer(this, world);

	//添加碰撞监听器
	world->SetContactListener(new ContactListener(this, this->gameManager->getObjManager()));

	//创建一个触摸监听
	auto touchListener = EventListenerTouchOneByOne::create();
	//设置下传触摸
	touchListener->setSwallowTouches(true);

	//开始触摸时回调onTouchBegan方法
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::myOnTouchBegan, this);
	//触摸移动时回调onTouchMoved方法
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::myOnTouchMoved, this);
	//抬起时回调onTouchEnded方法
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::myOnTouchEnded, this);
	//终止触摸时回调onTouchCancelled方法
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::myOnTouchCancelled, this);
	setTouchEnabled(true);
	//把监听器加入到挡板中
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, gameManager->getPaddelSprite());

	//创建一个键盘监听
	auto keyBoardListener = EventListenerKeyboard::create();
	//按下键盘时回调onKeyPressed方法
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);	
	//松开键盘时回调onKeyReleased方法
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	
	////调用更新
	//schedule(schedule_selector(GameLayer::update), 0.01f);

	//定时回调
	scheduleUpdate();
	
	return true;
}

Sprite* GameLayer::getLifeSprite() const
{
	return this->lifeSp;
}

void GameLayer::removePauseSprite()
{
	PauseSp->runAction(RemoveSelf::create(true));
	transparentBackgroundSp->runAction(RemoveSelf::create(true));
}

void GameLayer::setBackgroundSprite(Sprite* dSp)
{
	transparentBackgroundSp = dSp;
}

void GameLayer::setPauseSprite(Sprite* dSp)
{
	PauseSp = dSp;
}

bool GameLayer::myOnTouchBegan(Touch* touch, Event* event)
{
	return gameManager->myOnTouchBegan(touch, event);
}

void GameLayer::myOnTouchCancelled(Touch* touch, Event* event)
{
	gameManager->myOnTouchCancelled(touch, event);
}

void GameLayer::myOnTouchEnded(Touch* touch, Event* event)
{
	gameManager->myOnTouchEnded(touch, event);
}

void GameLayer::myOnTouchMoved(Touch* touch, Event* event)
{
	gameManager->myOnTouchMoved(touch, event);
}


void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	gameManager->onKeyPressed(keyCode, event);
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	gameManager->onKeyReleased(keyCode, event);
}

void GameLayer::step()
{
	//时间步进
	float32 timeStep = 2.0f / 60.0f;
	//速度迭代次数
	int32 velocityIterations = 6;
	//位置迭代次数
	int32 positionIterations = 2;
	//执行物理模拟
	world->Step(timeStep, velocityIterations, positionIterations);
}

void GameLayer::update(float delta)
{
	
	gameManager->Update();
	step();
}


void GameLayer::goNext()
{
	gameManager->goNext();
}

void GameLayer::menueBack(cocos2d::Ref*  pSender)
{
	gameManager->menueBack();
}

void GameLayer::menueContinue(cocos2d::Ref*  pSender)
{
	gameManager->menueContinue();
}

void GameLayer::menueNext(cocos2d::Ref*  pSender)
{
	gameManager->menueNext();
}

void GameLayer::menuePause(cocos2d::Ref*  pSender)
{
	gameManager->menuePause();
}

void GameLayer::menueReset(cocos2d::Ref*  pSender)
{
	gameManager->menueReset();
}

void GameLayer::restartGame()
{
	gameManager->restartGame();
}

void GameLayer::toNext()
{
	gameManager->toNext();
}

void GameLayer::toPause()
{
	gameManager->toPause();
}

void GameLayer::createBricks()
{
	gameManager->createLayerBricks(this, world);
}

void GameLayer::resetAcceleratePack(float delta)
{
	gameManager->resetAcceleratePack();
}

void GameLayer::resetDeacceleratePack(float delta)
{
	gameManager->resetDeacceleratePack();
}

void GameLayer::resetImagePack(float delta)
{
	gameManager->resetImagePack();
}

void GameLayer::resetLengthenPack(float delta)
{
	gameManager->resetLengthenPack();
}

void GameLayer::resetPermeatPack(float delta)
{
	gameManager->resetPermeatPack();
}

void GameLayer::resetReversalPack(float delta)
{
	gameManager->resetReversalPack();
}

void GameLayer::resetShortenPack(float delta)
{
	gameManager->resetShortenPack();
}

void GameLayer::resetUpgradePack(float delta)
{
	gameManager->resetUpgradePack();
}

void GameLayer::setPackresetschedule(char sid)
{
	switch (sid)
	{
	case 'L':
	{
		schedule(schedule_selector(GameLayer::resetLengthenPack), 7.0f, 0, 7.0f); 
		break;
	}
	case 'S':
	{
		schedule(schedule_selector(GameLayer::resetShortenPack), 7.0f, 0, 7.0f);
		break;
	}
	case 'A':
	{
		schedule(schedule_selector(GameLayer::resetAcceleratePack), 7.0f, 0, 7.0f);
		break;
	}
	case 'D':
	{
		schedule(schedule_selector(GameLayer::resetDeacceleratePack), 7.0f, 0, 7.0f);
		break;
	}
	case 'R':
	{
		schedule(schedule_selector(GameLayer::resetReversalPack), 7.0f, 0, 7.0f);
		break;
	}
	case 'I':
	{
		schedule(schedule_selector(GameLayer::resetImagePack), 7.0f, 0, 7.0f);
		break;
	}
	case 'F':
	{
		schedule(schedule_selector(GameLayer::resetPermeatPack), 7.0f, 0, 7.0f);
		break;
	}
	case 'U':
	{
		schedule(schedule_selector(GameLayer::resetUpgradePack), 7.0f, 0, 7.0f);
		break;
	}
	}
}

void GameLayer::playSound()
{
	gameManager->playSound();
}

void GameLayer::setSceneManager(SceneManager* sceneManager) const
{
	gameManager->setSceneManager(sceneManager);
}














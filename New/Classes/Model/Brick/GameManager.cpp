#include "GameManager.h"


GameManager::GameManager():mj(nullptr), layer(nullptr),objManager(nullptr),sceneManager(nullptr),UIcontroller(nullptr)
{
	isWin = false;
	keyright = false;
	keyleft = false;
	HP = 2;
}

GameManager::~GameManager()
{
}

void GameManager::init()
{	
	objManager = new ObjManager();
	UIcontroller = new UIController();
	sceneManager = new SceneManager();
}

void GameManager::initLayer(GameLayer* layer, b2World* world)
{
	this->layer = layer;
	objManager->createObj(world, layer);
	UIcontroller->setLayer(layer);
}

void GameManager::createLayerBricks(GameLayer* layer, b2World* world)
{
	objManager->createBricks(world, layer);
}


void GameManager::Update()
{
	if (isPause == true)
	{
		return;
	}
	
	b2Vec2 pos = objManager->getBallPos();
	if (pos.y * pixToMeter < -405.0)//如果球掉落屏幕底部
	{
		HP--;	
		if (HP > 0)
		{
			UIcontroller->updateLifeSprite(HP);
			objManager->stickyPackWork(); //等效于粘黏包裹
		}
		else //无生命值为0，游戏重新开始
		{
			sceneManager->reStart();
		}
		
	}//球掉落屏幕底部
	
	if (keyleft == true)											//如果左键被按住
		objManager->applyForce2Paddle(b2Vec2(-500.0f, 0.0f));
	if (keyright == true)											//如果右键被按住
		objManager->applyForce2Paddle(b2Vec2(500.0f, 0.0f));

	handelEventQueue();												//处理消息队列
	objManager->deleteObj();										//删除待删除物体
	objManager->updateObj();										//更新各物体
	if (objManager->getBrickCount() == 0)
		toNext();
}

bool GameManager::myOnTouchBegan(Touch* touch, Event* event)
{
	auto location = touch->getLocation();							//获取触控点的位置
	Size visibleSize = Director::getInstance()->getVisibleSize();	//获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();		//获取可见区域原点坐标
	b2Vec2 locationWorld = b2Vec2((location.x - origin.x - visibleSize.width / 2) / pixToMeter, (location.y - origin.y - visibleSize.height / 2) / pixToMeter);

	for (int i = 0; i<3; i++)
	{
		if (mj == nullptr)
		{
			objManager->setPaddleLinearDamping(0.0f);
			mj = new MyMouseJoint();
			mj = objManager->createMouseJoint(locationWorld, 10.0f, 0.0f);
			return true;
		}
	}
	return false;
}

void GameManager::myOnTouchMoved(Touch* touch, Event* event)
{
	auto location = touch->getLocation();//获取触控点的位置
	Size visibleSize = Director::getInstance()->getVisibleSize();//获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();//获取可见区域原点坐标
	b2Vec2 locationWorld = b2Vec2((location.x - origin.x - visibleSize.width / 2) / pixToMeter, (location.y - origin.y - visibleSize.height / 2) / pixToMeter);

	for (int i = 0; i < 3; i++)
	{
		if (mj != NULL)
		{
			mj->getMouseJoint()->SetTarget(locationWorld);
		}
	}

}

void GameManager::myOnTouchEnded(Touch* touch, Event* event)
{
	for (int i = 0; i < 3; i++)
	{
		if (mj != NULL)
		{
			b2Vec2 vLine(0.0, 0.0);
			mj->getMouseJoint()->GetBodyB()->SetLinearVelocity(vLine);
			delete mj;
			mj = nullptr;
		}
	}
}

void GameManager::myOnTouchCancelled(Touch* touch, Event* event)
{
	myOnTouchEnded(touch, event);
}

void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_SPACE == keyCode)
	{
		objManager->shootBall(); //发射球体
	}

	if (EventKeyboard::KeyCode::KEY_ESCAPE == keyCode)
	{
		toPause();
	}

	if (EventKeyboard::KeyCode::KEY_P == keyCode)//去下一关的作弊键
	{
		toNext();
	}

	if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keyCode)
	{
		keyleft = true;
	}

	if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keyCode)
	{
		keyright = true;
	}
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	bool pushLeftButton = EventKeyboard::KeyCode::KEY_LEFT_ARROW == keyCode;
	bool pushRightButton = EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keyCode;
	
	if (pushLeftButton || pushRightButton)
	{
		objManager->applyForce2Paddle(b2Vec2(0.0f, 0.0f));
		objManager->setPaddleVelocity(b2Vec2(0.0f, 0.0f));
		objManager->setPaddleLinearDamping(10.0f);
		if(pushLeftButton)
			keyleft = false;
		else
			keyright = false;

	}
}

void GameManager::toPause()
{
	//暂停所有定时器和动作
	layer->pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//当前不是暂停状态且未过关***********************
	{
		//获取可见区域尺寸
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取可见区域原点坐标
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//创建一个精灵对象，包含toumingBg.png图片
		Sprite* transparentBackgroundSp = Sprite::create("Image/toumingBg.png");
		//设置精灵对象的位置
		transparentBackgroundSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//将精灵添加到背景中
		layer->addChild(transparentBackgroundSp, 2);
		Sprite* PauseSp = Sprite::create("Image/suspend.png");//创建暂停后弹出的精灵
		PauseSp->setScale(0.6f);//设置精灵缩放比
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//设置精灵位置
		layer->addChild(PauseSp, 3);//将精灵添加到背景精灵中

		auto resetItem = MenuItemImage::create//创建重来菜单                      
		(
			"Image/restart.png",	//平时的图片
			"Image/restart1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueReset, layer) //点击时执行的回调方法
		);
		//设置重来菜单项的位置
		resetItem->setPosition
		(
			Point
			(
				origin.x - 450,//X坐标
				origin.y - 380	//Y坐标
			)
		);

		//创建重来菜单对象
		auto resetMenu = Menu::create(resetItem, NULL);
		resetMenu->setScale(0.3f);
		//设置菜单位置
		resetMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(resetMenu, 3);

		auto continueItem = MenuItemImage::create
		(
			"Image/continue.png",	//平时的图片
			"Image/continue1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueContinue, layer) //点击时执行的回调方法
		);
		//设置继续菜单项的位置
		continueItem->setPosition
		(
			Point
			(
				origin.x - 850,//X坐标
				origin.y - 380	//Y坐标
			)
		);

		//创建继续菜单对象
		auto continueMenu = Menu::create(continueItem, NULL);
		continueMenu->setScale(0.3f);
		//设置菜单位置
		continueMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(continueMenu, 3);

		//创建回欢迎界面菜单项
		auto backItem = MenuItemImage::create
		(
			"Image/back.png",	//平时的图片
			"Image/back1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueBack, layer) //点击时执行的回调方法
		);

		//设置回欢迎界面菜单项的位置
		backItem->setPosition
		(
			Point
			(
				origin.x - 50,//X坐标
				origin.y - 380	//Y坐标
			)
		);
		//创建菜单对象
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setScale(0.3f);
		//设置菜单位置
		backMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(backMenu, 3);

		PauseSp->runAction(Spawn::create(//创建一个同步执行动作对象并将其执行
			ScaleBy::create(0.6f, 1.67f, 2),//创建一个缩放动作对象
			RotateBy::create(0.6f, -360),//创建一个旋转动作对象
										 //RotateTo::create(0.5f,180),
			NULL));

		isPausable = false;//暂停菜单不可用
		layer->setPauseSprite(PauseSp);
		layer->setBackgroundSprite(transparentBackgroundSp);
	}
	else
	{
		isPause = false;
		isPausable = true;
	}
	isPause = false;
}

void GameManager::menuePause()
{

	//暂停所有定时器和动作
	layer->pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//当前不是暂停状态且未过关***********************
	{
		//获取可见区域尺寸
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取可见区域原点坐标
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//创建一个精灵对象，包含toumingBg.png图片
		Sprite* transparentBackgroundSp = Sprite::create("Image/toumingBg.png");

		//设置精灵对象的位置
		transparentBackgroundSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//将精灵添加到背景中
		layer->addChild(transparentBackgroundSp, 2);

		Sprite* PauseSp = Sprite::create("Image/suspend.png");//创建暂停后弹出的精灵
		PauseSp->setScale(0.6f);//设置精灵缩放比
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//设置精灵位置
		layer->addChild(PauseSp, 3);//将精灵添加到背景精灵中

		auto resetItem = MenuItemImage::create//创建重来菜单        
		(
			"Image/restart.png",	//平时的图片
			"Image/restart1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueReset, layer) //点击时执行的回调方法
		);
		//设置重来菜单项的位置
		resetItem->setPosition
		(
			Point
			(
				origin.x - 450,//X坐标
				origin.y - 380	//Y坐标
			)
		);

		//创建重来菜单对象
		auto resetMenu = Menu::create(resetItem, NULL);
		resetMenu->setScale(0.3f);
		//设置菜单位置
		resetMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(resetMenu, 3);

		auto continueItem = MenuItemImage::create
		(
			"Image/continue.png",	//平时的图片
			"Image/continue1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueContinue, layer) //点击时执行的回调方法
		);
		//设置继续菜单项的位置
		continueItem->setPosition
		(
			Point
			(
				origin.x - 850,//X坐标
				origin.y - 380	//Y坐标
			)
		);

		//创建继续菜单对象
		auto continueMenu = Menu::create(continueItem, NULL);
		continueMenu->setScale(0.3f);
		//设置菜单位置
		continueMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(continueMenu, 3);

		//创建回欢迎界面菜单项
		auto backItem = MenuItemImage::create
		(
			"Image/back.png",	//平时的图片
			"Image/back1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueBack, layer) //点击时执行的回调方法
		);

		//设置回欢迎界面菜单项的位置
		backItem->setPosition
		(
			Point
			(
				origin.x - 50,//X坐标
				origin.y - 380	//Y坐标
			)
		);
		//创建菜单对象
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setScale(0.3f);
		//设置菜单位置
		backMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(backMenu, 3);

		PauseSp->runAction(Spawn::create(//创建一个同步执行动作对象并将其执行
			ScaleBy::create(0.6f, 1.67f, 2),//创建一个缩放动作对象
			RotateBy::create(0.6f, -360),//创建一个旋转动作对象
										 //RotateTo::create(0.5f,180),
			NULL));
		isPausable = false;//暂停菜单不可用

		layer->setPauseSprite(PauseSp);
		layer->setBackgroundSprite(transparentBackgroundSp);
	}
	else
	{
		isPause = false;
		isPausable = true;
	}
	isPause = true;
}

void GameManager::goNext()
{

	//暂停所有定时器和动作
	layer->pauseSchedulerAndActions();
	if (isWin == true)//当前不是暂停状态且未过关***********************
	{
		
		//获取可见区域尺寸
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取可见区域原点坐标
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//创建一个精灵对象，包含toumingBg.png图片
		Sprite* transparentBackgroundSp = Sprite::create("Image/toumingBg.png");
		//设置精灵对象的位置
		transparentBackgroundSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		//将精灵添加到背景中
		layer->addChild(transparentBackgroundSp, 2);
		Sprite* PauseSp = Sprite::create("Image/suspend.png");//创建暂停后弹出的精灵
		PauseSp->setScale(0.6f);//设置精灵缩放比
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//设置精灵位置
		layer->addChild(PauseSp, 3);//将精灵添加到背景精灵中

		auto resetItem = MenuItemImage::create//创建重来菜单                
		(
			"Image/restart.png",	//平时的图片
			"Image/restart1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueReset, layer) //点击时执行的回调方法
		);
		//设置重来菜单项的位置
		resetItem->setPosition
		(
			Point
			(
				origin.x - 850,//X坐标
				origin.y - 380	//Y坐标
			)
		);

		//创建重来菜单对象
		auto resetMenu = Menu::create(resetItem, NULL);
		resetMenu->setScale(0.3f);
		//设置菜单位置
		resetMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(resetMenu, 3);

		auto nextItem = MenuItemImage::create
		(
			"Image/next.png",	//平时的图片
			"Image/next1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueNext, layer) //点击时执行的回调方法
		);
		//设置下一关菜单项的位置
		nextItem->setPosition
		(
			Point
			(
				origin.x - 450,//X坐标
				origin.y - 380	//Y坐标
			)
		);

		//创建下一关菜单对象
		auto nextMenu = Menu::create(nextItem, NULL);
		nextMenu->setScale(0.3f);
		//设置菜单位置
		nextMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(nextMenu, 3);

		//创建回欢迎界面菜单项
		auto backItem = MenuItemImage::create
		(
			"Image/back.png",	//平时的图片
			"Image/back1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueBack, layer) //点击时执行的回调方法
		);

		//设置回欢迎界面菜单项的位置
		backItem->setPosition
		(
			Point
			(
				origin.x - 50,//X坐标
				origin.y - 380	//Y坐标
			)
		);
		//创建菜单对象
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setScale(0.3f);
		//设置菜单位置
		backMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(backMenu, 3);

		PauseSp->runAction(Spawn::create(//创建一个同步执行动作对象并将其执行
			ScaleBy::create(0.6f, 1.67f, 2),//创建一个缩放动作对象
			RotateBy::create(0.6f, -360),//创建一个旋转动作对象
										 //RotateTo::create(0.5f,180),
			NULL));
		isPausable = false;//暂停菜单不可用

		layer->setPauseSprite(PauseSp);
		layer->setBackgroundSprite(transparentBackgroundSp);
	}
	else
	{
		isPause = false;
		isPausable = true;
	}
	isPause = true;
}

void GameManager::menueReset()
{

	if (layer->getLevel() == 1)
	{
		sceneManager->reStart();
	}
	else if (layer->getLevel() == 2)
	{
		sceneManager->reStart2();
	}
	else if (layer->getLevel() == 3)
	{
		sceneManager->reStart3();
	}
}

void GameManager::toNext()
{

	//卸载定时器
	layer->unscheduleAllSelectors();
	if (layer->getLevel() == 1)
	{
		sceneManager->goRound2Scene();
	}
	else if (layer->getLevel() == 2)
	{
		sceneManager->goRound3Scene();
	}
}

void GameManager::menueBack()
{

	//卸载定时器
	layer->unscheduleAllSelectors();
	SceneManager* sceneManager = layer->getSceneManager();
	sceneManager->goStartScene();
}

void GameManager::menueContinue()
{

	layer->removePauseSprite();
	isPause = false;
	isPausable = true;
	//恢复所有定时器和动作调用
	layer->resumeSchedulerAndActions();
}

void GameManager::menueNext()
{

	//卸载定时器
	layer->unscheduleAllSelectors();
	if (layer->getLevel() == 1)
	{
		sceneManager->goRound2Scene();
	}
	else if (layer->getLevel() == 2)
	{
		sceneManager->goRound3Scene();
	}
}

void GameManager::restartGame()
{

	//暂停所有定时器和动作
	layer->pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//当前不是暂停状态且未过关***********************
	{
		//获取可见区域尺寸
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取可见区域原点坐标
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//创建一个精灵对象，包含toumingBg.png图片
		Sprite* transparentBackgroundSp = Sprite::create("Image/toumingBg.png");
		//设置精灵对象的位置
		transparentBackgroundSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		//将精灵添加到背景中
		layer->addChild(transparentBackgroundSp, 2);


		Sprite* PauseSp = Sprite::create("Image/suspend.png");//创建暂停后弹出的精灵
		PauseSp->setScale(0.6f);//设置精灵缩放比
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//设置精灵位置
		layer->addChild(PauseSp, 3);//将精灵添加到背景精灵中

		auto resetItem = MenuItemImage::create//创建重来菜单           
		(
			"Image/restart.png",	//平时的图片
			"Image/restart1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueReset, layer) //点击时执行的回调方法
		);
		//设置重来菜单项的位置
		resetItem->setPosition
		(
			Point
			(
				origin.x - 700,//X坐标
				origin.y - 380	//Y坐标
			)
		);

		//创建重来菜单对象
		auto resetMenu = Menu::create(resetItem, NULL);
		resetMenu->setScale(0.3f);
		//设置菜单位置
		resetMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(resetMenu, 3);


		//创建回欢迎界面菜单项
		auto backItem = MenuItemImage::create
		(
			"Image/back.png",	//平时的图片
			"Image/back1.png",	//选中时的图片
			CC_CALLBACK_1(GameLayer::menueBack, layer) //点击时执行的回调方法
		);

		//设置回欢迎界面菜单项的位置
		backItem->setPosition
		(
			Point
			(
				origin.x - 200,//X坐标
				origin.y - 380	//Y坐标
			)
		);
		//创建菜单对象
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setScale(0.3f);
		//设置菜单位置
		backMenu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		PauseSp->addChild(backMenu, 3);

		PauseSp->runAction(Spawn::create(//创建一个同步执行动作对象并将其执行
			ScaleBy::create(0.6f, 1.67f, 2),//创建一个缩放动作对象
			RotateBy::create(0.6f, -360),//创建一个旋转动作对象
										 //RotateTo::create(0.5f,180),
			NULL));
		isPausable = false;//暂停菜单不可用

		layer->setPauseSprite(PauseSp);
		layer->setBackgroundSprite(transparentBackgroundSp);
	}
	isPause = true;
}

void GameManager::playSound()
{
	UIcontroller->playYX();
}

void GameManager::clearResetPack(char sid)
{
	layer->setPackresetschedule(sid);
}

Sprite* GameManager::getPaddelSprite() const
{
	return objManager->getPaddleSprite();
}

void GameManager::handelEventQueue()
{
	vector<eventObj*>::iterator il;
	for (il = eventQueue.begin(); il != eventQueue.end();)
	{
		eventObj* newEvent = *il;
		if (newEvent == nullptr)
			continue;
		switch (newEvent->eventType)
		{
		case PACK:
		{
			objManager->packWork(newEvent->Id->at(1));
			if (newEvent->Id->at(1) != 'G')
			{
				objManager->addPack2Reset(newEvent->Id->at(1), newEvent->Id);
				clearResetPack(newEvent->Id->at(1));
			}
			break;
		}
		case BRICK:
			objManager->updateBrickObj(newEvent->Id, newEvent->contact, newEvent->attack);
			break;
		case SOUND:
			layer->playSound();
			break;
		}
		il = eventQueue.erase(il);
	}
}





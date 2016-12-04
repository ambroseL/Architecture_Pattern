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
	if (pos.y * pixToMeter < -405.0)//����������Ļ�ײ�
	{
		HP--;	
		if (HP > 0)
		{
			UIcontroller->updateLifeSprite(HP);
			objManager->stickyPackWork(); //��Ч��ճ����
		}
		else //������ֵΪ0����Ϸ���¿�ʼ
		{
			sceneManager->reStart();
		}
		
	}//�������Ļ�ײ�
	
	if (keyleft == true)											//����������ס
		objManager->applyForce2Paddle(b2Vec2(-500.0f, 0.0f));
	if (keyright == true)											//����Ҽ�����ס
		objManager->applyForce2Paddle(b2Vec2(500.0f, 0.0f));

	handelEventQueue();												//������Ϣ����
	objManager->deleteObj();										//ɾ����ɾ������
	objManager->updateObj();										//���¸�����
	if (objManager->getBrickCount() == 0)
		toNext();
}

bool GameManager::myOnTouchBegan(Touch* touch, Event* event)
{
	auto location = touch->getLocation();							//��ȡ���ص��λ��
	Size visibleSize = Director::getInstance()->getVisibleSize();	//��ȡ�ɼ�����ߴ�
	Point origin = Director::getInstance()->getVisibleOrigin();		//��ȡ�ɼ�����ԭ������
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
	auto location = touch->getLocation();//��ȡ���ص��λ��
	Size visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	Point origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������
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
		objManager->shootBall(); //��������
	}

	if (EventKeyboard::KeyCode::KEY_ESCAPE == keyCode)
	{
		toPause();
	}

	if (EventKeyboard::KeyCode::KEY_P == keyCode)//ȥ��һ�ص����׼�
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
	//��ͣ���ж�ʱ���Ͷ���
	layer->pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//��ǰ������ͣ״̬��δ����***********************
	{
		//��ȡ�ɼ�����ߴ�
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ�ɼ�����ԭ������
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//����һ��������󣬰���toumingBg.pngͼƬ
		Sprite* transparentBackgroundSp = Sprite::create("Image/toumingBg.png");
		//���þ�������λ��
		transparentBackgroundSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//��������ӵ�������
		layer->addChild(transparentBackgroundSp, 2);
		Sprite* PauseSp = Sprite::create("Image/suspend.png");//������ͣ�󵯳��ľ���
		PauseSp->setScale(0.6f);//���þ������ű�
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//���þ���λ��
		layer->addChild(PauseSp, 3);//��������ӵ�����������

		auto resetItem = MenuItemImage::create//���������˵�                      
		(
			"Image/restart.png",	//ƽʱ��ͼƬ
			"Image/restart1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueReset, layer) //���ʱִ�еĻص�����
		);
		//���������˵����λ��
		resetItem->setPosition
		(
			Point
			(
				origin.x - 450,//X����
				origin.y - 380	//Y����
			)
		);

		//���������˵�����
		auto resetMenu = Menu::create(resetItem, NULL);
		resetMenu->setScale(0.3f);
		//���ò˵�λ��
		resetMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(resetMenu, 3);

		auto continueItem = MenuItemImage::create
		(
			"Image/continue.png",	//ƽʱ��ͼƬ
			"Image/continue1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueContinue, layer) //���ʱִ�еĻص�����
		);
		//���ü����˵����λ��
		continueItem->setPosition
		(
			Point
			(
				origin.x - 850,//X����
				origin.y - 380	//Y����
			)
		);

		//���������˵�����
		auto continueMenu = Menu::create(continueItem, NULL);
		continueMenu->setScale(0.3f);
		//���ò˵�λ��
		continueMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(continueMenu, 3);

		//�����ػ�ӭ����˵���
		auto backItem = MenuItemImage::create
		(
			"Image/back.png",	//ƽʱ��ͼƬ
			"Image/back1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueBack, layer) //���ʱִ�еĻص�����
		);

		//���ûػ�ӭ����˵����λ��
		backItem->setPosition
		(
			Point
			(
				origin.x - 50,//X����
				origin.y - 380	//Y����
			)
		);
		//�����˵�����
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setScale(0.3f);
		//���ò˵�λ��
		backMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(backMenu, 3);

		PauseSp->runAction(Spawn::create(//����һ��ͬ��ִ�ж������󲢽���ִ��
			ScaleBy::create(0.6f, 1.67f, 2),//����һ�����Ŷ�������
			RotateBy::create(0.6f, -360),//����һ����ת��������
										 //RotateTo::create(0.5f,180),
			NULL));

		isPausable = false;//��ͣ�˵�������
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

	//��ͣ���ж�ʱ���Ͷ���
	layer->pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//��ǰ������ͣ״̬��δ����***********************
	{
		//��ȡ�ɼ�����ߴ�
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ�ɼ�����ԭ������
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//����һ��������󣬰���toumingBg.pngͼƬ
		Sprite* transparentBackgroundSp = Sprite::create("Image/toumingBg.png");

		//���þ�������λ��
		transparentBackgroundSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//��������ӵ�������
		layer->addChild(transparentBackgroundSp, 2);

		Sprite* PauseSp = Sprite::create("Image/suspend.png");//������ͣ�󵯳��ľ���
		PauseSp->setScale(0.6f);//���þ������ű�
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//���þ���λ��
		layer->addChild(PauseSp, 3);//��������ӵ�����������

		auto resetItem = MenuItemImage::create//���������˵�        
		(
			"Image/restart.png",	//ƽʱ��ͼƬ
			"Image/restart1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueReset, layer) //���ʱִ�еĻص�����
		);
		//���������˵����λ��
		resetItem->setPosition
		(
			Point
			(
				origin.x - 450,//X����
				origin.y - 380	//Y����
			)
		);

		//���������˵�����
		auto resetMenu = Menu::create(resetItem, NULL);
		resetMenu->setScale(0.3f);
		//���ò˵�λ��
		resetMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(resetMenu, 3);

		auto continueItem = MenuItemImage::create
		(
			"Image/continue.png",	//ƽʱ��ͼƬ
			"Image/continue1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueContinue, layer) //���ʱִ�еĻص�����
		);
		//���ü����˵����λ��
		continueItem->setPosition
		(
			Point
			(
				origin.x - 850,//X����
				origin.y - 380	//Y����
			)
		);

		//���������˵�����
		auto continueMenu = Menu::create(continueItem, NULL);
		continueMenu->setScale(0.3f);
		//���ò˵�λ��
		continueMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(continueMenu, 3);

		//�����ػ�ӭ����˵���
		auto backItem = MenuItemImage::create
		(
			"Image/back.png",	//ƽʱ��ͼƬ
			"Image/back1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueBack, layer) //���ʱִ�еĻص�����
		);

		//���ûػ�ӭ����˵����λ��
		backItem->setPosition
		(
			Point
			(
				origin.x - 50,//X����
				origin.y - 380	//Y����
			)
		);
		//�����˵�����
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setScale(0.3f);
		//���ò˵�λ��
		backMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(backMenu, 3);

		PauseSp->runAction(Spawn::create(//����һ��ͬ��ִ�ж������󲢽���ִ��
			ScaleBy::create(0.6f, 1.67f, 2),//����һ�����Ŷ�������
			RotateBy::create(0.6f, -360),//����һ����ת��������
										 //RotateTo::create(0.5f,180),
			NULL));
		isPausable = false;//��ͣ�˵�������

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

	//��ͣ���ж�ʱ���Ͷ���
	layer->pauseSchedulerAndActions();
	if (isWin == true)//��ǰ������ͣ״̬��δ����***********************
	{
		
		//��ȡ�ɼ�����ߴ�
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ�ɼ�����ԭ������
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//����һ��������󣬰���toumingBg.pngͼƬ
		Sprite* transparentBackgroundSp = Sprite::create("Image/toumingBg.png");
		//���þ�������λ��
		transparentBackgroundSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		//��������ӵ�������
		layer->addChild(transparentBackgroundSp, 2);
		Sprite* PauseSp = Sprite::create("Image/suspend.png");//������ͣ�󵯳��ľ���
		PauseSp->setScale(0.6f);//���þ������ű�
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//���þ���λ��
		layer->addChild(PauseSp, 3);//��������ӵ�����������

		auto resetItem = MenuItemImage::create//���������˵�                
		(
			"Image/restart.png",	//ƽʱ��ͼƬ
			"Image/restart1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueReset, layer) //���ʱִ�еĻص�����
		);
		//���������˵����λ��
		resetItem->setPosition
		(
			Point
			(
				origin.x - 850,//X����
				origin.y - 380	//Y����
			)
		);

		//���������˵�����
		auto resetMenu = Menu::create(resetItem, NULL);
		resetMenu->setScale(0.3f);
		//���ò˵�λ��
		resetMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(resetMenu, 3);

		auto nextItem = MenuItemImage::create
		(
			"Image/next.png",	//ƽʱ��ͼƬ
			"Image/next1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueNext, layer) //���ʱִ�еĻص�����
		);
		//������һ�ز˵����λ��
		nextItem->setPosition
		(
			Point
			(
				origin.x - 450,//X����
				origin.y - 380	//Y����
			)
		);

		//������һ�ز˵�����
		auto nextMenu = Menu::create(nextItem, NULL);
		nextMenu->setScale(0.3f);
		//���ò˵�λ��
		nextMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(nextMenu, 3);

		//�����ػ�ӭ����˵���
		auto backItem = MenuItemImage::create
		(
			"Image/back.png",	//ƽʱ��ͼƬ
			"Image/back1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueBack, layer) //���ʱִ�еĻص�����
		);

		//���ûػ�ӭ����˵����λ��
		backItem->setPosition
		(
			Point
			(
				origin.x - 50,//X����
				origin.y - 380	//Y����
			)
		);
		//�����˵�����
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setScale(0.3f);
		//���ò˵�λ��
		backMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(backMenu, 3);

		PauseSp->runAction(Spawn::create(//����һ��ͬ��ִ�ж������󲢽���ִ��
			ScaleBy::create(0.6f, 1.67f, 2),//����һ�����Ŷ�������
			RotateBy::create(0.6f, -360),//����һ����ת��������
										 //RotateTo::create(0.5f,180),
			NULL));
		isPausable = false;//��ͣ�˵�������

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

	//ж�ض�ʱ��
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

	//ж�ض�ʱ��
	layer->unscheduleAllSelectors();
	SceneManager* sceneManager = layer->getSceneManager();
	sceneManager->goStartScene();
}

void GameManager::menueContinue()
{

	layer->removePauseSprite();
	isPause = false;
	isPausable = true;
	//�ָ����ж�ʱ���Ͷ�������
	layer->resumeSchedulerAndActions();
}

void GameManager::menueNext()
{

	//ж�ض�ʱ��
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

	//��ͣ���ж�ʱ���Ͷ���
	layer->pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//��ǰ������ͣ״̬��δ����***********************
	{
		//��ȡ�ɼ�����ߴ�
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ�ɼ�����ԭ������
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//����һ��������󣬰���toumingBg.pngͼƬ
		Sprite* transparentBackgroundSp = Sprite::create("Image/toumingBg.png");
		//���þ�������λ��
		transparentBackgroundSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		//��������ӵ�������
		layer->addChild(transparentBackgroundSp, 2);


		Sprite* PauseSp = Sprite::create("Image/suspend.png");//������ͣ�󵯳��ľ���
		PauseSp->setScale(0.6f);//���þ������ű�
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//���þ���λ��
		layer->addChild(PauseSp, 3);//��������ӵ�����������

		auto resetItem = MenuItemImage::create//���������˵�           
		(
			"Image/restart.png",	//ƽʱ��ͼƬ
			"Image/restart1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueReset, layer) //���ʱִ�еĻص�����
		);
		//���������˵����λ��
		resetItem->setPosition
		(
			Point
			(
				origin.x - 700,//X����
				origin.y - 380	//Y����
			)
		);

		//���������˵�����
		auto resetMenu = Menu::create(resetItem, NULL);
		resetMenu->setScale(0.3f);
		//���ò˵�λ��
		resetMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(resetMenu, 3);


		//�����ػ�ӭ����˵���
		auto backItem = MenuItemImage::create
		(
			"Image/back.png",	//ƽʱ��ͼƬ
			"Image/back1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(GameLayer::menueBack, layer) //���ʱִ�еĻص�����
		);

		//���ûػ�ӭ����˵����λ��
		backItem->setPosition
		(
			Point
			(
				origin.x - 200,//X����
				origin.y - 380	//Y����
			)
		);
		//�����˵�����
		auto backMenu = Menu::create(backItem, NULL);
		backMenu->setScale(0.3f);
		//���ò˵�λ��
		backMenu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		PauseSp->addChild(backMenu, 3);

		PauseSp->runAction(Spawn::create(//����һ��ͬ��ִ�ж������󲢽���ִ��
			ScaleBy::create(0.6f, 1.67f, 2),//����һ�����Ŷ�������
			RotateBy::create(0.6f, -360),//����һ����ת��������
										 //RotateTo::create(0.5f,180),
			NULL));
		isPausable = false;//��ͣ�˵�������

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





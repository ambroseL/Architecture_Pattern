#include "GameLayer.h"
#include "SimpleAudioEngine.h"
//#include "ContactListener.h""
//#include "GameSceneManager.h"
#include "GameManager.h"
#include "ContactListener.h"

bool GameLayer::init()
{
	//���ø���ĳ�ʼ��
	if (!Layer::init())
	{
		return false;
	}

	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��������������󣬰���background2.pngͼƬ
	auto bgSprite = Sprite::create("Image/background2.png");
	//���þ�������λ��
	bgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//��������ӵ�������
	this->addChild(bgSprite, -20);

	//������ͣ�˵���
	auto pauseItem = MenuItemImage::create
	(
		"Image/zanting_a.png",	//ƽʱ��ͼƬ
		"Image/zanting_b.png",	//ѡ��ʱ��ͼƬ
		CC_CALLBACK_1(GameLayer::menuePause, this) //���ʱִ�еĻص�����
	);
	//������ͣ�˵����λ��
	pauseItem->setPosition
	(
		Point
		(
			origin.x + visibleSize.width - 40,	//X����
			origin.y + visibleSize.height - 40	//Y����
		)
	);

	//�����˵�����
	auto pauseMenue = Menu::create(pauseItem, NULL);
	pauseMenue->setScale(1.0f);//���ò˵���������ű�
							  //���ò˵�λ��
	pauseMenue->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(pauseMenue, 2);

	auto hpSp = Sprite::create("Image/HP.png");
	//���þ�������λ��
	hpSp->setPosition(Point(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 40));
	hpSp->setScale(0.5f);
	//��������ӵ�������
	this->addChild(hpSp, 0);

	lifeSp = Sprite::create("Image/HP2.png");
	//���þ�������λ��
	lifeSp->setPosition(Point(origin.x + visibleSize.width - 130, origin.y + visibleSize.height - 40));
	lifeSp->setScale(0.6f);
	//��������ӵ�������
	this->addChild(lifeSp, 0);

	//Ԥ������Ч
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/eatprops.wav");

	//��ʼ����������
	//�����������ٶ�����
	b2Vec2 gravity(0.0f, 0.0f);
	//������������
	world = new b2World(gravity);
	//����ֹ��������
	world->SetAllowSleeping(true);
	
	gameManager = new GameManager();
	//��ʼ��������
	gameManager->init();

	//�����������������
	gameManager->initLayer(this, world);

	//�����ײ������
	world->SetContactListener(new ContactListener(this, this->gameManager->getObjManager()));

	//����һ����������
	auto touchListener = EventListenerTouchOneByOne::create();
	//�����´�����
	touchListener->setSwallowTouches(true);

	//��ʼ����ʱ�ص�onTouchBegan����
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::myOnTouchBegan, this);
	//�����ƶ�ʱ�ص�onTouchMoved����
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::myOnTouchMoved, this);
	//̧��ʱ�ص�onTouchEnded����
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::myOnTouchEnded, this);
	//��ֹ����ʱ�ص�onTouchCancelled����
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::myOnTouchCancelled, this);
	setTouchEnabled(true);
	//�Ѽ��������뵽������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, gameManager->getPaddelSprite());

	//����һ�����̼���
	auto keyBoardListener = EventListenerKeyboard::create();
	//���¼���ʱ�ص�onKeyPressed����
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);	
	//�ɿ�����ʱ�ص�onKeyReleased����
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	
	////���ø���
	//schedule(schedule_selector(GameLayer::update), 0.01f);

	//��ʱ�ص�
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
	//ʱ�䲽��
	float32 timeStep = 2.0f / 60.0f;
	//�ٶȵ�������
	int32 velocityIterations = 6;
	//λ�õ�������
	int32 positionIterations = 2;
	//ִ������ģ��
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














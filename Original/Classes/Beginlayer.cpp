#include "cocos2d.h"
#include "Beginlayer.h"
#include "LevelData.h"
#include "SimpleAudioEngine.h"
#include "MyContactListener.h"
#include <time.h>

int Beginlayer::level = 0;
//ʵ��Box2DLayer���е�init��������ʼ������
bool Beginlayer::init()
{
	//���ø���ĳ�ʼ��
	if (!Layer::init())
	{
		return false;
	}

	//��ȡ�ɼ�����ߴ�
	visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	origin = Director::getInstance()->getVisibleOrigin();

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
		CC_CALLBACK_1(Beginlayer::menuPause, this) //���ʱִ�еĻص�����
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
	auto pauseMenu = Menu::create(pauseItem, NULL);
	pauseMenu->setScale(1.0f);//���ò˵���������ű�
	//���ò˵�λ��
	pauseMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(pauseMenu, 2);

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
	b2Vec2 gravity(0.0f, -3.0f);
	//������������
	world = new b2World(gravity);
	//����ֹ��������
	world->SetAllowSleeping(true);
	//�����ײ������
	world->SetContactListener(new MyContactListener(this));

	//����һ����������
	auto listener = EventListenerTouchOneByOne::create();
	//�����´�����
	listener->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listener->onTouchBegan = CC_CALLBACK_2(Beginlayer::myOnTouchBegan, this);
	//�����ƶ�ʱ�ص�onTouchMoved����
	listener->onTouchMoved = CC_CALLBACK_2(Beginlayer::myOnTouchMoved, this);
	//̧��ʱ�ص�onTouchEnded����
	listener->onTouchEnded = CC_CALLBACK_2(Beginlayer::myOnTouchEnded, this);
	//��ֹ����ʱ�ص�onTouchCancelled����
	listener->onTouchCancelled = CC_CALLBACK_2(Beginlayer::myOnTouchCancelled, this);
	setTouchEnabled(true);

	//����һ�����̼���
	auto listener1 = EventListenerKeyboard::create();
	//���¼���ʱ�ص�onKeyPressed����
	listener1->onKeyPressed = CC_CALLBACK_2(Beginlayer::onKeyPressed, this);
	//�ɿ�����ʱ�ص�onKeyReleased����
	listener1->onKeyReleased = CC_CALLBACK_2(Beginlayer::onKeyReleased, this);

	if (!pom.empty())
		pom.clear();
	if (!listDestroy.empty())
		listDestroy.clear();
	if (!listForDel.empty())
		listForDel.clear();
	if (!listForFire.empty())
		listForFire.clear();

	LevelData* leveldata = new LevelData(level, world, this, pom);

	isWin = false;
	isPauseEnble = true;
	index = 0;
	PhyObject* po;
	float* data;
	std::string* ids;

	//�����������
	data = new float[4]{-512, -384, 512, -384};
	ids = new std::string(StringUtils::format("W%d", ++Wall::index));      //Ground
	ground = new Wall(ids, this, world, "Image/blockRed.png", data, 1, 0.0f, 1.0f);
	pom[*ids] = ground;
	
	//�����������
	data = new float[4]{-512, 384, 512, 384};
	ids = new std::string(StringUtils::format("W%d", ++Wall::index));
	po = new Wall(ids, this, world, "Image/blockRed.png", data, 1, 0.0f, 1.0f);
	pom[*ids] = po;

	//������ǽ�����
	data = new float[4]{-512, -384, -512, 384};
	ids = new std::string(StringUtils::format("W%d", ++Wall::index));
	po = new Wall(ids, this, world, "Image/blockRed.png", data, 1, 0.0f, 1.0f);
	pom[*ids] = po;


	//������ǽ�����
	data = new float[4]{512, -384, 512, 384};
	ids = new std::string(StringUtils::format("W%d", ++Wall::index));
	po = new Wall(ids,this, world, "Image/blockRed.png", data, 1, 0.0f, 1.0f);
	pom[*ids] = po;

	ball = NULL;
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	//��������
	data = new float[4]{0, -364, Paddle::s_length, Paddle::s_width};
	ids = new std::string(StringUtils::format("P%d", ++Paddle::index));
	paddle = new Paddle(ids, this, world, "Image/paddle.png", data, 1000.0f, 0.0f, 1.0f, 2);
	pom[*ids] = paddle;

	paddle->isSticky = true;
	data = new float[3]{0 + paddle->ball_x, -364.0f + paddle->ball_y, Ball::radius};
	paddle->Is_Sticky(world,this,data);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, paddle->dSp);//�ѵ�����ӵ���������

	mj = NULL;
	new PrismaticJoint(world, false, ground, paddle, b2Vec2(0, 0), b2Vec2(1.0f, 0.0f), 0, true, -1000.0f, 1000.0f, false, 0, 0);
	schedule(schedule_selector(Beginlayer::update), 0.0001f);

	//��ʱ�ص�
	scheduleUpdate();
	return true;
}

//��������ģ��
void Beginlayer::step()
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


void Beginlayer::update(float delta)
{
	if (isPause == true)
	{
		return;
	}

	if (paddle->isSticky == false)
	{
		b2Vec2 pos = ball->body->GetPosition();
		if (pos.y * pixToMeter < -405.0)   //����������Ļ�ײ�
		{
			paddle->HP--;
			paddle->isSticky = true;
			if (paddle->HP >= 0)
			{
				this->removeChild(lifeSp);
				lifeSp = Sprite::create("Image/HP" + StringUtils::format("%d", paddle->HP) + ".png");
				lifeSp->setPosition(Point(origin.x + visibleSize.width - 130, origin.y + visibleSize.height - 40));
				lifeSp->setScale(0.6f);
				//��������ӵ�������
				this->addChild(lifeSp, 0);
			}
			std::string* ids = ball->poId;
			this->removeChild(ball->dSp, true);//�ڲ�����ɾ����������Լ��ľ���
			this->removeChild(ball->cps, true);//�ڲ�����ɾ����������Լ��ľ���
			world->DestroyBody(ball->body);//������������ɾ����������Լ��ĸ���
			pom.erase(*ids);//��map��ɾ�����ָ��
			delete ball;//ɾ�������ָ��
			ball = NULL;
			b2Vec2 vec;
			if (paddle->isReversal == true)
				vec = paddle->body_paddle->GetPosition();
			else
				vec = paddle->body->GetPosition();
			float* data = new float[3]{vec.x * pixToMeter + Paddle::ball_x, vec.y * pixToMeter + Paddle::ball_y, Ball::radius};
			paddle->Is_Sticky(world, this, data);
		}
		else//��֤�������˶�
		{
			b2Vec2 vec = ball->body->GetLinearVelocity();
			if (sqrt(vec.x*vec.x + vec.y*vec.y) < Ball::speed)
			{
				float sq = sqrt(vec.x*vec.x + vec.y*vec.y);
				sq = Ball::speed / sq;
				vec.x *= sq;
				vec.y *= sq;
			}
			else if (sqrt(vec.x*vec.x + vec.y*vec.y) > Ball::speed)
			{
				float sq = sqrt(vec.x*vec.x + vec.y*vec.y);
				sq = Ball::speed / sq;
				vec.x *= sq;
				vec.y *= sq;
			}
			ball->body->SetLinearVelocity(vec);
		}
	}
	if (paddle->HP < 0)
	{
		Beginlayer::RestartGame();
	}

	//��������ģ��
	step();

	if (keyleft == true)        //����������ס
		paddle->body->ApplyForce(b2Vec2(-500.0f*paddle->body->GetMass(), 0.0f), paddle->body->GetWorldCenter(), true);
	if (keyright == true)       //����Ҽ�����ס
		paddle->body->ApplyForce(b2Vec2(500.0f*paddle->body->GetMass(), 0.0f), paddle->body->GetWorldCenter(), true);

	b2Vec2 vline = paddle->body->GetLinearVelocity();
	if (paddle->body_paddle != NULL)//���Ƹ�������ķ���
	{
		b2Vec2 position = paddle->body_paddle->GetPosition();
		b2Vec2 position1 = paddle->body->GetPosition();
		paddle->body_paddle->ApplyForce(b2Vec2(0.0f, 3.0f*paddle->body_paddle->GetMass()), paddle->body_paddle->GetWorldCenter(),true);
		if (vline.x == -1.0f || vline.x == 1.0f) 
		{
			vline.y = 0;
			if (vline.x == -1.0f)
			{
				vline.x = 55000.0f*paddle->body->GetMass();
				paddle->body_paddle->SetLinearVelocity(vline);
			}
			else if (vline.x == 1.0f)
			{
				vline.x = -55000.0f*paddle->body->GetMass();
				paddle->body_paddle->SetLinearVelocity(vline);
			}
		}
		if (position.x * pixToMeter > (512 - Paddle::length))
		{
			vline.y = 0;
			vline.x = -55000.0f*paddle->body->GetMass();
			paddle->body_paddle->SetLinearVelocity(vline);
		}
		else if (position.x * pixToMeter < -(512 - Paddle::length))
		{
			vline.y = 0;
			vline.x = 55000.0f*paddle->body->GetMass();
			paddle->body_paddle->SetLinearVelocity(vline);
		}
		else
		{
			vline.y = 0;
			vline.x = -vline.x;
			paddle->body_paddle->SetLinearVelocity(vline);
		}
	}

	//ִ��ɾ������
	std::vector<std::string>::iterator il;
	for (il = listForDel.begin(); il != listForDel.end(); il++)
	{
		PhyObject* po = pom[*il];//�õ����������ָ��
		if (po == NULL || po->body == NULL)
			continue;
		if (po)
		{
			b2Vec2 vec = po->body->GetPosition();
			if (po->poId->at(0) == 'B' && po->poId->at(1) == 'T')
			{
				po->Work(pom, this, world, vec.x * pixToMeter, vec.y * pixToMeter, ball, paddle);
				continue;
			}
			if (po->poId->at(0) == 'B')
			{
				//ש����ʧ������Ч��
				auto explosion = ParticleFire::create();
				explosion->setPosition(Vec2(origin.x + visibleSize.width / 2 + vec.x * pixToMeter, 
					origin.y + visibleSize.height / 2 + vec.y * pixToMeter));
				explosion->retain();
				explosion->setScale(0.8f);
				explosion->setLife(0.26f);
				this->addChild(explosion);
				listForFire.push_back(explosion);
				schedule(schedule_selector(Beginlayer::Cut), 0.36f);

				srand((unsigned)time(NULL));
				int flag = rand() % 10;
				if (flag < 6)      //60%���ʵ������
					po->Work(pom, this, world, vec.x * pixToMeter, vec.y * pixToMeter, ball, paddle);
			}
			else
				po->Work(pom, this, world, vec.x * pixToMeter, vec.y * pixToMeter, ball, paddle);
			if ((po->poId->at(0) == 'A') && (po->poId->at(1) != 'S'))
			{
				char id = il->at(1);
				Beginlayer::judgePack(id, po->poId);
			}
			this->removeChild(po->dSp, true);//�ڲ�����ɾ��������������Լ��ľ���
			listDestroy.push_back(po->body);
			if (po->poId->at(0) == 'B' && po->poId->at(1) != 'H')
			{
				LevelData::brickcount--;
				if (LevelData::brickcount == 0)
				{
					isWin = true;
					goNext();
				}
			}
		}
		if ((po->poId->at(0) != 'A') || (po->poId->at(0) == 'A' && po->poId->at(1) == 'S'))
		{
			pom.erase(*il);//��map��ɾ������������ָ��
			delete po;//ɾ�����������ָ��
		}
		else
			po->body = NULL;
	}
	listForDel.clear();//�б����

	std::vector<b2Body*>::iterator ik;
	for (ik = listDestroy.begin(); ik != listDestroy.end(); ik++)
	{
		b2Body* body = *ik;
		body->SetUserData(NULL);
		world->DestroyBody(body);
		body = NULL;
	}
	listDestroy.clear();//�б����

	//�������¸���״̬
	std::map<std::string, PhyObject*>::iterator iter;
	for (iter = pom.begin(); iter != pom.end(); iter++)
	{
		PhyObject* po = iter->second;
		if (po == NULL)
		{
			pom.erase(iter++);
			continue;
		}
		if (po->body != NULL)
		{
			b2Vec2 position = po->body->GetPosition();
			if (position.y * pixToMeter < -405.0 && po != ball)
			{
				this->removeChild(po->dSp, true);//�ڲ�����ɾ��������������Լ��ľ���
				world->DestroyBody(po->body);//������������ɾ��������������Լ��ĸ���

				pom.erase(iter++);//��map��ɾ������������ָ��
				delete po;//ɾ�����������ָ��
				continue;
			}
		}
		po->refresh();
	}
}

void Beginlayer::judgePack(char sid, std::string* ids)
{
	if (sid == 'L')
	{
		listForPackL.push_back(*ids);
		schedule(schedule_selector(Beginlayer::L_Reset), 7.0f, 0, 7.0f);
	}
	if (sid == 'B')
	{
		listForPackB.push_back(*ids);
		schedule(schedule_selector(Beginlayer::B_Reset), 7.0f, 0, 7.0f);
	}
	if (sid == 'R')
	{
		listForPackR.push_back(*ids);
		schedule(schedule_selector(Beginlayer::R_Reset), 7.0f, 0, 7.0f);
	}
	if (sid == 'I')
	{
		listForPackI.push_back(*ids);
		schedule(schedule_selector(Beginlayer::I_Reset), 7.0f, 0, 7.0f);
	}
	if (sid == 'A')
	{
		listForPackA.push_back(*ids);
		schedule(schedule_selector(Beginlayer::A_Reset), 7.0f, 0, 7.0f);
	}
	if (sid == 'D')
	{
		listForPackD.push_back(*ids);
		schedule(schedule_selector(Beginlayer::D_Reset), 7.0f, 0, 7.0f);
	}
	if (sid == 'U')
	{
		listForPackU.push_back(*ids);
		schedule(schedule_selector(Beginlayer::U_Reset), 7.0f, 0, 7.0f);
	}
	if (sid == 'F')
	{
		listForPackF.push_back(*ids);
		schedule(schedule_selector(Beginlayer::F_Reset), 7.0f, 0, 7.0f);
	}
}


//ִ����Ӧ�Ļ�ԭ����
void Beginlayer::L_Reset(float delta)  
{
	if (listForPackL.empty())
		return;
	std::vector<std::string>::iterator il;
	il = listForPackL.end();
	il--;
	package = pom[*il];
	package->Reset(this, world, ball, paddle);
	for (il = listForPackL.begin(); il != listForPackL.end(); il++)
		pom.erase(*il);
	listForPackL.clear();
	delete package; 
}

void Beginlayer::B_Reset(float delta)
{
	if (listForPackB.empty())
		return;
	std::vector<std::string>::iterator il;
	il = listForPackB.end();
	il--;
	package = pom[*il];
	package->Reset(this, world, ball, paddle);
	for (il = listForPackB.begin(); il != listForPackB.end(); il++)
		pom.erase(*il);
	listForPackB.clear();
	delete package;
}

void Beginlayer::R_Reset(float delta)
{
	if (listForPackR.empty())
		return;
	std::vector<std::string>::iterator il;
	il = listForPackR.end();
	il--;
	package = pom[*il];
	package->Reset(this, world, ball, paddle);
	for (il = listForPackR.begin(); il != listForPackR.end(); il++)
		pom.erase(*il);
	listForPackR.clear();
	delete package;
}
void Beginlayer::I_Reset(float delta)
{
	if (listForPackI.empty())
		return;
	std::vector<std::string>::iterator il;
	il = listForPackI.end();
	il--;
	package = pom[*il];
	package->Reset(this, world, ball, paddle);
	for (il = listForPackI.begin(); il != listForPackI.end(); il++)
		pom.erase(*il);
	listForPackI.clear();
	delete package;
}
void Beginlayer::A_Reset(float delta)
{
	if (listForPackA.empty())
		return;
	std::vector<std::string>::iterator il;
	il = listForPackA.end();
	il--;
	package = pom[*il];
	package->Reset(this, world, ball, paddle);
	for (il = listForPackA.begin(); il != listForPackA.end(); il++)
		pom.erase(*il);
	listForPackA.clear();
	delete package;
}
void Beginlayer::D_Reset(float delta)
{
	if (listForPackD.empty())
		return;
	std::vector<std::string>::iterator il;
	il = listForPackD.end();
	il--;
	package = pom[*il];
	package->Reset(this, world, ball, paddle);
	for (il = listForPackD.begin(); il != listForPackD.end(); il++)
		pom.erase(*il);
	listForPackD.clear();
	delete package;
}
void Beginlayer::U_Reset(float delta)
{
	if (listForPackU.empty())
		return;
	std::vector<std::string>::iterator il;
	il = listForPackU.end();
	il--;
	package = pom[*il];
	package->Reset(this, world, ball, paddle);
	for (il = listForPackU.begin(); il != listForPackU.end(); il++)
		pom.erase(*il);
	listForPackU.clear();
	delete package;
}
void Beginlayer::F_Reset(float delta)
{
	if (listForPackF.empty())
		return;
	std::vector<std::string>::iterator il;
	il = listForPackF.end();
	il--;
	package = pom[*il];
	package->Reset(this, world, ball, paddle);
	for (il = listForPackF.begin(); il != listForPackF.end(); il++)
		pom.erase(*il);
	listForPackF.clear();
	delete package;
}


void Beginlayer::Cut(float delta)  //��������Ч��
{
	if (listForFire.empty())
		return;
	std::vector<ParticleFire*>::iterator il;
	il = listForFire.begin();
	this->removeChild(*il);
	listForFire.erase(il);
}

//��ʼ�����¼��Ĵ�����
bool Beginlayer::myOnTouchBegan(Touch *touch, Event *event)
{
	auto location = touch->getLocation();//��ȡ���ص��λ��
	Size visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	Point origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������
	b2Vec2 locationWorld = b2Vec2((location.x - origin.x - visibleSize.width / 2) / pixToMeter, (location.y - origin.y - visibleSize.height / 2) / pixToMeter);

	
	for (int i = 0; i<3; i++)
	{
		//if (mj == NULL&&paddle->body->GetFixtureList()->TestPoint(locationWorld))//�ж��Ƿ��ڴ�����Χ
		if (mj == NULL)
		{
			index++;
			paddle->body->SetLinearDamping(0.0f);
			mj = new MouseJoint(new std::string(StringUtils::format("M%d", index)), world, true, ground, paddle, locationWorld, 58000.0f*paddle->body->GetMass(), 10.0f, 0.0f);
			return true;
		}
	}
	return false;
}
//�����ƶ��¼��Ĵ�����
void Beginlayer::myOnTouchMoved(Touch *touch, Event *event)
{
	auto location = touch->getLocation();//��ȡ���ص��λ��
	Size visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	Point origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������
	b2Vec2 locationWorld = b2Vec2((location.x - origin.x - visibleSize.width / 2) / pixToMeter, (location.y - origin.y - visibleSize.height / 2) / pixToMeter);

	for (int i = 0; i<3; i++)
	{
		if (mj != NULL)
		{
			mj->mJoint->SetTarget(locationWorld);
		}
	}
}
//���ؽ����¼��Ĵ�����
void Beginlayer::myOnTouchEnded(Touch *touch, Event *event)
{
	for (int i = 0; i<3; i++)
	{
		if (mj != NULL)
		{
			b2Vec2 vLine(0.0, 0.0);
			mj->mJoint->GetBodyB()->SetLinearVelocity(vLine);
			delete mj;
			mj = NULL;
		}
	}
}
//������ֹ�¼��Ĵ�����
void Beginlayer::myOnTouchCancelled(Touch *touch, Event *event)
{
	myOnTouchEnded(touch, event);
}

//���¼���ʱ�Ĵ�����
void Beginlayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_SPACE == keyCode && paddle->isSticky == true)
	{
		this->removeChild(paddle->dSp_ball, true);//�ڲ�����ɾ��������������Լ��ľ���
		paddle->dSp_ball = NULL;
		//world->DestroyBody(paddle->body_ball);//������������ɾ��������������Լ��ĸ���
		paddle->isSticky = false;
		std::string* ids = new std::string(StringUtils::format("Q%d", ++Ball::index));
		b2Vec2 vec = paddle->body->GetPosition();
		if (paddle->isReversal == true)
			vec = paddle->body_paddle->GetPosition();
		float* data = new float[3]{vec.x * pixToMeter + paddle->ball_x, vec.y * pixToMeter + paddle->ball_y, Ball::radius};
		ball = new Ball(ids, this, world, "Image/Ball1.png", data, 1, 0.0f, 1.0f, 1);
		Ball::isFast = false;
		b2Vec2 vLine(0.0, Ball::s_speed);
		ball->body->SetLinearVelocity(vLine);
		pom[*ids] = ball; 
	}

	if (EventKeyboard::KeyCode::KEY_ESCAPE == keyCode)
	{
		Beginlayer::toPause();
	}

	if (EventKeyboard::KeyCode::KEY_P == keyCode)//ȥ��һ�ص����׼�
	{
		Beginlayer::toNext();
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

void Beginlayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keyCode)
	{
		paddle->body->ApplyForce(b2Vec2(0.0f, 0.0f), paddle->body->GetWorldCenter(), true);
		paddle->body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		keyleft = false;
		paddle->body->SetLinearDamping(10.0f);
	}

	if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keyCode)
	{
		paddle->body->ApplyForce(b2Vec2(0.0f, 0.0f), paddle->body->GetWorldCenter(), true);
		paddle->body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		keyright = false;
		paddle->body->SetLinearDamping(10.0f);
	}
}

/*void Beginlayer::menuClose(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}*/

void Beginlayer::toPause()
{
	//��ͣ���ж�ʱ���Ͷ���
	pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//��ǰ������ͣ״̬��δ����***********************
	{
		//����һ��������󣬰���toumingBg.pngͼƬ
		toumingBgSp = Sprite::create("Image/toumingBg.png");
		//���þ�������λ��
		toumingBgSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//��������ӵ�������
		this->addChild(toumingBgSp, 2);
		PauseSp = Sprite::create("Image/suspend.png");//������ͣ�󵯳��ľ���
		PauseSp->setScale(0.6f);//���þ������ű�
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//���þ���λ��
		this->addChild(PauseSp, 3);//��������ӵ�����������

		auto resetItem = MenuItemImage::create//���������˵�                      
			(
			"Image/restart.png",	//ƽʱ��ͼƬ
			"Image/restart1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(Beginlayer::menuReset, this) //���ʱִ�еĻص�����
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
			CC_CALLBACK_1(Beginlayer::menuContinue, this) //���ʱִ�еĻص�����
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
			CC_CALLBACK_1(Beginlayer::menuBack, this) //���ʱִ�еĻص�����
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
		isPauseEnble = false;//��ͣ�˵�������
	}
	else
	{
		isPause = false;
		isPauseEnble = true;//��ͣ�˵�����
	}
	isPause = true;
}

void Beginlayer::menuPause(Ref* pSender)
{
	//��ͣ���ж�ʱ���Ͷ���
	pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//��ǰ������ͣ״̬��δ����***********************
	{
		//����һ��������󣬰���toumingBg.pngͼƬ
		toumingBgSp = Sprite::create("Image/toumingBg.png");
		//���þ�������λ��
		toumingBgSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//��������ӵ�������
		this->addChild(toumingBgSp, 2);
		PauseSp = Sprite::create("Image/suspend.png");//������ͣ�󵯳��ľ���
		PauseSp->setScale(0.6f);//���þ������ű�
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//���þ���λ��
		this->addChild(PauseSp, 3);//��������ӵ�����������

		auto resetItem = MenuItemImage::create//���������˵�        
			(
			"Image/restart.png",	//ƽʱ��ͼƬ
			"Image/restart1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(Beginlayer::menuReset, this) //���ʱִ�еĻص�����
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
			CC_CALLBACK_1(Beginlayer::menuContinue, this) //���ʱִ�еĻص�����
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
			CC_CALLBACK_1(Beginlayer::menuBack, this) //���ʱִ�еĻص�����
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
		isPauseEnble = false;//��ͣ�˵�������
	}
	else
	{
		isPause = false;
		isPauseEnble = true;//��ͣ�˵�����
	}
	isPause = true;
}

void Beginlayer::goNext()
{
	//��ͣ���ж�ʱ���Ͷ���
	pauseSchedulerAndActions();
	if (isWin == true)//��ǰ������ͣ״̬��δ����***********************
	{
		//����һ��������󣬰���toumingBg.pngͼƬ
		toumingBgSp = Sprite::create("Image/toumingBg.png");
		//���þ�������λ��
		toumingBgSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//��������ӵ�������
		this->addChild(toumingBgSp, 2);
		PauseSp = Sprite::create("Image/suspend.png");//������ͣ�󵯳��ľ���
		PauseSp->setScale(0.6f);//���þ������ű�
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//���þ���λ��
		this->addChild(PauseSp, 3);//��������ӵ�����������

		auto resetItem = MenuItemImage::create//���������˵�                
			(
			"Image/restart.png",	//ƽʱ��ͼƬ
			"Image/restart1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(Beginlayer::menuReset, this) //���ʱִ�еĻص�����
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
			CC_CALLBACK_1(Beginlayer::menuNext, this) //���ʱִ�еĻص�����
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
			CC_CALLBACK_1(Beginlayer::menuBack, this) //���ʱִ�еĻص�����
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
		isPauseEnble = false;//��ͣ�˵�������
	}
	else
	{
		isPause = false;
		isPauseEnble = true;//��ͣ�˵�����
	}
	isPause = true;
}


void Beginlayer::menuReset(cocos2d::Ref*  pSender)
{
	/*//ж�ض�ʱ��
	unscheduleAllSelectors();*/
	if (level == 1)
	{
		gsm->reStart();
	}
	else if (level == 2)
	{
		gsm->reStart2();
	}
	else if (level == 3)
	{
		gsm->reStart3();
	}
}

void Beginlayer::menuContinue(cocos2d::Ref*  pSender)
{
	PauseSp->runAction(RemoveSelf::create(true));
	toumingBgSp->runAction(RemoveSelf::create(true));
	isPause = false;
	isPauseEnble = true;
	//�ָ����ж�ʱ���Ͷ�������
	resumeSchedulerAndActions();
}

void Beginlayer::RestartGame()
{
	//��ͣ���ж�ʱ���Ͷ���
	pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//��ǰ������ͣ״̬��δ����***********************
	{
		//����һ��������󣬰���toumingBg.pngͼƬ
		toumingBgSp = Sprite::create("Image/toumingBg.png");
		//���þ�������λ��
		toumingBgSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//��������ӵ�������
		this->addChild(toumingBgSp, 2);
		PauseSp = Sprite::create("Image/suspend.png");//������ͣ�󵯳��ľ���
		PauseSp->setScale(0.6f);//���þ������ű�
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//���þ���λ��
		this->addChild(PauseSp, 3);//��������ӵ�����������

		auto resetItem = MenuItemImage::create//���������˵�           
			(
			"Image/restart.png",	//ƽʱ��ͼƬ
			"Image/restart1.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(Beginlayer::menuReset, this) //���ʱִ�еĻص�����
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
			CC_CALLBACK_1(Beginlayer::menuBack, this) //���ʱִ�еĻص�����
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
		isPauseEnble = false;//��ͣ�˵�������
	}
	else
	{
		//isPause = false;
		//isPauseEnble = true;//��ͣ�˵�����
	}
	isPause = true;
}
void Beginlayer::menuBack(cocos2d::Ref*  pSender)
{
	//ж�ض�ʱ��
	unscheduleAllSelectors();
	gsm->goWelcomeScene();
}

void Beginlayer::menuNext(cocos2d::Ref*  pSender)
{
	//ж�ض�ʱ��
	unscheduleAllSelectors();
	if (level == 1)
	{
		gsm->goRound2Scene();
	}
	else if (level == 2)
	{
		gsm->goRound3Scene();
	}
}

void Beginlayer::toNext()
{
	//ж�ض�ʱ��
	unscheduleAllSelectors();
	if (level == 1)
	{
		gsm->goRound2Scene();
	}
	else if (level == 2)
	{
		gsm->goRound3Scene();
	}
}

void Beginlayer::playYX()
{
	//��ʼ���ű�����Ч��false��ʾ��ѭ��
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/eatprops.wav", false);
	//������Ч����0.0-1.0
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
}
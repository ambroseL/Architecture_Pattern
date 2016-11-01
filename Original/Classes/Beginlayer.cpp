#include "cocos2d.h"
#include "Beginlayer.h"
#include "LevelData.h"
#include "SimpleAudioEngine.h"
#include "MyContactListener.h"
#include <time.h>

int Beginlayer::level = 0;
//实现Box2DLayer类中的init方法，初始化布景
bool Beginlayer::init()
{
	//调用父类的初始化
	if (!Layer::init())
	{
		return false;
	}

	//获取可见区域尺寸
	visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	origin = Director::getInstance()->getVisibleOrigin();

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
		CC_CALLBACK_1(Beginlayer::menuPause, this) //点击时执行的回调方法
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
	auto pauseMenu = Menu::create(pauseItem, NULL);
	pauseMenu->setScale(1.0f);//设置菜单对象的缩放比
	//设置菜单位置
	pauseMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(pauseMenu, 2);

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
	b2Vec2 gravity(0.0f, -3.0f);
	//创建物理世界
	world = new b2World(gravity);
	//允许静止物体休眠
	world->SetAllowSleeping(true);
	//添加碰撞监听器
	world->SetContactListener(new MyContactListener(this));

	//创建一个触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listener->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listener->onTouchBegan = CC_CALLBACK_2(Beginlayer::myOnTouchBegan, this);
	//触摸移动时回调onTouchMoved方法
	listener->onTouchMoved = CC_CALLBACK_2(Beginlayer::myOnTouchMoved, this);
	//抬起时回调onTouchEnded方法
	listener->onTouchEnded = CC_CALLBACK_2(Beginlayer::myOnTouchEnded, this);
	//终止触摸时回调onTouchCancelled方法
	listener->onTouchCancelled = CC_CALLBACK_2(Beginlayer::myOnTouchCancelled, this);
	setTouchEnabled(true);

	//创建一个键盘监听
	auto listener1 = EventListenerKeyboard::create();
	//按下键盘时回调onKeyPressed方法
	listener1->onKeyPressed = CC_CALLBACK_2(Beginlayer::onKeyPressed, this);
	//松开键盘时回调onKeyReleased方法
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

	//创建地面刚体
	data = new float[4]{-512, -384, 512, -384};
	ids = new std::string(StringUtils::format("W%d", ++Wall::index));      //Ground
	ground = new Wall(ids, this, world, "Image/blockRed.png", data, 1, 0.0f, 1.0f);
	pom[*ids] = ground;
	
	//创建上面刚体
	data = new float[4]{-512, 384, 512, 384};
	ids = new std::string(StringUtils::format("W%d", ++Wall::index));
	po = new Wall(ids, this, world, "Image/blockRed.png", data, 1, 0.0f, 1.0f);
	pom[*ids] = po;

	//创建左墙面刚体
	data = new float[4]{-512, -384, -512, 384};
	ids = new std::string(StringUtils::format("W%d", ++Wall::index));
	po = new Wall(ids, this, world, "Image/blockRed.png", data, 1, 0.0f, 1.0f);
	pom[*ids] = po;


	//创建右墙面刚体
	data = new float[4]{512, -384, 512, 384};
	ids = new std::string(StringUtils::format("W%d", ++Wall::index));
	po = new Wall(ids,this, world, "Image/blockRed.png", data, 1, 0.0f, 1.0f);
	pom[*ids] = po;

	ball = NULL;
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	//创建挡板
	data = new float[4]{0, -364, Paddle::s_length, Paddle::s_width};
	ids = new std::string(StringUtils::format("P%d", ++Paddle::index));
	paddle = new Paddle(ids, this, world, "Image/paddle.png", data, 1000.0f, 0.0f, 1.0f, 2);
	pom[*ids] = paddle;

	paddle->isSticky = true;
	data = new float[3]{0 + paddle->ball_x, -364.0f + paddle->ball_y, Ball::radius};
	paddle->Is_Sticky(world,this,data);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, paddle->dSp);//把挡板添加到监听器中

	mj = NULL;
	new PrismaticJoint(world, false, ground, paddle, b2Vec2(0, 0), b2Vec2(1.0f, 0.0f), 0, true, -1000.0f, 1000.0f, false, 0, 0);
	schedule(schedule_selector(Beginlayer::update), 0.0001f);

	//定时回调
	scheduleUpdate();
	return true;
}

//进行物理模拟
void Beginlayer::step()
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


void Beginlayer::update(float delta)
{
	if (isPause == true)
	{
		return;
	}

	if (paddle->isSticky == false)
	{
		b2Vec2 pos = ball->body->GetPosition();
		if (pos.y * pixToMeter < -405.0)   //如果球掉落屏幕底部
		{
			paddle->HP--;
			paddle->isSticky = true;
			if (paddle->HP >= 0)
			{
				this->removeChild(lifeSp);
				lifeSp = Sprite::create("Image/HP" + StringUtils::format("%d", paddle->HP) + ".png");
				lifeSp->setPosition(Point(origin.x + visibleSize.width - 130, origin.y + visibleSize.height - 40));
				lifeSp->setScale(0.6f);
				//将精灵添加到布景中
				this->addChild(lifeSp, 0);
			}
			std::string* ids = ball->poId;
			this->removeChild(ball->dSp, true);//在布景里删除球对象中自己的精灵
			this->removeChild(ball->cps, true);//在布景里删除球对象中自己的精灵
			world->DestroyBody(ball->body);//在物理世界中删除球对象中自己的刚体
			pom.erase(*ids);//在map里删掉球的指针
			delete ball;//删除球对象指针
			ball = NULL;
			b2Vec2 vec;
			if (paddle->isReversal == true)
				vec = paddle->body_paddle->GetPosition();
			else
				vec = paddle->body->GetPosition();
			float* data = new float[3]{vec.x * pixToMeter + Paddle::ball_x, vec.y * pixToMeter + Paddle::ball_y, Ball::radius};
			paddle->Is_Sticky(world, this, data);
		}
		else//保证球匀速运动
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

	//进行物理模拟
	step();

	if (keyleft == true)        //如果左键被按住
		paddle->body->ApplyForce(b2Vec2(-500.0f*paddle->body->GetMass(), 0.0f), paddle->body->GetWorldCenter(), true);
	if (keyright == true)       //如果右键被按住
		paddle->body->ApplyForce(b2Vec2(500.0f*paddle->body->GetMass(), 0.0f), paddle->body->GetWorldCenter(), true);

	b2Vec2 vline = paddle->body->GetLinearVelocity();
	if (paddle->body_paddle != NULL)//控制副本挡板的方法
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

	//执行删除任务
	std::vector<std::string>::iterator il;
	for (il = listForDel.begin(); il != listForDel.end(); il++)
	{
		PhyObject* po = pom[*il];//拿到物体类对象指针
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
				//砖块消失的粒子效果
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
				if (flag < 6)      //60%几率掉落包裹
					po->Work(pom, this, world, vec.x * pixToMeter, vec.y * pixToMeter, ball, paddle);
			}
			else
				po->Work(pom, this, world, vec.x * pixToMeter, vec.y * pixToMeter, ball, paddle);
			if ((po->poId->at(0) == 'A') && (po->poId->at(1) != 'S'))
			{
				char id = il->at(1);
				Beginlayer::judgePack(id, po->poId);
			}
			this->removeChild(po->dSp, true);//在布景里删除物体类对象中自己的精灵
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
			pom.erase(*il);//在map里删掉物理类对象的指针
			delete po;//删除物体类对象指针
		}
		else
			po->body = NULL;
	}
	listForDel.clear();//列表清空

	std::vector<b2Body*>::iterator ik;
	for (ik = listDestroy.begin(); ik != listDestroy.end(); ik++)
	{
		b2Body* body = *ik;
		body->SetUserData(NULL);
		world->DestroyBody(body);
		body = NULL;
	}
	listDestroy.clear();//列表清空

	//遍历更新刚体状态
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
				this->removeChild(po->dSp, true);//在布景里删除物体类对象中自己的精灵
				world->DestroyBody(po->body);//在物理世界中删除物体类对象中自己的刚体

				pom.erase(iter++);//在map里删掉物理类对象的指针
				delete po;//删除物体类对象指针
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


//执行相应的还原函数
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


void Beginlayer::Cut(float delta)  //消除粒子效果
{
	if (listForFire.empty())
		return;
	std::vector<ParticleFire*>::iterator il;
	il = listForFire.begin();
	this->removeChild(*il);
	listForFire.erase(il);
}

//开始触控事件的处理方法
bool Beginlayer::myOnTouchBegan(Touch *touch, Event *event)
{
	auto location = touch->getLocation();//获取触控点的位置
	Size visibleSize = Director::getInstance()->getVisibleSize();//获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();//获取可见区域原点坐标
	b2Vec2 locationWorld = b2Vec2((location.x - origin.x - visibleSize.width / 2) / pixToMeter, (location.y - origin.y - visibleSize.height / 2) / pixToMeter);

	
	for (int i = 0; i<3; i++)
	{
		//if (mj == NULL&&paddle->body->GetFixtureList()->TestPoint(locationWorld))//判断是否在触摸范围
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
//触控移动事件的处理方法
void Beginlayer::myOnTouchMoved(Touch *touch, Event *event)
{
	auto location = touch->getLocation();//获取触控点的位置
	Size visibleSize = Director::getInstance()->getVisibleSize();//获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();//获取可见区域原点坐标
	b2Vec2 locationWorld = b2Vec2((location.x - origin.x - visibleSize.width / 2) / pixToMeter, (location.y - origin.y - visibleSize.height / 2) / pixToMeter);

	for (int i = 0; i<3; i++)
	{
		if (mj != NULL)
		{
			mj->mJoint->SetTarget(locationWorld);
		}
	}
}
//触控结束事件的处理方法
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
//触控终止事件的处理方法
void Beginlayer::myOnTouchCancelled(Touch *touch, Event *event)
{
	myOnTouchEnded(touch, event);
}

//按下键盘时的处理方法
void Beginlayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_SPACE == keyCode && paddle->isSticky == true)
	{
		this->removeChild(paddle->dSp_ball, true);//在布景里删除物体类对象中自己的精灵
		paddle->dSp_ball = NULL;
		//world->DestroyBody(paddle->body_ball);//在物理世界中删除物体类对象中自己的刚体
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

	if (EventKeyboard::KeyCode::KEY_P == keyCode)//去下一关的作弊键
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
	//暂停所有定时器和动作
	pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//当前不是暂停状态且未过关***********************
	{
		//创建一个精灵对象，包含toumingBg.png图片
		toumingBgSp = Sprite::create("Image/toumingBg.png");
		//设置精灵对象的位置
		toumingBgSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//将精灵添加到背景中
		this->addChild(toumingBgSp, 2);
		PauseSp = Sprite::create("Image/suspend.png");//创建暂停后弹出的精灵
		PauseSp->setScale(0.6f);//设置精灵缩放比
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//设置精灵位置
		this->addChild(PauseSp, 3);//将精灵添加到背景精灵中

		auto resetItem = MenuItemImage::create//创建重来菜单                      
			(
			"Image/restart.png",	//平时的图片
			"Image/restart1.png",	//选中时的图片
			CC_CALLBACK_1(Beginlayer::menuReset, this) //点击时执行的回调方法
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
			CC_CALLBACK_1(Beginlayer::menuContinue, this) //点击时执行的回调方法
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
			CC_CALLBACK_1(Beginlayer::menuBack, this) //点击时执行的回调方法
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
		isPauseEnble = false;//暂停菜单不可用
	}
	else
	{
		isPause = false;
		isPauseEnble = true;//暂停菜单可用
	}
	isPause = true;
}

void Beginlayer::menuPause(Ref* pSender)
{
	//暂停所有定时器和动作
	pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//当前不是暂停状态且未过关***********************
	{
		//创建一个精灵对象，包含toumingBg.png图片
		toumingBgSp = Sprite::create("Image/toumingBg.png");
		//设置精灵对象的位置
		toumingBgSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//将精灵添加到背景中
		this->addChild(toumingBgSp, 2);
		PauseSp = Sprite::create("Image/suspend.png");//创建暂停后弹出的精灵
		PauseSp->setScale(0.6f);//设置精灵缩放比
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//设置精灵位置
		this->addChild(PauseSp, 3);//将精灵添加到背景精灵中

		auto resetItem = MenuItemImage::create//创建重来菜单        
			(
			"Image/restart.png",	//平时的图片
			"Image/restart1.png",	//选中时的图片
			CC_CALLBACK_1(Beginlayer::menuReset, this) //点击时执行的回调方法
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
			CC_CALLBACK_1(Beginlayer::menuContinue, this) //点击时执行的回调方法
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
			CC_CALLBACK_1(Beginlayer::menuBack, this) //点击时执行的回调方法
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
		isPauseEnble = false;//暂停菜单不可用
	}
	else
	{
		isPause = false;
		isPauseEnble = true;//暂停菜单可用
	}
	isPause = true;
}

void Beginlayer::goNext()
{
	//暂停所有定时器和动作
	pauseSchedulerAndActions();
	if (isWin == true)//当前不是暂停状态且未过关***********************
	{
		//创建一个精灵对象，包含toumingBg.png图片
		toumingBgSp = Sprite::create("Image/toumingBg.png");
		//设置精灵对象的位置
		toumingBgSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//将精灵添加到背景中
		this->addChild(toumingBgSp, 2);
		PauseSp = Sprite::create("Image/suspend.png");//创建暂停后弹出的精灵
		PauseSp->setScale(0.6f);//设置精灵缩放比
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//设置精灵位置
		this->addChild(PauseSp, 3);//将精灵添加到背景精灵中

		auto resetItem = MenuItemImage::create//创建重来菜单                
			(
			"Image/restart.png",	//平时的图片
			"Image/restart1.png",	//选中时的图片
			CC_CALLBACK_1(Beginlayer::menuReset, this) //点击时执行的回调方法
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
			CC_CALLBACK_1(Beginlayer::menuNext, this) //点击时执行的回调方法
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
			CC_CALLBACK_1(Beginlayer::menuBack, this) //点击时执行的回调方法
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
		isPauseEnble = false;//暂停菜单不可用
	}
	else
	{
		isPause = false;
		isPauseEnble = true;//暂停菜单可用
	}
	isPause = true;
}


void Beginlayer::menuReset(cocos2d::Ref*  pSender)
{
	/*//卸载定时器
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
	//恢复所有定时器和动作调用
	resumeSchedulerAndActions();
}

void Beginlayer::RestartGame()
{
	//暂停所有定时器和动作
	pauseSchedulerAndActions();
	if (isPause == false && isWin == false)//当前不是暂停状态且未过关***********************
	{
		//创建一个精灵对象，包含toumingBg.png图片
		toumingBgSp = Sprite::create("Image/toumingBg.png");
		//设置精灵对象的位置
		toumingBgSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//将精灵添加到背景中
		this->addChild(toumingBgSp, 2);
		PauseSp = Sprite::create("Image/suspend.png");//创建暂停后弹出的精灵
		PauseSp->setScale(0.6f);//设置精灵缩放比
		PauseSp->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20));//设置精灵位置
		this->addChild(PauseSp, 3);//将精灵添加到背景精灵中

		auto resetItem = MenuItemImage::create//创建重来菜单           
			(
			"Image/restart.png",	//平时的图片
			"Image/restart1.png",	//选中时的图片
			CC_CALLBACK_1(Beginlayer::menuReset, this) //点击时执行的回调方法
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
			CC_CALLBACK_1(Beginlayer::menuBack, this) //点击时执行的回调方法
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
		isPauseEnble = false;//暂停菜单不可用
	}
	else
	{
		//isPause = false;
		//isPauseEnble = true;//暂停菜单可用
	}
	isPause = true;
}
void Beginlayer::menuBack(cocos2d::Ref*  pSender)
{
	//卸载定时器
	unscheduleAllSelectors();
	gsm->goWelcomeScene();
}

void Beginlayer::menuNext(cocos2d::Ref*  pSender)
{
	//卸载定时器
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
	//卸载定时器
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
	//开始播放背景音效，false表示不循环
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/eatprops.wav", false);
	//设置音效音量0.0-1.0
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
}
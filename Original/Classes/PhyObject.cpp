#include "PhyObject.h"
#include "cocos2d.h"
#include <time.h>

b2Body* Create_Body(int type, int shape, std::string* id, Layer *layer, b2World* world, float* data, float density, float friction, float restitution, int groupIndex, int categoryBits, int maskBits)
{
	b2BodyDef bodyDef;       //创建刚体描述
	if (type==1)                                                          //动态刚体
		bodyDef.type = b2_dynamicBody;                                    
	else                                                                //静态刚体
		bodyDef.type = b2_staticBody;									
	bodyDef.position.Set(data[0] / pixToMeter, data[1] / pixToMeter);  //设置刚体位置
	b2Body* body = world->CreateBody(&bodyDef);                                //创建刚体对象
	body->SetUserData(id);                                             //记录对应的包装对象指针
	b2FixtureDef fixtureDef;                                       //创建刚体描述
	b2PolygonShape dynamicBox;                                          //创建矩形对象
	b2CircleShape dynamicCirecle;                                      //创建圆形对象
	if (shape == 1)													//刚体是矩形
	{
		dynamicBox.SetAsBox(data[2] / pixToMeter, data[3] / pixToMeter);    //设置半宽半高
		fixtureDef.shape = &dynamicBox;                                 //设置形状
	}
	else                                                            //刚体是圆形
	{
		dynamicCirecle.m_radius = data[2] / pixToMeter;                    //设置半径
		fixtureDef.shape = &dynamicCirecle;                            //设置形状
	}
	fixtureDef.density = density;                                  //设置密度
	fixtureDef.friction = friction;                                //设置摩擦系数
	fixtureDef.restitution = restitution;                          //设置恢复系数
	fixtureDef.filter.groupIndex = groupIndex;
	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits = maskBits;
	body->CreateFixture(&fixtureDef);                              //将描述与刚体结合
	body->SetLinearDamping(-0.0f);                                   //无阻尼
	return body;
}

Sprite* Create_Sprite(int shape, Layer *layer, b2World* world, float* data, std::string pic)
{
	Sprite* dSp = Sprite::create(pic);                                         //创建精灵
	layer->addChild(dSp, 1);                                           //将精灵添加到布景
	Size size = dSp->getContentSize();                                 //获取精灵尺寸
	float pw = data[2] * 2;                                            //计算精灵宽度
	float ph;
	if (shape==1)                                                     //矩形
		ph = data[3] * 2;                                            //计算精灵长度
	else                                                              //圆形
		ph = data[2] * 2;
	float scaleX = pw / size.width;                                    //计算x,y方向缩放比
	float scaleY = ph / size.height;
	dSp->setScaleX(scaleX);                                            //设置x,y方向缩放比
	dSp->setScaleY(scaleY);
	return dSp;
}

PhyObject::PhyObject(std::string* id,
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,
	float density,
	float friction,
	float restitution){
	body = NULL;
    this->poId = id;    //设置物体id
	HP = 0;
	attack = 0;
}

PhyObject::~PhyObject()
{
	delete poId;        //删除物体id
}

void PhyObject::refresh()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();    //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();      //获取可见区域原点坐标
	if (body) 
	{
		b2Vec2 position = body->GetPosition();                           //获取物体对应刚体位置
		float angle = body->GetAngle();
		dSp->setPosition(
			Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
			origin.y + visibleSize.height / 2 + position.y * pixToMeter));
		dSp->setRotation(-angle*180.0 / 3.1415926);
	}
}

void Ball::refresh()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();    //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();      //获取可见区域原点坐标
	if (body)
	{
		b2Vec2 position = body->GetPosition();                           //获取物体对应刚体位置
		float angle = body->GetAngle();
		dSp->setPosition(
			Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
			origin.y + visibleSize.height / 2 + position.y * pixToMeter));
		cps->setPosition(Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
			origin.y + visibleSize.height / 2 + position.y * pixToMeter));//位置
		dSp->setRotation(-angle*180.0 / 3.1415926);
	}
}

void Paddle::refresh()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();    //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();      //获取可见区域原点坐标
	if (body)
	{
		b2Vec2 position = body->GetPosition();                           //获取物体对应刚体位置
		float angle = body->GetAngle();
		if (dSp != NULL)
		{
			dSp->setPosition(
				Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
				origin.y + visibleSize.height / 2 + position.y * pixToMeter));
			dSp->setRotation(-angle*180.0 / 3.1415926);
		}
		if (dSp_ball != NULL)
		{
			if (isReversal)
			{
				position = body_paddle->GetPosition();
				float angle = body_paddle->GetAngle();
			}
			dSp_ball->setPosition(
				Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
				origin.y + visibleSize.height / 2 + position.y * pixToMeter + Paddle::ball_y));
			dSp_ball->setRotation(-angle*180.0 / 3.1415926);
		}
	}
	if (body_paddle != NULL)
	{
		b2Vec2 position = body_paddle->GetPosition();
		float angle = body_paddle->GetAngle();
		if (dSp_paddle != NULL)
		{
			dSp_paddle->setPosition(
				Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
				origin.y + visibleSize.height / 2 + position.y * pixToMeter));
			dSp_paddle->setRotation(-angle*180.0 / 3.1415926);
		}
	}
}

Paddle::Paddle(std::string* id,
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution,
	int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, 1, 2, 4);
	dSp = Create_Sprite(1, layer, world, data, pic);
	body->SetFixedRotation(true);                             //设置挡板不旋转
	body_ball = NULL;
	body_paddle = NULL;
	dSp_ball = NULL;
	dSp_paddle = NULL;
	isSticky = false;
	isReversal = false;
	isImage = false;
	HP = i_HP;
}

void Paddle::Is_Sticky(b2World* world, Layer* layer, float* data)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();    //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();      //获取可见区域原点坐标
	dSp_ball = Sprite::create("Image/Ball1.png");                                         //创建精灵
	layer->addChild(dSp_ball, 1);                                           //将精灵添加到布景
	dSp_ball->setPosition(
		Point(origin.x + visibleSize.width / 2 + data[0] * pixToMeter + ball_x,
		origin.y + visibleSize.height / 2 + data[1] * pixToMeter + ball_y));
	Size size = dSp_ball->getContentSize();                                 //获取精灵尺寸
	float pw = data[2] * 2;                                            //计算精灵宽度
	float ph = data[2] * 2;                                            //计算精灵长度
	float scaleX = pw / size.width;                                    //计算x,y方向缩放比
	float scaleY = ph / size.height;
	dSp_ball->setScaleX(scaleX);                                            //设置x,y方向缩放比
	dSp_ball->setScaleY(scaleY);
}

Ball::Ball(std::string* id,
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半径
	float density,
	float friction,
	float restitution,int i_attack) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 0, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(0, layer, world, data, pic);
	attack = i_attack;
	cps = ParticleMeteor::create();
	cps->retain();
	cps->setScale(0.8);
	cps->setPosition(ccp(data[0], data[1]));//位置
	cps->setLife(0.06f);//每个粒子生命周期
	layer->addChild(cps);//加到精灵图
}

int Common_Brick::index = 0;
int Hard_Brick::index = 0;
int Sticky_Brick::index = 0;
int Lengthen_Brick::index = 0;
int Shorten_Brick::index = 0;
int Accelerate_Brick::index = 0;
int Decelerate_Brick::index = 0;
int Upgrade_Brick::index = 0;
int Transmit_Brick::index = 0;
int Reversal_Brick::index = 0;
int Image_Brick::index = 0;
int Fast_Brick::index = 0;

int Lengthen_Pack::index = 0;
int Shorten_Pack::index = 0;
int Accelerate_Pack::index = 0;
int Decelerate_Pack::index = 0;
int Upgrade_Pack::index = 0;
int Sticky_Pack::index = 0;
int Reversal_Pack::index = 0;
int Image_Pack::index = 0;
int Fast_Pack::index = 0;

int Ball::index = 0;
int Paddle::index = 0;
int Wall::index = 0;
bool Ball::isFast = false;
float Ball::radius = 15.0;
float Ball::speed = 0;
float Ball::s_speed = 0;
float Paddle::ball_x = 0.0;
float Paddle::ball_y = 40.0;
float Paddle::length = 60.0;
float Paddle::width = 20.0;
float Paddle::s_length = 60.0;
float Paddle::s_width = 20.0;


Wall::Wall(std::string* id,
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	//创建线性刚体
	b2BodyDef bodyDef;	//创建刚体描述
	float positionX = (data[0] + data[2]) / 2;//计算刚体中心位置的X坐标
	float positionY = (data[1] + data[3]) / 2;//计算刚体中心位置的Y坐标
	bodyDef.position.Set(positionX / pixToMeter, positionY / pixToMeter);//设置刚体位置
	body = world->CreateBody(&bodyDef);//创建刚体对象
	body->SetUserData(id);//在刚体中记录对应的包装对象指针
	b2EdgeShape shape;//创建线形物体类对象
	shape.Set(b2Vec2((data[0] - positionX) / pixToMeter, (data[1] - positionY) / pixToMeter), b2Vec2((data[2] - positionX) / pixToMeter, (data[3] - positionY) / pixToMeter));//设置位置
	b2FixtureDef fixtureDef;//创建刚体物理描述
	fixtureDef.shape = &shape;//设置形状
	fixtureDef.density = density;//设置密度
	fixtureDef.friction = friction;//设置摩擦系数
	fixtureDef.restitution = restitution;//设置恢复系数
	if (index == 1)
	{
		fixtureDef.filter.categoryBits = 0;
	}
	else
	{
		fixtureDef.filter.groupIndex = 1;
		fixtureDef.filter.categoryBits = 2;
		fixtureDef.filter.maskBits = 4;
	}
	body->CreateFixture(&fixtureDef);//将物理描述与刚体结合
	body->SetLinearDamping(0);
	dSp = Sprite::create(pic);
	layer->addChild(dSp, 1);//将精灵添加到布景中
	Size size = dSp->getContentSize();//获取精灵的尺寸
	b2Vec2 v1 = shape.m_vertex1;//v1赋值为线形第一个顶点
	b2Vec2 v2 = shape.m_vertex2;//v2赋值为线形第二个顶点
	b2Vec2 v3 = v2 - v1;
	float scaleX, scaleY;
	if (v3.x == 0)
	{
		scaleX = v3.x / size.height;//计算出精灵Y方向缩放比
		scaleY = v3.Length()*pixToMeter / size.width;//计算出精灵X方向缩放比
	}
	else if (v3.y == 0)
	{
		scaleX = v3.Length()*pixToMeter / size.width;//计算出精灵X方向缩放比
		scaleY = 3 / size.height;//计算出精灵Y方向缩放比
	}
	dSp->setScaleX(scaleX);//设置精灵X方向缩放比
	dSp->setScaleY(scaleY);//设置精灵Y方向缩放比
}

//砖块类
Common_Brick::Common_Brick(std::string* id,                //普通砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Sticky_Brick::Sticky_Brick(std::string* id,                      //粘黏砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Reversal_Brick::Reversal_Brick(std::string* id,						//颠倒砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Image_Brick::Image_Brick(std::string* id,                //镜像砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Fast_Brick::Fast_Brick(std::string* id,                //穿透砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Hard_Brick::Hard_Brick(std::string* id,                //钢铁砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = 1000000007;
}

Lengthen_Brick::Lengthen_Brick(std::string* id,                //增长砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Shorten_Brick::Shorten_Brick(std::string* id,                //缩短砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Accelerate_Brick::Accelerate_Brick(std::string* id,                //加速砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Decelerate_Brick::Decelerate_Brick(std::string* id,                //减速砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Upgrade_Brick::Upgrade_Brick(std::string* id,                //升级砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

Transmit_Brick::Transmit_Brick(std::string* id,                //传送砖块构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution, int i_HP) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(0, 1, id, layer, world, data, density, friction, restitution, 2, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
	HP = i_HP;
}

//砖块作用函数
void Lengthen_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //增长砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AL%d", ++Lengthen_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Lengthen_Pack* pack = new Lengthen_Pack(ids, layer, world, "Image/Lengthen_Shorten_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

void Shorten_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //缩短砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AB%d", ++Shorten_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Shorten_Pack* pack = new Shorten_Pack(ids, layer, world, "Image/Lengthen_Shorten_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

void Accelerate_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //加速砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AA%d", ++Accelerate_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Accelerate_Pack* pack = new Accelerate_Pack(ids, layer, world, "Image/Accelerate_Decelerate_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

void Decelerate_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //减速砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AD%d", ++Decelerate_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Decelerate_Pack* pack = new Decelerate_Pack(ids, layer, world, "Image/Accelerate_Decelerate_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

void Upgrade_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //升级砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AU%d", ++Upgrade_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Upgrade_Pack* pack = new Upgrade_Pack(ids, layer, world, "Image/Upgrade_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

void Transmit_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //传送砖块的功能函数
{
	b2Vec2 position = ball->body->GetPosition();
	float d = 9999997.0;
	std::string ids;
	int num;
	for (int i = 1; i <= Transmit_Brick::index; i++)
	{
		ids = std::string(StringUtils::format("BT%d", i));
		PhyObject* po = pom[ids];
		b2Vec2 pos = po->body->GetPosition();
		float d1 = sqrt((position.x - pos.x) * (position.x - pos.x) + (position.y - pos.y) * (position.y - pos.y));
		if (d1 < d)
		{
			d = d1;
			num = i;
		}
	}
	srand((unsigned)time(NULL));
	int cnt = rand() % Transmit_Brick::index + 1;
	while (cnt == num)
	{
		cnt = rand() % Transmit_Brick::index + 1;
	}
	ids = std::string(StringUtils::format("BT%d", cnt));
	PhyObject* po = pom[ids];
	b2Vec2 pos = po->body->GetPosition();
	pos.y -= ((15 + Ball::radius) / pixToMeter);
	ball->body->SetLinearVelocity(b2Vec2(0.0f, -abs(Ball::speed)));
	ball->body->SetTransform(pos, 0);
}

void Sticky_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle) //粘黏砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AS%d", ++Sticky_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Sticky_Pack* pack = new Sticky_Pack(ids, layer, world, "Image/Sticky_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

void Reversal_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //颠倒砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AR%d", ++Reversal_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Reversal_Pack* pack = new Reversal_Pack(ids, layer, world, "Image/Reversal_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

void Image_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //镜像砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AI%d", ++Image_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Image_Pack* pack = new Image_Pack(ids, layer, world, "Image/Image_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

void Fast_Brick::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //穿透砖块的功能函数
{
	std::string* ids = new std::string(StringUtils::format("AF%d", ++Fast_Pack::index));
	float* data = new float[4]{x, y, 12.0, 12.0};
	Fast_Pack* pack = new Fast_Pack(ids, layer, world, "Image/Fast_Pack.png", data, 1, 0.0f, 1.0f);
	b2Vec2 vec(0.0f, -8.0f);
	pack->body->SetLinearVelocity(vec);
	pom[*ids] = pack;
}

//包裹类
Lengthen_Pack::Lengthen_Pack(std::string* id,               //增长包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

Shorten_Pack::Shorten_Pack(std::string* id,               //缩短包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

Accelerate_Pack::Accelerate_Pack(std::string* id,               //加速包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

Decelerate_Pack::Decelerate_Pack(std::string* id,               //减速包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

Upgrade_Pack::Upgrade_Pack(std::string* id,               //升级包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

Sticky_Pack::Sticky_Pack(std::string* id,				//粘黏包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

Image_Pack::Image_Pack(std::string* id,				//镜像包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

Reversal_Pack::Reversal_Pack(std::string* id,					//颠倒包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

Fast_Pack::Fast_Pack(std::string* id,				//镜像包裹构造函数
	Layer *layer,
	b2World* world,
	std::string pic,
	float* data,      //data[0]为x坐标,data[1]为y坐标,data[2]为半宽,data[3]为半高
	float density,
	float friction,
	float restitution) :
	PhyObject(id, layer, world, pic, data, density, friction, restitution){
	body = Create_Body(1, 1, id, layer, world, data, density, friction, restitution, -1, 4, 2);
	dSp = Create_Sprite(1, layer, world, data, pic);
}

//包裹效果实现
void Lengthen_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //增长效果
{
	Paddle* po = (Paddle*)paddle;
	if (Paddle::length * 1.2f > 1024)
		return;
	b2Fixture* fixture = paddle->body->GetFixtureList();
	b2Filter p_filter = fixture->GetFilterData();
	po->body->DestroyFixture(fixture);
	b2PolygonShape dynamicBox;
	Paddle::length *= 1.3f;
	dynamicBox.SetAsBox(Paddle::length / pixToMeter, Paddle::width / pixToMeter);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1000.0f;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 1;
	fixtureDef.filter = p_filter;
	po->body->CreateFixture(&fixtureDef);
	Size size = paddle->dSp->getContentSize();
	float pw = Paddle::length * 2;
	float scaleX = pw / size.width;
	po->dSp->setScaleX(scaleX);

	if (po->body_paddle != NULL)
	{
		b2Fixture* fixture = po->body_paddle->GetFixtureList();
		b2Filter p_filter = fixture->GetFilterData();
		po->body_paddle->DestroyFixture(fixture);
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(Paddle::length / pixToMeter, Paddle::width / pixToMeter);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1000.0f;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 1;
		fixtureDef.filter = p_filter;
		po->body_paddle->CreateFixture(&fixtureDef);
		Size size = po->dSp_paddle->getContentSize();
		float pw = Paddle::length * 2;
		float scaleX = pw / size.width;
		po->dSp_paddle->setScaleX(scaleX);
	}
}

void Shorten_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //缩短效果
{
	Paddle* po = (Paddle*)paddle;
	b2Fixture* fixture = po->body->GetFixtureList();
	b2Filter p_filter = fixture->GetFilterData();
	po->body->DestroyFixture(fixture);
	b2PolygonShape dynamicBox;
	Paddle::length *= 0.7f;
	dynamicBox.SetAsBox(Paddle::length / pixToMeter, Paddle::width / pixToMeter);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1000.0f;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 1;
	fixtureDef.filter = p_filter;
	po->body->CreateFixture(&fixtureDef);
	Size size = po->dSp->getContentSize();
	float pw = Paddle::length * 2;
	float scaleX = pw / size.width;
	po->dSp->setScaleX(scaleX);

	if (po->body_paddle != NULL)
	{
		b2Fixture* fixture = po->body_paddle->GetFixtureList();
		b2Filter p_filter = fixture->GetFilterData();
		po->body_paddle->DestroyFixture(fixture);
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(Paddle::length / pixToMeter, Paddle::width / pixToMeter);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1000.0f;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 1;
		fixtureDef.filter = p_filter;
		po->body_paddle->CreateFixture(&fixtureDef);
		Size size = po->dSp_paddle->getContentSize();
		float pw = Paddle::length * 2;
		float scaleX = pw / size.width;
		po->dSp_paddle->setScaleX(scaleX);
	}
}

void Accelerate_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //加速效果
{
	Ball::speed *= 1.2f;
}

void Decelerate_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //减速效果
{
	Ball::speed *= 0.8f;
}

void Upgrade_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //升级效果
{
	Paddle* pd = (Paddle*)paddle;
	if (pd->isSticky == true)
		return;
	Ball* po = (Ball*)ball;
	CCTexture2D* texture;
	if (++po->attack <= 3)
		texture = CCTextureCache::sharedTextureCache()->addImage("Image/Ball" + StringUtils::format("%d", po->attack) + ".png");
	else
	{
		texture = CCTextureCache::sharedTextureCache()->addImage("Image/Ball4.png"); po->attack = 1000000007;
	}
	po->dSp->setTexture(texture);
}

void Sticky_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //粘黏效果
{
	Paddle* po = (Paddle*)paddle;
	Ball* ba = (Ball*)ball;
	if (po->isSticky == true)
		return;
	std::string* ids = ball->poId;
	po->isSticky = true;
	layer->removeChild(ba->cps, true);
	layer->removeChild(ball->dSp, true);//在布景里删除球对象中自己的精灵
	world->DestroyBody(ball->body);//在物理世界中删除球对象中自己的刚体
	pom.erase(*ids);//在map里删掉球的指针
	delete ball;//删除球对象指针
	ball = NULL;
	b2Vec2 vec;
	if (po->isReversal == true)
		vec = po->body_paddle->GetPosition();
	else
		vec = po->body->GetPosition();
	float* data = new float[3]{vec.x * pixToMeter + Paddle::ball_x, vec.y * pixToMeter + Paddle::ball_y, Ball::radius};
	po->Is_Sticky(world, layer, data);
}

void Reversal_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //颠倒效果
{
	Paddle* po = (Paddle*)paddle;
	if (po->isReversal == true)
		return;
	po->isReversal = true;
	b2Vec2 vec = po->body->GetPosition();
	if (po->isImage == true)
	{
		b2Vec2 vec1 = po->body_paddle->GetPosition();
		Vec2 vec2 = po->dSp->getPosition();
		Vec2 vec3 = po->dSp_paddle->getPosition();
		po->body->SetTransform(vec, 0);
		po->dSp->setPosition(vec2);
		po->body_paddle->SetTransform(vec1, 0);
		po->dSp_paddle->setPosition(vec3);
	}
	else
	{
		x = vec.x * pixToMeter;
		y = vec.y * pixToMeter;
		float* data = new float[4]{x, y, po->length, po->width};
		b2Filter filter;
		filter.categoryBits = 0;
		po->body->GetFixtureList()->SetFilterData(filter);
		po->body_paddle = Create_Body(1, 1, po->poId, layer, world, data, 1000.0f, 0.0f, 1.0f, 2, 2, 4);
		po->dSp_paddle = Create_Sprite(1, layer, world, data, "Image/paddle.png");
		po->body_paddle->SetFixedRotation(true);//设置挡板副本不旋转
		Sprite* Sp = Sprite::create("Image/empty.png");
		po->dSp->setTexture(Sp->getTexture());
	}
}

void Image_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //镜像效果
{
	Paddle* po = (Paddle*)paddle;
	if (po->isImage == true)
		return;
	po->isImage = true;
	b2Vec2 vec;
	if (po->isReversal == true)
	{
		b2Vec2 vec1 = po->body_paddle->GetPosition();
		Vec2 vec2 = po->dSp_paddle->getPosition();
		po->body->SetTransform(vec1, 0);
		po->dSp->setPosition(vec2);
		Sprite* Sp = Sprite::create("Image/paddle.png");
		po->dSp->setTexture(Sp->getTexture());
		b2Filter filter;
		filter.groupIndex = 1;
		filter.categoryBits = 2;
		filter.maskBits = 4;
		po->body->GetFixtureList()->SetFilterData(filter);
	}
	else
	{
		vec = po->body->GetPosition();
		x = vec.x * pixToMeter;
		y = vec.y * pixToMeter;
		float* data = new float[4]{x, y, po->length, po->width};
		po->body_paddle = Create_Body(1, 1, po->poId, layer, world, data, 1000.0f, 0.0f, 1.0f, 2, 2, 4);
		po->dSp_paddle = Create_Sprite(1, layer, world, data, "Image/paddle.png");
		po->body_paddle->SetFixedRotation(true);//设置挡板副本不旋转
	}
}

void Fast_Pack::Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle)  //穿透效果
{
	if (Ball::isFast == true)
		return;
	Paddle* pd = (Paddle*)paddle;
	if (pd->isSticky == true)
		return;
	Ball* po = (Ball*)ball;
	Ball::isFast = true;
	layer->removeChild(po->cps);
	po->cps = ParticleSun::create();
	po->cps->retain();
	po->cps->setScale(1.0);
	//po->cps->setPosition(ccp(x, y));//位置
	po->cps->setLife(0.06f);//每个粒子生命周期
	layer->addChild(po->cps);//加到精灵图
}

//包裹效果还原
void Reversal_Pack::Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle)  //颠倒还原
{
	Paddle* po = (Paddle*)paddle;
	po->isReversal = false;
	b2Vec2 vec = po->body->GetPosition();
	if (po->isImage == true)
	{
		b2Vec2 vec1 = po->body_paddle->GetPosition();
		Vec2 vec2 = po->dSp->getPosition();
		Vec2 vec3 = po->dSp_paddle->getPosition();
		po->body->SetTransform(vec, 0);
		po->dSp->setPosition(vec2);
		po->body_paddle->SetTransform(vec1, 0);
		po->dSp_paddle->setPosition(vec3);
	}
	else
	{
		b2Vec2 vec1 = po->body_paddle->GetPosition();
		Vec2 vec2 = po->dSp_paddle->getPosition();
		po->body->SetTransform(vec1, 0);
		po->dSp->setPosition(vec2);
		layer->removeChild(po->dSp_paddle, true);//在布景里删除物体类对象中自己的精灵
		world->DestroyBody(po->body_paddle);//在物理世界中删除物体类对象中自己的刚体
		Sprite* Sp = Sprite::create("Image/paddle.png");
		po->dSp->setTexture(Sp->getTexture());
		b2Filter filter;
		filter.groupIndex = 1;
		filter.categoryBits = 2;
		filter.maskBits = 4;
		po->body->GetFixtureList()->SetFilterData(filter);
		po->dSp_paddle = NULL;
		po->body_paddle = NULL;
	}
}

void Image_Pack::Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle)   //镜像还原
{
	Paddle* po = (Paddle*)paddle;
	po->isImage = false;
	b2Vec2 vec = po->body->GetPosition();
	if (po->isReversal == true)
	{
		Sprite* Sp = Sprite::create("Image/empty.png");
		po->dSp->setTexture(Sp->getTexture());
		b2Filter filter;
		filter.categoryBits = 0;
		po->body->GetFixtureList()->SetFilterData(filter);
	}
	else
	{
		layer->removeChild(po->dSp_paddle, true);//在布景里删除物体类对象中自己的精灵
		world->DestroyBody(po->body_paddle);//在物理世界中删除物体类对象中自己的刚体
		po->dSp_paddle = NULL;
		po->body_paddle = NULL;
	}
}

void Lengthen_Pack::Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle)    //增长还原
{
	Paddle* po = (Paddle*)paddle;
	b2Fixture* fixture = po->body->GetFixtureList();
	b2Filter p_filter = fixture->GetFilterData();
	po->body->DestroyFixture(fixture);
	b2PolygonShape dynamicBox;
	Paddle::length = Paddle::s_length;
	dynamicBox.SetAsBox(Paddle::length / pixToMeter, Paddle::width / pixToMeter);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1000.0f;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 1;
	fixtureDef.filter = p_filter;
	po->body->CreateFixture(&fixtureDef);
	Size size = po->dSp->getContentSize();
	float pw = Paddle::length * 2;
	float scaleX = pw / size.width;
	po->dSp->setScaleX(scaleX);

	if (po->body_paddle != NULL)
	{
		b2Fixture* fixture = po->body_paddle->GetFixtureList();
		b2Filter p_filter = fixture->GetFilterData();
		po->body_paddle->DestroyFixture(fixture);
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(Paddle::length / pixToMeter, Paddle::width / pixToMeter);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1000.0f;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 1;
		fixtureDef.filter = p_filter;
		po->body_paddle->CreateFixture(&fixtureDef);
		Size size = po->dSp_paddle->getContentSize();
		float pw = Paddle::length * 2;
		float scaleX = pw / size.width;
		po->dSp_paddle->setScaleX(scaleX);
	}
}

void Shorten_Pack::Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle)       //缩短还原
{
	Paddle* po = (Paddle*)paddle;
	b2Fixture* fixture = po->body->GetFixtureList();
	b2Filter p_filter = fixture->GetFilterData();
	po->body->DestroyFixture(fixture);
	b2PolygonShape dynamicBox;
	Paddle::length = Paddle::s_length;
	dynamicBox.SetAsBox(Paddle::length / pixToMeter, Paddle::width / pixToMeter);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1000.0f;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 1;
	fixtureDef.filter = p_filter;
	po->body->CreateFixture(&fixtureDef);
	Size size = po->dSp->getContentSize();
	float pw = Paddle::length * 2;
	float scaleX = pw / size.width;
	po->dSp->setScaleX(scaleX);
	if (po->body_paddle != NULL)
	{
		b2Fixture* fixture = po->body_paddle->GetFixtureList();
		b2Filter p_filter = fixture->GetFilterData();
		po->body_paddle->DestroyFixture(fixture);
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(Paddle::length / pixToMeter, Paddle::width / pixToMeter);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1000.0f;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 1;
		fixtureDef.filter = p_filter;
		po->body_paddle->CreateFixture(&fixtureDef);
		Size size = po->dSp_paddle->getContentSize();
		float pw = Paddle::length * 2;
		float scaleX = pw / size.width;
		po->dSp_paddle->setScaleX(scaleX);
	}
}

void Accelerate_Pack::Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle)    //加速还原
{
	Ball::speed = Ball::s_speed;
}

void Decelerate_Pack::Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle)    //减速还原
{
	Ball::speed = Ball::s_speed;
}

void Upgrade_Pack::Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle)    //升级还原
{
	Paddle* pd = (Paddle*)paddle;
	if (pd->isSticky == true)
		return;
	Ball* po = (Ball*)ball;
	po->attack = 1;
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("Image/Ball1.png");
	po->dSp->setTexture(texture);
}

void Fast_Pack::Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle)   //穿透还原
{
	if (Ball::isFast == false)
		return;
	Ball::isFast = false;
	Paddle* pd = (Paddle*)paddle;
	if (pd->isSticky == true)
		return;
	Ball* po = (Ball*)ball;
	layer->removeChild(po->cps);
	po->cps = ParticleMeteor::create();
	po->cps->retain();
	po->cps->setScale(0.8);
	//po->cps->setPosition(ccp(x, y));//位置
	po->cps->setLife(0.06f);//每个粒子生命周期
	layer->addChild(po->cps);//加到精灵图
}

//砖块HP改变后修改精灵图片的函数
void Common_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Common_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Sticky_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Sticky_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Reversal_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Reversal_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Image_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Image_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Lengthen_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Lengthen_Shorten_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Shorten_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Lengthen_Shorten_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Accelerate_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Accelerate_Decelerate_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Decelerate_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Accelerate_Decelerate_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Upgrade_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Upgrade_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}

void Fast_Brick::HPchange(PhyObject* po)
{
	Sprite* Sp = Sprite::create("Image/Fast_Brick" + StringUtils::format("%d", po->HP) + ".png");
	po->dSp->setTexture(Sp->getTexture());
}
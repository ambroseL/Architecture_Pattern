#include "ObjManager.h"
#include "LengthenPack.h"
#include "ImagePack.h"
#include "PermeatPack.h"
#include "ReversalPack.h"
#include "UpgradePack.h"
#include "AcceleratePack.h"
#include "StickyPack.h"
#include "ImageBrick.h"
#include "LengthenBrick.h"
#include "PermeatBrick.h"
#include "ReversalBrick.h"
#include "DeaccelerateBrick.h"
#include "TransmitBrick.h"
#include "UpgradeBrick.h"
#include "StickyBrick.h"
#include "ObjSpawner.h"
#include "WallObj.h"
#include "LevelData.h"
#include "ShortenPack.h"
#include "DeacceleratePack.h"
#include "ShortenBrick.h"
#include "AccelerateBrick.h"


struct pos
{
	float x;
	float y;
	int cnt;
};

ObjManager::ObjManager():ball(nullptr),paddle(nullptr),imgPaddle(nullptr),layer(nullptr),world(nullptr)
{
	//清空待删除和待还原列表
	resetLengthenPackList.clear();
	resetShortenPackList.clear();
	resetImagePackList.clear();
	resetPermeatPackList.clear();
	resetReversalPackList.clear();
	resetAcceleratePackList.clear();
	resetDeacceleratePackList.clear();
	resetUpgradePackList.clear();
	deleteObjList.clear();
	deleteParticleList.clear();
	
	//清空物体ID与物体间的映射
	objMap.clear();
	
	objTexturePathMap.clear();
	//建立贴图路径与类名间的映射
	objTexturePathMap['C'] = "Image/Common_Brick";
	objTexturePathMap['L'] = "Image/Lengthen_Shorten_Brick";
	objTexturePathMap['S'] = "Image/Lengthen_Shorten_Brick";
	objTexturePathMap['I'] = "Image/Image_Brick";
	objTexturePathMap['F'] = "Image/Fast_Brick";
	objTexturePathMap['R'] = "Image/Reversal_Brick";
	objTexturePathMap['U'] = "Image/Upgrade_Brick";
	objTexturePathMap['A'] = "Image/Accelerate_Decelerate_Brick";
	objTexturePathMap['D'] = "Image/Accelerate_Decelerate_Brick";
	objTexturePathMap['G'] = "Image/Sticky_Brick";

	//建立包裹效果函数与类名间的映射
	packWorkFuncMap.clear();
	packWorkFuncMap['I'] = &ObjManager::imgPackWork;
	packWorkFuncMap['L'] = &ObjManager::lengthenPackWork;
	packWorkFuncMap['S'] = &ObjManager::shortenPackWork;
	packWorkFuncMap['F'] = &ObjManager::permeatPackWork;
	packWorkFuncMap['R'] = &ObjManager::reversalPackWork;
	packWorkFuncMap['A'] = &ObjManager::acceleratePackWork;
	packWorkFuncMap['D'] = &ObjManager::deacceleratePackWork;
	packWorkFuncMap['U'] = &ObjManager::upgradePackWork;
	packWorkFuncMap['G'] = &ObjManager::stickyPackWork;

	brickWorkFuncMap['I'] = &ObjManager::imgBrickWork;
	brickWorkFuncMap['L'] = &ObjManager::lengthenBrickWork;
	brickWorkFuncMap['S'] = &ObjManager::shortenBrickWork;
	brickWorkFuncMap['F'] = &ObjManager::permeatBrickWork;
	brickWorkFuncMap['R'] = &ObjManager::reversalBrickWork;
	brickWorkFuncMap['A'] = &ObjManager::accelerateBrickWork;
	brickWorkFuncMap['D'] = &ObjManager::deaccelerateBrickWork;
	brickWorkFuncMap['U'] = &ObjManager::upgradeBrickWork;
	brickWorkFuncMap['G'] = &ObjManager::stickyBrickWork;

	imagePackIndex = 0;
	reversalPackIndex = 0;
	lengthenPackIndex = 0;
	shortenPackIndex = 0;
	acceleratePackIndex = 0;
	deacceleratePackIndex = 0;
	upgradePackIndex = 0;
	permeatPackIndex = 0;
	stickyPackIndex = 0;
	transmitBrickIndex = 0;
	ballObjIndex = 0;
	brickCount = 0;
}

ObjManager::~ObjManager()
{
}

void ObjManager::createObj(int level, b2World* bWorld, Layer* Llayer)
{
	world = bWorld;
	layer = Llayer;

	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	EntityObj* po;
	GraphicsComponent* graphicsComponent;
	PhysicsComponent* physicsComponent;
	b2Body* body;
	Sprite* sprite;
	float* data;
	std::string* ids;

	//创建地面刚体
	data = new float[4]{ -512, -384, 512, -384 };
	ids = new std::string(StringUtils::format("W%d", 1));      //Ground
	body = createWallBody(1,ids, world, data, 1, 0.0f, 1.0f);
	sprite = createWallSprite(data, "Image/blockRed.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	physicsComponent = new PhysicsComponent(body);
	WallObj* ground = new WallObj(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = ground;

	//创建上面刚体
	data = new float[4]{ -512, 384, 512, 384 };
	ids = new std::string(StringUtils::format("W%d", 2));
	body = createWallBody(2, ids, world, data, 1, 0.0f, 1.0f);
	sprite = createWallSprite(data, "Image/blockRed.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	physicsComponent = new PhysicsComponent(body);
	ground = new WallObj(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = ground;

	//创建左墙面刚体
	data = new float[4]{ -512, -384, -512, 384 };
	ids = new std::string(StringUtils::format("W%d", 3));
	body = createWallBody(3, ids, world, data, 1, 0.0f, 1.0f);
	sprite = createWallSprite(data, "Image/blockRed.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	physicsComponent = new PhysicsComponent(body);
	ground = new WallObj(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = ground;


	//创建右墙面刚体
	data = new float[4]{ 512, -384, 512, 384 };
	ids = new std::string(StringUtils::format("W%d", 4));
	body = createWallBody(4, ids, world, data, 1, 0.0f, 1.0f);
	sprite = createWallSprite(data, "Image/blockRed.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	physicsComponent = new PhysicsComponent(body);
	ground = new WallObj(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = ground;
	

	//创建挡板
	float sWidth = 75.0;				/*初始宽度*/
	float sHeight = 20.0;				/*初始高度*/

	data = new float[4]{ 0, -364, sWidth, sHeight };
	ids = new std::string(StringUtils::format("P%d", 0));
	sprite = createSprite(1,data, "Image/paddle.png");
	layer->addChild(sprite);
	body = createBody(1, 1, ids, world, data, 1000.0f, 0.0f, 1.0f, 1, 2, 4);
	graphicsComponent = new GraphicsComponent(sprite);
	physicsComponent = new PhysicsComponent(body);
	paddle = new PaddleObj(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = paddle;
	paddle->setSticky(true);

	//创建球
	float fRadius = 15.0;				/*球的半径*/
	float fBallX = 0.0;					/*球与挡板的位置X偏移量*/
	float fBallY = fRadius + sHeight;	/*球与挡板的位置Y偏移量*/

	b2Vec2 vec = paddle->getPosition();
	data = new float[3]{ vec.x * pixToMeter + fBallX, vec.y * pixToMeter + fBallY, fRadius};
	ids = new std::string(StringUtils::format("Q%d", ++ballObjIndex));
	Sprite* spriteBall = createSprite(0, data, "Image/Ball1.png");
	layer->addChild(spriteBall);
	spriteBall->setPosition(Point(origin.x + visibleSize.width / 2 + data[0] * pixToMeter + fBallX,
		origin.y + visibleSize.height / 2 + data[1] * pixToMeter + fBallY));
    body = createBody(1, 0, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	graphicsComponent = new GraphicsComponent(spriteBall);
	ball = new BallObj(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = ball;


	//各类砖块模板
	BrickObj* brickObjPrototype = nullptr;
	LengthenBrick* lengthenBrickPrototype = nullptr;
	ShortenBrick* shortenBrickPrototype = nullptr;
	ReversalBrick* reversalBrickPrototype = nullptr;
	ImageBrick* imageBrickPrototype = nullptr;
	AccelerateBrick* accelerateBrickPrototype = nullptr;
	DeaccelerateBrick* decelerateBrickPrototype = nullptr;
	PermeatBrick* permeatBrickPrototype = nullptr;
	StickyBrick* stickyBrickPrototype = nullptr;
	UpgradeBrick* upgradeBrickPrototype = nullptr;

	ObjSpawner* objSpawner;

	//创建普通砖块模板
	data = new float[4]{ 0.0f, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BC%d", 0));
	sprite = createSprite(1, data, "Image/Common_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	brickObjPrototype = new BrickObj(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = brickObjPrototype;

	//创建长度砖块模板
	data = new float[4]{ -61, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BL%d", 0));
	sprite = createSprite(1, data, "Image/lengthen_Shorten_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	lengthenBrickPrototype = new LengthenBrick(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = lengthenBrickPrototype;

	data = new float[4]{ 61, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BS%d", 0));
	sprite = createSprite(1, data, "Image/Lengthen_Shorten_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	shortenBrickPrototype = new ShortenBrick(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = shortenBrickPrototype;

	//创建颠倒砖块模板
	data = new float[4]{ -122, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BR%d", 0));
	sprite = createSprite(1, data, "Image/Reversal_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	reversalBrickPrototype = new ReversalBrick(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = reversalBrickPrototype;

	//创建镜像砖块模板
	data = new float[4]{ 122.0f, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BI%d", 0));
	sprite = createSprite(1, data, "Image/Image_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	imageBrickPrototype = new ImageBrick(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = imageBrickPrototype;

	//创建加速砖块模板
	data = new float[4]{ -183.0f, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BA%d", 0));
	sprite = createSprite(1, data, "Image/Accelerate_Decelerate_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	accelerateBrickPrototype = new AccelerateBrick(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = accelerateBrickPrototype;

	//创建减速砖块模板
	data = new float[4]{ 183.0f, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BD%d", 0));
	sprite = createSprite(1, data, "Image/Accelerate_Decelerate_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	decelerateBrickPrototype = new DeaccelerateBrick(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = decelerateBrickPrototype;

	//创建穿透砖块模板
	data = new float[4]{ -244.0f, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BF%d", 0));
	sprite = createSprite(1, data, "Image/Fast_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	permeatBrickPrototype = new PermeatBrick(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = permeatBrickPrototype;

	//创建粘黏砖块模板
	data = new float[4]{ 244.0f, 230.0f - 0 * 31.0f, 30, 15 };
	ids = new std::string(StringUtils::format("BG%d", 0));
	sprite = createSprite(1, data, "Image/Sticky_Brick1.png");
	layer->addChild(sprite);
	graphicsComponent = new GraphicsComponent(sprite);
	body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	physicsComponent = new PhysicsComponent(body);
	stickyBrickPrototype = new StickyBrick(physicsComponent, graphicsComponent, ids);
	objMap[*ids] = stickyBrickPrototype;

	int index = 0;
	//批量生成被撞击消失的木块
	if (level == 1)
	{		
		for(int i = 1; i < 5; i++)
		{
			//批量生产普通转块
			objSpawner = new ObjSpawner(brickObjPrototype);
			BrickObj* brickObj = (BrickObj*)objSpawner->spawnEntity();
			brickObj->setPosition(b2Vec2(0.0f, 230.0f - i * 31.0f));
			layer->addChild(brickObj->getGraphicsComponent()->getSprite());
			ids = new std::string(StringUtils::format("BC%d", index + 1));
			brickObj->setID(ids);
			objMap[*ids] = brickObj;

			//批量生产长度转块
			objSpawner = new ObjSpawner(lengthenBrickPrototype);
			LengthenBrick* lengthenBrickObj = (LengthenBrick*)objSpawner->spawnEntity();
			lengthenBrickObj->setPosition(b2Vec2(-61, 230.0f - i * 31.0f));
			layer->addChild(lengthenBrickObj->getGraphicsComponent()->getSprite());
			ids = new std::string(StringUtils::format("BL%d", index + 1));
			lengthenBrickObj->setID(ids);
			objMap[*ids] = lengthenBrickObj;

			//批量生产缩短砖块
			objSpawner = new ObjSpawner(shortenBrickPrototype);
			ShortenBrick* shortenBrickObj = (ShortenBrick*)objSpawner->spawnEntity();
			shortenBrickObj->setPosition(b2Vec2(61, 230.0f - i * 31.0f));
			layer->addChild(shortenBrickObj->getGraphicsComponent()->getSprite());
			ids = new std::string(StringUtils::format("BS%d", index + 1));
			shortenBrickObj->setID(ids);
			objMap[*ids] = shortenBrickObj;

			//批量生产颠倒砖块模板
			objSpawner = new ObjSpawner(reversalBrickPrototype);
			ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
			reversalBrickObj->setPosition(b2Vec2(-122, 230.0f - i * 31.0f));
			layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
			ids = new std::string(StringUtils::format("BR%d", index + 1));
			reversalBrickObj->setID(ids);
			objMap[*ids] = reversalBrickObj;

			//批量生产镜像砖块模板
			objSpawner = new ObjSpawner(imageBrickPrototype);
			ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
			imageBrickObj->setPosition(b2Vec2(122.0f, 230.0f - i * 31.0f));
			layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
			ids = new std::string(StringUtils::format("BI%d", index + 1));
			imageBrickObj->setID(ids);
			objMap[*ids] = imageBrickObj;

			//批量生产加速砖块
			objSpawner = new ObjSpawner(accelerateBrickPrototype);
			AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
			accelerateBrickObj->setPosition(b2Vec2(-183.0f, 230.0f - i * 31.0f));
			layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
			ids = new std::string(StringUtils::format("BA%d", index + 1));
			accelerateBrickObj->setID(ids);
			objMap[*ids] = accelerateBrickObj;

			//批量生产减速砖块
			objSpawner = new ObjSpawner(decelerateBrickPrototype);
			DeaccelerateBrick* deaccelerateBrickObj = (DeaccelerateBrick*)objSpawner->spawnEntity();
			deaccelerateBrickObj->setPosition(b2Vec2(183.0f, 230.0f - i * 31.0f));
			layer->addChild(deaccelerateBrickObj->getGraphicsComponent()->getSprite());
			ids = new std::string(StringUtils::format("BD%d", index + 1));
			deaccelerateBrickObj->setID(ids);
			objMap[*ids] = deaccelerateBrickObj;

			//批量生产穿透砖块
			objSpawner = new ObjSpawner(permeatBrickPrototype);
			PermeatBrick* permeatBrickObj = (PermeatBrick*)objSpawner->spawnEntity();
			layer->addChild(permeatBrickObj->getGraphicsComponent()->getSprite());
			permeatBrickObj->setPosition(b2Vec2(-244.0f, 230.0f - 0 * 31.0f));
			ids = new std::string(StringUtils::format("BF%d", index + 1));
			permeatBrickObj->setID(ids);
			objMap[*ids] = permeatBrickObj;

			//批量生产粘黏砖块
			objSpawner = new ObjSpawner(stickyBrickPrototype);
			StickyBrick* stickyBrickObj = (StickyBrick*)objSpawner->spawnEntity();
			layer->addChild(stickyBrickObj->getGraphicsComponent()->getSprite());
			stickyBrickObj->setPosition(b2Vec2(-244.0f, 230.0f - i * 31.0f));
			ids = new std::string(StringUtils::format("BG%d", index + 1));
			stickyBrickObj->setID(ids);
			objMap[*ids] = stickyBrickObj;

			index++;
		}		
		brickCount = 45;
	}
	else if (level == 2)
	{
		upgradeBrickPrototype = nullptr;
		//创建传送砖块模板
		data = new float[4]{ 390.0f, 280.0f, 30, 15 };
		ids = new std::string(StringUtils::format("BT%d", ++transmitBrickIndex));
		sprite = createSprite(1, data, "Image/Transmit_Brick.png");
		layer->addChild(sprite);
		graphicsComponent = new GraphicsComponent(sprite);
		body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
		physicsComponent = new PhysicsComponent(body);
		TransmitBrick* transmitBrick = new TransmitBrick(physicsComponent, graphicsComponent, ids);
		objMap[*ids] = transmitBrick;

		//批量生产传送砖块
		objSpawner = new ObjSpawner(transmitBrick);
		transmitBrick = (TransmitBrick*)objSpawner->spawnEntity();
		transmitBrick->setPosition(b2Vec2(-390.0f, 280.0f));
		layer->addChild(transmitBrick->getGraphicsComponent()->getSprite());
		ids = new std::string(StringUtils::format("BT%d", ++transmitBrickIndex));
		transmitBrick->setID(ids);
		objMap[*ids] = transmitBrick;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5 - i; j++)
			{
				switch(j)
				{
					case 0:
					{
						//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						BrickObj* brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
					case 1:
					{
						if(upgradeBrickPrototype == nullptr)
						{
							//创建升级砖块模板
							data = new float[4]{ -320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f, 30, 15 };
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							sprite = createSprite(1, data, "Image/Upgrade_Brick2.png");
							layer->addChild(sprite);
							graphicsComponent = new GraphicsComponent(sprite);
							body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
							physicsComponent = new PhysicsComponent(body);
							upgradeBrickPrototype = new UpgradeBrick(physicsComponent, graphicsComponent, ids);
							upgradeBrickPrototype->setHP(2);
							objMap[*ids] = upgradeBrickPrototype;
						}
						else
						{
							//批量生产升级砖块
							objSpawner = new ObjSpawner(upgradeBrickPrototype);
							UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
							upgradeBrick->setPosition(b2Vec2(-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f));
							layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							upgradeBrick->setID(ids);
							objMap[*ids] = upgradeBrick;						
						}
						break;
					}
					case 2:
					{
						//批量增长砖块
						objSpawner = new ObjSpawner(lengthenBrickPrototype);
						LengthenBrick* lengthenBrickObj = (LengthenBrick*)objSpawner->spawnEntity();
						lengthenBrickObj->setPosition(b2Vec2(-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f));
						layer->addChild(lengthenBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BL%d", index + 1));
						lengthenBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Lengthen_Shorten_Brick2.png");
						lengthenBrickObj->setHP(2);
						lengthenBrickObj->setID(ids);
						objMap[*ids] = lengthenBrickObj;
						break;
					}
					case 3:
					{
						//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick1.png");
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{
						//批量生产普通砖块
						objSpawner = new ObjSpawner(brickObjPrototype);
						BrickObj* brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BC%d", index + 1));
						brickObj->setID(ids);
						objMap[*ids] = brickObj;
						break;
					}				
				}
				index++;
			}
			for (int j = 0; j < 5 - i; j++)
			{
				switch(j)
				{
					case 0:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						BrickObj* brickObj = (BrickObj*)objSpawner->spawnEntity();
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						brickObj->setPosition(b2Vec2(320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f));
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
					case 1:
					{	//批量粘黏砖块
						objSpawner = new ObjSpawner(lengthenBrickPrototype);
						StickyBrick* stickyBrickObj = (StickyBrick*)objSpawner->spawnEntity();
						layer->addChild(stickyBrickObj->getGraphicsComponent()->getSprite());
						stickyBrickObj->setPosition(b2Vec2(320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f));
						ids = new std::string(StringUtils::format("BG%d", index + 1));
						stickyBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Sticky_Brick2.png");
						stickyBrickObj->setHP(2);
						stickyBrickObj->setID(ids);
						objMap[*ids] = stickyBrickObj;
						break;
					}
					case 2:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Accelerate_Decelerate_Brick2.png");
						accelerateBrickObj->setHP(2);
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 3:
					{	//批量生产缩短砖块
						objSpawner = new ObjSpawner(shortenBrickPrototype);
						ShortenBrick* shortenBrickObj = (ShortenBrick*)objSpawner->spawnEntity();
						layer->addChild(shortenBrickObj->getGraphicsComponent()->getSprite());
						shortenBrickObj->setPosition(b2Vec2(320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f));
						ids = new std::string(StringUtils::format("BS%d", index + 1));
						shortenBrickObj->setID(ids);
						objMap[*ids] = shortenBrickObj;
						break;
					}
					case 4:
					{	//批量生产普通砖块
						objSpawner = new ObjSpawner(brickObjPrototype);
						BrickObj* brickObj = (BrickObj*)objSpawner->spawnEntity();
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						brickObj->setPosition(b2Vec2(320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f));
						ids = new std::string(StringUtils::format("BC%d", index + 1));
						brickObj->setID(ids);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
			}
		}
		brickCount = 20;
	}
	else if (level == 3)
	{
		upgradeBrickPrototype = nullptr;
		data = new float[4]{ 390.0f, 200.0f, 30, 15 };
		ids = new std::string(StringUtils::format("BT%d", ++transmitBrickIndex));
		sprite = createSprite(1, data, "Image/Transmit_Brick.png");
		layer->addChild(sprite);
		graphicsComponent = new GraphicsComponent(sprite);
		body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
		physicsComponent = new PhysicsComponent(body);
		TransmitBrick* transmitBrick = new TransmitBrick(physicsComponent, graphicsComponent, ids);
		objMap[*ids] = transmitBrick;

		objSpawner = new ObjSpawner(transmitBrick);
		transmitBrick = (TransmitBrick*)objSpawner->spawnEntity();
		layer->addChild(transmitBrick->getGraphicsComponent()->getSprite());
		transmitBrick->setPosition(b2Vec2(-390.0f, 200.0f));
		ids = new std::string(StringUtils::format("BT%d", ++transmitBrickIndex));
		transmitBrick->setID(ids);
		objMap[*ids] = transmitBrick;
		
		pos p[1005];
		int tot = 3, cnt = 1;
		p[1].x = 30.0f;
		p[1].y = 150.0f;
		p[1].cnt = 1;

		//批量生产最高的普通转块
		objSpawner = new ObjSpawner(brickObjPrototype);
		BrickObj* brickObj = (BrickObj*)objSpawner->spawnEntity();
		layer->addChild(brickObj->getGraphicsComponent()->getSprite());
		brickObj->setPosition(b2Vec2(p[1].x, p[1].y));
		ids = new std::string(StringUtils::format("BH%d", ++index));
		brickObj->setID(ids);
		brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
		brickObj->setHP(1000000007);
		objMap[*ids] = brickObj;

		p[2].x = -31.0f;
		p[2].y = 150.0f;
		p[2].cnt = 1;

		brickObj = (BrickObj*)objSpawner->spawnEntity();
		layer->addChild(brickObj->getGraphicsComponent()->getSprite());
		brickObj->setPosition(b2Vec2(p[2].x, p[2].y));
		ids = new std::string(StringUtils::format("BH%d", ++index));
		brickObj->setID(ids);
		brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
		brickObj->setHP(1000000007);
		objMap[*ids] = brickObj;

		p[3].x = 0.0f;
		p[3].y = 150.0f - 31.0f;
		p[3].cnt = 1;
		brickObj = (BrickObj*)objSpawner->spawnEntity();
		brickObj->setPosition(b2Vec2(p[3].x, p[3].y));
		layer->addChild(brickObj->getGraphicsComponent()->getSprite());
		ids = new std::string(StringUtils::format("BH%d", ++index));
		brickObj->setID(ids);
		brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
		brickObj->setHP(1000000007);
		objMap[*ids] = brickObj;

		for (int i = 1; i <= tot; i++)
		{
			if (p[i].cnt == 5)
				break;
			if (p[i].cnt == cnt)
			{
				tot++;
				p[tot].x = 30.0f + 31.0f * cnt;
				p[tot].y = 31.0f * cnt + 150.0f;
				p[tot].cnt = p[i].cnt + 1;
				switch(p[tot].cnt)
				{
					case 2:
					{	
						if (upgradeBrickPrototype == nullptr)
						{
							//创建升级砖块模板
							data = new float[4]{ p[tot].x, p[tot].y, 30, 15 };
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							sprite = createSprite(1, data, "Image/Upgrade_Brick3.png");
							layer->addChild(sprite);
							graphicsComponent = new GraphicsComponent(sprite);
							body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
							physicsComponent = new PhysicsComponent(body);
							upgradeBrickPrototype = new UpgradeBrick(physicsComponent, graphicsComponent, ids);
							upgradeBrickPrototype->setHP(3);
							objMap[*ids] = upgradeBrickPrototype;
						}
						else
						{
							//批量生产升级砖块
							objSpawner = new ObjSpawner(upgradeBrickPrototype);
							UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
							upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
							layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							upgradeBrick->setID(ids);
							objMap[*ids] = upgradeBrick;
							break;
						}					
					}
					case 3:
					{	//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
				tot++;

				p[tot].x = -30.0f - 31.0f * cnt;
				p[tot].y = 31.0f * cnt + 150.0f;
				p[tot].cnt = p[i].cnt + 1;

				switch(p[tot].cnt)
				{
					case 2:
					{	//批量生产升级砖块
						objSpawner = new ObjSpawner(upgradeBrickPrototype);
						UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
						upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BU%d", index + 1));
						upgradeBrick->setID(ids);
						objMap[*ids] = upgradeBrick;
						break;
					}
					case 3:
					{		//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
				cnt++;
			}
			if (p[i].x < 0)
			{
				tot++;
				p[tot].x = p[i].x - 61.0f;
				p[tot].y = p[i].y;
				p[tot].cnt = p[i].cnt + 1;

				switch (p[tot].cnt)
				{
					case 2:
					{	
						if (upgradeBrickPrototype == nullptr)
						{
							//创建升级砖块模板
							data = new float[4]{ p[tot].x, p[tot].y, 30, 15 };
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							sprite = createSprite(1, data, "Image/Upgrade_Brick3.png");
							layer->addChild(sprite);
							graphicsComponent = new GraphicsComponent(sprite);
							body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
							physicsComponent = new PhysicsComponent(body);
							upgradeBrickPrototype = new UpgradeBrick(physicsComponent, graphicsComponent, ids);
							upgradeBrickPrototype->setHP(3);
							objMap[*ids] = upgradeBrickPrototype;
						}
						else
						{
							//批量生产升级砖块
							objSpawner = new ObjSpawner(upgradeBrickPrototype);
							UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
							upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
							layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							upgradeBrick->setID(ids);
							objMap[*ids] = upgradeBrick;
							break;
						}
					}
					case 3:
					{	//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;				
			}
			else if (p[i].x > 0)
			{
				tot++;
				p[tot].x = p[i].x + 61.0f;
				p[tot].y = p[i].y;
				p[tot].cnt = p[i].cnt + 1;
				
				switch (p[tot].cnt)
				{
					case 2:
					{	
						if (upgradeBrickPrototype == nullptr)
						{
							//创建升级砖块模板
							data = new float[4]{ p[tot].x, p[tot].y, 30, 15 };
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							sprite = createSprite(1, data, "Image/Upgrade_Brick3.png");
							layer->addChild(sprite);
							graphicsComponent = new GraphicsComponent(sprite);
							body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
							physicsComponent = new PhysicsComponent(body);
							upgradeBrickPrototype = new UpgradeBrick(physicsComponent, graphicsComponent, ids);
							upgradeBrickPrototype->setHP(3);
							objMap[*ids] = upgradeBrickPrototype;
						}
						else
						{
							//批量生产升级砖块
							objSpawner = new ObjSpawner(upgradeBrickPrototype);
							UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
							upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
							layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							upgradeBrick->setID(ids);
							objMap[*ids] = upgradeBrick;
							break;
						}
					}
					case 3:
					{	//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
			}
			else if (p[i].x == 0)
			{
				tot++;
				p[tot].x = p[i].x + 61.0f;
				p[tot].y = p[i].y;
				p[tot].cnt = p[i].cnt + 1;
				
				switch (p[tot].cnt)
				{
					case 2:
					{	
						if (upgradeBrickPrototype == nullptr)
						{
							//创建升级砖块模板
							data = new float[4]{ p[tot].x, p[tot].y, 30, 15 };
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							sprite = createSprite(1, data, "Image/Upgrade_Brick3.png");
							layer->addChild(sprite);
							graphicsComponent = new GraphicsComponent(sprite);
							body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
							physicsComponent = new PhysicsComponent(body);
							upgradeBrickPrototype = new UpgradeBrick(physicsComponent, graphicsComponent, ids);
							upgradeBrickPrototype->setHP(3);
							objMap[*ids] = upgradeBrickPrototype;
						}
						else
						{
							//批量生产升级砖块
							objSpawner = new ObjSpawner(upgradeBrickPrototype);
							UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
							upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
							layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
							ids = new std::string(StringUtils::format("BU%d", index + 1));
							upgradeBrick->setID(ids);
							objMap[*ids] = upgradeBrick;
							break;
						}
					}
					case 3:
					{	//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
				tot++;

				p[tot].x = p[i].x - 61.0f;
				p[tot].y = p[i].y;
				p[tot].cnt = p[i].cnt + 1;

				switch (p[tot].cnt)
				{
					case 2:
					{	//批量生产升级砖块
						objSpawner = new ObjSpawner(upgradeBrickPrototype);
						UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
						upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BU%d", index + 1));
						upgradeBrick->setID(ids);
						objMap[*ids] = upgradeBrick;
						break;
					}
					case 3:
					{	//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
				tot++;

				p[tot].x = p[i].x + 30.0f;
				p[tot].y = p[i].y - 31.0f;
				p[tot].cnt = p[i].cnt + 1;
				
				switch (p[tot].cnt)
				{
					case 2:
					{	//批量生产升级砖块
						objSpawner = new ObjSpawner(upgradeBrickPrototype);
						UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
						upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BU%d", index + 1));
						upgradeBrick->setID(ids);
						objMap[*ids] = upgradeBrick;
						break;
					}
					case 3:
					{	//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
				tot++;

				p[tot].x = p[i].x - 30.0f;
				p[tot].y = p[i].y - 31.0f;
				p[tot].cnt = p[i].cnt + 1;
				
				switch (p[tot].cnt)
				{
					case 2:
					{	//批量生产升级砖块
						objSpawner = new ObjSpawner(upgradeBrickPrototype);
						UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
						upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BU%d", index + 1));
						upgradeBrick->setID(ids);
						objMap[*ids] = upgradeBrick;
						break;
					}
					case 3:
					{	//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
				tot++;

				p[tot].x = p[i].x;
				p[tot].y = p[i].y - 62.0f;
				p[tot].cnt = p[i].cnt + 1;
				switch (p[tot].cnt)
				{
					case 2:
					{	//批量生产升级砖块
						objSpawner = new ObjSpawner(upgradeBrickPrototype);
						UpgradeBrick* upgradeBrick = (UpgradeBrick*)objSpawner->spawnEntity();
						upgradeBrick->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(upgradeBrick->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BU%d", index + 1));
						upgradeBrick->setID(ids);
						objMap[*ids] = upgradeBrick;
						break;
					}
					case 3:
					{	//批量生产镜像砖块
						objSpawner = new ObjSpawner(imageBrickPrototype);
						ImageBrick* imageBrickObj = (ImageBrick*)objSpawner->spawnEntity();
						imageBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(imageBrickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BI%d", index + 1));
						imageBrickObj->setID(ids);
						imageBrickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Image_Brick2.png");
						imageBrickObj->setHP(2);
						objMap[*ids] = imageBrickObj;
						break;
					}
					case 4:
					{	//批量生产速度砖块
						objSpawner = new ObjSpawner(accelerateBrickPrototype);
						AccelerateBrick* accelerateBrickObj = (AccelerateBrick*)objSpawner->spawnEntity();
						layer->addChild(accelerateBrickObj->getGraphicsComponent()->getSprite());
						accelerateBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BA%d", index + 1));
						accelerateBrickObj->setID(ids);
						objMap[*ids] = accelerateBrickObj;
						break;
					}
					case 5:
					{	//批量生产颠倒砖块模板
						objSpawner = new ObjSpawner(reversalBrickPrototype);
						ReversalBrick* reversalBrickObj = (ReversalBrick*)objSpawner->spawnEntity();
						layer->addChild(reversalBrickObj->getGraphicsComponent()->getSprite());
						reversalBrickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						ids = new std::string(StringUtils::format("BR%d", index + 1));
						reversalBrickObj->setID(ids);
						objMap[*ids] = reversalBrickObj;
						break;
					}
					default:
					{	//批量生产最高的普通转块
						objSpawner = new ObjSpawner(brickObjPrototype);
						brickObj = (BrickObj*)objSpawner->spawnEntity();
						brickObj->setPosition(b2Vec2(p[tot].x, p[tot].y));
						layer->addChild(brickObj->getGraphicsComponent()->getSprite());
						ids = new std::string(StringUtils::format("BH%d", index + 1));
						brickObj->setID(ids);
						brickObj->getGraphicsComponent()->getSprite()->setTexture("Image/Hard_Brick.png");
						brickObj->setHP(1000000007);
						objMap[*ids] = brickObj;
						break;
					}
				}
				index++;
			}
		}
		brickCount = 72;
	}
}

void ObjManager::judgePack(char sid, std::string* ids)
{
	switch(sid)
	{
		case 'L':
		{
			resetLengthenPackList.push_back(*ids);
			schedule(schedule_selector(ObjManager::clearLengthenPackResetList), 7.0f, 0, 7.0f);
			break;
		}
		case 'S':
		{
			resetShortenPackList.push_back(*ids);
			schedule(schedule_selector(ObjManager::clearShortenPackResetList), 7.0f, 0, 7.0f);
			break;
		}
		case 'A':
		{
			resetAcceleratePackList.push_back(*ids);
			schedule(schedule_selector(ObjManager::clearAcceleratePackResetList), 7.0f, 0, 7.0f);
			break;
		}
		case 'D':
		{
			resetDeacceleratePackList.push_back(*ids);
			schedule(schedule_selector(ObjManager::clearDeacceleratePackResetList), 7.0f, 0, 7.0f);
			break;
		}
		case 'R':
		{
			resetReversalPackList.push_back(*ids);
			schedule(schedule_selector(ObjManager::clearReversalPackResetList), 7.0f, 0, 7.0f);
			break;
		}
		case 'I':
		{
			resetImagePackList.push_back(*ids);
			schedule(schedule_selector(ObjManager::clearImagePackResetList), 7.0f, 0, 7.0f);
			break;
		}
		case 'F':
		{
			resetPermeatPackList.push_back(*ids);
			schedule(schedule_selector(ObjManager::clearPermeatPackResetList), 7.0f, 0, 7.0f);
			break;
		}
		case 'U':
		{
			resetUpgradePackList.push_back(*ids);
			schedule(schedule_selector(ObjManager::clearUpgradePackResetList), 7.0f, 0, 7.0f);
			break;
		}
	}
}

void ObjManager::updateTexture(char sid, std::string* ids)
{
	BrickObj* obj = (BrickObj*)objMap[*ids];
	Texture2D* texture = CCTextureCache::sharedTextureCache()->addImage(objTexturePathMap[sid] + StringUtils::format("%d", obj->getHP()) + ".png");
	obj->setTexture(texture);
}

void ObjManager::addObj2Delete(std::string id)
{
	deleteObjList.push_back(id);
}

void ObjManager::addParticle2Delete(ParticleSystem* cps)
{
	deleteParticleList.push_back(cps);
}

void ObjManager::updateBall()
{
	if (ball->getPhysicsComponent()->getBody() == nullptr)
		return;

	Size visibleSize = Director::getInstance()->getVisibleSize();    //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();      //获取可见区域原点坐标

	b2Body* body = ball->getPhysicsComponent()->getBody();
	Sprite* dSp = ball->getGraphicsComponent()->getSprite();
	ParticleSystem* cps = ball->getGraphicsComponent()->getParticle();
	float angle = body->GetAngle();

	if (paddle->getSticky() == false)//球体不在挡板上
	{
		//设置位置
		b2Vec2 position = body->GetPosition();                           //获取物体对应刚体位置		
		dSp->setPosition(
			Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
				origin.y + visibleSize.height / 2 + position.y * pixToMeter));
		cps->setPosition(Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
			origin.y + visibleSize.height / 2 + position.y * pixToMeter));

		//设置速度
		//保证球体匀速运动
		b2Vec2 vec1 = ball->getSpeed();
		b2Vec2 vec2 = ball->getRealSpeed();
		float sSpeed = sqrt(vec1.x*vec1.x + vec1.y*vec1.y);
		float realSpeed = sqrt(vec2.x*vec2.x + vec2.y*vec2.y);
		float ratio = realSpeed / sSpeed;
		vec1.x *= ratio;
		vec1.y *= ratio;
		ball->setSpeed(vec1);
	}
	else//球体在挡板上
	{
		//设置位置
		b2Vec2 vec;
		if (paddle->getReversal() == true)
		{
			angle = imgPaddle->getPhysicsComponent()->getBody()->GetAngle();
			vec = imgPaddle->getPosition();
		}
		else
		{
			angle = paddle->getPhysicsComponent()->getBody()->GetAngle();
			vec = paddle->getPosition();
		}
		float fBallX = 0.0;										/*球与挡板的位置X偏移量*/
		float fBallY = ball->getRadius() + paddle->getHeight();	/*球与挡板的位置Y偏移量*/
		ball->setPosition(b2Vec2(vec.x * pixToMeter + fBallX, vec.y * pixToMeter + fBallY));

		//设置速度
		//保证球体静止
		ball->setSpeed(b2Vec2(0, 0));

	}//球在挡板上

	dSp->setRotation(-angle*180.0 / 3.1415926);

}

void ObjManager::updatePaddle()
{
	//挡板的速度控制由外部设置
	b2Vec2 vline = paddle->getSpeed();

	Size visibleSize = Director::getInstance()->getVisibleSize();    //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();      //获取可见区域原点坐标

	b2Body* body = paddle->getPhysicsComponent()->getBody();
	Sprite* dSp = paddle->getGraphicsComponent()->getSprite();
	b2Body* imgBody = imgPaddle->getPhysicsComponent()->getBody();
	Sprite* imgDsp = imgPaddle->getGraphicsComponent()->getSprite();

	//设置位置
	if (body != nullptr)
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
	}

	if (imgBody != nullptr)//控制副本挡板的方法
	{
		//设置位置
		b2Vec2 position = imgPaddle->getPosition();
		float angle = imgBody->GetAngle();
		if (imgDsp != NULL)
		{
			imgDsp->setPosition(
				Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
					origin.y + visibleSize.height / 2 + position.y * pixToMeter));
			imgDsp->setRotation(-angle*180.0 / 3.1415926);
		}

		//设置速度
		imgBody->ApplyForce(b2Vec2(0.0f, 3.0f*paddle->getPhysicsComponent()->getMass()), paddle->getPhysicsComponent()->getWorldCenter(), true);
		if (vline.x == -1.0f || vline.x == 1.0f)
		{
			vline.y = 0;
			if (vline.x == -1.0f)
			{
				vline.x = 55000.0f*paddle->getPhysicsComponent()->getMass();
				imgPaddle->setSpeed(vline);
			}
			else if (vline.x == 1.0f)
			{
				vline.x = -55000.0f*paddle->getPhysicsComponent()->getMass();
				imgPaddle->setSpeed(vline);
			}
		}
		if (position.x * pixToMeter > (512 - paddle->getWidth())) //移出界外
		{
			vline.y = 0;
			vline.x = -55000.0f*paddle->getPhysicsComponent()->getMass();
			imgPaddle->setSpeed(vline);
		}
		else if (position.x * pixToMeter < -(512 - paddle->getWidth())) //移出界外
		{
			vline.y = 0;
			vline.x = 55000.0f*paddle->getPhysicsComponent()->getMass();
			imgPaddle->setSpeed(vline);
		}
		else //界内
		{
			vline.y = 0;
			vline.x = -vline.x;
			imgPaddle->setSpeed(vline);
		}
	}
}

void ObjManager::updateObj()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();    //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();      //获取可见区域原点坐标

	updateBall();													 //更新球
	
	updatePaddle();													 //更新挡板

	std::map<std::string, EntityObj*>::iterator iter;				//更新其他物体
	for (iter = objMap.begin(); iter != objMap.end(); iter++)
	{
		EntityObj* po = iter->second;
		
		if (po->getID()->at(0) == 'Q' || po->getID()->at(0) == 'P') //球与挡板不在此更新
			continue;
		
		if (po == nullptr)
		{
			addObj2Delete(po->getID()->c_str());
			continue;
		}
		
		b2Body* body =po->getPhysicsComponent()->getBody();
		Sprite* dSp = po->getGraphicsComponent()->getSprite();
		
		if (body != nullptr)
		{
			b2Vec2 position = body->GetPosition();
			if (position.y * pixToMeter < -405.0 && po != ball)
			{
				addObj2Delete(po->getID()->c_str());
				continue;
			}
			float angle = body->GetAngle();
			dSp->setPosition(
				Point(origin.x + visibleSize.width / 2 + position.x * pixToMeter,
					origin.y + visibleSize.height / 2 + position.y * pixToMeter));
			dSp->setRotation(-angle*180.0 / 3.1415926);
		}		
	}
}

int ObjManager::getBrickCount() const
{
	return this->brickCount;
}

void ObjManager::deleteObj()
{
	if (deleteObjList.empty())
		return;

	Size visibleSize = Director::getInstance()->getVisibleSize();    //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin();      //获取可见区域原点坐标

	//遍历待删除物体列表
	std::vector<std::string>::iterator il;
	for (il = deleteObjList.begin(); il != deleteObjList.end(); il++)
	{
		EntityObj* po = objMap[*il];//拿到物体类对象指针	
		if (po == nullptr || po->getPhysicsComponent()->getBody() == nullptr)
		{
			objMap.erase(*il);
			continue;
		}
		//待销毁物体为砖块
		if (po->getID()->at(0) == 'B')
		{
			b2Vec2 vec = po->getPosition();
			if (po->getID()->at(1) == 'T')//传送砖块
			{
				transmitBrickWork();
				continue;
			}
			//砖块消失的粒子效果
			auto explosion = ParticleFire::create();
			explosion->setPosition(Vec2(origin.x + visibleSize.width / 2 + vec.x * pixToMeter,
					origin.y + visibleSize.height / 2 + vec.y * pixToMeter));
			explosion->retain();				
			explosion->setScale(0.8f);
			explosion->setLife(0.26f);
			layer->addChild(explosion);
			addParticle2Delete(explosion);
			//60%几率掉落包裹
			srand((unsigned)time(NULL));
			int flag = rand() % 10;
			if (flag < 6)      
			{
				std::map<char, ptr_func2>::iterator it = brickWorkFuncMap.find(po->getID()->at(1));
				if (it != brickWorkFuncMap.end())
				{
					ptr_func2 pFun = it->second;
					if (pFun)
						(this->*pFun)(vec);
				}
				continue;
			}
			if (po->getID()->at(1) != 'H')				//更新砖块总数
				brickCount--;
		}	
		else//待销毁物体为包裹
		{
			std::map<char, ptr_func1>::iterator it = packWorkFuncMap.find(po->getID()->at(1));
			if (it != packWorkFuncMap.end())
			{
				ptr_func1 pFun = it->second;
				if (pFun)
					(this->*pFun)();
			}
			if ((po->getID()->at(0) == 'A') && (po->getID()->at(1) != 'S'))	//除粘黏包裹外均放入还原倒计时
			{
				judgePack(po->getID()->at(1), new string(po->getID()->c_str()));
			}
		}	
		//销毁物体
		layer->removeChild(po->getGraphicsComponent()->getSprite(), true);	//在布景里删除物体类对象中自己的精灵	
		world->DestroyBody(po->getPhysicsComponent()->getBody());			//在物理世界里删除物体类对象中自己的刚体
		if ((po->getID()->at(0) != 'A') || (po->getID()->at(0) == 'A' && po->getID()->at(1) == 'S'))
		{
			objMap.erase(*il);												//在map里删掉非包裹类对象的指针
			delete po;
		}
		else
		{	
			po->getPhysicsComponent()->setBody(nullptr);					//包裹类对象在还原函数中删除
		}
	}
	deleteObjList.clear();

}

void ObjManager::deleteParticle()
{
	if (deleteParticleList.empty())
		return;
	std::vector<ParticleSystem*>::iterator il;
	il = deleteParticleList.begin();
	layer->removeChild(*il);
}

void ObjManager::clearImagePackResetList(float delta)
{
	if (resetImagePackList.empty())
		return;
	imgPackReset();
	std::vector<std::string>::iterator il;
	for (il = resetImagePackList.begin(); il != resetImagePackList.end(); il++)
		objMap.erase(*il);
	resetImagePackList.clear();
}

void ObjManager::clearLengthenPackResetList(float delta)
{
	if (resetLengthenPackList.empty())
		return;
	lengthenPackReset();
	std::vector<std::string>::iterator il;
	for (il = resetLengthenPackList.begin(); il != resetLengthenPackList.end(); il++)
		objMap.erase(*il);
	resetLengthenPackList.clear();
}

void ObjManager::clearShortenPackResetList(float delta)
{
	if (resetShortenPackList.empty())
		return;
	shortenPackReset();
	std::vector<std::string>::iterator il;
	for (il = resetShortenPackList.begin(); il != resetShortenPackList.end(); il++)
		objMap.erase(*il);
	resetShortenPackList.clear();
}

void ObjManager::clearPermeatPackResetList(float delta)
{
	if (resetPermeatPackList.empty())
		return;
	permeatPackReset();
	std::vector<std::string>::iterator il;
	for (il = resetPermeatPackList.begin(); il != resetPermeatPackList.end(); il++)
		objMap.erase(*il);
	resetPermeatPackList.clear();
}

void ObjManager::clearReversalPackResetList(float delta)
{
	if (resetReversalPackList.empty())
		return;
	reversalPackReset();
	std::vector<std::string>::iterator il;
	for (il = resetReversalPackList.begin(); il != resetReversalPackList.end(); il++)
		objMap.erase(*il);
	resetReversalPackList.clear();
}

void ObjManager::clearAcceleratePackResetList(float delta)
{
	if (resetDeacceleratePackList.empty())
		return;
	deacceleratePackReset();
	std::vector<std::string>::iterator il;
	for (il = resetDeacceleratePackList.begin(); il != resetDeacceleratePackList.end(); il++)
		objMap.erase(*il);
	resetDeacceleratePackList.clear();
}

void ObjManager::clearDeacceleratePackResetList(float delta)
{
	if (resetAcceleratePackList.empty())
		return;
	acceleratePackReset();
	std::vector<std::string>::iterator il;
	for (il = resetAcceleratePackList.begin(); il != resetAcceleratePackList.end(); il++)
		objMap.erase(*il);
	resetAcceleratePackList.clear();
}

void ObjManager::clearUpgradePackResetList(float delta)
{
	if (resetUpgradePackList.empty())
		return;
	upgradePackReset();
	std::vector<std::string>::iterator il;
	for (il = resetUpgradePackList.begin(); il != resetUpgradePackList.end(); il++)
		objMap.erase(*il);
	resetUpgradePackList.clear();
}

void ObjManager::imgBrickWork(b2Vec2 pos)
{
	std::string* ids = new std::string(StringUtils::format("AI%d", ++imagePackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };
	Sprite* sprite = createSprite(1,data, "Image/Image_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	ImagePack* pack = new ImagePack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;
}

void ObjManager::imgPackWork()
{
	if (paddle->getImage() == true)
		return;
	paddle->setImage(true);
	if (paddle->getReversal() == true)
	{
		Sprite* dSp = paddle->getGraphicsComponent()->getSprite();
		b2Body* body = paddle->getPhysicsComponent()->getBody();

		b2Vec2 vec1 = imgPaddle->getPosition();
		Vec2 vec2 = imgPaddle->getGraphicsComponent()->getPosition();
		
		body->SetTransform(vec1, 0);
		dSp->setPosition(vec2);
		dSp->setTexture("Image/paddle.png");
		
		b2Filter filter;
		filter.groupIndex = 1;
		filter.categoryBits = 2;
		filter.maskBits = 4;
		body->GetFixtureList()->SetFilterData(filter);
	}
	else
	{
		imgPaddle = (PaddleObj*)paddle->Clone();
		layer->addChild(imgPaddle->getGraphicsComponent()->getSprite());
	}
}

void ObjManager::imgPackReset()
{

	paddle->setImage(false);
	b2Vec2 vec = paddle->getPosition();
	if (paddle->getReversal() == true)
	{
		Sprite* dSp = paddle->getGraphicsComponent()->getSprite();
		b2Body* body = paddle->getPhysicsComponent()->getBody();
		dSp->setTexture("Image/empty.png");
		b2Filter filter;
		filter.categoryBits = 0;
		body->GetFixtureList()->SetFilterData(filter);
	}
	else
	{
		layer->removeChild(imgPaddle->getGraphicsComponent()->getSprite(),true);
		world->DestroyBody(imgPaddle->getPhysicsComponent()->getBody());
		delete imgPaddle;
		imgPaddle = nullptr;
	}
}

void ObjManager::lengthenBrickWork(b2Vec2 pos)
{
	std::string* ids = new std::string(StringUtils::format("AL%d", ++acceleratePackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };

	Sprite* sprite = createSprite(1, data, "Image / Lengthen_Shorten_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	LengthenPack* pack = new LengthenPack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;
}

void ObjManager::lengthenPackReset()
{
	paddle->setWidth(paddle->getInitialWidth());

	if (imgPaddle != nullptr)
	{
		imgPaddle->setWidth(imgPaddle->getInitialWidth());
	}
}

void ObjManager::lengthenPackWork()
{
	
	if (paddle->getWidth() * 1.2f > 1024)
		return;
	paddle->setWidth(paddle->getWidth() * 1.3f);

	if ( imgPaddle!= nullptr)
	{
		imgPaddle->setWidth(imgPaddle->getWidth() * 1.3f);
	}
}

void ObjManager::permeatBrickWork(b2Vec2 pos)
{
	std::string* ids = new std::string(StringUtils::format("AF%d", ++permeatPackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };
	Sprite* sprite = createSprite(1, data, "Image/Fast_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	PermeatPack* pack = new PermeatPack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;

}

void ObjManager::permeatPackReset()
{
	if (ball->getPermeat() == false)
		return;
	ball->setPermeat(false);
	if (paddle->getSticky() == true)
		return;

	addParticle2Delete(ball->getParticle());

	ParticleMeteor* cps = ParticleMeteor::create();
	cps->retain();
	cps->setScale(0.8);
	cps->setLife(0.06f);//每个粒子生命周期
	layer->addChild(cps);//加到精灵图
}

void ObjManager::permeatPackWork()
{
	if (ball->getPermeat() == true)
		return;
	if (paddle->getSticky()== true)
		return;

	ball->setPermeat(true);
	addParticle2Delete(ball->getParticle());
	
	ParticleSystem * particle = createParticle(1.0, 0.06f,Vec2(0,0));
	layer->addChild(particle);//加到精灵图
}

void ObjManager::reversalBrickWork(b2Vec2 pos)
{
	std::string* ids = new std::string(StringUtils::format("AR%d", ++reversalPackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };
	Sprite* sprite = createSprite(1, data, "Image/Reversal_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	
	ReversalPack* pack = new ReversalPack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;

}

void ObjManager::reversalPackReset()
{
	paddle->setReversal(false);
	b2Vec2 vec = paddle->getPosition();
	if (paddle->getImage() == true)
	{
		b2Vec2 vec1 = imgPaddle->getPosition();
		Vec2 vec2 = paddle->getGraphicsComponent()->getPosition();
		Vec2 vec3 = imgPaddle->getGraphicsComponent()->getPosition();
		
		paddle->getPhysicsComponent()->getBody()->SetTransform(vec, 0);
		paddle->getGraphicsComponent()->setPosition(vec2);
		
		imgPaddle->getPhysicsComponent()->getBody()->SetTransform(vec1, 0);
		imgPaddle->getGraphicsComponent()->setPosition(vec3);
	}
	else
	{
		b2Vec2 vec1 = imgPaddle->getPosition();
		Vec2 vec2 = imgPaddle->getGraphicsComponent()->getPosition();
		paddle->getPhysicsComponent()->getBody()->SetTransform(vec1, 0);
		paddle->getGraphicsComponent()->setPosition(vec2);
		layer->removeChild(imgPaddle->getGraphicsComponent()->getSprite(), true);//在布景里删除物体类对象中自己的精灵
		world->DestroyBody(imgPaddle->getPhysicsComponent()->getBody());//在物理世界中删除物体类对象中自己的刚体
		delete imgPaddle;
		imgPaddle = nullptr;

		Texture2D* texture = CCTextureCache::sharedTextureCache()->addImage("Image/paddle.png");
		paddle->getGraphicsComponent()->getSprite()->setTexture(texture);
		b2Filter filter;
		filter.groupIndex = 1;
		filter.categoryBits = 2;
		filter.maskBits = 4;
		paddle->getPhysicsComponent()->setFilterData(filter);		
	}
}

void ObjManager::reversalPackWork()
{
	if (paddle->getReversal() == true)
		return;
	paddle->setReversal(true);
	b2Vec2 vec = paddle->getPosition();
	if (paddle->getImage()== true)
	{
		b2Vec2 vec1 = imgPaddle->getPosition();
		Vec2 vec2 = imgPaddle->getGraphicsComponent()->getPosition();
		Vec2 vec3 = paddle->getGraphicsComponent()->getPosition();
		paddle->getPhysicsComponent()->getBody()->SetTransform(vec, 0);
		paddle->getGraphicsComponent()->setPosition(vec2);
		imgPaddle->getPhysicsComponent()->getBody()->SetTransform(vec1, 0);
		imgPaddle->getGraphicsComponent()->setPosition(vec3);
	}
	else
	{
		imgPaddle = (PaddleObj*)paddle->Clone();
		layer->addChild(imgPaddle->getGraphicsComponent()->getSprite());
		Texture2D* texture = CCTextureCache::sharedTextureCache()->addImage("Image/empty.png");
		imgPaddle->setTexture(texture);
	}
}

void ObjManager::accelerateBrickWork(b2Vec2 pos)
{
	std::string* ids = new std::string(StringUtils::format("AA%d", ++acceleratePackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };
	Sprite* sprite = createSprite(1, data, "Image/Accelerate_Decelerate_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	AcceleratePack* pack = new AcceleratePack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;
}

void ObjManager::acceleratePackReset()
{
	if(ball != nullptr)
		ball->setSpeed(ball->getInitialSpeed());
}

void ObjManager::acceleratePackWork()
{
	if (ball != nullptr)
		ball->setSpeed(b2Vec2(ball->getSpeed().x * 1.2f, ball->getSpeed().y * 1.2f));
}

void ObjManager::stickyBrickWork(b2Vec2 pos)
{
	std::string* ids = new std::string(StringUtils::format("AG%d", ++stickyPackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };
	Sprite* sprite = createSprite(1, data, "Image/Sticky_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	StickyPack* pack = new StickyPack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;
	
}

void ObjManager::stickyPackWork()
{
	float fBallX = 0.0;					/*球与挡板的位置X偏移量*/
	float fBallY = ball->getRadius() + paddle->getHeight();	/*球与挡板的位置Y偏移量*/

	if (paddle->getSticky() == true)
		return;
	paddle->setSticky(true);

	//克隆当前球体
	BallObj* newBall = (BallObj*)ball->Clone();
	layer->addChild(newBall->getGraphicsComponent()->getSprite());

	//删除原球体
	objMap.erase(*ball->getID());
	layer->removeChild(ball->getGraphicsComponent()->getSprite());
	world->DestroyBody(ball->getPhysicsComponent()->getBody());
	delete ball;
	ball = nullptr;
	
	//将当前球体加入待删除物体队列
	//addObj2Delete(ball->getID()->c_str());
	
	b2Vec2 vec;
	if (paddle->getReversal() == true)
		vec = imgPaddle->getPosition();
	else
		vec = paddle->getPosition();
	
	newBall->setPosition(b2Vec2(vec.x * pixToMeter + fBallX, vec.y * pixToMeter + fBallY));
	string* ids = new std::string(StringUtils::format("Q%d", ++ballObjIndex));
	newBall->setID(ids);
	objMap[*ids] = newBall;
	
	//将球体指针指向新球体
	ball = newBall;
}

void ObjManager::transmitBrickWork()
{
	b2Vec2 position = ball->getPosition();
	float d = 9999997.0;
	std::string ids;
	int num;
	for (int i = 1; i <= transmitBrickIndex; i++)
	{
		ids = std::string(StringUtils::format("BT%d", i));
		EntityObj* po = objMap[ids];
		b2Vec2 pos = po->getPosition();
		float d1 = sqrt((position.x - pos.x) * (position.x - pos.x) + (position.y - pos.y) * (position.y - pos.y));
		if (d1 < d)
		{
			d = d1;
			num = i;
		}
	}
	srand((unsigned)time(NULL));
	int cnt = rand() % transmitBrickIndex + 1;
	while (cnt == num)
	{
		cnt = rand() % transmitBrickIndex + 1;
	}
	ids = std::string(StringUtils::format("BT%d", cnt));
	EntityObj* po = objMap[ids];
	b2Vec2 pos = po->getPosition();
	pos.y -= ((15 + ball->getRadius()) / pixToMeter);
	ball->setSpeed(b2Vec2(0.0f, -abs(sqrt(ball->getSpeed().x * ball->getSpeed().x + ball->getSpeed().y * ball->getSpeed().y))));
	ball->setPosition(pos);
}

void ObjManager::upgradeBrickWork(b2Vec2 pos)
{	
	std::string* ids = new std::string(StringUtils::format("AU%d", ++upgradePackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };
	Sprite* sprite = createSprite(1, data, "Image/Upgrade_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	UpgradePack* pack = new UpgradePack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;

}

void ObjManager::upgradePackReset()
{
	if (paddle->getSticky() == true)
		return;
	ball->setAttack(1);
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("Image/Ball1.png");
	ball->setTexture(texture);
}

void ObjManager::upgradePackWork()
{
	if (paddle->getSticky() == true)
		return;
	CCTexture2D* texture;
	int attack = ball->getAttack();
	if (++attack <= 3)
	{
		texture = CCTextureCache::sharedTextureCache()->addImage("Image/Ball" + StringUtils::format("%d", ball->getAttack() + 1) + ".png");
		ball->setAttack(attack);
	}
	else
	{
		texture = CCTextureCache::sharedTextureCache()->addImage("Image/Ball4.png"); 
		ball->setAttack(1000000007);
	}
	ball->setTexture(texture);
}

void ObjManager::deaccelerateBrickWork(b2Vec2 pos)
{
	std::string* ids = new std::string(StringUtils::format("AD%d", ++deacceleratePackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };
	Sprite* sprite = createSprite(1, data, "Image/Accelerate_Decelerate_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	DeacceleratePack* pack = new DeacceleratePack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;
}

void ObjManager::deacceleratePackReset()
{
	if (ball != nullptr)
		ball->setSpeed(ball->getInitialSpeed());
}

void ObjManager::deacceleratePackWork()
{
	if (ball != nullptr)
		ball->setSpeed(b2Vec2(ball->getSpeed().x * 0.7f,ball->getSpeed().y * 0.7f));
}

void ObjManager::shortenBrickWork(b2Vec2 pos)
{
	std::string* ids = new std::string(StringUtils::format("AS%d", ++shortenPackIndex));
	float* data = new float[4]{ pos.x, pos.y, 12.0, 12.0 };
	Sprite* sprite = createSprite(1, data, "Image/Lengthen_Shorten_Pack.png");
	layer->addChild(sprite);
	GraphicsComponent* graphicsComponent = new GraphicsComponent(sprite);
	b2Body* body = createBody(0, 1, ids, world, data, 1, 0.0f, 1.0f, 2, 4, 2);
	PhysicsComponent* physicsComponent = new PhysicsComponent(body);
	ShortenPack* pack = new ShortenPack(physicsComponent, graphicsComponent, ids);

	b2Vec2 vec(0.0f, -8.0f);
	pack->setSpeed(vec);
	objMap[*ids] = pack;
}

void ObjManager::shortenPackReset()
{
	paddle->setWidth(paddle->getInitialWidth());
	if (imgPaddle != nullptr)
		imgPaddle->setWidth(imgPaddle->getInitialWidth());
}

void ObjManager::shortenPackWork()
{
	paddle->setWidth(paddle->getWidth() * 0.7f);
	if (imgPaddle != nullptr)
	{
		imgPaddle->setWidth(imgPaddle->getWidth() * 0.7f);
	}
}

 b2Vec2 ObjManager::getBallPos() const
{
	 return ball->getPosition();
}

 void ObjManager::applyForce2Paddle(b2Vec2 force)
 {
	 paddle->getPhysicsComponent()->getBody()->ApplyForce(b2Vec2(force.x * paddle->getPhysicsComponent()->getMass(), force.y), 
	 	paddle->getPhysicsComponent()->getBody()->GetWorldCenter(), true);
 }























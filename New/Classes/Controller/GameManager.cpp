#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

//进行物理模拟
//void ObjManager::step()
//{
//	//时间步进
//	float32 timeStep = 2.0f / 60.0f;
//	//速度迭代次数
//	int32 velocityIterations = 6;
//	//位置迭代次数
//	int32 positionIterations = 2;
//	//执行物理模拟
//	world->Step(timeStep, velocityIterations, positionIterations);
//}


void GameManager::Update(float delta)
{
	if (isPause == true)
	{
		return;
	}
	
	b2Vec2 pos = objManager->getBallPos();
	if (pos.y * pixToMeter < -405.0)//如果球掉落屏幕底部
	{
		HP--;	
		if (HP >= 0)
		{
			//this->removeChild(lifeSp);
			//lifeSp = Sprite::create("Image/HP" + StringUtils::format("%d", paddle->HP) + ".png");
			//lifeSp->setPosition(Point(origin.x + visibleSize.width - 130, origin.y + visibleSize.height - 40));
			//lifeSp->setScale(0.6f);
			////将精灵添加到布景中
			//this->addChild(lifeSp, 0);
		}
		objManager->stickyPackWork(); //等效于粘黏包裹
	}//球掉落屏幕底部
	
	if (HP < 0)//无生命值为0，游戏重新开始
	{
		//sceneManager->reStart();
	}

	//进行物理模拟
	//step();

	if (keyleft == true)//如果左键被按住
		objManager->applyForce2Paddle(b2Vec2(-500.0f, 0.0f));
	if (keyright == true)//如果右键被按住
		objManager->applyForce2Paddle(b2Vec2(500.0f, 0.0f));

	objManager->updateObj(); //更新各物体

	objManager->deleteObj(); //删除待删除物体
}

bool GameManager::myOnTouchBegan(Touch* touch, Event* event)
{
	return false;
}

void GameManager::myOnTouchCancelled(Touch* touch, Event* event)
{
	
}

void GameManager::myOnTouchEnded(Touch* touch, Event* event)
{
	
}

void GameManager::myOnTouchMoved(Touch* touch, Event* event)
{
	
}

void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	
}







#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

//��������ģ��
//void ObjManager::step()
//{
//	//ʱ�䲽��
//	float32 timeStep = 2.0f / 60.0f;
//	//�ٶȵ�������
//	int32 velocityIterations = 6;
//	//λ�õ�������
//	int32 positionIterations = 2;
//	//ִ������ģ��
//	world->Step(timeStep, velocityIterations, positionIterations);
//}


void GameManager::Update(float delta)
{
	if (isPause == true)
	{
		return;
	}
	
	b2Vec2 pos = objManager->getBallPos();
	if (pos.y * pixToMeter < -405.0)//����������Ļ�ײ�
	{
		HP--;	
		if (HP >= 0)
		{
			//this->removeChild(lifeSp);
			//lifeSp = Sprite::create("Image/HP" + StringUtils::format("%d", paddle->HP) + ".png");
			//lifeSp->setPosition(Point(origin.x + visibleSize.width - 130, origin.y + visibleSize.height - 40));
			//lifeSp->setScale(0.6f);
			////��������ӵ�������
			//this->addChild(lifeSp, 0);
		}
		objManager->stickyPackWork(); //��Ч��ճ����
	}//�������Ļ�ײ�
	
	if (HP < 0)//������ֵΪ0����Ϸ���¿�ʼ
	{
		//sceneManager->reStart();
	}

	//��������ģ��
	//step();

	if (keyleft == true)//����������ס
		objManager->applyForce2Paddle(b2Vec2(-500.0f, 0.0f));
	if (keyright == true)//����Ҽ�����ס
		objManager->applyForce2Paddle(b2Vec2(500.0f, 0.0f));

	objManager->updateObj(); //���¸�����

	objManager->deleteObj(); //ɾ����ɾ������
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







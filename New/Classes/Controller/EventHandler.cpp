#include "EventHandler.h"
#include "cocos2d.h"
#include "globalObj.h"
#include <cmath>

void BallToBrick::doStrategy()
{
	if (bodyA->GetUserData() == NULL || bodyB->GetUserData() == NULL)
		return;
	std::string* aid = (std::string*)bodyA->GetUserData();
	std::string* bid = (std::string*)bodyB->GetUserData();

	eventObj* newEvent = new eventObj(SOUND, 0, NULL, contact);
	eventQueue.push_back(newEvent);
	//thisLayer->playSound();
	
	b2WorldManifold* pos = new b2WorldManifold();
	contact->GetWorldManifold(pos);
	
	if (aid->at(0) != 'Q')
	{
		std::string* temp = aid;
		aid = bid;
		bid = temp;

		b2Body* temp1 = bodyA;
		bodyA = bodyB;
		bodyB = temp1;

	}
	
	b2Vec2 position = bodyB->GetPosition();
	b2Vec2 vec = bodyA->GetLinearVelocity();
	//Ä£ÄâÔ²½Ç¾ØÐÎÅö×²
	if (abs(position.x + 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y - 20.0f / pixToMeter - pos->points->y) <= 1)//ÓÒÏÂ½Ç
	{
		if (vec.y > 0)
		{
			vec.x *= 1.2f;
			vec.y = sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
			if (vec.x > 0)
				bodyA->SetLinearVelocity(vec);
			else if (vec.x < 0)
			{
				vec.y = -vec.y;
				bodyA->SetLinearVelocity(vec);
			}
			else
			{
				vec.x = vec.y * 0.268f;
				vec.y = sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
		}
		else if (vec.y <= 0)
		{
			if (vec.x < 0)
			{
				vec.y *= 1.2f;
				vec.x = -sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);
				bodyA->SetLinearVelocity(vec);
			}
			else if (vec.x == 0)
				bodyA->SetLinearVelocity(vec);
		}
		return;
	}

	if (abs(position.x + 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y + 20.0f / pixToMeter - pos->points->y) <= 1)//ÓÒÉÏ½Ç
	{
		if (vec.y < 0)
		{
			vec.x *= 1.2f;
			vec.y = -sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
			if (vec.x > 0)
				bodyA->SetLinearVelocity(vec);
			else if (vec.x < 0)
			{
				vec.y = -vec.y;
				bodyA->SetLinearVelocity(vec);
			}
			else
			{
				vec.x = -vec.y * 0.268f;
				vec.y = -sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
		}
		else if (vec.y >= 0)
		{
			if (vec.x < 0)
			{
				vec.y *= 1.2f;
				vec.x = -sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
			else if (vec.x == 0)
				bodyA->SetLinearVelocity(vec);
		}
		return;
	}
	if (abs(position.x - 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y - 20.0f / pixToMeter - pos->points->y) <= 1)//×óÏÂ½Ç
	{
		if (vec.y > 0)
		{
			vec.x *= 1.2f;
			vec.y = sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
			if (vec.x < 0)
				bodyA->SetLinearVelocity(vec);
			else if (vec.x > 0)
			{
				vec.y = -vec.y;
				bodyA->SetLinearVelocity(vec);
			}
			else
			{
				vec.x = -vec.y * 0.268f;
				vec.y = sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
		}
		if (vec.y <= 0)
		{
			if (vec.x > 0)
			{
				vec.y *= 1.2f;
				vec.x = sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
			else if (vec.x == 0)
				bodyA->SetLinearVelocity(vec);
		}
		return;
	}
	if (abs(position.x - 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y + 20.0f / pixToMeter - pos->points->y) <= 1)//×óÉÏ½Ç
	{
		if (vec.y < 0)
		{
			vec.x *= 1.2f;
			vec.y = sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
			if (vec.x < 0)
				bodyA->SetLinearVelocity(vec);
			else if (vec.x > 0)
			{
				vec.y = -vec.y;
				bodyA->SetLinearVelocity(vec);
			}
			else
			{
				vec.x = vec.y * 0.268f;
				vec.y = sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
		}
		if (vec.y >= 0)
		{
			if (vec.x > 0)
			{
				vec.y *= 1.2f;
				vec.x = sqrt(objManager->getBallSpeed().x * objManager->getBallSpeed().y - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
			else if (vec.x == 0)
				bodyA->SetLinearVelocity(vec);
		}
		return;
	}
	
	newEvent = new eventObj(BRICK, objManager->getBallAttack(), bid, contact);
	eventQueue.push_back(newEvent);
	
	//¸üÐÂÄ¾¿é
	//objManager->updateBrickObj(bid, contact);
	
}

void BallToWall::doStrategy()
{
	eventObj* newEvent = new eventObj(SOUND, 0, NULL, contact);
	eventQueue.push_back(newEvent);
	thisLayer->playSound();
}

void PaddleToPack::doStrategy()
{
	if (bodyA->GetUserData() == NULL || bodyB->GetUserData() == NULL)
		return;
	std::string* aid = (std::string*)bodyA->GetUserData();
	std::string* bid = (std::string*)bodyB->GetUserData();

	char preFixA = aid->at(0);
	char preFixB = bid->at(0);

	eventObj* newEvent = new eventObj(SOUND, 0, NULL, contact);
	eventQueue.push_back(newEvent);
	//thisLayer->playSound();

	if (preFixA == 'A')
	{
		eventObj* newEvent = new eventObj(PACK, 0, aid, contact);
		eventQueue.push_back(newEvent);
		objManager->addObj2Delete(*aid);
		//thisLayer->listForDel.push_back(*aid);
	}
	else if (preFixB == 'A')
	{
		eventObj* newEvent = new eventObj(PACK, 0, bid, contact);
		eventQueue.push_back(newEvent);
		objManager->addObj2Delete(*bid);
		//thisLayer->listForDel.push_back(*bid);
	}
}

void PaddleToWall::doStrategy()
{
	if (bodyA->GetUserData() == NULL || bodyB->GetUserData() == NULL)
		return;
	std::string* aid = (std::string*)bodyA->GetUserData();
	std::string* bid = (std::string*)bodyB->GetUserData();

	char preFixA = aid->at(0);
	char preFixB = bid->at(0);

	if (preFixA == 'P')
	{
		b2Vec2 position = bodyA->GetPosition();
		if (position.x > 0)
		{
			b2Vec2 vec(-1.0f, 0.0f);
			bodyA->SetLinearVelocity(vec);
		}
		else
		{
			b2Vec2 vec(1.0f, 0.0f);
			bodyA->SetLinearVelocity(vec);
		}
	}
	else if (preFixB == 'P')
	{
		b2Vec2 position = bodyB->GetPosition();
		if (position.x > 0)
		{
			b2Vec2 vec(-1.0f, 0.0f);
			bodyB->SetLinearVelocity(vec);
		}
		else
		{
			b2Vec2 vec(1.0f, 0.0f);
			bodyB->SetLinearVelocity(vec);
		}
	}
}

void PaddleToBall::doStrategy()
{
	b2Vec2 ball_vec;
	if (bodyA->GetUserData() == NULL || bodyB->GetUserData() == NULL)
		return;
	std::string* aid = (std::string*)bodyA->GetUserData();

	eventObj* newEvent = new eventObj(SOUND, 0, NULL, contact);
	eventQueue.push_back(newEvent);
	//thisLayer->playSound();
	b2WorldManifold* pos = new b2WorldManifold();
	contact->GetWorldManifold(pos);
	//thisLayer->playSound();
	if (aid->at(0) != 'P')
	{

		b2Body* temp1 = bodyA;
		bodyA = bodyB;
		bodyB = temp1;

	}
	float x = bodyA->GetPosition().x, y = bodyA->GetPosition().y, d;
	if (pos->points->y < y + objManager->getPaddleInitialHeight() / pixToMeter - 3.0f)
	{
		bodyB->SetLinearVelocity(b2Vec2(0, -20.0f));
		return;
	}
	ball_vec = bodyB->GetLinearVelocity();
	d = objManager->getPaddleInitialHeight() * 2;
	x = abs(pos->points->x - x);
	int flag = 1;
	if (ball_vec.y > 0)
		flag = -1;
	if (pos->points->x > bodyA->GetPosition().x)
	{
		ball_vec.x = x / d * (-ball_vec.y) * 1.8f;
		ball_vec.y = sqrt(objManager->getBallSpeed().y * objManager->getBallSpeed().y - ball_vec.x * ball_vec.x) * flag;

		
	}
	else
	{
		ball_vec.x = -x / d * (-ball_vec.y) * 1.8f;
		ball_vec.y = sqrt(objManager->getBallSpeed().y * objManager->getBallSpeed().y - ball_vec.x * ball_vec.x) * flag;
	}
	bodyB->SetLinearVelocity(ball_vec);
}
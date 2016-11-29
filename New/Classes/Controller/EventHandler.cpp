#include "EventHandler.h"
#include "cocos2d.h"

void BallToBrick::doStrategy()
{
	//b2Body* bodyA = contact->GetFixtureA()->GetBody();
	//b2Body* bodyB = contact->GetFixtureB()->GetBody();
	b2Body* ball_body;
	b2Vec2 ball_vec;
	if (bodyA->GetUserData() == NULL || bodyB->GetUserData() == NULL)
		return;
	std::string* aid = (std::string*)bodyA->GetUserData();
	std::string* bid = (std::string*)bodyB->GetUserData();

	char preFixA = aid->at(0);
	char preFixB = bid->at(0);

	eventObj* newEvent = new eventObj(SOUND, 0, NULL);
	eventQueue.push_back(newEvent);
	thisLayer->playYX();
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
	if (bid->at(1) == 'T')//�����ײ���Ǵ���ש��
	{
		thisLayer->listForDel.push_back(*aid);
		return;
	}
	if (Ball::isFast == true)//
	{
		ball_vec = bodyA->GetLinearVelocity();
		ball_body = bodyA;
	}
	b2Vec2 position = bodyB->GetPosition();
	b2Vec2 vec = bodyA->GetLinearVelocity();
	//ģ��Բ�Ǿ�����ײ
	if (abs(position.x + 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y - 20.0f / pixToMeter - pos->points->y) <= 1)//���½�
	{
		if (vec.y > 0)
		{
			vec.x *= 1.2f;
			vec.y = sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
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
				vec.y = sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
		}
		else if (vec.y <= 0)
		{
			if (vec.x < 0)
			{
				vec.y *= 1.2f;
				vec.x = -sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);
				bodyA->SetLinearVelocity(vec);
			}
			else if (vec.x == 0)
				bodyA->SetLinearVelocity(vec);
		}
		return;
	}

	else if (abs(position.x + 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y + 20.0f / pixToMeter - pos->points->y) <= 1)//���Ͻ�
	{
		if (vec.y < 0)
		{
			vec.x *= 1.2f;
			vec.y = -sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
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
				vec.y = -sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
		}
		else if (vec.y >= 0)
		{
			if (vec.x < 0)
			{
				vec.y *= 1.2f;
				vec.x = -sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
			else if (vec.x == 0)
				bodyA->SetLinearVelocity(vec);
		}
		return;
	}
	else if (abs(position.x - 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y - 20.0f / pixToMeter - pos->points->y) <= 1)//���½�
	{
		if (vec.y > 0)
		{
			vec.x *= 1.2f;
			vec.y = sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
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
				vec.y = sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
		}
		if (vec.y <= 0)
		{
			if (vec.x > 0)
			{
				vec.y *= 1.2f;
				vec.x = sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
			else if (vec.x == 0)
				bodyA->SetLinearVelocity(vec);
		}
		return;
	}
	else if (abs(position.x - 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y + 20.0f / pixToMeter - pos->points->y) <= 1)//���Ͻ�
	{
		if (vec.y < 0)
		{
			vec.x *= 1.2f;
			vec.y = sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
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
				vec.y = sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
		}
		if (vec.y >= 0)
		{
			if (vec.x > 0)
			{
				vec.y *= 1.2f;
				vec.x = sqrt(ball->getSpeed() * ball->getSpeed() - vec.x * vec.x);//
				bodyA->SetLinearVelocity(vec);
			}
			else if (vec.x == 0)
				bodyA->SetLinearVelocity(vec);
		}
		return;
	}
	eventObj* newEvent = new eventObj(BRICK, ball->getAttack(), bid);
	eventQueue.push_back(newEvent);
	//ɾ��ľ��
	thisLayer->pom[*bid]->HP -= thisLayer->pom[*aid]->attack;//��ש�������ֵ��ȥ��Ĺ�����
	if (thisLayer->pom[*bid]->HP <= 0)
	{
		thisLayer->listForDel.push_back(*bid);
		b2Filter filter;
		filter.categoryBits = 0;
		contact->GetFixtureB()->SetFilterData(filter);
	}
	else
	{
		PhyObject* po = thisLayer->pom[*bid];
		po->HPchange(po);
	}
}

void BallToWall::doStrategy()
{
	eventObj* newEvent = new eventObj(SOUND, 0, NULL);
	eventQueue.push_back(newEvent);
	thisLayer->playYX();
}

void PaddleToPack::doStrategy()
{
	if (bodyA->GetUserData() == NULL || bodyB->GetUserData() == NULL)
		return;
	std::string* aid = (std::string*)bodyA->GetUserData();
	std::string* bid = (std::string*)bodyB->GetUserData();

	char preFixA = aid->at(0);
	char preFixB = bid->at(0);

	eventObj* newEvent = new eventObj(SOUND, 0, NULL);
	eventQueue.push_back(newEvent);
	thisLayer->playYX();

	if (preFixA == 'A')
	{
		eventObj* newEvent = new eventObj(PACK, 0, aid);
		eventQueue.push_back(newEvent);
		thisLayer->listForDel.push_back(*aid);
	}
	else if (preFixB == 'A')
	{
		eventObj* newEvent = new eventObj(PACK, 0, bid);
		eventQueue.push_back(newEvent);
		thisLayer->listForDel.push_back(*bid);
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
	b2Body* ball_body;
	b2Vec2 ball_vec;
	if (bodyA->GetUserData() == NULL || bodyB->GetUserData() == NULL)
		return;
	std::string* aid = (std::string*)bodyA->GetUserData();
	std::string* bid = (std::string*)bodyB->GetUserData();

	char preFixA = aid->at(0);
	char preFixB = bid->at(0);

	eventObj* newEvent = new eventObj(SOUND, 0, NULL);
	eventQueue.push_back(newEvent);
	thisLayer->playYX();
	b2WorldManifold* pos = new b2WorldManifold();
	contact->GetWorldManifold(pos);
	thisLayer->playYX();
	if (aid->at(0) != 'P')
	{
		std::string* temp = aid;
		aid = bid;
		bid = temp;

		b2Body* temp1 = bodyA;
		bodyA = bodyB;
		bodyB = temp1;

	}
	float x = bodyA->GetPosition().x, y = bodyA->GetPosition().y, d;
	if (pos->points->y < y + paddle->getInitialWidth() / 2 / pixToMeter - 3.0f)
	{
		bodyB->SetLinearVelocity(b2Vec2(0, -20.0f));
		return;
	}

	b2Vec2 position = bodyA->GetPosition();
	b2Vec2 vec = bodyB->GetLinearVelocity();
	ball_body = bodyB;
	ball_vec = bodyB->GetLinearVelocity();
	d = paddle->getInitialWidth();
	x = abs(pos->points->x - x);
	int flag = 1;
	if (ball_vec.y > 0)
		flag = -1;
	if (pos->points->x > bodyA->GetPosition().x)
	{
		ball_vec.x = x / d * (-ball_vec.y) * 1.8f;
		ball_vec.y = sqrt(ball->getSpeed() * ball->getSpeed() - ball_vec.x * ball_vec.x) * flag;
	}
	else
	{
		ball_vec.x = -x / d * (-ball_vec.y) * 1.8f;
		ball_vec.y = sqrt(ball->getSpeed() * ball->getSpeed() - ball_vec.x * ball_vec.x) * flag;
	}
	bodyB->SetLinearVelocity(ball_vec);
}
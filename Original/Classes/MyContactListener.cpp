#include "MyContactListener.h"
#include "cocos2d.h"

b2Body* MyContactListener::body = NULL;
b2Vec2 MyContactListener::body_vec;

b2Body* MyContactListener::ball_body = NULL;
b2Vec2 MyContactListener::ball_vec;

bool MyContactListener::isChange = false;
bool MyContactListener::isFast = false;

void MyContactListener::BeginContact(b2Contact* contact)
{	
	//碰撞开始时的回调方法
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL)
	{
		std::string* aid = (std::string*)bodyA->GetUserData();
		std::string* bid = (std::string*)bodyB->GetUserData();

		char preFixA = aid->at(0);
		char preFixB = bid->at(0);
		if ((preFixA == 'Q' || preFixB == 'Q') && (preFixA == 'W' || preFixB == 'W'))//球碰撞墙时播放音效
			hl->playYX();
		//如果一个参与碰撞的是球,另一个参与碰撞的是砖块
		if ((preFixA == 'Q' || preFixB == 'Q') && (preFixA == 'B' || preFixB == 'B'))
		{
			hl->playYX();
			pos = new b2WorldManifold();
			contact->GetWorldManifold(pos);
			if (preFixA == 'Q')
			{
				if (bid->at(1) == 'T')//如果相撞的是传送砖块
				{
					hl->listForDel.push_back(*bid);
					return;
				}
				if (Ball::isFast == true)
				{
					isFast = true;
					ball_vec = bodyA->GetLinearVelocity();
					ball_body = bodyA;
				}
				b2Vec2 position = bodyB->GetPosition();
				b2Vec2 vec = bodyA->GetLinearVelocity();
				//模拟圆角矩形碰撞
				if (abs(position.x + 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y - 20.0f / pixToMeter - pos->points->y) <= 1)//右下角
				{
					if (vec.y > 0)
					{
						vec.x *= 1.2f;
						vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
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
							vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyA->SetLinearVelocity(vec);
						}
					}
					else if (vec.y <= 0)
					{
						if (vec.x < 0)
						{
							vec.y *= 1.2f;
							vec.x = -sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyA->SetLinearVelocity(vec);
						}
						else if (vec.x == 0)
							bodyA->SetLinearVelocity(vec);
					}
					return;
				}
				else if (abs(position.x + 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y + 20.0f / pixToMeter - pos->points->y) <= 1)//右上角
				{
					if (vec.y < 0)
					{
						vec.x *= 1.2f;
						vec.y = -sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
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
							vec.y = -sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyA->SetLinearVelocity(vec);
						}
					}
					else if (vec.y >= 0)
					{
						if (vec.x < 0)
						{
							vec.y *= 1.2f;
							vec.x = -sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyA->SetLinearVelocity(vec);
						}
						else if (vec.x == 0)
							bodyA->SetLinearVelocity(vec);
					}
					return;
				}
				else if (abs(position.x - 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y - 20.0f / pixToMeter - pos->points->y) <= 1)//左下角
				{
					if (vec.y > 0)
					{
						vec.x *= 1.2f;
						vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
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
							vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyA->SetLinearVelocity(vec);
						}
					}
					if (vec.y <= 0)
					{
						if (vec.x > 0)
						{
							vec.y *= 1.2f;
							vec.x = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyA->SetLinearVelocity(vec);
						}
						else if (vec.x == 0)
							bodyA->SetLinearVelocity(vec);
					}
					return;
				}
				else if (abs(position.x - 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y + 20.0f / pixToMeter - pos->points->y) <= 1)//左上角
				{
					if (vec.y < 0)
					{
						vec.x *= 1.2f;
						vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
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
							vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyA->SetLinearVelocity(vec);
						}
					}
					if (vec.y >= 0)
					{
						if (vec.x > 0)
						{
							vec.y *= 1.2f;
							vec.x = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyA->SetLinearVelocity(vec);
						}
						else if (vec.x == 0)
							bodyA->SetLinearVelocity(vec);
					}
					return;
				}
				//删除木块
				hl->pom[*bid]->HP -= hl->pom[*aid]->attack;//让砖块的生命值减去球的攻击力
				if (hl->pom[*bid]->HP <= 0)
				{
					hl->listForDel.push_back(*bid);
					b2Filter filter;
					filter.categoryBits = 0;
					contact->GetFixtureB()->SetFilterData(filter);
				}
				else
				{
					PhyObject* po = hl->pom[*bid];
					po->HPchange(po);
				}
			}
			else if (preFixB == 'Q')
			{
				if (aid->at(1) == 'T')//如果相撞的是传送砖块
				{
					hl->listForDel.push_back(*aid);
					return;
				}
				if (Ball::isFast == true)
				{
					isFast = true;
					ball_vec = bodyB->GetLinearVelocity();
					ball_body = bodyB;
				}
				b2Vec2 position = bodyA->GetPosition();
				b2Vec2 vec = bodyB->GetLinearVelocity();
				//模拟圆角矩形碰撞
				if (abs(position.x + 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y - 20.0f / pixToMeter - pos->points->y) <= 1)//右下角
				{
					if (vec.y > 0)
					{
						vec.x *= 1.2f;
						vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
						if (vec.x > 0)
							bodyB->SetLinearVelocity(vec);
						else if (vec.x < 0)
						{
							vec.y = -vec.y;
							bodyB->SetLinearVelocity(vec);
						}
						else
						{
							vec.x = vec.y * 0.268f;
							vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyB->SetLinearVelocity(vec);
						}
					}
					else if (vec.y <= 0)
					{
						if (vec.x < 0)
						{
							vec.y *= 1.2f;
							vec.x = -sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyB->SetLinearVelocity(vec);
						}
						else if (vec.x == 0)
							bodyB->SetLinearVelocity(vec);
					}
					return;
				}
				else if (abs(position.x + 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y + 20.0f / pixToMeter - pos->points->y) <= 1)//右上角
				{
					if (vec.y < 0)
					{
						vec.x *= 1.2f;
						vec.y = -sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
						if (vec.x > 0)
							bodyB->SetLinearVelocity(vec);
						else if (vec.x < 0)
						{
							vec.y = -vec.y;
							bodyB->SetLinearVelocity(vec);
						}
						else
						{
							vec.x = -vec.y * 0.268f;
							vec.y = -sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyB->SetLinearVelocity(vec);
						}
					}
					else if (vec.y >= 0)
					{
						if (vec.x < 0)
						{
							vec.y *= 1.2f;
							vec.x = -sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyB->SetLinearVelocity(vec);
						}
						else if (vec.x == 0)
							bodyB->SetLinearVelocity(vec);
					}
					return;
				}
				else if (abs(position.x - 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y - 20.0f / pixToMeter - pos->points->y) <= 1)//左下角
				{
					if (vec.y > 0)
					{
						vec.x *= 1.2f;
						vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
						if (vec.x < 0)
							bodyB->SetLinearVelocity(vec);
						else if (vec.x > 0)
						{
							vec.y = -vec.y;
							bodyB->SetLinearVelocity(vec);
						}
						else
						{
							vec.x = -vec.y * 0.268f;
							vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyB->SetLinearVelocity(vec);
						}
					}
					if (vec.y <= 0)
					{
						if (vec.x > 0)
						{
							vec.y *= 1.2f;
							vec.x = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyB->SetLinearVelocity(vec);
						}
						else if (vec.x == 0)
							bodyB->SetLinearVelocity(vec);
					}
					return;
				}
				else if (abs(position.x - 50.0f / pixToMeter - pos->points->x) <= 1 && abs(position.y + 20.0f / pixToMeter - pos->points->y) <= 1)//左上角
				{
					if (vec.y < 0)
					{
						vec.x *= 1.2f;
						vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
						if (vec.x < 0)
							bodyB->SetLinearVelocity(vec);
						else if (vec.x > 0)
						{
							vec.y = -vec.y;
							bodyB->SetLinearVelocity(vec);
						}
						else
						{
							vec.x = vec.y * 0.268f;
							vec.y = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyB->SetLinearVelocity(vec);
						}
					}
					if (vec.y >= 0)
					{
						if (vec.x > 0)
						{
							vec.y *= 1.2f;
							vec.x = sqrt(Ball::speed * Ball::speed - vec.x * vec.x);
							bodyB->SetLinearVelocity(vec);
						}
						else if (vec.x == 0)
							bodyB->SetLinearVelocity(vec);
					}
					return;
				}
				//删除木块
				hl->pom[*aid]->HP -= hl->pom[*bid]->attack;//让砖块的生命值减去球的攻击力
				if (hl->pom[*aid]->HP <= 0)
				{
					hl->listForDel.push_back(*aid);
					b2Filter filter;
					filter.categoryBits = 0;
					contact->GetFixtureA()->SetFilterData(filter);
				}
				else
				{
					PhyObject* po = hl->pom[*aid];
					po->HPchange(po);
				}
			}
		}
		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'A' || preFixB == 'A'))
		{
			if (preFixA == 'A')
			{
				hl->listForDel.push_back(*aid);
			}
			else if (preFixB == 'A')
			{
				hl->listForDel.push_back(*bid);
			}
		}
		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'W' || preFixB == 'W'))
		{
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
		if ((preFixA == 'P' || preFixB == 'P') && (preFixA == 'Q' || preFixB == 'Q'))
		{
			hl->playYX();
			pos = new b2WorldManifold();
			contact->GetWorldManifold(pos);
			if (preFixA == 'P')
			{
				float x = bodyA->GetPosition().x, y = bodyA->GetPosition().y, d;
				if (pos->points->y < y + Paddle::s_width / pixToMeter - 3.0f)
				{
					bodyB->SetLinearVelocity(b2Vec2(0, -20.0f));
					return;
				}

				b2Vec2 position = bodyA->GetPosition();
				b2Vec2 vec = bodyB->GetLinearVelocity();
				ball_body = bodyB;
				ball_vec = bodyB->GetLinearVelocity();
				d = Paddle::length;
				x =abs(pos->points->x - x);
				int flag = 1;
				if (ball_vec.y > 0)
					flag = -1;
				if (pos->points->x > bodyA->GetPosition().x)
				{
					ball_vec.x = x / d * (-ball_vec.y) * 1.8f;
					ball_vec.y = sqrt(Ball::speed * Ball::speed - ball_vec.x * ball_vec.x) * flag;
				}
				else
				{
					ball_vec.x = -x / d * (-ball_vec.y) * 1.8f;
					ball_vec.y = sqrt(Ball::speed * Ball::speed - ball_vec.x * ball_vec.x) * flag;
				}
				bodyB->SetLinearVelocity(ball_vec);

			}
			if (preFixB == 'P')
			{
				float x = bodyB->GetPosition().x, y = bodyB->GetPosition().y, d;
				if (pos->points->y < y + Paddle::s_width / pixToMeter - 3.0f)
				{
					bodyA->SetLinearVelocity(b2Vec2(0, -20.0f));
					return;
				}
				b2Vec2 position = bodyB->GetPosition();
				b2Vec2 vec = bodyA->GetLinearVelocity();
				ball_body = bodyA;
				ball_vec = bodyA->GetLinearVelocity();
				d = Paddle::length;
				x = abs(pos->points->x - x);
				int flag = 1;
				if (ball_vec.y > 0)
					flag = -1;
				if (pos->points->x > bodyB->GetPosition().x)
				{
					ball_vec.x = x / d * (-ball_vec.y) * 1.8;
					ball_vec.y = sqrt(Ball::speed * Ball::speed - ball_vec.x * ball_vec.x) * flag;
				}
				else
				{
					ball_vec.x = -x / d * (-ball_vec.y) * 1.8;
					ball_vec.y = sqrt(Ball::speed * Ball::speed - ball_vec.x * ball_vec.x) * flag;
				}
				bodyA->SetLinearVelocity(ball_vec);
			}
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{
	if (isFast == true)
	{
		isFast = false;
		ball_body->SetLinearVelocity(ball_vec);
	}
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}


#include "LevelData.h"
#include <vector>

int LevelData::brickcount = 0;
float LevelData::speed = 0;
struct pos
{
	float x;
	float y;
	int cnt;
};

LevelData::LevelData(int level, b2World* world, Layer* layer, std::map<std::string, PhyObject*> &pom)
{
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();
	Common_Brick::index = 0;
	Hard_Brick::index = 0;
	Sticky_Brick::index = 0;
	Lengthen_Brick::index = 0;
	Shorten_Brick::index = 0;
	Accelerate_Brick::index = 0;
	Decelerate_Brick::index = 0;
	Upgrade_Brick::index = 0;
	Transmit_Brick::index = 0;
	Reversal_Brick::index = 0;
	Image_Brick::index = 0;

	Lengthen_Pack::index = 0;
	Shorten_Pack::index = 0;
	Accelerate_Pack::index = 0;
	Decelerate_Pack::index = 0;
	Upgrade_Pack::index = 0;
	Sticky_Pack::index = 0;
	Reversal_Pack::index = 0;
	Image_Pack::index = 0;

	Wall::index = 0;
	Ball::index = 0;
	Ball::radius = 15.0;
	Ball::isFast = false;
	Ball::speed = 25 + (level - 1) * 4.0f;
	Ball::s_speed = 25 + (level - 1) * 4.0f;
	Paddle::ball_x = 0.0;
	Paddle::length = 75.0;
	Paddle::width = 20.0;
	Paddle::s_length = 75.0;
	Paddle::s_width = 20.0;
	Paddle::ball_y = Ball::radius + Paddle::s_width;
	Paddle::index = 0;

	LevelData::brickcount = 0;
	LevelData::speed = 25 + (level - 1) * 4.0f;
	PhyObject* po;
	float* data;
	std::string* ids;

	auto bgSprite = Sprite::create("Image/guanka" + StringUtils::format("%d", level) + ".png");
	//设置精灵对象的位置
	bgSprite->setPosition(Point(100.0 + origin.x, visibleSize.height + origin.y - 40.0));
	bgSprite->setScale(0.6f);
	layer->addChild(bgSprite, 0);

	//批量生成被撞击消失的木块
	if (level == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			data = new float[4]{0.0f, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BC%d", ++Common_Brick::index));                  
			po = new Common_Brick(ids, layer, world, "Image/Common_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;

			data = new float[4]{-61, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BL%d", ++Lengthen_Brick::index));                  
			po = new Lengthen_Brick(ids, layer, world, "Image/Lengthen_Shorten_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;

			data = new float[4]{61, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BB%d", ++Shorten_Brick::index));                  
			po = new Shorten_Brick(ids, layer, world, "Image/Lengthen_Shorten_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;

			data = new float[4]{-122, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));                  
			po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;

			data = new float[4]{122.0f, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));                  
			po = new Image_Brick(ids, layer, world, "Image/Image_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;

			data = new float[4]{-183.0f, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));                  
			po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;

			data = new float[4]{183.0f, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BD%d", ++Decelerate_Brick::index));                  
			po = new Decelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;

			data = new float[4]{-244.0f, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BF%d", ++Fast_Brick::index));                  
			po = new Fast_Brick(ids, layer, world, "Image/Fast_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;

			data = new float[4]{244.0f, 230.0f - i * 31.0f, 30, 15};
			ids = new std::string(StringUtils::format("BS%d", ++Sticky_Brick::index));                  
			po = new Sticky_Brick(ids, layer, world, "Image/Sticky_Brick1.png", data, 1, 0.0f, 1.0f, 1);
			pom[*ids] = po;
		}
		LevelData::brickcount = 45;
	}
	else if (level == 2)
	{
		data = new float[4]{390.0f, 280.0f, 30, 15};
		ids = new std::string(StringUtils::format("BT%d", ++Transmit_Brick::index));                  
		po = new Transmit_Brick(ids, layer, world, "Image/Transmit_Brick.png", data, 1, 0.0f, 1.0f, 1);
		pom[*ids] = po;

		data = new float[4]{-390.0f, 280.0f, 30, 15};
		ids = new std::string(StringUtils::format("BT%d", ++Transmit_Brick::index));                  
		po = new Transmit_Brick(ids, layer, world, "Image/Transmit_Brick.png", data, 1, 0.0f, 1.0f, 1);
		pom[*ids] = po;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5 - i; j++)
			{
				if (j == 0)
				{
					data = new float[4]{-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));                  
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
					pom[*ids] = po;
				}
				if (j == 1)
				{
					data = new float[4]{-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));                  
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick2.png", data, 1, 0.0f, 1.0f, 2);
					pom[*ids] = po;
				}
				if (j == 2)
				{
					data = new float[4]{-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BL%d", ++Lengthen_Brick::index));                  
					po = new Lengthen_Brick(ids, layer, world, "Image/Lengthen_Shorten_Brick2.png", data, 1, 0.0f, 1.0f, 2);
					pom[*ids] = po;
				}
				if (j == 3)
				{
					data = new float[4]{-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));                  
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick1.png", data, 1, 0.0f, 1.0f, 1);
					pom[*ids] = po;
				}
				if (j == 4)
				{
					data = new float[4]{-320.0f + (i * 40.0f) + j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BC%d", ++Common_Brick::index));                  
					po = new Common_Brick(ids, layer, world, "Image/Common_Brick1.png", data, 1, 0.0f, 1.0f, 1);
					pom[*ids] = po;
				}
			}
			for (int j = 0; j < 5 - i; j++)
			{
				if (j == 0)
				{
					data = new float[4]{320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));                 
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
					pom[*ids] = po;
				}
				if (j == 1)
				{
					data = new float[4]{320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BA%d", ++Sticky_Brick::index));
					po = new Sticky_Brick(ids, layer, world, "Image/Sticky_Brick2.png", data, 1, 0.0f, 1.0f, 2);
					pom[*ids] = po;
				}
				if (j == 2)
				{
					data = new float[4]{320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BS%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick2.png", data, 1, 0.0f, 1.0f, 2);
					pom[*ids] = po;
				}
				if (j == 3)
				{
					data = new float[4]{320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BB%d", ++Shorten_Brick::index));                  
					po = new Shorten_Brick(ids, layer, world, "Image/Lengthen_Shorten_Brick1.png", data, 1, 0.0f, 1.0f, 1);
					pom[*ids] = po;
				}
				if (j == 4)
				{
					data = new float[4]{320.0f - (i * 40.0f) - j * 61.0f, 200.0f - i * 31.0f, 30, 15};
					ids = new std::string(StringUtils::format("BC%d", ++Common_Brick::index));                  
					po = new Common_Brick(ids, layer, world, "Image/Common_Brick1.png", data, 1, 0.0f, 1.0f, 1);
					pom[*ids] = po;
				}
			}
		}
		LevelData::brickcount = 20;
	}
	else if (level == 3)
	{
		data = new float[4]{390.0f, 200.0f, 30, 15};
		ids = new std::string(StringUtils::format("BT%d", ++Transmit_Brick::index));
		po = new Transmit_Brick(ids, layer, world, "Image/Transmit_Brick.png", data, 1, 0.0f, 1.0f, 1);
		pom[*ids] = po;

		data = new float[4]{-390.0f, 200.0f, 30, 15};
		ids = new std::string(StringUtils::format("BT%d", ++Transmit_Brick::index));
		po = new Transmit_Brick(ids, layer, world, "Image/Transmit_Brick.png", data, 1, 0.0f, 1.0f, 1);
		pom[*ids] = po;

		pos p[1005];
		int tot = 3, cnt = 1;
		p[1].x = 30.0f;
		p[1].y = 150.0f;
		p[1].cnt = 1;
		data = new float[4]{p[1].x, p[1].y, 30, 15};
		ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
		po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
		pom[*ids] = po;

		p[2].x = -31.0f;
		p[2].y = 150.0f;
		p[2].cnt = 1;
		data = new float[4]{p[2].x, p[2].y, 30, 15};
		ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
		po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
		pom[*ids] = po;

		p[3].x = 0.0f;
		p[3].y = 150.0f - 31.0f;
		p[3].cnt = 1;
		data = new float[4]{p[3].x, p[3].y, 30, 15};
		ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
		po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
		pom[*ids] = po;

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
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;

				tot++;
				p[tot].x = -30.0f - 31.0f * cnt;
				p[tot].y = 31.0f * cnt + 150.0f;
				p[tot].cnt = p[i].cnt + 1;
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;

				cnt++;
			}
			if (p[i].x < 0)
			{
				tot++;
				p[tot].x = p[i].x - 61.0f;
				p[tot].y = p[i].y;
				p[tot].cnt = p[i].cnt + 1;
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;

			}
			else if (p[i].x > 0)
			{
				tot++;
				p[tot].x = p[i].x + 61.0f;
				p[tot].y = p[i].y;
				p[tot].cnt = p[i].cnt + 1;
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;
			}
			else if (p[i].x == 0)
			{
				tot++;
				p[tot].x = p[i].x + 61.0f;
				p[tot].y = p[i].y;
				p[tot].cnt = p[i].cnt + 1;
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;

				tot++;
				p[tot].x = p[i].x - 61.0f;
				p[tot].y = p[i].y;
				p[tot].cnt = p[i].cnt + 1;
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;

				tot++;
				p[tot].x = p[i].x + 30.0f;
				p[tot].y = p[i].y - 31.0f;
				p[tot].cnt = p[i].cnt + 1;
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;

				tot++;
				p[tot].x = p[i].x - 30.0f;
				p[tot].y = p[i].y - 31.0f;
				p[tot].cnt = p[i].cnt + 1;
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;

				tot++;
				p[tot].x = p[i].x;
				p[tot].y = p[i].y - 62.0f;
				p[tot].cnt = p[i].cnt + 1;
				data = new float[4]{p[tot].x, p[tot].y, 30, 15};
				if (p[tot].cnt == 2)
				{
					ids = new std::string(StringUtils::format("BU%d", ++Upgrade_Brick::index));
					po = new Upgrade_Brick(ids, layer, world, "Image/Upgrade_Brick3.png", data, 1, 0.0f, 1.0f, 3);
				}
				else if (p[tot].cnt == 3)
				{
					ids = new std::string(StringUtils::format("BI%d", ++Image_Brick::index));
					po = new Image_Brick(ids, layer, world, "Image/Image_Brick2.png", data, 1, 0.0f, 1.0f, 2);
				}
				else if (p[tot].cnt == 4)
				{
					ids = new std::string(StringUtils::format("BA%d", ++Accelerate_Brick::index));
					po = new Accelerate_Brick(ids, layer, world, "Image/Accelerate_Decelerate_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else if (p[tot].cnt == 5)
				{

					ids = new std::string(StringUtils::format("BR%d", ++Reversal_Brick::index));
					po = new Reversal_Brick(ids, layer, world, "Image/Reversal_Brick1.png", data, 1, 0.0f, 1.0f, 1);
				}
				else
				{
					ids = new std::string(StringUtils::format("BH%d", ++Hard_Brick::index));
					po = new Hard_Brick(ids, layer, world, "Image/Hard_Brick.png", data, 1, 0.0f, 1.0f, 1);
				}
				pom[*ids] = po;
			}
		}
		LevelData::brickcount = 72;
	}
}
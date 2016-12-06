#include "MyHelpLayer.h"// class implemented

/////////////// PUBLIC///////////////////////

bool MyHelpLayer::init()
{
	//���ø���ĳ�ʼ��
	if (!Layer::init())
	{
		return false;
	}
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();

	//�������ز˵���
	auto backItem = MenuItemImage::create
	(
		"Image/back.png",	//ƽʱ��ͼƬ
		"Image/back1.png",	//ѡ��ʱ��ͼƬ
		CC_CALLBACK_1(MyHelpLayer::menueBack, this) //���ʱִ�еĻص�����
	);
	//���÷��ز˵����λ��
	backItem->setPosition(
		Point(
			origin.x + visibleSize.width - 40,	//X����
			origin.y + visibleSize.height - 40	//Y����
		)
	);
	backItem->setScale(0.25f);
	//�����˵�����
	auto backMenu = Menu::create(backItem, NULL);
	//���ò˵�λ��
	backMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(backMenu, 1);

	//����һ��������󣬰���background.pngͼƬ
	auto bgSprite = Sprite::create("Image/backgroundhelp.png");
	//���þ�������λ��
	bgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//��������ӵ�������
	this->addChild(bgSprite, 0);

	return true;
}

//==============��Ĳ��� =====================

void MyHelpLayer::menueBack(cocos2d::Ref*  pSender)
{
	gsm->goStartScene();
}

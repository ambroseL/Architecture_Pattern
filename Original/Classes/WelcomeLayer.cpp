#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
#include "Beginlayer.h"
using namespace std;

//USING_NS_CC;
using namespace cocos2d;
bool Welcomelayer::playBgM = false;

Welcomelayer::~Welcomelayer()
{

}

//ʵ��WelcomeLayer���е�init��������ʼ������
bool Welcomelayer::init()
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

	auto titleSp = Sprite::create("Image/title.png");
	titleSp->setPosition(Point(visibleSize.width + origin.x -300, visibleSize.height + origin.y - 270));
	titleSp->setScale(1.3f);
	this->addChild(titleSp, 1);
	//������ʼ�˵���
	auto startItem = MenuItemImage::create
		(
			"Image/start1.png",	//ƽʱ��ͼƬ
			"Image/start2.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(Welcomelayer::menuStart, this) //���ʱִ�еĻص�����
		);
	//���ÿ�ʼ�˵����λ��
	startItem->setPosition(
		Point(
		origin.x + visibleSize.width / 2 + 225,//X����
			origin.y + visibleSize.height / 2 - 120//Y����
		)
		);

	//�����˵�����
	auto startMenu = Menu::create(startItem, NULL);
	//���ò˵�λ��
	startMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(startMenu, 1);

	//���������˵���
	auto helpItem = MenuItemImage::create
		(
			"Image/help1.png",	//ƽʱ��ͼƬ
			"Image/help2.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_1(Welcomelayer::menuHelp, this) //���ʱִ�еĻص�����
		);

	//���ð����˵����λ��
	helpItem->setPosition(
		Point(
			origin.x + visibleSize.width / 2 + 225,	//X����
			origin.y + visibleSize.height / 2 - 200	//Y����
		)
		);
	//�����˵�����
	auto helpMenu = Menu::create(helpItem, NULL);
	//���ò˵�λ��
	helpMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(helpMenu, 1);

	//�����˳��˵���
	auto exitItem = MenuItemImage::create
		(
			"Image/exit1.png",
			"Image/exit2.png",
			CC_CALLBACK_1(Welcomelayer::menuExit, this) //���ʱִ�еĻص�����
		);
	exitItem->setPosition(
		Point(
		origin.x + visibleSize.width / 2 + 225,	//X����
		origin.y + visibleSize.height / 2 - 280		//Y����
		)
		);
	//�����˵�����
	auto exitMenu = Menu::create(exitItem, NULL);
	//���ò˵�λ��
	exitMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(exitMenu, 1);

	//����һ��������󣬰���background.pngͼƬ
	auto bgSprite = Sprite::create("Image/background.png");
	//���þ�������λ��
	bgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//��������ӵ�������
	this->addChild(bgSprite, 0);

	// Ԥ���ر�������
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sound/bgm.mp3");
	//��ʼ���ű������֣�true��ʾѭ��
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/bgm.mp3", true);
	//��������0.0-1.0
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);

	return true;
}

void Welcomelayer::menuStart(cocos2d::Ref* pSender)
{
	gsm->gogameScene();
}

void Welcomelayer::menuHelp(cocos2d::Ref* pSender)
{
	gsm->goHelpScene();

}

void Welcomelayer::menuExit(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();//��Ϸ����
}
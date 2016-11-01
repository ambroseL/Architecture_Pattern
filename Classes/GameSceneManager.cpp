#include "GameSceneManager.h"
#include "Beginlayer.h"
#include "LevelData.h"
#include "Helplayer.h"
using namespace cocos2d;

void GameSceneManager::createScene()
{
	//����һ����������
	welcomeScene = Scene::create();

	//����һ����ӭ��������
	Welcomelayer *wlayer = Welcomelayer::create();

	welcomeScene->addChild(wlayer);
	//���ù�����
	wlayer->gsm = this;
}

void GameSceneManager::gogameScene()//ȥ��Ϸ�����ķ���
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 1;
	//������������
	gameScene = Scene::create();
	//����һ����������
	Beginlayer *glayer = Beginlayer::create();
	//���ù�����
	glayer->gsm = this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::goWelcomeScene()//ȥ��ӭ����
{
	Director::getInstance()->setDepthTest(true);
	welcomeScene = Scene::create();//������ӭ��������
	Welcomelayer* wlayer = Welcomelayer::create();
	wlayer->gsm = this;//���ù�����
	welcomeScene->addChild(wlayer);
	auto ss = TransitionFade::create(0.5f, welcomeScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound2Scene()//ȥ�ڶ��صķ���
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 2;
	//������������
	gameScene = Scene::create();
	//����һ����������
	Beginlayer *glayer = Beginlayer::create();
	//���ù�����
	glayer->gsm = this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::goRound3Scene()//ȥ�����صķ���
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 3;
	//������������
	gameScene = Scene::create();
	//����һ����������
	Beginlayer *glayer = Beginlayer::create();
	//���ù�����
	glayer->gsm = this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::goHelpScene()//ȥ��������
{
	Director::getInstance()->setDepthTest(true);
	helpScene = Scene::create();//����������������
	Helplayer* hlayer = Helplayer::create();
	hlayer->gsm = this;//���ù�����
	helpScene->addChild(hlayer);

	auto ss = TransitionFade::create(0.5f, helpScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::reStart()//�����һ�صķ���
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 1;
	//������������
	gameScene = Scene::create();
	//����һ����������
	Beginlayer *glayer = Beginlayer::create();
	//���ù�����
	glayer->gsm = this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::reStart2()//����ڶ��صķ���
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 2;
	//������������
	gameScene = Scene::create();
	//����һ����������
	Beginlayer *glayer = Beginlayer::create();
	//���ù�����
	glayer->gsm = this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::reStart3()//��������صķ���
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 3;
	//������������
	gameScene = Scene::create();
	//����һ����������
	Beginlayer *glayer = Beginlayer::create();
	//���ù�����
	glayer->gsm = this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}


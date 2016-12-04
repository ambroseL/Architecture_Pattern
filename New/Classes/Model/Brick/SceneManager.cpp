#include "SceneManager.h"
#include "GameLayer.h"
#include "StartLayer.h"
#include "MyHelpLayer.h"


void SceneManager::createScene()
{
	//����һ����������
	startScene = Scene::create();

	//����һ����ӭ��������
	StartLayer *wlayer = StartLayer::create();

	wlayer->setScenemanager(this);

	//���ù�����
	startScene->addChild(wlayer);	
}

void SceneManager::gogameScene()//ȥ��Ϸ�����ķ���
{
	Director::getInstance()->setDepthTest(true);
	
	//������������
	gameScene = Scene::create();
	
	GameLayer* glayer = GameLayer::create();
	glayer->setLevel(1);
	glayer->createBricks();
	
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);
	

	//���ù�����
	glayer->setSceneManager(this);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::goStartScene()//ȥ��ӭ����
{
	Director::getInstance()->setDepthTest(true);
	startScene = Scene::create();//������ӭ��������
	
	StartLayer* wlayer = StartLayer::create();
	
	wlayer->setScenemanager(this);//���ù�����

	startScene->addChild(wlayer);
	auto ss = TransitionFade::create(0.5f, startScene);

	Director::getInstance()->replaceScene(ss);
}

void SceneManager::goHelpScene()//ȥ��������
{
	Director::getInstance()->setDepthTest(true);

	helpScene = Scene::create();//����������������

	MyHelpLayer* hlayer = MyHelpLayer::create();

	helpScene->addChild(hlayer);

	hlayer->setSceneManager(this);//���ù�����

	auto ss = TransitionFade::create(0.5f, helpScene);
	Director::getInstance()->replaceScene(ss);
}

void SceneManager::goRound2Scene()//ȥ�ڶ��صķ���
{
	Director::getInstance()->setDepthTest(true);

	//������������
	gameScene = Scene::create();
	//����һ����������
	
	GameLayer *glayer = GameLayer::create();
	glayer->setLevel(2);
	glayer->createBricks();
	
	glayer->setSceneManager(this);//���ù�����

	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::goRound3Scene()//ȥ�����صķ���
{
	Director::getInstance()->setDepthTest(true);

	//������������
	gameScene = Scene::create();
	
	GameLayer *glayer = GameLayer::create();
	glayer->setLevel(3);
	glayer->createBricks();

	glayer->setSceneManager(this);//���ù�����
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void SceneManager::reStart()//�����һ�صķ���
{
	Director::getInstance()->setDepthTest(true);
	
	//������������
	gameScene = Scene::create();

	//����һ����������

	GameLayer *glayer = GameLayer::create();
	glayer->setLevel(1);
	glayer->createBricks();

	//���ù�����
	glayer->setSceneManager(this);

	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::reStart2()//����ڶ��صķ���
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();

	//����һ����������

	GameLayer *glayer = GameLayer::create();;
	glayer->setLevel(2);
	glayer->createBricks();


	//���ù�����
	glayer->setSceneManager(this);
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::reStart3()//��������صķ���
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();

	//����һ����������

	GameLayer *glayer = GameLayer::create();
	glayer->setLevel(3);
	glayer->createBricks();

	//���ù�����
	glayer->setSceneManager(this);
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}


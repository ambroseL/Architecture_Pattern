#include "SceneManager.h"
#include "GameLayer.h"
#include "StartLayer.h"
#include "MyHelpLayer.h"


void SceneManager::createScene()
{
	Scene* startScene = Scene::create();
	
	//����һ����ӭ��������
	StartLayer *wlayer = StartLayer::create();
	
	wlayer->setScenemanager(this);

	//���ù�����
	startScene->addChild(wlayer);
	
	auto director = Director::getInstance();
	director->runWithScene(startScene);
}

void SceneManager::gogameScene()//ȥ��Ϸ�����ķ���
{
	Scene*  gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);
	GameLayer* glayer = GameLayer::create();

	glayer->setLevel(1);
	glayer->createBricks();
	
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);
	//���ù�����
	glayer->setSceneManager(this);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));

}

void SceneManager::goStartScene()//ȥ��ӭ����
{
	Scene*  startScene = Scene::create();

	Director::getInstance()->setDepthTest(true);

	StartLayer* wlayer = StartLayer::create();

	wlayer->setScenemanager(this);//���ù�����

	startScene->addChild(wlayer);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, startScene));


}

void SceneManager::goHelpScene()//ȥ��������
{
	Scene* helpScene = Scene::create();

	Director::getInstance()->setDepthTest(true);

	MyHelpLayer* hlayer = MyHelpLayer::create();
	
	helpScene->addChild(hlayer);

	hlayer->setSceneManager(this);//���ù�����

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, helpScene));

}

void SceneManager::goRound2Scene()//ȥ�ڶ��صķ���
{
	Scene* gameScene = Scene::create();
	Director::getInstance()->setDepthTest(true);

	//����һ����������
	
	GameLayer *glayer = GameLayer::create();

	glayer->setLevel(2);
	glayer->createBricks();
	
	glayer->setSceneManager(this);//���ù�����

	//�򳡾���Ӳ���
	gameScene->addChild(glayer);
	
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void SceneManager::goRound3Scene()//ȥ�����صķ���
{
	Scene* gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);
	
	GameLayer *glayer = GameLayer::create();

	glayer->setLevel(3);
	glayer->createBricks();

	glayer->setSceneManager(this);//���ù�����
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void SceneManager::reStart()//�����һ�صķ���
{
	Scene* gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);

	//����һ����������

	GameLayer *glayer = GameLayer::create();


	glayer->setLevel(1);
	glayer->createBricks();

	//���ù�����
	glayer->setSceneManager(this);

	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void SceneManager::reStart2()//����ڶ��صķ���
{
	Scene* gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);

	//����һ����������

	GameLayer *glayer = GameLayer::create();

	glayer->setLevel(2);
	glayer->createBricks();


	//���ù�����
	glayer->setSceneManager(this);
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void SceneManager::reStart3()//��������صķ���
{
	Scene* gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);


	//����һ����������
	GameLayer *glayer = GameLayer::create();


	glayer->setLevel(3);
	glayer->createBricks();

	//���ù�����
	glayer->setSceneManager(this);
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);
	
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));	
}


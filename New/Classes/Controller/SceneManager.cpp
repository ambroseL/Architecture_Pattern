#include "SceneManager.h"
#include "GameLayer.h"
#include "StartLayer.h"
#include "MyHelpLayer.h"


void SceneManager::createScene()
{
	Scene* startScene = Scene::create();
	
	//创建一个欢迎布景对象
	StartLayer *wlayer = StartLayer::create();
	
	wlayer->setScenemanager(this);

	//设置管理者
	startScene->addChild(wlayer);
	
	auto director = Director::getInstance();
	director->runWithScene(startScene);
}

void SceneManager::gogameScene()//去游戏场景的方法
{
	Scene*  gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);
	GameLayer* glayer = GameLayer::create();

	glayer->setLevel(1);
	glayer->createBricks();
	
	//向场景添加布景
	gameScene->addChild(glayer);
	//设置管理者
	glayer->setSceneManager(this);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));

}

void SceneManager::goStartScene()//去欢迎场景
{
	Scene*  startScene = Scene::create();

	Director::getInstance()->setDepthTest(true);

	StartLayer* wlayer = StartLayer::create();

	wlayer->setScenemanager(this);//设置管理者

	startScene->addChild(wlayer);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, startScene));


}

void SceneManager::goHelpScene()//去帮助场景
{
	Scene* helpScene = Scene::create();

	Director::getInstance()->setDepthTest(true);

	MyHelpLayer* hlayer = MyHelpLayer::create();
	
	helpScene->addChild(hlayer);

	hlayer->setSceneManager(this);//设置管理者

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, helpScene));

}

void SceneManager::goRound2Scene()//去第二关的方法
{
	Scene* gameScene = Scene::create();
	Director::getInstance()->setDepthTest(true);

	//创建一个布景对象
	
	GameLayer *glayer = GameLayer::create();

	glayer->setLevel(2);
	glayer->createBricks();
	
	glayer->setSceneManager(this);//设置管理者

	//向场景添加布景
	gameScene->addChild(glayer);
	
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void SceneManager::goRound3Scene()//去第三关的方法
{
	Scene* gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);
	
	GameLayer *glayer = GameLayer::create();

	glayer->setLevel(3);
	glayer->createBricks();

	glayer->setSceneManager(this);//设置管理者
	//向场景添加布景
	gameScene->addChild(glayer);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void SceneManager::reStart()//重玩第一关的方法
{
	Scene* gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);

	//创建一个布景对象

	GameLayer *glayer = GameLayer::create();


	glayer->setLevel(1);
	glayer->createBricks();

	//设置管理者
	glayer->setSceneManager(this);

	//向场景添加布景
	gameScene->addChild(glayer);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void SceneManager::reStart2()//重玩第二关的方法
{
	Scene* gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);

	//创建一个布景对象

	GameLayer *glayer = GameLayer::create();

	glayer->setLevel(2);
	glayer->createBricks();


	//设置管理者
	glayer->setSceneManager(this);
	//向场景添加布景
	gameScene->addChild(glayer);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void SceneManager::reStart3()//重玩第三关的方法
{
	Scene* gameScene = Scene::create();

	Director::getInstance()->setDepthTest(true);


	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();


	glayer->setLevel(3);
	glayer->createBricks();

	//设置管理者
	glayer->setSceneManager(this);
	//向场景添加布景
	gameScene->addChild(glayer);
	
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));	
}


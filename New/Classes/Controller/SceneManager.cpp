#include "SceneManager.h"
#include "GameLayer.h"
#include "StartLayer.h"
#include "MyHelpLayer.h"


void SceneManager::createScene()
{
	//创建一个场景对象
	startScene = Scene::create();

	//创建一个欢迎布景对象
	StartLayer *wlayer = StartLayer::create();

	startScene->addChild(wlayer);
	//设置管理者
//	wlayer->gsm = this;
}

void SceneManager::gogameScene()//去游戏场景的方法
{
	Director::getInstance()->setDepthTest(true);
	
	//创建场景对象
	gameScene = Scene::create();
	
	//创建一个布景对象
	
	GameLayer *glayer = nullptr;
	glayer->setLevel(1);
	glayer = GameLayer::create();

	//设置管理者
	glayer->setSceneManager(this);
	
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::goStartScene()//去欢迎场景
{
	Director::getInstance()->setDepthTest(true);
	startScene = Scene::create();//创建欢迎场景对象
	
	StartLayer* wlayer = StartLayer::create();
	
	wlayer->setScenemanager(this);//设置管理者

	startScene->addChild(wlayer);
	auto ss = TransitionFade::create(0.5f, startScene);

	Director::getInstance()->replaceScene(ss);
}

void SceneManager::goRound2Scene()//去第二关的方法
{
	Director::getInstance()->setDepthTest(true);

	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	
	
	GameLayer *glayer = nullptr;
	glayer->setLevel(2);
	glayer = GameLayer::create();
	
	glayer->setSceneManager(this);//设置管理者

	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::goRound3Scene()//去第三关的方法
{
	Director::getInstance()->setDepthTest(true);
	//GameLayer::level = 3;
	//创建场景对象
	gameScene = Scene::create();
	
	GameLayer *glayer = nullptr;
	glayer->setLevel(3);
	glayer = GameLayer::create();

	glayer->setSceneManager(this);//设置管理者
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::goHelpScene()//去帮助场景
{
	Director::getInstance()->setDepthTest(true);
	helpScene = Scene::create();//创建帮助场景对象
	
	MyHelpLayer* hlayer = MyHelpLayer::create();
	
	hlayer->setSceneManager(this);//设置管理者
	
	helpScene->addChild(hlayer);

	auto ss = TransitionFade::create(0.5f, helpScene);
	Director::getInstance()->replaceScene(ss);
}

void SceneManager::reStart()//重玩第一关的方法
{
	Director::getInstance()->setDepthTest(true);
	
	//创建场景对象
	gameScene = Scene::create();

	//创建一个布景对象

	GameLayer *glayer = nullptr;
	glayer->setLevel(1);
	glayer = GameLayer::create();

	//设置管理者
	glayer->setSceneManager(this);

	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::reStart2()//重玩第二关的方法
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();

	//创建一个布景对象

	GameLayer *glayer = nullptr;
	glayer->setLevel(2);
	glayer = GameLayer::create();

	//设置管理者
	glayer->setSceneManager(this);
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void SceneManager::reStart3()//重玩第三关的方法
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();

	//创建一个布景对象

	GameLayer *glayer = nullptr;
	glayer->setLevel(3);
	glayer = GameLayer::create();

	//设置管理者
	glayer->setSceneManager(this);
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}


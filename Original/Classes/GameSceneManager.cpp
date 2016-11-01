#include "GameSceneManager.h"
#include "Beginlayer.h"
#include "LevelData.h"
#include "Helplayer.h"
using namespace cocos2d;

void GameSceneManager::createScene()
{
	//创建一个场景对象
	welcomeScene = Scene::create();

	//创建一个欢迎布景对象
	Welcomelayer *wlayer = Welcomelayer::create();

	welcomeScene->addChild(wlayer);
	//设置管理者
	wlayer->gsm = this;
}

void GameSceneManager::gogameScene()//去游戏场景的方法
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 1;
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	Beginlayer *glayer = Beginlayer::create();
	//设置管理者
	glayer->gsm = this;
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::goWelcomeScene()//去欢迎场景
{
	Director::getInstance()->setDepthTest(true);
	welcomeScene = Scene::create();//创建欢迎场景对象
	Welcomelayer* wlayer = Welcomelayer::create();
	wlayer->gsm = this;//设置管理者
	welcomeScene->addChild(wlayer);
	auto ss = TransitionFade::create(0.5f, welcomeScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound2Scene()//去第二关的方法
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 2;
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	Beginlayer *glayer = Beginlayer::create();
	//设置管理者
	glayer->gsm = this;
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::goRound3Scene()//去第三关的方法
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 3;
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	Beginlayer *glayer = Beginlayer::create();
	//设置管理者
	glayer->gsm = this;
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::goHelpScene()//去帮助场景
{
	Director::getInstance()->setDepthTest(true);
	helpScene = Scene::create();//创建帮助场景对象
	Helplayer* hlayer = Helplayer::create();
	hlayer->gsm = this;//设置管理者
	helpScene->addChild(hlayer);

	auto ss = TransitionFade::create(0.5f, helpScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::reStart()//重玩第一关的方法
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 1;
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	Beginlayer *glayer = Beginlayer::create();
	//设置管理者
	glayer->gsm = this;
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::reStart2()//重玩第二关的方法
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 2;
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	Beginlayer *glayer = Beginlayer::create();
	//设置管理者
	glayer->gsm = this;
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::reStart3()//重玩第三关的方法
{
	Director::getInstance()->setDepthTest(true);
	Beginlayer::level = 3;
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	Beginlayer *glayer = Beginlayer::create();
	//设置管理者
	glayer->gsm = this;
	//向场景添加布景
	gameScene->addChild(glayer);

	auto ss = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(ss);

}


#include "UIController.h"
#include "deprecated/CCDeprecated.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

UIController::UIController():layer(nullptr)
{
}

UIController::~UIController()
{
}

void UIController::setLayer(GameLayer* layer)
{
	this->layer = layer;
}

void UIController::updateLifeSprite(int HP)
{
	Sprite* dSp = layer->getLifeSprite();
	Texture2D* texture = CCTextureCache::sharedTextureCache()->addImage("Image/HP" + StringUtils::format("%d", HP) + ".png");
	dSp->setTexture(texture);
}

void UIController::playYX()
{
	//��ʼ���ű�����Ч��false��ʾ��ѭ��
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/eatprops.wav", false);
	//������Ч����0.0-1.0
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
}

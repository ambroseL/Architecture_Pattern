#include "UIController.h" // class implemented
#include "deprecated/CCDeprecated.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

UIController::UIController():layer(nullptr)
{
}//UIController

UIController::~UIController()
{
}//~UIController

 //==============���Դ�ȡ=====================
void UIController::setLayer(GameLayer* layer)
{
	this->layer = layer;
}

//==============��Ĳ��� =====================

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

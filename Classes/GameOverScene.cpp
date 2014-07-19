//
//  GameOverScene.cpp
//  BaseGame02
//
//  Created by P on 2014/07/17.
//
//

#include "GameOverScene.h"
#include "OpeningScene.h"

using namespace cocos2d;

// 画面のScene,Layerを生成
Scene* GameOverScene::createScene(){
    Scene* scene = Scene::create();
    Layer* layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

// Layerの初期処理
bool GameOverScene::init(){
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }
    
    // 画像描画用に画面のサイズと座標開始位置を取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // レイヤーの背景色を設定
    // DeprecationWarnning:
    // ccc4()は非推奨のため、Color4B()を使用（中身はinline関数で、ccc4を実行していた）
    LayerColor *color = LayerColor::create(Color4B(100.0f,100.0f,100.0f,255.0f));
    this->addChild(color);
    
    
    // ゲームオーバ画像の追加（スプライト生成）
    auto sprite = Sprite::create("GameOverBackground.png");
    // 画面中央への配置
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // レイヤーへスプライト追加
    this->addChild(sprite, 0);

    
    
    // クリアボタン作成
    MenuItemFont* titleButton = MenuItemFont::create("Title!",
                                                     [this](Ref *pSender){
                                                         float duration = 1.0f;
                                                         Scene* pScene = TransitionFadeUp::create(duration, OpeningScene::createScene());
                                                         Director::getInstance()->replaceScene(pScene);
                                                     });
    
    
    titleButton->setPosition(Vec2(origin.x + titleButton->getContentSize().width * 4 ,
                                  origin.y + titleButton->getContentSize().height * 2));
    
    
    
    // メニュー作成
    Menu* menu = Menu::create(titleButton, NULL);
    menu->setPosition(0,0);
    this->addChild(menu);
    
    return true;
}


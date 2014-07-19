//
//  TitleScene.cpp
//  BaseGame02
//
//  Created by P on 2014/07/17.
//
//

#include "TitleScene.h"
#include "PlayScene.h"

using namespace cocos2d;

// 画面のScene,Layerを生成
Scene* TitleScene::createScene(){
    Scene* scene = Scene::create();
    Layer* layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

// Layerの初期処理
// ここにゲームの一番最初の処理を記載
bool TitleScene::init(){
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
    LayerColor *color = LayerColor::create(Color4B(0.0f,0.0f,200.0f,255.0f));
    this->addChild(color);

    
    // タイトル画像の追加（スプライト生成）
    auto sprite = Sprite::create("TitleBackground.png");
    // 画面中央への配置
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // レイヤーへスプライト追加
    this->addChild(sprite, 0);

    
    // スタートボタンの作成
    MenuItemImage* startButton = MenuItemImage::create(
                                                       "start.png",
                                                       "start.png",
                                                       [this](Ref *pSender){
                                                           // スタートボタンタップ後はプレイ画面へ遷移
                                                           Director::getInstance()->replaceScene(PlayScene::createScene());
                                                       });
    
    startButton->setPosition(Vec2(origin.x + startButton->getContentSize().width * 3 ,
                                  origin.y + startButton->getContentSize().height *5));
    
    // 作成したスタートボタンの設置
    Menu* menu = Menu::create(startButton, NULL);
    menu->setPosition(0,0);
    this->addChild(menu);


    
    return true;
}

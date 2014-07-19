//
//  PlayScene.cpp
//  BaseGame02
//
//  Created by P on 2014/07/17.
//
//

#include "PlayScene.h"
#include "MenuLayer.h"
#include "EndingScene.h"
#include "GameOverScene.h"

using namespace cocos2d;

// 画面のScene,Layerを生成
Scene* PlayScene::createScene(){
    Scene* scene = Scene::create();
    Layer* layer = PlayScene::create();
    scene->addChild(layer);
    return scene;
}

// Layerの初期処理
// ここにゲームの一番最初の処理を記載
bool PlayScene::init(){
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
    LayerColor *color = LayerColor::create(Color4B(0.0f,200.0f,0.0f,255.0f));
    this->addChild(color);

    
    // プレイ画像の追加（スプライト生成）
    auto sprite = Sprite::create("PlayBackground.png");
    // 画面中央への配置
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // レイヤーへスプライト追加
    this->addChild(sprite, 0);

    
    // メニューボタン作成（ゲーム一時停止ボタン）
    MenuItemImage* menuButton = MenuItemImage::create(
                                                      "menubutton.png",
                                                      "menubutton.png",
                                                      [this](Ref *pSender){
                                                          auto menuLayer = MenuLayer::create(this);
                                                          this->addChild(menuLayer,100,70000);
                                                      });
    
    
    menuButton->setPosition(Vec2(origin.x + menuButton->getContentSize().width * 6 ,
                                 origin.y + menuButton->getContentSize().height / 2));
    
    // メニュー作成
    Menu* menu = Menu::create(menuButton, NULL);
    menu->setPosition(0,0);
    this->addChild(menu);
    
    // ゲーム処理（ゲームそのものの実行）
    gameLogic();
    
    
    return true;
}



// ======================================================
// これ以降をゲームのメイン処理として、ゲームごとに書き換える
// パズルゲームなのか、アクションゲームなのか、この中の処理で変わる
// ==================↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓=====================


// ゲームメイン処理
void PlayScene::gameLogic(){
    // 座標開始位置を取得
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ゲームオブジェクトの追加とそのアニメーション処理
    schedule(schedule_selector(PlayScene::addGameObject), 2.0);
    

    // クリアボタン作成
    MenuItemFont* clearButton = MenuItemFont::create("CLEAR!",
                                                      [this](Ref *pSender){
                                                          float duration = 1.0f;
                                                          Scene* pScene = TransitionFadeDown::create(duration, EndingScene::createScene());
                                                          Director::getInstance()->replaceScene(pScene);
                                                      });
    
    
    clearButton->setPosition(Vec2(origin.x + clearButton->getContentSize().width * 8 ,
                                 origin.y + clearButton->getContentSize().height * 2));
    
    // ゲームオーバーボタン作成
    MenuItemFont* gameOverButton = MenuItemFont::create("GAMEOVER!",
                                                     [this](Ref *pSender){
                                                         float duration = 1.0f;
                                                         Scene* pScene = TransitionJumpZoom::create(duration, GameOverScene::createScene());
                                                         Director::getInstance()->replaceScene(pScene);
                                                     });
    
    
    gameOverButton->setPosition(Vec2(origin.x + gameOverButton->getContentSize().width * 5 ,
                                  origin.y + gameOverButton->getContentSize().height * 4));

    
    
    // 作成したボタンの追加
    Menu* menu = Menu::create(clearButton, gameOverButton, NULL);
    menu->setPosition(0,0);
    this->addChild(menu);
}

// ゲームオブジェクトの追加
void PlayScene::addGameObject(float delta){
    // 画像描画用に画面のサイズと座標開始位置を取得
    // TODO:HelloWorldの描画をそのままパクっただけなので、もうちょいマシな方法を考える。
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // ゲームオブジェクト画像の追加（スプライト生成）
    auto gameObjectSprite = Sprite::create("tomato.png");
    // 画面中央への配置
    gameObjectSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // レイヤーへスプライト追加
    this->addChild(gameObjectSprite, 0);
    
    // ゲームオブジェクトの移動アニメーション
    float duration = 2.0f;
    MoveTo* actionMove = MoveTo::create(duration, Vec2(origin.x, origin.y + visibleSize.height));
    gameObjectSprite->runAction(actionMove);    
}


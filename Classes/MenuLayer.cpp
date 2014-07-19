//
//  MenuLayer.cpp
//  BaseGame02
//
//  Created by P on 2014/07/17.
//
//

#include "MenuLayer.h"
#include "TitleScene.h"

using namespace cocos2d;

// staticメンバ変数の初期化
Layer* MenuLayer::mFromLayer = 0;

// メニュー画面レイヤ作成関数
MenuLayer* MenuLayer::create(cocos2d::Layer* const pFromLayer) {

    // 呼び出し元のレイヤ
    mFromLayer = pFromLayer;

    // メニュー画面呼び出し元を一時停止
    // まず小要素すべてを一時停止
    Vector<Node*> vec = mFromLayer->getChildren();
    for (Vector<Node*>::iterator it = vec.begin(); it != vec.end(); ++it) {
        Node *node = *it;
        node->pause();
    }
    // メニュー画面呼び出し元を一時停止
    mFromLayer->pause();

    // CREATE_FUNC()の中で実行される内容を記載
    // コンストラクタ呼び出しやメモリ自動開放処理など
    MenuLayer *pRet = new MenuLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

// メニュー画面初期処理
bool MenuLayer::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    // 画像描画用に画面のサイズと座標開始位置を取得(レイアウトを決める他にいい方法はないか？)
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // レイヤーの背景色を設定
    // DeprecationWarnning:
    // ccc4()は非推奨のため、Color4B()を使用（中身はinline関数で、ccc4を実行していた）
    LayerColor *color = LayerColor::create(Color4B(0.0f,0.0f,0.0f,100.0f));
    this->addChild(color);
    
    
    // メニュー画像の追加（スプライト生成）
    auto sprite = Sprite::create("HelloWorld.png");
    // 画面中央への配置
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // レイヤーへスプライト追加
    this->addChild(sprite, 0);
    
    
    // タイトルへ戻るボタンの作成
    MenuItemImage* startButton = MenuItemImage::create(
                                                       "titlebutton.png",
                                                       "titlebutton.png",
                                                       // DeprecationWarnning:
                                                       // Objectクラスが非推奨のため、Refクラスを使用
                                                       [this](Ref *pSender){
                                                           // タイトル画面へ遷移
                                                           Director::getInstance()->replaceScene(TitleScene::createScene());
                                                       });
    
    startButton->setPosition(Vec2(origin.x + startButton->getContentSize().width * 3 ,
                                  origin.y + startButton->getContentSize().height * 5));

    
    // つづけるボタンの作成
    MenuItemImage* resumeButton = MenuItemImage::create(
                                                       "buttonContinue.png",
                                                       "buttonContinue.png",
                                                       // DeprecationWarnning:
                                                       // Objectクラスが非推奨のため、Refクラスを使用
                                                       [this](Ref *pSender){
                                                           // メニュー画面の削除
                                                           this->removeFromParentAndCleanup(true);

                                                           // プレイ中レイヤーの小要素取得
                                                           cocos2d::Vector<Node*> vec = mFromLayer->getChildren();
                                                           for (cocos2d::Vector<Node*>::iterator it = vec.begin(); it != vec.end(); ++it) {
                                                               Node *node = *it;
                                                               node->resume();
                                                           }
                                                           // プレイ中レイヤーの復帰処理
                                                           mFromLayer->resume();
                                                       });
    
    // つづけるボタンのポジション
    resumeButton->setPosition(Vec2(origin.x + resumeButton->getContentSize().width * 3 ,
                                   origin.y + resumeButton->getContentSize().height * 3));
    
    
    
    // 作成したボタンの設置
    Menu* menu = Menu::create(startButton, resumeButton, NULL);
    menu->setPosition(0,0);
    this->addChild(menu);
    
    
    // ゲームオブジェクトの追加とそのアニメーション処理
    schedule(schedule_selector(MenuLayer::addGameObject), 2.0);

    
    return true;
}





// ゲームオブジェクトの追加（ポーズ状態確認用）
void MenuLayer::addGameObject(float delta){
    // 画像描画用に画面のサイズと座標開始位置を取得
    // こいつはローカル変数として持つべき値じゃないよな。どうすべきか。
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // ゲームオブジェクト画像の追加（スプライト生成）
    auto gameObjectSprite = Sprite::create("tomato.png");
    // 画面中央ちょい左へ配置
    gameObjectSprite->setPosition(Vec2(visibleSize.width/3 + origin.x, visibleSize.height/3 + origin.y));
    // レイヤーへスプライト追加
    this->addChild(gameObjectSprite, 0);
    
    // ゲームオブジェクトの移動アニメーション
    float duration = 2.0f;
    MoveTo* actionMove = MoveTo::create(duration, Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height));
    gameObjectSprite->runAction(actionMove);
}


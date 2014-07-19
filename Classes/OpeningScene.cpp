//
//  OpeningScene.cpp
//  BaseGame02
//
//  Created by P on 2014/07/17.
//
//

#include "OpeningScene.h"
#include "TitleScene.h"

using namespace cocos2d;


// 画面のScene,Layerを生成
Scene* OpeningScene::createScene(){
    Scene* scene = Scene::create();
    Layer* layer = OpeningScene::create();
    scene->addChild(layer);
    return scene;
}

// Layerの初期処理
// ここにゲームの一番最初の処理を記載
bool OpeningScene::init(){
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
    LayerColor *color = LayerColor::create(Color4B(200.0f,0.0f,0.0f,255.0f));
    this->addChild(color);

    
    // オープニング画像の追加（スプライト生成）
    auto sprite = Sprite::create("OpeningBackground.png");
    // 画面中央への配置
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // レイヤーへスプライト追加
    this->addChild(sprite, 0);

    
    // 一定時間後にシーン切り替え
    // TODO:仮で1.5秒待つようにしているマジックナンバーを変数なり定数なりに修正
    this->scheduleOnce(schedule_selector(OpeningScene::transitionToTitleScene), 1.5f);
    
    
    return true;
}


// タイトルシーンへの遷移（スケジュール登録のために必要なfloat型の引数を入れている）
void OpeningScene::transitionToTitleScene (float delta){
    
    float duration = 1.0f;
    Scene* pScene = TransitionFlipX::create(duration, TitleScene::createScene());
    Director::getInstance()->replaceScene(pScene);

}
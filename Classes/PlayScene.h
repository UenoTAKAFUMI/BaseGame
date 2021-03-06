//
//  PlayScene.h
//  BaseGame02
//
//  Created by P on 2014/07/17.
//
//

#ifndef __BaseGame02__PlayScene__
#define __BaseGame02__PlayScene__

#include <iostream>

#include "cocos2d.h"

// プレイ中クラス
class PlayScene : public cocos2d::Layer {
public:
    // シーン生成静的関数
    //（この関数名がcreateだとCREATE_FUNCで生成される関数名とかぶってエラーになるっぽい）
    static cocos2d::Scene* createScene();
    
    // レイヤーの初期化処理（cocos2d::Layerクラスの仮想関数オーバーライド）
    virtual bool init();
    
    // OpeningLayer* OpeningLayer::create() 関数の自動生成（autorelease付きのインスタンスを返す）
    CREATE_FUNC(PlayScene);
    
private:
    void gameLogic();
    void addGameObject(float delta);
};


#endif /* defined(__BaseGame02__PlayScene__) */

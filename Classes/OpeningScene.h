//
//  OpeningScene.h
//  BaseGame02
//
//  Created by P on 2014/07/17.
//
//

#ifndef __BaseGame02__OpeningScene__
#define __BaseGame02__OpeningScene__

#include "cocos2d.h"

// オープニングクラス
class OpeningScene : public cocos2d::Layer {
public:
    // シーン生成静的関数
    //（この関数名がcreateだとCREATE_FUNCで生成される関数名とかぶってエラーになるっぽい）
    static cocos2d::Scene* createScene();
    
    // レイヤーの初期化処理（cocos2d::Layerクラスの仮想関数オーバーライド）
    virtual bool init();
    
    // OpeningLayer* OpeningLayer::create() 関数の自動生成（autorelease付きのインスタンスを返す）
    CREATE_FUNC(OpeningScene);


private:
    // タイトル画面遷移関数
    void transitionToTitleScene(float delta);

};



#endif /* defined(__BaseGame02__OpeningScene__) */

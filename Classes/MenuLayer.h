//
//  MenuLayer.h
//  BaseGame02
//
//  Created by P on 2014/07/17.
//
//

#ifndef __BaseGame02__MenuLayer__
#define __BaseGame02__MenuLayer__

#include "cocos2d.h"

class MenuLayer : public cocos2d::Layer {
public:
    // 初期処理
    // クラス生成関数（引数に呼び出し元のレイヤのアドレスを渡してもらう）
    static MenuLayer* create(cocos2d::Layer* const pFromLayer) ;
    virtual bool init();


private:
    // 呼び出し元レイヤ
    static cocos2d::Layer* mFromLayer;
    
    void addGameObject(float delta);
    
};



#endif /* defined(__BaseGame02__MenuLayer__) */

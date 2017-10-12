#pragma once

//! @file cSceneBase
//! @brief 全てのSceneに継承させる基盤クラスです
//! @note
//!       Scene切り替えは_isEnd で判断します
//! @date 2017-10-12
//! @author Taka Nomoto

class cSceneBase
{
public:
	//初期化
	virtual void setup() = 0;
	//Sceneの終了時のメモリ削除とか
	virtual void shutDown() = 0;
	virtual void update() = 0;
	//3D描画
	virtual void draw() = 0;
	//いるかわからんから一応
	virtual void draw2D() = 0;
	//サイズ変更時に呼びたいとき
	virtual void resize() = 0;

	bool isEnd() { return mIsEnd; }

protected:

	bool mIsEnd;
};
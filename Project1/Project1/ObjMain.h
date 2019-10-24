#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"


//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjMain : public CObj
{
	public:
		CObjMain(int map[10][10]);
		~CObjMain() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ド
	private:
		int m_map[10][10];   //マップ情報
		float m_scroll;   //左右スクロール用
};
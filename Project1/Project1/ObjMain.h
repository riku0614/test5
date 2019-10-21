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
		void Init();
		void Action();
		void Draw();
	private:
		int m_map[10][10];   //マップ情報
		void BlockDraw(float x, float y, RECT_F* dst, float c[]);
		
};
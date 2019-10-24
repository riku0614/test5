#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"


//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjMain : public CObj
{
	public:
		CObjMain(int map[100][100]);
		~CObjMain() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー
		void SetScrollX(float s) { m_scroll_x = s; }
		float GetScrollX() { return m_scroll_x; }
		void SetScrollY(float r) { m_scroll_y = r; }
		float GetScrollY() { return m_scroll_y; }
	private:
		int m_map[100][100];   //マップ情報
		float m_scroll_x;   //左右スクロール用
		float m_scroll_y;   //上下スクロール用
};
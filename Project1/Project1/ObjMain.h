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
		void SetScrollX(float s) { m_scroll_x = s; }//X方向のスクロール
		float GetScrollX() { return m_scroll_x; }
		void SetScrollY(float r) { m_scroll_y = r; }//Y方向へのスクロール
		float GetScrollY() { return m_scroll_y; }
		
		int m_map[100][100];//マップ情報ブロック数（X=１２個、Y=１０個）

		void BlockHit(
			float *x, float *y, bool scroll_on_x,bool scroll_on_y,
			bool *up, bool *down, bool *left, bool *right,
			float *vx, float *vy, int *bt
		);
	private:
		

		

		float m_scroll_x;   //左右スクロール用
		float m_scroll_y;   //上下スクロール用
};
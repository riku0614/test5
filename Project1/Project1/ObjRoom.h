#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjRoom : public CObj
{
public:
	CObjRoom(int map[25][25]);
	~CObjRoom() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetScrollX(float s) { m_scroll_x = s; }//X方向のスクロール
	float GetScrollX() { return m_scroll_x; }
	void SetScrollY(float r) { m_scroll_y = r; }//Y方向へのスクロール
	float GetScrollY() { return m_scroll_y; }
	int m_map[25][25];//マップ情報ブロック数（X=１２個、Y=１０個）



private:

	float m_scroll_x;   //左右スクロール用
	float m_scroll_y;   //上下スクロール用



};
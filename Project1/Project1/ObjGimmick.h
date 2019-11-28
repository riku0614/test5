#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjGimmick : public CObj
{
public:
	CObjGimmick(float x,float y) ;
	~CObjGimmick() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetY(int y) { pj = y; }
	void SetX(int x) { pi = x; }


private:
	int m_map[MAP_X][MAP_Y];//マップ情報
	int gx;	//アイテムのX位置保管用
	int gy; //アイテムのY位置保管用

	float m_vx; //オブジェクトの移動用ベクトルX
	float m_vy; //オブジェクトの移動用ベクトルY

	bool gimmick_flg;
	bool stop_flg;

	int pi;
	int pj;

	int h_count;
};

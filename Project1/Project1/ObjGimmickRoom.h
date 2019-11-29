#pragma once
#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjGimmickRoom : public CObj
{
public:
	CObjGimmickRoom(float x, float y);
	~CObjGimmickRoom() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetY(int y) { pj = y; }
	void SetX(int x) { pi = x; }


private:

	int r_map[ROOM_X][ROOM_Y];//マップ情報
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

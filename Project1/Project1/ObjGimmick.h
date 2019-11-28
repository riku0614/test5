#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjGimmick : public CObj
{
public:
	CObjGimmick(int map[MAP_X][MAP_Y]);
	~CObjGimmick() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー


private:
	int m_map[MAP_X][MAP_Y];//マップ情報
	int ix;	//アイテムのX位置保管用
	int iy; //アイテムのY位置保管用

	float m_px;  //オブジェクトの位置X
	float m_py;  //オブジェクトの位置Y
	float m_vx; //オブジェクトの移動用ベクトルX
	float m_vy; //オブジェクトの移動用ベクトルY

	bool gimmick_flg;
	bool stop_flg;

	int pi;
	int pj;

	int h_count;
};

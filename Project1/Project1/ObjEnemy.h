#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjEnemy : public CObj
{
public:
	CObjEnemy(float x, float y);;
	~CObjEnemy() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }
private:
	float m_px;  //オブジェクトの位置X
	float m_py;  //オブジェクトの位置Y
	float m_vx; //オブジェクトの移動用ベクトルX
	float m_vy; //オブジェクトの移動用ベクトルY
	float m_posture; //姿勢
	bool m_flg;//追従移動の管理用フラグ

		//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
};
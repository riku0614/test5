#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjHero : public CObj
{
public:
	CObjHero() {};
	~CObjHero() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	float m_px; //位置
	float m_py;
	float m_vx; //移動ベクトル
	float m_vy;
	float m_posture; //姿勢

};
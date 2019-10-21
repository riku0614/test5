//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHero::Init()
{
	m_px = 0.0f; //位置
	m_py = 0.0f;
	m_vx = 0.0f; //移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f; //右向き0.0ｆ　左向き1.0ｆ
}

//アクション
void CObjHero::Action()
{
	//移動ベクトルの破棄
	m_vy = 0.0f;

	//キーの入力方向
	if (Input::GetVKey('A') == true)
	{
		m_vx += 1.0f;
		m_posture = 1.0f;
	}
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= 1.0f;
		m_posture = 0.0f;
	}

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

}

void CObjHero::Draw()
{
	//描画カラー情報　R=RED　G=Green　B=Blue　A=Alpha（透過情報）
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f*m_posture) + m_px;
	dst.m_right = (64 - 64.0f*m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//1番目に登録したグラフィックをsrc.dst.cの情報を元に描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

}

//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjClickTitle.h"
#include "SceneMain.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjClickTitle::Init()
{
	m_yj = 0.0f;
	m_f = true;
}
//アクション
void CObjClickTitle::Action()
{
	
	//Enterを押したときの処理
	if (m_yj == 0.0f && Input::GetVKey(VK_RETURN))
	{
		Scene::SetScene(new CSceneMain);
	}
	
	//'W'keyを押した時の矢印処理
	if (Input::GetVKey('W') == true)
	{ 
		//m_fがtrueの場合...
		if (m_f == true)
		{
			//m_yjが0.0f(初期位置)だった場合の処理
			if (m_yj <= 0.0f)
			{
			m_yj = m_yj + 150.0f;
			}
			//m_yjが0以上の場合
			if (m_yj > 0.0f)
			{
			m_yj -= 50.0f;//3つ選択できるようのするため、+の値の三分の一の数を上方向（-y）に動かす
			}

			m_f = false;//m_fをfalseに→'W'を押し続けてもカーソルが動かないようにする
		}
	}

	//'S'keyを押した時の矢印処理
	else if (Input::GetVKey('S') == true)
	{
		//m_fがtrueの場合...
		if (m_f == true)
		{
			//m_yjが100.0f(最大値の位置)だった場合の処理
			if (m_yj >= 100.0f)
			{
				m_yj = m_yj - 150.0f;
			}
			//m_yjが100以下の場合
			if (m_yj <= 100.0f)
			{
				m_yj += 50.0f;//3つ選択できるようのするため、-の値の三分の一の数を上方向（+y）に動かす
			}

			m_f = false;//m_fをfalseに→'W','S'を押し続けてもカーソルが動かないようにする
		}
	}
	//'W','S'を一度押した処理
	else
	{
		m_f = true;//m_fをtrueに
	}
}

//ドロー
void CObjClickTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置設定
	dst.m_top = 335.0f + m_yj;
	dst.m_right = 450.0f;
	dst.m_left = dst.m_right + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	//描画設定
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//クリックする場所
	//ゲームを始める場所
	Font::StrDraw(L"最初から", 320, 350, 30, c);
	Font::StrDraw(L"続きから", 320, 400, 30, c);
	Font::StrDraw(L"ゲーム終了", 300, 450, 30, c);

}

//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/DrawFont.h"

#include "GameHead.h"
#include "ObjGameUI.h"
#include"ObjHero.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameUI::Init()
{
	item_flag = false;
	item_flag_2 = false;
	item_flag_3 = false;

	take_flag = false;
	take_flag_2 = false;
	take_flag_3 = false;


	m_id = 0;
	h_id = 0;
}

//アクション
void CObjGameUI::Action()
{
	item_flag = true;//アイテムを使うためのフラグ,主人公にて使用
	item_flag_2 = true;
	item_flag_3 = true;

		//主人公のアイテムを使ったフラグを持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	
	m_id = hero->GetKeyID();
	h_id = hero->GatHealID();
	
	//アイテムを使ったらアイテムを消す処理
	if (hero->SetItemflag() == true) //アイテム欄の1番目
	{
		hero->SetFlug(false);
		m_id = 0;
	}

	
	
	if (hero->SetItemflag_2() == true) //アイテム欄の2番目
	{
		hero->SetFlug_2(false);
		h_id = 0;
	}
	/*
	if (hero->SetItemflag_3() == true) //アイテム欄の3番目
	{
		hero->SetFlug_3(false);
		m_id = 0;
	}*/
}

//ドロー
void CObjGameUI::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };


	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 680.0f;

	//表示位置設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + 800.0f;
	dst.m_bottom = dst.m_top + 600.0f;
	
	//描画設定
	Draw::Draw(17, &src, &dst, c, 0.0f);

	//主人公のアイテムと当たったフラグを持ってくる
	CObjHero* HERO = (CObjHero*)Objs::GetObj(OBJ_HERO);

	/*ダメージエフェクト*/
	if (HERO->action_flag()== true && HERO->m_hero_life <= 20)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 680.0f;

		//表示位置設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 800.0f;
		dst.m_bottom = dst.m_top + 600.0f;
		
		//描画設定

		Draw::Draw(22, &src, &dst, c, 0.0f);
	}
	if (HERO->action_flag2() == true && HERO->m_hero_life <= 10)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 680.0f;

		//表示位置設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 800.0f;
		dst.m_bottom = dst.m_top + 600.0f;

		//描画設定

		Draw::Draw(23, &src, &dst, c, 0.0f);
	}
	
	//切り取り位置の設定
	src.m_top = 19.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 38.0f;

	//表示位置設定
	dst.m_top = 559.0f;
	dst.m_left = 686.0f;
	dst.m_right = dst.m_left + 64.0f + 50.0f;
	dst.m_bottom = dst.m_top + 21.0f + 20.0f;

	//描画設定
	Draw::Draw(6, &src, &dst, c, 0.0f);

	
	//主人公のアイテムと当たったフラグを持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	

	//アイテムの表示（1番）
	if (hero->Getflag() == true)
	{
		RECT_F src;	//描画元切り取り位置
		RECT_F dst;	//描画先表示位置

		src.m_top = 10.0f;
		src.m_left = 10.0f;
		src.m_right = 40.0f;
		src.m_bottom = 40.0f;

	
		//表示位置設定
		dst.m_top = 562.0f;
		dst.m_left = 686.0f;
		dst.m_right = dst.m_left + 40.0f;
		dst.m_bottom = dst.m_top + 45.0f;
		
		//描画設定
		Draw::Draw(9, &src, &dst, c, 0.0f);

		take_flag = true; //1番目のアイテムを持っているかどうかのフラグをtrueにする→主人公にてアイテムを使用できるかどうかの判定


	}

	//2番のアイテム表示
	if (hero->Getflag_2() == true)
	{
		RECT_F src;	//描画元切り取り位置
		RECT_F dst;	//描画先表示位置

		src.m_top = 32.0f;
		src.m_left = 32.0f;
		src.m_right = 224.0f;
		src.m_bottom = 224.0f;


		//表示位置設定
		dst.m_top = 559.0f;
		dst.m_left = 725.0f;
		dst.m_right = dst.m_left + 38.0f;
		dst.m_bottom = dst.m_top + 45.0f;

		//描画設定
		Draw::Draw(21, &src, &dst, c, 0.0f);

		take_flag_2 = true; //2番目のアイテムを持っているかどうかのフラグをtrueにする→主人公にてアイテムを使用できるかどうかの判定
	}
	
	//3番のアイテム表示
	if (hero->Getflag_3() == true)
	{
		RECT_F src;	//描画元切り取り位置
		RECT_F dst;	//描画先表示位置

		src.m_top = 0.0f;
		src.m_left = 100.0f;
		src.m_right = 400.0f;
		src.m_bottom = 512.0f;


		//表示位置設定
		dst.m_top = 559.0f;
		dst.m_left = 762.0f;
		dst.m_right = dst.m_left + 38.0f;
		dst.m_bottom = dst.m_top + 45.0f;

		//描画設定
		Draw::Draw(26, &src, &dst, c, 0.0f);

		take_flag_3 = true; //3番目のアイテムを持っているかどうかのフラグをtrueにする→主人公にてアイテムを使用できるかどうかの判定
		
	}
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (main->MapChangeData() == 0)
	{
		//階の表示
		Font::StrDraw(L"8階", 730, 10, 30, c);
	}
	else if (main->MapChangeData() == 1)
	{
		//階の表示
		Font::StrDraw(L"1階", 730, 10, 30, c);
	}
	
}
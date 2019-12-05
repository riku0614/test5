#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_TITLE,
	OBJ_CLICK_TITLE,
	OBJ_HERO,
	OBJ_ENEMY,
	OBJ_MAIN,
	OBJ_GAMEOVER,
	OBJ_GAMECLEAR,
	OBJ_GAME_UI,
	OBJ_ITEM,
	OBJ_MENU,
	OBJ_GIMMICK,
	OBJ_GIMMICK2,
	OBJ_GIMMICK3,
	OBJ_GIMMICK4,
	OBJ_GIMMICK5,
	OBJ_GIMMICK6,
	OBJ_GIMMICK7,
	OBJ_GIMMICK8,
	OBJ_HEAL,

	//OBJ_CHAR,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--
enum ITEM_ID
{
	ITEM_KEY,
	CHAR_HERO,
	CHAR_ENEMY,
	ITEM_HEAL,
};


//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "ObjTitle.h"
#include "ObjHero.h"
#include "ObjClickTitle.h"
#include "ObjMain.h"
#include "ObjEnemy.h"
#include "ObjGameUI.h"
#include "ObjGameOver.h"
#include "ObjGameClear.h"
#include "ObjGameUI.h"
#include "ObjItem.h"
#include "ObjMenu.h"
#include "ObjGimmick.h"
#include "ObjGimmick2.h"
#include "ObjGimmick3.h"
#include "ObjGimmick4.h"
#include "ObjGimmick5.h"
#include "ObjGimmick6.h"
#include "ObjGimmick7.h"
#include "ObjGimmick8.h"
#include "objheal.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"
#include "SceneGameUI.h"
#include "SceneMenu.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------
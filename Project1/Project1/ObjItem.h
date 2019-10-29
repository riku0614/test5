#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjItem : public CObj
{
public:
	CObjItem(int map[100][100]);
	~CObjItem() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	int m_map[100][100];//マップ情報
	//int ix;	//アイテムのX位置保管用
	//int iy; //アイテムのY位置保管用
};

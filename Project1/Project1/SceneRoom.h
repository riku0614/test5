#pragma once
//使用するヘッダーファイル
#include"GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームタイトル
class CSceneRoom :public CScene
{
public:
	CSceneRoom();
	~CSceneRoom();
	void InitScene();	//ゲームタイトルの初期化メソッド
	void Scene();		//ゲームタイトルの実行中メソッド
	void Draw();
private:
	int m_map[25][25];
};
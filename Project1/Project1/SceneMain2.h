#pragma once
//使用するヘッダー
#include "GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームメイン
class CSceneMain2 : public CScene
{
public:
	CSceneMain2();
	~CSceneMain2();
	void InitScene();//ゲームメイン初期化メソッド
	void Scene();//ゲームメイン実行中メソッド
private:
};
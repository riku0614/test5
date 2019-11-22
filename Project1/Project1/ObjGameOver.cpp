//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGameOver.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameOver::Init()
{
	GO_time = 0;
	Title_flag = false;
}

//アクション
void CObjGameOver::Action()
{
	GO_time++;//タイムの経過によってタイトルに移行するため、後置インクリメントで値を増やしていく

	//タイムの経過とは別に、'Z'キーを押した場合にタイトルに移行するようにする
	if (Input::GetVKey('Z') == true)
	{
		Title_flag = true;	//タイトルに移行するためのフラグをオンに
	}
}

//ドロー
void CObjGameOver::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"GAME OVER", 260, 250, 60, c);

	if (Title_flag == true)
	{
		Scene::SetScene(new CSceneTitle);
	}
	else if (GO_time > 300)
	{
		Scene::SetScene(new CSceneTitle);
	}
}
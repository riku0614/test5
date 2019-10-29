//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjMenu.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMenu::Init()
{

}

//アクション
void CObjMenu::Action()
{
	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle);
	}

	if (Input::GetVKey('E') == true)
	{
		Scene::SetScene(new CSceneMain);
	}


}

//ドロー
void CObjMenu::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"Enterキーでタイトルへ戻る", 200, 250, 32, c);
}
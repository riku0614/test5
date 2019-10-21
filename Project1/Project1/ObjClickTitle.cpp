//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjClickTitle.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjClickTitle::Init()
{

}

//アクション
void CObjClickTitle::Action()
{

}

//ドロー
void CObjClickTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	//クリックする場所
	//ゲームを始める場所
	Font::StrDraw(L"最初から", );

}

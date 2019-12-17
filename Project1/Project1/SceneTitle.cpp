//STL�f�o�b�O�@�\���I�t��
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"
#include "GameL/DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "ObjClickTitle.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneTitle::CSceneTitle()
{

}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//�Q�[�����C�����������\�b�h
void CSceneTitle::InitScene()
{
	//���y���̓ǂݍ���
	Audio::LoadAudio(0, L"0�^�C�g��BGM.wav", SOUND_TYPE::BACK_MUSIC);

	//���y�X�^�[�g
	Audio::Start(0);

	//�o�͂����镶���̃O���t�B�b�N�쐬
	Font::SetStrTex(L"���q");
	Font::SetStrTex(L"�`�J�C�G�`");
	Font::SetStrTex(L"�ŏ�����");

	//���ǉ�
	Draw::LoadImageW(L"�J�[�\��.png", 0, TEX_SIZE_512);
	Draw::LoadImageW(L"�^�C�g�����.png", 1, TEX_SIZE_1024);

	//�N���b�N�^�C�g���I�u�W�F�N�g�쐬
	CObjClickTitle* objb = new CObjClickTitle();	//�N���b�N�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(objb, OBJ_CLICK_TITLE, 11);		//�^�C�g���I�u�W�F�N�g�o�^


}

//�Q�[�����C�����s�����\�b�h
void CSceneTitle::Scene()
{

}
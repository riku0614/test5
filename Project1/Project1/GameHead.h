#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
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

	//OBJ_CHAR,
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
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
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
enum ITEM_ID
{
	ITEM_KEY,
	CHAR_HERO,
	CHAR_ENEMY,
};


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjTitle.h"
#include "ObjHero.h"
#include "ObjClickTitle.h"
#include "ObjMain.h"
#include "ObjEnemy.h"
#include "ObjGameUI.h"
#include "ObjGameOver.h"
#include "ObjGameClear.h"
#include "ObjGameUI.h"
//#include "ObjChar.h"
#include "ObjItem.h"
#include "ObjMenu.h"
#include "ObjGimmick.h"
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"
#include "SceneGameUI.h"
#include "SceneMenu.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------
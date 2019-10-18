#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_TITLE,
	OBJ_MAIN,
	OBJ_CHAR,
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
enum CHARACTER_BLOCK_ID
{
	CHAR_BLOCK_ONLY = 99, //��Q��
    CHAR_BLOCK_FREE = 0,  //�u���b�N����
	CHAR_MONK,            //�L�����N�^�[�u���b�N�@�m��
	CHAR_DRAGON,          //�L�����N�^�[�u���b�N�@�h���S��
	CHAR_VALKYRIE,        //�L�����N�^�[�u���b�N�@���@���L���[
	CHAR_DRAGONQUEEN,     //�L�����N�^�[�u���b�N�@�h���S���N�C�[��
	CHAR_SOLDIER,         //�L�����N�^�[�u���b�N�@�\���W���[
	CHAR_GENERAL,         //�L�����N�^�[�u���b�N�@���R
};


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjTitle.h"
#include "ObjMain.h"
#include "ObjChar.h"

//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneTitle.h"
#include "SceneMain.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------
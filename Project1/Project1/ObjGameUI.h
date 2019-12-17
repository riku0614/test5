#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define Status (1)

//�I�u�W�F�N�g�F���C��
class CObjGameUI : public CObj
{
public:
	CObjGameUI() {};
	~CObjGameUI() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	bool GetItemflag() { return item_flag; }
	bool GetItemflag_2() { return item_flag_2; }
	bool GetItemflag_3() { return item_flag_3; }

	bool takeItemflag() { return take_flag; }
	bool takeItemflag_2() { return take_flag_2; }
	bool takeItemflag_3() { return take_flag_3; }

	void Settakeflag(bool i) { take_flag = i; }		//��l���ɓn���A�A�C�e���������Ă��邩�ǂ����̃t���O�i1�ԗp�j�A���g������܂�
	void Settakeflag_2(bool i) { take_flag_2 = i; } //2�ԗp
	void Settakeflag_3(bool i) { take_flag_3 = i; } //3�ԗp
	void SetID(int id) { b_id = id; }
	
private:

	bool item_flag;		//��l���ɂăA�C�e��1�Ԃ��g�p���邽�߂̃g���K�[�t���O
	bool item_flag_2;	//2��
	bool item_flag_3;	//3��

	bool take_flag;		//��l�����A�C�e���i1�ԁj�������Ă��邩�𔻒f���邽�߂̃t���O
	bool take_flag_2;	//2��
	bool take_flag_3;	//3��


	int m_id;	//key�p�ϐ�
	int h_id;	//Heal�p�ϐ�
	int b_id;	//bar�p�ϐ�
};
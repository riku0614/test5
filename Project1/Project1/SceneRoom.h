#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL/SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�Q�[���^�C�g��
class CSceneRoom :public CScene
{
public:
	CSceneRoom();
	~CSceneRoom();
	void InitScene();	//�Q�[���^�C�g���̏��������\�b�h
	void Scene();		//�Q�[���^�C�g���̎��s�����\�b�h
	void Draw();
private:
	int m_map[25][25];
};
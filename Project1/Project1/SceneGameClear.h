#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�Q�[�����C��
class CSceneGameClear : public CScene
{
public:
	CSceneGameClear();
	~CSceneGameClear();
	void InitScene();//�Q�[�����C�����������\�b�h
	void Scene();//�Q�[�����C�����s�����\�b�h

	bool Ending1() { return ED; }
private:
	int m_time;	//�e���b�v�o���p�i����j
	bool ED;	//ED1�o���p
};
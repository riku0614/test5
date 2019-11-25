//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjItem.h"
#include "GameL/HitBoxManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjItem::CObjItem(int map[75][75])
{
	memcpy(m_map, map, sizeof(int)*(75 * 75));
}

//�C�j�V�����C�Y
void CObjItem::Init()
{
	//�ϐ�������
	//ix = 0;
	//iy = 0;

	//���C���̈ʒu���擾
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	for (int i = 0; i < 75; i++)
	{
		for (int j = 0; j < 75; j++)
		{
			if (m_map[i][j] == 4)
			{

				//�����蔻��phitbox���쐬
				Hits::SetHitBox(this, j-main->GetScrollY(), i-main->GetScrollX(), 64, 64, ELEMENT_ITEM, OBJ_ITEM, 1);
			}
		}
	}

}

//�A�N�V����
void CObjItem::Action()
{
	


	
}

//�h���[
void CObjItem::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�`��؂���ʒu
	src.m_top = 17.0f;
	src.m_left = 20.0f;
	src.m_right = src.m_left + 25.0f;
	src.m_bottom = src.m_top + 30.0f;

	//���C���̈ʒu���擾
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	float hx = main->GetScrollX();
	float hy = main->GetScrollY();

	for (int i = 0; i < 75; i++)
	{
		for (int j = 0; j < 75; j++)
		{
			if (m_map[i][j] == 4)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f + hy;
				dst.m_left = j * 64.0f + hx;
				dst.m_right = dst.m_left + 20.0;
				dst.m_bottom = dst.m_top + 20.0;

				Draw::Draw(8, &src, &dst, c, 0.0f);
			}
		}
	}
	
}
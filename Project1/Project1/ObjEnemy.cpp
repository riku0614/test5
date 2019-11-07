//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "SceneMain.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;




CObjEnemy::CObjEnemy(int map[100][100])
{
	memcpy(m_map, map, sizeof(int)*(100 * 100));
}
//�C�j�V�����C�Y
void CObjEnemy::Init()
{

	m_vx = 1.0f;
	m_vy = 1.0f;
	m_ex = 64.0f; //�ʒu
	m_ey = 64*3.0f;

	m_flg = 0;
	
	
	//block�Ƃ̏Փˊm�F�p

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	
	//��l���̈ʒu���擾
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_ex, m_ey, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);


}

//�A�N�V����
void CObjEnemy::Action()
{
	
	int km_map[100][100];
	
	if(m_hit_left==true)
	{
		m_flg=1;
	}
	else if (m_hit_down == true)
	{
		m_flg=2;
	}
	else if (m_hit_right == true)
	{
		m_flg=3;
	}
	else if (m_hit_up == true)
	{
		m_flg = 0;
	}
	

	if (m_flg == 0)
	{
		m_ex += 5.0f*2;
		
		
	}
    else if (m_flg == 1)
	{
		m_ey += 5.0f*2;
	}
	else if (m_flg == 2)
	{
		m_ex -= 5.0f*2;
	}
	else if (m_flg == 3)
	{
		m_ey -= 5.0f*2;
	}
	
	//�����ړ��ɂ��block����
	bool b;
	float pxx, pyy, r;
	CObjMain* pbb = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	if (pbb->GetScrollX() > 0)
		pbb->SetScrollX(0);
	if (pbb->GetScrollY() > 0)
		pbb->SetScrollY(0);
	//�ړ�������ray���΂�
	float vx;
	
	if (m_vx > 0)
		vx = 500 - pbb->GetScrollX();
	else
		vx = 0 - pbb->GetScrollX();

	//ray����
	b = pbb->HeroBlockCrossPoint(m_ex - pbb->GetScrollX() + 64, m_ey - pbb->GetScrollY() + 64, vx, 0.0f, &pxx, &pyy, &r);

	if (b == true)
	{
		//��_�擾
		px = pxx + pbb->GetScrollX();
		py = pyy - pbb->GetScrollY();

		float aa = (m_ex)-px;//A�i��_����l���̈ʒu�j�x�N�g��
		float bb = (m_ex + m_vx) - px;//B�i��_����l���̈ړ���ʒu�j�x�N�g��

									  //��l���̕����I�t�Z�b�g
		if (vx > 0)
			px += -64;
		else
			px += 2;

		//A��B���t�������Ă���i��l�����ړ���̕ǂ��z���Ă���j
		if (aa*bb < 0)
		{
			//�ړ��x�N�g�����i��_����l���̈ʒu�j�x�N�g���ɂ���
			m_vx = px - m_ex;
		}
	}
	else
	{
		px = 0.0f;
		py = 0.0f;
	}

	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;
	//�u���b�N�̓����蔻����s
	CObjMain* pb = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	pb->BlockHit(&m_ex, &m_ey, false, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d);

	CObjMain* scroll = (CObjMain*)Objs::GetObj(OBJ_MAIN);
    //���g��hitbox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//hitbox�̈ʒu�̕ύX
	hit->SetPos(m_ex + scroll->GetScrollX(), m_ey + scroll->GetScrollY());

	
}

//�h���[
void CObjEnemy::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	CObjMain* scroll = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_ey+scroll->GetScrollY();
	dst.m_left = (64.0) + m_ex+scroll->GetScrollX();
	dst.m_right = (64 - 64.0f)+m_ex+scroll->GetScrollX();
	dst.m_bottom = 64.0f + m_ey+scroll->GetScrollY();

	//3�Ԗڂɓo�^�����O���t�B�b�N��src.dst.c�̏������ɕ`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
}
/*�}�b�v���̎擾���]�b�g
�����P�@�F�v�f�ԍ�X
�����Q�@�F�v�f�ԍ�Y
�߂�l�@�F�v�f��Ԃ��B�v�f�ԍ����z��O�̏ꍇ-1��Ԃ�
�w�肵���v�f�ԍ���m_map��Ԃ�*/
int CObjEnemy::GetMap(int x, int y)
{

	//x.y����O�I�Ȓl�̏ꍇ�A���s(�|1)��Ԃ�
	if (x < MAP_MIN)return -1;
	if (y < MAP_MIN)return -1;
	if (x >= 100)return 1;
	if (y >= 100)return 1;

	//�v�f��Ԃ�
	return m_map[y][x];
}

/*�}�b�v��Block��ID�����郁�]�b�g
�����P�@int  x �F �v�f�ԍ�X
�����Q�@int  y �F �v�f�ԍ�Y
�����R�@int id �F �v�f�ɓ����ID
�w�肵���v�f�ԍ���map��ID������*/
void CObjEnemy::SetMap(int x, int y, int id)
{
	//�I�[�o�[�t���[�ɂ���O����
	if (x < MAP_MIN)   return;
	if (y < MAP_MIN)   return;
	if (x >= 100) return;
	if (y >= 100) return;

	//ID��Map�ɓ����
	m_map[y][x] = id;

	return;

}

/*�}�b�v�I�[�o�[�t���[�`�F�b�N���]�b�g
�����P�@int x :�}�b�v�v�f�ԍ�x
�����Q�@int y :�}�b�v�v�f�ԍ�y
�߂�l�@bool �̈�O��false�@�̈����true
�v�f�ԍ��̃I�[�o�[�t���[�`�F�b�N�����܂��B*/
bool CObjEnemy::OverFlowCheck(int x, int y)
{
	if (x < MAP_MIN)         return false;
	if (y < MAP_MIN)         return false;
	if (x >= 100)         return false;
	if (y >= 100)         return false;

	return true;

}

/*�T���o�b�t�@�`�F�b�N�p���]�b�g
�����P�@int x :�}�b�v�v�f�ԍ�x
�߂�l�@�f�[�^������ꏊ*/
int CObjEnemy::BufferCheck(XY b[])
{
	for (int i = 0; i < BUFFER_MAX; i++)
	{
		if (b[i].x != BUFFER_NO_DATA && b[i].x != BUFFER_DELETE_DATA)
			return i;
	}
	return -1;


}

/*4�����T�[�`���o�^���]�b�g
�����P�@int  set_x �@�@�@�@�@�F�����o����X�ʒu
�����Q�@int  set_y �@�@�@�@�@�F�����o����Y�ʒu
�����R�@int[][] c_map  �@�@�@�F�L�����N�^�[�u���b�N�}�b�v
�����S  int[][] km_map �@�@�@�F����������}�b�v
�����T�@XY[] buffer    �@�@�@�F�o�b�t�@
�����U�@int* buffer_count    �F�o�b�t�@�J�E���g
�߂�l�@�@�F�Ȃ�
�����o���ʒu����S�����̗v�f�𒲂ׂċ�����o�^����*/
void CObjEnemy::EveryDirectionSearchSet
(int set_x, int set_y,
	int c_map[100][100], int km_map[100][100],
	XY buffer[], int *buffer_count
)
{
	//���������p�z��i�㉺���E�j
	const XY search[SEARCH_MAX] = { { 1,0 },{ -1,0 },{ 0,-1 },{ 0,1 } };

	//�L�����N�^�[ID�擾�@����ID�̂݌�������
	int c_id = 2;

	//�S�[���̏㉺���E�̔z����������ē���ID�����邩�ǂ������ׂ�
	int count = BufferCheck(buffer);
	for (int i = 0; i < SEARCH_MAX; i++)
	{
		//�o�b�t�@���ʒu���猟�������̗v�f�ԍ����o��
		int x = search[i].x + buffer[count].x;
		int y = search[i].y + buffer[count].y;

		//�I�[�o�[�t���[�`�F�b�N
		if (OverFlowCheck(x, y) == false)
			continue;

		//�אڃm�[�h����������o�b�t�@�E�����n�̍X�V
		if (c_map[y][x] == c_id)
		{
			if (km_map[y][x] > km_map[set_y][set_x] + SEARCH_MAP_NEXT)
			{
				km_map[y][x] = km_map[set_y][set_x] + SEARCH_MAP_NEXT;
				(*buffer_count)++;
				buffer[*buffer_count].x = x;
				buffer[*buffer_count].y = y;


			}
		}

	}

	//���������̂Ńf�[�^��j���ŏ㏑��
	buffer[count].x = BUFFER_DELETE_DATA;
	buffer[count].y = BUFFER_DELETE_DATA;
	return;
}

/*�_�C�N�X�g���@���]�b�g
�����P�@int[][] c_map  �@�@�@�F�L�����N�^�[�u���b�N�p�}�b�v�z��
�����Q  int[][] km_map �@�@�@�F����������}�b�v�z��
�����R�@int    goal_x�@�@�@�@�F�S�[���m�[�h�̗v�f�ԍ�X
�����S�@int    goal_y    �@�@�F�S�[���m�[�h�̗v�f�ԍ�Y
�߂�l�@int    :�T����*/
int CObjEnemy::Dijkstras(int c_map[100][100], int km_map[100][100],
	int goal_x, int goal_y)
{
	//�o�b�t�@�J�E���g�p
	int buffer_count = 0;
	int point = 0;

	//�T���o�b�t�@
	XY buffer[BUFFER_MAX];
	memset(buffer, 0xFF, sizeof(XY) * BUFFER_MAX);

	//�I�[�o�[�t���[�ƃS�[���u���b�N�ɂȂ�Ȃ�ID��O����
	if (OverFlowCheck(goal_x, goal_y) == false) return 0;
	if (c_map[goal_y][goal_x] == 9) return 0;
	if (c_map[goal_y][goal_x] == 3) return 0;

	//�S�[���̐ݒu
	int c_id = c_map[goal_y][goal_x];//�L�����N�^�[ID�擾�@����ID�̂݌�������
	km_map[goal_y][goal_x] = 0;
	buffer[buffer_count].x = goal_x;//�S�[���m�[�h�ʒu���o�b�t�@�o�^
	buffer[buffer_count].y = goal_y;

	//��������ʒu�̏㉺���E�̔z����������ē���ID�����邩�ǂ������ׂ�
	int search_count = 0;//���������m�[�h��
	do
	{
		EveryDirectionSearchSet(buffer[point].x, buffer[point].y, c_map, km_map, buffer, &buffer_count);
		point = BufferCheck(buffer);
		search_count++;
	} while (point != BUFFER_NO_DATA);

	return search_count;
}


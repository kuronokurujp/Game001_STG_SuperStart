/**
 */
#ifndef __LASERBULLET_H__
#define __LASERBULLET_H__

#include "InterfaceBullet.h"
#include "common/Common.h"

class C_LaserBullet : public I_InterfaceBullet
{
public:
    C_LaserBullet();
    virtual ~C_LaserBullet();

    void init();
    void release();
    void update();
    void draw() const;

    /*
            @brief	�łp�x
            @param	�p�x�w��
    */
    void setBulletAngle(float i_angle);

    /*
            @brief	�e������
            @param	i_spos	:	�e�̏������W
    */
    void shot(const D3DXVECTOR3& i_spos);

    /*
            @brief	��������
            @param	i_cpos		:	�I�u�W�F�N�g�̒��S���W
            @param	i_size_x	:	���T�C�Y
            @param	i_size_y	:	�c�T�C�Y
            @return	�Փ�[true]	/	��Փ�[false]
    */
    bool isIntersected(const D3DXVECTOR3& i_cpos, float i_size_x, float i_size_y);

private:
    // �n�_�̍��W
    D3DXVECTOR3 m_pos;
    D3DXVECTOR3 m_dir;
    // ���[�U�[�̒���
    float m_length;
    bool mb_shot;
};

#endif  // __LASERBULLET_H__

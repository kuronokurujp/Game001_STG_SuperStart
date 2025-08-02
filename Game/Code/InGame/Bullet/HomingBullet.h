/**
 *	@file 	HomingBullet.h
 */
#ifndef _HOMINGBULLET_H__
#define _HOMINGBULLET_H__

#include "InterfaceBullet.h"

class C_HomingBullet : public I_InterfaceBullet
{
public:
    C_HomingBullet();
    virtual ~C_HomingBullet();

    void init();
    void release();
    void update();
    void draw() const;

    bool isShot() const { return mb_shot; }
    void SetShotFlg(const bool in_Flg) { mb_shot = in_Flg; }

    /*
            @brief	�łp�x
            @param	�p�x�w��
    */
    void setBulletAngle(float i_angle);

    /*
            @brief	�z�[�~���O�Ώۂ̍��W�w��
            @param	ia_target_pos	:	�Ώۍ��W
    */
    void setTargetPos(const D3DXVECTOR3& i_target_pos);
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

    //	�f�o�b�O�ݒ�p
    static void setDebug(int in_DebugSceneHandle);

private:
    D3DXVECTOR3* mp_tree_pos;
    D3DXVECTOR3 m_set_dir, m_dir;
    D3DXVECTOR3 m_target_pos;

    bool mb_shot;
    bool m_bHoming;
};

#endif  // HOMINGBULLET_H__

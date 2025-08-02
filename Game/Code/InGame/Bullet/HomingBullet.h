/**
 *	@file 	HomingBullet.h
 *	@brief	指定した座標に誘導弾
 *	@author	yuto uchida
 *	@data   2011-01-25
 *	@note
 *
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
            @brief	打つ角度
            @param	角度指定
    */
    void setBulletAngle(float i_angle);

    /*
            @brief	ホーミング対象の座標指定
            @param	ia_target_pos	:	対象座標
    */
    void setTargetPos(const D3DXVECTOR3& i_target_pos);
    /*
            @brief	弾を撃つ
            @param	i_spos	:	弾の初期座標
    */
    void shot(const D3DXVECTOR3& i_spos);

    /*
            @brief	交差判定
            @param	i_cpos		:	オブジェクトの中心座標
            @param	i_size_x	:	横サイズ
            @param	i_size_y	:	縦サイズ
            @return	衝突[true]	/	非衝突[false]
    */
    bool isIntersected(const D3DXVECTOR3& i_cpos, float i_size_x, float i_size_y);

    //	デバッグ設定用
    static void setDebug(int in_DebugSceneHandle);

private:
    D3DXVECTOR3* mp_tree_pos;
    D3DXVECTOR3 m_set_dir, m_dir;
    D3DXVECTOR3 m_target_pos;

    bool mb_shot;
    bool m_bHoming;
};

#endif  // HOMINGBULLET_H__

//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		前景・後景処理
//																BackFore.h
//=============================================================================

#pragma once

//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//ヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"

//======================================================================
// バッククラウンド　プロシージャクラス
//
// (注意)基本プロシージャクラスは継承していない
//
//======================================================================
class CBackProc
{
protected:
public:
};
//======================================================================
// フォアクラウンド　プロシージャクラス
//
// (注意)基本プロシージャクラスは継承していない
//
//======================================================================
class CForeProc
{
protected:
	CGameMain*		m_pGMain;
	CSprite*		m_pForegrd;
	CSprite*        ST;          // M.S 強化武器獲得のスプライト
	CSprite*        m_pSchest;   // M.S 残機のハートのスプライト
	CSprite*        m_pCMp3;      // M.S MPの栗(1つ)のスプライト
	CSprite*        m_pCMp2;      // M.S MPの栗(2つ)のスプライト
	CSprite*        m_pCMp1;      // M.S MPの栗(3つ)のスプライト
public:
	void Update();
	CForeProc(CGameMain* pGMain);	// コンストラクタ
	~CForeProc();
};
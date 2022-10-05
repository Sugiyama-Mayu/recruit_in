//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		プレイキャラクターの処理
//																Playchar.h
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
// プレイキャラクター　オブジェクトクラス
class CPcObj : public CBaseObj
{
protected:
public:
	void Update() override;
	int  m_nShotWait;
	void ChangeStatePC();
	// コンストラクタ（オブジェクトの初期化）
	CPcObj(CGameMain* pGMain);
	~CPcObj();
};
//======================================================================
// プレイキャラクター　プロシージャクラス
class CPcProc : public CBaseProc
{
protected:
public:
	// アクセス関数
	CPcObj*			    GetPcObjPtr() { return m_pPcObj; }
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num; }
	int                 m_nPcNum; // 残機
	int                 m_nMaxPcNum; // Max残機
	CPcObj*			m_pPcObj;

	CPcProc(CGameMain* pGMain);	// コンストラクタ
	~CPcProc() { ; }
};
//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//      武器の処理
//																Weapon.h
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

#define  WEAPON_SHOT_MAX  200
#define  WEAPON_ESHOT_MAX 200
//======================================================================
// (PC)武器・ショット　オブジェクトクラス
class CWeaponShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CWeaponShotObj(CGameMain* pGMain);
	~CWeaponShotObj();
};
//======================================================================
// (PC)武器・ショット　プロシージャクラス
class CWeaponShotProc : public CBaseProc
{
public:
	BOOL Start( VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponShotProc() { ; }
};
//======================================================================
// M.S (敵)武器・ショット　オブジェクトクラス
class CEWeaponShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	bool bRet;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;
	
	// コンストラクタ
	CEWeaponShotObj(CGameMain* pGMain);
	~CEWeaponShotObj();
};
//======================================================================
// M.S (敵)武器・ショット　プロシージャクラス
class CEWeaponShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CEWeaponShotProc(CGameMain* pGMain);	// コンストラクタ
	~CEWeaponShotProc() { ; }
};
//======================================================================
// 武器全体のメインプロシージャクラス
//======================================================================
class CWeaponProc : public CBaseProc
{
public:
	CWeaponShotProc*	m_pWeaponShotProc;  // PCの武器プロシージャ
	CEWeaponShotProc*   m_pEWeaponShotProc; // M.S 敵の武器プロシージャ

public:
	CWeaponProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponProc() { ; }
};

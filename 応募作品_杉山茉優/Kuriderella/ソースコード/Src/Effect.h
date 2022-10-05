//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		映像効果の処理
//																Effect.h
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

// M.S 各アイテムの追加
#define  ITEMRESQUE   1           // M.S 回復
#define  ITEMDOOR     2           // M.S ドア
#define  ITEMSILVER   3           // M.S 銀箔
#define  ITEMGOLD     4           // M.S 金箔
#define  ITEMVISION   5           // M.S 幻の砂糖
#define  ITEMOSETI    6           // M.S おせちドア
#define  ITEMST       7           // M.S 強化武器

#define  ITEM_MAX  50
#define  EFFECT_BOM_MAX  50
//======================================================================
// 映像効果・爆発　オブジェクトクラス
class CEffectBomObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2) override;

	void Update() override;

	// コンストラクタ
	CEffectBomObj(CGameMain* pGMain);
	~CEffectBomObj();

};
//======================================================================
// 映像効果・爆発　プロシージャクラス
class CEffectBomProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2);

	CEffectBomProc(CGameMain* pGMain);	// コンストラクタ
	~CEffectBomProc() { ; }	// デストラクタ

};
//=================================================================================================================
//======================================================================
// アイテム　オブジェクトクラス
class CItemObj : public CBaseObj
{
protected:
	//CDirectInput* pDI = m_pDI;
	CDirectInput* pDI = m_pGMain->m_pDI;
	int doorN, secondN, keyN = 0;
	
	
public:

	BOOL Start(VECTOR2, DWORD) override;
	void Update() override;

	// コンストラクタ
	CItemObj(CGameMain* pGMain);
	~CItemObj();

};
//======================================================================
// アイテム　プロシージャクラス
class CItemProc : public CBaseProc
{
public:
	// M.S 各アイテムの発生関数
	void RaiseResque(VECTOR2 vPos);  // M.S 回復
	void RaiseDoor(VECTOR2 vPos);    // M.S ドア
	void RaiseSilver(VECTOR2 vPos);  // M.S 銀箔
	void RaiseGold(VECTOR2 vPos);    // M.S 金箔
	void RaiseVision(VECTOR2 vPos);  // M.S 幻の砂糖
	void RaiseOseti(VECTOR2 vPos);   // M.S おせちドア
	void RaiseSt(VECTOR2 vPos);      // M.S 強化武器

	void Update() override;
	CItemProc(CGameMain* pGMain);	// コンストラクタ
	~CItemProc() { ; }	// デストラクタ
};
//=================================================================================================================
//======================================================================
// 映像効果　プロシージャクラス
class CEffectProc : public CBaseProc
{
public:
	CEffectBomProc*		m_pEffectBomProc;

	CItemProc*			m_pItemProc;
	CSprite*     m_pSprite;   
public:
	void  SetNonActive();

	CEffectProc(CGameMain* pGMain);	// コンストラクタ
	~CEffectProc() { ; }	// デストラクタ
};

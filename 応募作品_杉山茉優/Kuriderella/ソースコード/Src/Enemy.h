//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		敵の処理
//																Enamy.h
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

#define  ENM_WATER_MAX  30
#define  ENM_TORD_MAX  20
#define  ENM_WOLF_MAX  20
#define  ENM_FOX_MAX  20
#define  ENM_KING_MAX 20
#define  ENM_DOS_MAX 20
#define  ENM_SKY_MAX 20
//======================================================================
// 水の敵　オブジェクトクラス
class CEnmWaterObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmWaterObj(CGameMain* pGMain);
	~CEnmWaterObj();
};
//======================================================================
// 水の敵　プロシージャクラス
class CEnmWaterProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// コンストラクタ
	CEnmWaterProc(CGameMain* pGMain);
	~CEnmWaterProc() { ; }
};
//======================================================================
// 灰色の敵　オブジェクトクラス
class CEnmTordObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmTordObj(CGameMain* pGMain);
	~CEnmTordObj();
};
//======================================================================
// 灰色の敵　プロシージャクラス
class CEnmTordProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// コンストラクタ
	CEnmTordProc(CGameMain* pGMain);
	~CEnmTordProc() { ; }
};
//======================================================================
// 赤色の敵　オブジェクトクラス
class CEnmWolfObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmWolfObj(CGameMain* pGMain);
	~CEnmWolfObj();
};
//======================================================================
// 赤色の敵　プロシージャクラス
class CEnmWolfProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// コンストラクタ
	CEnmWolfProc(CGameMain* pGMain);
	~CEnmWolfProc() { ; }
};
//======================================================================
// 緑色の敵　オブジェクトクラス
class CEnmFoxObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;
	int RandomNumAns(int num); // M.S 引数を0～2の数にする
	int num = 0;     // M.S ランダム変数(0～9)
	int returnNum;   // M.S numを0～2の値に変えた変数

	// コンストラクタ
	CEnmFoxObj(CGameMain* pGMain);
	~CEnmFoxObj();
};
//======================================================================
// 緑色の敵　プロシージャクラス
class CEnmFoxProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// コンストラクタ
	CEnmFoxProc(CGameMain* pGMain);
	~CEnmFoxProc() { ; }
};
//======================================================================
// M.S ドッスンの敵　オブジェクトクラス
class CEnmDosObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmDosObj(CGameMain* pGMain);
	~CEnmDosObj();
};
//======================================================================
// M.S ドッスンの敵　プロシージャクラス
class CEnmDosProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// コンストラクタ
	CEnmDosProc(CGameMain* pGMain);
	~CEnmDosProc() { ; }
};
//======================================================================
// M.S ボスの敵　オブジェクトクラス
class CEnmKingObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;
	int eWaitNum;  // M.S 弾発射待ち時間

	// コンストラクタ
	CEnmKingObj(CGameMain* pGMain);
	~CEnmKingObj();
};
//======================================================================
// M.S ボスの敵　プロシージャクラス
class CEnmKingProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// コンストラクタ
	CEnmKingProc(CGameMain* pGMain);
	~CEnmKingProc() { ; }
};
//======================================================================
// M.S 水鳥のオブジェクトクラス
class CEnmSkyObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmSkyObj(CGameMain* pGMain);
	~CEnmSkyObj();
};
//======================================================================
// M.S 水鳥のプロシージャクラス
class CEnmSkyProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// コンストラクタ
	CEnmSkyProc(CGameMain* pGMain);
	~CEnmSkyProc() { ; }
};
//======================================================================
// 敵キャラクター全体のメインプロシージャクラス
//======================================================================
class CEnmProc : public CBaseProc
{
public:
	CEnmWaterProc*	m_pEnmWaterProc;// 水の敵のプロシージャ
	CEnmTordProc*	m_pEnmTordProc; // 灰色の敵のプロシージャ
	CEnmWolfProc*	m_pEnmWolfProc; // 赤色の敵のプロシージャ
	CEnmFoxProc*	m_pEnmFoxProc;  // 緑色の敵のプロシージャ
	CEnmDosProc*    m_pEnmDosProc;  // M.S ドッスンの敵のプロシージャ
	CEnmKingProc*   m_pEnmKingProc; // M.S ボスの敵のプロシージャ
	CEnmSkyProc*    m_pEnmSkyProc;  // M.S 水鳥のプロシージャ
public:
	void  SetNonActive();
	CEnmProc(CGameMain* pGMain);	// コンストラクタ
	~CEnmProc() { ; }
};
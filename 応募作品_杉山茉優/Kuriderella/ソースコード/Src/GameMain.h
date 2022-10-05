//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		ゲームメイン処理
//																GameMain.h
//=============================================================================

#pragma once

//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//ヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>
#include <vector>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Shader.h"
#include "Dinput.h"
#include "Sprite.h"
#include "BaseProc.h"

// ステータスタイプ
#define  NONE				0x00000000
#define  TITLE				0x00000001
#define  STAGEDEMO  		0x00000002
#define  GAMEMAIN			0x00000004
#define  GAMEOVER			0x00000008
#define  GAMECLEAR			0x00000010
#define  GAMEEND			0x00000020

#define  NORMAL				0x00000001
#define  STANBY				0x00000002
#define  CATCH				0x00000004
#define  ATTACK				0x00000008
#define  DAMAGE				0x00000010
#define  DEAD				0x00000020
#define  FLASH				0x00000040
#define  WALK				0x00000080
#define  JUMP				0x00000100
#define  RAND				0x00000200
#define  STOP				0x00000400

// ステータスサブ
#define  ATTACKNONE			0x00000001
#define  ATTACKMOVE			0x00000002
#define  ATTACKLASER		0x00000004
#define  ATTACKCANNON		0x00000008
#define  ATTACKBOM			0x00000010
#define  ATTACKEARTH		0x00000020

// オブジェクト区分
#define  PC					0x00000001
#define  NPC				0x00000002
#define  ENM				0x00000004

// 方向（DirIdx）
#define  UP					0
#define  RIGHT				1
#define  DOWN				2
#define  LEFT				3

#define  GRAVITY  1.0

class CMain;
class CShader;
class CSpriteImage;
class CSprite;
class CFontTexture;
class CBaseObj;
class CBaseProc;
class CPcProc;
class CEnmProc;
class CWeaponProc;
class CWeaponEProc;
class CEffectProc;
class CForeProc;
class CMapProc;
class CTitleProc;
class CBaseProc;

// --------------------------------------------------------------------------------------------------
//  ゲームメインクラス
// --------------------------------------------------------------------------------------------------
class CGameMain
{
public:
	// メンバ変数
	CMain*			m_pMain;		// メインクラス
	CDirect3D*		m_pD3D;			//	Direct3Dオブジェクト
	CXAudio*		m_pXAudio;		//	XAudioオブジェクト
	CDirectInput*	m_pDI;			//	DirectInputDオブジェクト
	CShader*		m_pShader;		//	シェーダー
	CFontTexture*	m_pFont;		//	フォントテクスチャー

	DWORD			m_dwGameStatus;
	VECTOR2			m_vScroll;

	TCHAR str[256];  // M.S テキスト表示に使用する変数
	int SilverS = 0; // M.S 銀箔の数
	int GoldS = 0;   // M.S 金箔の数
	int VisionS = 0; // M.S 幻の砂糖の数
	float sabun;  // M.S プレイキャラの方向へ弾を打つ位置の差分
	int time;     // M.S ゲーム時間カウント
	int SumP = 0; // M.S トータルスコア
	int ints = 0; // M.S 水鳥のコメントの種類を分ける変数 
	int timeSum;  // M.S 残りの制限時間
	int henk;     // M.S ドッスンの敵との接触フラグ
	int hank;     // M.S 水の敵との接触フラグ
	short textStr = 0;  // M.S 武器強化コメントの種類を分ける変数
	int CR = 0;         // M.S ゲームクリアフラグ
	int m_nEShotWait = 10; // M.S 弾の待ち時間
	bool mapSsw;           // M.S マップ移動時フラグ
	int spP = 0;           // M.S SPステージを呼びだしたフラグ
	int mapNumP = 0;       // M.S 武器強化チャンスステージ後へ行くマップ変数
	int valS = 0;          // M.S 武器強化チャンスステージの場所乱数
	int i = 0;             // M.S 一度のみ武器強化チャンスステージの場所乱数排出処理をするフラグ
	short stS = 0;         // M.S 武器強化をしたフラグ
	bool strongSSw = false; // M.S 武器が強化されているかどうかフラグ
	bool transactionW;  // M.S 武器強化取引コメントの表示フラグ
	int timekon = 1;    // M.S 武器強化取引コメント表示時間
	short scoreCnt = 0; // M.S スコアの表示並び替えを一度のみする

	// プロシージャ
	CPcProc*		m_pPcProc;
	CEnmProc*		m_pEnmProc;
	CWeaponProc*	m_pWeaponProc;
	CWeaponEProc*	m_pWeaponEProc;
	CEffectProc*	m_pEffectProc;
	CForeProc*		m_pForeProc;
	CMapProc*		m_pMapProc;
	CTitleProc*		m_pTitleProc;

	// サウンド
	CXAudioSource*  m_pSeShot;
	CXAudioSource*  m_pSeHit;
	CXAudioSource*  m_pSePower;
	CXAudioSource*  m_pBgm1;

	// スプライト
	CSpriteImage*   m_pImageChar;
	CSpriteImage*   m_pImageSprite;
	CSpriteImage*   m_pImageChestHeart;
	CSpriteImage*   m_pImageOrange;
	CSprite*        m_pOrangeM;
	CSpriteImage*   m_pWeaponImage;
	CSpriteImage*   m_pImageSpriteS;
	CSpriteImage*   m_pImageSpriteV;
	CSpriteImage*   m_pImageRank;
	
	CDirectInput* pDI = m_pDI;
public:
	// メソッド
	CGameMain(CMain* pMain);
	~CGameMain();

	void DrawSkyText();           // M.S 水鳥の各ステージでのコメントテキストの表示
	void DrawMenuText();          // M.S メニューテキストの表示
	void DrawWeaponTradingText(); // M.S 武器の強化取引テキストの表示
	void CountGameTime();         // M.S 制限時間の計算
	void CalculateScore();        // M.S スコアの計算
	HRESULT Init();
	void    Loop();
	void    GameMain();
	void    Quit();

	HRESULT ChangeScreenMode(int nMode=-1);    // -- 2020.1.15

};


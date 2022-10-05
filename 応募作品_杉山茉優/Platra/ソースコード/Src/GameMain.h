//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//
//		ゲームのメイン処理
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
#include "Shader.h"
#include "FbxMesh.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite3D.h"
#include "Collision.h"
#include "Displace.h"
#include "BBox.h"
#include "BaseProc.h"
#include "MyImgui.h"

// ステータスタイプ
#define  NONE				0x00000000
#define  TITLE				0x00000001
#define  STAGEDEMO  		0x00000002
#define  GAMEMAIN			0x00000004
#define  GAMEOVER			0x00000008
#define  GAMECLEAR			0x00000010
#define  GAMEEND			0x00000020

#define  NORMAL				0x00000001
#define  WAIT				0x00000002
#define  DAMAGE				0x00000004
#define  FLASH				0x00000008
#define  DEAD				0x00000010

// ステータスサブ
#define  ATTACKNONE			0x00000001
#define  ATTACKMOVE			0x00000002
#define  ATTACKLASER		0x00000004
#define  ATTACKCANNON		0x00000008
#define  ATTACKBOM			0x00000010
#define  ATTACKEARTH		0x00000020
#define  ATTACKSWORD		0x00000040
#define  ATTACKFLAME		0x00000080
#define  ATTACKWAIT			0x00000100

// オブジェクト区分
#define  PC					0x00000001
#define  NPC				0x00000002
#define  ENM				0x00000004


class CMain;
class CShader;
class CSpriteImage;
class CSprite;
class CFontTexture;
class CCollision;
class CWave;
class CBBox;
class CFbxMeshCtrl;

class CBaseObj;
class CBaseProc;
class CPcProc;
class CCameraProc;
class CEnmProc;
class CMapProc;
class CWeaponProc;
class CEffectProc;
class CBackForeProc;
class CTitleProc;

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
	CFontTexture*	m_pFont;		//	フォントテクスチャー
	CShader*		m_pShader;		//	シェーダー
	CFbxMeshCtrl*	m_pFbxMeshCtrl;	// メッシュコントロールクラス    // -- 2021.2.4
	CBBox*          m_pBox;

	DWORD           m_dwGameStatus;
	
	// カメラ・ライト・ビュー
	VECTOR3         m_vEyePt;		//カメラ（視点）位置
	VECTOR3         m_vLookatPt;	//注視位置
	MATRIX4X4       m_mView;
	MATRIX4X4       m_mProj;
	VECTOR3         m_vLightDir;	//ディレクショナルライトの方向

	// プロシージャ
	CPcProc*		m_pPcProc;
	CCameraProc*	m_pCameraProc;
	CEnmProc*		m_pEnmProc;
	CMapProc*		m_pMapProc;
	CWeaponProc*	m_pWeaponProc;
	CEffectProc*	m_pEffectProc;
	CBackForeProc*	m_pBackForeProc;
	CTitleProc*		m_pTitleProc;

	// M.S プラトレのサウンド
	CXAudioSource*   titleBgm;
	CXAudioSource*   gameBgm;
	CXAudioSource*   gameClearBgm;
	CXAudioSource*   resultBgm;
	CXAudioSource*   gameOverBgm;

	CXAudioSource*   turnThePageSound;
	CXAudioSource*   selectSound;
	CXAudioSource*   saveWarningSound;
	CXAudioSource*   bornStarSound;
	CXAudioSource*   goSound;
	CXAudioSource*   timeCountSound;
	CXAudioSource*   lineChangeSound;
	CXAudioSource*   linePlacementSound;
	CXAudioSource*   rideSound;
	CXAudioSource*   saveOkSound;
	CXAudioSource*   nextStarOkSound;
	
public:
	// メソッド
	CGameMain(CMain* pMain);
	~CGameMain();

	HRESULT Init();
	void    Loop();
	void    Quit();

	void    GameMain();
	HRESULT ChangeScreenMode(int nMode=-1);    // -- 2020.1.15
	// M.S ファイルの読み込み関数
	void FileRead();
	// M.S ファイルの書き込み関数
	void FileWrite();
	// M.S 効果音音量調整関数
	void SetSoundVolume();
	// M.S BGM音音量調整関数
	void SetBgmVolume();

	int m_dwGameMode;
	// M.S カーソルの位置
	int cursolX;
	int cursolY;
	// M.S 回転の処理が行われたフラグ
	bool rotateFlag;
	bool transparentSwitch;   // M.S プレイキャラの透明処理の判定
	int initialH;          // M.S プレイキャラのマスの初期値(縦)
	int initialV;          // M.S プレイキャラのマスの初期値(横)
	int lineTrainSelectNum;  // M.S プログラムで使用する線路数
	int passengersSelectNum;  // M.S プログラムで使用する乗車人数
	int waitingTimeSelectNum; // M.S プログラムで使用する待ち時間
	float bgmSelectNum;  // M.S プログラムで使用するBGM音量
	float seSelectNum;   // M.S プログラムで使用するSE音量
	int traveledStar;    // M.S 行った星の数
	int haveToGoStar;    // M.S 行かなければならない星の数
	int starArray[25] = { 0 }; // M.S ファイル読み込み、書き出しに使用する星の配列
	int redMan;    // M.S ファイル読み込み、書き出しに使用する人数(赤)
	int yellowMan; // M.S ファイル読み込み、書き出しに使用する人数(黄)
	int blueMan;   // M.S ファイル読み込み、書き出しに使用する人数(青)
	int rankOne;   // M.S ファイル読み込み、書き出しに使用する1位のスコア数
	int rankTwo;   // M.S ファイル読み込み、書き出しに使用する2位のスコア数
	int rankThree; // M.S ファイル読み込み、書き出しに使用する3位のスコア数
	int rankFour;  // M.S ファイル読み込み、書き出しに使用する4位のスコア数
	int rankFive;  // M.S ファイル読み込み、書き出しに使用する5位のスコア数
	bool stopOperation;  // M.S ゲームの処理を止めるフラグ
	
	int rankLineTrainSelectNum;   // M.S ランキングモード時使用する線路数
	int rankPassengersSelectNum;  // M.S ランキングモード時使用する乗車人数
	int rankWaitingTimeSelectNum; // M.S ランキングモード時使用する待ち時間
	int rankTraveledStar; // M.S ランキングモード時使用する行った星の数
    int rankHaveToGoStar; // M.S ランキングモード時使用する行かなければならない星の数
	int rankRedMan;    // M.S ランキングモード時使用する人数(赤)
	int rankYellowMan; // M.S ランキングモード時使用する人数(黄)
	int rankBlueMan;   // M.S ランキングモード時使用する人数(青)

	bool continuationFlag; // M.S セーブデータがあるかどうかフラグ
	FILE* dataFileWrite;   // M.S ファイル構造体のポインタ
};
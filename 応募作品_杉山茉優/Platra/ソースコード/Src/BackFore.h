//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0     BackFore.h
//=============================================================================
#pragma once
#include "GameMain.h"


// --------------------------------------------------------------------
// 前景・背景　プロシージャクラス
// 
// (注意)基本プロシージャクラスは継承していない
// --------------------------------------------------------------------
class CBackForeProc 
{
protected:
	CGameMain*		m_pGMain;
	CSprite*        m_pSprite;
	// スプライトイメージの変数
	CSpriteImage*   m_pImageForegrd;
	CSpriteImage*   m_pImageDynamicStarScene;  // M.S ゲーム中のUI
	CSpriteImage*   m_pImagePlacementSceneNum; // M.S ゲーム中の数字イメージ
	CSpriteImage*   m_pImageStarBridgeSaving;  // M.S セーブテキストイメージ
	CSpriteImage*   m_pImageRankingNum;        // M.S ランキング数字イメージ
	CSpriteImage*   m_pImageStarBridgeButton;  // M.S 星の架け橋をかけるボタンイメージ
	CSpriteImage*   m_pImageRemainingStar;     // M.S 残りの星の数テキストイメージ
	CSpriteImage*   m_pImageLineKind;          // M.S 選択中の線路の種類テキストイメージ
	CSpriteImage*   m_pImageLinePermission;    // M.S 配置許可(〇×)イメージ
	// M.S 移動距離を満たした場合のエフェクトイメージ
	CSpriteImage*   m_pImageGaugeGlitter;      
	CSpriteImage*   m_pImageGoalButton;        // M.S ゴールボタンイメージ

public:
	void			Update();
	CSpriteImage*   GetImage() { return m_pImageForegrd; }
	CSprite*        GetSprite() { return m_pSprite; }
	CBackForeProc(CGameMain* pGMain);	// コンストラクタ
	~CBackForeProc();
	// M.S CBackForeProcのここから下は追加した変数、関数です
	// M.S ↓--------------------------------------------------------------------
	// ランキング用イメージのゲッター
	CSpriteImage* GetRankingNum() { return m_pImageRankingNum; }
	// 数字を桁で分けて保存するための関数
	int VariableAnalysis(int analysisObject);
	void VariableAnalysisChangeNum(int analysisObject, int analysisObjectKind);
	// キラキラ表示関数
	void DrawGlitterGauge();
	// 星の架け橋ゲージの文字表示
	void DrawNextPassengersText();
	// 次の星までの乗車人数の文字表示
	void DrawNextGaugeText();
	// 必要な乗車人数の表示
	void DrawNextNeedPassengers();
	// 必要な電車の移動距離ゲージの表示
	void DrawStarGauge();
	// 発射までのカウントダウン
	void DrawWaitTime();
	// 次の星へ行くボタンの表示
	void DrawGoNextStarButton();
	// 選択中の線路の表示とその線路が配置可能かの表示
	void DrawArrowLine();
	// 各ステージの表示関数
	void DrawStage1();
	void DrawStage2();
	void DrawStage3();

	int numArray[5] = { 0 };    // 数字を桁で分けて保存する配列
	// 待ち時間のカウント数字の初期数
	int waitingDrawTime;
	// 表示用カウント数字保存変数
	int initialDraw;
	// 架け橋がかかったかどうか保存変数
	bool builtStarBridge;
	// 点滅カウント数字
	int starBridgeSceneNext;
	int starBridgeSceneTime;
	// 点滅させるカウント変数
	int buttonBlinking;
	// 次の星へ行くボタン用位置変数
	int DestXStarBridgeButton;
	int DestYStarBridgeButton;
	int nHeightScaleStarBridgeButton;
	int nWidthScaleStarBridgeButton;
	// 発射までのカウント用変数
	int drawWaitingNum;
	// 発射までのカウントの数字セットを一度のみ行う変数
	bool initialWaitingNumSet;
	// 発射までのカウントの音を鳴らすフラグ
	bool ringTime;    
	// キラキラ用位置変数
	int glitterGaugeDestX;
	int glitterGaugeDestY;
	int glitterGaugenHeight;
	int glitterGaugenWidth;
	int glitterGaugenWidthScale;
	int glitterGaugenHeightScale;
	int glitterAnimNum;
	// セーブ音を一度鳴らすための変数
	bool doneBridgeSound;
	// 今のシーンの乗車人数
	int allManNum;
	// ゲージの幅
	int gaugenWidth;
	// キラキラのアニメーション用カウント変数
	int waitTime;
};


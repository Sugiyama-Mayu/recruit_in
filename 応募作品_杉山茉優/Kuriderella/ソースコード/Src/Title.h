//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//      オープニングタイトル・ゲームクリヤー・ゲームオーバーの処理
//																Title.h
//=============================================================================

#pragma once

#include "GameMain.h"

// --------------------------------------------------------------------
// タイトル　プロシージャクラス
// --------------------------------------------------------------------
class CTitleProc : public CBaseProc
{
protected:
	CGameMain*		m_pGMain;

	CSpriteImage*   m_pImageTitle;
	CSpriteImage*   m_pImageClear;
	CSpriteImage*   m_pImageOver;
	CSprite*        m_pSprite;
	CSprite*        m_pScore;  // M.S スコア枠

	DWORD           m_dwCntTime;
public:
	void Title();
	void GameClear();
	void GameOver();
	CTitleProc(CGameMain* pGMain);	// コンストラクタ
	~CTitleProc();

	int s1[1], s2[1], s3[1]; // M.S ランキング表示のための配列
};


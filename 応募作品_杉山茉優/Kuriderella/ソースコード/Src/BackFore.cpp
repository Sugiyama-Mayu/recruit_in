//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		前景・後景処理
//																BackFore.cpp
//=============================================================================

#include "GameMain.h"
#include "Playchar.h"
#include "BackFore.h"


// ========================================================================================
//
// 前景の処理
//
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	前景プロシージャのコンストラクタ	
//
//  引数　CGameMain* pGMain
//
//------------------------------------------------------------------------
CForeProc::CForeProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_pForegrd = new CSprite(m_pGMain->m_pShader);
	// M.S 残機の表示スプライト
	m_pSchest = new CSprite(m_pGMain->m_pImageChestHeart, 192, 0, 64, 64);
	// M.S MPの栗のスプライト(3つ)
	m_pCMp3 = new CSprite(m_pGMain->m_pImageChestHeart, 0, 0, 192, 64);
	// M.S MPの栗のスプライト(2つ)
	m_pCMp2 = new CSprite(m_pGMain->m_pImageChestHeart, 0, 0, 128, 64);
	// M.S MPの栗のスプライト(1つ)
	m_pCMp1 = new CSprite(m_pGMain->m_pImageChestHeart, 0, 0, 64, 64);
	// M.S 強化武器のスプライト
	ST = new CSprite(m_pGMain->m_pImageSprite, 48, 0, 48, 48);
}
// ---------------------------------------------------------------------------
//
// 前景プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CForeProc::~CForeProc()
{
	SAFE_DELETE(m_pForegrd);
	SAFE_DELETE(m_pSchest);  // M.S 残機のハートのスプライト
	SAFE_DELETE(m_pCMp3);     // M.S MPの栗のスプライト(3つ)
	SAFE_DELETE(m_pCMp2);     // M.S MPの栗のスプライト(2つ)
	SAFE_DELETE(m_pCMp1);     // M.S MPの栗のスプライト(1つ)
	SAFE_DELETE(ST);         // M.S 強化武器獲得のスプライト
}
//-----------------------------------------------------------------------------
// 前景プロシージャの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CForeProc::Update()
{
	CSpriteImage* pImageFore = m_pGMain->m_pImageSprite; // すでに読み込んであるスプライトイメージを使用する

	// M.S ＨＰとＭＰの表示
	TCHAR str[256];
	_stprintf(str, _T("%d"), m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp());  // M.S HPの表示
	m_pGMain->m_pFont->Draw(64, 14, str, 50, RGB(127, 255, 212));
	int a = m_pGMain->m_pPcProc->GetPcNum();
	// M.S 残機の表示
	if (m_pGMain->m_pPcProc->GetPcNum() >= 2) {                 
		m_pSchest->Draw(115, 3);
	}
	// M.S MPの栗の表示(3つ)
	if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetMp() >= 900 ) {  
		m_pCMp3->Draw(1125, 0);
	}	
	// M.S MPの栗の表示(2つ)
	else if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetMp() >= 600) {
		m_pCMp2->Draw(1125, 0);
	}
	// M.S MPの栗の表示(1つ)
	else if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetMp() >= 300) {
		m_pCMp1->Draw(1125, 0);
	}
	
	if (m_pGMain->stS == 1) {    // M.S 強化武器の獲得画像表示
		ST->Draw(200, 15);
	}
}
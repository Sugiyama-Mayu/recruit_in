//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//      オープニングタイトル・ゲームクリヤー・ゲームオーバーの処理
//																Title.cpp
//=============================================================================
#include "Title.h"
#include "Playchar.h"
#include <stdio.h>
#include <string>
//============================================================================
//
// タイトルプロシージャのコンストラクタ
//
// ---------------------------------------------------------------------------
CTitleProc::CTitleProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pGMain = pGMain;
	m_pSprite = new CSprite(m_pGMain->m_pShader); // スプライトの生成
	m_pImageTitle = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/title.png")); // イメージのロード
	m_pImageClear = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/clear.png")); // イメージのロード
	m_pImageOver = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/over.png")); // イメージのロード
	m_pScore = new CSprite(m_pGMain->m_pImageRank, 0, 0, 500, 70);

	m_dwCntTime = 0;
}
// ---------------------------------------------------------------------------
//
// タイトルタイトルプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CTitleProc::~CTitleProc()
{
	SAFE_DELETE(m_pImageTitle);
	SAFE_DELETE(m_pImageClear);
	SAFE_DELETE(m_pImageOver);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pScore);
}
//------------------------------------------------------------------------
//
//	タイトルの表示	
//
//------------------------------------------------------------------------
void CTitleProc::Title()
{
	// フルスクリーンにする(なぜか1度だけだと戻ってしまうので、再度フルスクリーンにする)
	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pGMain->m_pFont->Draw(323, 193, _T("栗デレラ"), 130, RGB(175, 238, 238), 1.0f, _T("メイリオ"));
	m_pGMain->m_pFont->Draw(320, 190, _T("栗デレラ"), 130, RGB(255, 165, 0), 1.0f, _T("メイリオ"));
	// フォント名　"ＤＦ勘亭流"，"ＭＳ Ｐゴシック"，"ＭＳ ゴシック"，"HGP創英角ﾎﾟｯﾌﾟ体"，"HGP創英角ｺﾞｼｯｸUB"
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH - 430, 270, _T("DirectX11対応"), 60, RGB(0, 255, 127), 1.0f, _T("メイリオ"));
	m_dwCntTime++;
	if (m_dwCntTime % 10 > 5)
	{
		m_pGMain->m_pFont->Draw(400, WINDOW_HEIGHT - 110, _T("HIT SPACE KEY!!"), 40, RGB(64, 224, 208), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_RETURN)
		|| m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON)
		|| m_dwCntTime > 600)
	{
		// サウンドの再生
		m_pGMain->m_pBgm1->Play(AUDIO_LOOP);
		m_pGMain->m_dwGameStatus = GAMEMAIN;  // ゲームメインへ(開始)
		m_dwCntTime = 0;
	}

	// M.S 過去のランキングの読み込み
	FILE* fIn1;
	
	fIn1 = fopen("scoreF.txt", "r");
	fscanf(fIn1, "%d %d %d", s1, s2, s3);
	fclose(fIn1);
}
//------------------------------------------------------------------------
//
//	ゲームクリヤーの表示	
//
//------------------------------------------------------------------------
void CTitleProc::GameClear()
{
	// 背景表示
	m_pSprite->Draw(m_pImageClear, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	TCHAR str[256];
	// M.S トータルスコアの表示
	_stprintf(str, _T("%d"), m_pGMain->SumP);
	m_pGMain->m_pFont->Draw(710, 203, str, 70, RGB(153, 51, 102));
	_stprintf(str, _T("%d"), m_pGMain->SumP);
	m_pGMain->m_pFont->Draw(710, 200, str, 70, RGB(255, 255, 153));

	m_pGMain->m_pFont->Draw(490, 200, _T("スコア："), 70, RGB(255, 204, 153), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	m_pGMain->m_pFont->Draw(403, 83, _T("GAME CLEAR"), 90, RGB(0, 0, 0), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	m_pGMain->m_pFont->Draw(400, 80, _T("GAME CLEAR"), 90, RGB(240, 128, 128), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	// M.S ランキングの枠イメージの表示
	m_pScore->Draw(420, 300);
	m_pScore->Draw(420, 380);
	m_pScore->Draw(420, 460);
	// M.S ランキングの配列の並び替え
	if (m_pGMain->scoreCnt <= 0) { 	// M.S 一度のみの処理 
		// M.S トータルスコアの計算
		m_pGMain->CalculateScore();
		// M.S 今回のスコアが一位以上かどうか
		if (m_pGMain->SumP >= s1[0]) { 
			s3[0] = s2[0];
			s2[0] = s1[0];
			s1[0] = m_pGMain->SumP;
		}
		// M.S 今回のスコアが二位以上かどうか
		else if (m_pGMain->SumP >= s2[0]) {
			s3[0] = s2[0];
			s2[0] = m_pGMain->SumP;
		}
		// M.S 今回のスコアが三位以上かどうか
		else if (m_pGMain->SumP >= s3[0]) {
			s3[0] = m_pGMain->SumP;
		}	
		// M.S 並び変えた配列を変数に入れる
		FILE* fOut;
		fOut = fopen("scoreF.txt", "w");

		char smo1[5], smo2[5], smo3[5];
		sprintf(smo1, "%d", s1[0]);
		sprintf(smo2, "%d", s2[0]);
		sprintf(smo3, "%d", s3[0]);
		// M.S スペースで区切ってファイルに書き込む
		fputs(smo1,fOut);
		fputc(' ', fOut);
		fputs(smo2, fOut);
		fputc(' ', fOut);
		fputs(smo3, fOut);

		fclose(fOut);

		m_pGMain->scoreCnt++; 
	}
	// M.S ランキングの表示
	_stprintf(str, _T("1位     %d" ), s1[0]);
	m_pGMain->m_pFont->Draw(520, 310, str, 50, RGB(0, 191, 255),1.0f, _T("メイリオ"));
	_stprintf(str, _T("1位     %d" ), s1[0]);
	m_pGMain->m_pFont->Draw(522, 312, str, 50, RGB(255, 250, 250), 1.0f, _T("メイリオ"));

	_stprintf(str, _T("2位     %d"), s2[0]);
	m_pGMain->m_pFont->Draw(520, 390, str, 50, RGB(0, 191, 255), 1.0f, _T("メイリオ"));
	_stprintf(str, _T("2位     %d"), s2[0]);
	m_pGMain->m_pFont->Draw(522, 392, str, 50, RGB(255, 250, 250), 1.0f, _T("メイリオ"));

	_stprintf(str, _T("3位     %d"), s3[0]);
	m_pGMain->m_pFont->Draw(520, 470, str, 50, RGB(0, 191, 255), 1.0f, _T("メイリオ"));
	_stprintf(str, _T("3位     %d"), s3[0]);
	m_pGMain->m_pFont->Draw(522, 472, str, 50, RGB(255, 250, 250), 1.0f, _T("メイリオ"));
	
	m_dwCntTime++;
	if (m_dwCntTime % 10 > 5)
	{
		m_pGMain->m_pFont->Draw(500, WINDOW_HEIGHT - 120, _T("HIT SPACE KEY!!"), 40, RGB(64, 224, 208), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	}

	// 時間がたっていて、操作をしたら
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_RETURN)
		|| m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON) 
		|| m_dwCntTime > 600)
	{
		// ゲームの終了処理
		m_pGMain->m_pBgm1->Stop();
		m_pGMain->m_dwGameStatus = GAMEEND;
		m_pGMain->scoreCnt = 0;
		m_dwCntTime = 0;
	}
}
//------------------------------------------------------------------------
//
//	ゲームオーバーの表示	
//
//------------------------------------------------------------------------
void CTitleProc::GameOver()
{
	// 表示
	m_pSprite->Draw(m_pImageOver, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pGMain->m_pFont->Draw(423, 153, _T("GAME OVER"), 90, RGB(0, 0, 0), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	m_pGMain->m_pFont->Draw(420, 150, _T("GAME OVER"), 90, RGB(0, 0, 255), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));

	m_dwCntTime++;
	if (m_dwCntTime % 10 > 5)
	{
		m_pGMain->m_pFont->Draw(500, WINDOW_HEIGHT - 120, _T("HIT SPACE KEY!!"), 40, RGB(64, 224, 208), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	}

	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_RETURN) ||
		m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON) 
		|| m_dwCntTime > 600)	
	{
		// ゲームの終了処理
		m_pGMain->m_pBgm1->Stop();
		m_pGMain->m_dwGameStatus = GAMEEND;
		m_dwCntTime = 0;
	}
}
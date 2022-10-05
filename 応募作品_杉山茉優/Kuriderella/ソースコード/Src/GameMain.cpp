//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		ゲームメイン処理
//																GameMain.cpp
//=============================================================================

#include <stdio.h>
#include <string>

#include "GameMain.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"
#include "Map.h"
#include "Title.h"

//------------------------------------------------------------------------
//
//	ゲームメインクラスのコンストラクタ	
//
//  引数　CMain*	pMain
//
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain*	pMain)
{
	ZeroMemory(this, sizeof(CGameMain));
	m_pMain = pMain;
}
//------------------------------------------------------------------------
//
//	ゲームメインクラスのデストラクタ	
//
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{

	SAFE_DELETE(m_pTitleProc);
	SAFE_DELETE(m_pMapProc);
	SAFE_DELETE(m_pForeProc);
	SAFE_DELETE(m_pEffectProc);
	SAFE_DELETE(m_pWeaponProc);
	SAFE_DELETE(m_pEnmProc);
	SAFE_DELETE(m_pPcProc);

	SAFE_DELETE(m_pSePower);
	SAFE_DELETE(m_pSeShot);
	SAFE_DELETE(m_pSeHit);
	SAFE_DELETE(m_pBgm1);

	SAFE_DELETE(m_pImageChar);
	SAFE_DELETE(m_pImageSprite);

	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDI);
	SAFE_DELETE(m_pXAudio);
	SAFE_DELETE(m_pD3D);

	CoUninitialize();   // COMの解放
}
//------------------------------------------------------------------------
//
//	アプリケーションの初期化処理	
//
//  引数　なし
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CGameMain::Init()
{
	// ＣＯＭの初期化
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoInitialize( NULL );

	// Direct3Dの初期化
	m_pD3D = new CDirect3D;
	if (FAILED(m_pD3D->InitD3D(m_pMain->m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("Direct3Dを初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// シェーダーの初期化
	m_pShader = new CShader(m_pD3D);
	if (FAILED(m_pShader->InitShader())) {
		MessageBox(0, _T("Shaderを生成・初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// XAudio2の初期化
	m_pXAudio = new CXAudio;
	if (FAILED(m_pXAudio->InitAudio(m_pMain->m_hWnd))) {
		MessageBox(0, _T("XAudio2を初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// DirectInputの初期化
	m_pDI = new CDirectInput;
	if (FAILED(m_pDI->StartDirectInput(m_pMain->m_hInstance, m_pMain->m_hWnd,
		INIT_KEYBOARD | INIT_MOUSE | INIT_JOYSTICK, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("DirectInputを初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// フォントテクスチャーの初期化
	m_pFont = new CFontTexture(m_pShader);

	// フォント＆スプライト用のシェーダーのセット
	// 最初に1回だけシェーダーのセットをする。途中でシェーダーの変更はないため。
	m_pFont->SetShader();

	// ----------------------------------------------------------------------------------------
	// スプライトイメージのロード
	m_pImageOrange = new CSpriteImage(m_pShader, _T("Data/Image/オレンジ枠 ウィンドウ.png")); // メニュー画面のロード
	m_pImageChar   = new CSpriteImage(m_pShader, _T("Data/Image/スプライトシート キャラクターY.png"));   // キャラクターイメージのロード
	m_pImageSprite = new CSpriteImage(m_pShader, _T("Data/Image/アイテムスプライト2.png")); // スプライトイメージのロード
	m_pImageSpriteS = new CSpriteImage(m_pShader, _T("Data/Image/アイテムスプライト3.png"));
	m_pImageSpriteV = new CSpriteImage(m_pShader, _T("Data/Image/アイテムスプライト4.png"));
	m_pImageChestHeart = new CSpriteImage(m_pShader, _T("Data/Image/くりとはーと.png"));  // HPMP残機のイメージの表示
	m_pWeaponImage = new CSpriteImage(m_pShader, _T("Data/Image/弾 スプライト.png")); // 弾のイメージのロード
	m_pImageRank = new CSpriteImage(m_pShader, _T("Data/Image/rank.png"));  // ランクの枠

	// プロシージャの初期化
	m_pPcProc   = new CPcProc(this);
	m_pEnmProc  = new CEnmProc(this);
	m_pWeaponProc  = new CWeaponProc(this);
	m_pEffectProc  = new CEffectProc(this);
	m_pForeProc = new CForeProc(this);
	m_pMapProc  = new CMapProc(this);
	m_pTitleProc = new CTitleProc(this);

	// サウンド
	m_pSePower = new CXAudioSource(m_pXAudio, _T("Data/Sound/PowerUp2.wav"));
	m_pSeHit = new CXAudioSource(m_pXAudio, _T("Data/Sound/Damage.wav"), 5);
	m_pSeShot = new CXAudioSource(m_pXAudio, _T("Data/Sound/MainShot.wav"), 10);
	m_pBgm1 = new CXAudioSource(m_pXAudio, _T("Data/Sound/bgm.mp3"));

	// ゲーム変数の初期化
	m_dwGameStatus = TITLE;
	// スクロール座標の初期化
	m_vScroll = VECTOR2(0, 0);

	return S_OK;
}

//------------------------------------------------------------------------
//
//	アプリケーションのメインループ処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::Loop()
{
	m_pDI->GetInput();			// 入力情報の取得
	m_pFont->Refresh();         // フォント情報のリフレッシュ
	time += 1;
	if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // フルスクリーンの切り替え       // -- 2018.12.14
	
	switch (m_dwGameStatus)
	{
		case TITLE:				// ゲーム開始タイトル
			m_pTitleProc->Title();
			break;

		case GAMEMAIN:			// ゲーム主処理
			GameMain();
			break;

		case GAMECLEAR:			// ゲームクリヤー処理
			m_pTitleProc->GameClear();
			break;

		case GAMEOVER:			// ゲームオーバー処理
			m_pTitleProc->GameOver();
			break;

		case GAMEEND:			// ゲーム終了
			PostQuitMessage(0);
			break;
	}

	//画面更新（バックバッファをフロントバッファに）
	m_pD3D->m_pSwapChain->Present(0, 0);
}
//M.S 水鳥の各ステージでのコメントテキストの表示
//引  数：なし
//戻り値：なし
void CGameMain::DrawSkyText() {
	if (ints == 1) { // ステージ1
		m_pFont->Draw(200, 140, _T("「スイ君」"), 48, RGB(255, 215, 0),
			1.0f, _T("メイリオ"));
		m_pFont->Draw(200, 190, _T("石のエネミーに当たって、イガをとろう！"), 48, RGB(32, 178, 170),
			1.0f, _T("メイリオ"));
	}
	if (ints == 2) { // ステージ2
		m_pFont->Draw(200, 140, _T("「スイ君」"), 48, RGB(255, 215, 0),
			1.0f, _T("メイリオ"));
		m_pFont->Draw(200, 190, _T("お湯に当たって、煮よう！"), 48, RGB(32, 178, 170),
			1.0f, _T("メイリオ"));
	}
	if (ints == 3) { // ステージ3
		m_pFont->Draw(200, 140, _T("「スイ君」"), 48, RGB(255, 215, 0),
			1.0f, _T("メイリオ"));
		m_pFont->Draw(200, 190, _T("ラスボスだ！全部倒さなくてもいいよ！"), 48, RGB(32, 178, 170),
			1.0f, _T("メイリオ"));
	}
	if (ints == 4) { // ステージSP
		m_pFont->Draw(200, 140, _T("「スイ君」"), 48, RGB(255, 215, 0),
			1.0f, _T("メイリオ"));
		m_pFont->Draw(200, 190, _T("SPステージだよ！"), 48, RGB(32, 178, 170),
			1.0f, _T("メイリオ"));
	}
	if (ints == 5) { // 武器強化ステージ
		m_pFont->Draw(200, 140, _T("「スイ君」"), 48, RGB(255, 215, 0),
			1.0f, _T("メイリオ"));
		m_pFont->Draw(200, 190, _T("武器強化チャンスだよ！"), 48, RGB(32, 178, 170),
			1.0f, _T("メイリオ"));
	}
}
//M.S メニューテキストの表示
//引  数：なし
//戻り値：なし
void CGameMain::DrawMenuText() {
	m_pOrangeM = new CSprite(m_pImageOrange, 0, 0, 800, 500);
	m_pOrangeM->Draw(0, 0);

	if (henk == 1) {  // ドッスンの敵と接触したかどうか
		m_pFont->Draw(600, 140, _T(":済"), 48, RGB(255, 99, 71),
			1.0f, _T("メイリオ"));
	}

	if (hank == 1) {  // 水の敵と接触したかどうか
		m_pFont->Draw(600, 190, _T(":済"), 48, RGB(255, 99, 71),
			1.0f, _T("メイリオ"));
	}

	_stprintf(str, _T("%d"), SilverS);  // 銀箔の数
	m_pFont->Draw(500, 310, str, 48, RGB(165, 42, 42));

	_stprintf(str, _T("%d"), GoldS);    // 金箔の数
	m_pFont->Draw(500, 360, str, 48, RGB(165, 42, 42));

	_stprintf(str, _T("%d"), VisionS);  // 幻の砂糖の数
	m_pFont->Draw(500, 410, str, 48, RGB(165, 42, 42));
}
//M.S 武器の強化取引テキストの表示
//引  数：なし
//戻り値：なし
void CGameMain::DrawWeaponTradingText() {
	if (transactionW == true) { 
		if (textStr == 0) {      // 最初のコメント
			m_pFont->Draw(200, 100, _T("強化武器が欲しいのならば、"), 40, RGB(240, 230, 140),
				1.0f, _T("メイリオ"));

			m_pFont->Draw(200, 150, _T("金ぱく:１,銀ぱく:５ わたすのじゃ"), 40, RGB(240, 230, 140),
				1.0f, _T("メイリオ"));

			m_pFont->Draw(200, 200, _T("取引に従う：Eキー"), 40, RGB(240, 230, 140),
				1.0f, _T("メイリオ"));
		}
		else if (textStr == 1) {  // 取引をした時のコメント
			m_pFont->Draw(200, 100, _T("毎度ありじゃ"), 40, RGB(240, 230, 140),
				1.0f, _T("メイリオ"));

		}
		else if (textStr == 2) {  // アイテムが足りず取引ができない時のコメント
			m_pFont->Draw(200, 100, _T("足りないのじゃ"), 40, RGB(240, 230, 140),
				1.0f, _T("メイリオ"));
		}
	}
}
//M.S 制限時間の計算
//引  数：なし
//戻り値：なし
void CGameMain::CountGameTime() {
	int time2 = 200;         // Max制限時間
	int time1 = time / 100;
	timeSum = time2 - time1; // 残りの制限時間を出す
}
//------------------------------------------------------------------------
//
//	ゲームのメイン処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::GameMain()
{
	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,1,1 };// クリア色作成　RGBAの順
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア

	// プロシージャの更新
	m_pMapProc->Update();		// マッププロシージャの更新
	m_pEffectProc->UpdateAll();	// 映像効果プロシージャの更新
	m_pEnmProc->UpdateAll();	// 敵プロシージャの更新
	m_pPcProc->UpdateAll();		// ＰＣプロシージャの更新

	m_pWeaponProc->UpdateAll();	// 武器プロシージャの更新


	m_pMapProc->Update2();		// マッププロシージャの更新2
	m_pForeProc->Update();		// 前景プロシージャの更新	

	DrawSkyText();   //M.S 水鳥の各ステージでのコメントテキストの表示
	DrawWeaponTradingText();  //M.S メニューテキストの表示	

	// キーを押した際のメニュー(レシピ)表示
	if (m_pDI->CheckKey(KD_DAT, DIK_Q)) 
	{	
		DrawMenuText();  // M.S 武器の強化取引テキストの表示
	}
	CountGameTime();     // M.S 残り制限時間を出す
	if (timeSum <= 0) {  // M.S 制限時間が0以下になったらゲームオーバー
		m_pTitleProc->GameOver();
	}
	else {
		_stprintf(str, _T("%03d"), timeSum);   // M.S 時間表示
		m_pFont->Draw(1010, 15, str, 48, RGB(255, 51, 0));  
	}
	//画面更新（バックバッファをフロントバッファに）
	m_pD3D->m_pSwapChain->Present(0, 0);
}
//M.S ゲームクリアのスコア処理
//引  数：なし
//戻り値：なし
void CGameMain::CalculateScore() {
	// アイテムのスコアを出す
	int SilverSum = 30 * SilverS;  // 銀箔
	int GoldSum = 100 * GoldS;     // 金箔
	int VisionSum = 200 * VisionS; // 幻の砂糖
	CountGameTime();   // ゲームクリア時の残り制限時間を出す
	SumP = SilverSum + GoldSum + VisionSum + timeSum;   // 合計スコアの計算
}
//------------------------------------------------------------------------
//
//	アプリケーションの終了処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::Quit()
{

}
//------------------------------------------------------------------------    // -- 2018.12.14
//
//	ウィンドウモードとフルスクリーンモードを切り替える処理	
//
//  引数　モード  0:ウインドウモード　1:フルスクリーン　-1:モード切り替え（省略値）
//
//	戻り値 なし
//
//------------------------------------------------------------------------
HRESULT CGameMain::ChangeScreenMode(int nMode)
{
	HRESULT Ret = S_OK;
	BOOL bFullScreen;  // フルスクリーンモードか？

	//	現在のスクリーンモードを得る
	m_pD3D->m_pSwapChain->GetFullscreenState(&bFullScreen, NULL);

	switch (nMode)
	{
	case 0:    // ウインドウモードにする
		if( bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		break;
	case 1:    // フルスクリーンモードにする
		if( !bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		break;
	default:   // 現在のモードを切り替える
		if (bFullScreen)
		{
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		}
		else {
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		}
	}

	return Ret;
}


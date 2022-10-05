//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//
//		ゲームのメイン処理
//																GameMain.cpp
//=============================================================================
#include "GameMain.h"
#include "Playchar.h"
#include "Camera.h"
#include "Enemy.h"
#include "Map.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"
#include "Title.h"

// ============================================================================================
//
// CGameMain ゲームメインクラスの処理
//
// ============================================================================================
//------------------------------------------------------------------------
//
//	ゲームメインクラスのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain*	pMain)
{
	ZeroMemory(this, sizeof(CGameMain));
	m_pMain = pMain;
	m_dwGameMode = 0;
	
	continuationFlag = false;   // M.S セーブデータがあるかどうかフラグ
	// M.S カーソルの位置
	cursolX = 0;
	cursolY = 0;
	// M.S 回転の処理が行われたフラグ
	rotateFlag = false;
	transparentSwitch = false;   // M.S プレイキャラの透明処理の判定
	initialH = 4;          // M.S プレイキャラのマスの初期値(縦)
	initialV = 4;          // M.S プレイキャラのマスの初期値(横)
	lineTrainSelectNum = 30;  // M.S プログラムで使用する線路数
	passengersSelectNum = 0;  // M.S プログラムで使用する乗車人数
	waitingTimeSelectNum = 0; // M.S プログラムで使用する待ち時間
	bgmSelectNum = 0;  // M.S プログラムで使用するBGM音量
	seSelectNum = 0;   // M.S プログラムで使用するSE音量
	traveledStar = 0;    // M.S 行った星の数
	haveToGoStar = 0;    // M.S 行かなければならない星の数
	redMan = 0;    // M.S ファイル読み込み、書き出しに使用する人数(赤)
	yellowMan = 0; // M.S ファイル読み込み、書き出しに使用する人数(黄)
	blueMan = 0;   // M.S ファイル読み込み、書き出しに使用する人数(青)
	rankOne = 1;   // M.S ファイル読み込み、書き出しに使用する1位のスコア数
	rankTwo = 2;   // M.S ファイル読み込み、書き出しに使用する2位のスコア数
	rankThree = 3; // M.S ファイル読み込み、書き出しに使用する3位のスコア数
	rankFour = 4;  // M.S ファイル読み込み、書き出しに使用する4位のスコア数
	rankFive = 5;  // M.S ファイル読み込み、書き出しに使用する5位のスコア数
	stopOperation = false;  // M.S ゲームの処理を止めるフラグ

	rankLineTrainSelectNum = 0;   // M.S ランキングモード時使用する線路数
	rankPassengersSelectNum = 0;  // M.S ランキングモード時使用する乗車人数
	rankWaitingTimeSelectNum = 0; // M.S ランキングモード時使用する待ち時間
	rankTraveledStar = 0; // M.S ランキングモード時使用する行った星の数
	rankHaveToGoStar = 0; // M.S ランキングモード時使用する行かなければならない星の数
	rankRedMan = 0;    // M.S ランキングモード時使用する人数(赤)
	rankYellowMan = 0; // M.S ランキングモード時使用する人数(黄)
	rankBlueMan = 0;   // M.S ランキングモード時使用する人数(青)
}
//------------------------------------------------------------------------
//
//	ゲームメインクラスのデストラクタ	
//
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{
	MyImgui::ImguiQuit();          // -- 2020.11.15    // MyImguiの終了処理

	SAFE_DELETE(titleBgm);
	SAFE_DELETE(gameBgm);
	SAFE_DELETE(gameClearBgm);
	SAFE_DELETE(resultBgm);
	SAFE_DELETE(gameOverBgm);

	SAFE_DELETE(turnThePageSound);
	SAFE_DELETE(selectSound);
	SAFE_DELETE(saveWarningSound);
	SAFE_DELETE(bornStarSound);
	SAFE_DELETE(goSound);
	SAFE_DELETE(timeCountSound);
	SAFE_DELETE(lineChangeSound);
	SAFE_DELETE(linePlacementSound);
	SAFE_DELETE(rideSound);
	SAFE_DELETE(saveOkSound);
	SAFE_DELETE(nextStarOkSound);
	
	SAFE_DELETE(m_pEnmProc);
	SAFE_DELETE(m_pPcProc);
	SAFE_DELETE(m_pCameraProc);
	SAFE_DELETE(m_pMapProc);
	SAFE_DELETE(m_pWeaponProc);
	SAFE_DELETE(m_pEffectProc);
	SAFE_DELETE(m_pBackForeProc);
	SAFE_DELETE(m_pTitleProc);

	SAFE_DELETE(m_pFbxMeshCtrl);    // -- 2021.2.4
	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDI);
	SAFE_DELETE(m_pXAudio);
	SAFE_DELETE(m_pD3D);

	SAFE_DELETE(m_pBox);

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
	m_pD3D->SetViewPort(false);   // M.S 1画面の表示
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

	// MyImguiの初期化
	MyImgui::ImguiInit(m_pMain->m_hWnd, m_pD3D, WINDOW_WIDTH, WINDOW_HEIGHT);           // -- 2020.11.15

	// Fbxメッシュコントロールクラス
	m_pFbxMeshCtrl = new CFbxMeshCtrl(m_pShader);                       // -- 2021.2.4

	// ----------------------------------------------------------------------------------------
	// 変数の初期化
	m_dwGameStatus = TITLE;
	m_vLightDir = normalize( VECTOR3(0.8f, 1, -1) );  // 光源座標の初期値。正規化する

	// プロジェクショントランスフォーム（射影変換）の初期値
	//m_mProj = XMMatrixPerspectiveFovLH((FLOAT)(XM_PI / 4), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);
	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);

	// ビュートランスフォーム（視点座標変換）の初期値
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f); //上方位置
	m_vEyePt = VECTOR3(0.0f, 1.0f, 0.0f);
	m_vLookatPt = VECTOR3(0.0f, 1.0f, 1.0f);
	m_mView = XMMatrixLookAtLH(m_vEyePt, m_vLookatPt, vUpVec);

	// 各プロシージャの初期化
	m_pPcProc = new CPcProc(this);		// ＰＣプロシージャ

	m_pCameraProc = new CCameraProc(this);	// カメラプロシージャ

	m_pEnmProc = new CEnmProc(this);	// 敵プロシージャ

	m_pEffectProc = new CEffectProc(this);  // ３Ｄ効果

	m_pWeaponProc = new CWeaponProc(this);	// Weaponプロシージャ

	m_pMapProc = new CMapProc(this);	// Mapプロシージャ

	m_pBackForeProc = new CBackForeProc(this);  // 前景・背景

	m_pTitleProc = new CTitleProc(this);  // タイトル。ゲームクリヤー。ゲームオーバー

	// M.S プラトレのBGMサウンド
	titleBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/startScene.mp3"));
	gameBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/game.mp3"));
	gameClearBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/gameClear.mp3"));
	resultBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/result.mp3"));
	gameOverBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/gameOver.mp3"));
	// M.S プラトレのSEサウンド
	turnThePageSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/turnThePage.mp3"));
	selectSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/selectButton.wav"));
	saveWarningSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/saveWarning.wav"));
	bornStarSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/starBorn.mp3"));
	goSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/goButton.wav"));
	timeCountSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/timeCount.wav"));
	lineChangeSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/lineSelectButton.mp3"));
	linePlacementSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/placement.wav"));
	rideSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/ride.wav"));
	saveOkSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/saveOk.wav"));
	nextStarOkSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/nextStarOk.mp3"));
	FileRead();  // M.S ファイルの読み込み
	// M.S セーブデータがあるかどうか
	for (int i = 0; i < 25; i++) {
		if (starArray[i] != 0) {
			continuationFlag = true; 
			break;
		}
		else {
			continuationFlag = false;
		}
	}
	m_pTitleProc->ChangeSelect(); // M.S オプション画面で使う数字へ変換
	titleBgm->Play(AUDIO_LOOP);   // M.S 音楽再生
	// M.S 読み込んだファイルから音声のボリュームを設定
	SetSoundVolume();
	SetBgmVolume();
	return S_OK;
}

//------------------------------------------------------------------------
//
//	ゲームのループ処理	
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
	MyImgui::ImguiNewFrame();   // MyImgui描画前処理    // -- 2020.11.15
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

	MyImgui::ImguiRender();      // MyImgui実描画処理    // -- 2020.11.15

	//画面更新（バックバッファをフロントバッファに）
	//m_pD3D->m_pSwapChain->Present(1, 0);                   // 60fps Vsync
	m_pD3D->m_pSwapChain->Present(0, 0);                   // Vsyncなし
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
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア
	m_pD3D->SetViewPort(false);     // M.S 1画面の表示
	// M.S マップナンバーによってカメラの位置を決める
	switch (m_pMapProc->MapNumGet()) {
	case 1:
		m_pCameraProc->GetCameraObjPtr()->cameraChangeSwitch = 0;
		break;
	case 2:
		m_pCameraProc->GetCameraObjPtr()->cameraChangeSwitch = 2;
		break;
	case 3:
		m_pCameraProc->GetCameraObjPtr()->cameraChangeSwitch = 3;
		break;
	}
	// M.S Cameraの更新
	m_pCameraProc->UpdateAll();
	// Mapの更新
	m_pMapProc->Update();
	// ＰＣの更新
	m_pPcProc->UpdateAll();
	// 敵の更新
	m_pEnmProc->UpdateAll();
	// 武器の更新
	m_pWeaponProc->UpdateAll();
	// ３Ｄ効果の更新
	m_pEffectProc->UpdateAll();
	// Mapの描画2
	// 半透明のマップオブジェクトを描画するため、主ループの最後に実行
	m_pMapProc->Render2();
	// 前景・背景の更新
	m_pBackForeProc->Update();
	// M.S マップナンバーが2(線路配置画面)かつ1画面フラグがfalseの場合
	if (m_pMapProc->MapNumGet() == 2 && m_pPcProc->oneScreenFlag == false) {
		m_pD3D->SetViewPort(true);  // 分割画面の表示
		// M.S 分割画面の描画
		m_pCameraProc->GetCameraObjPtr()->cameraChangeSwitch = 1;
		m_pCameraProc->UpdateAll();
		// M.S Mapの描画
		m_pMapProc->Render();
		m_pMapProc->Render2();
		m_pMapProc->TrainLST->RenderLine(m_pMapProc->trainNumSt, m_pMapProc->trainNumSd,
			m_pMapProc->trainNumCg, m_pMapProc->trainNumSta, this); // M.S 線路の描画
		// M.S 人キャラ(赤)を順に見る
		for (int i = 0; i < m_pEnmProc->m_pEnmGolemProc->manNum; i++) {
			// M.S アニメーションを止める
			m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->SetPlayAnimHigh(false);
			// M.S 人キャラが乗車していないかどうか
			if (m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->alive == true) {
				// M.S 人キャラの描画
				m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->DoRenderHigh();
			}
		}
		// M.S 人キャラ(黄)を順に見る
		for (int i = 0; i < m_pEnmProc->m_pEnmRSProc->manNum; i++) {
			// M.S アニメーションを止める
			m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->SetPlayAnimMiddle(false);
			// M.S 人キャラが乗車していないかどうか
			if (m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->alive == true) {
				// M.S 人キャラの描画
				m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->DoRenderMiddle();
			}
		}
		// M.S 人キャラ(青)を順に見る
		for (int i = 0; i < m_pEnmProc->m_pEnmBdProc->manNum; i++) {
			// M.S アニメーションを止める
			m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->SetPlayAnimLow(false);
			// M.S 人キャラが乗車していないかどうか
			if (m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->alive == true) {
				// M.S 人キャラの描画
				m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->DoRenderLow();
			}
		}
		// M.S 人キャラ(赤)を順に見る
		for (int i = 0; i < m_pEnmProc->m_pEnmGolemProc->manNum; i++) {
			// M.S アニメ―ションの再開
			m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->SetPlayAnimHigh(true);
		}
		// M.S 人キャラ(黄)を順に見る
		for (int i = 0; i < m_pEnmProc->m_pEnmRSProc->manNum; i++) {
			// M.S アニメ―ションの再開
			m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->SetPlayAnimMiddle(true);
		}
		// M.S 人キャラ(青)を順に見る
		for (int i = 0; i < m_pEnmProc->m_pEnmBdProc->manNum; i++) {
			// M.S アニメ―ションの再開
			m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->SetPlayAnimLow(true);
		}
		// M.S ＰＣのアニメーションを止める
		m_pPcProc->GetPcObjPtr()->SetPlayAnim(false);
		// M.S ＰＣの描画
		m_pPcProc->GetPcObjPtr()->DoRender();
		// M.S 線路のキラキラエフェクトの描画
		m_pEffectProc->m_pBillProc->Render();
		// M.S ＰＣのアニメーションを再開
		m_pPcProc->GetPcObjPtr()->SetPlayAnim(true);
	}
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
	;
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
//M.S ファイルへデータを書き込む
//引  数：なし
//戻り値：なし
void CGameMain::FileWrite() {
	// ランキングモードでなく、マップナンバーが3(星の架け橋画面)だった場合
	if (m_dwGameMode != 3 && m_pMapProc->MapNumGet() == 3) {
		// 書き込み用変数に各乗車人数を入れる
		redMan = m_pEnmProc->getHighMan;
		yellowMan = m_pEnmProc->getMiddleMan;
		blueMan = m_pEnmProc->getLowMan;
	}
	// 書き込みモードでファイルを開く
	dataFileWrite = fopen("gameData.txt", "w");
	// 次の星までの線路数、乗車人数、待ち時間、BGM音量、SE音量を書き込む
	fprintf(dataFileWrite, "%d,%d,%d,%f,%f\n", lineTrainSelectNum, passengersSelectNum, waitingTimeSelectNum, 
		bgmSelectNum, seSelectNum);
	// 行った星数、行かなければならない星数を書き込む
	fprintf(dataFileWrite, "%d,%d\n", traveledStar, haveToGoStar);
	// 動的生成した星配列を書き込む
	for (int i = 0; i < 25; i++) {
		if (i < 24) {
		fprintf(dataFileWrite, "%d,", starArray[i]);
		}
		else {
			// 最後は改行させる
			fprintf(dataFileWrite, "%d\n", starArray[i]);
		}
	}
	// 各人の乗車人数を書き込む
	fprintf(dataFileWrite, "%d,%d,%d\n", redMan, yellowMan, blueMan);
	// ランキングスコアを書き込む
	fprintf(dataFileWrite, "%d,%d,%d,%d,%d\n", rankOne, rankTwo, rankThree, rankFour, rankFive);
	fclose(dataFileWrite);  // ファイルを閉じる
}
//M.S ファイルのデータを読み込む
//引  数：なし
//戻り値：なし
void CGameMain::FileRead() {
	// 読み込みモードでファイルを開く
	dataFileWrite = fopen("gameData.txt", "r");
	// 次の星までの線路数、乗車人数、待ち時間、BGM音量、SE音量を読み込む
	fscanf(dataFileWrite, "%d,%d,%d,%f,%f", &lineTrainSelectNum, &passengersSelectNum, &waitingTimeSelectNum,
		&bgmSelectNum, &seSelectNum);
	// 行った星数、行かなければならない星数を読み込む
	fscanf(dataFileWrite, "%d,%d", &traveledStar, &haveToGoStar);
	// 動的生成した星配列を読み込む
	fscanf(dataFileWrite, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&starArray[0], &starArray[1], &starArray[2], &starArray[3], &starArray[4], &starArray[5], &starArray[6],
		&starArray[7], &starArray[8], &starArray[9], &starArray[10], &starArray[11], &starArray[12], &starArray[13],
		&starArray[14], &starArray[15], &starArray[16], &starArray[17], &starArray[18], &starArray[19], &starArray[20],
		&starArray[21], &starArray[22], &starArray[23], &starArray[24]);
	// 各人の乗車人数を読み込む
	fscanf(dataFileWrite, "%d,%d,%d", &redMan, &yellowMan, &blueMan);
	// ランキングスコアを読み込む
	fscanf(dataFileWrite, "%d,%d,%d,%d,%d", &rankOne, &rankTwo, &rankThree, &rankFour, &rankFive);
	fclose(dataFileWrite);  // ファイルを閉じる
}
//M.S 効果音に音量を設定
//引  数：なし
//戻り値：なし
void  CGameMain::SetSoundVolume() {
	// 効果音に音量を設定
    selectSound->Volume(seSelectNum);
	turnThePageSound->Volume(seSelectNum);
	saveWarningSound->Volume(seSelectNum);
	bornStarSound->Volume(seSelectNum);
	goSound->Volume(seSelectNum);
	timeCountSound->Volume(seSelectNum);
	lineChangeSound->Volume(seSelectNum);
	linePlacementSound->Volume(seSelectNum);
	rideSound->Volume(seSelectNum);
	saveOkSound->Volume(seSelectNum);
	nextStarOkSound->Volume(seSelectNum);
}
//M.S BGMに音量を設定
//引  数：なし
//戻り値：なし
void  CGameMain::SetBgmVolume() {
	// BGMに音量を設定
	titleBgm->Volume(bgmSelectNum);
	gameBgm->Volume(bgmSelectNum);
	gameClearBgm->Volume(bgmSelectNum);
	resultBgm->Volume(bgmSelectNum);
	gameOverBgm->Volume(bgmSelectNum);
}
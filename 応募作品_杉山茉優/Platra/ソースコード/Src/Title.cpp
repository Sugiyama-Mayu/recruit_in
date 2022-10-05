//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        201.1.11
//		タイトル・ゲームクリヤー・ゲームオーバーの処理
//																Title.cpp
//=============================================================================
#include  "Title.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Enemy.h"
#include  "BackFore.h"

//============================================================================
//
// タイトルプロシージャのコンストラクタ
//
// ---------------------------------------------------------------------------
CTitleProc::CTitleProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_pImageTitle = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/TITLE.png")); // イメージのロード
	m_pImageOption = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/option.png")); // イメージのロード
	// あそびかた画面のページ
	m_pImagePage1 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P1.png")); // イメージのロード
	m_pImagePage2 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P2.png")); // イメージのロード
	m_pImagePage3 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P3.png")); // イメージのロード
	m_pImagePage4 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P4.png")); // イメージのロード
	m_pImagePage5 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P5.png")); // イメージのロード
	m_pImagePage6 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P6.png")); // イメージのロード
	m_pImagePage7 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P7.png")); // イメージのロード
	m_pImagePage8 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P8.png")); // イメージのロード
	// あそびかた画面のページ移動ボタン
	m_pImagePageButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/orangeButton.png")); // イメージのロード
	// 使用する画像のロード
	m_pImageClear = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_GAMECLEAR.png")); // イメージのロード
	m_pImageOver  = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_GAMEOVER.png")); // イメージのロード
	m_pSprite = new CSprite(m_pGMain->m_pShader); // スプライトの生成
	m_pImageSelect = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/TitleSelect.png")); // イメージのロード
	m_pImageOptionNum = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/optionNumTex.png")); // イメージのロード
	m_pImageOptionBackButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/option_BackButton.png")); // イメージのロード
	m_pImageResult = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_RESULT.png")); // イメージのロード
	m_pImageRanking = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_RANKING.png")); // イメージのロード
	m_pImageSaveWarning = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/saveWarning.png")); // イメージのロード
	m_pImageNoSave = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/noSaveDatapng.png")); // イメージのロード
	m_pImageGreenButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/greenButton.png")); // イメージのロード
	m_dwCntTime = 0;
	nTitleSelect = 0;

	linetrainNum = 0;      // M.S 線路の選択数字
	passengersNum = 0;     // M.S 乗車人数の選択数字
	waitingTime = 0;       // M.S 待ち時間の選択数字
	bgmNum = 0;            // M.S BGM音量の選択数字
	seNum = 0;             // M.S SE音量の選択数字
	lineTrainSelect = 0;     // M.S 線路の選択決定数字
	passengersSelect = 4;    // M.S 乗車人数の選択決定数字
	waitingTimeSelect = 10;  // M.S 待ち時間の選択決定数字
	bgmSelect = 16;          // M.S BGM音量の選択決定数字
	seSelect = 22;           // M.S SE音量の選択決定数字
	selectedKindNum = 0;     // M.S オプション画面のボタンの列の数字

	rankingTime = 0;               // M.S ランキング画面のタイムカウント
	myRanking = 0;                 // M.S 自分のランキング
	totalScore = 0;                // M.S トータルスコア
	initialRankingSorting = true;  // M.S 1度のみランキング並び替えフラグ
	ScoreWriteProcess = false;  // M.S ファイル書き込みフラグ
	saveWarningFlag = false;    // M.S セーブデータある注意フラグ
	noSaveFlag = false;         // M.S セーブデータない注意フラグ
	nowPage = 0;                  // M.S 操作説明で選択中のページ

	gameClearCount = 0;          // M.S ゲームクリアタイムカウント
	gameOverCount = 0;           // M.S ゲームオーバータイムカウント
	// M.S BGM鳴らすフラグの初期化
	RingSound = false;
	RingResultSound = false;
}
// ---------------------------------------------------------------------------
//
// タイトルタイトルプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CTitleProc::~CTitleProc()
{
	// 使用した画像
	SAFE_DELETE(m_pImageTitle);
	SAFE_DELETE(m_pImageOption);
	SAFE_DELETE(m_pImageClear);
	SAFE_DELETE(m_pImageOver);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pImageSelect);
	SAFE_DELETE(m_pImageOptionNum);
	SAFE_DELETE(m_pImageOptionBackButton);
	SAFE_DELETE(m_pImageResult);
	SAFE_DELETE(m_pImageRanking);
	SAFE_DELETE(m_pImageSaveWarning);
	SAFE_DELETE(m_pImageNoSave);
	SAFE_DELETE(m_pImageGreenButton);
	// あそびかた画面のページ
	SAFE_DELETE(m_pImagePage1);
	SAFE_DELETE(m_pImagePage2);
	SAFE_DELETE(m_pImagePage3);
	SAFE_DELETE(m_pImagePage4);
	SAFE_DELETE(m_pImagePage5);
	SAFE_DELETE(m_pImagePage6);
	SAFE_DELETE(m_pImagePage7);
	SAFE_DELETE(m_pImagePage8);
	// あそびかた画面のページボタン
	SAFE_DELETE(m_pImagePageButton);
}
//------------------------------------------------------------------------
//
//	タイトルの表示	
//
//------------------------------------------------------------------------
void CTitleProc::Title()
{
	switch (m_dwStatusPhase)
	{
	case 0:    // フェーズ１  ゲームモードを選ぶ
		//M.S タイトルセレクト
		TitleSelect();
		break;
	case 1:    // フェーズ２  ゲーム開始かオプション画面	
		switch (m_pGMain->m_dwGameMode) {
		case 1:
			// M.S はじめから
			// M.S タイトルBGMを止める
			m_pGMain->titleBgm->Stop();
			// M.S ゲームBGMを流す
			m_pGMain->gameBgm->Play(AUDIO_LOOP);
			// M.S 星の生成変数の初期化
			m_pGMain->traveledStar = 0;
			m_pGMain->haveToGoStar = 0;
			m_pGMain->starArray[25] = { 0 };
			// M.S 人キャラの乗車人数変数の初期化
			m_pGMain->redMan = 0;
			m_pGMain->yellowMan = 0;
			m_pGMain->blueMan = 0;
			m_pGMain->m_pEnmProc->getHighMan = m_pGMain->redMan;
			m_pGMain->m_pEnmProc->getMiddleMan = m_pGMain->yellowMan;
			m_pGMain->m_pEnmProc->getLowMan = m_pGMain->blueMan;
			// M.S マップ1のロード
			m_pGMain->m_pMapProc->LoadMap1();
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			break;
		case 2:
			// M.S 続きから
			// M.S タイトルBGMを止める
			m_pGMain->titleBgm->Stop();
			// M.S ゲームBGMを流す
			m_pGMain->gameBgm->Play(AUDIO_LOOP);
			// M.S ファイルから読み込んだ乗車人数を変数へ入れる
			m_pGMain->m_pEnmProc->getHighMan = m_pGMain->redMan;
			m_pGMain->m_pEnmProc->getMiddleMan = m_pGMain->yellowMan;
			m_pGMain->m_pEnmProc->getLowMan = m_pGMain->blueMan;
			// M.S マップ2のロード
			m_pGMain->m_pMapProc->LoadMap2();
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			break;
		case 3:
			// M.S ランキングモード
			// M.S タイトルBGMを止める
			m_pGMain->titleBgm->Stop();
			// M.S ゲームBGMを流す
			m_pGMain->gameBgm->Play(AUDIO_LOOP);
			// M.S セーブデータに書き込み、読み込みしない
			// M.S ランキング用の変数を使用
			m_pGMain->rankLineTrainSelectNum = 30;
			m_pGMain->rankPassengersSelectNum = 3;
			m_pGMain->rankWaitingTimeSelectNum = 3;
			m_pGMain->rankTraveledStar = 0;
			m_pGMain->rankHaveToGoStar = 5;  // M.S 5つの星を渡る
			m_pGMain->rankRedMan = 0;
			m_pGMain->rankYellowMan = 0;
			m_pGMain->rankBlueMan = 0;
			// M.S マップ2のロード
			m_pGMain->m_pMapProc->LoadMap2();
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			break;
		}
	case 2:
		//M.S オプション画面
		TitleOption();
		break;
	case 3:
		//M.S ランキング確認画面
		DrawRanking();
		break;
	case 4:
		// M.S 操作方法の説明画面
		TitleExplanation();
		break;
	}
}
bool CTitleProc::TitleTitle()
{
	BOOL bRet = FALSE;

	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	// フォント名　"_T(ＤＦ勘亭流")，_T("ＭＳ Ｐゴシック")，_T("ＭＳ ゴシック")，_T("HGP創英角ﾎﾟｯﾌﾟ体")，_T("HGP創英角ｺﾞｼｯｸUB")
	m_pGMain->m_pFont->Draw(253, 53, _T("３Ｄアクションゲーム"), 90, RGB(0, 0, 0), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	m_pGMain->m_pFont->Draw(250, 50, _T("３Ｄアクションゲーム"), 90, RGB(255, 0, 0), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));

	m_pGMain->m_pFont->Draw(WINDOW_WIDTH - 200, 20, _T("C3DAct112"), 30, RGB(192, 0, 0), 1.0f, _T("HGP創英角ｺﾞｼｯｸUB"));
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH - 250, 130, _T("DirectX11対応"), 30, RGB(0, 0, 64), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
	return bRet;
}
// M.S オプション画面で設定した数字をプログラムで使用する数字に変換
//引  数：int bgmOrSeNum 0:すべての処理をする 1:BGMの処理のみ 2:SEの処理のみ
//戻り値：なし
void CTitleProc::ChangeSelectNum(int bgmOrSeNum) {
	// bgmOrSeNum:0 すべての処理をする 1:BGMのみ 2:SEのみ
	// オプション画面のボタンからプログラムで使用する数字への変換
	switch (bgmOrSeNum) {
	case 0:
		// 線路数の変換
		switch (lineTrainSelect) {
		case 0:
			m_pGMain->lineTrainSelectNum = 30;
			break;
		case 1:
			m_pGMain->lineTrainSelectNum = 50;
			break;
		case 2:
			m_pGMain->lineTrainSelectNum = 70;
			break;
		case 3:
			m_pGMain->lineTrainSelectNum = 80;
		}
		// 乗車人数の変換
		switch (passengersSelect) {
		case 4:
			m_pGMain->passengersSelectNum = 0;
			break;
		case 5:
			m_pGMain->passengersSelectNum = 3;
			break;
		case 6:
			m_pGMain->passengersSelectNum = 6;
			break;
		case 7:
			m_pGMain->passengersSelectNum = 9;
			break;
		case 8:
			m_pGMain->passengersSelectNum = 12;
			break;
		case 9:
			m_pGMain->passengersSelectNum = 18;
		}
		// 発射までの待ち時間の変換
		for (int i = 10; i < 16; i++) {
			if (waitingTimeSelect == i) {
				m_pGMain->waitingTimeSelectNum = i - 10;
				break;
			}
		}
		// BGM音量の変換
		for (int i = 16; i < 22; i++) {
			if (bgmSelect == i) {
				m_pGMain->bgmSelectNum = (i - 16) * 0.2;
				break;
			}
		}
		// SE音量の変換
		for (int i = 22; i < 28; i++) {
			if (seSelect == i) {
				m_pGMain->seSelectNum = (i - 22) * 0.2;
				break;
			}
		}
		break;
	case 1:  // BGM音量の変換
		for (int i = 16; i < 22; i++) {
			if (bgmSelect == i) {
				m_pGMain->bgmSelectNum = (i - 16) * 0.2;
				break;
			}
		}
		break;
	case 2:  // SE音量の変換
		for (int i = 22; i < 28; i++) {
			if (seSelect == i) {
				m_pGMain->seSelectNum = (i - 22) * 0.2;
				break;
			}
		}
		break;
	}
}
// M.S プログラムで使用する数字をオプション画面で設定した数字へ変換
//引  数：なし
//戻り値：なし
void CTitleProc::ChangeSelect() {
	// 線路数の変換
	switch (m_pGMain->lineTrainSelectNum) {
	case 30:
		lineTrainSelect = 0;
		break;
	case 50:
		lineTrainSelect = 1;
		break;
	case 70:
		lineTrainSelect = 2;
		break;
	case 80:
		lineTrainSelect = 3;
	}
	// 乗車人数の変換
	switch (m_pGMain->passengersSelectNum) {
	case 0:
		passengersSelect = 4;
		break;
	case 3:
		passengersSelect = 5;
		break;
	case 6:
		passengersSelect = 6;
		break;
	case 9:
		passengersSelect = 7;
		break;
	case 12:
		passengersSelect = 8;
		break;
	case 18:
		passengersSelect = 9;
	}
	// 発射までの待ち時間の変換
	for (int i = 0; i < 6; i++) {
		if (m_pGMain->waitingTimeSelectNum == i) {
			waitingTimeSelect = i + 10;
			break;
		}
	}
	// BGM音量の変換
	int bgmBuf = m_pGMain->bgmSelectNum * 10;
	for (int i = 0; i < 6; i++) {
		if (bgmBuf == i * 2) {
			bgmSelect = i + 16;
			break;
		}
	}
	// SE音量の変換
	int seBuf = m_pGMain->seSelectNum * 10;
	for (float i = 0; i < 6; i++) {
		if (seBuf == i * 2) {
			seSelect = i + 22;
			break;
		}
	}
}
// M.S はじめからを選択した時のセーブデータがあると知らせる注意表示
//引  数：なし
//戻り値：bool trueの場合、OKボタンを押しゲーム開始に進んだ
bool CTitleProc::DrawSaveWarning() {
	bool bRet = false;               
	int saveWarningTextPosX = 373;    // セーブデータある注意表示テキストのX位置
	int saveWarningTextPosY = 182;    // セーブデータある注意表示テキストのY位置
	int saveWarningTextWidth = 620;   // セーブデータある注意表示テキストの幅
	int saveWarningTextHeight = 378;  // セーブデータある注意表示テキストの高さ
	int saveWarningOkPosX = 486;      // OKボタンのX位置
	int saveWarningOkPosY = 474;  // ボタンのY位置
	int saveWarningBackPosX = 709;    // 戻るボタンのX位置
	int saveWarningBackPosY = 474;  // ボタンのY位置
	int saveWarningButtonWidth = 173; // ボタンの幅
	int saveWarningButtonHeight = 70; // ボタンの高さ
	float lightColor = 0.5f;          // 薄い色で表示する透明度
	// セーブデータある注意表示フラグがtrueかどうか
	if (saveWarningFlag == true) {
		// セーブデータある注意テキスト表示
		m_pSprite->Draw(m_pImageSaveWarning, saveWarningTextPosX,
			saveWarningTextPosY, 0, 0, saveWarningTextWidth, saveWarningTextHeight);
		// OKボタンを選択中かどうか
		if (CheckMousePos(saveWarningOkPosX, saveWarningOkPosY,
			saveWarningButtonWidth, saveWarningButtonHeight) == true)
		{
			// 選択中ボタンを表示
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningOkPosX, saveWarningOkPosY,
				0, 378, saveWarningButtonWidth, saveWarningButtonHeight);
			// 選択中でないボタン薄い色で表示
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningBackPosX, saveWarningOkPosY,
				173, 378, saveWarningButtonWidth, saveWarningButtonHeight, lightColor);
			// 決定したかどうか
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE)
				|| m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				m_pGMain->selectSound->Play();  // 効果音の発生
				saveWarningFlag = false; // セーブデータある注意表示フラグをfalse
				//noSaveFlag = false;
				m_dwStatusPhase = 1;            // ゲーム開始フェーズへ
				m_pGMain->m_dwGameMode = 1;     // はじめから
				bRet = TRUE;  // 終了
			}
		}
		// 戻るボタンを選択中かどうか
		else if (CheckMousePos(saveWarningBackPosX, saveWarningBackPosY,
			saveWarningButtonWidth, saveWarningButtonHeight) == true) {
			// 選択中ボタンを表示
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningBackPosX, saveWarningBackPosY,
				173, 378, saveWarningButtonWidth, saveWarningButtonHeight);
			// 選択中でないボタン薄い色で表示
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningOkPosX, saveWarningBackPosY,
				0, 378, saveWarningButtonWidth, saveWarningButtonHeight, lightColor);
			// 決定したかどうか
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE)
				|| m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				m_pGMain->selectSound->Play();  // 効果音の発生
				saveWarningFlag = false; // セーブデータある注意表示フラグをfalse
			}
		}
		else {
			// ボタンを選択していない場合、ボタンを薄い色で表示
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningOkPosX, saveWarningOkPosY,
				0, 378, saveWarningButtonWidth, saveWarningButtonHeight, lightColor);
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningBackPosX, saveWarningBackPosY,
				173, 378, saveWarningButtonWidth, saveWarningButtonHeight, lightColor);
		}
	}
	return bRet;
}
// M.S つづきからを選択した時のセーブデータがないと知らせる注意表示
//引  数：なし
//戻り値：なし
void CTitleProc::DrawNoSaveDataWarning() {
	int saveWarningTextPosX = 373;    // セーブデータない注意表示テキストのX位置
	int saveWarningTextPosY = 102;    // セーブデータない注意表示テキストのY位置
	int saveWarningTextWidth = 620;   // セーブデータない注意表示テキストの幅
	int saveWarningTextHeight = 378;  // セーブデータない注意表示テキストの高さ
	int saveWarningBackPosX = 607;    // 戻るボタンのX位置
	int saveWarningBackPosY = 394;    // 戻るボタンのY位置
	int saveWarningBackWidth = 173;   // 戻るボタンの幅
	int saveWarningBackHeight = 70;   // 戻るボタンの高さ
	float lightColor = 0.5f;          // 薄い色で表示する透明度
	// セーブデータない注意表示フラグがtrueかどうか
	if (noSaveFlag == true) {
		// セーブデータない注意表示テキスト表示
		m_pSprite->Draw(m_pImageNoSave, saveWarningTextPosX, saveWarningTextPosY, 0, 0, saveWarningTextWidth, saveWarningTextHeight);
		// 戻るボタンを選択中かどうか
		if (CheckMousePos(saveWarningBackPosX, saveWarningBackPosY, saveWarningBackWidth, saveWarningBackHeight) == true)
		{
			// 選択中ボタンを表示
			m_pSprite->Draw(m_pImageNoSave, saveWarningBackPosX, saveWarningBackPosY, 0, 378, saveWarningBackWidth, saveWarningBackHeight);
			// 決定したかどうか
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE)
				|| m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				m_pGMain->selectSound->Play(); // 効果音の発生
				noSaveFlag = false;  // セーブデータない注意表示フラグをfalse
			}
		}
		else {
			// ボタンを選択していない場合、ボタンを薄い色で表示
			m_pSprite->Draw(m_pImageNoSave, saveWarningBackPosX, saveWarningBackPosY, 0, 378, saveWarningBackWidth, saveWarningBackHeight, lightColor);
		}
	}
}
// M.S あそびかたボタンとランキング確認ボタンの表示、選択処理
//引  数：なし
//戻り値：bool trueの場合、選択した画面に進んだ
bool CTitleProc::DrawHowToPlayRanking() {
	bool bRet = false;
	int howToPlayCursorButtonPosX = 905; // あそびかたボタン選択範囲のX位置
	int howToPlayCursorButtonPosY = 644; // あそびかたボタン選択範囲のY位置
	int rankingCursorButtonPosX = 1130;  // ランキング確認ボタン選択範囲のX位置
	int rankingCursorButtonPosY = 644;   // ランキング確認ボタン選択範囲のY位置
	int buttonCursorWidth = 201;         // ボタンの選択範囲の幅
	int buttonCursorHeight = 101;        // ボタンの選択範囲の高さ
	int howToPlayButtonPosX = 893;       // あそびかたボタンのX位置
	int howToPlayButtonPosY = 634;       // あそびかたボタンのY位置
	int rankingButtonPosX = 1118;  // ランキング確認ボタンのX位置
	int rankingButtonPosY = 634;   // ランキング確認ボタンのY位置
	int buttonWidth = 225;               // ボタンの幅
	int buttonHeight = 122;              // ボタンの高さ	
	float lightColor = 0.5f;             // 薄い色で表示する透明度
	// あそびかたモード
	// あそびかたボタンを選択しているかどうか
	if (CheckMousePos(howToPlayCursorButtonPosX, howToPlayCursorButtonPosY,
		buttonCursorWidth, buttonCursorHeight) == true)
	{
		m_pSprite->
			Draw(m_pImageGreenButton, howToPlayButtonPosX, howToPlayButtonPosY,
				0, 0, buttonWidth, buttonHeight);  		// あそびかたボタンを表示
		// 決定したかどうか
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
		{
			m_pGMain->selectSound->Play(); // 選択効果音
			m_dwStatusPhase = 4; // 操作方法の説明画面
			bRet = TRUE;  // 終了
			return bRet;
		}
	}
	else {
		// 選択していないのであそびかたボタンを薄い色で表示
		m_pSprite->
			Draw(m_pImageGreenButton, howToPlayButtonPosX, howToPlayButtonPosY,
				0, 0, buttonWidth, buttonHeight, lightColor);  	 
	}
	// ランキング確認モード
	// ランキング確認ボタンを選択しているかどうか
	if (CheckMousePos(rankingCursorButtonPosX, rankingCursorButtonPosY,
		buttonCursorWidth, buttonCursorHeight) == true)
	{
		m_pSprite->
			Draw(m_pImageGreenButton, rankingButtonPosX, rankingButtonPosY,
				225, 0, buttonWidth, buttonHeight);  // ランキング確認ボタンを表示
		// 決定したかどうか
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
		{
			m_pGMain->selectSound->Play(); // 選択効果音
			m_dwStatusPhase = 3; // ランキング確認画面
			bRet = TRUE;  // 終了
			return bRet;
		}
	}
	else {
		// 選択していないのでランキング確認ボタンを薄い色で表示
		m_pSprite->
			Draw(m_pImageGreenButton, rankingButtonPosX, rankingButtonPosY,
				225, 0, buttonWidth, buttonHeight, lightColor);
	}
	return bRet;
}
// M.S タイトルセレクト画面の表示、選択処理
//引  数：なし
//戻り値：bool true タイトルセレクト画面の終了
bool CTitleProc::TitleSelect()
{
	BOOL bRet = FALSE;
	const int nNum = 4;   // セレクトボタンの数
	const float fScale = 1.2f;
	// セレクトボタンのX、Y位置
	const int nStartX = 502, nStartY = 384;
	// セレクトボタンの幅、高さ
	const int nWidth = 362, nHeight = 95;
	// セレクトボタンの拡大した幅、高さ
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// 薄い色で表示する透明度
	float lightColor = 0.5f;             
	int i;
	// 画面の表示
	m_pSprite->
		Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth,
			m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	// あそびかたボタンとランキング確認ボタンの表示、選択処理
	bRet = DrawHowToPlayRanking();
	// あそびかたボタンかランキング確認ボタンが押されたかどうか
	if (bRet == TRUE) {
		return bRet;  		// 終了
	}
	// 4つのセレクトボタンを順に調べる
	for (i = 0; i < nNum; i++)
	{
		// マウスカーソルが調べているセレクトボタン内あるかどうか
		if (CheckMousePos(nStartX, nStartY + (nHeight * i), nWidth, nHeight) == true)
		{
			nTitleSelect = i;   //調べているセレクトボタンの数字をnTitleSelectに入れる
			break;
		}
		else {
			nTitleSelect = 10;  // カーソル内にない場合
		}
	}
	// セレクトボタンの表示
	for (i = 0; i < nNum; i++)
	{
		if (nTitleSelect == i)
		{
			// 選択中のボタン
			m_pSprite->Draw(m_pImageSelect, nStartX - 35, nStartY + (nHeight * i),
				0, 0 + (nHeight * i), nWidth, nHeight, nWidthScale, nHeightScale);	
		}
		else {
			// 選択していなボタン
			m_pSprite->Draw(m_pImageSelect, nStartX, nStartY + (nHeight * i),
				0, 0 + (nHeight * i), nWidth, nHeight, lightColor);
		}
	}
	// 終了キー
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) 
		|| m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) 
		|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
		// はじめからかつセーブデータがあるかどうか
		if (nTitleSelect == 0 && m_pGMain->continuationFlag == true) {
			m_pGMain->saveWarningSound->Play(); // 注意効果音
		    saveWarningFlag = true;   // セーブデータある注意表示フラグをtrue
		}
		// つづきからかつセーブデータが無いかどうか
		else if (nTitleSelect == 1 && m_pGMain->continuationFlag == false) {
			m_pGMain->saveWarningSound->Play(); // 注意効果音
			noSaveFlag = true;    // セーブデータない注意表示フラグをtrue 
		}
		else if (saveWarningFlag == false && noSaveFlag == false) {
			saveWarningFlag = false;         // 注意フラグの初期化
			noSaveFlag = false;
			// オプションを選択していない、かつボタン外を選択していないかどうか
			if (nTitleSelect != 3 && nTitleSelect != 10) {
				m_pGMain->selectSound->Play();   // 選択効果音
				// ゲーム開始フェーズへ
				m_dwStatusPhase = 1;
				// 選んだゲームモードへ
				m_pGMain->m_dwGameMode = nTitleSelect + 1;
			}
			// オプションを選択したかどうか
			else if(nTitleSelect == 3){
				m_pGMain->selectSound->Play();   // 選択効果音
				// オプション画面へ
				m_dwStatusPhase = 2;
			}
			bRet = TRUE;  // 終了
			return bRet;
		}
	}
	bRet = DrawSaveWarning();// セーブデータある注意表示
	// セーブデータある注意表示でOKを押され、ゲーム開始になっているかどうか
	if (bRet == TRUE) {
		return bRet;  		// 終了
	}
	DrawNoSaveDataWarning(); // セーブデータない注意表示
	return bRet;
}
// M.S オプション画面の線路数ボタン数字の表示、選択処理
//引  数：なし
//戻り値：なし
void CTitleProc::SelectLineNum(bool judgeRange, int selectKind, int i) {
	// 線路数
	const float fScale = 1.2f; // 表示ボタンの拡大値 
	// 表示位置のX、Y位置
	const int nStartX = 690, nStartY = 80;
	// ボタンの幅、高さ
	const int nWidth = 50, nHeight = 50;
	// 拡大したボタンの幅、高さ
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// 薄い色で表示する透明度
	float lightColor = 0.5f;
	// 選択し決定しているボタンかどうか
	if (lineTrainSelect == i) {
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // 表示する色を赤色にする
		m_pSprite->Draw(m_pImageOptionNum, nStartX + (i * 70), nStartY, 
			i * 50, 50, nWidth, nHeight, 1.0f);  // 色を変えて表示
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // 色を元に戻す
	}
	else {
		// selectKindは他のオプションの列の数(ボタン)に反応させないため
		// judgeRangeは現在カーソル内かどうかかつ
		// カーソル内にある数字(ボタン)かどうか
		if (linetrainNum == i && selectKind == 1 && judgeRange == true) {  
			m_pSprite->Draw(m_pImageOptionNum, nStartX + (i * 70), nStartY,
				i * 50, 50, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
			// カーソル内かつ選択しているかどうか
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				// 選択中の数字の更新
				lineTrainSelect = i;
				m_pGMain->selectSound->Play(); // 選択効果音
			}
		}
		else {
			// 選択中でもなくカーソルもあっていない数字の描画
			m_pSprite->Draw(m_pImageOptionNum, nStartX + (i * 70), nStartY, 
				i * 50, 50, nWidth, nHeight, lightColor);  // 薄い色で表示
		}
	}
}
// M.S オプション画面の乗車人数ボタン数字の表示、選択処理
//引  数：なし
//戻り値：なし
void CTitleProc::SelectPassengersNum(bool judgeRange, int selectKind, int i) {
	//乗車人数
	const float fScale = 1.2f; // 表示ボタンの拡大値 
	// 表示位置のX、Y位置
	const int nStartX = 690, nStartY = 80;
	// ボタンの幅、高さ
	const int nWidth = 50, nHeight = 50;
	// 拡大したボタンの幅、高さ
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// 薄い色で表示する透明度
	float lightColor = 0.5f;
	// 選択し決定しているボタンかどうか
	if (passengersSelect == i) {
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // 表示する色を赤色にする
		m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 4) * 70), nStartY + 125,
			(i - 4) * 50, 0, nWidth, nHeight, 1.0f);  // 色を変えて表示
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // 色を元に戻す
	}
	else {
		// selectKindは他のオプションの列の数(ボタン)に反応させないため
		// judgeRangeは現在カーソル内かどうかかつ
		// カーソル内にある数字(ボタン)どうか
		if (passengersNum == i && selectKind == 2 && judgeRange == true)
		{
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 4) * 70), nStartY + 125,
				(i - 4) * 50, 0, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
			// カーソル内かつ選択しているかどうか
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) 
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	
			{
				// 選択中の数字の更新
				passengersSelect = i;
				m_pGMain->selectSound->Play();  // 選択効果音
			}
		}
		else {
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 4) * 70), nStartY + 125,
				(i - 4) * 50, 0, nWidth, nHeight, lightColor);  // 薄い色で表示
		}
	}
}
// M.S オプション画面の発射までの待ち時間ボタン数字の表示、選択処理
//引  数：なし
//戻り値：なし
void CTitleProc::SelectWaitTime(bool judgeRange, int selectKind, int i) {
	// 待ち時間
	const float fScale = 1.2f; // 表示ボタンの拡大値 
	// 表示位置のX、Y位置
	const int nStartX = 690, nStartY = 80;
	// ボタンの幅、高さ
	const int nWidth = 50, nHeight = 50;
	// 拡大したボタンの幅、高さ
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// 薄い色で表示する透明度
	float lightColor = 0.5f;
	// 選択し決定しているボタンかどうか
	if (waitingTimeSelect == i) { 
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // 表示する色を赤色にする
		m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 10) * 70), nStartY + 245,
			(i - 10) * 50, 100, nWidth, nHeight, 1.0f);  // 色を変えて表示
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // 色を元に戻す
	}
	else {
		// selectKindは他のオプションの列の数(ボタン)に反応させないため
		// judgeRangeは現在カーソル内かどうかかつ
		// カーソル内にある数字(ボタン)かどうか
		if (waitingTime == i && selectKind == 3 && judgeRange == true)
		{
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 10) * 70), nStartY + 245,
				(i - 10) * 50, 100, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
			// カーソル内かつ選択しているかどうか
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				// 選択中の数字の更新
				waitingTimeSelect = i;
				m_pGMain->selectSound->Play();  // 選択効果音
			}
		}
		else {
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 10) * 70), nStartY + 245, 
				(i - 10) * 50, 100, nWidth, nHeight, lightColor);  // 薄い色で表示
		}
	}
}
// M.S オプション画面のBGM音量ボタン数字の表示、選択処理
//引  数：なし
//戻り値：なし
void CTitleProc::SelectBgm(bool judgeRange, int selectKind, int i) {
	// BGM音量
	const float fScale = 1.2f; // 表示ボタンの拡大値 
	// 表示位置のX、Y位置
	const int nStartX = 690, nStartY = 80;
	// ボタンの幅、高さ
	const int nWidth = 50, nHeight = 50;
	// 拡大したボタンの幅、高さ
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// 薄い色で表示する透明度
	float lightColor = 0.5f;
	// 選択し決定しているボタンかどうか
	if (bgmSelect == i) {
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // 表示する色を赤色にする
		m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 16) * 70), nStartY + 360,
			(i - 16) * 50, 100, nWidth, nHeight, 1.0f);  // 色を変えて表示
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // 色を元に戻す
	}
	else {
		// selectKindは他のオプションの列の数(ボタン)に反応させないため
		// judgeRangeは現在カーソル内かどうかかつ
		// カーソル内にある数字(ボタン)かどうか
		if (bgmNum == i && selectKind == 4 && judgeRange == true) {
			{
				m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 16) * 70), nStartY + 360,
					(i - 16) * 50, 100, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
				// カーソル内かつ選択しているかどうか
				if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
					|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
				{
					// 選択中の数字の更新
					bgmSelect = i;
					// 選択した数字を音量設定に使う数字に変換
					ChangeSelectNum(1);
					// 音量の設定
					m_pGMain->SetBgmVolume();
					m_pGMain->selectSound->Play();  // 選択効果音
				}
			}
		}
		else {
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 16) * 70), nStartY + 360,
				(i - 16) * 50, 100, nWidth, nHeight, lightColor);  // 薄い色で表示
		}
	}
}
// M.S オプション画面のSE音量ボタン数字の表示、選択処理
//引  数：なし
//戻り値：なし
void CTitleProc::SelectSe(bool judgeRange, int selectKind, int i) {
	// SE音量
	const float fScale = 1.2f; // 表示ボタンの拡大値 
	// 表示位置のX、Y位置
	const int nStartX = 690, nStartY = 80;
	// ボタンの幅、高さ
	const int nWidth = 50, nHeight = 50;
	// 拡大したボタンの幅、高さ
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// 薄い色で表示する透明度
	float lightColor = 0.5f;
	// 選択し決定しているボタンかどうか
	if (seSelect == i) {
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // 表示する色を赤色にする
		m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 22) * 70), nStartY + 470,
			(i - 22) * 50, 100, nWidth, nHeight, 1.0f);  // 色を変えて表示
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // 色を元に戻す
	}
	else {
		// selectKindは他のオプションの列の数(ボタン)に反応させないため
		// judgeRangeは現在カーソル内かどうかかつ
		// カーソル内にある数字(ボタン)かどうか
		if (seNum == i && selectKind == 5 && judgeRange == true)
		{
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 22) * 70), nStartY + 470,
				(i - 22) * 50, 100, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
			// カーソル内かつ選択しているかどうか
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				// 選択中の数字の更新
				seSelect = i;
				// 選択した数字を音量設定に使う数字に変換
				ChangeSelectNum(2);
				// 音量の設定
				m_pGMain->SetSoundVolume();
				m_pGMain->selectSound->Play();  // 選択効果音
			}
		}
		else {
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 22) * 70), nStartY + 470,
				(i - 22) * 50, 100, nWidth, nHeight, lightColor); // 薄い色で表示
		}
	}
}
// M.S オプション画面のボタンの選択処理
//引  数：なし
//戻り値：なし
void CTitleProc::DrawSelectNum(bool judgeRange, int selectKind)
{
	const int nNum = 28; // オプションの選択ボタンの数
	const float fScale = 1.2f; // 表示ボタンの拡大値 
	// 表示位置のX、Y位置
	const int nStartX = 690, nStartY = 80;
	// ボタンの幅、高さ
	const int nWidth = 50, nHeight = 50;
	// 拡大したボタンの幅、高さ
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	int i; 
	//オプション画面の描画と選択処理
	for (i = 0; i < nNum; i++)
	{
		if (i < 4) {
			SelectLineNum(judgeRange, selectKind, i);  // 線路数
		}
		else if (i < 10) {
			SelectPassengersNum(judgeRange, selectKind, i);  // 乗車人数
		}
		else if (i < 16) {
			SelectWaitTime(judgeRange, selectKind, i);  // 出発までの待ち時間
		}
		else if (i < 22) {
			SelectBgm(judgeRange, selectKind, i);  // BGM音量
		}
		else if (i < 28) {
			SelectSe(judgeRange, selectKind, i);  // SE音量
		}
	}
}
// M.S オプション画面の表示、選択処理
//引  数：なし
//戻り値：bool true オプション画面の終了
bool CTitleProc::TitleOption()
{
	BOOL bRet = FALSE;
	const int nNum = 28;         // 配列要素数
	const float fScale = 1.2f;   // 拡大値
	// オプション数字ボタンを表示するX、Y位置
	const int nStartX = 690, nStartY = 80;  
	// オプション数字ボタンの幅、高さ
	const int nWidth = 50, nHeight = 50;   
	// 戻るボタンを表示するX、Y位置
	const int nStartXBack = 586, nStartYBack = 618; 
	// 戻るボタンの幅、高さ
	const int nWidthBack = 194, nHeightBack = 72;   
	// 戻るボタンの拡大した幅
	const int nWidthBackScale = nWidthBack * fScale;
	// 戻るボタンの拡大した高さ
	const int nHeightBackScale = nHeightBack * fScale;
	// 薄い色で表示する透明度
	float lightColor = 0.5f;
	int i;
	// 画面表示
	m_pSprite->Draw(m_pImageOption, 0, 0, 0, 0, 
		m_pImageOption->m_dwImageWidth, m_pImageOption->m_dwImageHeight,WINDOW_WIDTH, WINDOW_HEIGHT);
	// マウスによるオプションボタン選択
	for (i = 0; i < nNum; i++)
	{
		if (i < 4) {       // 線路数
			if (CheckMousePos(nStartX + (i * 70), nStartY , nWidth, nHeight) == true)
			{
				linetrainNum = i;     // マウスカーソルがボタン内にある				
				selectedKindNum = 1;  // 選択しているボタンがある列のセット
			}	
		}		
		else if (i < 10) { // 乗車人数
			if (CheckMousePos(nStartX + ((i - 4) * 70), nStartY + 125, nWidth, nHeight) == true)
			{
				passengersNum = i;    // マウスカーソルがボタン内にある		
				selectedKindNum = 2;  // 選択しているボタンがある列のセット 
			}		
		}	
		else if (i < 16) { // 発射までの待ち時間
			if (CheckMousePos(nStartX + ((i - 10) * 70), nStartY + 245, nWidth, nHeight) == true)
			{
				waitingTime = i;      // マウスカーソルがボタン内にある		
				selectedKindNum = 3;  // 選択しているボタンがある列のセット
			}	
		}
		else if (i < 22) { // BGM音量
			if (CheckMousePos(nStartX + ((i - 16) * 70), nStartY + 360, nWidth, nHeight) == true)
			{
				bgmNum = i;           // マウスカーソルがボタン内にある		
				selectedKindNum = 4;  // 選択しているボタンがある列のセット
			}			
		}
		else if (i < 28) { // SE音量
			if (CheckMousePos(nStartX + ((i - 22) * 70), nStartY + 470, nWidth, nHeight) == true)
			{
				seNum = i;            // マウスカーソルがボタン内にある		
				selectedKindNum = 5;  // 選択しているボタンがある列のセット
			}
		}
	}
	// どこかのボタン(数字)内にカーソルがあるかどうか
	if (selectedKindNum != 0) {
		DrawSelectNum(true, selectedKindNum);
	}
	else {
		DrawSelectNum(false, selectedKindNum);
	}
	selectedKindNum = 0;  // selectedKindNumの初期化
	// 終了キー
	    // 戻るボタンを選択中かどうか
		if (CheckMousePos(nStartXBack, nStartYBack, nWidthBack, nHeightBack) == true) {
				// 戻るボタンを表示
				m_pSprite->Draw(m_pImageOptionBackButton, nStartXBack - 15, nStartYBack, 0, 0,
					nWidthBack, nHeightBack, nWidthBackScale, nHeightBackScale); 
				// 戻るボタンを選択し決定したかどうか
				if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) 
					|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {		
					m_pGMain->selectSound->Play(); // 選択効果音
					ChangeSelectNum(0);            // 選択し決定したオプションの数値に更新
					m_pGMain->FileWrite();         // 更新した情報をファイルに書き込む
					m_dwStatusPhase = 0;           // タイトルセレクト画面へ
					bRet = TRUE;  // 終了 
				}
		}
		else {
			m_pSprite->Draw(m_pImageOptionBackButton, nStartXBack, nStartYBack,
				0, 0, nWidthBack, nHeightBack, lightColor); // 薄い色で表示
		}
	return bRet;
}
// M.S あそびかた画面の選択中ページの表示
//引  数：なし
//戻り値：なし
void CTitleProc::DrawExplanationPage(int nowPage) {
	// 選択中のページを表示する
	switch (nowPage) {
	case 0:
		m_pSprite->Draw(m_pImagePage1, 0, 0, 0, 0,
			m_pImagePage1->m_dwImageWidth, m_pImagePage1->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 1:
		m_pSprite->Draw(m_pImagePage2, 0, 0, 0, 0,
			m_pImagePage2->m_dwImageWidth, m_pImagePage2->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 2:
		m_pSprite->Draw(m_pImagePage3, 0, 0, 0, 0,
			m_pImagePage3->m_dwImageWidth, m_pImagePage3->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 3:
		m_pSprite->Draw(m_pImagePage4, 0, 0, 0, 0,
			m_pImagePage4->m_dwImageWidth, m_pImagePage4->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 4:
		m_pSprite->Draw(m_pImagePage5, 0, 0, 0, 0,
			m_pImagePage5->m_dwImageWidth, m_pImagePage5->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 5:
		m_pSprite->Draw(m_pImagePage6, 0, 0, 0, 0,
			m_pImagePage6->m_dwImageWidth, m_pImagePage6->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 6:
		m_pSprite->Draw(m_pImagePage7, 0, 0, 0, 0,
			m_pImagePage7->m_dwImageWidth, m_pImagePage7->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 7:
		m_pSprite->Draw(m_pImagePage8, 0, 0, 0, 0,
			m_pImagePage8->m_dwImageWidth, m_pImagePage8->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	}
}
// M.S あそびかた画面の表示、選択処理
//引  数：なし
//戻り値：bool true あそびかた画面の終了
bool CTitleProc::TitleExplanation()
{
	BOOL bRet = FALSE;
	const int maxPage = 7;   // 最大ページ数
	const int minPage = 0;   // 最小ページ数
	// 次へ進むボタンを表示するX位置
	int rightButtonPosX = 1297;
	// 次へ進むボタンを表示するY位置
	int rightButtonPosY = 657;
	// 前へ戻るボタンを表示するX位置
	int leftButtonPosX = 0;
	// 前へ戻るボタンを表示するY位置
	int leftButtonPosY = 657;
	// 次へ、前へボタンの幅、高さ
	int buttonWidth = 69, buttonHeight = 69;
	//戻るボタンの拡大値
	const float fScale = 1.2f;
	// 戻るボタンを表示するX、Y位置
	const int nStartXBack = 1084, nStartYBack = 690;
	// 戻るボタンの幅、高さ
	const int nWidthBack = 194, nHeightBack = 72;
	// 戻るボタンの拡大した幅
	const int nWidthScale = nWidthBack * fScale;
	// 戻るボタンの拡大した高さ
	const int nHeightScale = nHeightBack * fScale;
	// 薄い色で表示する透明度
	float lightColor = 0.5f;
	// 選択中のページを表示する
	DrawExplanationPage(nowPage);
	// 左の戻るボタン内にカーソルがあるかどうか
	if (CheckMousePos(leftButtonPosX, leftButtonPosY, buttonHeight, buttonWidth) == true)
	{
		// ボタンの表示
		m_pSprite->Draw(m_pImagePageButton, leftButtonPosX, leftButtonPosY,
			0, 0, buttonWidth, buttonHeight);
		// 決定したかどうか
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
			// ページ移動変数を引く
			nowPage--;
			m_pGMain->turnThePageSound->Play();  // ページをめくる効果音
		}
	}
	else {
		m_pSprite->Draw(m_pImagePageButton, leftButtonPosX, leftButtonPosY, 
			0, 0, buttonWidth, buttonHeight, lightColor); // 薄い色でボタンを表示
	}
	// 右の進むボタン内にカーソルがあるかどうか
	if (CheckMousePos(rightButtonPosX, rightButtonPosY, buttonHeight, buttonWidth) == true)
	{
		// ボタンの表示
		m_pSprite->Draw(m_pImagePageButton, rightButtonPosX, rightButtonPosY,
			buttonWidth, 0, buttonWidth, buttonHeight);
		// 決定したかどうか
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
			// クリックしたらページ移動変数を足す
			nowPage++;
			m_pGMain->turnThePageSound->Play();  // ページをめくる効果音
		}
	}
	else {
		m_pSprite->Draw(m_pImagePageButton, rightButtonPosX, rightButtonPosY,
			buttonWidth, 0, buttonWidth, buttonHeight, lightColor);  // 薄い色でボタンを表示
	}
	// ページ移動変数がページ最大値より大きかったら
	if (nowPage > maxPage) {
		nowPage = minPage; // ページ移動変数をページ最小値にセット
	}
	// ページ移動変数がページ最小値より小さかったら
	else if (nowPage < minPage) {
		nowPage = maxPage; // ページ移動変数をページ最大値にセット
	}
	// 終了キー
	// 戻るボタン内にカーソルがあるかどうか
	if (CheckMousePos(nStartXBack, nStartYBack, nWidthBack, nHeightBack) == true) {
		{
			// 戻るボタンを表示
			m_pSprite->Draw(m_pImageOptionBackButton, nStartXBack - 15, nStartYBack,
				0, 0, nWidthBack, nHeightBack,nWidthScale, nHeightScale); 
			// 決定したかどうか
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				m_pGMain->selectSound->Play();  // 選択効果音
				m_dwStatusPhase = 0;  // タイトルセレクト画面へ
				bRet = TRUE;  // 終了
			}
		}
	}
	else {
		m_pSprite->Draw(m_pImageOptionBackButton, nStartXBack, nStartYBack,
			0, 0, nWidthBack, nHeightBack, lightColor); // 薄い色でボタンを表示
	}
	return bRet;
}
// M.S 通常モードのスコアの表示(画像の数字から表示させる)
//引  数：なし
//戻り値：なし
void CTitleProc::DrawManScoreNormalMode() {
	int DestXHigh = 700;   // 乗車人数(赤)のスコアの表示位置X
	int DestYHigh = 197;   // 乗車人数(赤)のスコアの表示位置Y
	int DestXMiddle = 700; // 乗車人数(黄)のスコアの表示位置X
	int DestYMiddle = 320; // 乗車人数(黄)のスコアの表示位置Y
	int DestXLow = 700;    // 乗車人数(青)のスコアの表示位置X
	int DestYLow = 448;    // 乗車人数(青)のスコアの表示位置Y
	int nWidth = 39;       // 表示する数字の幅
	int nHeight = 53;      // 表示する数字の高さ
	// 乗車人数から各人のスコアを出す
	totalHighManScore = m_pGMain->m_pEnmProc->getHighMan * 30;
	totalMiddleManScore = m_pGMain->m_pEnmProc->getMiddleMan * 20;
	totalLowManScore = m_pGMain->m_pEnmProc->getLowMan * 10;
	// 各人のスコアを足してトータルスコアを出す
	totalScore = totalHighManScore + totalMiddleManScore + totalLowManScore;
	// 乗車人数(赤)のスコアの1桁ずつの数字を出す
	int arrayNumHigh = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->m_pEnmProc->getHighMan);
	for (int i = 0; arrayNumHigh > i; i++) {  // 乗車人数(赤)のスコアの表示(1桁ずつ)
		// numArrayには乗車人数(赤)のスコアの1桁ずつの数字が入っている
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXHigh + (i * 59), DestYHigh,
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 乗車人数(黄)のスコアの1桁ずつの数字を出す
	int arrayNumMiddle = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->m_pEnmProc->getMiddleMan);
	for (int i = 0; arrayNumMiddle > i; i++) {  // 乗車人数(黄)のスコアの表示(1桁ずつ)
		// numArrayには乗車人数(黄)のスコアの1桁ずつの数字が入っている
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXMiddle + (i * 59), DestYMiddle,
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 乗車人数(青)のスコアの1桁ずつの数字を出す
	int arrayNumLow = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->m_pEnmProc->getLowMan);
	for (int i = 0; arrayNumLow > i; i++) {  // 乗車人数(青)のスコアの表示(1桁ずつ)
		// numArrayには乗車人数(青)のスコアの1桁ずつの数字が入っている
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXLow + (i * 59), DestYLow, 
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
}
// M.S ランキングモードのスコアの表示(画像の数字から表示させる)
//引  数：なし
//戻り値：なし
void CTitleProc::DrawManScoreRankingMode() {
	int DestXHigh = 700;   // 乗車人数(赤)のスコアの表示位置X
	int DestYHigh = 197;   // 乗車人数(赤)のスコアの表示位置Y
	int DestXMiddle = 700; // 乗車人数(黄)のスコアの表示位置X
	int DestYMiddle = 320; // 乗車人数(黄)のスコアの表示位置Y
	int DestXLow = 700;    // 乗車人数(青)のスコアの表示位置X
	int DestYLow = 448;    // 乗車人数(青)のスコアの表示位置Y
	int nWidth = 39;       // 表示する数字の幅
	int nHeight = 53;      // 表示する数字の高さ
	// 乗車人数から各人のスコアを出す
	totalHighManScore = m_pGMain->rankRedMan * 30;
	totalMiddleManScore = m_pGMain->rankYellowMan * 20;
	totalLowManScore = m_pGMain->rankBlueMan * 10;
	// 各人のスコアを足してトータルスコアを出す
	totalScore = totalHighManScore + totalMiddleManScore + totalLowManScore;
	// 乗車人数(赤)のスコアの1桁ずつの数字を出す
	int arrayNumHigh = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankRedMan);
	for (int i = 0; arrayNumHigh > i; i++) {  // 乗車人数(赤)のスコアの表示(1桁ずつ)
		// numArrayには乗車人数(赤)のスコアの1桁ずつの数字が入っている
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXHigh + (i * 59), DestYHigh, 
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 乗車人数(黄)のスコアの1桁ずつの数字を出す
	int arrayNumMiddle = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankYellowMan);
	for (int i = 0; arrayNumMiddle > i; i++) {  // 乗車人数(黄)のスコアの表示(1桁ずつ)
		// numArrayには乗車人数(黄)のスコアの1桁ずつの数字が入っている
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXMiddle + (i * 59), DestYMiddle,
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 乗車人数(青)のスコアの1桁ずつの数字を出す
	int arrayNumLow = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankBlueMan);
	for (int i = 0; arrayNumLow > i; i++) {  // 乗車人数(青)のスコアの表示(1桁ずつ)
		// numArrayには乗車人数(青)のスコアの1桁ずつの数字が入っている
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXLow + (i * 59), DestYLow, 
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
}
// M.S トータルスコアの表示(画像の数字から表示させる)
//引  数：なし
//戻り値：なし
void CTitleProc::DrawTotalScore() {
	int nWidth = 39;       // 表示する数字の幅
	int nHeight = 53;      // 表示する数字の高さ
	int DestXTotal = 636;  // 表示するトータルスコアの表示位置X
	int DestYTotal = 661;  // 表示するトータルスコアの表示位置Y
	// トータルスコアの1桁ずつの数字を出す
	int arrayTotalScore = m_pGMain->m_pBackForeProc->VariableAnalysis(totalScore);
	for (int i = 0; arrayTotalScore > i; i++) { // トータルスコアの表示(1桁ずつ)
	    // numArrayにはトータルスコアの1桁ずつの数字が入っている
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXTotal + (i * 59), DestYTotal, 
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
}
// M.S ランキングの並べかえ
// 引  数：なし
// 戻り値：なし
void CTitleProc::SortRanking() {
	// ランキングの数字変数
	int numberOne = 1, numberTwo = 2, numberThree = 3, numberFour = 4, numberFive = 5;
	// 今回のプレイスコアが1位より大きい場合の並べ替え
	if (totalScore > m_pGMain->rankOne) {
		m_pGMain->rankFive = m_pGMain->rankFour;
		m_pGMain->rankFour = m_pGMain->rankThree;
		m_pGMain->rankThree = m_pGMain->rankTwo;
		m_pGMain->rankTwo = m_pGMain->rankOne;
		m_pGMain->rankOne = totalScore;
		myRanking = numberOne;
	}
	// 今回のプレイスコアが2位より大きい場合の並べ替え
	else if (totalScore > m_pGMain->rankTwo) {
		m_pGMain->rankFive = m_pGMain->rankFour;
		m_pGMain->rankFour = m_pGMain->rankThree;
		m_pGMain->rankThree = m_pGMain->rankTwo;
		m_pGMain->rankTwo = totalScore;
		myRanking = numberTwo;
	}
	// 今回のプレイスコアが3位より大きい場合の並べ替え
	else if (totalScore > m_pGMain->rankThree) {
		m_pGMain->rankFive = m_pGMain->rankFour;
		m_pGMain->rankFour = m_pGMain->rankThree;
		m_pGMain->rankThree = totalScore;
		myRanking = numberThree;
	}
	// 今回のプレイスコアが4位より大きい場合の並べ替え
	else if (totalScore > m_pGMain->rankFour) {
		m_pGMain->rankFive = m_pGMain->rankFour;
		m_pGMain->rankFour = totalScore;
		myRanking = numberFour;
	}
	// 今回のプレイスコアが5位より大きい場合の並べ替え
	else if (totalScore > m_pGMain->rankFive) {
		m_pGMain->rankFive = totalScore;
		myRanking = numberFive;
	}
}
// M.S ランキングの追加、表示(画像の数字から表示させる)
//引  数：なし
//戻り値：なし
void CTitleProc::AddRanking() {
	int DestXOne = 466;     // ランキング1位スコア表示のX位置
	int DestYOne = 216;     // ランキング1位スコア表示のY位置
	int DestXTwo = 466;     // ランキング2位スコア表示のX位置
	int DestYTwo = 341;     // ランキング2位スコア表示のY位置
	int DestXThree = 466;   // ランキング3位スコア表示のX位置
	int DestYThree = 463;   // ランキング3位スコア表示のY位置
	int DestXFour = 466;    // ランキング4位スコア表示のX位置
	int DestYFour = 581;    // ランキング4位スコア表示のY位置
	int DestXFive = 466;    // ランキング5位スコア表示のX位置
	int DestYFive = 677;    // ランキング5位スコア表示のY位置
	int nWidth = 39;        // 表示するランキング数字の幅
	int nHeight = 53;       // 表示するランキング数字の高さ
	int blinkingTimeReset = 0;     // 点滅表示させる時間の初期化
	int goAroundBlinkingTime = 60; // 点滅表示させる時間が1周した時間
	int halfBlinkingTime = 30;     // 点滅表示させる時間が半周した時間
	float lightColor = 0.3f;       // 薄い色で表示する透明度
	// ランキングの数字変数
	int numberOne = 1, numberTwo = 2, numberThree = 3, numberFour = 4, numberFive = 5;
	// ランキングの並べ替えをしていないかどうか
	if (initialRankingSorting == true) {  
		SortRanking();                 // ランキングの並べかえ
		initialRankingSorting = false; // ランキングの並べ替えを完了
	}
	// 現在の1位のスコアの1桁ずつの数字を出す
	int arrayOne = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankOne);
	for (int i = 0; arrayOne > i; i++) {  // 現在の1位のスコアの表示(1桁ずつ)
		if (myRanking == numberOne && rankingTime <= halfBlinkingTime) {  // 今回のプレイランクならばrankingTimeの点滅表示
			// numArrayには現在の1位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXOne + (i * 59), DestYOne,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXOne + (i * 59), DestYOne,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	}
	// 現在の2位のスコアの1桁ずつの数字を出す
	int arrayTwo = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankTwo);
	for (int i = 0; arrayTwo > i; i++) {  // 現在の2位のスコアの表示(1桁ずつ)
		if (myRanking == numberTwo && rankingTime <= halfBlinkingTime) {  // 今回のプレイランクならばrankingTimeの点滅表示
			// numArrayには現在の2位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXTwo + (i * 59), DestYTwo, 
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXTwo + (i * 59), DestYTwo,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	}
	// 現在の3位のスコアの1桁ずつの数字を出す
	int arrayThree = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankThree);
	for (int i = 0; arrayThree > i; i++) {  // 現在の3位のスコアの表示(1桁ずつ)
		if (myRanking == numberThree && rankingTime <= halfBlinkingTime) {  // 今回のプレイランクならばrankingTimeの点滅表示
			// numArrayには現在の3位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXThree + (i * 59), DestYThree,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXThree + (i * 59), DestYThree,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	}
	// 現在の4位のスコアの1桁ずつの数字を出す
	int arrayFour = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankFour);
	for (int i = 0; arrayFour > i; i++) {  // 現在の4位のスコアの表示(1桁ずつ)
		if (myRanking == numberFour && rankingTime <= halfBlinkingTime) {  // 今回のプレイランクならばrankingTimeの点滅表示
			// numArrayには現在の4位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFour + (i * 59), DestYFour,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFour + (i * 59), DestYFour, 
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	}
	// 現在の5位のスコアの1桁ずつの数字を出す
	int arrayFive = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankFive);
	for (int i = 0; arrayFive > i; i++) {  // 現在の5位のスコアの表示(1桁ずつ)
		if (myRanking == numberFive && rankingTime <= halfBlinkingTime) {  // 今回のプレイランクならばrankingTimeの点滅表示
			// numArrayには現在の5位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFive + (i * 59), DestYFive,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFive + (i * 59), DestYFive,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	} // 点滅表示をする場合に必要になる変数の処理(30ごとに点滅をさせる)
	if (rankingTime <= goAroundBlinkingTime) {
		rankingTime++;
	}
	else {
		rankingTime = blinkingTimeReset;
	}
}
//------------------------------------------------------------------------
//
//	ゲームクリヤーの表示	
//
//------------------------------------------------------------------------
void CTitleProc::GameClear()
{
	m_pGMain->m_pD3D->SetViewPort(false);  // M.S 1画面の表示
	gameClearCount++;      //ゲームクリア表示時間のカウント
	// M.S ゲームクリア画面処理
	if (gameClearCount <= 250) {
		// M.S クリアBGMを鳴らしていない場合
		if (RingSound == false) {
			m_pGMain->gameBgm->Stop();  // M.S ゲームBGMを止める
			m_pGMain->gameClearBgm->Play(AUDIO_LOOP); // M.S クリアBGMを鳴らす
			RingSound = true;  // M.S クリアBGMを鳴らした
		}
		// ゲームクリア画面の表示
		m_pSprite->Draw(m_pImageClear, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth,
			m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	// M.S リザルト画面処理
	else if (gameClearCount > 250 && gameClearCount <= 600) {
		// M.S リザルト画面の表示
		m_pSprite->Draw(m_pImageResult, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth,
			m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		// M.S リザルトBGMを鳴らしていない場合
		if (RingResultSound == false) {
			m_pGMain->gameClearBgm->Stop();  // M.S クリアBGMを止める
			m_pGMain->resultBgm->Play(AUDIO_LOOP); // M.S リザルトBGMを鳴らす
			RingResultSound = true;  // M.S リザルトBGMを鳴らした
		}
		// M.S ランキングモードかどうか
		if (m_pGMain->m_dwGameMode == 3) {
			DrawManScoreRankingMode(); // M.S 各人スコア表示
		}
		else {
			DrawManScoreNormalMode(); // M.S 各人スコア表示	
		}
		DrawTotalScore(); // トータルスコアの表示
	}
	// M.S ランキング画面処理  指定時間でランキングモードの場合
	else if (gameClearCount > 500 && gameClearCount <= 700 && m_pGMain->m_dwGameMode == 3) {
		// M.S ランキング画面の表示
		m_pSprite->Draw(m_pImageRanking, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth,
			m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		// M.S ランキングの追加
		AddRanking();
		// M.S ランキングをファイルに書き込んでいない場合
		if (ScoreWriteProcess == false) {
			m_pGMain->FileWrite(); // M.S ファイルに書き込む
			ScoreWriteProcess = true; // M.S 書き込んだフラグをtrue
		}
	}
	// M.S ゲーム終了処理  ランキングモードとその他のモードで指定時間を分ける
	else if (gameClearCount > 700 || gameClearCount > 600 && gameClearCount <= 700
		&& (m_pGMain->m_dwGameMode == 1 || m_pGMain->m_dwGameMode == 2)) {
		m_pGMain->resultBgm->Stop();  // M.S リザルトBGMを止める
		// M.S 通常モードの場合
		if (m_pGMain->m_dwGameMode == 1 || m_pGMain->m_dwGameMode == 2) {
			// M.S セーブデータの初期化
			m_pGMain->traveledStar = 0;             // M.S 行った星の数
			m_pGMain->haveToGoStar = 0;             // M.S 行くべき星の数
			m_pGMain->m_pEnmProc->getHighMan = 0;   // M.S 乗車人数(赤)
			m_pGMain->m_pEnmProc->getMiddleMan = 0; // M.S 乗車人数(黄)
			m_pGMain->m_pEnmProc->getLowMan = 0;    // M.S 乗車人数(青)
			m_pGMain->redMan = 0;     // M.S ファイルに書き込む乗車人数(赤)
			m_pGMain->yellowMan = 0;  // M.S ファイルに書き込む乗車人数(黄)
			m_pGMain->blueMan = 0;    // M.S ファイルに書き込む乗車人数(青)
			for (int i = 0; i < 25; i++) {
				m_pGMain->starArray[i] = 0; // M.S 生成した星の配列
			}
			m_pGMain->FileWrite();  // M.S ファイルに書き込む
		}
		// M.S 初期化
		myRanking = 0;        // M.S 順位変数 
		rankingTime = 0;      // M.S ランキング時間カウント
		gameClearCount = 0;   // M.S クリア
		ScoreWriteProcess = false;  // M.S ファイルへの書き込みフラグ
		m_pGMain->m_pPcProc->oneScreenFlag = false; // M.S 1画面描画フラグ
		m_pGMain->m_dwGameStatus = GAMEEND; // ゲーム終了へ
	}
}
//------------------------------------------------------------------------
//
//	ゲームオーバーの表示	
//
//------------------------------------------------------------------------
void CTitleProc::GameOver()
{
	// M.S 1画面のみの描画へ変更
	m_pGMain->m_pD3D->SetViewPort(false);  // 1画面の表示
	// ゲームオーバー画面表示
	m_pSprite->Draw(m_pImageOver, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	// M.S ゲームオーバーBGMを鳴らしていないかどうか
	if (RingSound == false) {
		m_pGMain->gameBgm->Stop();                // M.S ゲームのBGMを止める
		m_pGMain->gameOverBgm->Play(AUDIO_LOOP);  // M.S ゲームオーバーBGMを鳴らす
		RingSound = true;   // M.S ゲームオーバーBGMを鳴らし済み(RingSouundをtrue)にする
	}
	// M.S ゲームオーバーの終了時間を+1
	gameOverCount++;
	// M.S 操作またはgameOverCountが400より大きいかどうか
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A)
		|| m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON) || gameOverCount > 400 )
	{
		m_pGMain->gameOverBgm->Stop();       // M.S ゲームオーバーBGMを止める
		m_pGMain->m_dwGameStatus = GAMEEND;  // M.S ゲームの終了
		// M.S 1応1画面のみ描画フラグをfalse、gameOverCountを0にする
		m_pGMain->m_pPcProc->oneScreenFlag = false; // M.S 1画面表示フラグをfalse
		gameOverCount = 0;   // M.S ゲームオーバー時間カウントの初期化
	}
}
//------------------------------------------------------------------------
//
// マウスカーソルが指定した矩形内にあるかどうかを判定する
//
// 引数  int nPosX,  int nPosY     矩形左上座標
//       int nWidth, int nHeight   矩形の幅と高さ
//
// 戻り値  BOOL  TRUE:矩形内にある    FALSE:矩形内に無い
//
//------------------------------------------------------------------------
bool CTitleProc::CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight)
{
	POINT MPos = m_pGMain->m_pDI->GetMousePos();
	if (MPos.x >= nPosX && MPos.x <= nPosX + nWidth &&
		MPos.y >= nPosY && MPos.y <= nPosY + nHeight)
	{
		return TRUE;  // 矩形内にある
	}
	else {
		return FALSE;  // 矩形内に無い
	}
}
// M.S ランキング確認画面の表示(画像の数字から表示させる)
//引  数：なし
//戻り値：なし
void CTitleProc::DrawRanking()
{
	m_pGMain->m_pD3D->SetViewPort(false);   // 1画面の表示
	// ランキング確認画面の表示
	m_pSprite->Draw(m_pImageRanking, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, 
		m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	int DestXHigh = 700;   // 乗車人数(赤)のスコアの表示位置X
	int DestYHigh = 197;   // 乗車人数(赤)のスコアの表示位置Y
	int DestXMiddle = 700; // 乗車人数(黄)のスコアの表示位置X
	int DestYMiddle = 320; // 乗車人数(黄)のスコアの表示位置Y
	int DestXLow = 700;    // 乗車人数(青)のスコアの表示位置X
	int DestYLow = 448;    // 乗車人数(青)のスコアの表示位置Y
	int nWidth = 39;       // 表示する数字の幅
	int nHeight = 53;      // 表示する数字の高さ
	int DestXTotal = 636;  // 表示するトータルスコアの表示位置X
	int DestYTotal = 661;  // 表示するトータルスコアの表示位置Y
	int DestXOne = 466;     // ランキング1位スコア表示のX位置
	int DestYOne = 216;     // ランキング1位スコア表示のY位置
	int DestXTwo = 466;     // ランキング2位スコア表示のX位置
	int DestYTwo = 341;     // ランキング2位スコア表示のY位置
	int DestXThree = 466;   // ランキング3位スコア表示のX位置
	int DestYThree = 463;   // ランキング3位スコア表示のY位置
	int DestXFour = 466;    // ランキング4位スコア表示のX位置
	int DestYFour = 581;    // ランキング4位スコア表示のY位置
	int DestXFive = 466;    // ランキング5位スコア表示のX位置
	int DestYFive = 677;    // ランキング5位スコア表示のY位置
	int nStartXBack = 1178; // 戻るボタンを表示するX位置
	int nStartYBack = 688;  // 戻るボタンを表示するY位置
	int nWidthBack = 173;  	// 戻るボタンの幅
	int nHeightBack = 70;   // 戻るボタンの高さ
	float lightColor = 0.5f;  // 薄い色で表示する透明度
	// 現在の1位のスコアの1桁ずつの数字を出す
	int arrayOne = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankOne); 
	for (int i = 0; arrayOne > i; i++) { // 現在の1位のスコアの表示(1桁ずつ)
			// numArrayには現在の1位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXOne + (i * 59), DestYOne,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 現在の2位のスコアの1桁ずつの数字を出す
	int arrayTwo = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankTwo);
	for (int i = 0; arrayTwo > i; i++) { // 現在の2位のスコアの表示(1桁ずつ)
			// numArrayには現在の2位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXTwo + (i * 59), DestYTwo, 
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 現在の3位のスコアの1桁ずつの数字を出す
	int arrayThree = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankThree);
	for (int i = 0; arrayThree > i; i++) { // 現在の3位のスコアの表示(1桁ずつ)
			// numArrayには現在の3位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXThree + (i * 59), DestYThree,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 現在の4位のスコアの1桁ずつの数字を出す
	int arrayFour = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankFour);
	for (int i = 0; arrayFour > i; i++) { // 現在の4位のスコアの表示(1桁ずつ)
			// numArrayには現在の4位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFour + (i * 59), DestYFour, 
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 現在の5位のスコアの1桁ずつの数字を出す
	int arrayFive = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankFive);
	for (int i = 0; arrayFive > i; i++) { // 現在の5位のスコアの表示(1桁ずつ)
			// numArrayには現在の5位のスコアの1桁ずつの数字が入っている
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFive + (i * 59), DestYFive,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// 戻るボタン内にカーソルがあるかどうか
	if (CheckMousePos(nStartXBack, nStartYBack, nWidthBack, nHeightBack) == true) {
		// 戻るボタンを表示
		m_pSprite->Draw(m_pImageSaveWarning, nStartXBack, nStartYBack, 
			173, 378, nWidthBack, nHeightBack);
		// 戻るボタンを決定したかどうか
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
			m_dwStatusPhase = 0; // タイトルセレクトへ
			m_pGMain->selectSound->Play(); // 選択効果音
		}
	}
	else {
		m_pSprite->Draw(m_pImageSaveWarning, nStartXBack, nStartYBack,
			173, 378, nWidthBack, nHeightBack, lightColor); // 戻るボタンを薄い色で表示
	}
}
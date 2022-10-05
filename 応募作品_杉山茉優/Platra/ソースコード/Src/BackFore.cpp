//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//		前景・背景							                   BackFore.cpp
//=============================================================================
#include  "BackFore.h"
#include  "Playchar.h"
#include  "Title.h"
#include  "Enemy.h"
#include  "Effect.h"


//============================================================================
//
// 前景・背景プロシージャのコンストラクタ
//
// ---------------------------------------------------------------------------
CBackForeProc::CBackForeProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_pImageForegrd = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/foregrd3.png")); // スプライトイメージのロード
	m_pSprite = new CSprite(m_pGMain->m_pShader); // スプライトの生成
	m_pImageDynamicStarScene = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_gameUI.png"));
	m_pImagePlacementSceneNum = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_gameNum.png"));
	m_pImageStarBridgeSaving = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Saving.png"));
	m_pImageRankingNum = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/rankingNum.png"));
	m_pImageStarBridgeButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/StarBridgeButton.png"));
	m_pImageRemainingStar = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/remainingStarNotification.png"));
	m_pImageLineKind = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/allLineKindDisplay.png"));
	m_pImageLinePermission = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/lineKindPermission.png"));
	m_pImageGaugeGlitter = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/tktk_Recovery_17L.png"));
	m_pImageGoalButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/goalButton.png"));

	// M.S ここから下のコンストラクタの内容は追加しました
	////// ↓--------------------------------------------------------------------
	// 待ち時間のカウント数字の初期数
    waitingDrawTime = 60;
	// 表示用カウント数字保存変数
	initialDraw = 0;
	// 架け橋がかかったかどうか保存変数
	builtStarBridge = false;
	// 点滅カウント数字
	starBridgeSceneNext = 50;
	starBridgeSceneTime = 0;
	// 点滅させるカウント変数
	buttonBlinking = 0;
	// 次の星へ行くボタン用位置変数
	DestXStarBridgeButton = 1157;
	DestYStarBridgeButton = 253;
	nHeightScaleStarBridgeButton = 94 * 1.1f;
	nWidthScaleStarBridgeButton = 154 * 1.1f;
	// 発射までのカウント用変数
	drawWaitingNum = 0;
	// 発射までのカウントの数字セットを一度のみ行う変数
	initialWaitingNumSet = true;
	// 発射までのカウントの音を鳴らすフラグ
	ringTime = true;
	// ゲージの表示位置
	glitterGaugeDestX = 585;
	glitterGaugeDestY = 170;
	glitterGaugenHeight = 384;
	glitterGaugenWidth = 384;
	glitterGaugenHeightScale = glitterGaugenHeight * 0.8;
	glitterGaugenWidthScale = glitterGaugenWidth * 1.75;
	glitterAnimNum = 0;
	waitTime = 0;

	doneBridgeSound = false;
}
// ---------------------------------------------------------------------------
//
// 前景・背景プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CBackForeProc::~CBackForeProc()
{
	SAFE_DELETE(m_pImageForegrd);
	SAFE_DELETE(m_pImageDynamicStarScene);
	SAFE_DELETE(m_pImagePlacementSceneNum);
	SAFE_DELETE(m_pImageStarBridgeSaving);
	SAFE_DELETE(m_pImageRankingNum);
	SAFE_DELETE(m_pImageStarBridgeButton);
	SAFE_DELETE(m_pImageRemainingStar);
	SAFE_DELETE(m_pImageLineKind);
	SAFE_DELETE(m_pImageLinePermission);
	SAFE_DELETE(m_pImageGaugeGlitter);
	SAFE_DELETE(m_pImageGoalButton);

	SAFE_DELETE(m_pSprite);
}
//------------------------------------------------------------------------
//
//	前景・背景プロシージャの更新	
//
//------------------------------------------------------------------------
void CBackForeProc::Update()
{
	if (m_pGMain->m_pMapProc->MapNumGet() == 1) {
		DrawStage1();
	}else if(m_pGMain->m_pMapProc->MapNumGet() == 2){
		DrawStage2();
	}
	else if (m_pGMain->m_pMapProc->MapNumGet() == 3) {
		DrawStage3();
	}
}
//M.S 星動的生成画面の表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawStage1()
{
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	// 今回めぐる星々の文字表示 
	DestX = 358;
	DestY = 30;
	nWidth = 650;
	nHeight = 73;
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 0, nWidth, nHeight);
	// 出発ボタンの表示
	DestX = 1010;
	DestY = 530;
	nWidth = 289;
	nHeight = 152;
	if (m_pGMain->m_pTitleProc->CheckMousePos(1010, 530, nWidth, nHeight) == true)
	{
		// ボタンをクリックしたら
		m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 73, nWidth, nHeight);
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
		{
			// 次のマップの読み込み
			m_pGMain->goSound->Play();
			m_pGMain->m_pMapProc->LoadMap2();
		}
	}
	else {
		m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 73, nWidth, nHeight, 0.5f);
	}
}
//M.S 星の架け橋ゲージの文字表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawNextPassengersText() {
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	// 次の星までの乗車人数
	DestX = 700;
	DestY = 30;
	nWidth = 638;
	nHeight = 51;
	nWidthScale = nWidth * 0.8;
	nHeightScale = nHeight * 0.8;
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 225, nWidth, nHeight, nWidthScale, nHeightScale);
}
//M.S 次の星までの乗車人数の文字表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawNextGaugeText() {
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	DestX = 700;
	DestY = 215;
	nWidth = 483;
	nHeight = 49;
	nWidthScale = nWidth * 0.8;
	nHeightScale = nHeight * 0.8;
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 276, nWidth, nHeight, nWidthScale, nHeightScale);
}
//M.S 必要な乗車人数の表示(画像の数字から表示させる)
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawNextNeedPassengers() {
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	DestX = 740;
	DestY = 105;
	nWidth = 90;
	nHeight = 82;
	nWidthScale = nWidth * 0.8;
	nHeightScale = nHeight * 0.8;

	// allManNumは現在の星の合計乗車人数
	// 必要な人数が固定なランクモードと分ける
    allManNum = m_pGMain->m_pEnmProc->getHighStageMan + m_pGMain->m_pEnmProc->getMiddleStageMan + m_pGMain->m_pEnmProc->getLowStageMan;
	int needManNum = 0;
	if (m_pGMain->m_dwGameMode == 3 && allManNum <= m_pGMain->rankPassengersSelectNum) {
		needManNum = m_pGMain->rankPassengersSelectNum - allManNum;
	}
	else if (m_pGMain->m_dwGameMode != 3 && allManNum <= m_pGMain->passengersSelectNum) {
		needManNum = m_pGMain->passengersSelectNum - allManNum;
	}
	// 関数を呼びだしてarrayNumに桁数が入る
	int arrayNum = VariableAnalysis(needManNum);
	// arrayNumの桁分ループして90*iで位置をずらし数字を表示し、最後に人の文字を表示
	for (int i = 0; arrayNum + 1 > i; i++) {
		if (arrayNum > i) {
			// numArrayに入れた数字を画像から表示させる
			m_pSprite->Draw(m_pImagePlacementSceneNum, DestX + (90 * i), DestY, numArray[i] * 90, 0, nWidth, nHeight, nWidthScale, nHeightScale);
		}
		else {
			m_pSprite->Draw(m_pImagePlacementSceneNum, DestX + (90 * i), DestY, 900, 0, nWidth, nHeight, nWidthScale, nHeightScale);
		}
	}

}
//M.S 必要な電車の移動距離ゲージの表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawStarGauge() {
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	int maxGauge = 435;
	// ゲージの中
	DestX = 740;
	DestY = 297;
	gaugenWidth = 435;  // ←ここの値を変えるとゲージの表示長さが変わる
	nHeight = 49;
	// ゲージのmax/次の星に必要な移動距離をして
	// それに現在の移動距離をかけて表示する長さを出す
	// 必要な人数が固定なランクモードと分ける
	if (m_pGMain->m_dwGameMode != 3) {
		gaugenWidth = gaugenWidth / m_pGMain->lineTrainSelectNum;
	}
	else if (m_pGMain->m_dwGameMode == 3) {
		gaugenWidth = gaugenWidth / m_pGMain->rankLineTrainSelectNum;
	}
	gaugenWidth = gaugenWidth * m_pGMain->m_pPcProc->trainStep;
	// 移動距離が満たされていればmax(全てのゲージを)表示する
	if (m_pGMain->m_dwGameMode != 3 && m_pGMain->m_pPcProc->trainStep >= m_pGMain->lineTrainSelectNum) {
		gaugenWidth = maxGauge;
	}
	else if (m_pGMain->m_dwGameMode == 3 && m_pGMain->m_pPcProc->trainStep >= m_pGMain->rankLineTrainSelectNum) {
		gaugenWidth = maxGauge;
	}
	nWidthScale = gaugenWidth * 0.85;
	nHeightScale = nHeight * 0.85;
	// ゲージの中の表示
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 374, gaugenWidth, nHeight, nWidthScale, nHeightScale);

	// ゲージの外
	DestX = 740;
	DestY = 295;
	nWidth = 435;
	nHeight = 49;
	nWidthScale = nWidth * 0.85;
	nHeightScale = nHeight * 0.85;
	// ゲージの外の表示
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 325, nWidth, nHeight, nWidthScale, nHeightScale);

	// max(全てのゲージを)表示されていたらキラキラを表示する
	if (gaugenWidth >= 435) {
		DrawGlitterGauge();
	}
}
//M.S 発射までのカウントダウン(画像の数字から表示させる)
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawWaitTime() {
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	DestX = 303;
	DestY = 331;
	nWidth = 39;
	nHeight = 53;
	nWidthScale = nWidth * 2.0;
	nHeightScale = nHeight * 2.0;
	int waitTimeTextWidth = 39;    // 画像の数字の幅
	// 待ち時間が固定なランクモードと分ける
	if (m_pGMain->m_dwGameMode != 3) {
		if (initialWaitingNumSet == true) {
			// 選択されている待ち時間をdrawWaitingNumに入れる
			drawWaitingNum = m_pGMain->waitingTimeSelectNum;
			initialWaitingNumSet = false;
		}
		// 待ち時間を超えていなければ数字を表示させる
		if (initialDraw <= m_pGMain->waitingTimeSelectNum) {
			waitingDrawTime--;
			// 各秒の最初に音を鳴らす
			if (ringTime == true) {
				m_pGMain->timeCountSound->Play();
				ringTime = false;
			}
			if (waitingDrawTime > 0) {
				m_pSprite->Draw(m_pImageRankingNum, DestX, DestY, drawWaitingNum * waitTimeTextWidth, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			}
			else {
				// 1秒たったら音を鳴らす
				ringTime = true;
				drawWaitingNum--;
				initialDraw++;
				waitingDrawTime = 60;
			}
		}
		else {
			// 出発させる
			m_pGMain->m_pPcProc->GetPcObjPtr()->startTimeFlag = true;
		}
	}
	else if (m_pGMain->m_dwGameMode == 3) {
		if (initialWaitingNumSet == true) {
			// ランキングの待ち時間をdrawWaitingNumに入れる
			drawWaitingNum = m_pGMain->rankWaitingTimeSelectNum;
			initialWaitingNumSet = false;
		}
		// 待ち時間を超えていなければ数字を表示させる
		if (initialDraw <= m_pGMain->rankWaitingTimeSelectNum) {
			waitingDrawTime--;
			// 各秒の最初に音を鳴らす
			if (ringTime == true) {
				m_pGMain->timeCountSound->Play();
				ringTime = false;
			}
			if (waitingDrawTime > 0) {
				m_pSprite->Draw(m_pImageRankingNum, DestX, DestY, drawWaitingNum * waitTimeTextWidth, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			}
			else {
				ringTime = true;
				drawWaitingNum--;
				initialDraw++;
				waitingDrawTime = 60;
			}
		}
		else {
			// 出発させる
			m_pGMain->m_pPcProc->GetPcObjPtr()->startTimeFlag = true;
		}
	}
}
//M.S 次の星へ行くボタンの表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawGoNextStarButton() {
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	// 次の星へ行くボタンの表示
	nWidth = 154;
	nHeight = 94;
	DestX = 1165;
	DestY = 260;
	if ((m_pGMain->m_dwGameMode != 3 && m_pGMain->m_pPcProc->trainStep >= m_pGMain->lineTrainSelectNum && m_pGMain->passengersSelectNum - allManNum <= 0)
		|| (m_pGMain->m_dwGameMode == 3 && m_pGMain->m_pPcProc->trainStep >= m_pGMain->rankLineTrainSelectNum && m_pGMain->rankPassengersSelectNum - allManNum <= 0)) {
		if (m_pGMain->m_dwGameMode == 3 && m_pGMain->rankHaveToGoStar - (m_pGMain->rankTraveledStar + 1) > 0 || m_pGMain->m_dwGameMode != 3 && m_pGMain->haveToGoStar - (m_pGMain->traveledStar + 1) > 0) {
			buttonBlinking++;
			if (m_pGMain->m_pTitleProc->CheckMousePos(DestX, DestY, nWidth, nHeight) == true)
			{
				// カーソルと接触していてbuttonBlinkingが50以下なら大きく、赤く表示する
				if (buttonBlinking <= 50) {
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pSprite->Draw(m_pImageStarBridgeButton, DestXStarBridgeButton, DestYStarBridgeButton, 0, 0, nWidth, nHeight, nWidthScaleStarBridgeButton, nHeightScaleStarBridgeButton, 1.0f);
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				}// それ以外なら大きく表示する
				else if (buttonBlinking <= 100) {
					m_pSprite->Draw(m_pImageStarBridgeButton, DestXStarBridgeButton, DestYStarBridgeButton, 0, 0, nWidth, nHeight, nWidthScaleStarBridgeButton, nHeightScaleStarBridgeButton, 1.0f);
					// 100以上ならbuttonBlinkinを0にする
					if (buttonBlinking >= 100) {
						buttonBlinking = 0;
					}
				}
				if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
				{
					// クリックされたら次のマップの読み込み
					if (m_pGMain->stopOperation == false) {
						m_pGMain->m_pMapProc->LoadMap3();
					}
				}
			}
			else {
				// カーソルと接触していなければ通常の大きさで表示させる
				if (buttonBlinking <= 50) {
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pSprite->Draw(m_pImageStarBridgeButton, DestX, DestY, 0, 0, nWidth, nHeight, 1.0f);
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else if (buttonBlinking <= 100) {
					m_pSprite->Draw(m_pImageStarBridgeButton, DestX, DestY, 0, 0, nWidth, nHeight, 1.0f);
					if (buttonBlinking >= 100) {
						buttonBlinking = 0;
					}
				}
			}
		}
		else {
			// 最後の星だった場合、ゴールボタンを表示する
			buttonBlinking++;
			if (m_pGMain->m_pTitleProc->CheckMousePos(DestX, DestY, nWidth, nHeight) == true)
			{
				if (buttonBlinking <= 50) {
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pSprite->Draw(m_pImageGoalButton, DestXStarBridgeButton, DestYStarBridgeButton, 0, 0, nWidth, nHeight, nWidthScaleStarBridgeButton, nHeightScaleStarBridgeButton, 1.0f);
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else if (buttonBlinking <= 100) {
					m_pSprite->Draw(m_pImageGoalButton, DestXStarBridgeButton, DestYStarBridgeButton, 0, 0, nWidth, nHeight, nWidthScaleStarBridgeButton, nHeightScaleStarBridgeButton, 1.0f);
					if (buttonBlinking >= 100) {
						buttonBlinking = 0;
					}
				}
				if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
				{
					// 次のマップの読み込み
					if (m_pGMain->stopOperation == false) {
						m_pGMain->m_pMapProc->LoadMap3();
					}
				}
			}
			else {
				if (buttonBlinking <= 50) {
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pSprite->Draw(m_pImageGoalButton, DestX, DestY, 0, 0, nWidth, nHeight, 1.0f);
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else if (buttonBlinking <= 100) {
					m_pSprite->Draw(m_pImageGoalButton, DestX, DestY, 0, 0, nWidth, nHeight, 1.0f);
					if (buttonBlinking >= 100) {
						buttonBlinking = 0;
					}
				}
			}
		}

	}
}
//M.S 選択中の線路の表示とその線路が配置可能かの表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawArrowLine()
{
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	int DestXLineArrow, DestYLineArrow, nHeightLineArrow, nWidthLineArrow;
	DestX = 14;
	DestY = 10;
	nWidth = 377;
	nHeight = 68;
	DestXLineArrow = 331;
	DestYLineArrow = 19;
	nWidthLineArrow = 46;
	nHeightLineArrow = 46;

	switch (m_pGMain->m_pMapProc->ChangeButton) {
	case 0:  // 通常線路
		m_pSprite->Draw(m_pImageLineKind, DestX, DestY, 0, 0, nWidth, nHeight);
		if (m_pGMain->m_pMapProc->ArrowPlacementPos() == true) {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 0, 0, nWidthLineArrow, nHeightLineArrow);
		}
		else {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 46, 0, nWidthLineArrow, nHeightLineArrow);
		}
		break;
	case 1:  // 方向転換線路
		m_pSprite->Draw(m_pImageLineKind, DestX, DestY, 0, 136, nWidth, nHeight);
		if (m_pGMain->m_pMapProc->typeChangeNum == 2 && m_pGMain->m_pMapProc->AllowEndPlacement(true) == false
			&& m_pGMain->m_pMapProc->changeButtonWithinRange == true && m_pGMain->m_pMapProc->ArrowPlacementPos() == true) {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 0, 0, nWidthLineArrow, nHeightLineArrow);
		}
		else {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 46, 0, nWidthLineArrow, nHeightLineArrow);
		}
		break;
	case 2:  // 駅
		m_pSprite->Draw(m_pImageLineKind, DestX, DestY, 0, 68, nWidth, nHeight);
		if (m_pGMain->m_pMapProc->typeChangeNum == 2 && m_pGMain->m_pMapProc->AllowEndPlacement(true) == false
			&& m_pGMain->m_pMapProc->ArrowPlacementPos() == true) {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 0, 0, nWidthLineArrow, nHeightLineArrow);
		}
		else {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 46, 0, nWidthLineArrow, nHeightLineArrow);
		}
		break;
	}
}
//M.S 線路配置ゲーム画面の表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawStage2() {
	DrawArrowLine();
	DrawNextPassengersText();
	DrawNextGaugeText();
	DrawNextNeedPassengers();
	DrawStarGauge();
	DrawWaitTime();
	DrawGoNextStarButton();	
}
//M.S 星の架け橋をかける画面の表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawStage3()
{
	// 表示位置の定義
	int DestX, DestY, nHeight, nWidth;
	// 文字の表示
	DestX = 20;
	DestY = 30;
	nWidth = 524;
	nHeight = 96;
	 m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 423, nWidth, nHeight);
	DestX = 901;
	DestY = 37;
	nWidth = 334;
	nHeight = 36;
	 m_pSprite->Draw(m_pImageRemainingStar, DestX, DestY, 0, 0, nWidth, nHeight);

	DestX = 1252;
	DestY = 35;
	nWidth = 39;
	nHeight = 53;
	int arrayStarNum;
	// 残りの行くべき星の数の表示
	// ランキングモードは行く星の数が固定なので分ける
	if (m_pGMain->m_dwGameMode != 3) {
		arrayStarNum = VariableAnalysis(m_pGMain->haveToGoStar - m_pGMain->traveledStar);
	}
	else if (m_pGMain->m_dwGameMode == 3) {
		arrayStarNum = VariableAnalysis(m_pGMain->rankHaveToGoStar - m_pGMain->rankTraveledStar);

	}
	// 桁の数ループを回して星の数の表示(画像の数字から表示させる)
	for (int i = 0; arrayStarNum > i; i++) {
		m_pSprite->Draw(m_pImageRankingNum, DestX + (50 * i), DestY, numArray[i] * 39, 0, nWidth, nHeight);
	}
	if (builtStarBridge == true) {
		// 通常モードはセーブの表示をする
		if (m_pGMain->m_dwGameMode != 3) {
			DestX = 910;
			DestY = 600;
			nWidth = 429;
			nHeight = 52;
			 m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 519, nWidth, nHeight);
			DestX = 1090;
			DestY = 680;
			nWidth = 244;
			nHeight = 44;
			 m_pSprite->Draw(m_pImageStarBridgeSaving, DestX, DestY, 0, 0, nWidth, nHeight);
			 // セーブ音を鳴らす
			if (doneBridgeSound == false) {
				doneBridgeSound = true;
				m_pGMain->saveOkSound->Play();
			}
		}
		starBridgeSceneTime++;
		// 一定時間たったら次の画面に移る
		if (starBridgeSceneNext <= starBridgeSceneTime) {
			m_pGMain->m_pMapProc->LoadMap2();
			starBridgeSceneTime = 0;
		}
	}
}
//M.S 与えられた数字の桁数を返し、VariableAnalysisChangeNumを呼びだす
//引  数：int analysisObject   求めたい数字
//戻り値：int                  求めたい数字の桁数
int CBackForeProc::VariableAnalysis(int analysisObject)
{
	int analysisObjectKind = 0;
	if (analysisObject / 10000 != 0) {
		analysisObjectKind = 5;   // 5桁
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
	else if (analysisObject / 1000 != 0) {
		analysisObjectKind = 4;   // 4桁
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
	else if (analysisObject / 100 != 0) {
		analysisObjectKind = 3;   // 3桁
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
	else if (analysisObject / 10 != 0) {
		analysisObjectKind = 2;   // 2桁
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
	else {
		analysisObjectKind = 1;   // 1桁
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
}
//M.S 数字の各桁の数を配列(numArray)に入れて求める
//引  数：int analysisObject      求めたい数字
//        int analysisObjectKind  求めたい数字の桁数
//戻り値：なし              
void CBackForeProc::VariableAnalysisChangeNum(int analysisObject, int analysisObjectKind)
{
	int analysisObjectNum = analysisObject;
	int arrayElementsNum = 0;
	// numArrayを0で初期化
	for (int i = 0; i < 5; i++) {
		numArray[i] = 0;
	}
	// 処理する桁-1回divideNumに10をかけ、analysisObjectNum / その数をして出た数字をnumArrayに入れる
	// analysisObjectNumからnumArrayにいれた数字*dividNumを引き、その数字で次のループをする
	for (int i = analysisObjectKind; i >= 1; i--) {
		int divideNum = 1;
		for (int num = 1; num < i; num++) {
			divideNum = divideNum * 10;
		}
		numArray[arrayElementsNum] = analysisObjectNum / divideNum;
		analysisObjectNum = analysisObjectNum - numArray[arrayElementsNum] * divideNum;
		arrayElementsNum++;
	}
}
//M.S 移動距離ゲージがmax(全てのゲージ表示)になった時のキラキラ表示
//引  数：なし
//戻り値：なし
void CBackForeProc::DrawGlitterGauge()
{
	int glitterGaugeImagePosX;
	int glitterGaugeImagePosY;
	// glitterAnimNumが10以上になったら、アニメーションを最初に戻す
	if (glitterAnimNum >= 10) {
		glitterAnimNum = 0;
	}
    // glitterAnimNumによってスプライトの表示する位置を求める
	glitterGaugeImagePosX = glitterAnimNum / 5 * 384;
	glitterGaugeImagePosY = glitterAnimNum % 5 * 384;
	// 表示
	m_pSprite->Draw(m_pImageGaugeGlitter, glitterGaugeDestX, glitterGaugeDestY, glitterGaugeImagePosX, glitterGaugeImagePosY, glitterGaugenWidth, glitterGaugenHeight, glitterGaugenWidthScale, glitterGaugenHeightScale);//nWidthScale,nHeightScale);
	waitTime++;
    // waitTimeが8になったら次のアニメーションに変える
	if (waitTime % 8 == 0) {
		glitterAnimNum++;
		waitTime = 0;
	}
}

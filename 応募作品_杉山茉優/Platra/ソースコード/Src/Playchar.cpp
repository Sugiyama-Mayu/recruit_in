//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//
//		プレイキャラクターの制御
//																Playchar.cpp
//=============================================================================
#include  "Playchar.h"
#include  "Camera.h"
#include  "BackFore.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "Enemy.h"
#include  "Title.h"

//============================================================================
//
// ＰＣプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nNum = 3;    // PCの最大出現数
	// キャラクター　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	// M.S プレイキャラモデル
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/GalaxyTrain/trainModelCenter01.mesh")); 
	// アニメーション読み込み 
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/trainModelCenter01.anmx"));    // M.S 通常
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/trainModelCenter01.anmx"));    // M.S
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/trainModelCenter01.anmx"));    // M.S ゲームオーバー時
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/galaxyTrain_GameOver.anmx"));  // M.S
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/galaxyTrain_InsideOut.anmx")); // M.S ゲームオーバー後
	m_pMesh->m_fHeightMax = 0.01f;
	m_pMesh->m_iMaxDevide = 16;
	// -------------------------------------------------------------------------
	m_pObjArray.push_back(new CPcObj(m_pGMain));	// m_pObjArrayにオブジェクトを登録する
	((CPcObj*)m_pObjArray[0])->SetMesh(this);		// メッシュポインタを設定する
	m_nPcNum  =  nNum;
	// M.S ここから下のコンストラクタの内容は追加しました
	////// ↓--------------------------------------------------------------------
	// プレイヤーの位置が上の場合
	upFront1 = VECTOR3(0.0f, 7.0f, 4.0f);
	upBack1 = VECTOR3(0.0f, 5.5f, 4.0f);
	downFront1 = VECTOR3(0.0f, 7.0f, -4.0f);
	downBack1 = VECTOR3(0.0f, 5.5f, -4.0f);
	rightFront1 = VECTOR3(4.0f, 7.0f, 0.0f);
	rightBack1 = VECTOR3(4.0f, 5.5f, 0.0f);
	leftFront1 = VECTOR3(-4.0f, 7.0f, 0.0f);
	leftBack1 = VECTOR3(-4.0f, 5.5f, 0.0f);
	// プレイヤーの位置が真ん中
	upFront2 = VECTOR3(0.0f, 4.0f, -7.0f);
	upBack2 = VECTOR3(0.0f, 4.0f, -5.5f);
	downFront2 = VECTOR3(0.0f, -4.0f, -7.0f);
	downBack2 = VECTOR3(0.0f, -4.0f, -5.5f);
	rightFront2 = VECTOR3(4.0f, 0.0f, -7.0f);
	rightBack2 = VECTOR3(4.0f, 0.0f, -5.5f);
	leftFront2 = VECTOR3(-4.0f, 0.0f, -7.0f);
	leftBack2 = VECTOR3(-4.0f, 0.0f, -5.5f);
	// プレイヤーの位置が下
	upFront3 = VECTOR3(0.0f, -7.0f, -4.0f);
	upBack3 = VECTOR3(0.0f, -5.5f, -4.0f);
	downFront3 = VECTOR3(0.0f, -7.0f, 4.0f);
	downBack3 = VECTOR3(0.0f, -5.5f, 4.0f);
	rightFront3 = VECTOR3(4.0f, -7.0f, 0.0f);
	rightBack3 = VECTOR3(4.0f, -5.5f, 0.0f);
	leftFront3 = VECTOR3(-4.0f, -7.0f, 0.0f);
	leftBack3 = VECTOR3(-4.0f, -5.5f, 0.0f);
	// プレイヤーの位置が裏の真ん中
	upFront4 = VECTOR3(0.0f, -4.0f, 7.0f);
	upBack4 = VECTOR3(0.0f, -4.0f, 5.5f);
	downFront4 = VECTOR3(0.0f, 4.0f, 7.0f);
	downBack4 = VECTOR3(0.0f, 4.0f, 5.5f);
	rightFront4 = VECTOR3(4.0f, 0.0f, 7.0f);
	rightBack4 = VECTOR3(4.0f, 0.0f, 5.5f);
	leftFront4 = VECTOR3(-4.0f, 0.0f, 7.0f);
	leftBack4 = VECTOR3(-4.0f, 0.0f, 5.5f);
	// プレイヤーの位置が右
	upFront5 = VECTOR3(7.0f, 0.0f, 4.0f);
	upBack5 = VECTOR3(5.5f, 0.0f, 4.0f);
	downFront5 = VECTOR3(7.0f, 0.0f, -4.0f);
	downBack5 = VECTOR3(5.5f, 0.0f, -4.0f);
	rightFront5 = VECTOR3(7.0f, -4.0f, 0.0f);
	rightBack5 = VECTOR3(5.5f, -4.0f, 0.0f);
	leftFront5 = VECTOR3(7.0f, 4.0f, 0.0f);
	leftBack5 = VECTOR3(5.5f, 4.0f, 0.0f);
	// プレイヤーの位置が左
	upFront6 = VECTOR3(-7.0f, 0.0f, 4.0f);
	upBack6 = VECTOR3(-5.5f, 0.0f, 4.0f);
	downFront6 = VECTOR3(-7.0f, 0.0f, -4.0f);
	downBack6 = VECTOR3(-5.5f, 0.0f, -4.0f);
	rightFront6 = VECTOR3(-7.0f, 4.0f, 0.0f);
	rightBack6 = VECTOR3(-5.5f, 4.0f, 0.0f);
	leftFront6 = VECTOR3(-7.0f, -4.0f, 0.0f);
	leftBack6 = VECTOR3(-5.5f, -4.0f, 0.0f);

	// 面の回転を保存する変数
	rotateMapNorthNow = 0;
	// falseならばマップの回転を止める
	rotateOkFlag = true;
	oneScreenFlag = false;  // 1面のみ描画フラグ
	initialStart = true;    // 最初のスタート処理
	trainStep = 0;           // 移動距離
	NewSurfaceNum = 0;       // プレイキャラがいる面	
}
// ---------------------------------------------------------------------------
//
// ＰＣプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CPcProc::~CPcProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================
//
// ＰＣオブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_bActive		= TRUE;
	m_dwStatus		= NORMAL;
	m_fLocalRotY = 0.0f;                   // -- 2018.8.4
	m_bSide = TRUE;                        // -- 2018.8.4
	// m_fSpeedをもし10倍したらmoveTimesMaxを10分の1すればよい（スピード変更）
	m_fSpeed = 0.015f;    // 一回の移動スピード M.S
	m_fRotSpeed = 8.0f;   // 回転速度      // -- 2019.3.5
	m_fJumpSpeed = 0.2f;  // ジャンプ速度  // -- 2019.3.5
	 moveTimes = 0;  
	 // 一回の移動スピードが0.015f、1移動の完了が1mなのでmoveTimesのMAX66回  M.S
	 moveTimesMax = 66;      
	 oldHP = m_pGMain->initialH;           // 最初の現在地 行 M.S
	 oldVP = m_pGMain->initialV;           // 最初の現在地 列 M.S
	 changeStepNum = 0;       // 方向切り替えブロックの挙動の管理
	// バウンディングボックスの設定
	m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3( -0.16f, 0.0f, -0.25f), VECTOR3(0.15f, 0.32f, 0.24f));
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11
	m_mWorldOld = m_mWorld;
	// M.S ここから下のコンストラクタの内容は追加しました
	////// ↓--------------------------------------------------------------------
	trainDirectionFlag = 1;    // 向かっている方向の保存
	upArrow = 1;     // 上
	rightArrow = 2;  // 右
	downArrow = 3;   // 下
	leftArrow = 4;   // 左
	// ゲームオーバーのアニメフェーズ
	gameOverAnim = 0;
	DoneMove = false;   	   // 1ループ中に移動をしたかどうかを入れる変数
	chPlacementNearH = oldHP - 1;
	chPlacementH = oldHP - 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP + 1;
	edgePos = 9;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;                      // 方向切り替え線路のプレイキャラの回転変数
	moveValueH = 2;      	                 // 次の線路までの移動する距離(行)
	moveValueV = 1;      	                 // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                   // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                       // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                  // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
	surfaceNum = 0;      // プレイキャラがいる位置
	frontFlag = true;   // 正面にプレイキャラがいるフラグ  
	nowPcPosNum = 0;     // 原点から見て(+Y軸が上で-z軸がこちらに向いているの状態) 0:上 1:手前 2:下 3:1の裏 4:右 5:左
	needRotateFlag = 0;       // マップの面から面に移動する際のプレイヤー位置に掛ける変数の数の調整用変数
	edgeFlag = false;  // 端から次の面への移動フラグをfalse

	gameOverTime = 100;  // ゲームオーバーアニメーションが終わった後のカウント
	animCount = 59;      // ゲームオーバーアニメーションの調整カウント
	startTime = 0;       // ゲーム開始までのカウント
	startTimeFlag = false;  // ゲーム開始フラグ
}
// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj() 
{
}
// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのメッシュポインタ設定
//
//  CPcProc* pProc
//
// ---------------------------------------------------------------------------
void CPcObj::SetMesh(CPcProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
	m_nHoldItem = pProc->GetHoldItem();			// 手に持つ武器の情報を得る  // -- 2020.6.21
	m_AnimStatus.SetNum(0);                     // アニメーションのセット
	m_AnimStatus.animFrame = 0;                 // アニメーションフレームのセット
}
// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CPcObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}
//M.S ゲームの初期化をする関数
//引  数：なし
//戻り値：なし
void	CPcProc::ResetNewGamePc() {
	GetPcObjPtr()->oldHP = m_pGMain->initialH;  // 4
	GetPcObjPtr()->oldVP = m_pGMain->initialV;  // 4
	GetPcObjPtr()->changeStepNum = 0;
	GetPcObjPtr()->surfaceNum = 0;
	GetPcObjPtr()->frontFlag = true;
	GetPcObjPtr()->nowPcPosNum = 0;
	GetPcObjPtr()->trainDirectionFlag = 1;
	GetPcObjPtr()->edgeFlag = false;
	GetPcObjPtr()->ResetNewGamePcObj();
	for (int hori = 0; hori < 10; hori++) {
		for (int ver = 0; ver < 10; ver++) {
			lineMapSub[hori][ver] = { 0 };
		}
	}
	rotateMapNorthNow = 0;
	rotateOkFlag = true;
	oneScreenFlag = false;
	initialStart = true;
	trainStep = 0;
	// BackForeの初期化
	m_pGMain->m_pBackForeProc->initialDraw = 0;
	m_pGMain->m_pBackForeProc->builtStarBridge = false;
	m_pGMain->m_pBackForeProc->initialWaitingNumSet = true;
	// Titleの初期化
	m_pGMain->m_pTitleProc->initialRankingSorting = true;
	m_pGMain->stopOperation = false;
	//  Title ゲームクリア、オーバー、リザルトの初期サウンド処理の初期化
	m_pGMain->m_pTitleProc->RingSound = false;
	m_pGMain->m_pTitleProc->RingResultSound = false;
}
//M.S ゲームの初期化をする関数
//引  数：なし
//戻り値：なし
void	CPcObj::ResetNewGamePcObj() {
	m_fLocalRotY = 0.0f;
	moveTimes = 0;
	m_AnimStatus.playAnim = true;
	m_AnimStatus.SetNum(0);
	gameOverTime = 100;
	animCount = 59;
	startTimeFlag = false;
}
//-----------------------------------------------------------------------------
// ＰＣオブジェクトの更新
//
//　キーボードでＰＣを動かす
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還、マップとの接触判定
//　ＰＣの攻撃処理を行う
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{
	// M.S 最初のスタ―ト処理をしていないかどうか
	if (m_pGMain->m_pPcProc->initialStart == true) {
		if (m_pGMain->m_dwGameMode != 3) {      // M.S ランキングモード以外だったら
			// M.S startTimeに発射までの待ち時間を入れる
			startTime = m_pGMain->waitingTimeSelectNum * 60;
		}
		else if (m_pGMain->m_dwGameMode == 3) { // M.S ランキングモードだったら
			// M.S startTimeに発射までの待ち時間を入れる
			startTime = m_pGMain->rankWaitingTimeSelectNum * 60;
		}
		// M.S 最初のスタ―ト処理フラグ(initialStart)をfalse
		m_pGMain->m_pPcProc->initialStart = false;
	}
	if (m_pGMain->transparentSwitch == true) {   // M.S キャラクターの非表示フラグがtrueかどうか
		m_bActive = false;   // M.S キャラクターの表示をfalse
	}
	else {
		startTime--;  // M.S startTimeを減らす
		// M.S 待ち時間が0以下かつ、スタート可能フラグがtrueかつ
		//     人キャラの乗車処理中でないかどうか
		if (startTime <= 0 && startTimeFlag == true 
			&& m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess == false
			&& m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess == false 
			&& m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess == false) {
			startTime = 0;                       // M.S startTimeを0にする
			m_bActive = true;                    // M.S キャラの表示
			m_pGMain->m_pPcProc->rotateOkFlag = false;     // M.S マップの回転を止める
			// 一つ前の位置を保存
			m_mWorldOld = m_mWorld;
			UpdateNormal();  // ＰＣオブジェクトの更新 通常状態（NORMAL）
			// マップコリジョンと自然落下
    		m_fJumpY += (0.5f*GRAVITY*0.00005f)*m_fJumpTime;	// 自然落下
			m_fJumpTime += 1.0f;
			if (m_pGMain->m_pMapProc->isCollisionMoveGravity(&m_mWorld, m_mWorldOld) != 3)  // マップコリジョン
			{
				m_fJumpY = 0.0f;  // 自然落下の停止
				m_fJumpTime = 0.0f;
			}
			//レンダリング
			int shineFlag = 0;    // レンダーの指定 M.S	
			m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
			// バウンディングボックス
			m_pBBox->m_mWorld = m_mWorld;
			// 手に持つ武器やアイテムの表示をする     // -- 2021.2.4
			if (m_nHoldItem.m_nHoldObjNo != 0) // 手に持つ武器やアイテムがあるとき
			{
				MATRIX4X4 mHold;
				mHold = m_pMesh->GetFrameMatrices(m_AnimStatus, m_mWorld, m_nHoldItem.m_nPosBone, m_nHoldItem.m_nPosMesh);  // 手の位置のボーンマトリックス
				m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->Disp(mHold, m_nHoldItem); // アイテム表示
			}

		}  // M.S それ以外(乗車処理中など)だった場合
		else {
			if (frontFlag == true) {   	// M.S キャラが操作可能面にいるかどうか
				frontFlag = false;      // M.S frontFlagをfalse 
			}
			// M.S nowPositionRideStopにキャラの現在地を入れる
			VECTOR3 nowPositionRideStop = GetPositionVector(m_mWorld);
			// M.S キャラの現在地(面)の取得
			JudgeNowPcMap(nowPositionRideStop, false);
			// M.S キャラがいる面マップの更新をする
			m_pGMain->m_pPcProc->lineMapNew(surfaceNum);
			//レンダリング
			int shineFlag = 0;   // レンダーの指定 M.S	
			m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
		}
	}
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの更新 通常状態（NORMAL）
//
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還、マップとの接触判定
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormal()
{
	if (m_dwStatus == FLASH) // ＰＣがダメージから復帰したときの処理
	{
		m_nCnt1--;
		if (m_nCnt1 <= 0) m_dwStatus = NORMAL;
	}
	UpdateNormalMove();      // ＰＣオブジェクトの移動処理
	// 全ての敵のバウンディングボックスとのあたり判定
	if (m_dwStatus != FLASH) m_pGMain->m_pEnmProc->Hitcheck(this, m_pBBox);   // -- 2019.6.8
}
// M.S
// プレイキャラがいるマップ配列を持ってくる関数
// 引  数：int surfaceNum    更新したい面(プレイキャラがいる面)の数字
// 戻り値：なし
void CPcProc::lineMapNew(int surfaceNum) {
	// 面によって保存されているlineMapBufをlineMapSubに持ってくる
	switch (surfaceNum) {
	case 0:     // 初期ゲーム画面上で正面
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf1[h][v];
			}
		}
		break;
	case 1:     // 初期ゲーム画面上で正面の下
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf2[h][v];
			}
		}
		break;
	case 2:    // 初期ゲーム画面上で正面の裏側
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf3[h][v];
			}
		}
		break;
	case 3:    // 初期ゲーム画面上で正面の上
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf4[h][v];
			}
		}
		break;
	case 4:    // 初期ゲーム画面上で正面の右
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf5[h][v];
			}
		}
		break;
	case 5:   // 初期ゲーム画面上で正面の左
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf6[h][v];
			}
		}
		break;
	}
}
// M.S
// プレイキャラがいたマップ配列を記録する関数
// 引  数：int oldsurfaceNum    プレイキャラがいた面の数字
// 戻り値：なし
void CPcProc::lineMapSet(int oldsurfaceNum) {
	// 先に操作マップを書き換えないようにする
		// 回転のしたものをいれる
	switch (oldsurfaceNum) {
	case 0:     // 初期ゲーム画面上で正面
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf1[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 1:    // 初期ゲーム画面上で正面の下
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf2[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 2:    // 初期ゲーム画面上で正面の裏側
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf3[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 3:    // 初期ゲーム画面上で正面の上
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf4[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 4:    // 初期ゲーム画面上で正面の右
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf5[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 5:    // 初期ゲーム画面上で正面の左
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf6[h][v] = lineMapSub[h][v];
			}
		}
		break;
	}
}
// M.S
// 絶対値からキャラの上がX軸、Y軸、Z軸のどこを向いているのか調べる
// 引  数：int                kindNum    0はプレイキャラの場合  1は人キャラの場合
//       ：Vector             pos        キャラの位置
// 戻り値：なし
void CPcProc::JudgeAbsoluteSize(int kindNum, VECTOR3 pos) {
	float upperLimit;
	float upPos = 6.0f;
	if (kindNum == 0) {
		upperLimit = 5.0f;
	}
	else if (kindNum == 1) {
		upperLimit = 4.7f;
	}
	// 100倍してintにキャストをする
	float castX = pos.x * 100.0f;
	float castY = pos.y * 100.0f;
	float castZ = pos.z * 100.0f;
	int castX1 = (int)castX;
	int castY1 = (int)castY;
	int castZ1 = (int)castZ;
	// 100分の1してposの値の小数第二位未満を切る
	castX = castX1 / 100.0f;
	castY = castY1 / 100.0f;
	castZ = castZ1 / 100.0f;
	// 絶対値を求める
	float x = fabsf(castX);
	float y = fabsf(castY);
	float z = fabsf(castZ);
	// xがupperLimitより大きいかどうか
	if (x >= upperLimit) {
		x = x - 6.0f;     
	}
	else {
		x = 100;
	}
	// yがupperLimitより大きいかどうか
	if (y >= upperLimit) {
		y = y - 6.0f;
	}
	else {
		y = 100;
	}
	// zがupperLimitより大きいかどうか
	if (z >= upperLimit) {
		z = z - 6.0f;
	}
	else {
		z = 100;
	}
	// 絶対値を求める
	float conmpX = fabsf(x);
	float conmpY = fabsf(y);
	float conmpZ = fabsf(z);
	// conmpX,conmpY,conmpZを比べて一番小さい値(向いている軸)の変数をtrue
	if (conmpX < conmpY && conmpX < conmpZ) {
		this->xJudge = true;
	}
	else if (conmpY < conmpX && conmpY < conmpZ) {
		this->yJudge = true;
	}
	else if (conmpZ < conmpX && conmpZ < conmpY) {
		this->zJudge = true;
	}
}
// M.S
// 回転の角度を調べる関数
// 引  数：int                 surfaceNum          調べる面の数字
//       ：float               upBack              BBoxを調べる上のレイの位置(奥)
//       ：float               upFront             BBoxを調べる上のレイの位置(前)
//       ：float               downBack            BBoxを調べる下のレイの位置(奥)
//       ：float               downFront           BBoxを調べる下のレイの位置(前)
//       ：float               rightBack           BBoxを調べる右のレイの位置(奥)
//       ：float               rightFront          BBoxを調べる右のレイの位置(前)
//       ：float               leftBack            BBoxを調べる左のレイの位置(奥)
//       ：float               leftFront           BBoxを調べる左のレイの位置(前)
// 戻り値：int                 rotateMapNorthNow   右回転 1:回転なし 2:+90度回転 3:+180度回転 4:+270度回転
int CPcProc::JudgeRotateSurface(int surfaceNum, VECTOR3 upBack, VECTOR3 upFront,
	                           VECTOR3 downBack, VECTOR3 downFront, VECTOR3 rightBack,
	                           VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront) {
	switch (surfaceNum) {
	case 0:
		rotateMapNorthNow = JudgeRotateSurfaceUp(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 1:
		rotateMapNorthNow = JudgeRotateSurfaceUnder(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 2:
		rotateMapNorthNow = JudgeRotateSurfaceDown(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 3:
		rotateMapNorthNow = JudgeRotateSurfaceAbove(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 4:
		rotateMapNorthNow = JudgeRotateSurfaceRight(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 5:
		rotateMapNorthNow = JudgeRotateSurfaceLeft(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	}
	return 5;
}
// M.S
// 回転の角度を調べる関数(初期状態で正面の面)
// 引  数：VECTOR3               upBack              BBoxを調べる上のレイの位置(奥)
//       ：VECTOR3               upFront             BBoxを調べる上のレイの位置(前)
//       ：VECTOR3               downBack            BBoxを調べる下のレイの位置(奥)
//       ：VECTOR3               downFront           BBoxを調べる下のレイの位置(前)
//       ：VECTOR3               rightBack           BBoxを調べる右のレイの位置(奥)
//       ：VECTOR3               rightFront          BBoxを調べる右のレイの位置(前)
//       ：VECTOR3               leftBack            BBoxを調べる左のレイの位置(奥)
//       ：VECTOR3               leftFront           BBoxを調べる左のレイの位置(前)
// 戻り値：int                 rotateMapNorthNow   右回転 1:回転なし 2:+90度回転 3:+180度回転 4:+360度回転
int CPcProc::JudgeRotateSurfaceUp(VECTOR3 upBack, VECTOR3 upFront,VECTOR3 downBack, 
	                              VECTOR3 downFront, VECTOR3 rightBack,VECTOR3 rightFront, 
	                              VECTOR3 leftBack, VECTOR3 leftFront) {
	//上下左右にレイを飛ばして元のマップからどれだけ回転しているかみる
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow1[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow1[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow1[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow1[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// 回転の角度を調べる関数(初期状態で正面の下の面)
// 引  数：VECTOR3               upBack              BBoxを調べる上のレイの位置(奥)
//       ：VECTOR3               upFront             BBoxを調べる上のレイの位置(前)
//       ：VECTOR3               downBack            BBoxを調べる下のレイの位置(奥)
//       ：VECTOR3               downFront           BBoxを調べる下のレイの位置(前)
//       ：VECTOR3               rightBack           BBoxを調べる右のレイの位置(奥)
//       ：VECTOR3               rightFront          BBoxを調べる右のレイの位置(前)
//       ：VECTOR3               leftBack            BBoxを調べる左のレイの位置(奥)
//       ：VECTOR3               leftFront           BBoxを調べる左のレイの位置(前)
// 戻り値：int                 rotateMapNorthNow   右回転 1:回転なし 2:+90度回転 3:+180度回転 4:+360度回転
int CPcProc::JudgeRotateSurfaceUnder(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                 VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
	                                 VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow4[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow4[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow4[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow4[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// 回転の角度を調べる関数(初期状態で正面の裏の面)
// 引  数：VECTOR3               upBack              BBoxを調べる上のレイの位置(奥)
//       ：VECTOR3               upFront             BBoxを調べる上のレイの位置(前)
//       ：VECTOR3               downBack            BBoxを調べる下のレイの位置(奥)
//       ：VECTOR3               downFront           BBoxを調べる下のレイの位置(前)
//       ：VECTOR3               rightBack           BBoxを調べる右のレイの位置(奥)
//       ：VECTOR3               rightFront          BBoxを調べる右のレイの位置(前)
//       ：VECTOR3               leftBack            BBoxを調べる左のレイの位置(奥)
//       ：VECTOR3               leftFront           BBoxを調べる左のレイの位置(前)
// 戻り値：int                 rotateMapNorthNow  右回転 1:回転なし 2:+90度回転 3:+180度回転 4:+360度回転
int CPcProc::JudgeRotateSurfaceDown(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
	                                VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow3[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow3[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow3[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow3[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// 回転の角度を調べる関数(初期状態で正面の上の面)
// 引  数：int                 upBack              BBoxを調べる上のレイの位置(奥)
//       ：VECTOR3               upFront             BBoxを調べる上のレイの位置(前)
//       ：VECTOR3               downBack            BBoxを調べる下のレイの位置(奥)
//       ：VECTOR3               downFront           BBoxを調べる下のレイの位置(前)
//       ：VECTOR3               rightBack           BBoxを調べる右のレイの位置(奥)
//       ：VECTOR3               rightFront          BBoxを調べる右のレイの位置(前)
//       ：VECTOR3               leftBack            BBoxを調べる左のレイの位置(奥)
//       ：VECTOR3               leftFront           BBoxを調べる左のレイの位置(前)
// 戻り値：int                 rotateMapNorthNow   右回転 1:回転なし 2:+90度回転 3:+180度回転 4:+360度回転
int CPcProc::JudgeRotateSurfaceAbove(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                 VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
                                   	 VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow2[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow2[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow2[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow2[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// 回転の角度を調べる関数(初期状態で正面の右の面)
// 引  数：VECTOR3               upBack              BBoxを調べる上のレイの位置(奥)
//       ：VECTOR3               upFront             BBoxを調べる上のレイの位置(前)
//       ：VECTOR3               downBack            BBoxを調べる下のレイの位置(奥)
//       ：VECTOR3               downFront           BBoxを調べる下のレイの位置(前)
//       ：VECTOR3               rightBack           BBoxを調べる右のレイの位置(奥)
//       ：VECTOR3               rightFront          BBoxを調べる右のレイの位置(前)
//       ：VECTOR3               leftBack            BBoxを調べる左のレイの位置(奥)
//       ：VECTOR3               leftFront           BBoxを調べる左のレイの位置(前)
// 戻り値：int                 rotateMapNorthNow   右回転 1:回転なし 2:+90度回転 3:+180度回転 4:+360度回転
int CPcProc::JudgeRotateSurfaceRight(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                 VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
	                                 VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow5[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow5[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow5[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow5[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// 回転の角度を調べる関数(初期状態で正面の左の面)
// 引  数：VECTOR3               upBack              BBoxを調べる上のレイの位置(奥)
//       ：VECTOR3               upFront             BBoxを調べる上のレイの位置(前)
//       ：VECTOR3               downBack            BBoxを調べる下のレイの位置(奥)
//       ：VECTOR3               downFront           BBoxを調べる下のレイの位置(前)
//       ：VECTOR3               rightBack           BBoxを調べる右のレイの位置(奥)
//       ：VECTOR3               rightFront          BBoxを調べる右のレイの位置(前)
//       ：VECTOR3               leftBack            BBoxを調べる左のレイの位置(奥)
//       ：VECTOR3               leftFront           BBoxを調べる左のレイの位置(前)
// 戻り値：int                 rotateMapNorthNow  右回転 1:回転なし 2:+90度回転 3:+180度回転 4:+360度回転
int CPcProc::JudgeRotateSurfaceLeft(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
	                                VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow6[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow6[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow6[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow6[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// キャラがいる位置のマップ面の回転の角度を調べる関数
// 引  数：int                surfaceNum             調べる面の数字
//       ：Vector             pos                    キャラの位置
//       ：int                kindNum                0はプレイキャラの場合  1は人キャラの場合              
// 戻り値：int                rotateMapNorthNow      右回転 1:回転なし 2:右90度回転 3:右180度回転 4:右270度回転
int CPcProc::judgeDirection(int surfaceNum, VECTOR3 pos, int kindNum) {
	// 調べるキャラの上はどこに向いているか調べるための変数
	float charLimit = 5.5f;
	float charLimitMinus = -5.5f;
	float manLimit = 4.7f;
	float manLimitMinus = -4.7f;
	xJudge = false;           // x軸の値に対応したbool変数
	yJudge = false;           // y軸の値に対応したbool変数
	zJudge = false;           // z軸の値に対応したbool変数
	// マップ面の回転に合わせてtrueになるフラグの初期化
	directrioFlag1 = false;
	directrioFlag2 = false;
	directrioFlag3 = false;
	directrioFlag4 = false;
	// 絶対値からキャラの上がどこに向いているのか調べる
    // xJudge、yJudgey、zJudgeのどれかにtrueが入ったので、どの軸を向いているかわかる
	JudgeAbsoluteSize(kindNum, pos);
	// マップ面識別変数rotateMapNorthNow 右回転 1:回転なし 2:+90度回転 3:+180度回転 4:+360度回転
	if (yJudge == true) {
		if (kindNum == 0 && pos.y >= charLimit || kindNum == 1 && pos.y >= manLimit) {           // 初期ゲーム画面でカメラの正面

			return JudgeRotateSurface(surfaceNum, upBack1, upFront1, downBack1, downFront1, rightBack1, rightFront1, leftBack1, leftFront1);			
		}
	}
	if (zJudge == true) {
    	if (kindNum == 0 && pos.z <= charLimitMinus || kindNum == 1 && pos.z <= manLimitMinus) { // 初期ゲーム画面でカメラの正面の下
			return JudgeRotateSurface(surfaceNum, upBack2, upFront2, downBack2, downFront2, rightBack2, rightFront2, leftBack2, leftFront2);
		}
	}
	if (yJudge == true) {
    	if (kindNum == 0 && pos.y <= charLimitMinus || kindNum == 1 && pos.y <= manLimitMinus) { // 初期ゲーム画面でカメラの正面の裏側
			return JudgeRotateSurface(surfaceNum, upBack3, upFront3, downBack3, downFront3, rightBack3, rightFront3, leftBack3, leftFront3);
		}
	}
	if (zJudge == true) {
	   if (kindNum == 0 && pos.z >= charLimit || kindNum == 1 && pos.z >= manLimit) {           // 初期ゲーム画面でカメラの正面の上
		   return JudgeRotateSurface(surfaceNum, upBack4, upFront4, downBack4, downFront4, rightBack4, rightFront4, leftBack4, leftFront4);
		}
	}
	if (xJudge == true) {
		if (kindNum == 0 && pos.x >= charLimit || kindNum == 1 && pos.x >= manLimit) {          // 初期ゲーム画面でカメラの正面の右
			return JudgeRotateSurface(surfaceNum, upBack5, upFront5, downBack5, downFront5, rightBack5, rightFront5, leftBack5, leftFront5);
		}
	}
	if (xJudge == true) {
		if (kindNum == 0 && pos.x <= charLimitMinus || kindNum == 1 && pos.x <= manLimitMinus) { // 初期ゲーム画面でカメラの正面の左
			return JudgeRotateSurface(surfaceNum, upBack6, upFront6, downBack6, downFront6, rightBack6, rightFront6, leftBack6, leftFront6);
		}
	}
	return 5;
}
// M.S
// マップ面の端から次の面へ移動する時の現在地の更新
// 引  数：int                trainDirectionFlag            キャラが移動している方向
//                                                           1：上  2：右  3：下  4：左
//       ：int                oldHP                         更新前のキャラの位置(行)
//       ：int                oldVP                         更新前のキャラの位置(列)
//       ：int                surfaceNum                    移動前の面の数字
// 戻り値：なし
void CPcObj::updateEdgeOldHV(int trainDirectionFlag,int oldHP, int oldVP, int surfaceNum) {
	// プレイキャラが上端にいて、移動方向が上だったら
	if (oldHP == 0 && trainDirectionFlag == 1) {   
		switch (surfaceNum) {
		case 0:                   // 初期ゲーム画面でカメラの正面
			this->oldHP = 10;
			this->oldVP = oldVP;
			break;
		case 1:
			this->oldHP = 10;
			this->oldVP = oldVP;
			break;
		case 2:
			this->oldHP = 10;
			this->oldVP = oldVP;	
			break;
		case 3:
			this->oldHP = 10;
			this->oldVP = oldVP;
			break;
		case 4:
			this->oldHP = 9 - oldVP;
			this->oldVP = 10;
			this->trainDirectionFlag = 4;
			break;
		case 5:
			this->oldHP = oldVP;
			this->oldVP = -1;
			this->trainDirectionFlag = 2;
			break;
		}
	}// プレイキャラが下端にいて、移動方向が下だったら
	else if (oldHP == 9 && trainDirectionFlag == 3) { 
		switch (surfaceNum) {
		case 0:
		    this->oldHP = -1;
			this->oldVP = oldVP;
			break;
		case 1:
		   	this->oldHP = -1;
			this->oldVP = oldVP;
			break;
		case 2:
			this->oldHP = -1;
			this->oldVP = oldVP;
			break;
		case 3:
			this->oldHP = -1;
			this->oldVP = oldVP;
			break;
		case 4:
			this->oldHP = oldVP;
			this->oldVP = 10;
			this->trainDirectionFlag = 4;
			break;
		case 5:
			this->oldHP = 9 - oldVP;
			this->oldVP = -1;
			this->trainDirectionFlag = 2;
			break;	
		}
	}// プレイキャラが左端にいて、移動方向が左だったら
	else if (oldVP == 0 && trainDirectionFlag == 4) {
		switch (surfaceNum) {
		case 0:
			//if (PlacementSurfaceNum == 0) {
			this->oldHP = oldHP;
			this->oldVP = 10;
			break;
		case 1:
			this->oldHP = 10;
			this->oldVP = 9 - oldHP;
			this->trainDirectionFlag = 1;
			break;
		case 2:
			this->oldHP = 9 - oldHP;
			this->oldVP = -1;
			this->trainDirectionFlag = 2;
			break;
		case 3:
			this->oldVP = oldHP;
			this->oldHP = -1;
			this->trainDirectionFlag = 3;
			break;		
		case 4:
			this->oldHP = oldHP;
			this->oldVP = 10;
			break;
		case 5:
			this->oldHP = 9 - oldHP;
			this->oldVP = -1;
			this->trainDirectionFlag = 2;
			break;
		}
	}// プレイキャラが右端にいて、移動方向が右だったら
	else if (oldVP == 9 && trainDirectionFlag == 2) {
		switch (surfaceNum) {
		case 0:
			this->oldHP = oldHP;
			this->oldVP = -1;
			break;
		case 1:
			this->oldVP = oldHP;
			this->oldHP = 10;
			this->trainDirectionFlag = 1;
			break;
		case 2:
			this->oldHP = 9 - oldHP;
			this->oldVP = 10;
			this->trainDirectionFlag = 4;
			break;
		case 3:
			this->oldHP = -1;
			this->oldVP = 9 - oldHP;
			this->trainDirectionFlag = 3;
			break;
		case 4:
			this->oldHP = 9 - oldHP;
			this->oldVP = 10;
			this->trainDirectionFlag = 4;
			break;
		case 5:
			this->oldHP = oldHP;
			this->oldVP = -1;
			break;		
		}
	}
}
// M.S
// upBack、upFrontにレイを飛ばし、そのレイの場所にどこの面がいるのか調べる
// 引  数：MATRIX4X4          upBack           飛ばすレイの場所(奥)
//       ：MATRIX4X4          upFront          飛ばすレイの場所(手前)  
// 戻り値：int                                 当たった面の数字
int CPcObj::RayOrderSurfaceBBox(MATRIX4X4 upBack, MATRIX4X4 upFront) {
	for (int i = 0; i < 6; i++) {
		// 各面のBBoxを順番に見ていき、レイと当たるかどうか
		bool nowPosSurfaceflag = m_pGMain->m_pMapProc->m_pBBoxPosition[i]->OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
		// 当たったらその面の数字をsurfaceNumに入れる
		if (nowPosSurfaceflag == true) {
			surfaceNum = i;
			return surfaceNum;
		}
	}
	return 10;
}
// M.S
// キャラがいる面の数字や位置を調べる
// 引  数：VECTOR3          nowPosition           キャラがいる位置
//       ：bool             onlyFront             true  ：正面(操作可能面)にいるかどうか判定のみ行う
//                                                      false ：すべての処理を行う
//                                                      nowPcPosNumにはキャラの位置の数字が入っています
//                                                      nowPcPosNum 0:上 1:手前 2:下 3:1の裏 4:右 5:左
// 戻り値：int                                          キャラがいる面の数字
int CPcObj::JudgeNowPcMap(VECTOR3 nowPosition, bool onlyFront) {
	float charLimit = 5.5f;
	float charLimitMinus = -5.5f;
	m_pGMain->m_pPcProc->xJudge = false;           // x軸の値に対応したbool変数
	m_pGMain->m_pPcProc->yJudge = false;           // y軸の値に対応したbool変数
	m_pGMain->m_pPcProc->zJudge = false;           // z軸の値に対応したbool変数
	// 絶対値からキャラの上がどこに向いているのか調べる
	// xJudge、yJudgey、zJudgeのどれかにtrueが入ったので、どの軸を向いているかわかる
	m_pGMain->m_pPcProc->JudgeAbsoluteSize(0, nowPosition);
	if (m_pGMain->m_pPcProc->yJudge == true) {         // 初期ゲーム画面でカメラの正面
		if (nowPosition.y >= charLimit) {  
				// BBoxへ飛ばすレイ
				MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 10.0f, 0.0f);  // 手前
				MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 3.0f, 0.0f);    // 奥
				nowPcPosNum = 0;            // 場所の値  
				frontFlag = true;           // 正面にプレイキャラがいるフラグをtrue
				if (onlyFront == true) {   	// 正面(操作可能面)にいるかどうか判定のみ行うかどうか
					return 10;
				}  
				return RayOrderSurfaceBBox(upBack, upFront);  // 各面のBBoxにレイを飛ばし、当たった面の数字を返す
		}
	}
	if (m_pGMain->m_pPcProc->zJudge == true) {         // 初期ゲーム画面でカメラの正面の下
		if (nowPosition.z <= charLimitMinus) {
				// BBoxへ飛ばすレイ
				MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 0.0f, -10.0f);  // 手前
				MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 0.0f, -3.0f);    // 奥
				nowPcPosNum = 1;          // 場所の値 
				return RayOrderSurfaceBBox(upBack, upFront);   // 各面のBBoxにレイを飛ばし、当たった面の数字を返す
		}
	}
	if (m_pGMain->m_pPcProc->yJudge == true) {
		if (nowPosition.y <= charLimitMinus) {         // 初期ゲーム画面でカメラの正面の裏側
				// BBoxへ飛ばすレイ
				MATRIX4X4 upFront = XMMatrixTranslation(0.0f, -10.0f, 0.0f);  // 手前
				MATRIX4X4 upBack = XMMatrixTranslation(0.0f, -3.0f, 0.0f);    // 奥
				nowPcPosNum = 2;          // 場所の値  
				return RayOrderSurfaceBBox(upBack, upFront);   // 各面のBBoxにレイを飛ばし、当たった面の数字を返す
		}
	} 
	if (m_pGMain->m_pPcProc->zJudge == true) {
		if (nowPosition.z >= charLimit) {              // 初期ゲーム画面でカメラの正面の上
				// BBoxへ飛ばすレイ
				MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 0.0f, 10.0f);   // 手前
				MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 0.0f, 3.0f);     // 奥
				nowPcPosNum = 3;          // 場所の値 
				return RayOrderSurfaceBBox(upBack, upFront);   // 各面のBBoxにレイを飛ばし、当たった面の数字を返す
		}
	}
	if (m_pGMain->m_pPcProc->xJudge == true) {
		if (nowPosition.x >= charLimit) {              // 初期ゲーム画面でカメラの正面の右
				// BBoxへ飛ばすレイ
				MATRIX4X4 upFront = XMMatrixTranslation(10.0f, 0.0f, 0.0f);    // 手前
				MATRIX4X4 upBack = XMMatrixTranslation(3.0f, 0.0f, 0.0f);      // 奥
				nowPcPosNum = 4;          // 場所の値 
				return RayOrderSurfaceBBox(upBack, upFront);   // 各面のBBoxにレイを飛ばし、当たった面の数字を返す
		}
	}
	if (m_pGMain->m_pPcProc->xJudge == true) {
		if (nowPosition.x <= charLimitMinus) {         // 初期ゲーム画面でカメラの正面の左
				// BBoxへ飛ばすレイ
				MATRIX4X4 upFront = XMMatrixTranslation(-10.0f, 0.0f, 0.0f);   // 手前
				MATRIX4X4 upBack = XMMatrixTranslation(-3.0f, 0.0f, 0.0f);     // 奥
				nowPcPosNum = 5;         // 場所の値 
				return RayOrderSurfaceBBox(upBack, upFront);    // 各面のBBoxにレイを飛ばし、当たった面の数字を返す
		}
	}
	return -1;
}
// M.S
// キャラの右移動処理
// 引  数：なし
// 戻り値：なし     
void	CPcObj::MoveRight(){
	// 右移動
	// 配置できない配列の上限値(upper)、下限値(lower)
	// Hが行、Vが列
	float upperLimitH = 10;
	float lowerLimitH = 0;
	float upperLimitV = 9;
	float lowerLimitV = -1;
	int moveValue = 1;      	// 次の線路へ移動する距離
	int loopPlusMoveTimes = 1;  // ループして進んでいく度にmoveTimesに足す変数
	int lineNum = 1;            // 直線線路の配列にいれた数字
	int stationNum = 3;         // 駅の配列にいれた数字
	int afterLineNum = 5;       // 直線線路の通過後に配列にいれる数字
	int afterStationNum = 8;    // 駅の通過後に配列にいれる数字
	// プレイキャラの位置が配置可能範囲かどうか
	// プレイキャラの位置が配置可能範囲かどうか
	if (oldHP < upperLimitH && oldHP >= lowerLimitH && oldVP < upperLimitV && oldVP >= lowerLimitV) {
		if (trainDirectionFlag == rightArrow) {       // プレイヤーが右方向に進んでいるかどうか
			if (frontFlag == true) {         //プレイヤーが正面の場合
				// 配列の現在地の列+1に直線線路または駅が配置されているかどうか
				if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] == lineNum
					|| m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] == stationNum) {
					DoneMove = true;         // 移動したフラグをtrue
					// 一つの線路の移動が終わっていなければ
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed); // 移動させる
						moveTimes += loopPlusMoveTimes;        // 移動変数(moveTimes)を+1
					}
					// 一つの線路の移動が終わっていれば
					else {
						// 配置されているオブジェクトが線路ならば
						if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] == lineNum) {
							// 配列にafterLineNumを入れる
							m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] = afterLineNum;
						}
						// 配置されているオブジェクトが駅ならば
						else if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] == stationNum) {
							// 配列にafterStationNumを入れる
							m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] = afterStationNum;
						}
						oldVP += moveValue;                       // 現在地の更新
						if (oldVP == upperLimitV) {                 // 移動後が端の位置ならば
							edgeFlag = true;              // edgeFlagをtrue
						}
						moveTimes = 0;                    // 移動変数(moveTimes)を0に初期化
						trainDirectionFlag = rightArrow;           // 移動方向を右にする
						m_pGMain->m_pPcProc->trainStep++; // 移動距離をたす
					}
				}
			}
			else if (frontFlag == false) {  //プレイヤーが正面以外の場合
				// 配列の現在地の列+1に直線線路または駅が配置されているかどうか
				if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] == lineNum
					|| m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] == stationNum) {
					DoneMove = true;              // 移動したフラグをtrue
					// 一つの線路の移動が終わっていなければ
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);  // 移動させる
						moveTimes += loopPlusMoveTimes;     // 移動変数(moveTimes)を+1
					}
					// 一つの線路の移動が終わっていれば
					else {
						// 配置されているオブジェクトが線路ならば
						if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] == lineNum) {
							// 配列にafterLineNumを入れる
							m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] = afterLineNum;
						}
						// 配置されているオブジェクトが駅ならば
						else if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] == stationNum) {
							// 配列にafterStationNumを入れる
							m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] = afterStationNum;
						}
						oldVP += moveValue;                         // 現在地の更新
						if (oldVP == upperLimitV) {                 // 移動後が端の位置ならば
							edgeFlag = true;              // edgeFlagをtrue
						}
						moveTimes = 0;                    // 移動変数(moveTimes)を0に初期化
						trainDirectionFlag = rightArrow;           // 移動方向を右にする
						m_pGMain->m_pPcProc->trainStep++; // 移動距離をたす
					}
				}
			}
		}
	}
}
// M.S
// キャラの左移動処理
// 引  数：なし
// 戻り値：なし   
void	CPcObj::MoveLeft() {
	// 左移動
	// 配置できない配列の上限値(upper)、下限値(lower)
	// Hが行、Vが列
	float upperLimitH = 10;
	float lowerLimitH = 0;
	float upperLimitV = 11;
	float lowerLimitV = 1;
	int moveValue = 1;      	// 次の線路へ移動する距離
	int loopPlusMoveTimes = 1;  // ループして進んでいく度にmoveTimesに足す変数
	int lineNum = 1;            // 直線線路の配列にいれた数字
	int stationNum = 3;         // 駅の配列にいれた数字
	int afterLineNum = 5;       // 直線線路の通過後に配列にいれる数字
	int afterStationNum = 8;    // 駅の通過後に配列にいれる数字
	// プレイキャラの位置が配置可能範囲かどうか
	if (oldHP < upperLimitH && oldHP >= lowerLimitH && oldVP >= lowerLimitV && oldVP < upperLimitV) {
		if (trainDirectionFlag == leftArrow) {       // プレイヤーが左方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				// 配列の現在地の列-1に直線線路または駅が配置されているかどうか
				if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] == lineNum
					|| m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] == stationNum) {
					DoneMove = true;        // 移動したフラグをtrue
					// 一つの線路の移動が終わっていなければ
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);  // 移動させる
						moveTimes += loopPlusMoveTimes;     // 移動変数(moveTimes)を+1
					}
					// 一つの線路の移動が終わっていれば
					else {
						// 配置されているオブジェクトが線路ならば
						if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] == lineNum) {
							// 配列にafterLineNumを入れる
							m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] = afterLineNum;
						}
						// 配置されているオブジェクトが駅ならば
						else if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] == stationNum) {
							// 配列にafterStationNumを入れる
							m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] = afterStationNum;
						}
						oldVP -= moveValue;                          // 現在地の更新
						if (oldVP == lowerLimitH) {                    // 移動後が端の位置ならば
							edgeFlag = true;                 // edgeFlagをtrue
						}
						moveTimes = 0;                       // 移動変数(moveTimes)を0に初期化
						trainDirectionFlag = leftArrow;      // 移動方向を左にする
						m_pGMain->m_pPcProc->trainStep++;    // 移動距離をたす
					}
				}

			}
			else if (frontFlag == false) {  //プレイヤーが正面以外の場合
				// 配列の現在地の列-1に直線線路または駅が配置されているかどうか
				if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] == lineNum
					|| m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] == stationNum) {
					DoneMove = true;          // 移動したフラグをtrue
					// 一つの線路の移動が終わっていなければ
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);    // 移動させる
						moveTimes += loopPlusMoveTimes;       // 移動変数(moveTimes)を+1
					}
					// 一つの線路の移動が終わっていれば
					else {
						// 配置されているオブジェクトが線路ならば
						if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] == lineNum) {
							// 配列にafterLineNumを入れる
							m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] = afterLineNum;
						}
						// 配置されているオブジェクトが駅ならば
						else if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] == stationNum) {
							// 配列にafterStationNumを入れる
							m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] = afterStationNum;
						}
						oldVP -= moveValue;                 // 現在地の更新
						if (oldVP == 0) {                   // 移動後が端の位置ならば
							edgeFlag = true;                // edgeFlagをtrue
						}
						moveTimes = 0;                      // 移動変数(moveTimes)を0に初期化
						trainDirectionFlag = leftArrow;     // 移動方向を左にする
						m_pGMain->m_pPcProc->trainStep++;   // 移動距離をたす
					}
				}
			}
		}
	}
}
// M.S
// キャラの下移動処理
// 引  数：なし
// 戻り値：なし   
void	CPcObj::MoveDown() {
	// 下移動
	// 配置できない配列の上限値(upper)、下限値(lower)
	// Hが行、Vが列
	float upperLimitH = 9;
	float lowerLimitH = -1;
	float upperLimitV = 10;
	float lowerLimitV = 0;
	int moveValue = 1;      	// 次の線路へ移動する距離
	int loopPlusMoveTimes = 1;  // ループして進んでいく度にmoveTimesに足す変数
	int lineNum = 1;            // 直線線路の配列にいれた数字
	int stationNum = 3;         // 駅の配列にいれた数字
	int afterLineNum = 5;       // 直線線路の通過後に配列にいれる数字
	int afterStationNum = 8;    // 駅の通過後に配列にいれる数字
	// プレイキャラの位置が配置可能範囲かどうか
	if (oldHP < upperLimitH && oldHP >= lowerLimitH && oldVP < upperLimitV && oldVP >= lowerLimitV) {
		if (trainDirectionFlag == downArrow) {       // プレイヤーが下方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				// 配列の現在地の行+1に直線線路または駅が配置されているかどうか
				if (m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] == lineNum
					|| m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] == stationNum) {
					DoneMove = true;   // 移動したフラグをtrue
					// 一つの線路の移動が終わっていなければ
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);   // 移動させる
						moveTimes += loopPlusMoveTimes;      // 移動変数(moveTimes)を+1
					}
					// 一つの線路の移動が終わっていれば
					else {
						// 配置されているオブジェクトが線路ならば
						if (m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] == lineNum) {
							// 配列にafterLineNumを入れる
							m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] = afterLineNum;
						}
						// 配置されているオブジェクトが駅ならば
						else if (m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] == stationNum) {
							// 配列にafterStationNumを入れる
							m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] = afterStationNum;
						}
						oldHP += moveValue;                         // 現在地の更新
						if (oldHP == upperLimitH) {                   // 移動後が端の位置ならば
							edgeFlag = true;                // edgeFlagをtrue
						}
						moveTimes = 0;                      // 移動変数(moveTimes)を0に初期化
						trainDirectionFlag = downArrow;             // 移動方向を下にする
						m_pGMain->m_pPcProc->trainStep++;   // 移動距離をたす
					}
				}
			}
			else if (frontFlag == false) {   //プレイヤーが正面以外の場合
				// 配列の現在地の列-1に直線線路または駅が配置されているかどうか
				if (m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] == lineNum
					|| m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] == stationNum) {
					DoneMove = true;        // 移動したフラグをtrue
					// 一つの線路の移動が終わっていなければ
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);   // 移動させる
						moveTimes += loopPlusMoveTimes;     // 移動変数(moveTimes)を+1
					}
					// 一つの線路の移動が終わっていれば
					else {
						// 配置されているオブジェクトが線路ならば
						if (m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] == lineNum) {
							// 配列にafterLineNumを入れる
							m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] = afterLineNum;
						}
						// 配置されているオブジェクトが駅ならば
						else if (m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] == stationNum) {
							// 配列にafterStationNumを入れる
							m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] = afterStationNum;
						}
						oldHP += moveValue;                        // 現在地の更新
						if (oldHP == upperLimitH) {                  // 移動後が端の位置ならば
							edgeFlag = true;               // edgeFlagをtrue
						}
						moveTimes = 0;                     // 移動変数(moveTimes)を0に初期化
						trainDirectionFlag = downArrow;            // 移動方向を下にする
						m_pGMain->m_pPcProc->trainStep++;  // 移動距離をたす
					}
				}
			}
		}
	}
}
// M.S
// キャラの上移動処理
// 引  数：なし
// 戻り値：なし   
void	CPcObj::MoveUp() {
	//	上移動
	// 配置できない配列の上限値(upper)、下限値(lower)
	// Hが行、Vが列
	float upperLimitH = 11;
	float lowerLimitH = 1;
	float upperLimitV = 10;
	float lowerLimitV = 0;
	int moveValue = 1;      	// 次の線路へ移動する距離
	int loopPlusMoveTimes = 1;  // ループして進んでいく度にmoveTimesに足す変数
	int lineNum = 1;            // 直線線路の配列にいれた数字
	int stationNum = 3;         // 駅の配列にいれた数字
	int afterLineNum = 5;       // 直線線路の通過後に配列にいれる数字
	int afterStationNum = 8;    // 駅の通過後に配列にいれる数字
	// プレイキャラの位置が配置可能範囲かどうか
	if (oldHP < upperLimitH && oldHP >= lowerLimitH && oldVP < upperLimitV && oldVP >= lowerLimitV) {
		if (trainDirectionFlag == upArrow) {       // プレイヤーが上方向に進んでいるかどうか
			if (frontFlag == true) {    //プレイヤーが正面の場合
				// 配列の現在地の行-1に直線線路または駅が配置されているかどうか
				if (m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] == lineNum
					|| m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] == stationNum) {
					DoneMove = true;     // 移動したフラグをtrue
					// 一つの線路の移動が終わっていなければ
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);    // 移動させる
						moveTimes += loopPlusMoveTimes;       // 移動変数(moveTimes)を+1     
					}
					// 一つの線路の移動が終わっていれば
					else {
						// 配置されているオブジェクトが線路ならば
						if (m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] == lineNum) {
							// 配列にafterLineNumを入れる
							m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] = afterLineNum;
						}
						// 配置されているオブジェクトが駅ならば
						else if (m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] == stationNum) {
							// 配列にafterStationNumを入れる
							m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] = afterStationNum;
						}
						oldHP -= moveValue;                          // 現在地の更新
						if (oldHP == lowerLimitV) {          // 移動後が端の位置ならば
							edgeFlag = true;                 // edgeFlagをtrue
						}
						moveTimes = 0;                       // 移動変数(moveTimes)を0に初期化
						trainDirectionFlag = upArrow;              // 移動方向を下にする
						m_pGMain->m_pPcProc->trainStep++;    // 移動距離をたす
					}
				}
			}
			else if (frontFlag == false) {  //プレイヤーが正面以外の場合
				// 配列の現在地の列-1に直線線路または駅が配置されているかどうか
				if (m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] == lineNum
					|| m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] == stationNum) {
					DoneMove = true;           // 移動したフラグをtrue
					// 一つの線路の移動が終わっていなければ
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);   // 移動させる
						moveTimes += loopPlusMoveTimes;      // 移動変数(moveTimes)を+1   
					}
					// 一つの線路の移動が終わっていれば
					else {
						// 配置されているオブジェクトが線路ならば
						if (m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] == lineNum) {
							// 配列にafterLineNumを入れる
							m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] = afterLineNum;
						}
						// 配置されているオブジェクトが駅ならば
						else if (m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] == stationNum) {
							// 配列にafterStationNumを入れる
							m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] = afterStationNum;
						}
						oldHP -= moveValue;                        // 現在地の更新
						if (oldHP == lowerLimitV) {        // 移動後が端の位置ならば
							edgeFlag = true;               // edgeFlagをtrue
						}
						moveTimes = 0;                     // 移動変数(moveTimes)を0に初期化
						trainDirectionFlag = upArrow;            // 移動方向を下にする
						m_pGMain->m_pPcProc->trainStep++;  // 移動距離をたす
					}
				}
			}
		}
	}
}
// M.S
// キャラの上から右移動の変数のセット
// 引  数：なし
// 戻り値：なし   
void	CPcObj::SetUpRightChangeLineValue() {
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	lowerLimitH = 0;
	upperLimitV = 10;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	chPlacementNearH = oldHP - 1;
	chPlacementH = oldHP - 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP + 1;
	edgePos = 9;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;                      // 方向切り替え線路のプレイキャラの回転変数
	moveValueH = 2;      	                   // 次の線路までの移動する距離(行)
	moveValueV = 1;      	                   // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                     // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                         // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                    // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
}
// M.S
// キャラの上から左移動の変数のセット
// 引  数：なし
// 戻り値：なし  
void	CPcObj::SetUpLeftChangeLineValue() {
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	lowerLimitH = 0;
	lowerLimitV = 0;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	chPlacementNearH = oldHP - 1;
	chPlacementH = oldHP - 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP - 1;
	edgePos = 0;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;                      // 方向切り替え線路のプレイキャラの回転変数
	moveValueH = 2;      	                   // 次の線路までの移動する距離(行)
	moveValueV = 1;      	                   // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                     // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                         // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                    // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
}
// M.S
// キャラの下から右移動の変数のセット
// 引  数：なし
// 戻り値：なし  
void	CPcObj::SetDownRightChangeLineValue() {
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	upperLimitH = 10;
	upperLimitV = 10;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	chPlacementNearH = oldHP + 1;
	chPlacementH = oldHP + 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP + 1;
	edgePos = 9;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;                      // 方向切り替え線路のプレイキャラの回転変数                
	moveValueH = 2;      	                   // 次の線路までの移動する距離(行)
	moveValueV = 1;      	                   // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                     // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                         // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                    // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
}
// M.S
// キャラの下から左移動の変数のセット
// 引  数：なし
// 戻り値：なし  
void	CPcObj::SetDownLeftChangeLineValue() {
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	upperLimitH = 10;
	lowerLimitV = 0;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	chPlacementNearH = oldHP + 1;
	chPlacementH = oldHP + 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP - 1;
	edgePos = 0;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;                      // 方向切り替え線路のプレイキャラの回転変数
	moveValueH = 2;      	                   // 次の線路までの移動する距離(行)
	moveValueV = 1;      	                   // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                     // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                         // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                    // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
}
// M.S
// キャラの右から上移動の変数のセット
// 引  数：なし
// 戻り値：なし  
void	CPcObj::SetRightUpChangeLineValue() {
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	upperLimitH = 10;
	lowerLimitV = 0;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	chPlacementNearH = oldHP;
	chPlacementH = oldHP - 1;
	chPlacementNearV = oldVP + 1;
	chPlacementV = oldVP + 2;
	edgePos = 0;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;                      // 方向切り替え線路のプレイキャラの回転変数
	moveValueH = 1;      	                   // 次の線路までの移動する距離(行)
	moveValueV = 2;      	                   // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                     // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                         // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                    // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
}
// M.S
// キャラの右から下移動の変数のセット
// 引  数：なし
// 戻り値：なし  
void	CPcObj::SetRightDownChangeLineValue() {
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	upperLimitH = 10;
	upperLimitV = 10;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	chPlacementNearH = oldHP;
	chPlacementH = oldHP + 1;
	chPlacementNearV = oldVP + 1;
	chPlacementV = oldVP + 2;
	edgePos = 9;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;                      // 方向切り替え線路のプレイキャラの回転変数
	moveValueH = 1;      	                   // 次の線路までの移動する距離(行)
	moveValueV = 2;      	                   // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                     // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                         // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                    // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
}
// M.S
// キャラの左から上移動の変数のセット
// 引  数：なし
// 戻り値：なし  
void	CPcObj::SetLeftUpChangeLineValue() {
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	lowerLimitH = 0;
	lowerLimitV = 0;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	chPlacementNearH = oldHP;
	chPlacementH = oldHP - 1;
	chPlacementNearV = oldVP - 1;
	chPlacementV = oldVP - 2;
	edgePos = 0;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;                      // 方向切り替え線路のプレイキャラの回転変数
	moveValueH = 1;      	                   // 次の線路までの移動する距離(行)
	moveValueV = 2;      	                   // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                     // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                         // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                    // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
}
// M.S
// キャラの左から下移動の変数のセット
// 引  数：なし
// 戻り値：なし  
void	CPcObj::SetLeftDownChangeLineValue() {
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	upperLimitH = 10;
	lowerLimitV = 0;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	chPlacementNearH = oldHP;
	chPlacementH = oldHP + 1;
	chPlacementNearV = oldVP - 1;
	chPlacementV = oldVP - 2;
	edgePos = 9;                             // プレイキャラが端にいるときの配列の値
	rotateChar = 90.0f;
	moveValueH = 1;      	                   // 次の線路までの移動する距離(行)
	moveValueV = 2;      	                   // 次の線路までの移動する距離(列)
	loopPlusMoveTimes = 1;                     // ループして進んでいく度にmoveTimesに足す変数
	changeLineNum = 2;                         // 方向切り替え線路の配列にいれた数字
	afterChangeLineNum = 6;                    // 方向切り替え線路の通過後に配列にいれる数字
	chLineMoveTimesMax = moveTimesMax * 2;   // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
}
// M.S
// キャラの方向切り替え線路移動処理(上から右移動)
// 引  数：なし
// 戻り値：なし   
void	CPcObj::MoveUpRight() {
	SetUpRightChangeLineValue();     // 変数の値をセット
	// プレイキャラの位置が配置可能範囲かどうか
	if (chPlacementH >= lowerLimitH && chPlacementV < upperLimitV) {
		if (trainDirectionFlag == upArrow) {       // プレイヤーが上方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;            // 移動したフラグをtrue
					// changeStepNumでフェーズごとに移動をさせる
					switch (changeStepNum) {
						// フェーズ0：2マス分の直線移動
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                        // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);        // 前に移動
							moveTimes += loopPlusMoveTimes;                          // 回数を足す
						}
						else {
							moveTimes = 0;                                           // 現在地の更新
							changeStepNum++;                                         // 次の移動を行う
						}
						break;
						// フェーズ1：プレイキャラの回転
					case 1:  //回転
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                             //次の移動を行う
						break;
					case 2:
						// フェーズ2：回転後の1マス分の直線移動
						if (moveTimes < moveTimesMax) {                              // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);        // 前に移動
							moveTimes += loopPlusMoveTimes;                          // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = rightArrow;  // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                        // 現在地の更新
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;  // 移動距離を足す
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                          // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // 正面以外
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                        // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);        // 前に移動
							moveTimes += loopPlusMoveTimes;                          // 回数を足す
						}
						else {
							moveTimes = 0;
							//oldHP -= 2;                                            // 現在地の更新
							changeStepNum++;                                         // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                             //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                              // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);        // 前に移動
							moveTimes += loopPlusMoveTimes;                          // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = rightArrow;   // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                        // 現在地の更新
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;  // 移動距離を足す
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                 // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// キャラの方向切り替え線路移動処理(上から左移動)
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveUpLeft() {
	SetUpLeftChangeLineValue();     // 変数の値をセット
	if (chPlacementH >= lowerLimitH && chPlacementV >= lowerLimitV) {
		if (trainDirectionFlag == upArrow) {       // プレイヤーが上方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = leftArrow;  // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							oldHP -= moveValueH;                                         // 現在地の更新
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // 移動距離を足す
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                 // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // 正面以外
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][oldVP] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][oldVP] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < moveTimesMax * 2) {                         // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = leftArrow;  // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][oldVP] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][oldVP] = afterChangeLineNum;
							oldHP -= moveValueH;                                         // 現在地の更新
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // 移動距離を足す
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                  // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// キャラの方向切り替え線路移動処理(下から右移動)
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveDownRight() {
	SetDownRightChangeLineValue();     // 変数の値をセット
	if (chPlacementH < upperLimitH && chPlacementV < upperLimitV) {
		if (trainDirectionFlag == downArrow) {       // プレイヤーが下方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = rightArrow;  // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                       // 現在地の更新
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV; // 移動距離を足す
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                   // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // 正面以外
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = rightArrow;   // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                         // 現在地の更新
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // 移動距離を足す
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// キャラの方向切り替え線路移動処理(下から左移動)
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveDownLeft() {
	SetDownLeftChangeLineValue();     // 変数の値をセット
	if (chPlacementH < upperLimitH && chPlacementV >= lowerLimitV) {
		if (trainDirectionFlag == downArrow) {       // プレイヤーが下方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = leftArrow;    // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							oldHP += moveValueH;                                         // 現在地の更新
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // 移動距離を足す
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                  // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // 正面以外
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = leftArrow;    // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;       // 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							oldHP += moveValueH;                                          // 現在地の更新
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // 移動距離を足す
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;              // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// キャラの方向切り替え線路移動処理(右から上移動)
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveRightUp() {
	SetRightUpChangeLineValue();     // 変数の値をセット
	if (chPlacementH >= lowerLimitV && chPlacementV < upperLimitH) {
		if (trainDirectionFlag == rightArrow) {       // プレイヤーが右方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = upArrow;   // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                          // 現在地の更新
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // 移動距離を足す
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                      // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // 正面以外
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum) {
					DoneMove = true;

					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = upArrow;   // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;       // 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                          // 現在地の更新
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // 移動距離を足す
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                 // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
		}
	}

}
// M.S
// キャラの方向切り替え線路移動処理(右から下移動)
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveRightDown() {
	SetRightDownChangeLineValue();     // 変数の値をセット
	if (chPlacementH < upperLimitH && chPlacementV < upperLimitV) {
		if (trainDirectionFlag == rightArrow) {       // プレイヤーが右方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = downArrow;    // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                                // 現在地の更新
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;          // 移動距離を足す
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                        // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // 正面以外
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = downArrow;     // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                          // 現在地の更新
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // 移動距離を足す
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                        // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
		}
	}

}
// M.S
// キャラの方向切り替え線路移動処理(左から上移動)
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveLeftUp() {
	SetLeftUpChangeLineValue();     // 変数の値をセット
	if (chPlacementH >= lowerLimitH && chPlacementV >= lowerLimitV) {
		if (trainDirectionFlag == leftArrow) {       // プレイヤーが左方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = upArrow;      // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                         // 現在地の更新
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // 移動距離を足す
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                  // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // 正面以外
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = upArrow;        // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;        // 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                                  // 現在地の更新
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;            // 移動距離を足す
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                    // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
		}
	}

}
// M.S
// キャラの方向切り替え線路移動処理(左から下移動)
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveLeftDown() {
	SetLeftDownChangeLineValue();     // 変数の値をセット
	if (chPlacementH < upperLimitH && chPlacementV >= lowerLimitV) {
		if (trainDirectionFlag == leftArrow) {       // プレイヤーが左方向に進んでいるかどうか
			if (frontFlag == true) {   //プレイヤーが正面の場合
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動する
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = downArrow;        // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                            // 現在地の更新
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;      // 移動距離を足す
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                      // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // 正面以外
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // 移動
						if (moveTimes < chLineMoveTimesMax) {                       // ２マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // 次の移動を行う
						}
						break;
					case 1:  //回転
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //次の移動を行う
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1マス移動
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // 前に移動
							moveTimes += loopPlusMoveTimes;                         // 回数を足す
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = downArrow;        // 電車の進んでいる方向のセット
							// 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;     // 移動したため配列の数値変更(方向変換スイッチは6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;    				                      // 現在地の更新       
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // 移動距離を足す
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                     // 次の移動のためにchangeStepNumを0に戻す
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// マップ面の端から次の面への
// プレイキャラの回転角度、位置を求める関数
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveEdgePos1(){
	// マップ面配列の端にいて、向かう方向が次のマップ面かどうかみて処理をする
	// nowNorth 1:マップが無回転 2:マップが+90度回転 3:マップが+180度回転 4:マップが+180度回転
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // 上方向へ向かう
		newPcPos = XMMatrixTranslation(nowPcPos.x, 5.5f, 6.0f);     // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f)); // 回転角度
		needRotateFlag = 1;     // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // 右方向へ向かう
		newPcPos = XMMatrixTranslation(6.0f, 5.5f, nowPcPos.z);      // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // 回転角度
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // 回転角度
		needRotateFlag = 2;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // 下方向へ向かう
		newPcPos = XMMatrixTranslation(nowPcPos.x, 5.5f, -6.0f);     // 位置  
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // 回転角度
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(180.0f)); // 回転角度
		needRotateFlag = 2;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) { // 左方向へ向かう
		newPcPos = XMMatrixTranslation(-6.0f, 5.5f, nowPcPos.z);     // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // 回転角度
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // 回転角度
		needRotateFlag = 2;   // かける回転の数
	}
}
// M.S
// マップ面の端から次の面への
// プレイキャラの回転角度、位置を求める関数
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveEdgePos2() {
	// nowPcPosNum:絶対座標からの位置 0:上 1:手前 2:下 3:手前裏 4:右 5:左
	//nowNorth 1:マップが無回転 2:マップが+90度回転 3:マップが+180度回転 4:マップが+180度回転
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // 上方向へ向かう
		newPcPos = XMMatrixTranslation(nowPcPos.x, 6.0f, -5.5f);     // 位置
		needRotateFlag = 0;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // 右方向へ向かう
		newPcPos = XMMatrixTranslation(6.0f, nowPcPos.y, -5.5f);     // 位置
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(270.0f)); // 回転角度
		needRotateFlag = 1;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // 下方向へ向かう
		newPcPos = XMMatrixTranslation(nowPcPos.x, -6.0f, -5.5f);    // 位置
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(180.0f)); // 回転角度
		needRotateFlag = 1;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(-6.0f, nowPcPos.y, -5.5f);   // 位置
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(90.0f)); // 回転角度
		needRotateFlag = 1;   // かける回転の数
	}
}
// M.S
// マップ面の端から次の面への
// プレイキャラの回転角度、位置を求める関数
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveEdgePos3() {
	// nowPcPosNum:絶対座標からの位置 0:上 1:手前 2:下 3:手前裏 4:右 5:左
	//nowNorth 1:マップが無回転 2:マップが+90度回転 3:マップが+180度回転 4:マップが+180度回転
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // 上方向へ向かう
		newPcPos = XMMatrixTranslation(nowPcPos.x, -5.5f, -6.0f);    // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(270.0f)); // 回転角度
		needRotateFlag = 1;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // 右方向へ向かう
		newPcPos = XMMatrixTranslation(6.0f, -5.5f, nowPcPos.z);     // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(270.0f)); // 回転角度
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // 回転角度
		needRotateFlag = 2;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // 下方向へ向かう
		newPcPos = XMMatrixTranslation(nowPcPos.x, -5.5f, 6.0);      // 位置
		edgeRotate2 = XMMatrixRotationZ(XMConvertToRadians(180.0f)); // 回転角度
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // 回転角度
		needRotateFlag = 2;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(-6.0f, -5.5f, nowPcPos.z);    // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(270.0f)); // 回転角度
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // 回転角度
		needRotateFlag = 2;   // かける回転の数
	}
}
// M.S
// マップ面の端から次の面への
// プレイキャラの回転角度、位置を求める関数
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveEdgePos4() {
	// nowPcPosNum:絶対座標からの位置 0:上 1:手前 2:下 3:手前裏 4:右 5:左
	//nowNorth 1:マップが無回転 2:マップが+90度回転 3:マップが+180度回転 4:マップが+180度回転
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // 上方向へ向かう
		newPcPos = XMMatrixTranslation(nowPcPos.x, -6.0f, 5.5f);     // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(180.0f)); // 回転角度
		needRotateFlag = 1;    // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // 右方向へ向かう
		newPcPos = XMMatrixTranslation(6.0f, nowPcPos.y, 5.5f);      // 位置
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(90.0f));  // 回転角度
 		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(180.0f)); // 回転角度
		needRotateFlag = 2;    // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // 下方向へ向かう
		newPcPos = XMMatrixTranslation(nowPcPos.x, 6.0f, 5.5f);       // 位置
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(180.0f));  // 回転角度
		needRotateFlag = 1;   // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(-6.0f, nowPcPos.y, 5.5);      // 位置
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(180.0f)); // 回転角度
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(270.0f)); // 回転角度
		needRotateFlag = 2;   // かける回転の数
	}
}
// M.S
// マップ面の端から次の面への
// プレイキャラの回転角度、位置を求める関数
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveEdgePos5() {
	// nowPcPosNum:絶対座標からの位置 0:上 1:手前 2:下 3:手前裏 4:右 5:左
	//nowNorth 1:マップが無回転 2:マップが+90度回転 3:マップが+180度回転 4:マップが+180度回転
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // 上方向へ向かう
		newPcPos = XMMatrixTranslation(5.5f, nowPcPos.y, 6.0f);      // 位置
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // 回転角度
		edgeRotate2 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // 回転角度
		needRotateFlag = 2;  // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // 右方向へ向かう
		newPcPos = XMMatrixTranslation(5.5f, -6.0f, nowPcPos.z);     // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(180.0f)); // 回転角度
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // 回転角度
		needRotateFlag = 2;  // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // 下方向へ向かう
		newPcPos = XMMatrixTranslation(5.5f, nowPcPos.y, -6.0f);     // 位置
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(90.0f));  // 回転角度
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // 回転角度
		needRotateFlag = 2;  // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(5.5f, 6.0f, nowPcPos.z);      // 位置
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // 回転角度
		needRotateFlag = 1;  // かける回転の数
	}
}
// M.S
// マップ面の端から次の面への
// プレイキャラの回転角度、位置を求める関数
// 引  数：なし
// 戻り値：なし 
void	CPcObj::MoveEdgePos6() {
	// nowPcPosNum:絶対座標からの位置 0:上 1:手前 2:下 3:手前裏 4:右 5:左
    // nowNorth 1:マップが無回転 2:マップが+90度回転 3:マップが+180度回転 4:マップが+180度回転
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // 上方向へ向かう
		newPcPos = XMMatrixTranslation(-5.5f, nowPcPos.y, 6.0f);     // 位置
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // 回転角度
		edgeRotate2 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // 回転角度
		needRotateFlag = 2;  // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // 右方向へ向かう
		newPcPos = XMMatrixTranslation(-5.5f, 6.0f, nowPcPos.z);     // 位置
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // 回転角度
		needRotateFlag = 1;  // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // 下方向へ向かう
		newPcPos = XMMatrixTranslation(-5.5f, nowPcPos.y, -6.0f);     // 位置
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(270.0f));  // 回転角度
		edgeRotate2 = XMMatrixRotationZ(XMConvertToRadians(270.0f));  // 回転角度
		needRotateFlag = 2;  // かける回転の数
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(-5.5f, -6.0f, nowPcPos.z);     // 位置
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(270.0f));  // 回転角度
		edgeRotate2 = XMMatrixRotationZ(XMConvertToRadians(180.0f));  // 回転角度
		needRotateFlag = 2;  // かける回転の数
	}
}
// M.S
// キャラの位置からMoveEdgePosを呼んで
// 端から移動した時の位置と回転を求める
// 引  数：なし
// 戻り値：なし 
void	CPcObj::SetEdgePos() {
	switch (nowPcPosNum) {   // M.S 今のpcの位置
	case 0:
		MoveEdgePos1();      // M.S プレイキャラの位置と回転角度を求める
		break;
	case 1:
		MoveEdgePos2();      // M.S プレイキャラの位置と回転角度を求める
		break;
	case 2:
		MoveEdgePos3();      // M.S プレイキャラの位置と回転角度を求める
		break;
	case 3:
		MoveEdgePos4();      // M.S プレイキャラの位置と回転角度を求める
		break;
	case 4:
		MoveEdgePos5();      // M.S プレイキャラの位置と回転角度を求める
		break;
	case 5:
		MoveEdgePos6();      // M.S プレイキャラの位置と回転角度を求める
		break;
	}
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの移動処理
//
//　ＰＣを動かす
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalMove()
{
	mPos = XMMatrixTranslation(0.0f, 0.0f, 0.0f); // ＰＣの移動マトリックスの初期化
	m_fLocalRotY = 0;		
   if (frontFlag == true) {     // M.S 正面(操作可能面)にいるフラグをfalse
	 frontFlag = false;
   }
     VECTOR3 nowPosition = GetPositionVector(m_mWorld); // M.S プレイキャラの位置
	 JudgeNowPcMap(nowPosition, false);                 // M.S キャラがいる面を調べる
     m_pGMain->m_pPcProc->lineMapNew(surfaceNum);       // M.S マップ配列を持ってくる
	mPos = XMMatrixTranslation(0.0f, 0.0f, 0.0f);    	// 自然落下の初期値
	DoneMove = false;   	   // M.S 1ループ中に移動をしたかどうかを入れる変数
		// M.S 全ての移動処理を見て、配列に合わせた処理をさせる
	MoveRight();   // M.S キャラの右移動処理   直線線路または駅の移動
	MoveLeft();    // M.S キャラの左移動処理
	MoveDown();    // M.S キャラの下移動処理
	MoveUp();      // M.S キャラの上移動処理	
	MoveUpRight();      // M.S 上から右移動 方向変換スイッチの移動   
	MoveUpLeft();       // M.S 上から左移動
	MoveDownRight();    // M.S 下から右移動
	MoveDownLeft();     // M.S 下から左移動
	MoveRightUp();      // M.S 右から上移動
	MoveRightDown();    // M.S 右から下移動
	MoveLeftUp();       // M.S 左から上移動
	MoveLeftDown();     // M.S 左から下移動
	if (DoneMove == false 
		&& m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess == false
		&& m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess == false
		&& m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess == false
		&& edgeFlag == false) {
		UpdateDead();  // M.S 1ループ中に移動していなく乗車処理中でなければゲームオーバー
	}
	if (frontFlag == false) {
		m_pGMain->m_pPcProc->lineMapSet(surfaceNum);  // M.S 正面(操作面)にいなければ、いた面を更新
	}
	if (m_fLocalRotY >= 360.0f) {  // 回転の角度が360度を超えないようにする
		for (int i = 0; m_fLocalRotY >= 360.0f; i++) {
			m_fLocalRotY = m_fLocalRotY - 360.0f;
		}
	}
	MATRIX4X4 rotate = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY)); // キャラの回転の計算
	m_mWorld = mPos * rotate * m_mWorld;     // キャラを移動させる
	// M.S マップの面から面へ移動する時(端にいて向かっている方向が次の面)
	if (oldHP == 0 && trainDirectionFlag == 1 || oldHP == 9 && trainDirectionFlag == 3 
		|| oldVP == 9 && trainDirectionFlag == 2 || oldVP == 0 && trainDirectionFlag == 4) {
		// M.S 周りに人キャラがいなければ端から移動の処理を行う
		if (frontFlag == false && m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP] == 8 &&
			(m_pGMain->m_pPcProc->lineMapSub[oldHP + 1][oldVP] == 10 ||
				m_pGMain->m_pPcProc->lineMapSub[oldHP - 1][oldVP] == 10 ||
				m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + 1] == 10 ||
				m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - 1] == 10 )||
			frontFlag == true && m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP] == 8 &&
			(m_pGMain->m_pMapProc->lineMap1[oldHP + 1][oldVP] == 10 ||
				m_pGMain->m_pMapProc->lineMap1[oldHP - 1][oldVP] == 10 ||
				m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + 1] == 10 ||
				m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - 1] == 10)){
		}
		else {
			if (edgeFlag == true) {    // M.S 端から次の面への移動フラグがtrueかどうか
				 nowPcPos = GetPositionVector(m_mWorld);  // M.S キャラの位置の取得
				 // M.S プレイキャラのいる面の数字を調べる
				 nowPcPosMap = JudgeNowPcMap(nowPcPos, false); 
				 // M.S マップ面の回転を調べる
				 nowNorth = m_pGMain->m_pPcProc->judgeDirection(nowPcPosMap, nowPcPos, 0);
				 SetEdgePos();    // M.S nowPcPosMapから移動後の位置と回転を求める
				// M.S 現在地の更新
				updateEdgeOldHV(trainDirectionFlag, oldHP, oldVP, nowPcPosMap);
				edgeFlag = false;  // M.S 端から次の面への移動フラグをfalse
				m_mWorld = newPcPos;   // M.S プレイキャラの位置のセット
				// M.S プレイキャラの回転のセット
				if (needRotateFlag == 1) {  
					m_mWorld = edgeRotate1 * m_mWorld; 
				}
				else if (needRotateFlag == 2) {
					m_mWorld = edgeRotate1 * edgeRotate2 * m_mWorld; 
				}
				// M.S 移動後のプレイキャラの位置取得
				VECTOR3 nowPcPos2 = GetPositionVector(m_mWorld); 
				// M.S 移動後のプレイキャラのいる面の数字を調べる
				m_pGMain->m_pPcProc->NewSurfaceNum = JudgeNowPcMap(nowPcPos2, false);
			}
		}
	}
	        // M.S 移動処理が終わったので回転可能フラグをtrue
			m_pGMain->m_pPcProc->rotateOkFlag = true;  
}
//-----------------------------------------------------------------------------   // -- 2021.1.10
// ＰＣオブジェクトの移動処理　キー操作毎の各種移動処理
//
//   引数　DWORD Key キー種別　DirectInputのキーコード
//
//   戻り値  移動マトリックス
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalMoveKeystate(DWORD DIKey)
{
	MATRIX4X4 mPos;
	
	if (m_AnimStatus.animNum == 0) m_AnimStatus.SetNum(1);
	if (m_AnimStatus.isEnd(1))     m_AnimStatus.SetNum(2);

	if (m_bSide && DIKey != DIK_W)   // サイドモードで前進以外のとき
	{
		switch (DIKey)
		{
		case DIK_S:    // 後退
			// 方向を変えずに後退
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, -m_fSpeed);
			break;
		case DIK_D:    // 右
			// 方向を変えずに右移動
			mPos = XMMatrixTranslation(m_fSpeed, m_fJumpY, 0.0f);
			break;
		case DIK_A:    // 左
			// 方向を変えずに左移動
			mPos = XMMatrixTranslation(-m_fSpeed, m_fJumpY, 0.0f);
			break;
		}
	}
	else {
		// 進行方向に回転してから前進

		// ルートボーンアニメーションを行うかどうかルートアニメーションタイプを確認する
		if (m_pMesh->GetRootAnimType(m_AnimStatus.animNum) == eRootAnimNone)
		{
			// ルートボーンアニメーションを行わず固定の前進移動値
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, m_fSpeed);
		}
		else {
			// ルートボーンアニメーションでの前進移動値
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f) * m_pMesh->GetRootAnimUpMatrices(m_AnimStatus);
		}

		// 進行方向に回転する処理
		// ・回転角度はm_vRotUp.yにある。-180～180度
		// ・１回の回転速度はm_fRotSpeed
		if (m_vRotUp.y > 180.0f)  m_vRotUp.y -= 360.0f;
		if (m_vRotUp.y < -180.0f) m_vRotUp.y += 360.0f;

		float fAngle;  // 目標回転角度
		switch (DIKey)
		{
		case DIK_W:    // 前進
			fAngle = 0.0f;
			break;
		case DIK_S:    // 後退
			if (m_vRotUp.y >= 0)  // 最小回転になるように方向を合わせる
			{
				fAngle = 180.0f;
			}
			else {
				fAngle = -180.0f;
			}
			break;
		case DIK_D:    // 右
			fAngle = 90.0f;
			if (m_vRotUp.y == -180.0f) m_vRotUp.y = 180.0f;  // 最小回転になるように方向を合わせる
			break;
		case DIK_A:    // 左
			fAngle = -90.0f;
			if (m_vRotUp.y == 180.0f) m_vRotUp.y = -180.0f;  // 最小回転になるように方向を合わせる
			break;
		}
	}
	return mPos;
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの攻撃処理
//
//　キーボード／マウスでＰＣの攻撃処理を行う
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalAttack()
{
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの更新 ダメージ状態（DAMAGE）
//
//　ダメージを受けたときの処理
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDamage()
{
	MATRIX4X4 mTemp;
	const int nDeadTime = 200;    // 死亡時間
	const int nFlashTime = 5;      // 無敵状態の時間

	m_pGMain->m_pBackForeProc->GetSprite()->DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(255, 255, 255), 1.0f); // 画面を一瞬白くフラッシュ

	mTemp = XMMatrixTranslation(0, 0, -0.25f);	// バックする
	m_mWorld = mTemp * m_mWorld;

	m_nHp -= m_pHitObj->GetAtc();	// 攻撃を受けたダメージ
	if (m_nHp <= 0)		// HPが０なので死亡へ
	{
		m_nHp = 0;
		m_dwStatus = DEAD;		// HPが０なので死亡へ
		m_AnimStatus.SetNum(4);	// 死亡モーションにする
		m_nCnt1 = nDeadTime;			// 死亡時間の設定
	}
	else {
		m_nCnt1 = nFlashTime;   // 無敵状態の時間
		m_dwStatus = FLASH;     // ダメージからの復帰処理を行う
	}
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの更新 死亡状態（DEAD）
//
//　死亡状態のときの処理
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDead()
{
	// M.S ゲームの処理をストップさせるstopOperationをtrue
	m_pGMain->stopOperation = true;
	if (gameOverAnim == 0) {	// M.S ゲームオーバーのアニメフェーズが0ならば
		gameOverAnim = 1;       // M.S ゲームオーバーのアニメフェーズを1する
		m_AnimStatus.SetNum(3); // M.S ゲームオーバーの回転アニメーションを発生		
	}
	else if(gameOverAnim == 1){  // M.S ゲームオーバーのアニメフェーズが1ならば
		animCount--;             // M.S アニメーションカウントを引く
		// M.S animCountが0以下ならば(ゲームオーバーの回転アニメーションが終了したら)
		if (animCount <= 0) { 
			gameOverAnim = 2; // M.S ゲームオーバーアニメフェーズを2にする  
			m_AnimStatus.SetNum(4);  // M.S ゲームオーバーの転覆アニメーションを発生
		}
	}
	// M.S ゲームオーバーの転覆アニメーションが終わり、
	// M.S ゲームオーバーアニメフェーズが2ならば
	if (m_AnimStatus.isEnd(4) && gameOverAnim == 2)  
	{
		m_AnimStatus.playAnim = false;	// アニメーションを止める
		m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // フレームエンドの一つ手前にする
		gameOverAnim = 3;	// M.S ゲームオーバーアニメフェーズが3にする
	}
	if (gameOverAnim == 3) // M.S ゲームオーバーアニメフェーズが3ならば
	{
		--gameOverTime;    // M.S gameOverTimeを引く
		if (gameOverTime <= 0) {   // M.S gameOverTimeが0以下ならば
			m_pGMain->m_pPcProc->oneScreenFlag = true;  // M.S 1面のみ描画フラグをtrue
			m_pGMain->m_dwGameStatus = GAMEOVER;	// ゲームオーバーへ
			gameOverAnim = 0;                       // M.S ゲームオーバーアニメフェーズを0に戻す          
		}
	}
}

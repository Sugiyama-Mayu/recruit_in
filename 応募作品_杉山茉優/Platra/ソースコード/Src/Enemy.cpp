//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//
//		敵キャラクターの処理
//																Enemy.cpp
//=============================================================================
#include  "Enemy.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "BackFore.h"

#include "stdlib.h"
#include "time.h"

//============================================================================
//
// 敵メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pGMain = pGMain;

	m_pEnmGolemProc = new CEnmGolemProc(m_pGMain);     // HighMan(赤)プロシージャの生成
	m_pProcArray.push_back(m_pEnmGolemProc);           // プロシージャをプロシージャ配列に登録する

	m_pEnmRSProc = new CEnmRSProc(m_pGMain);           // MiddleMan(黄)プロシージャの生成
	m_pProcArray.push_back(m_pEnmRSProc);              // プロシージャをプロシージャ配列に登録する

	m_pEnmBdProc = new CEnmBdProc(m_pGMain);           // LowMan(青)プロシージャの生成
	m_pProcArray.push_back(m_pEnmBdProc);              // プロシージャをプロシージャ配列に登録する

	// M.S 回転に合わせてセットする角度の変数
	rotate90angle = 270.0f;
	rotate180angle = 180.0f;
	rotate270angle = 90.0f;
	// M.S 乗車合計人数
	getLowMan = 0;     // M.S 青
	getMiddleMan = 0;  // M.S 黄
	getHighMan = 0;    // M.S 赤
	// M.S 一つの星での乗車人数
	getLowStageMan = 0;     // M.S 青 
	getMiddleStageMan = 0;  // M.S 黄
	getHighStageMan = 0;    // M.S 赤
	rotateOkFlagMan = true;  // M.S マップの回転を止めるフラグ
}
//============================================================================
// 敵プロシージャの更新
//
//　敵の数を数え、０になったらゲームクリヤーにする
//
//   引数　　　なし
//============================================================================
void	CEnmProc::Update()
{
}
//============================================================================
//
// 全ての敵プロシージャの発生数を初期値にリセットする
// （最大発生数(m_nMaxNum)を発生数m_nNumに設定する
//
// 引数    CBaseProc* pProc  対象とするプロシージャ。省略値はNULL
//                           NULLの時は自プロシージャ
// 戻り値  なし
// ---------------------------------------------------------------------------
void CEnmProc::ResetEnmNum(CBaseProc* pProc)
{
	if (pProc)   // 対象とするプロシージャ
	{
		pProc->SetMaxNum();  // 最大発生数(m_nMaxNum)を発生数m_nNumに設定する

		// 下位のプロシージャを探索していく
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			ResetEnmNum(pProc->GetProcArrayPtr()[i]);  // 再帰呼び出し
		}
	}
	else {   // 自プロシージャ
		SetMaxNum();  // 最大発生数(m_nMaxNum)を発生数m_nNumに設定する

		// 下位のプロシージャを探索していく
		for (DWORD i = 0; i < m_pProcArray.size(); i++)
		{
			ResetEnmNum(m_pProcArray[i]);  // 再帰呼び出し
		}
	}
}
//============================================================================
//
// 全ての敵オブジェクトの残っている敵の数を数える処理
// （残っている敵の数とは、まだ発生していない数(m_nNumの値)＋現在生きている数のことである）
//
// 引数    CBaseProc* pProc  対象とするプロシージャ。NULLの時は自プロシージャ。省略値はNULL
//         int        nNum   上位のプロシージャから与えられた敵の数。省略値は0
//
// 戻り値  int 残っている敵の数
// ---------------------------------------------------------------------------
int CEnmProc::CountActiveEnm(CBaseProc* pProc, int nNum)
{

	if (pProc)   // 対象とするプロシージャ
	{
		nNum += pProc->GetNum();									// プロシージャ中に残っている敵の数（まだ発生していない数）
		for (DWORD j = 0; j < pProc->GetObjArrayPtr().size(); j++)
		{
			if (pProc->GetObjArrayPtr()[j]->GetActive()) nNum++;	// オブジェクト中にすでに発生している敵の数（現在生きている数）
		}

		// 下位のプロシージャを探索していく
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			nNum = CountActiveEnm(pProc->GetProcArrayPtr()[i], nNum);  // 再帰呼び出し
		}
	}
	else {   // 自プロシージャ
		nNum += GetNum();											// プロシージャ中に残っている敵の数（まだ発生していない数）
		for (DWORD j = 0; j < m_pObjArray.size(); j++)
		{
			if (m_pObjArray[j]->GetActive()) nNum++;				// オブジェクト中にすでに発生している敵の数（現在生きている数）
		}

		// 下位のプロシージャを探索していく
		for (DWORD i = 0; i < m_pProcArray.size(); i++)
		{
			nNum = CountActiveEnm(m_pProcArray[i], nNum);  // 再帰呼び出し
		}
	}
	return nNum;
}
//M.S ゲームの初期化をする関数
//引  数：なし
//戻り値：なし
void CEnmProc::ResetNewGameMan() {
	// 人キャラ自体のリセット
	for (int i = 0; i < 6; i++) {
		// HighManのリセット
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->doneProcess = false; 
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->alive = true;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->manSurfaceNum = -1;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->thisManArrayNumber = 0;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->initialProcess = true;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->initialRotate = 0.0f;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->initialDeadAnim = 0;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->animCount = 173;

		// MiddleManのリセット
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->doneProcess = false;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->alive = true;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->manSurfaceNum = -1;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->thisManArrayNumber = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->initialProcess = true;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->initialRotate = 0.0f;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->initialDeadAnim = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->animCount = 80;

		// LowManのリセット
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->doneProcess = false;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->alive = true;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->manSurfaceNum = -1;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->thisManArrayNumber = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->initialProcess = true;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->initialRotate = 0.0f;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->initialDeadAnim = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->animCount = 60;
	}

	for (int i = 0; i < 6; i++) {
		// 配置位置格納配列の初期化
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->numH[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->numV[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->numH[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->numV[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->numH[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->numV[i] = 0;
		// 配置済みか確認配列の初期化
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->PlacementManMap[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->PlacementManMap[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->PlacementManMap[i] = 0;
	}
	// HighManプロシージャのリセット
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->manNum = 0;
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->exclusiveMan = false;
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget = 0;
	m_pGMain->m_pEnmProc->getHighStageMan = 0;
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = false;
	// MiddleManプロシージャのリセット
	m_pGMain->m_pEnmProc->m_pEnmRSProc->manNum = 0;
	m_pGMain->m_pEnmProc->m_pEnmRSProc->exclusiveMan = false;
	m_pGMain->m_pEnmProc->m_pEnmRSProc->surfaceNumTarget = 0;
	m_pGMain->m_pEnmProc->getMiddleStageMan = 0;
	m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = false;
	// LowManプロシージャのリセット
	m_pGMain->m_pEnmProc->m_pEnmBdProc->manNum = 0;
	m_pGMain->m_pEnmProc->m_pEnmBdProc->exclusiveMan = false;
	m_pGMain->m_pEnmProc->m_pEnmBdProc->surfaceNumTarget = 0;
	m_pGMain->m_pEnmProc->getLowStageMan = 0;
	m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = false;
}
// =====================================================================================================
// 
// 各敵プロシージャ毎の処理
// 
// =====================================================================================================

//============================================================================
//
// 敵ゴーレムプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmGolemProc::CEnmGolemProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	const int nWait    = 400;                   // 敵が発生するまでの待ち時間
	m_dwProcID         = ENM_GOLEM_ID;          // 敵ゴーレムのID
	m_nNum = m_nMaxNum = ENM_GOLEM_ALLMAX;      // 敵ゴーレムの最大出現数
	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh( m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/Man/highMan_Breath.mesh"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/highMan_Breath.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/highMan_Happy.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/man_JumpingMotion.anmx"));
	m_pMesh->m_fHeightMax = 0.05f;     // ディスプレースメントマッピングの高さ  // -- 2020.1.24
	m_pMesh->m_iMaxDevide = 64;
	m_nHoldItem.m_nHoldObjNo = 0;	// 手に持つ武器のオブジェ番号(設定しない)  // -- 2021.2.4
	for (int i = 0; i < ENM_GOLEM_MAX; i++)
	{
		m_pObjArray.push_back( new CEnmGolemObj(m_pGMain) );  // m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjID(m_dwProcID);						// -- 2021.2.4
		m_pObjArray[i]->SetObjNo(i);
		((CEnmGolemObj*)m_pObjArray[i])->SetMesh(this);    // メッシュのアドレスをオブジェクトに設定する   // -- 2021.2.4
	}
	m_nWaitTime = m_nMaxwaitTime = nWait;
	manNum = 0;                     // M.S 配置済み人数
	exclusiveMan = false;           // M.S 配置中フラグ
	surfaceNumTarget = 0;           // M.S 調べる面の数字
	managementDeadProcess = false;  // M.S 乗車処理中フラグ
}
//============================================================================
//
// 敵ゴーレムプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmGolemProc::~CEnmGolemProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================
//
// 敵ゴーレムオブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmGolemObj::CEnmGolemObj( CGameMain* pGMain) : CBaseObj( pGMain)
{
	const int nMaxHP = 1200;     // 体力
	const int nAtc   = 200;      // 体の攻撃力
	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_vTarget = GetPositionVector(m_mWorld);
	// オブジェクトのバウンディングボックスの設定
	VECTOR3 vMin(-1.8f, -0.05f, -1.0f);
	VECTOR3 vMax(1.8f, 7.5f, 1.0f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11
	m_nHp = m_nMaxHp = nMaxHP;
	m_nAtc = nAtc;
	doneProcess = false;   // M.S 配置しているかフラグ
	alive = true;          // M.S 未乗車処理フラグ
	manSurfaceNum = -1;	    // M.S 人オブジェクトがいる面の数字
	thisManArrayNumber = 0; // M.S 配置した順番の保存
	initialProcess = true;  // M.S 最初のみの処理フラグ
	// M.S プレイキャラの方向を向かせる角度をマップの回転に合わせて調整する変数
	initialRotate = 0.0f;
	// M.S 0:まだ周りに通過済み駅線路がない 1:周りに通過済み駅線路が発生 3:乗り込みアニメーションと処理が終了
	initialDeadAnim = 0;
	// M.S 乗車アニメーションのタイムカウント
	animCount = 173;
	// M.S 乗車アニメーションの時間
	saveAnimCount = 173;
}
// ---------------------------------------------------------------------------
//
// 敵ゴーレムオブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmGolemObj::~CEnmGolemObj()
{
}
// ---------------------------------------------------------------------------  // -- 2021.2.4
//
// 敵ゴーレムオブジェクトのメッシュポインタ設定
//
//  CEnmGolemProc* pProc
//
// ---------------------------------------------------------------------------
void CEnmGolemObj::SetMesh(CEnmGolemProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
	m_nHoldItem = pProc->GetHoldItem();			// 手に持つ武器の情報を得る

	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;
}
// M.S 配置する位置を排出する関数
// 引  数：なし
// 戻り値：なし
void CEnmGolemProc::ResetPlacementMan() {
	srand(time(NULL));              // 乱数パターンの取得
	for (int i = 0; i < 6; i++) {
		int num = rand() % 10;  // ランダムで位置取得
		int var = num;          // verに設定
		num = rand() % 10;      // ランダムで位置取得
		int hori = num;         // horiに設定
		for (int num = 0; num < 100; num++) {
		// ゲーム開始時に操作できないようにならない(詰まない)ために調整
		// 配置する行が3以下ならばverとhoriを再設定
			if (i == 0 && hori <= 3) {
				int againNum = rand() % 10; 
				var = againNum;
				againNum = rand() % 10;
				hori = againNum;
			}
			else {
				break;
			}
		}
		// 配列に配置する行と列をセット
		numH[i] = hori; 
		numV[i] = var;
	}
}
// ---------------------------------------------------------------------------
//
// 敵ゴーレムプロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmGolemProc::Update()
{
	// M.S マップ数字が2かどうか
	if (m_pGMain->m_pMapProc->MapNumGet() == 2) {    
		VECTOR3 mHit;
		VECTOR3 mNor;
      	// M.S 現在の線路配置可能の面を調べる
		for (int i = 0; i < 6; i++) {
			// M.S 正面(操作配置可能面)か調べるためレイを飛ばす位置変数
			MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 10.0f, 0.0f);
			MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
			bool nowPosSurfaceflag = m_pGMain->m_pMapProc->m_pBBoxPosition[i]->
				OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
           // M.S 調べた面にまだ人を配置していなく
		   // 配置中の人オブジェクトがなければ配置する
			if (nowPosSurfaceflag == true) {
				surfaceNumTarget = i;
				if ((PlacementManMap[surfaceNumTarget] == 0)
					&& (m_pGMain->m_pEnmProc->m_pEnmGolemProc->exclusiveMan == false)) {
					if (manNum < 6) {
						m_pObjArray[manNum]->Start();
						manNum++;     // M.S 配置済み人数を足す
					}
		    // M.S 配置が終了したらPlacementManMapのその面の要素に1をいれる
					PlacementManMap[surfaceNumTarget] = 1;
					break;
				}
			}
		}
	}
}
// ---------------------------------------------------------------------------
//
// 敵ゴーレムオブジェクトの発生
//
// ---------------------------------------------------------------------------
BOOL CEnmGolemObj::Start()
{
	// M.S マップ2かつまだ配置していない人オブジェクトだったら
	if ((m_pGMain->m_pMapProc->MapNumGet() == 2) && (doneProcess == false)) {
		srand(time(NULL));              // M.S 乱数パターンの取得
		// M.S マップの回転可能フラグをfalse
		m_pGMain->m_pMapProc->doneManPlacement = false;
		// M.S 人オブジェクト操作中フラグをtrue
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->exclusiveMan = true;		
		// M.S 回転角度フラグを初期化
		rotate0 = false;
		rotate90 = false;
		rotate180 = false;   
		rotate270 = false;		
		// M.S 正面(操作可能面)の位置の変数
		VECTOR3 frontPos = VECTOR3(0.0f, 6.0f, 0.0f);
		// M.S 配置する面の現在の回転を調べる  
		// rotate0:0度回転 rotate90:90度回転 rotate180:180度回転 rotate270:270度回転
		int northNow = m_pGMain->m_pPcProc->
			judgeDirection(m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget, frontPos, 0);
		switch (northNow) {
		case 1:
			rotate0 = true;
			break;
		case 2:
			rotate90 = true;
			break;
		case 3:
			rotate180 = true;
			break;
		case 4:
			rotate270 = true;
			break;
		}
		// M.S 人オブジェクトの配置している人数の数字をmanArrayNumに入れる
		int manArrayNum = m_pGMain->m_pEnmProc->m_pEnmGolemProc->manNum;
		// M.S 配置が他の人オブジェクトと重なっていないか、重なっていた場合再度乱数で配置を決める
		int investigateHori = m_pGMain->m_pEnmProc->m_pEnmGolemProc->numH[manArrayNum];
		int investigateVer = m_pGMain->m_pEnmProc->m_pEnmGolemProc->numV[manArrayNum];
		for (int i = 0; i < 100; i++) {
			if (m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] == 0) {
				break;
			}
			int hori = rand() % 10;
			int var = rand() % 10;
			for (int num = 0; num < 100; num++) {
				hori = rand() % 10;
				var = rand() % 10;
				// M.S ゲーム開始時に操作できないようにならない(詰まない)ために調整
				// M.S 初期面でない、またはhoriが3より大きいならば
				if (manArrayNum != 0 || hori > 3) {
					// M.S 配列にhoriとvarをセットしてループを抜ける
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->numH[manArrayNum] = hori;
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->numV[manArrayNum] = var;
					// M.S investigateHoriとinvestigateVerに値をセット
					investigateHori = hori;
					investigateVer = var;
					break;
				}
			}
		}
		// M.S マップ配列面の数字と座標の位置を合わせる数の変数
		float adjustPlusPos = 4.5f;    
		float adjustMinusPos = -4.5f;
		float yPos = 5.0f;   // M.S 配置する高さ(Y座標)
		// M.S マップの回転に合わせて配置位置と回転をinitialRotateに保存
		if (rotate0 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateVer, yPos, adjustPlusPos -1 * investigateHori);
		}
		else if (rotate90 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateHori, yPos, adjustPlusPos - 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate90angle;
		}
		else if (rotate180 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateVer, yPos, adjustMinusPos + 1 * investigateHori);
			initialRotate = m_pGMain->m_pEnmProc->rotate180angle;
		}
		else if (rotate270 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateHori, yPos, adjustMinusPos + 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate270angle;
		}
	    m_bActive = TRUE;
	    // M.S 人オブジェクトの配置されている面を保存
		manSurfaceNum = m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget;
		// M.S マップ配列を更新
		m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] = 10;
		// M.S マップの回転可能フラグをtrue
		m_pGMain->m_pMapProc->doneManPlacement = true;
		// M.S 人オブジェクトの配置している人数の数字を保存
		thisManArrayNumber = manArrayNum;
		// M.S 人オブジェクト操作中フラグをfalse
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->exclusiveMan = false;
		// M.S 配置済み
		doneProcess = true;
		return TRUE;
	}
	return FALSE;
}
// M.S プレイキャラの位置に合わせて
// 人オブジェクトとプレイキャラが上面にいるとした位置をだす
// 引  数：なし
// 戻り値：なし
void	CEnmGolemObj::OutUpPos() {
	switch (m_pGMain->m_pPcProc->GetPcObjPtr()->nowPcPosNum) {
	case 0:
		manPos = VECTOR3(manPos.x, manPos.y, manPos.z);
		pcPos = VECTOR3(pcPos.x, pcPos.y, pcPos.z);
		break;
	case 1:
		manPos = VECTOR3(manPos.x, 5.0f, manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, pcPos.y);
		break;
	case 2:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.z);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.z);
		break;
	case 3:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.y);
		break;
	case 4:
		manPos = VECTOR3(-1.0f * manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(-1.0f * pcPos.y, 5.0f, pcPos.z);
		break;
	case 5:
		manPos = VECTOR3(manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(pcPos.y, 5.0f, pcPos.z);
		break;
	}
}
//-----------------------------------------------------------------------------
// 敵ゴーレムオブジェクトの制御
//
//　キーボードとマウスで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定　その他
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmGolemObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない

	if (alive == true ) {
		// 変数の初期化  ---------------------------------------
		m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
		m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
		m_mWorldOld = m_mWorld;  // 一つ前の位置
		// M.S マップの回転を止める
		m_pGMain->m_pEnmProc->rotateOkFlagMan = false;
		// M.S プレイキャラと人オブジェクトのいる面が一致していた場合
		if ((manSurfaceNum == m_pGMain->m_pPcProc->GetPcObjPtr()->surfaceNum) 
			&& m_pGMain->m_pMapProc->MapNumGet() == 2) {
			// M.S プレイキャラの位置を取得
			pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
			// M.S 人オブジェクトの位置を取得
			manPos = GetPositionVector(m_mWorld);
			float plusAngle = 0.0f;  // M.S 回転の角度
			// M.S その人オブジェクトのいる面の回転を調べる
			int north = m_pGMain->m_pPcProc->judgeDirection(manSurfaceNum, manPos, 1);
			// M.S 調べた回転を合わせてplusAngleに角度をいれる
			switch (north) {  // M.S 1:回転なし 2:右90度回転 3:右180度回転 4:右270度回転 
			case 1:
				break;
			case 2:
				plusAngle = m_pGMain->m_pEnmProc->rotate90angle;
				break;
			case 3:
				plusAngle = m_pGMain->m_pEnmProc->rotate180angle;
				break;
			case 4:
				plusAngle = m_pGMain->m_pEnmProc->rotate270angle;
			}
			// M.S プレイキャラの位置に合わせて
			// 人オブジェクトとプレイキャラが上面にいるとした位置をだす
			OutUpPos();
			// M.S 人オブジェクトがプレイキャラを向いているマトリックス
			MATRIX4X4 manLookWorld = GetLookatMatrix(manPos, pcPos);
			// M.S manLookWorldのY要素を取り出す
			MATRIX4X4 manLookRotateY = GetRotateMatrixY(manLookWorld);
			// M.S manLookRotateYのvector（角度）
			VECTOR3 manLookRotate = GetRotateVector(manLookRotateY);
			// M.S manLookRotate.y + 面の回転 - 配置時の角度する
			manLookRotate.y = manLookRotate.y + plusAngle - initialRotate;
			// M.S manLookRotate.yが360より小さくなるようにする
			for (int i = 0; i < 100; i++) {
				if (manLookRotate.y >= 360) {
					manLookRotate.y = manLookRotate.y - 360.0f;
				}
				else {
					break;
				}
			}
			// M.S manLookRotate.y(プレイキャラの方向を向く)の回転マトリックス
			manRotate = XMMatrixRotationY(XMConvertToRadians(manLookRotate.y));
			if (initialProcess == true) {
				// M.S 最初のみの処理
				m_mWorld = manRotate * m_mWorld;
				initialProcess = false;
			}
			else {
				// M.S manRotateOldをかけて戻してからmanRotateをかけてプレイヤーの方を向かせる
				MATRIX4X4 returnManRotate = manRotateOld * m_mWorld;
				m_mWorld = manRotate * returnManRotate;
			}
			// M.S 戻す回転を保存
			manRotateOld = XMMatrixRotationY(XMConvertToRadians(360.0f - manLookRotate.y));
			// M.S マップの回転をできるようにする
			m_pGMain->m_pMapProc->doneManPlacement = true;
			// M.S プレイキャラが近づいた時のアニメーションの変更
			float distance = magnitude(manPos - pcPos);
			if (distance <= 2.0f && initialDeadAnim != 1) {
				m_AnimStatus.SetNum(1);
			}
			else if (initialDeadAnim == false) {
				m_AnimStatus.SetNum(0);
			}
			// M.S 駅が近くに置かれた時の処理
			UpdateDead();
		}
		// M.S マップの回転を可能にする
		m_pGMain->m_pEnmProc->rotateOkFlagMan = true;
		// 描画処理  ---------------------------------------------
		// スキンメッシュレンダリング
		int shineFlag = 0;    // M.S レンダーの指定
		m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
		// バウンディングボックス
		m_pBBox->m_mWorld = m_mWorld;
	}
}

//-----------------------------------------------------------------------------
// 敵ゴーレムオブジェクトの制御
//
//　敵が通常状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmGolemObj::UpdateNormal()
{
}

//-----------------------------------------------------------------------------
// 敵ゴーレムオブジェクトの制御
//
//  敵がダメージ状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmGolemObj::UpdateDamage()
{
	
}

//-----------------------------------------------------------------------------
// 敵ゴーレムオブジェクトの制御
//
//  敵が死亡状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmGolemObj::UpdateDead()
{
	int afterStationNum = 8;  // M.S プレイヤーが通過後の配列に入っている数字
	int humanNum = 10;        // M.S 人キャラがいる場所に入っている数字
	int afterHumanNum = 0;    // M.S 人キャラ乗車後に配列に入っている数字(初期化)
	// M.S 配置されている人オブジェクトだった場合
	if (doneProcess == true && alive == true) {
		// M.S 短くするために行、列を変数に入れる
		int hori = m_pGMain->m_pEnmProc->m_pEnmGolemProc->numH[thisManArrayNumber];
		int ver = m_pGMain->m_pEnmProc->m_pEnmGolemProc->numV[thisManArrayNumber];
		// M.S マップ正面だった場合、上下左右どこかに駅オブジェクトがあったら
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->frontFlag == true) {		
			if (m_pGMain->m_pMapProc->lineMap1[hori][ver] == humanNum
				&&(m_pGMain->m_pMapProc->lineMap1[hori + 1][ver] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori - 1][ver] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][ver + 1] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][ver - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {    // M.S 乗車フェーズが0の場合
					// M.S 乗車処理中フラグをtrue
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);	   // M.S 乗車アニメーションをセット
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // フレームエンドの一つ手前にする
					initialDeadAnim = 1;       // M.S 乗車フェーズを1にする
				}
				// M.S 乗車アニメーションが終わったら(animCountが0以下ならば)
				else if(animCount <= 0){     
					animCount = saveAnimCount;     // M.S animCountをもとに戻す
					initialDeadAnim = 3;           // M.S 乗車フェーズを3にする
					// M.S HighMan(赤)の乗車人数を+1
					m_pGMain->m_pEnmProc->getHighStageMan++;  
					// M.S 乗車後のマップ配列を0にして更新
					m_pGMain->m_pMapProc->lineMap1[hori][ver] = afterHumanNum;
					// M.S 乗車処理中フラグをfalse
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = false;
					m_bActive = FALSE; 		      // M.S 画面に表示させない
					m_pGMain->rideSound->Play();  // M.S 乗車効果音
					m_AnimStatus.SetNum(0);       // M.S アニメーションを元に戻す
					alive = false;                // M.S 未乗車処理フラグをfalse
				}
				animCount--;                // M.S アニメーションする時間を引く
			}
		}
		else {
			// M.S マップ正面以外だった場合、上下左右どこかに駅オブジェクトがあったら
			if (m_pGMain->m_pPcProc->lineMapSub[hori][ver] == humanNum
				&& (m_pGMain->m_pPcProc->lineMapSub[hori + 1][ver] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori - 1][ver] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][ver + 1] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][ver - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {    // M.S 乗車フェーズが0の場合
					// M.S 乗車処理中フラグをtrue
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);    // M.S 乗車アニメーションをセット
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // フレームエンドの一つ手前にする
					initialDeadAnim = 1;       // M.S 乗車フェーズを1にする
				}
				// M.S 乗車アニメーションが終わったら(animCountが0以下ならば)
				else if (animCount <= 0) {  
					animCount = saveAnimCount;   // M.S animCountをもとに戻す
					initialDeadAnim = 3;         // M.S 乗車フェーズを3にする			
					// M.S HighMan(赤)の乗車人数を+1	
					m_pGMain->m_pEnmProc->getHighStageMan++;      
					// M.S マップ配列を0にする
					m_pGMain->m_pPcProc->lineMapSub[hori][ver] = afterHumanNum; 
					// M.S マップ配列の更新
					m_pGMain->m_pPcProc->lineMapSet(manSurfaceNum);   
					// M.S 乗車処理中フラグをfalse
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = false;
					m_bActive = FALSE; 		      // M.S 画面に表示させない
					m_pGMain->rideSound->Play();  // M.S 乗車効果音
					m_AnimStatus.SetNum(0);       // M.S アニメーションを元に戻す
					alive = false;                // M.S 未乗車処理フラグをfalse
				}
				animCount--;                      // M.S アニメーションする時間を引く
			}
		}
	}
}

//============================================================================
//
// 敵ＲＳプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmRSProc::CEnmRSProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait    = 500;                   // 敵が発生するまでの待ち時間
	m_dwProcID         = ENM_RS_ID;             // 敵ＲＳのID
	m_nNum = m_nMaxNum = ENM_RS_ALLMAX;         // 敵ＲＳの最大出現数

	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/Man/MiddleMan_Idle.mesh") );
	m_pMesh->LoadAnimation(_T("Data/Char/Man/MiddleMan_Idle.anmx"), eRootAnimXZ);
	m_pMesh->LoadAnimation(_T("Data/Char/Man/MiddleMan_HappyIdle.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/MiddleMan_Jump.anmx"));
	m_pMesh->m_fHeightMax = 0.01f;
	m_pMesh->m_iMaxDevide = 8;
	m_nHoldItem.m_nHoldObjNo = 7;	// 手に持つ武器のオブジェ番号(透明な盾)  // -- 2021.2.4
	m_nHoldItem.m_nPosMesh = 0;		// 剣の根元位置のメッシュ番号
	m_nHoldItem.m_nPosBone = 48;	// 剣の根元位置のボーン番号
	m_nHoldItem.m_nOffsetPos = VECTOR3(0.0f, -0.5f, 0.0f);  // 手に持つ武器の位置オフセット
	m_nHoldItem.m_nOffsetRot = VECTOR3(-20.0f, -70.0f, -30.0f);  // 手に持つ武器の角度オフセット

	for (int i = 0; i < ENM_RS_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmRSObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjID(m_dwProcID);						// -- 2021.2.4
		m_pObjArray[i]->SetObjNo(i);
		((CEnmRSObj*)m_pObjArray[i])->SetMesh(this);  // メッシュのアドレスをオブジェクトに設定する  // -- 2021.2.4
	}

	m_nWaitTime = m_nMaxwaitTime = nWait;
	exclusiveMan = false;         // M.S 配置中フラグ
	surfaceNumTarget = 0;          // M.S 調べる面の数字
	managementDeadProcess = false;  // M.S 乗車処理中フラグ
}
//============================================================================
//
// 敵ＲＳプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmRSProc::~CEnmRSProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================
//
// 敵ＲＳオブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmRSObj::CEnmRSObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nMaxHP = 800;      // 体力
	const int nAtc   = 150;      // 体の攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	m_vTarget = GetPositionVector(m_mWorld);

	// バウンディングボックスの設定
	VECTOR3 vMin(-1.0f, -0.05f, -1.0f);
	VECTOR3 vMax(1.0f, 2.7f, 1.5f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11

	m_nHp = m_nMaxHp = nMaxHP;
	m_nAtc = nAtc;

	doneProcess = false;    // M.S 配置しているかフラグ
	alive = true;           // M.S 未乗車処理フラグ
	manSurfaceNum = -1;       // M.S 人オブジェクトがいる面の数字
	thisManArrayNumber = 0;  // M.S 配置した順番の保存
	initialProcess = true;  // M.S 最初のみの処理フラグ
	// M.S プレイキャラの方向を向かせる角度をマップの回転に合わせて調整する変数
	initialRotate = 0.0f;
	// M.S 0:まだ周りに通過済み駅線路がない 1:周りに通過済み駅線路が発生 3:乗り込みアニメーションと処理が終了
	initialDeadAnim = 0;
	// M.S 乗車アニメーションのタイムカウント
	animCount = 80;
	// M.S 乗車アニメーションの時間
	saveAnimCount = 80;
}
// ---------------------------------------------------------------------------
//
// 敵ＲＳオブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmRSObj::~CEnmRSObj()
{
	;
}
// ---------------------------------------------------------------------------
//
// 敵ＲＳオブジェクトのメッシュポインタ設定
//
//  CEnmRSProc* pProc
//
// ---------------------------------------------------------------------------  // -- 2021.2.4
void CEnmRSObj::SetMesh(CEnmRSProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
	m_nHoldItem = pProc->GetHoldItem();			// 手に持つ武器の情報を得る

	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;
}
// M.S 配置する位置を排出する関数
// 引  数：なし
// 戻り値：なし
void CEnmRSProc::ResetPlacementMan() {
	srand(time(NULL));              // 乱数パターンの取得
	for (int i = 0; i < 6; i++) {
		int num = rand() % 10;  // ランダムで位置取得
		int var = num;          // verに設定
		num = rand() % 10;      // ランダムで位置取得
		int hori = num;         // horiに設定
		for (int num = 0; num < 100; num++) {
			// ゲーム開始時に操作できないようにならない(詰まない)ために調整
			// 配置する行が3以下ならばverとhoriを再設定
			if (i == 0 && hori <= 3) {
				int againNum = rand() % 10;
				var = againNum;
				againNum = rand() % 10;
				hori = againNum;
			}
			else {
				break;
			}
		}
		// 配列に配置する行と列をセット
		numH[i] = hori;
		numV[i] = var;
	}
}
// ---------------------------------------------------------------------------
//
// 敵ＲＳプロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmRSProc::Update()
{
	// M.S マップ数字が2かどうか
	if (m_pGMain->m_pMapProc->MapNumGet() == 2) {
		VECTOR3 mHit;
		VECTOR3 mNor;
		// M.S 現在の線路配置可能の面を調べる
		for (int i = 0; i < 6; i++) {
			// M.S 正面(操作配置可能面)か調べるためレイを飛ばす位置変数
			MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 10.0f, 0.0f);
			MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
			bool nowPosSurfaceflag = m_pGMain->m_pMapProc->m_pBBoxPosition[i]->
			  OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
			// M.S 調べた面にまだ人を配置していなく
	        // 配置中の人オブジェクトがなければ配置する  
			if (nowPosSurfaceflag == true) {
				surfaceNumTarget = i;
				if ((PlacementManMap[surfaceNumTarget] == 0) 
					&& (m_pGMain->m_pEnmProc->m_pEnmRSProc->exclusiveMan == false)) {
					if (manNum < 6) {
						m_pObjArray[manNum]->Start();
						manNum++;      // M.S 配置済み人数を足す
					}
					// M.S 配置が終了したらPlacementManMapのその面の要素に1をいれる
					PlacementManMap[surfaceNumTarget] = 1;
					break;
				}
			}
		}
	}
}
// ---------------------------------------------------------------------------
//
// 敵ＲＳオブジェクトの発生
//
// ---------------------------------------------------------------------------
BOOL CEnmRSObj::Start()
{
	// M.S マップ2かつまだ配置していない人オブジェクトだったら
	if ((m_pGMain->m_pMapProc->MapNumGet() == 2) && (doneProcess == false)) {
		srand(time(NULL));     // M.S 乱数パターンの取得
		// M.S マップの回転可能フラグをfalse
		m_pGMain->m_pMapProc->doneManPlacement = false;
		// M.S 人オブジェクト操作中フラグをtrue
		m_pGMain->m_pEnmProc->m_pEnmRSProc->exclusiveMan = true;
		// M.S 回転角度フラグを初期化
		rotate0 = false;
		rotate90 = false;
		rotate180 = false;
		rotate270 = false;
		// M.S 正面(操作可能面)の位置の変数
		VECTOR3 frontPos = VECTOR3(0.0f, 6.0f, 0.0f);
		// M.S 配置する面の現在の回転を調べる  
		// rotate0:0度回転 rotate90:90度回転 rotate180:180度回転 rotate270:270度回転
		int northNow = m_pGMain->m_pPcProc->
			judgeDirection(m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget, frontPos, 0);
		switch (northNow) {
		case 1:
			rotate0 = true;
			break;
		case 2:
			rotate90 = true;
			break;
		case 3:
			rotate180 = true;
			break;
		case 4:
			rotate270 = true;
			break;
		}
		// M.S 人オブジェクトの配置している人数の数字をmanArrayNumに入れる
		int manArrayNum = m_pGMain->m_pEnmProc->m_pEnmRSProc->manNum;
		// M.S 配置が他の人オブジェクトと重なっていないか、重なっていた場合再度乱数で配置を決める
		int investigateHori = m_pGMain->m_pEnmProc->m_pEnmRSProc->numH[manArrayNum];
		int investigateVer = m_pGMain->m_pEnmProc->m_pEnmRSProc->numV[manArrayNum];
		for (int i = 0; i < 100; i++) {
			if (m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] == 0) {
				break;
			}
			int hori = rand() % 10;
			int var = rand() % 10;
			for (int num = 0; num < 100; num++) {
				hori = rand() % 10;
			    var = rand() % 10;
				// M.S ゲーム開始時に操作できないようにならない(詰まない)ために調整
			    // M.S 初期面でない、またはhoriが3より大きいならば
				if (manArrayNum != 0 || hori > 3) {  
					// M.S 配列にhoriとvarをセットしてループを抜ける
					m_pGMain->m_pEnmProc->m_pEnmRSProc->numH[manArrayNum] = hori;
					m_pGMain->m_pEnmProc->m_pEnmRSProc->numV[manArrayNum] = var;
					// M.S investigateHoriとinvestigateVerに値をセット
					investigateHori = hori;
					investigateVer = var;
					break;
				}
			}
		}
		// M.S マップ配列面の数字と座標の位置を合わせる数の変数
		float adjustPlusPos = 4.5f;
		float adjustMinusPos = -4.5f;
		float yPos = 5.0f;   // M.S 配置する高さ(Y座標)
		// M.S マップの回転に合わせて配置位置と回転をinitialRotateに保存
		if (rotate0 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateVer, yPos, adjustPlusPos - 1 * investigateHori);
		}
		else if (rotate90 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateHori, yPos, adjustPlusPos - 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate90angle;;
		}
		else if (rotate180 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateVer, yPos, adjustMinusPos + 1 * investigateHori);
			initialRotate = m_pGMain->m_pEnmProc->rotate180angle;;
		}
		else if (rotate270 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateHori, yPos, adjustMinusPos + 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate270angle;;
		}
		m_bActive = TRUE;
		// M.S 人オブジェクトの配置されている面を保存
		manSurfaceNum = m_pGMain->m_pEnmProc->m_pEnmRSProc->surfaceNumTarget;
		// M.S マップ配列を更新
		m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] = 10;
		// M.S マップの回転可能フラグをtrue
		m_pGMain->m_pMapProc->doneManPlacement = true;
		// M.S 人オブジェクトの配置している人数の数字を保存
		thisManArrayNumber = manArrayNum;
		// M.S 人オブジェクト操作中フラグをfalse
		m_pGMain->m_pEnmProc->m_pEnmRSProc->exclusiveMan = false;
		// M.S 配置済み
		doneProcess = true;
		return TRUE;
	}
	return FALSE;
}
// M.S プレイキャラの位置に合わせて
// 人オブジェクトとプレイキャラが上面にいるとした位置をだす
// 引  数：なし
// 戻り値：なし
void	CEnmRSObj::OutUpPos() {
	switch (m_pGMain->m_pPcProc->GetPcObjPtr()->nowPcPosNum) {
	case 0:
		manPos = VECTOR3(manPos.x, manPos.y, manPos.z);
		pcPos = VECTOR3(pcPos.x, pcPos.y, pcPos.z);
		break;
	case 1:
		manPos = VECTOR3(manPos.x, 5.0f, manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, pcPos.y);
		break;
	case 2:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.z);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.z);
		break;
	case 3:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.y);
		break;
	case 4:
		manPos = VECTOR3(-1.0f * manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(-1.0f * pcPos.y, 5.0f, pcPos.z);
		break;
	case 5:
		manPos = VECTOR3(manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(pcPos.y, 5.0f, pcPos.z);
		break;
	}
}
//-----------------------------------------------------------------------------
// 敵ＲＳオブジェクトの制御
//
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmRSObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない
	if (alive == true ) {
		// 変数の初期化  ---------------------------------------
		m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
		m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
		m_mWorldOld = m_mWorld;  // 一つ前の位置
		// M.S マップの回転を止める
		m_pGMain->m_pEnmProc->rotateOkFlagMan = false;
		// M.S プレイキャラと人オブジェクトのいる面が一致していた場合
		if ((manSurfaceNum == m_pGMain->m_pPcProc->GetPcObjPtr()->surfaceNum)
			&& m_pGMain->m_pMapProc->MapNumGet() == 2) {
			// M.S プレイキャラの位置を取得
		    pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
			// M.S 人オブジェクトの位置を取得
			manPos = GetPositionVector(m_mWorld);
			float plusAngle = 0.0f;  // M.S 回転の角度
			// M.S その人オブジェクトのいる面の回転を調べる
			int north = m_pGMain->m_pPcProc->judgeDirection(manSurfaceNum, manPos, 1);
			// M.S 調べた回転を合わせてplusAngleに角度をいれる
			switch (north) {  // M.S 1:回転なし 2:右90度回転 3:右180度回転 4:右270度回転 
			case 1:
				break;
			case 2:
				plusAngle = m_pGMain->m_pEnmProc->rotate90angle;
				break;
			case 3:
				plusAngle = m_pGMain->m_pEnmProc->rotate180angle;
				break;
			case 4:
				plusAngle = m_pGMain->m_pEnmProc->rotate270angle;
			}
			// M.S プレイキャラの位置に合わせて
			// 人オブジェクトとプレイキャラが上面にいるとした位置をだす
			OutUpPos();
			// M.S 人オブジェクトがプレイキャラを向いているマトリックス
			MATRIX4X4 manLookWorld = GetLookatMatrix(manPos, pcPos);
			// M.S manLookWorldのY要素を取り出す
			MATRIX4X4 manLookRotateY = GetRotateMatrixY(manLookWorld);
			// M.S manLookRotateYのvector（角度）
			VECTOR3 manLookRotate = GetRotateVector(manLookRotateY);
			// M.S manLookRotate.y + 面の回転 - 配置時の角度をする
			manLookRotate.y = manLookRotate.y + plusAngle - initialRotate;
			// M.S manLookRotate.yが360より小さくなるようにする
			for (int i = 0; i < 100; i++) {
				if (manLookRotate.y >= 360) {
					manLookRotate.y = manLookRotate.y - 360.0f;
				}
				else {
					break;
				}
			}
			// M.S manLookRotate.y(プレイキャラの方向を向く)の回転マトリックス
			manRotate = XMMatrixRotationY(XMConvertToRadians(manLookRotate.y));
			if (initialProcess == true) {
				// M.S 最初のみの処理
				m_mWorld = manRotate * m_mWorld;
				initialProcess = false;
			}
			else {
				// M.S manRotateOldをかけて戻してからmanRotateをかけてプレイヤーの方を向かせる
				MATRIX4X4 returnManRotate = manRotateOld * m_mWorld;
				m_mWorld = manRotate * returnManRotate;
			}
			// M.S 戻す回転を保存
			manRotateOld = XMMatrixRotationY(XMConvertToRadians(360.0f - manLookRotate.y));
			// M.S マップの回転をできるようにする
			m_pGMain->m_pMapProc->doneManPlacement = true;
			// M.S プレイキャラが近づいた時のアニメーションの変更
			float distance = magnitude(manPos - pcPos);
			if (distance <= 2.0f && initialDeadAnim != 1) {
				m_AnimStatus.SetNum(1);
			}
			else if (initialDeadAnim == false) {
				m_AnimStatus.SetNum(0);
			}
			// M.S 駅が近くに置かれた時の処理
			UpdateDead();
		}
		// M.S マップの回転を可能にする
		m_pGMain->m_pEnmProc->rotateOkFlagMan = true;
		// 描画処理  ---------------------------------------------
		// スキンメッシュレンダリング
		int shineFlag = 0;  // M.S レンダーの指定
		m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
		// バウンディングボックス
		m_pBBox->m_mWorld = m_mWorld;
	}
}

//-----------------------------------------------------------------------------
// 敵ＲＳオブジェクトの制御
//
// 敵が通常状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmRSObj::UpdateNormal()
{

}

//-----------------------------------------------------------------------------
// 敵ＲＳオブジェクトの制御
//
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmRSObj::UpdateDamage()
{
	
}
//-----------------------------------------------------------------------------
// 敵ＲＳオブジェクトの制御
//
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmRSObj::UpdateDead()
{
	int afterStationNum = 8;  // M.S プレイヤーが通過後の配列に入っている数字
	int humanNum = 10;        // M.S 人キャラがいる場所に入っている数字
	int afterHumanNum = 0;    // M.S 人キャラが乗車後に配列に入っている数字(初期化)
	// M.S 配置されている人オブジェクトだった場合
	if (doneProcess == true && alive == true) {
		// M.S 短くするために行、列を変数に入れる
		int hori = m_pGMain->m_pEnmProc->m_pEnmRSProc->numH[thisManArrayNumber];
		int var = m_pGMain->m_pEnmProc->m_pEnmRSProc->numV[thisManArrayNumber];	
		// M.S マップ正面だった場合、上下左右どこかに駅オブジェクトがあったら
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->frontFlag == true) {
			if (m_pGMain->m_pMapProc->lineMap1[hori][var] == humanNum
				&&(m_pGMain->m_pMapProc->lineMap1[hori + 1][var] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori - 1][var] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][var + 1] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][var - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {   // M.S 乗車フェーズが0の場合
					// M.S 乗車処理中フラグをtrue
					m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);   // M.S 乗車アニメーションをセット
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // フレームエンドの一つ手前にする
					initialDeadAnim = 1;    // M.S 乗車フェーズを1にする
				}
				// M.S 乗車アニメーションが終わったら(animCountが0以下ならば)
				else if (animCount <= 0) {   
					animCount = saveAnimCount;  // M.S animCountをもとに戻す
					initialDeadAnim = 3;        // M.S 乗車フェーズを3にする
					// M.S MiddleMan(黄)の乗車人数を+1
					m_pGMain->m_pEnmProc->getMiddleStageMan++; 
					// M.S 乗車後のマップ配列を0にして更新
					m_pGMain->m_pMapProc->lineMap1[hori][var] = afterHumanNum;
					// M.S 乗車処理中フラグをfalse
					m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = false;
					m_bActive = FALSE;           // M.S 画面に表示させない
					m_pGMain->rideSound->Play(); // M.S 乗車効果音
					m_AnimStatus.SetNum(0);      // M.S アニメーションを元に戻す
					alive = false;               // M.S 未乗車処理フラグをfalse
				}
				animCount--;            // M.S アニメーションする時間を引く
			}
		}
		else {
			// M.S マップ正面以外だった場合、上下左右どこかに駅オブジェクトがあったら
			if (m_pGMain->m_pPcProc->lineMapSub[hori][var] == humanNum
				&&(m_pGMain->m_pPcProc->lineMapSub[hori + 1][var] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori - 1][var] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][var + 1] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][var - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {       // M.S 乗車フェーズが0の場合
					// M.S 乗車処理中フラグをtrue
					m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);       // M.S 乗車アニメーションをセット
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // フレームエンドの一つ手前にする
					initialDeadAnim = 1;          // M.S 乗車フェーズを1にする
				}
				// M.S 乗車アニメーションが終わったら(animCountが0以下ならば)
				else if (animCount <= 0) {
					animCount = saveAnimCount;    // M.S animCountをもとに戻す
					initialDeadAnim = 3;          // M.S 乗車フェーズを3にする
					// M.S MiddleMan(黄)の乗車人数を+1	
					m_pGMain->m_pEnmProc->getMiddleStageMan++; 
					// M.S マップ配列を0にする
					m_pGMain->m_pPcProc->lineMapSub[hori][var] = afterHumanNum; 
					// M.S マップ配列の更新
					m_pGMain->m_pPcProc->lineMapSet(manSurfaceNum); 
					// M.S 乗車処理中フラグをfalse
					m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = false;
					m_bActive = FALSE;            // M.S 画面に表示させない
					m_pGMain->rideSound->Play();  // M.S 乗車効果音
					m_AnimStatus.SetNum(0);       // M.S アニメーションを元に戻す
					alive = false;                // M.S 未乗車処理フラグをfalse
				}
				animCount--;                      // M.S アニメーションする時間を引く
			}
		}
	}
}
//============================================================================
//
// 敵ブルードラゴンプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmBdProc::CEnmBdProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	const int nWait    = 600;                   // 敵が発生するまでの待ち時間
	m_dwProcID         = ENM_BD_ID;             // 敵ブルードラゴンのID
	m_nNum = m_nMaxNum = ENM_BD_ALLMAX;         // 敵ブルードラゴンの最大出現数

	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/Man/LowMan_Idle.mesh"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/LowMan_Idle.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/LowMan_HappyIdle.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/LowMan_Jump.anmx"));
	m_pMesh->m_fHeightMax = 0.05f;     // ディスプレースメントマッピングの高さ  // -- 2020.1.24
	m_pMesh->m_iMaxDevide = 64;
	m_nHoldItem.m_nHoldObjNo = 4;	// 手に持つ武器のオブジェ番号(透明な銃)  // -- 2021.2.4
	m_nHoldItem.m_nPosMesh = 0;		// 剣の根元位置のメッシュ番号
	m_nHoldItem.m_nPosBone = 9;		// 剣の根元位置のボーン番号
	m_nHoldItem.m_nOffsetPos = VECTOR3(0.0f, 0.0f, 0.0f);  // 手に持つ武器の位置オフセット
	m_nHoldItem.m_nOffsetRot = VECTOR3(0.0f, 0.0f, 0.0f);  // 手に持つ武器の角度オフセット

	for (int i = 0; i < ENM_BD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmBdObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjID(m_dwProcID);						// -- 2021.2.4
		m_pObjArray[i]->SetObjNo(i);
		((CEnmBdObj*)m_pObjArray[i])->SetMesh( this);  // メッシュのアドレスをオブジェクトに設定する
	}

	m_nWaitTime = m_nMaxwaitTime = nWait;
	manNum = 0;                     // M.S 配置済み人数
	exclusiveMan = false;           // M.S 配置中フラグ
	surfaceNumTarget = 0;           // M.S 調べる面の数字
	managementDeadProcess = false;  // M.S 乗車処理中フラグ
}
//============================================================================
//
// 敵ブルードラゴンプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmBdProc::~CEnmBdProc()
{
	SAFE_DELETE(m_pMesh);
}

//============================================================================
//
// 敵ブルードラゴンオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CEnmBdObj::CEnmBdObj(CGameMain* pGMain) : CBaseObj( pGMain)
{
	const int nMaxHP = 5000;        // 体力
	const int nAtc   = 500;         // 体の攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	m_vTarget = GetPositionVector(m_mWorld);

	// バウンディングボックスの設定
	VECTOR3 vMin(-2.8f, -0.05f, -2.0f);
	VECTOR3 vMax(2.8f, 15.0f, 2.0f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11

	m_nHp = m_nMaxHp = nMaxHP;
	m_nAtc = nAtc;
	doneProcess = false;       // M.S 配置しているかフラグ
	alive = true;              // M.S 未乗車処理フラグ
	manSurfaceNum = 0;         // M.S 人オブジェクトがいる面の数字
	thisManArrayNumber = 0;    // M.S 配置した順番の保存
	initialProcess = true;    // M.S 最初のみの処理フラグ
	// M.S プレイキャラの方向を向かせる角度をマップの回転に合わせて調整する変数
	initialRotate = 0.0f;
	// M.S 0:まだ周りに通過済み駅線路がない 1:周りに通過済み駅線路が発生 3:乗り込みアニメーションと処理が終了
	initialDeadAnim = 0;
	// M.S 乗車アニメーションのタイムカウント
	animCount = 60;
	// M.S 乗車アニメーションの時間
	saveAnimCount = 60;
}
// ---------------------------------------------------------------------------
//
// 敵ブルードラゴンオブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmBdObj::~CEnmBdObj()
{
	;
}
// ---------------------------------------------------------------------------
//
// 敵ブルードラゴンオブジェクトのメッシュポインタ設定
//
//  CEnmBdProc* pProc
//
// ---------------------------------------------------------------------------  // -- 2021.2.4
void CEnmBdObj::SetMesh(CEnmBdProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
	m_nHoldItem = pProc->GetHoldItem();			// 手に持つ武器の情報を得る

	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;
}
// M.S 配置する位置を排出する関数
// 引  数：なし
// 戻り値：なし
void CEnmBdProc::ResetPlacementMan() {
	srand(time(NULL));              // 乱数パターンの取得
	for (int i = 0; i < 6; i++) {
		int num = rand() % 10;  // ランダムで位置取得
		int var = num;          // verに設定
		num = rand() % 10;      // ランダムで位置取得
		int hori = num;         // horiに設定
		for (int num = 0; num < 100; num++) {
			// ゲーム開始時に操作できないようにならない(詰まない)ために調整
			// 配置する行が3以下ならばverとhoriを再設定
			if (i == 0 && hori <= 3) {
				int againNum = rand() % 10;
				var = againNum;
				againNum = rand() % 10;
				hori = againNum;
			}
			else {
				break;
			}
		}
		// 配列に配置する行と列をセット
		numH[i] = hori;
		numV[i] = var;
	}
}
// ---------------------------------------------------------------------------
//
// 敵ブルードラゴンプロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmBdProc::Update()
{
	// M.S マップ数字が2かどうか
	if (m_pGMain->m_pMapProc->MapNumGet() == 2) {
		VECTOR3 mHit;
		VECTOR3 mNor;
		// M.S 現在の線路配置可能の面を調べる
		for (int i = 0; i < 6; i++) {
			// M.S 正面(操作配置可能面)か調べるためレイを飛ばす位置変数
			MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 10.0f, 0.0f);
			MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
			bool nowPosSurfaceflag = m_pGMain->m_pMapProc->
				m_pBBoxPosition[i]->
				OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
			// M.S 調べた面にまだ人を配置していなく
		    // 配置中の人オブジェクトがなければ配置する
			if (nowPosSurfaceflag == true) {
				surfaceNumTarget = i;
				if ((PlacementManMap[surfaceNumTarget] == 0) 
					&& (m_pGMain->m_pEnmProc->m_pEnmBdProc->exclusiveMan == false)) {
					if (manNum < 6) {
						m_pObjArray[manNum]->Start();
						manNum++;      // M.S 配置済み人数を足す
					}
					// M.S 配置が終了したらPlacementManMapのその面の要素に1をいれる
					PlacementManMap[surfaceNumTarget] = 1;
					break;
				}
			}
		}
	}
}
// ---------------------------------------------------------------------------
//
// 敵ブルードラゴンオブジェクトの発生
//
// ---------------------------------------------------------------------------
BOOL CEnmBdObj::Start()
{
	// M.S マップ2かつまだ配置していない人オブジェクトだったら
	if ((m_pGMain->m_pMapProc->MapNumGet() == 2) && (doneProcess == false)) {
		srand(time(NULL));     // M.S 乱数パターンの取得
		// M.S マップの回転可能フラグをfalse
		m_pGMain->m_pMapProc->doneManPlacement = false;
		// M.S 人オブジェクト操作中フラグをtrue
		m_pGMain->m_pEnmProc->m_pEnmBdProc->exclusiveMan = true;
		// M.S 回転角度フラグを初期化
		rotate0 = false;
		rotate90 = false;
		rotate180 = false;
		rotate270 = false;				// M.S 配置する面の現在の回転を調べる  
		// M.S 正面(操作可能面)の位置の変数
		VECTOR3 frontPos = VECTOR3(0.0f, 6.0f, 0.0f);
		// M.S 配置する面の現在の回転を調べる  
		// rotate0:0度回転 rotate90:90度回転 rotate180:180度回転 rotate270:270度回転
		int northNow = m_pGMain->m_pPcProc->
			judgeDirection(m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget, frontPos, 0);
		switch (northNow) {
		case 1:
			rotate0 = true;
			break;
		case 2:
			rotate90 = true;
			break;
		case 3:
			rotate180 = true;
			break;
		case 4:
			rotate270 = true;
			break;
		}
		// M.S 人オブジェクトの配置している人数の数字をmanArrayNumに入れる
		int manArrayNum = m_pGMain->m_pEnmProc->m_pEnmBdProc->manNum;
		// M.S 配置が他の人オブジェクトと重なっていないか、重なっていた場合再度乱数で配置を決める
		int investigateHori = m_pGMain->m_pEnmProc->m_pEnmBdProc->numH[manArrayNum];
		int investigateVer = m_pGMain->m_pEnmProc->m_pEnmBdProc->numV[manArrayNum];
		for (int i = 0; i < 100; i++) {
			if (m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] == 0) {
				break;
			}
			int hori = rand() % 10;
			int var = rand() % 10;
			for (int num = 0; num < 100; num++) {
				hori = rand() % 10;
				var = rand() % 10;
				// M.S ゲーム開始時に操作できないようにならない(詰まない)ために調整
				// M.S 初期面でない、またはhoriが3より大きいならば
				if (manArrayNum != 0 || hori > 3) {
					// M.S 配列にhoriとvarをセットしてループを抜ける
					m_pGMain->m_pEnmProc->m_pEnmBdProc->numH[manArrayNum] = hori;
					m_pGMain->m_pEnmProc->m_pEnmBdProc->numV[manArrayNum] = var;
					// M.S investigateHoriとinvestigateVerに値をセット
					investigateHori = hori;   
					investigateVer = var;
					break;
				}
			}
		}
		// M.S マップ配列面の数字と座標の位置を合わせる数の変数
		float adjustPlusPos = 4.5f;
		float adjustMinusPos = -4.5f;
		float yPos = 5.0f;   // M.S 配置する高さ(Y座標)
		// M.S マップの回転に合わせて配置位置と回転をinitialRotateに保存
		if (rotate0 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateVer, yPos, adjustPlusPos - 1 * investigateHori);
		}
		else if (rotate90 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateHori, yPos, adjustPlusPos - 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate90angle;;
		}
		else if (rotate180 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateVer, yPos, adjustMinusPos + 1 * investigateHori);
			initialRotate = m_pGMain->m_pEnmProc->rotate180angle;;
		}
		else if (rotate270 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateHori, yPos, adjustMinusPos + 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate270angle;;
		}
		m_bActive = TRUE;
		// M.S 人オブジェクトの配置されている面を保存
		manSurfaceNum = m_pGMain->m_pEnmProc->m_pEnmBdProc->surfaceNumTarget;
		// M.S マップ配列を更新
		m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] = 10;
		// M.S マップの回転可能フラグをtrue
		m_pGMain->m_pMapProc->doneManPlacement = true;
		// M.S 人オブジェクトの配置している人数の数字を保存
		thisManArrayNumber = manArrayNum;
		// M.S 人オブジェクト操作中フラグをfalse
		m_pGMain->m_pEnmProc->m_pEnmBdProc->exclusiveMan = false;
		// M.S 配置済み
		doneProcess = true;
		return TRUE;
	}
	return FALSE;
}
// M.S プレイキャラの位置に合わせて
// 人オブジェクトとプレイキャラが上面にいるとした位置をだす
// 引  数：なし
// 戻り値：なし
void	CEnmBdObj::OutUpPos() {
	switch (m_pGMain->m_pPcProc->GetPcObjPtr()->nowPcPosNum) {
	case 0:
		manPos = VECTOR3(manPos.x, manPos.y, manPos.z);
		pcPos = VECTOR3(pcPos.x, pcPos.y, pcPos.z);
		break;
	case 1:
		manPos = VECTOR3(manPos.x, 5.0f, manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, pcPos.y);
		break;
	case 2:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.z);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.z);
		break;
	case 3:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.y);
		break;
	case 4:
		manPos = VECTOR3(-1.0f * manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(-1.0f * pcPos.y, 5.0f, pcPos.z);
		break;
	case 5:
		manPos = VECTOR3(manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(pcPos.y, 5.0f, pcPos.z);
		break;
	}
}
//-----------------------------------------------------------------------------
// 敵ブルードラゴンオブジェクトの制御
//
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmBdObj::Update()
{
	if (alive == true) {
		if (!m_bActive) return;  // 非表示のときは処理をしない
			// 変数の初期化  ---------------------------------------
		m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
		m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
		m_mWorldOld = m_mWorld;  // 一つ前の位置
		// M.S マップの回転を止める
		m_pGMain->m_pEnmProc->rotateOkFlagMan = false;
		// M.S プレイキャラと人オブジェクトのいる面が一致していた場合
		if ((manSurfaceNum == m_pGMain->m_pPcProc->GetPcObjPtr()->surfaceNum) && m_pGMain->m_pMapProc->MapNumGet() == 2) {
			// M.S プレイキャラの位置を取得
		    pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
			// M.S 人オブジェクトの位置を取得
			manPos = GetPositionVector(m_mWorld);
			float plusAngle = 0.0f;  // M.S 回転の角度
			// M.S その人オブジェクトのいる面の回転を調べる
			int north = m_pGMain->m_pPcProc->judgeDirection(manSurfaceNum, manPos, 1);
			// M.S 調べた回転を合わせてplusAngleに角度をいれる
			switch (north) {  // M.S 1:回転なし 2:右90度回転 3:右180度回転 4:右270度回転 
			case 1:
				break;
			case 2:
				plusAngle = m_pGMain->m_pEnmProc->rotate90angle;
				break;
			case 3:
				plusAngle = m_pGMain->m_pEnmProc->rotate180angle;
				break;
			case 4:
				plusAngle = m_pGMain->m_pEnmProc->rotate270angle;
			}
			// M.S プレイキャラの位置に合わせて
			// 人オブジェクトとプレイキャラが上面にいるとした位置をだす
			OutUpPos();
			// M.S 人オブジェクトがプレイキャラを向いているマトリックス
			MATRIX4X4 manLookWorld = GetLookatMatrix(manPos, pcPos);
			// M.S manLookWorldのY要素を取り出す
			MATRIX4X4 manLookRotateY = GetRotateMatrixY(manLookWorld);
			// M.S manLookRotateYのvector（角度）
			VECTOR3 manLookRotate = GetRotateVector(manLookRotateY);
			// M.S manLookRotate.y + 面の回転 - 配置時の角度をする
			manLookRotate.y = manLookRotate.y + plusAngle - initialRotate;
			// M.S manLookRotate.yが360より小さくなるようにする
			for (int i = 0; i < 100; i++) {
				if (manLookRotate.y >= 360) {
					manLookRotate.y = manLookRotate.y - 360.0f;
				}
				else {
					break;
				}
			}
			// M.S manLookRotate.y(プレイキャラの方向を向く)の回転マトリックス
			manRotate = XMMatrixRotationY(XMConvertToRadians(manLookRotate.y));
			if (initialProcess == true) {
				// M.S 最初のみの処理
				m_mWorld = manRotate * m_mWorld;
				initialProcess = false;
			}
			else {
				// M.S manRotateOldをかけて戻してからmanRotateをかけてプレイヤーの方を向かせる
				MATRIX4X4 returnManRotate = manRotateOld * m_mWorld;
				m_mWorld = manRotate * returnManRotate;
			}
			// M.S 戻す回転を保存
			manRotateOld = XMMatrixRotationY(XMConvertToRadians(360.0f - manLookRotate.y));
			// M.S マップの回転をできるようにする
			m_pGMain->m_pMapProc->doneManPlacement = true;
			// M.S プレイキャラが近づいた時のアニメーションの変更
			float distance = magnitude(manPos - pcPos);
			if (distance <= 2.0f && initialDeadAnim != 1) {
				m_AnimStatus.SetNum(1);
			}
			else if (initialDeadAnim == false) {
				m_AnimStatus.SetNum(0);
			}
			// M.S 駅が近くに置かれた時の処理
			UpdateDead();
		}
		// M.S マップの回転を可能にする
		m_pGMain->m_pEnmProc->rotateOkFlagMan = true;
		// 描画処理  ---------------------------------------------
		// スキンメッシュレンダリング
		int shineFlag = 0;    // M.S レンダーの指定
		m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
		// バウンディングボックス
		m_pBBox->m_mWorld = m_mWorld;
	}
}

//-----------------------------------------------------------------------------
// 敵ブルードラゴンオブジェクトの制御
//
// 敵が通常状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmBdObj::UpdateNormal()
{
}

//-----------------------------------------------------------------------------
// 敵ブルードラゴンオブジェクトの制御
//
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmBdObj::UpdateDamage()
{
}
//-----------------------------------------------------------------------------
// 敵ブルードラゴンオブジェクトの制御
//
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmBdObj::UpdateDead()
{ 
	int afterStationNum = 8;  // M.S プレイヤーが通過後の配列に入っている数字
	int humanNum = 10;        // M.S 人キャラがいる場所に入っている数字
	int afterHumanNum = 0;    // M.S 人キャラが乗車後に配列に入っている数字(初期化)
	// M.S 配置されている人オブジェクトだった場合
	if (doneProcess == true && alive == true) {
		// M.S 短くするために行、列を変数に入れる
		int hori = m_pGMain->m_pEnmProc->m_pEnmBdProc->numH[thisManArrayNumber];
		int ver = m_pGMain->m_pEnmProc->m_pEnmBdProc->numV[thisManArrayNumber];
		// M.S マップ正面だった場合、上下左右どこかに駅オブジェクトがあったら
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->frontFlag == true) {
			if (m_pGMain->m_pMapProc->lineMap1[hori][ver] == humanNum
				&&(m_pGMain->m_pMapProc->lineMap1[hori + 1][ver] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori - 1][ver] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][ver + 1] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][ver - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {   // M.S 乗車フェーズが0の場合
					// M.S 乗車処理中フラグをtrue
					m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);  // M.S 乗車アニメーションをセット
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // フレームエンドの一つ手前にする
					initialDeadAnim = 1;    // M.S 乗車フェーズを1にする
				}
				// M.S 乗車アニメーションが終わったら(animCountが0以下ならば)
				else if (animCount <= 0) {
					animCount = saveAnimCount;   // M.S animCountをもとに戻す
					initialDeadAnim = 3;         // M.S 乗車フェーズを3にする
					// M.S lowMan(青)の乗車人数を+1
					m_pGMain->m_pEnmProc->getLowStageMan++; 
					// M.S 乗車処理中フラグをfalse
					m_pGMain->m_pMapProc->lineMap1[hori][ver] = afterHumanNum;
					m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = false;
					m_bActive = FALSE;           // M.S 画面に表示させない
					m_pGMain->rideSound->Play(); // M.S 乗車効果音
					m_AnimStatus.SetNum(0);      // M.S アニメーションを元に戻す
					alive = false;               // M.S 未乗車処理フラグをfalse              
				}
				animCount--;          // M.S アニメーションする時間を引く
			}
		}
		else {
			// M.S マップ正面以外だった場合、上下左右どこかに駅オブジェクトがあったら
			if (m_pGMain->m_pPcProc->lineMapSub[hori][ver] == humanNum
				&&(m_pGMain->m_pPcProc->lineMapSub[hori + 1][ver] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori - 1][ver] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][ver + 1] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][ver - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {      // M.S 乗車フェーズが0の場合
					// M.S 乗車処理中フラグをtrue
					m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);      // M.S 乗車アニメーションをセット
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // フレームエンドの一つ手前にする
					initialDeadAnim = 1;         // M.S 乗車フェーズを1にする
				}
				// M.S 乗車アニメーションが終わったら(animCountが0以下ならば)
				else if (animCount <= 0) {     
					animCount = saveAnimCount;   // M.S animCountをもとに戻す 
					initialDeadAnim = 3;         // M.S 乗車フェーズを3にする
					// M.S lowMan(青)の乗車人数を+1	
					m_pGMain->m_pEnmProc->getLowStageMan++; 
					// M.S マップ配列を0にする
					m_pGMain->m_pPcProc->lineMapSub[hori][ver] = afterHumanNum; 
					// M.S マップ配列の更新
					m_pGMain->m_pPcProc->lineMapSet(manSurfaceNum); 
					// M.S 乗車処理中フラグをfalse
					m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = false;
					m_bActive = FALSE;           // M.S 画面に表示させない
					m_pGMain->rideSound->Play(); // M.S 乗車効果音
					m_AnimStatus.SetNum(0);      // M.S アニメーションを元に戻す
					alive = false;               // M.S 未乗車処理フラグをfalse
				}
				animCount--;    // M.S アニメーションする時間を引く
			}
		}
	}
}


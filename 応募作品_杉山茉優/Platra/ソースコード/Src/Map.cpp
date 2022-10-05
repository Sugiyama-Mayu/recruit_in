//=============================================================================
//		３Ｄゲームプログラム A
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//		  マップの処理
//																	Map.cpp
//=============================================================================
#include  "BaseProc.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Enemy.h"
#include  "Weapon.h"
#include  "GameMain.h"
#include  "Camera.h"
#include  "BackFore.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

//  星の動的配置
//M.S ランダム数字の排出関数
// 引  数：なし
// 戻り値：int   排出された1～4までのランダム数字
int CMapProc::RandomNumMeth() {             
	srand((unsigned int)time(NULL));  // ランダムの初期化
	randomNum = 1 + rand() % 4;       // 1～4までのランダム数字を取得
	return randomNum;
}
// M.S 方向を決め、その方向に進んだ時の縦横の位置排出
// 引  数：なし
// 戻り値：なし
void CMapProc::DecideDirection() {
	ver = startVertical;              // bufに縦と横を入れる
	hori = startHorizontal;
	randomNum = RandomNumMeth();      // ランダム数字を出し、進む方向を決める(1を入れる)
	switch (randomNum) {
	case 1:
		up = 1;
		break;
	case 2:
		down = 1;
		break;
	case 3:
		left = 1;
		break;
	case 4:
		right = 1;
	}
	if ((up == 1) || (down == 1)) {      // 縦か横かで関数を通った後の戻り値の受け取りを変更
		hori = outStartNum(up, down, left, right, ver, hori);
	}
	else if ((left == 1) || (right == 1)) {
		ver = outStartNum(up, down, left, right, ver, hori);
	}
}
// M.S 方向に進んだ時の縦横の位置排出
// 引  数：int up                  1の場合、排出する方向は上
//         int down                1の場合、排出する方向は下
//         int left                1の場合、排出する方向は左
//         int righ                1の場合、排出する方向は右
//         int startVertical       位置を求める位置の列数
//         int startHorizontal     位置を求める位置の行数
// 戻り値：int                     求めた位置 
//                                 求められなかった場合、0
int CMapProc::outStartNum(int up, int down, int left, int right, int startVertical, int startHorizontal) {  
	int startVerticalBuf = startVertical;
	int startHorizontalBuf = startHorizontal;
	if (up == 1) {
		startHorizontalBuf -= 2;       // 位置を求める場所から2進む
		return startHorizontalBuf;
	}
	else if (down == 1) {
		startHorizontalBuf += 2;
		return startHorizontalBuf;
	}
	else if (left == 1) {
		startVerticalBuf -= 2;
		return startVerticalBuf;
	}
	else if (right == 1) {
		startVerticalBuf += 2;
		return startVerticalBuf;
	}
	return 0;
}
//M.S 星の動的生成の関数
// 引  数：なし
// 戻り値：int*          生成した星の配列のポインタ
int* CMapProc::MapDynamic()
{
	startVertical = 0;                              // 初期値をセット
	startVertical = 0 + rand() % 5;                 // 0～4までのランダム数字を取得
	startHorizontal = 0;                            // 初期値をセット   
	startHorizontal = 0 + rand() % 5;               // 0～4までのランダム数字を取得
	startMap[startHorizontal][startVertical] = 1;   // そこをスタートに決定(１を入れる)
	// 無限ループ
	while (1) {
		DecideDirection();
		while (1) { // 進める位置が確定するまで無限ループ
			// verとhoriが0～4で、進んだ先が0だった場合（配列に1を入れる）
			if (ver < 5 && hori < 5 && ver > -1 && hori > -1 && startMap[hori][ver] == 0) {
				// 進んだ方向に合わせて配列に１を入れる
				if (up == 1) {                 
					if (startMap[hori + 1][ver] != 1) {
						startMap[hori + 1][ver] = 1;
					}
					else {
					}
				}
				else if (down == 1) {
					if (startMap[hori - 1][ver] != 1) {
						startMap[hori - 1][ver] = 1;
					}
					else {
					}
				}
				else if (right == 1) {
					if (startMap[hori][ver - 1] != 1) {
						startMap[hori][ver - 1] = 1;
					}
					else {
					}
				}
				else if (left == 1) {
					if (startMap[hori][ver + 1] != 1) {
						startMap[hori][ver + 1] = 1;
					}
					else {
					}
				}
				arrowSwitch[0] = 0;         // 各方向判定スイッチの初期化
				arrowSwitch[1] = 0;
				arrowSwitch[2] = 0;
				arrowSwitch[3] = 0;
				startMap[hori][ver] = 1;       // 進んだ先に１を入れる
				startHorizontal = hori;        // 位置の更新
				startVertical = ver;
				break;
			}
			else { // 進んだ先が0以外(配置済み)だった場合(配列に1を入れない)
				// 方向を全て試しても進める方向がないかどうか
				if (arrowSwitch[0] == 1 && arrowSwitch[1] == 1 && arrowSwitch[2] == 1 && arrowSwitch[3] == 1) {
					int* startMapP;
					startMapP = &startMap[0][0];  // startMapPにstartMap配列のアドレスを入れる
					return startMapP;
				}
				if (up == 1) {   // 方向変数の初期化
					up = 0;
				}
				else if (down == 1) {
					down = 0;
				}
				else if (left == 1) {
					left = 0;
				}
				else if (right == 1) {
					right = 0;
				}
				randomNum = RandomNumMeth(); // ランダム数字の排出
				switch (randomNum) {
				case 1:
					up = 1;
					arrowSwitch[0] = 1;       // 済んだ方向に確認済みの1を入れる
					break;
				case 2:
					down = 1;
					arrowSwitch[1] = 1;
					break;
				case 3:
					left = 1;
					arrowSwitch[2] = 1;
					break;
				case 4:
					right = 1;
					arrowSwitch[3] = 1;
				}
				ver = startVertical;
				hori = startHorizontal;
				if ((up == 1) || (down == 1)) {   // 縦か横かで関数を通った後の戻り値の受け取りを変更
					hori = outStartNum(up, down, left, right, ver, hori);
				}
				else if ((left == 1) || (right == 1)) {
					ver = outStartNum(up, down, left, right, ver, hori);
				}
			}
		}
	}
}
//=============================================================================
//
// マッププロシージャのコンストラクタ
//
//-----------------------------------------------------------------------------
CMapProc::CMapProc(CGameMain*	pGMain)
{
	// クラス全体のクリヤー
	// (vectorクラスは初期化不要)
	m_pGMain = pGMain;
	m_dwMapNo = 1;
	m_bActive = FALSE;
	m_pColMesh = NULL;					// コリジョンメッシュへのポインタ
	m_nEvtIdx = 0;							// -- 2021.2.4
	// M.S ここから下のコンストラクタの内容は追加しました
	// M.S ↓--------------------------------------------------------------------
	mapStarArrayBuf = MapDynamic(); // 星の動的生成配列の作成
	up = 0;                         // 星の動的生成で使う方向変数
	down = 0;
	right = 0;
	left = 0;                 
	startVertical = 0;              // 星の動的生成に使用する配列の列
	startHorizontal = 0;            // 星の動的生成に使用する配列の行
	ver = startVertical;            // 星の動的生成に使用する配列の列buf
	hori = startHorizontal;         // 星の動的生成に使用する配列の行buf
	randomNum = 0;                  //RandomNumMeth()で使用する変数
	// ゲーム中に使用する変数
	lineMap1[4][4] = 5;             // 初期プレイヤー位置
	ChangeButton = 0;               // 配置物の変更数字
    trainNumSt = 0;                 // 各線路の配置数
	trainNumSd = 0;
	trainNumCg = 0;
	trainNumSta = 0;
	oldH = m_pGMain->initialH;      // 今の配置物の位置の保存
	oldV = m_pGMain->initialV;
	LineChangeFlag = 0;             // 0:初期 1:上 2:右 3:下 4:左
	changeNum = 0;					// 方向転換線路の方向変数1
	aboutArrow = 0;                 // 方向転換線路の方向変数2
	typeChangeNum = 1;              // 配置可能な線路の数字
	starRotateSwitch = 0;           // 星の回転を順番通りに処理する為の変数
	pointArrow1 = 0;                // 星の回転角度を求めるための変数
	pointArrow2 = 0;
	pointArrow3 = 0;
	pointArrow4 = 0;
	sideDegree = 0.0f;              // 星の回転角度の保存(横回転)
	heightDegree = 0.0f;            // 星の回転角度の保存(縦回転)
	rotateFinish = false;           // 回転処理終了フラグ
	surfaceMap = 0;                 // 正面にある面の数字
	pointArrowNum1 = 0;             // pointArrow変数の計算結果の保存変数
	pointArrowNum2 = 0;
	setOk = false;                  // 配列の書き込み、読み込みを順番通りにする変数
	northNow = 0;                   // 現在の星の面の回転（北）の位置保存変数
    horiRotate = 0;                 // 回転後のカーソルの位置を配列に合わせたものにして保存する変数(行)
	verRotate = 0;                  // 回転後のカーソルの位置を配列に合わせたものにして保存する変数(列)
	oldRotateSurface = 0;           // 保存するべき面を示す変数
	PlacementSurfaceNum = 0;        // 最後に操作したマップ面の保存変数
	newSurfacePlacement = false;    // 次のマップ面への配置許可
	permissionH = 0;               // 次のマップ面への配置許可用のクリック位置変数
	permissionV = 0;
	doneManPlacement = true;       // 人の配置が完了したかどうかのフラグ
	// マップの回転に合わせてオブジェクトの移動が終わったかどうか
	rotateProcessDoneFlag = true;  // 回転処理のオブジェクトの回転などが終わったのかフラグ
	arrayHNum = 0;                 // 回転用の各人キャラクターの数
	arrayMNum = 0;
	arrayLNum = 0;
	front = VECTOR3(0.0f, 10.0f, 0.0f);   // 位置を調べるためのバウンディングボックスの位置変数
	back  = VECTOR3(0.0f, 1.5f, 0.0f);
	starBridgeLitingTime = 0;   // 星の架け橋を光らせるカウント変数
	starBridgePosNum = 1;       // だんだん橋を光らせる為の橋移動用変数
	changeButtonWithinRange = false; // 配置する線路が範囲内かどうかのフラグ
	surfaceMapLineJudge = 0;         // 現在の操作面マップ
	linePlacementOkFlag = true;      // 配置処理完了フラグ
	SaveRotateSurfaceFlag = false;   // マップ面の保存、更新完了フラグ
	waitTime = 0;                    // 星生成のエフェクトのタイムカウント
	saveHori = 0;                    // 星生成のエフェクトに使用する配列要素番号(行)
	saveVer = 0;                     // 星生成のエフェクトに使用する配列要素番号(列)
	starEffectOrder = 0;             // 星生成のエフェクトのフェーズ
	starObjArrayNum = 0;             // 発生させた星生成エフェクトの数	
	// マップ3の星の架け橋の配置許可
	starBridgePermission = false;  // 星の架け橋配置許可
	starBridgeInputFlag = false;   // クリックしたかフラグ
	NearStarCol = false;           // 手前の星とマウスの接触フラグ
	frontStarCol = false;          // 奥の星とマウスの接触フラグ
}
//-----------------------------------------------------------------------------
//
// マッププロシージャのデストラクタ
//
//-----------------------------------------------------------------------------
CMapProc::~CMapProc()
{
	DestroyAll();
}

//-----------------------------------------------------------------------------
//
// マップの削除
//
//-----------------------------------------------------------------------------
void CMapProc::DestroyAll()
{
	m_bActive = FALSE;
	m_nEvtIdx = 0;							// -- 2021.2.4

	// メッシュのデリート
	for(DWORD i = 0; i<m_SkyMap.size(); i++)
	{
		SAFE_DELETE(m_SkyMap[i].m_pMesh);
		SAFE_DELETE(m_SkyMap[i].m_pWave);    // 使用していないが念のため削除
	}
	for(DWORD i = 0; i<m_StageMap.size(); i++)
	{
		SAFE_DELETE(m_StageMap[i].m_pMesh);
		SAFE_DELETE(m_StageMap[i].m_pWave);
		SAFE_DELETE(m_StageMap[i].m_pBBox);
	}
	for (DWORD i = 0; i<m_MoveMap.size(); i++)
	{
		SAFE_DELETE(m_MoveMap[i].m_pMesh);
		SAFE_DELETE(m_MoveMap[i].m_pColMesh);
	}
	for (DWORD i = 0; i < m_EventMap.size(); i++)   // -- 2021.2.4
	{
		SAFE_DELETE(m_EventMap[i].m_pBBox);
	}
	SAFE_DELETE(m_pColMesh);

	m_dwMapNo = 0;
	// vectorの削除
	m_SkyMap.clear();					// 空のマップ  配列削除
	m_SkyMap.shrink_to_fit();			// 空のマップ  不要メモリ解放
	m_StageMap.clear();					// ステージのマップ  配列削除
	m_StageMap.shrink_to_fit();			// ステージのマップ 不要メモリ解放
	m_MoveMap.clear();					// 移動マップ  配列削除
	m_MoveMap.shrink_to_fit();			// 移動マップ 不要メモリ解放
	m_NavMap.clear();					// ナビゲーションマップ配列削除
	m_NavMap.shrink_to_fit();			// ナビゲーションマップ不要メモリ解放
	m_EventMap.clear();					// イベントマップ配列削除
	m_EventMap.shrink_to_fit();			// イベントマップ不要メモリ解放
}
// M.S ゲームの初期化をする関数
// 引  数：なし
// 戻り値：なし
void CMapProc::ResetNewGameMap() {
	for (int hori = 0; hori < 10; hori++) {
		for (int ver = 0; ver < 10; ver++) {
			lineMap1[hori][ver] = 0 ;      // 操作用のマップ配列
			lineMapBuf1[hori][ver] = 0;    // 初期状態でこちら側の面
			lineMapBuf2[hori][ver] = 0;    // こちら側のその下の面
			lineMapBuf3[hori][ver] = 0;    // 一番下の面
			lineMapBuf4[hori][ver] = 0;    // lineMapBuf2の裏側
			lineMapBuf5[hori][ver] = 0;    // 左側の面
			lineMapBuf6[hori][ver] = 0;    // 右側の面
		}
	}
	for (int hori = 0; hori < 5; hori++) {  // 星の動的配列の初期化
		for (int ver = 0; ver < 5; ver++) {
			startMap[hori][ver] = 0;
		}
	}
	lineMap1[4][4] = 5;           // ラインマップのプレイヤーの位置
	up = 0;                       // 星動的生成の穴を掘る方向用変数
	down = 0;
	right = 0;
	left = 0;                     // 方向変数
	startVertical = 0;            // 星の動的生成に使用する配列の列
	startHorizontal = 0;          // 星の動的生成に使用する配列の行
	ver = startVertical;          // 星の動的生成に使用する配列の列buf
	hori = startHorizontal;       // 星の動的生成に使用する配列の行buf
	arrowSwitch[4] = { 0 };       // どの方向が終わったかの判定用配列
	ChangeButton = 0;             //配置物の変更数字
	trainNumSt = 0;               // 各線路の配置数
	trainNumSd = 0;
	trainNumCg = 0;
	trainNumSta = 0;
	oldH = m_pGMain->initialH;    // 今の配置物の位置の記憶
	oldV = m_pGMain->initialV;
	LineChangeFlag = 0;           // 0:初期 1:上 2:右 3:下 4:左
	changeNum = 0;                // 方向転換線路の方向変数1
	aboutArrow = 0;               // 方向転換線路の方向変数2
	typeChangeNum = 1;            // 配置可能な線路の数字
	starRotateSwitch = 0;         // 星の回転を順番通りに処理する為の変数
	pointArrow1 = 0;              // 星の回転角度を求めるための変数
	pointArrow2 = 0; 
	pointArrow3 = 0;
	pointArrow4 = 0;
	sideDegree = 0.0f;            // 星の回転角度の保存(横回転)
	heightDegree = 0.0f;          // 星の回転角度の保存(縦回転)         
	rotateFinish = false;         // 回転処理終了フラグ
	pointArrowNum1 = 0;           // pointArrow変数の計算結果の保存変数
	pointArrowNum2 = 0;
	setOk = false;                // 配列の書き込み、読み込みを順番通りにする変数
	northNow = 0;                 // 現在の星の面の回転（北）の位置保存変数
	horiRotate = 0;               // 回転後のカーソルの位置を配列に合わせたものにして保存する変数(行)
	verRotate = 0;                // 回転後のカーソルの位置を配列に合わせたものにして保存する変数(列)
	oldRotateSurface = 0;         // 保存するべき面を示す変数
	PlacementSurfaceNum = 0;      // 最後に操作したマップ面の保存変数
	newSurfacePlacement = false;  // 次のマップ面への配置許可
    saveHori = 0;                 // 星動的生成時にエフェクトを発生するために確認した場所の保存
	saveVer = 0;
	permissionH = 0;               // 次のマップ面への配置許可用のクリック位置変数
	permissionV = 0;
	SaveRotateSurfaceFlag = false; // 次のマップ面の保存フラグ
	doneManPlacement = true;
	// マップの回転に合わせてオブジェクトの移動が終わったかどうか
	rotateProcessDoneFlag = true;
	arrayHNum = 0;                 // 回転用の各人キャラクターの数
	arrayMNum = 0;
	arrayLNum = 0;
	// PlayCharのリセット
	m_pGMain->m_pPcProc->ResetNewGamePc();
	// Manのリセット
	m_pGMain->m_pEnmProc->ResetNewGameMan();
	// GameMainのリセット
	m_pGMain->rotateFlag = false;
	// 現在の操作マップの位置
	surfaceMap = 0;
	// 星の架け橋のオブジェクトの移動用変数
	starBridgePosNum = 1;
    // 星の架け橋ゲージのキラキラのアニメーション数の初期化
	m_pGMain->m_pBackForeProc->glitterAnimNum = 0;
	// セーブ完了音フラグの初期化
	m_pGMain->m_pBackForeProc->doneBridgeSound = false;
	starBridgeLitingTime = 0;                 // 星の架け橋を光らせるカウント変数
	changeButtonWithinRange = false;          // 配置する線路が範囲内かどうかのフラグ
}
//-----------------------------------------------------------------------------
//
// マップ１の遠くから画面
//		m_bActive	0	int
//-----------------------------------------------------------------------------
void CMapProc::LoadMap1()
{
	// vector初期化用の構造体
	const STAGEMAP      sm;
	const MOVEMAP       mm;
	const NAVIGATIONMAP nv;
	//	M.S 動的生成した星配列のポインタをずらしつつ実体をmapStarArray配列に入れる
	for (int hori = 0; hori < 5; hori++) {
		for (int ver = 0; ver < 5; ver++) {
			mapStarArray[hori][ver] = *mapStarArrayBuf;
			mapStarArrayBuf++;
		}
	}
	// 全マップの削除 -----------------------------------------------
	DestroyAll();
	// 全ての敵・武器・効果の非表示化 
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // 敵の発生数のリセット
	// ＰＣを(0,0,-20)の位置に置く -------------------------------------
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(-5.0f, 70.0f, -0.0f));   // ワールド座標でもマップと同じ座標
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ローカル軸(Y軸)を0度にする
	m_pGMain->transparentSwitch = true;
	// ステージマップの設定・コリジョンマップの設定 -----------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // コリジョンマップの生成	
	int arrayNum = 0;
	// M.S ファイル書き込み用配列の初期化
	for (int arrayNum = 0; arrayNum < 25; arrayNum++) {
		m_pGMain->starArray[arrayNum] = 0;
	}
	int i = 0;
	// M.S 動的生成した星の情報を保存
	for (int hori = 0; hori < 5; hori++) {
		for (int ver = 0; ver < 5; ver++) {
			// M.S 星配列が1ならば
			if (mapStarArray[hori][ver] == 1) {
				// M.S 5.0fの変え方で幅が変わる -〇の増減でモデルが左右に動く
				// M.S -5.0の変え方で幅が変わる +〇を増やすと上にモデルが動く
				float starSetX = 5.0f*ver + 10.0f*ver;    
				float starSetZ = -5.0f*hori - 10.0f*hori;  
				m_StageMap.push_back(sm);
				// M.S 星の作成
				m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/EarthStar/earthStar.mesh"));
				m_StageMap[i].m_mWorld = XMMatrixTranslation(0, 0.0f, 100);
				m_StageMap[i].m_pBBox = new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax); // xyz１mのオブジェクト
				m_StageMap[i].m_pBBox->m_mWorld = m_StageMap[i].m_mWorld;
				m_pColMesh->AddFbxLoad(_T("Data/Map/EarthStar/earthStar.mesh"), VECTOR3(0, 0.0f, 100)); // ドアメッシュコリジョンの設定
				m_pGMain->haveToGoStar++;   // M.S 行かなければならない星の数を足す
				m_pGMain->starArray[i] = 1; // M.S ファイル書き込み用配列に入れる
				i++;
			}
			else {
			}
		}
	}
	// 空用  -----------------------------------------------------------
	// 空マップの設定[0]
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/GalaxyBack/galaxyBackGround.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	// ファイルの書き込み
	m_pGMain->FileWrite();
	// マップＮＯ１
	m_dwMapNo = 1;
	m_bActive = TRUE;
}
// M.S 登録する配置物の数
const int MAX_SET = 600;
// M.S 縦の線路(TrainLineStProc)のコンストラクタ
// 引  数：GameMainのポインタ
TrainLineStProc::TrainLineStProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	// メッシュの設定
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/trainLine.mesh"));
	for (int i = 0; i < MAX_SET; i++) {
		m_pTLSObjArray.push_back(new TrainLineStObj(m_pGMain));
		m_pTLSObjArray[i]->SetLineNum(1);            // 配置物番号の登録
		m_pTLSObjArray[i]->SetMesh(this);            // メッシュアドレスの登録
	}
}
// M.S 縦の線路(TrainLineStProc)のデストラクタ
TrainLineStProc::~TrainLineStProc() {

}
// M.S 横の線路(TrainLineSdProc)のコンストラクタ
// 引  数：GameMainのポインタ
TrainLineSdProc::TrainLineSdProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	// メッシュの設定
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/trainLineSide.mesh"));
	for (int i = 0; i < MAX_SET; i++) {
		m_pTLSDObjArray.push_back(new TrainLineSdObj);
		m_pTLSDObjArray[i]->SetLineNum(1);            // 配置物番号の登録
		m_pTLSDObjArray[i]->SetMesh(this);            // メッシュアドレスの登録
	}
}
// M.S 横の線路(TrainLineSdProc)のデストラクタ

TrainLineSdProc::~TrainLineSdProc() {

}
// M.S 方向切り替え線路(TrainLineCgProc)のコンストラクタ
// 引  数：GameMainのポインタ
TrainLineCgProc::TrainLineCgProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	// メッシュの設定
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/trainLine_Big_Center.mesh"));
	for (int i = 0; i < MAX_SET; i++) {
		m_pTCGObjArray.push_back(new TrainLineCgObj);
		m_pTCGObjArray[i]->SetLineNum(2);            // 配置物番号の登録
		m_pTCGObjArray[i]->SetMesh(this);            // メッシュアドレスの登録
	}
}
// M.S 方向切り替え線路(TrainLineCgProc)のデストラクタ
TrainLineCgProc::~TrainLineCgProc() {

}
// M.S 駅(TrainLineStationProc)のコンストラクタ
// 引  数：GameMainのポインタ
TrainLineStationProc::TrainLineStationProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	// メッシュの設定
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/station.mesh"));
	for (int i = 0; i < MAX_SET; i++) {
		m_pTLSTAObjArray.push_back(new TrainLineStationObj);
		m_pTLSTAObjArray[i]->SetLineNum(3);            // 配置物番号の登録
		m_pTLSTAObjArray[i]->SetMesh(this);            // メッシュアドレスの登録
	}
}
// M.S 駅(TrainLineStationProc)のデストラクタ
TrainLineStationProc::~TrainLineStationProc() {

}
// M.S 縦の線路(TrainLineStObj)のコンストラクタ
// 引  数：GameMainのポインタ
TrainLineStObj::TrainLineStObj(CGameMain* pGMain) {
}
// M.S 縦の線路(TrainLineStObj)のデストラクタ
TrainLineStObj::~TrainLineStObj() {

}
// M.S 横の線路(TrainLineSdObj)のコンストラクタ
// 引  数：なし
TrainLineSdObj::TrainLineSdObj() {

}
// M.S 横の線路(TrainLineSdObj)のデストラクタ
TrainLineSdObj::~TrainLineSdObj() {

}
// M.S 方向切り替え線路(TrainLineCgObj)のコンストラクタ
// 引  数：なし
TrainLineCgObj::TrainLineCgObj() {

}
// M.S 方向切り替え線路(TrainLineCgObj)のデストラクタ
TrainLineCgObj::~TrainLineCgObj() {

}
// M.S 駅(TrainLineStationObj)のコンストラクタ
// 引  数：なし
TrainLineStationObj::TrainLineStationObj() {

}
// M.S 駅(TrainLineStationObj)のデストラクタ
TrainLineStationObj::~TrainLineStationObj() {

}
// M.S 各面に1つ配置するBBoxの作成、配置
// 引  数：なし
// 戻り値：なし
void CMapProc::MakeFrontBBox(){
  //  正面に向いている面の判定BBox
  // 初期状態でy軸のプラス方向の面に配置するBBox
  m_pBBoxPosition[0] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5)); 
  // 初期状態でz軸のマイナス方向の面に配置するBBox
  m_pBBoxPosition[1] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5)); 
  // 初期状態でy軸のマイナス方向の面に配置するBBox
  m_pBBoxPosition[2] =
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5)); 
  // 初期状態でz軸のプラス方向の面に配置するBBox
  m_pBBoxPosition[3] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
  // 初期状態でx軸のプラス方向の面に配置するBBox
  m_pBBoxPosition[4] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
  // 初期状態でx軸のマイナス方の面向に配置するBBox
  m_pBBoxPosition[5] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));

  // 作ったBBoxを各面に配置する
  m_pBBoxPosition[0]->m_mWorld = XMMatrixTranslation(0.0f, 5.0f, 0.0f);  
  m_pBBoxPosition[1]->m_mWorld = XMMatrixTranslation(0.0f, 0.0f, -5.0f); 
  m_pBBoxPosition[2]->m_mWorld = XMMatrixTranslation(0.0f, -5.0f, 0.0f); 
  m_pBBoxPosition[3]->m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 5.0f);  
  m_pBBoxPosition[4]->m_mWorld = XMMatrixTranslation(5.0f, 0.0f, 0.0f);  
  m_pBBoxPosition[5]->m_mWorld = XMMatrixTranslation(-5.0f, 0.0f, 0.0f); 
}
// M.S 各面に4つ配置するBBox(面の回転を見るため)の作成
// 引  数：なし
// 戻り値：なし
void CMapProc::MakeSurfaceBBox() {
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow1[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow2[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow3[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow4[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow5[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow6[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
}
// M.S 各面に4つ配置するBBox(面の回転を見るため)の配置
// 引  数：なし
// 戻り値：なし
void CMapProc::SetPosSurfaceBBox(){
	// 初期状態でy軸のプラス方向の面に配置するBBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow1[ar]->m_mWorld = XMMatrixTranslation(0.0f, 6.0f, 4.0f);  // 上
			break;
		case 1:
			m_pBBoxArrow1[ar]->m_mWorld = XMMatrixTranslation(0.0f, 6.0f, -4.0f); // 下
			break;
		case 2:
			m_pBBoxArrow1[ar]->m_mWorld = XMMatrixTranslation(4.0f, 6.0f, 0.0f);  // 右
			break;
		case 3:
			m_pBBoxArrow1[ar]->m_mWorld = XMMatrixTranslation(-4.0f, 6.0f, 0.0f); // 左
			break;
		}
	}
// 初期状態でz軸のプラス方向の面に配置するBBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow2[ar]->m_mWorld = XMMatrixTranslation(0.0f, -4.0f, 6.0f);  // 上
			break;
		case 1:
			m_pBBoxArrow2[ar]->m_mWorld = XMMatrixTranslation(0.0f, 4.0f, 6.0f); // 下
			break;
		case 2:
			m_pBBoxArrow2[ar]->m_mWorld = XMMatrixTranslation(4.0f, 0.0f, 6.0f);  // 右
			break;
		case 3:
			m_pBBoxArrow2[ar]->m_mWorld = XMMatrixTranslation(-4.0f, 0.0f, 6.0f); // 左
			break;
		}
	}
// 初期状態でy軸のマイナス方向の面に配置するBBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow3[ar]->m_mWorld = XMMatrixTranslation(0.0f, -6.0f, -4.0f); // 上
			break;
		case 1:
			m_pBBoxArrow3[ar]->m_mWorld = XMMatrixTranslation(0.0f, -6.0f, 4.0f);  // 下
			break;
		case 2:
			m_pBBoxArrow3[ar]->m_mWorld = XMMatrixTranslation(4.0f, -6.0f, 0.0f);  // 右
			break;
		case 3:
			m_pBBoxArrow3[ar]->m_mWorld = XMMatrixTranslation(-4.0f, -6.0f, 0.0f); // 左
			break;
		}
	}
// 初期状態でz軸のマイナス方向の面に配置するBBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow4[ar]->m_mWorld = XMMatrixTranslation(0.0f, 4.0f, -6.0f);  // 上
			break;
		case 1:
			m_pBBoxArrow4[ar]->m_mWorld = XMMatrixTranslation(0.0f, -4.0f, -6.0f); // 下
			break;
		case 2:
			m_pBBoxArrow4[ar]->m_mWorld = XMMatrixTranslation(4.0f, 0.0f, -6.0f);  // 右
			break;
		case 3:
			m_pBBoxArrow4[ar]->m_mWorld = XMMatrixTranslation(-4.0f, 0.0f, -6.0f); // 左
			break;
		}
	}
// 初期状態でx軸のプラス方向の面に配置するBBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow5[ar]->m_mWorld = XMMatrixTranslation(6.0f, 0.0f, 4.0f);  // 上
			break;
		case 1:
			m_pBBoxArrow5[ar]->m_mWorld = XMMatrixTranslation(6.0f, 0.0f, -4.0f); // 下
			break;
		case 2:
			m_pBBoxArrow5[ar]->m_mWorld = XMMatrixTranslation(6.0f, -4.0f, 0.0f); // 右
			break;
		case 3:
			m_pBBoxArrow5[ar]->m_mWorld = XMMatrixTranslation(6.0f, 4.0f, 0.0f);  // 左
			break;
		}
	}
// 初期状態でx軸のマイナス方向の面に配置するBBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow6[ar]->m_mWorld = XMMatrixTranslation(-6.0f, 0.0f, 4.0f);  // 上
			break;
		case 1:
			m_pBBoxArrow6[ar]->m_mWorld = XMMatrixTranslation(-6.0f, 0.0f, -4.0f); // 下
			break;
		case 2:
			m_pBBoxArrow6[ar]->m_mWorld = XMMatrixTranslation(-6.0f, 4.0f, 0.0f);  // 右
			break;
		case 3:
			m_pBBoxArrow6[ar]->m_mWorld = XMMatrixTranslation(-6.0f, -4.0f, 0.0f); // 左
			break;
		}
	}
}
//-----------------------------------------------------------------------------
//
// マップ２の作成と移動の処理
//
//-----------------------------------------------------------------------------
void CMapProc::LoadMap2()
{
	// vector初期化用の構造体
	const STAGEMAP      sm;
	const NAVIGATIONMAP nv;
	// 全マップの削除  -----------------------------------------------
	DestroyAll();
	// 全ての敵・武器・効果の非表示化
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // 敵の発生数のリセット
	lineMap1[4][4] = 5;       // M.S プレイヤーの位置を配列マップに反映
	// M.S 線路のvectorの添え字
	trainNumSt = 0;
	trainNumSd = 0;
	trainNumCg = 0;
	trainNumSta = 0;
	changeNum = 0;             // M.S 方向切り替えブロックの方向数字
	aboutArrow = 0;
	typeChangeNum = 1;         // M.S 線路の置く種類の識別数字  1:直線線路 2:方向変更線路
	starRotateSwitch = 0;      // M.S 星の回転を一回の操作で一度のみ行うため
	oldH = m_pGMain->initialH;   // M.S プレイヤーの初期位置4(行)
	oldV = m_pGMain->initialV;   // M.S プレイヤーの初期位置4(列)
	LineChangeFlag = 0;          // M.S プレイヤーの進んでいる方向
	// ステージマップの設定 ------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // コリジョンマップの生成
	int i = 0;
	m_pGMain->transparentSwitch = false; //キャラクターの表示
	// マップメッシュの設定[0]
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/EarthStar/centerEarthStar.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_StageMap[i].m_pBBox =
		new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax);
	// M.S 10*10のバウンディングボックスの作成
	for (int lineNumHori = 0; lineNumHori < 10; lineNumHori++) {
		for (int lineNumVer = 0; lineNumVer < 10; lineNumVer++) {
			m_pBBoxLine[lineNumHori][lineNumVer] = 
				new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-5.0f + lineNumVer, 0.0f, 4.0f - lineNumHori),
					/*Max*/ VECTOR3(-4.0f + lineNumVer, 0.01f, 5.0f - lineNumHori));
			m_pBBoxLine[lineNumHori][lineNumVer]->m_mWorld = XMMatrixTranslation(0.0f, 5.0f, 0.0f);
		}
	}
	i++;
	// M.S スタート位置の配置物
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/startPosition.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(-0.5f, 5.0f, 0.0f);
	m_StageMap[i].m_pBBox =
		new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax);
	i++;
	MakeFrontBBox();      // M.S 各面に1つ配置するBBoxの作成、配置
	MakeSurfaceBBox();    // M.S 各面に4つ配置するBBox(面の回転を見るため)の作成
	SetPosSurfaceBBox();  // M.S 各面に4つ配置するBBox(面の回転を見るため)の配置
	mMapWorldOld = m_StageMap[0].m_mWorld;    // -- 2022.1.18  回転前を保存
    // M.S 配置させたい位置とマップ位置をかけて、プレイキャラの位置を出す	
	MATRIX4X4 position = XMMatrixTranslation(-0.45f, 6.0f, 0.5f);  
	position = position * m_StageMap[0].m_mWorld;
	// M.S キャラクターの位置をセット
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(position);
	// キャラクターの位置を保存
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ローカル軸(Y軸)を0度にする
    // M.S 線路のオブジェクトを作る
	TrainLST = new TrainLineStProc(m_pGMain);            // M.S 縦線路
	TrainLSD = new TrainLineSdProc(m_pGMain);            // M.S 横線路
	TrainLChange = new TrainLineCgProc(m_pGMain);        // M.S 方向切り替え線路
	TrainLStation = new TrainLineStationProc(m_pGMain);  // M.S 駅
	// ドアメッシュの設定[1] 
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/MapItem/DOOR1.mesh")); // マップメッシュコリジョンの設定
	m_StageMap[i].m_mWorld = XMMatrixTranslation(220.0f, 0.0f, 240.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapItem/DOOR1.mesh"), VECTOR3(220.0f, 0.0f, 240.0f));
	SetEvent(VECTOR3(-1.5f, -0.05f, -1.0f), VECTOR3(1.5f, 2.8f, 1.0f), m_StageMap[i].m_mWorld, eEvtChangeMap, 3);  // イベントの設定(マップ3へ移動する)
	i++;
	// 空
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/GalaxyBack/galaxyBack_Circle.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	// M.S 人オブジェクトの配置ランダム位置の排出
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->ResetPlacementMan();
	m_pGMain->m_pEnmProc->m_pEnmRSProc->ResetPlacementMan();
	m_pGMain->m_pEnmProc->m_pEnmBdProc->ResetPlacementMan();
	// マップＮＯ２
	m_dwMapNo = 2;
	m_bActive = TRUE;
}
//-----------------------------------------------------------------------------
//
// マップ３の作成と移動の処理
//
//-----------------------------------------------------------------------------
void CMapProc::LoadMap3()
{
	// vector初期化用の構造体
	const STAGEMAP      sm;
	const MOVEMAP       mm;
	const NAVIGATIONMAP nv;

	// 全マップの削除 -----------------------------------------------
	DestroyAll();
	// M.S 行った星の数の更新
	// M.S ランキングモードかどうか
	if (m_pGMain->m_dwGameMode == 3) {
		// M.S 人オブジェクトの合計を出す
		m_pGMain->rankRedMan += m_pGMain->m_pEnmProc->getHighStageMan;
		m_pGMain->rankYellowMan += m_pGMain->m_pEnmProc->getMiddleStageMan;
		m_pGMain->rankBlueMan += m_pGMain->m_pEnmProc->getLowStageMan;
		// M.S 行った星の数の更新
		m_pGMain->rankTraveledStar++;
	}
	else if(m_pGMain->m_dwGameMode != 3){
		// M.S 人オブジェクトの合計の保存
		m_pGMain->m_pEnmProc->getHighMan += m_pGMain->m_pEnmProc->getHighStageMan;
		m_pGMain->m_pEnmProc->getMiddleMan += m_pGMain->m_pEnmProc->getMiddleStageMan;
		m_pGMain->m_pEnmProc->getLowMan += m_pGMain->m_pEnmProc->getLowStageMan;
		// M.S 行った星の数の更新
		m_pGMain->traveledStar++;
	}	
	// M.S 最後の星だったらゴール(ランキングモードの場合)
	if (m_pGMain->m_dwGameMode == 3 && m_pGMain->rankHaveToGoStar - m_pGMain->rankTraveledStar <= 0) {
		m_pGMain->m_dwGameStatus = GAMECLEAR;
	}
	// M.S 最後の星だったらゴール(通常モードの場合)
	else if (m_pGMain->m_dwGameMode != 3 && m_pGMain->haveToGoStar - m_pGMain->traveledStar <= 0) {
		m_pGMain->m_dwGameStatus = GAMECLEAR;
	}
	// 全ての敵・武器・効果の非表示化
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // 敵の発生数のリセット	
	ResetNewGameMap();                        // M.S 変数のリセット
	m_pGMain->transparentSwitch = true;       // M.S キャラの非表示
	// ステージマップの設定 ------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // コリジョンマップの生成
	int i = 0;
	m_StageMap.push_back(sm);     // 手前の星
	m_StageMap[i].m_pMesh =
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/EarthStar/centerEarthStar.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_StageMap[i].m_pBBox =
		new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax);
	m_StageMap[i].m_pBBox->m_mWorld = m_StageMap[i].m_mWorld;
	m_pColMesh->AddFbxLoad(_T("Data/Map/EarthStar/centerEarthStar.mesh"), VECTOR3(0.0f, 0.0f, 0.0f)); 
	i++;
	m_StageMap.push_back(sm);     // 奥の星
	m_StageMap[i].m_pMesh = 
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/EarthStar/centerEarthStar.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 20.0f);
	m_StageMap[i].m_pBBox = 
		new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax); 
	m_StageMap[i].m_pBBox->m_mWorld = m_StageMap[i].m_mWorld;
	m_pColMesh->AddFbxLoad(_T("Data/Map/EarthStar/centerEarthStar.mesh"), VECTOR3(0.0f, 0.0f, 20.0f)); 
	i++;
	// M.S 橋の透明度を表すため、内側と外側の架け橋に分けている
	// M.S だんだん明るく橋を表示するためオブジェクトを2組用意
	m_StageMap.push_back(sm);          // M.S 内側
	m_StageMap[i].m_nMaterialFlag = 1;
	m_StageMap[i].m_pMesh =
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/StarBridge/starBridge_Inside.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 100.0f);
	i++;
	m_StageMap.push_back(sm);          // M.S 外側
	m_StageMap[i].m_nMaterialFlag = 1;
	m_StageMap[i].m_pMesh = 
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/StarBridge/starBridge_Outside.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 100.0f);
	i++;
	m_StageMap.push_back(sm);          // M.S 内側
	m_StageMap[i].m_nMaterialFlag = 1;  
	m_StageMap[i].m_pMesh = 
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/StarBridge/starBridge_Inside.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 10.0f);
	i++;
	m_StageMap.push_back(sm);          // M.S 外側
	m_StageMap[i].m_nMaterialFlag = 1;
	m_StageMap[i].m_pMesh =
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/StarBridge/starBridge_Outside.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 10.0f);
	i++;
	// 空用  ----------------------------------------------------------
	// 空マップの設定[0]
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/GalaxyBack/galaxyBackGround100.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, -5.0f, 0.0f);
	// マップＮＯ３
	m_dwMapNo = 3;
	m_bActive = TRUE;
}
//-----------------------------------------------------------------------------
// マッププロシージャのあたり判定
//
// ・相手（主にＰＣの武器）とコリジョンマップとのあたり判定
//
//   CBaseObj*    pObj      相手のオブジェクト
//   VECTOR3* pHit		接触点の座標（出力）
//   VECTOR3* pNormal	接触点の法線ベクトル（出力）wwwwwwwwwwwwwwwwwwwww

//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal)
{
	return  Hitcheck(GetPositionVector(pObj->GetWorld()), GetPositionVector(pObj->GetWorldOld()), pHit, pNormal);
}
//-----------------------------------------------------------------------------
// マッププロシージャのあたり判定
//
// ・相手（主にＰＣの武器）とコリジョンマップとのあたり判定
//
//   VECTOR3 vNow       相手の現在位置
//   VECTOR3 vOld       相手の一つ前の位置
//   VECTOR3* vHit		接触点の座標（出力）
//   VECTOR3* vNormal	接触点の法線ベクトル（出力）
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal)
{
	BOOL  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal))
	{
		return TRUE;
	}
	else {
		return FALSE;
	}

}
//-----------------------------------------------------------------------------  // -- 2020.12.11
// マッププロシージャのあたり判定
//
// ・相手（主にＰＣの武器）の球とコリジョンマップとのあたり判定
//
//   VECTOR3 vNow       相手の現在のオブジェクト中心位置
//   VECTOR3 vOld       相手の一つ前のオブジェクト中心位置
//   float& fRadius     球の半径
//   VECTOR3 &vHit      接触時のオブジェクト中心位置の座標（出力）
//   VECTOR3 &vNormal   接触点の法線ベクトル（出力）
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal)
{
	BOOL  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal))
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}
//-----------------------------------------------------------------------------
// オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	高低差と重力を考慮した、接触判定を行う									2019.9.3
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  float fRadius          オブジェクトの半径（省略値は0.2）
//  
//  戻り値　int
//		エラー		= -1
//		面上を移動	= 1
//		着地		= 2
//		落下中		= 3
//-----------------------------------------------------------------------------
int  CMapProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0;  // -- 2019.9.3

	// 移動マップとの接触判定と移動
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, fRadius);  // -- 2019.9.3
			if (nRetMove == 1 || nRetMove == 2) break;   // 移動マップと接触したとき
		}
	}

	// 通常のマップとの接触判定と移動
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, fRadius);  // -- 2019.9.3
	}

	if (nRetMove == 1 || nRetMove == 2)  // 移動マップと接触していたとき   // -- 2019.9.3
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}
//-----------------------------------------------------------------------------
// オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	重力を考えず、接触判定を行う											2019.9.3
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  float fRadius          オブジェクトの半径（省略値は0.2）
//  
//  戻り値　int
//		接触したとき　		１
//		接触していないとき	０
//-----------------------------------------------------------------------------
int CMapProc::isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0;  // -- 2019.9.3

	// 移動マップとの接触判定と移動
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMove(*pWorld, mWorldOld, fRadius);  // -- 2019.9.3
			if (nRetMove == 1) break;
		}
	}

	// 通常のマップとの接触判定と移動
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMove(*pWorld, mWorldOld, fRadius);  // -- 2019.9.3
	}

	if (nRetMove == 1)  // 移動マップと接触していたとき     // -- 2019.9.3
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}

//M.S 方向転換線路がマップ配列に入るか、また入った場合その配列の更新
//引  数：int   h     入れるマップ配列の行
//        int   v     入れるマップ配列の列
//戻り値：bool  true  マップ配列に入る 
//              false マップ配列に入らない
bool CMapProc::SetChangeBoxJudge(int h, int v) {
	// 四つのマスの左下を[h][v]とする     二次元配列は下に行くほど、右に行くほど要素数の値が大きくなる
		if (lineMap1[h][v] == 0 && lineMap1[h - 1][v] == 0 && lineMap1[h][v + 1] == 0 && lineMap1[h - 1][v + 1] == 0) {
			lineMap1[h][v] = 2;
			lineMap1[h - 1][v] = 2;
			lineMap1[h][v + 1] = 2;
			lineMap1[h - 1][v + 1] = 2;

			return true;
		}
		return false;
}
//M.S 配置したい方向変換の進む方向と配置可能かどうか見る
//引  数：int   h     入れるマップ配列の行
//        int   v     入れるマップ配列の列
//        int   oldH  一番新しく配置した線路の現在地(行)
//        int   oldV  一番新しく配置した線路の現在地(列)
//戻り値：int         線路配置後に向かう方向
int CMapProc::GetChangeNum(int h,int v,int oldH,int oldV) {
	// aboutArrow 1:上 2:右 3:下 4:左
	// changeNum  1:上 2:右 3:下 4:左
	if (h == oldH - 1 && v == oldV) {           // カーソルと前の位置の関係
		aboutArrow = 1;               // 上移動後右へ方向転換
	   return 2;
	}
	else if (h == oldH - 1 && v == oldV - 1) {
		aboutArrow = 1;                // 上移動後左へ方向転換
		return 4;
	}
	else if (h == oldH + 2 && v == oldV) {
		aboutArrow = 3;                // 下移動後右へ方向転換
		return 2;
	}
	else if (h == oldH + 2 && v == oldV - 1) {
		aboutArrow = 3;                // 下移動後左へ方向転換
		return 4;
	}
	else if (h == oldH && v == oldV + 1) {
		aboutArrow = 2;                // 右移動後上へ方向転換
		return 1;
	}
	else if (h == oldH + 1 && v == oldV + 1) {
		aboutArrow = 2;                // 右移動後下へ方向転換
		return 3;
	}
	else if (h == oldH && v == oldV - 2) {
		aboutArrow = 4;                // 左移動後上へ方向転換
		return 1;
	}
	else if (h == oldH + 1 && v == oldV - 2){
		aboutArrow = 4;                // 左移動後下へ方向転換
		return 3;
    }
	return 9;
}
//M.S 方向転換線路配置時のプレイヤー現在地の更新
//引  数：int   h     入れるマップ配列の行
//        int   v     入れるマップ配列の列
//        int   oldH  一番新しく配置した線路の現在地(行)
//        int   oldV  一番新しく配置した線路の現在地(列)
//戻り値：なし
void CMapProc::UpadateOldHV(int oldH, int oldV,int h, int v) {
	// aboutArrou 1:上 2:右 3:下 4:左
	// changeNum  1:上 2:右 3:下 4:左
	switch (aboutArrow) {
	case 1:  // 上
		if (changeNum == 2) {
			this->oldH = h - 1;
			this->oldV = v + 1;
		}
		else if (changeNum == 4) {
			this->oldH = h - 1;
			this->oldV = v;
		}
		break;
	case 3:   // 下
		if (changeNum == 2) {
			this->oldH = h;
			this->oldV = v + 1;
		}
		else if (changeNum == 4) {
			this->oldH = h;
			this->oldV = v;
		}
		break;
	case 2:  //右
		if (changeNum == 1) {
			this->oldH = h - 1;
			this->oldV = v + 1;
		}
		else if (changeNum == 3) {
			this->oldH = h;
			this->oldV = v + 1;
		}
		break;
	case 4:
		if (changeNum == 1) {
			this->oldH = h - 1;
			this->oldV = v;
		}
		else if (changeNum == 3) {
			this->oldH = h;
			this->oldV = v;
		}
		break;		
	}	
}
//M.S 人オブジェクトの回転関数
//引  数：MATRIX4X4 old   前回の回転を戻す回転マトリクス
//        MATRIX4X4 mYaw  今回の回転マトリクス
//戻り値：なし
void CMapProc::MapManRotate(MATRIX4X4 old, MATRIX4X4 mYaw){
	// 各人オブジェクトの現在の配置数の取得
	// 6より大きければ6、小さければ、manNumの数字を入れる
	if (m_pGMain->m_pEnmProc->m_pEnmGolemProc->manNum > 6) { // higiMan
		arrayHNum = 6;
	}
	else {
		arrayHNum = m_pGMain->m_pEnmProc->m_pEnmGolemProc->manNum;
	}
	if (m_pGMain->m_pEnmProc->m_pEnmRSProc->manNum > 6) {    // middleMan	
		arrayMNum = 6;
	}
	else {
		arrayMNum = m_pGMain->m_pEnmProc->m_pEnmRSProc->manNum;
	}
	if (m_pGMain->m_pEnmProc->m_pEnmBdProc->manNum > 6) {     // lowMan
		arrayLNum = 6;
	}
	else {
		arrayLNum = m_pGMain->m_pEnmProc->m_pEnmBdProc->manNum;
	}
	// 人オブジェクトの回転
	for (int i = 0; i < arrayHNum; i++) {  // higiMan	
		MATRIX4X4 manWorld = m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetWorld(i) * old;
		manWorld = manWorld * mYaw;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->SetWorld(manWorld, i);
	}

	for (int i = 0; i < arrayMNum; i++) {  // middleMan	
		MATRIX4X4 manWorld = m_pGMain->m_pEnmProc->m_pEnmRSProc->GetWorld(i) * old;
		manWorld = manWorld * mYaw;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->SetWorld(manWorld, i);
	}

	for (int i = 0; i < arrayLNum; i++) {  // lowMan
		MATRIX4X4 manWorld = m_pGMain->m_pEnmProc->m_pEnmBdProc->GetWorld(i) * old;
		manWorld = manWorld * mYaw;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->SetWorld(manWorld, i);
	}

}
//M.S バウンディングボックスの回転関数
//引  数：MATRIX4X4 old   前回の回転を戻す回転マトリクス
//        MATRIX4X4 mYaw  今回の回転マトリクス
//戻り値：なし
void CMapProc::MapBBoxRotate(MATRIX4X4 old, MATRIX4X4 mYaw){
	// 各面の正面判定BBoxの回転   
	for (int num = 0; num < 6; num++) {
		// ワールドマトリックスに今の回転をかける
		m_pBBoxPosition[num]->m_mWorld = m_pBBoxPosition[num]->m_mWorld * old;
		// ワールドマトリックスに今の回転をかける
		m_pBBoxPosition[num]->m_mWorld = m_pBBoxPosition[num]->m_mWorld * mYaw;
	}
	// 各面の上下左右判定BBoxの回転   初期位置:正面  
	for (int num = 0; num < 4; num++) {
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow1[num]->m_mWorld = m_pBBoxArrow1[num]->m_mWorld * old;
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow1[num]->m_mWorld = m_pBBoxArrow1[num]->m_mWorld * mYaw;
	}
	// 初期位置:上
	for (int num = 0; num < 4; num++) {
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow2[num]->m_mWorld = m_pBBoxArrow2[num]->m_mWorld * old;
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow2[num]->m_mWorld = m_pBBoxArrow2[num]->m_mWorld * mYaw;
	}
	// 初期位置:裏
	for (int num = 0; num < 4; num++) {
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow3[num]->m_mWorld = m_pBBoxArrow3[num]->m_mWorld * old;
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow3[num]->m_mWorld = m_pBBoxArrow3[num]->m_mWorld * mYaw;
	}
	// 初期位置:下
	for (int num = 0; num < 4; num++) {
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow4[num]->m_mWorld = m_pBBoxArrow4[num]->m_mWorld * old;
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow4[num]->m_mWorld = m_pBBoxArrow4[num]->m_mWorld * mYaw;
	}
	// 初期位置:右
	for (int num = 0; num < 4; num++) {
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow5[num]->m_mWorld = m_pBBoxArrow5[num]->m_mWorld * old;
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow5[num]->m_mWorld = m_pBBoxArrow5[num]->m_mWorld * mYaw;
	}
	// 初期位置:左
	for (int num = 0; num < 4; num++) {
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow6[num]->m_mWorld = m_pBBoxArrow6[num]->m_mWorld * old;
		// ワールドマトリックスに今の回転をかける
		m_pBBoxArrow6[num]->m_mWorld = m_pBBoxArrow6[num]->m_mWorld * mYaw;
	}

	for (int i = 0; i < trainNumSt; i++) {  // 縦線路
		TrainLST->m_pTLSObjArray[i]->m_mWorld = TrainLST->m_pTLSObjArray[i]->m_mWorld * old;
		TrainLST->m_pTLSObjArray[i]->m_mWorld = TrainLST->m_pTLSObjArray[i]->m_mWorld * mYaw;
		TrainLST->m_pTLSObjArray[i]->GridWorld = TrainLST->m_pTLSObjArray[i]->GridWorld * old;
		TrainLST->m_pTLSObjArray[i]->GridWorld = TrainLST->m_pTLSObjArray[i]->GridWorld * mYaw;
	}
	for (int i = 0; i < trainNumSd; i++) {  //横線路
		TrainLSD->m_pTLSDObjArray[i]->m_mWorld = TrainLSD->m_pTLSDObjArray[i]->m_mWorld * old;
		TrainLSD->m_pTLSDObjArray[i]->m_mWorld = TrainLSD->m_pTLSDObjArray[i]->m_mWorld * mYaw;
		TrainLSD->m_pTLSDObjArray[i]->GridWorld = TrainLSD->m_pTLSDObjArray[i]->GridWorld * old;
		TrainLSD->m_pTLSDObjArray[i]->GridWorld = TrainLSD->m_pTLSDObjArray[i]->GridWorld * mYaw;
	}
	for (int i = 0; i < trainNumCg; i++) {  // 方向変更ブロック
		TrainLChange->m_pTCGObjArray[i]->m_mWorld = TrainLChange->m_pTCGObjArray[i]->m_mWorld * old;
		TrainLChange->m_pTCGObjArray[i]->m_mWorld = TrainLChange->m_pTCGObjArray[i]->m_mWorld * mYaw;
		TrainLChange->m_pTCGObjArray[i]->GridWorld = TrainLChange->m_pTCGObjArray[i]->GridWorld * old;
		TrainLChange->m_pTCGObjArray[i]->GridWorld = TrainLChange->m_pTCGObjArray[i]->GridWorld * mYaw;
	}
	for (int i = 0; i < trainNumSta; i++) {  // 駅
		TrainLStation->m_pTLSTAObjArray[i]->m_mWorld = TrainLStation->m_pTLSTAObjArray[i]->m_mWorld * old;
		TrainLStation->m_pTLSTAObjArray[i]->m_mWorld = TrainLStation->m_pTLSTAObjArray[i]->m_mWorld * mYaw;
		TrainLStation->m_pTLSTAObjArray[i]->GridWorld = TrainLStation->m_pTLSTAObjArray[i]->GridWorld * old;
		TrainLStation->m_pTLSTAObjArray[i]->GridWorld = TrainLStation->m_pTLSTAObjArray[i]->GridWorld * mYaw;
	}
}
//M.S 星回転時に星に乗っているオブジェクトの回転を行う
//    前の回転に-をかけて計算後、今の回転をかけて行っている
//引  数：MATRIX4X4 old   前回の回転を戻す回転マトリクス
//        MATRIX4X4 mYaw  今回の回転マトリクス
//戻り値：なし
void CMapProc::MapPcRotate(MATRIX4X4 old, MATRIX4X4 mYaw) {
	rotateProcessDoneFlag = false;
	// 人オブジェクトの回転
	MapManRotate(old, mYaw);
	// プレイキャラの回転
	MATRIX4X4 mPcWorld = m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld()* old;
	mPcWorld = mPcWorld * mYaw;               // 回転後の行列を掛ける
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(mPcWorld);
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(mPcWorld);
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetPosUp(VECTOR3(0, 0, 0));
	// スタート位置のオブジェクトの回転
	MATRIX4X4 startWorld = m_StageMap[1].m_mWorld * old;
	m_StageMap[1].m_mWorld = startWorld * mYaw;
	// BBoxの回転
	MapBBoxRotate(old, mYaw);
	mMapWorldOld = m_StageMap[0].m_mWorld;
	rotateProcessDoneFlag = true;

}
//M.S マップ配列記録用の関数
//引  数：int oldRotateSurface   配列を記録する面の数字
//戻り値：なし
void CMapProc::lineMapSet(int oldRotateSurface) {
	// 先に操作マップを書き換えないようにする
	if (setOk == false) {
		int mapBuf[10][10] = { 0 };
		setOk = true;
		//bufに今の操作面マップの配列を入れる
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				mapBuf[h][v] = lineMap1[h][v];
			}
		}
		// 今の面の配列を記録する
		switch (oldRotateSurface) {
		case 0:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf1[h][v] = mapBuf[h][v];
				}
			}
			break;
		case 1:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf2[h][v] = mapBuf[h][v];
				}
			}
			break;
		case 2:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf3[h][v] = mapBuf[h][v];
				}
			}
			break;
		case 3:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf4[h][v] = mapBuf[h][v];
				}
			}
			break;
		case 4:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf5[h][v] = mapBuf[h][v];
  				}
			}
			break;
		case 5:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf6[h][v] = mapBuf[h][v];
				}
			}
			break;
		}
	}
}
//M.S 新しい面のマップを読み込む
//引  数：int rotateSurface   配列を読み込む面の数字
//戻り値：なし
void CMapProc::lineMapNew(int rotateSurface) {
	if (setOk == true) {
		setOk = false;
		int mapBuf[10][10] = { 0 };
		switch (rotateSurface) {
		case 0:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf1[h][v];
				}
			}
			break;
		case 1:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf2[h][v];
				}
			}
			break;
		case 2:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf3[h][v];
				}
			}
			break;
		case 3:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf4[h][v];
				}
			}
			break;
		case 4:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf5[h][v];
				}
			}
			break;
		case 5:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf6[h][v];
				}
			}
			break;
		}
		// 操作面配列にbufを入れる
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMap1[h][v] = mapBuf[h][v];
			}
		}
	}	
}
//M.S BBoxを使用して正面の面を調べる関数
//引  数：int   bBoxArrayNum   調べるBBox(面)の数字
//戻り値：bool  true           レイとBBoxが当たった
//              false          レイとBBoxが当たっていない
bool CMapProc::SearchFinalPlacementSurface(int bBoxArrayNum) {
	return m_pBBoxPosition[bBoxArrayNum]->OBBCollisionLay(back, front, &mHit, &mNor);
}
//M.S 最後に配置操作したマップ面の保存用関数
//引  数：なし
//戻り値：int   正面にある面の数字
//              どこの面も正面にない場合、10
int CMapProc::SearchFinalPlacementSurface() {
	for (int nowPlacement = 0;  nowPlacement < 6; nowPlacement++) {
		// レイを飛ばして正面の面を調べる
		if (SearchFinalPlacementSurface(nowPlacement) == true) {
			return nowPlacement;
		}
	}
	return 10;
}
//M.S 次の面への配置になる時の配置位置の管理
//引  数：bool onlyArrowJudgeFlag   true、配置判断のみ false、配置処理も行う
//戻り値：bool                      true、配置可能     false、配置不可
bool CMapProc::AllowEndPlacement(bool onlyArrowJudgeFlag) {
	// 操作マップの外側からつないだ場合
	// permissionH,permissionVに配置できる位置を入れて、カーソルの位置と比べる
	newSurfacePlacement = false;  // 配置可能判定newSurfacePlacementの初期化
	if (oldH == 0 && LineChangeFlag == 1) {
		switch (surfaceMap) {
		case 0:
			if (PlacementSurfaceNum == 1) {
				permissionH = 9;
				permissionV = oldV;
			}
			break;
		case 1:
			if (PlacementSurfaceNum == 2) {
				permissionH = 9;
				permissionV = oldV;
			}
			break;
		case 2:
			if (PlacementSurfaceNum == 3) {
				permissionH = 9;
				permissionV = oldV;
			}
			break;
		case 3:
			if (PlacementSurfaceNum == 0) {
				permissionH = 9;
				permissionV = oldV;
			}
			else if (PlacementSurfaceNum == 4) {
				permissionH = 9 - oldV;
				permissionV = 9;
				LineChangeFlag = 4;
			}
			else if (PlacementSurfaceNum == 5) {
				permissionH = oldV;
				permissionV = 0;
				LineChangeFlag = 2;
			}
			break;
		}
	}// プレイキャラが下端にいて、移動方向が下だったら
	else if (oldH == 9 && LineChangeFlag == 3) {
		switch (surfaceMap) {
		case 0:
			if (PlacementSurfaceNum == 3) {
				permissionH = 0;
				permissionV = oldV;
			}
			break;
		case 1:
			if (PlacementSurfaceNum == 0) {
				permissionH = 0;
				permissionV = oldV;
			}
			else if (PlacementSurfaceNum == 4) {
				permissionH = oldV;
				permissionV = 9;
				LineChangeFlag = 4;
			}
			else if (PlacementSurfaceNum == 5) {
				permissionH = 9 - oldV;
				permissionV = 0;
				LineChangeFlag = 2;
			}
			break;
		case 2:
			if (PlacementSurfaceNum == 1) {
				permissionH = 0;
				permissionV = oldV;
			}
			break;
		case 3:
			if (PlacementSurfaceNum == 2) {
				permissionH = 0;
				permissionV = oldV;
			}
			break;
		}
	}// プレイキャラが左端にいて、移動方向が左だったら
	else if (oldV == 0 && LineChangeFlag == 4) {
		switch (surfaceMap) {
		case 2:
			if (PlacementSurfaceNum == 5) {
				permissionH = 9 - oldH;
				permissionV = 0;
				LineChangeFlag = 2;
			}
			break;
		case 0:
			if (PlacementSurfaceNum == 4) {
				permissionH = oldH;
				permissionV = 9;
			}
			break;
		case 5:
			if (PlacementSurfaceNum == 0) {
				permissionH = oldH;
				permissionV = 9;
			}
			else if (PlacementSurfaceNum == 1) {
				permissionH = 9;
				permissionV = 9 - oldH;
				LineChangeFlag = 1;
			}
			else if (PlacementSurfaceNum == 2) {
				permissionH = 9 - oldH;
				permissionV = 0;
				LineChangeFlag = 2;
			}
			else if (PlacementSurfaceNum == 3) {
				permissionH = 0;
				permissionV = oldH;
				LineChangeFlag = 3;
			}
		}
	}// プレイキャラが右端にいて、移動方向が右だったら
	else if (oldV == 9 && LineChangeFlag == 2) {
		switch (surfaceMap) {
		case 2:
			if (PlacementSurfaceNum == 4) {
				permissionH = 9 - oldH;
				permissionV = 9;
				LineChangeFlag = 4;
			}
			break;
		case 0:
			if (PlacementSurfaceNum == 5) {
				permissionH = oldH;
				permissionV = 0;
			}
			break;
		case 4:
			if (PlacementSurfaceNum == 0) {
				permissionH = oldH;
				permissionV = 0;
			}
			else if (PlacementSurfaceNum == 1) {
				permissionH = 9;
				permissionV = oldH;
				LineChangeFlag = 1;
			}
			else if (PlacementSurfaceNum == 2) {
				permissionH = 9 - oldH;
				permissionV = 9;
				LineChangeFlag = 4;
			}
			else if (PlacementSurfaceNum == 3) {     
				permissionH = 0;
				permissionV = 9 - oldH;
				LineChangeFlag = 3;
			}
		}
	}
	if (permissionH == horiRotate && permissionV == verRotate) {
		if (onlyArrowJudgeFlag == false) {    // ジャッジのみかどうか
			typeChangeNum = 1;                // 直線線路のみの配置
			newSurfacePlacement = true;       // 新しい面に配置物置いてよい
			return true;
		}
		else {
			return true;
		}
	}
	return false;
}
//M.S (配置されているかなどを考えず)位置的に配置できるか判断する関数
//引  数：なし
//戻り値：bool     true、配置可能   false、配置不可
bool CMapProc::ArrowPlacementPos() {
	bool changeLineArrow = false;
	// 直線線路か駅の場合かどうか
	if (ChangeButton != 1) {
		// 端の判定かどうか
		if (AllowEndPlacement(true) == true) {
			return true;
		}
		// 進んでいる方向などから配置できるかどうか判断
		switch (LineChangeFlag) {
		case 0:
		case 1:
			if (horiRotate == oldH - 1 && verRotate == oldV) {
				return true;
			}
			break;
		case 2:
			if (horiRotate == oldH && verRotate == oldV + 1) {
				return true;
			}
			break;
		case 3:
			if (horiRotate == oldH + 1 && verRotate == oldV) {
				return true;
			}
			break;
		case 4:
			if (horiRotate == oldH && verRotate == oldV - 1) {
				return true;
			}
		}
	}
	else {
		switch (LineChangeFlag) {
		case 1:
			if (horiRotate == oldH - 1 && verRotate == oldV) {           // カーソルと前の位置の関係
				changeLineArrow = true;                   // 上移動後右へ方向転換
			}
			else if (horiRotate == oldH - 1 && verRotate == oldV - 1) {
				changeLineArrow = true;                // 上移動後左へ方向転換
			}
			break;
		case 3:
			if (horiRotate == oldH + 2 && verRotate == oldV) {
				changeLineArrow = true;                // 下移動後右へ方向転換
			}
			else if (horiRotate == oldH + 2 && verRotate == oldV - 1) {
				changeLineArrow = true;                // 下移動後左へ方向転換
			}
			break;
		case 2:
			if (horiRotate == oldH && verRotate == oldV + 1) {
				changeLineArrow = true;                // 右移動後上へ方向転換
			}
			else if (horiRotate == oldH + 1 && verRotate == oldV + 1) {
				changeLineArrow = true;                // 右移動後下へ方向転換
			}
			break;
		case 4:
			if (horiRotate == oldH && verRotate == oldV - 2) {
				changeLineArrow = true;                // 左移動後上へ方向転換
			}
			else if (horiRotate == oldH + 1 && verRotate == oldV - 2) {
				changeLineArrow = true;               // 左移動後下へ方向転換
			}
		}
	}
	if (changeLineArrow == true) {
		if (lineMap1[horiRotate][verRotate] == 0 
			&& lineMap1[horiRotate - 1][verRotate] == 0 
			&& lineMap1[horiRotate][verRotate + 1] == 0 
			&& lineMap1[horiRotate - 1][verRotate + 1] == 0) {
			return true;
		}
	}
	return false;
}
//M.S 星の動的配置表示とエフェクト
//引  数：なし
//戻り値：なし
void CMapProc::BornStarEffect() {
	int finishFlag = 0;
	bool breakFlag = false;
	int effectPlayWaitTime = 30;
	int moveStarTime = 68;
	if (starObjArrayNum < m_StageMap.size()) {  // 星の数エフェクトを行う
		if (saveHori < 5) {
			if (saveVer < 5) {
				if (mapStarArray[saveHori][saveVer] == 1) {
					// 5.0fの変え方で幅が変わる // -〇の増減でモデルが左右に動く
					float starSetX = 5.0f*saveVer + 10.0f*saveVer;        
					// +〇を増やすと上にモデルが動く  // -5.0の変え方で幅が変わる
					float starSetZ = -5.0f*saveHori - 10.0f*saveHori;     
					// waitTimeがeffectPlayWaitTime以上になり、最初の処理だったら
					if (waitTime >= effectPlayWaitTime && starEffectOrder == 0) {   
						VECTOR3 starEffectPos = VECTOR3(starSetX, 20.0f, starSetZ);
						// エフェクトの表示
						m_pGMain->m_pEffectProc->m_pBillStarProc->Start(starEffectPos);
						// 最初の処理から次(1)の処理へ
						starEffectOrder = 1;
						// 星発生音
						m_pGMain->bornStarSound->Play();
					}
					// waitTimeがmoveStarTime以上になり、次(1)の処理だったら
					else if (waitTime >= moveStarTime && starEffectOrder == 1) {
						// 星を移動させる
						m_StageMap[starObjArrayNum].m_mWorld = XMMatrixTranslation(starSetX, 0.0f, starSetZ);
						m_StageMap[starObjArrayNum].m_pBBox->m_mWorld = m_StageMap[starObjArrayNum].m_mWorld;
						// 処理完了した星数をたす
						starObjArrayNum++;
						// 処理の順番変数を初期化
						starEffectOrder = 0;
						// waitTimeを初期化
						waitTime = 0;
						//次の配列を見るようにsaveVerをたす
						saveVer++;
						// 縦5、横5の配列のなのでsaveVerが5になったら次の行を見るようにする
						if (saveVer % 5 <= 0) {
							saveHori++;
							saveVer = 0;
						}
					}
					waitTime++;
				}
				else {
					// 星がなかった場合の処理 次の配列を見るようにする
					saveVer++;
					if (saveVer % 5 <= 0) {
						saveHori++;
						saveVer = 0;
					}
					waitTime++;
				}
			}
		}
	}
}
//M.S 星の架け橋をかけて、ランキングモード以外ならばセーブをする関数
//引  数：VECTOR3 longCursol    直線移動後の座標 
//        VECTOR3 shortCursol   直線移動前の座標
//戻り値：なし
void CMapProc::BuiltStarBridge(VECTOR3 longCursol, VECTOR3 shortCursol) {
	CDirectInput* pDI = m_pGMain->m_pDI;
	int builtTime = 50;
	// ボタンを離したら星の架け橋フラグの初期化
	if (pDI->CheckMouse(KD_UTRG, DIM_LBUTTON)) {
		starBridgeInputFlag = false;
		NearStarCol = false;
		frontStarCol = false;
	}
	// クリックしたらstarBridgeinputFlagをtrue
	if (pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
		starBridgeInputFlag = true;
	}
	// クリックしていて前方と後方の星と接触していたらフラグをtrueにする
	if (starBridgeInputFlag == true && NearStarCol == false && frontStarCol == false) {
		if (m_StageMap[0].m_pBBox->OBBCollisionLay(longCursol, shortCursol, &mHit, &mNor) == true) {
			NearStarCol = true;
		}
	}
	if (starBridgeInputFlag == true && NearStarCol == true) {
		if (m_StageMap[1].m_pBBox->OBBCollisionLay(longCursol, shortCursol, &mHit, &mNor)) {
			frontStarCol = true;
		}
	}
	// 二つの星のフラグがtrueだったらstarBridgePermissionをtrue
	if (NearStarCol == true && frontStarCol == true) {
		starBridgePermission = true;
	}
	if (starBridgePermission == true) {
     // starBridgeLitingTimeの待ち時間が終わり、全ての架け橋がかかっていなかったら
		if (starBridgeLitingTime % builtTime <= 0 && starBridgePosNum <= 4) {
			// starBridgePosNum分星の架け橋を移動させる
			m_StageMap[2].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, starBridgePosNum * 2.5f);
			m_StageMap[3].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, starBridgePosNum * 2.5f);
			m_StageMap[4].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 10 + starBridgePosNum * 2.5f);
			m_StageMap[5].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 10 + starBridgePosNum * 2.5f);
			starBridgePosNum++;
			// 効果音
			m_pGMain->bornStarSound->Play();
		}
		// 星の架け橋がかけ終わったら
		else if (starBridgePosNum == 5) {
			// 星の架け橋フラグをfalse
			starBridgeInputFlag = false;
			starBridgePermission = false;
			NearStarCol = false;
			frontStarCol = false;
			starBridgePosNum++;
			// セーブフラグをtrue
			m_pGMain->m_pBackForeProc->builtStarBridge = true;
			// ランクモード以外ならばセーブをする
			if (m_pGMain->m_dwGameMode != 3) {
				m_pGMain->FileWrite();
			}
		}
		starBridgeLitingTime++;
	}
}
//M.S 星の回転をする関数
//引  数：なし
//戻り値：なし
void CMapProc::RotateStar() {
	CDirectInput* pDI = m_pGMain->m_pDI;
	//星の回転のプレイヤー操作
	if (pDI->CheckMouse(KD_TRG, DIM_RBUTTON) && m_pGMain->m_pPcProc->rotateOkFlag == true
		&& rotateProcessDoneFlag == true && m_pGMain->m_pMapProc->doneManPlacement == true
		&& m_pGMain->m_pEnmProc->rotateOkFlagMan == true && starRotateSwitch == 0) {
		beforePoint = pDI->GetMousePos(); // ドラッグ（星の回転）をされたら、カーソルが触れた位置の取得
		starRotateSwitch = 1;
	}
	if (pDI->CheckMouse(KD_UTRG, DIM_RBUTTON) && starRotateSwitch == 1) {
		afterPoint = pDI->GetMousePos(); // ドラッグ（星の回転）をされたら、カーソルが離れた位置の取得
		starRotateSwitch = 2;
	}
	if (starRotateSwitch == 2) {
		starRotateSwitch = 3;
		resultPoint.x = afterPoint.x - beforePoint.x;    // 前の座標から今の座標を引く
		resultPoint.y = afterPoint.y - beforePoint.y;
		long absoluteX;
		long absoluteY;
		absoluteX = labs(resultPoint.x);                 // ↑の計算結果の絶対値を出す
		absoluteY = labs(resultPoint.y);
		// 回転させた方向に応じてpointArrowを足す
		if (absoluteX > absoluteY && resultPoint.x > 0) {  // →   
			pointArrow1 += 1;
			m_pGMain->rotateFlag = true;
		}
		else if (absoluteX > absoluteY && resultPoint.x < 0) {  // ←
			pointArrow2 += 1;
			m_pGMain->rotateFlag = true;
		}
		else if (absoluteX < absoluteY && resultPoint.y < 0) {  // ↑
			pointArrow3 += 1;
			m_pGMain->rotateFlag = true;
		}
		else if (absoluteX < absoluteY && resultPoint.y > 0) {   // ↓
			pointArrow4 += 1;
			m_pGMain->rotateFlag = true;
		} // ドラッグのカーソルが動いていなかったら回転させない
		else if (absoluteX == absoluteY) {
			m_pGMain->rotateFlag = false;
			starRotateSwitch = 0;
		}
	}
	linePlacementOkFlag = true;
	if (m_pGMain->rotateFlag == true) {      // 回転の操作が行われたら		
		MATRIX4X4 oldZ = XMMatrixRotationZ(XMConvertToRadians(-1 * sideDegree));  // 前の回転の-のマトリックス
		// マップの位置にoldZをかけて回転を戻す
		m_StageMap[0].m_mWorld = m_StageMap[0].m_mWorld * oldZ;
		sideDegree = 0.0f;                   // 回転角度の初期化
		// 横回転を出す  pointArrow2が大きい場合+90度、pointArrow1が大きい場合-90度
		pointArrowNum1 = pointArrow2 - pointArrow1;
		if (pointArrowNum1 > 0) {                           // pointArrow2が大きい場合
			for (int i = 0; pointArrowNum1 % 4 > i; i++) {  // ← 4回(360°のときは回転しない) 
				sideDegree += 90.0f;
			}
		}
		else if (0 > pointArrowNum1) {                       // → 
			for (int i = 0; pointArrowNum1 % 4 < i; i--) {  // pointArrow1が大きい場合
				sideDegree -= 90.0f;
			}
		}
		mYawZ = XMMatrixRotationZ(XMConvertToRadians(sideDegree));      // Z回転角度のマトリックス
		m_StageMap[0].m_mWorld = m_StageMap[0].m_mWorld * mYawZ;        // マップの位置に回転をかける
		MapPcRotate(oldZ, mYawZ);          // 星に配置されているオブジェクトの回転
		// 縦回転の処理
		MATRIX4X4 oldX = XMMatrixRotationX(XMConvertToRadians(-1 * heightDegree)); // 前の回転の-回転のマトリックス
		 // マップの位置にoldXをかけて回転を戻す
		m_StageMap[0].m_mWorld = m_StageMap[0].m_mWorld * oldX;
		heightDegree = 0.0f;              // 回転角度の初期化
		// pointArrow3の方が大きい場合+90度、pointArrow4が大きい場合-90度
		pointArrowNum2 = pointArrow3 - pointArrow4;
		if (pointArrowNum2 > 0) {
			for (int i = 0; pointArrowNum2 % 4 > i; i++) {   // ↑  4回(360°のときは回転しない) 
				heightDegree += 90.0f;
			}
		}
		else if (0 > pointArrowNum2) {                      // ↓
			for (int i = 0; pointArrowNum2 % 4 < i; i--) {  // pointArrow4の方が大きい場合
				heightDegree -= 90.0f;
			}
		}
		mYawX = XMMatrixRotationX(XMConvertToRadians(heightDegree));    // X回転角度のマトリックス
		m_StageMap[0].m_mWorld = m_StageMap[0].m_mWorld * mYawX;        // マップの位置に回転をかける
		MapPcRotate(oldX, mYawX);       // 星に配置されているオブジェクトの回転
		rotateFinish = true;            // 回転フラグの初期化
		starRotateSwitch = 0;
		SaveRotateSurfaceFlag = true;
		m_pGMain->rotateFlag = false;
	}
}
//M.S 現在の操作面マップを調べる
//引  数：なし
//戻り値：なし
void CMapProc::JudgeSurface() {
	for (int surfaceArrayNum = 0; surfaceArrayNum < 6; surfaceArrayNum++) {
		if (SearchFinalPlacementSurface(surfaceArrayNum) == true) {
			// レイと当たったBBoxがある面を保存
			surfaceMapLineJudge = surfaceArrayNum;
			if (rotateFinish == true) {  
				// 回転していたらsurfaceMapに調べた面の数を入れる、フラグもfalse
				surfaceMap = surfaceArrayNum;
				rotateFinish = false;
			}
		}
	}
}
//M.S 線路のキラキラエフェクトの表示
//引  数：なし
//戻り値：なし
void CMapProc::GlitterEffect() {
	// 線路キラキラエフェクトの表示
	float withinRange = 3.0f;  // エフェクト表示範囲
	// 縦線路
	for (int i = 0; i < trainNumSt; i++) {
		// プレイキャラと線路の位置の取得
		VECTOR3 linePos = GetPositionVector(TrainLST->m_pTLSObjArray[i]->GridWorld);
		VECTOR3 pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		float distance = magnitude(linePos - pcPos);  // 線路とプレイキャラの距離計算
		// 線路が配置面にある、またはプレイキャラと同じ面でdistanceがwithinRange以内だったら
		// エフェクトを出す
		if (TrainLST->m_pTLSObjArray[i]->stLineMap == surfaceMapLineJudge
			|| (TrainLST->m_pTLSObjArray[i]->stLineMap == m_pGMain->m_pPcProc->NewSurfaceNum
				&& distance <= withinRange)) {
			// エフェクトの発生
			m_pGMain->m_pEffectProc->m_pBillProc->Start(linePos);
		}
	}
	// 横線路
	for (int i = 0; i < trainNumSd; i++) {
		// プレイキャラと線路の位置の取得
		VECTOR3 linePos = GetPositionVector(TrainLSD->m_pTLSDObjArray[i]->GridWorld);
		VECTOR3 pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		float distance = magnitude(linePos - pcPos);  // 線路とプレイキャラの距離計算
		// 線路が配置面にあり、またはdistanceがwithinRange以内だったらエフェクトを出す
		if (TrainLSD->m_pTLSDObjArray[i]->sdLineMap == surfaceMapLineJudge
			|| (TrainLSD->m_pTLSDObjArray[i]->sdLineMap == m_pGMain->m_pPcProc->NewSurfaceNum
				&& distance <= withinRange)) {
			// エフェクトの発生
			m_pGMain->m_pEffectProc->m_pBillProc->Start(linePos);
		}
	}
	// 方向転換線路
	for (int i = 0; i < trainNumCg; i++) {
		// プレイキャラと線路の位置の取得
		VECTOR3 linePos = GetPositionVector(TrainLChange->m_pTCGObjArray[i]->GridWorld);
		VECTOR3 pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		float distance = magnitude(linePos - pcPos);  // 線路とプレイキャラの距離計算
		// 線路が配置面にあり、またはdistanceがwithinRange以内だったらエフェクトを出す
		if (TrainLChange->m_pTCGObjArray[i]->cgLineMap == surfaceMapLineJudge
			|| (TrainLChange->m_pTCGObjArray[i]->cgLineMap == m_pGMain->m_pPcProc->NewSurfaceNum
				&& distance <= withinRange)) {
			// エフェクトの発生
			m_pGMain->m_pEffectProc->m_pBillProc->Start(linePos);
		}
	}
	// 駅
	for (int i = 0; i < trainNumSta; i++) {
		// プレイキャラと線路の位置の取得
		VECTOR3 linePos = GetPositionVector(TrainLStation->m_pTLSTAObjArray[i]->GridWorld);
		VECTOR3 pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		float distance = magnitude(linePos - pcPos);  // 線路とプレイキャラの距離計算
		// 線路が配置面にあり、またはdistanceがwithinRange以内だったらエフェクトを出す
		if (TrainLStation->m_pTLSTAObjArray[i]->staLineMap == surfaceMapLineJudge
			|| (TrainLStation->m_pTLSTAObjArray[i]->staLineMap == m_pGMain->m_pPcProc->NewSurfaceNum
				&& distance <= 2.0f)) {
			// エフェクトの発生
			m_pGMain->m_pEffectProc->m_pBillProc->Start(linePos);
		}
	}
}
//M.S カーソルガイドの表示
//引  数：int h   カーソルに接触しているBBoxの行
//      ：int v   カーソルに接触しているBBoxの列
//戻り値：なし
void CMapProc::DrawCursorGuide(int h, int v) {
	VECTOR3 frontPos = VECTOR3(0.0f, 6.0f, 0.0f);
	// 星の回転の取得（北の向き）
	northNow = m_pGMain->m_pPcProc->judgeDirection(surfaceMap, frontPos, 0);
	changeButtonWithinRange = false;
	if (ChangeButton == 1) {  // 方向転換線路が選択されていた場合
		switch (northNow) {  // 星の回転に合わせてガイドを表示
		case 1:
			if (h - 1 >= 0 && v + 1 <= 9) {  // 無回転
				// カーソルと当たっているマス目の表示
				m_pBBoxLine[h][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);  
				m_pBBoxLine[h - 1][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h][v + 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h - 1][v + 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				changeButtonWithinRange = true;
			}break;
		case 2:
			// カーソルと当たっているマス目の表示
			if (h + 1 <= 9 && v + 1 <= 9) { //+90度
				m_pBBoxLine[h][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);  
				m_pBBoxLine[h + 1][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h][v + 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h + 1][v + 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				changeButtonWithinRange = true;
			}break;
		case 3:
			if (h + 1 <= 9 && v - 1 >= 0) { //+180度
				 // カーソルと当たっているマス目の表示
				m_pBBoxLine[h][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt); 
				m_pBBoxLine[h][v - 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h + 1][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h + 1][v - 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				changeButtonWithinRange = true;
			}break;
		case 4:
			if (h - 1 >= 0 && v - 1 >= 0) { //+270度
				// カーソルと当たっているマス目の表示
				m_pBBoxLine[h][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);  
				m_pBBoxLine[h][v - 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h - 1][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h - 1][v - 1]->
                    Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				changeButtonWithinRange = true;
			}
		}

	}
	else { // 方向転換線路以外が選択されていた場合 そのままカーソルの場所を表示
		m_pBBoxLine[h][v]->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt); 
	}
	// 星の回転(面の回転)を配列マップに合わせて変換する
	switch (northNow) {
	case 1: //そのまま
		horiRotate = h;
		verRotate = v;
		break;
	case 2: // 右に90度
		horiRotate = 9 - v;
		verRotate = h;
		break;
	case 3: // 右に180度
		horiRotate = (h - 9)* -1;
		verRotate = 9 - v;
		break;
	case 4: // 右に270度
		horiRotate = v;
		verRotate = (h - 9)* -1;
		break;
	}
}
//M.S 直進線路の配置
//引  数：int h   配置する行
//        int v   配置する列
//戻り値：なし
void CMapProc::PlacementStLine(int h, int v) {
	// 初期処理ではない場合、次の面への移動の最初の処理かどうか見る
	if (LineChangeFlag != 0) {
		AllowEndPlacement(false);
	}// 初期処理
	if (LineChangeFlag == 0) {
		if (horiRotate == oldH - 1 && verRotate == oldV 
			&& lineMap1[oldH][oldV] != 0) {// 上
			m_pGMain->linePlacementSound->Play();  // 配置音
			// マップ配列の更新
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSt += 1;  // 線路の数をプラスする
			// 配置した線路の面の保存
			TrainLST->m_pTLSObjArray[trainNumSt - 1]->stLineMap = surfaceMap;  
			// オブジェクトの情報をセット
			TrainLST->Update(trainNumSt, v, h);
			LineChangeFlag = 1;  // 初期処理から上移動方向(1)に更新
			typeChangeNum = 2;   // 全ての線路を置ける
			// 現在地を更新
			oldH = horiRotate;
			oldV = verRotate;
			linePlacementOkFlag = false;
		}
	}
	//縦線路
	else if (LineChangeFlag == 1) {   //上
		if (horiRotate == oldH - 1 && verRotate == oldV 
			&& lineMap1[oldH][oldV] != 0 || newSurfacePlacement == true) {
			m_pGMain->linePlacementSound->Play();  // 配置音
			// マップ配列の更新
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSt += 1;  // 線路の数をプラスする
		    // 配置した線路の面の保存
			TrainLST->m_pTLSObjArray[trainNumSt - 1]->stLineMap = surfaceMap;
			// オブジェクトの情報をセット
			TrainLST->Update(trainNumSt, v, h);
			typeChangeNum = 2;  // 全ての線路を置ける
			// 現在地を更新
			oldH = horiRotate;
			oldV = verRotate;
			newSurfacePlacement = false;
			PlacementSurfaceNum = SearchFinalPlacementSurface(); // 最後に操作した面の数の保存
			linePlacementOkFlag = false;
		}
	}
	else if (LineChangeFlag == 3) {             // 下
		if (horiRotate == oldH + 1 && verRotate == oldV 
			&& lineMap1[oldH][oldV] != 0 || newSurfacePlacement == true) {
			m_pGMain->linePlacementSound->Play();  // 配置音
			// マップ配列の更新
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSt += 1; // 線路の数をプラスする
			// 配置した線路の面の保存
			TrainLST->m_pTLSObjArray[trainNumSt - 1]->stLineMap = surfaceMap;
			// オブジェクトの情報をセット
			TrainLST->Update(trainNumSt, v, h);
			typeChangeNum = 2;   // 全ての線路を置ける
			oldH = horiRotate;
			oldV = verRotate;
			newSurfacePlacement = false;
			PlacementSurfaceNum = SearchFinalPlacementSurface(); // 最後に操作した面の数の保存
			linePlacementOkFlag = false;
		}
	}// 横線路
	else if (LineChangeFlag == 2) {          //右
		if (verRotate == oldV + 1 && horiRotate == oldH 
			&& lineMap1[oldH][oldV] != 0 || newSurfacePlacement == true) {
			m_pGMain->linePlacementSound->Play(); // 配置音
			// マップ配列の更新
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSd += 1;  // 線路の数をプラスする
			// 配置した線路の面の保存
			TrainLSD->m_pTLSDObjArray[trainNumSd - 1]->sdLineMap = surfaceMap;
			// オブジェクトの情報をセット
			TrainLSD->Update(trainNumSd, v, h);
			typeChangeNum = 2;  // 全ての線路を置ける
			oldH = horiRotate;
			oldV = verRotate;
			newSurfacePlacement = false;
			PlacementSurfaceNum = SearchFinalPlacementSurface(); // 最後に操作した面の数の保存
		}
	}
	else if (LineChangeFlag == 4) {          // 左
		if (verRotate == oldV - 1 && horiRotate == oldH 
			&& lineMap1[oldH][oldV] != 0 || newSurfacePlacement == true) {
			m_pGMain->linePlacementSound->Play();  // 配置音
			// マップ配列の更新
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSd += 1;  // 線路の数をプラスする
			// 配置した線路の面の保存
			TrainLSD->m_pTLSDObjArray[trainNumSd - 1]->sdLineMap = surfaceMap;
			// オブジェクトの情報をセット
			TrainLSD->Update(trainNumSd, v, h);
			typeChangeNum = 2;  // 全ての線路を置ける
			oldH = horiRotate;
			oldV = verRotate;
			newSurfacePlacement = false;
			PlacementSurfaceNum = SearchFinalPlacementSurface(); // 最後に操作した面の数の保存
		}
	}
}
//M.S 方向転換線路の配置
//引  数：int h   配置する行
//        int v   配置する列
//戻り値：なし 
void CMapProc::PlacementCgLine(int h, int v){
// 初期処理ではない場合、次の面への移動の最初の処理かどうか見る{
	if (LineChangeFlag != 0) {
		AllowEndPlacement(false);
	}
	changeNum = GetChangeNum(horiRotate, verRotate, oldH, oldV);  // オブジェクトの位置を入れる
	// changeNum              1:上 2:右 3:下 4:左
	//  LineChangeFlag        1:上 2:右 3:下 4:左 方向に進んでいる  
	// aboutArrou             1:上 2:右 3:下 4:左
	if (typeChangeNum == 2 && changeButtonWithinRange == true 
		&& newSurfacePlacement == false && changeNum != 9) {
		// 方向切り替えブロックの配置位置に置けるかどうか&マップ配列の更新         
		bool judge = SetChangeBoxJudge(horiRotate, verRotate);     
		if (LineChangeFlag == aboutArrow) {           //進んでいる方向の確認(上)
			if (judge == true) {
				//changeNum(配置後の回転)に合わせてプレイヤーの方向を切り替える
				m_pGMain->linePlacementSound->Play();
				LineChangeFlag = changeNum;
				trainNumCg += 1;                                  // 配置線路の数を+1
				TrainLChange->Update(trainNumCg, v, h);           // 各情報を入れる
				UpadateOldHV(oldH, oldV, horiRotate, verRotate);  // 配置現在地の更新
				typeChangeNum = 1;                                // 直線線路以外配置不可
				TrainLChange->m_pTCGObjArray[trainNumCg - 1]->cgLineMap = surfaceMap;  // 配置面の保存
				PlacementSurfaceNum = SearchFinalPlacementSurface();  // 最後に操作した面の数の保存
				newSurfacePlacement = false;
			}
		}
	}
}
//M.S 駅の配置
//引  数：int h   配置する行
//        int v   配置する列
//戻り値：なし
void CMapProc::PlacementStaLine(int h, int v) {
	// 初期処理ではない場合、次の面への移動の最初の処理かどうか見る
	if (LineChangeFlag != 0) {
		AllowEndPlacement(false);
	}
	if (typeChangeNum == 2 && newSurfacePlacement == false) {
		if (LineChangeFlag == 1) {             //上
			if (horiRotate == oldH - 1 && verRotate == oldV && lineMap1[oldH][oldV] != 0) {
				m_pGMain->linePlacementSound->Play(); // 効果音
				trainNumSta += 1; // 配置線路数を+1
				// 配置した面の保存
				TrainLStation->m_pTLSTAObjArray[trainNumSta - 1]->staLineMap = surfaceMap;
				// 線路情報を入れる
				TrainLStation->Update(trainNumSta, v, h);
				// マップ配列に配置線路情報を入れる
				lineMap1[horiRotate][verRotate] = 3;
				// 全ての線路を置けるようにする
				typeChangeNum = 2;
				// 配置位置の更新
				oldH = horiRotate;
				oldV = verRotate;
				newSurfacePlacement = false;
				PlacementSurfaceNum = SearchFinalPlacementSurface(); // 最後に操作した面の数の保存
			}
		}
		else if (LineChangeFlag == 3) {             // 下
			if (horiRotate == oldH + 1 && verRotate == oldV && lineMap1[oldH][oldV] != 0) {
				m_pGMain->linePlacementSound->Play(); // 効果音
				trainNumSta += 1; // 配置線路数を+1
				// 配置した面の保存
				TrainLStation->m_pTLSTAObjArray[trainNumSta - 1]->staLineMap = surfaceMap;
				// 線路情報を入れる
				TrainLStation->Update(trainNumSta, v, h);
				// マップ配列に配置線路情報を入れる
				lineMap1[horiRotate][verRotate] = 3;
				// 全ての線路を置けるようにする
				typeChangeNum = 2;
				// 配置位置の更新
				oldH = horiRotate;
				oldV = verRotate;
				newSurfacePlacement = false;
				PlacementSurfaceNum = SearchFinalPlacementSurface(); // 最後に操作した面の数の保存
			}
		}// 横線路
		else if (LineChangeFlag == 2) {          //右
			if (verRotate == oldV + 1 && horiRotate == oldH && lineMap1[oldH][oldV] != 0) {
				m_pGMain->linePlacementSound->Play(); // 効果音
				trainNumSta += 1; // 配置線路数を+1
				// 配置した面の保存
				TrainLStation->m_pTLSTAObjArray[trainNumSta - 1]->staLineMap = surfaceMap;
				// 線路情報を入れる
				TrainLStation->Update(trainNumSta, v, h);
				// マップ配列に配置線路情報を入れる
				lineMap1[horiRotate][verRotate] = 3;
				// 全ての線路を置けるようにする
				typeChangeNum = 2;
				// 配置位置の更新
				oldH = horiRotate;
				oldV = verRotate;
				newSurfacePlacement = false;
				PlacementSurfaceNum = SearchFinalPlacementSurface(); // 最後に操作した面の数の保存
			}
		}
		else if (LineChangeFlag == 4) {          // 左
			if (verRotate == oldV - 1 && horiRotate == oldH && lineMap1[oldH][oldV] != 0) {
				m_pGMain->linePlacementSound->Play(); // 効果音
				trainNumSta += 1; // 配置線路数を+1
				// 配置した面の保存
				TrainLStation->m_pTLSTAObjArray[trainNumSta - 1]->staLineMap = surfaceMap;
				// 線路情報を入れる
				TrainLStation->Update(trainNumSta, v, h);
				// マップ配列に配置線路情報を入れる
				lineMap1[horiRotate][verRotate] = 3;
				// 全ての線路を置けるようにする
				typeChangeNum = 2;
				// 配置位置の更新
				oldH = horiRotate;
				oldV = verRotate;
				newSurfacePlacement = false;
				PlacementSurfaceNum = SearchFinalPlacementSurface(); // 最後に操作した面の数の保存
			}
		}
	}
}
//-----------------------------------------------------------------------------
//
// マッププロシージャの更新
//
//-----------------------------------------------------------------------------
void CMapProc::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	// カーソル位置の取得
	POINT point = pDI->GetMousePos();
	m_pGMain->cursolX = point.x;
	m_pGMain->cursolY = point.y;
	// Z座標の再定義はいらない
	VECTOR3 longCursol = XMVector3Unproject(VECTOR3(m_pGMain->cursolX, m_pGMain->cursolY, 1.0f), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		m_pGMain->m_mProj, m_pGMain->m_mView, XMMatrixIdentity());  // XMMatrixIdentityは基本0でOK、斜めからの判定とかに0以外の数字を入れる
	VECTOR3 shortCursol = XMVector3Unproject(VECTOR3(m_pGMain->cursolX, m_pGMain->cursolY, 0.0f), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		m_pGMain->m_mProj, m_pGMain->m_mView, XMMatrixIdentity());  // XMMatrixIdentityは基本0でOK、斜めからの判定とかに0以外の数字を入れる
	//マップ1の処理
	if (m_dwMapNo == 1) {
		BornStarEffect();
	}
	if (m_dwMapNo == 3) {
		BuiltStarBridge(longCursol, shortCursol);
	}
	if (pDI->CheckMouse(KD_TRG, DIM_MBUTTON)) {   // 配置物選択番号の変更   0:直線線路 1:方向転換線路 2:駅
		m_pGMain->lineChangeSound->Play();
		ChangeButton = (ChangeButton + 1) % 3;
	}
	const float Right_Rotate = 90.0f;
	const float Left_Rotate = -90.0f;	
	if (m_dwMapNo == 2) {
		RotateStar();
		oldRotateSurface = surfaceMap;		
		JudgeSurface();
		// マップ面配列の保存、更新
		if (SaveRotateSurfaceFlag == true) {             // 回転スイッチをfalse	
			lineMapSet(oldRotateSurface);
			lineMapNew(surfaceMap);
			SaveRotateSurfaceFlag = false;
		}
        // 配置線路の表示
		TrainLST->RenderLine(trainNumSt, trainNumSd, trainNumCg, trainNumSta, m_pGMain);
		//繰り返し文などをでると文字は描画されなくなる	
		GlitterEffect();
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				rotateProcessDoneFlag = false;
				// 配置カーソルガイドとの当たり判定
				bool f = m_pBBoxLine[h][v]->OBBCollisionLay(longCursol, shortCursol, &mHit, &mNor);
				if (f == true) {
					DrawCursorGuide(h, v);
					if ((pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) && (lineMap1[horiRotate][verRotate] == 0) 
						&& (m_pGMain->stopOperation == false)) {						
						switch (ChangeButton) {
							//LineChangeFlag          0:初期処理
							//LineChangeFlag          1:上 2:右 3:下 4:左 方向に進んでいる
						case 0:   // 縦線路  横線路の配置
							PlacementStLine(h, v);
							break;
						case 1:   // 方向転換線路の配置
							PlacementCgLine(h, v);
							break;
						case 2:   // 駅の配置			
							PlacementStaLine(h, v);
							break;
						}
					}					
				}
			}
		}
	}
	rotateProcessDoneFlag = true;
	// 空の更新　　カメラを中心とした位置に置き、Ｙ軸回転させる
	if (m_SkyMap.size() > 0 )
	{
		MATRIX4X4 mRot;
		mRot = XMMatrixRotationY(XMConvertToRadians(0.01f));//(0.005f));
		m_SkyMap[0].m_mWorld = mRot * m_SkyMap[0].m_mWorld;
	}
	// 移動マップ更新処理
	UpdateMoveMap();
	//レンダリング
	Render();
}
// M.S
// 直線線路オブジェ(縦)に情報をセット
// 引  数：int trainNumSt 配置する直線線路(縦)の合計の数
//         int v          配置するマップ配列の列数
//         int h          配置するマップ配列の行数
// 戻り値：なし
void TrainLineStProc::Update(int trainNumSt,int v,int h) {
	// 配置する位置の変数
	float verPos  = -4.5f + 1 * v;
	float horiPos = 4.0f - h * 1;
	float yPos    = 5.05f;
	// 線路の種類の数字をm_pTLSObjArrayの配置する線路の要素に入れる
	m_pTLSObjArray[trainNumSt - 1]->SetLineNum(1);
	// 配置する位置のマトリックスを作る
	MATRIX4X4 trans = XMMatrixTranslation(verPos, yPos, horiPos);
	// 配置する線路の位置をセットする
	m_pTLSObjArray[trainNumSt - 1]->m_mWorld = trans;
	m_pTLSObjArray[trainNumSt - 1]->m_mWorldOld = trans;
	// キラキラエフェクトの位置の調整用変数
	float gridAdjust = 0.5f;
	// キラキラエフェクトの位置のセット
	m_pTLSObjArray[trainNumSt - 1]->GridWorld = XMMatrixTranslation(verPos, yPos, gridAdjust + horiPos);
}
// M.S
// 直線線路オブジェ(横)に情報をセット
// 引  数：int trainNumSt 配置する直線線路(横)の合計の数
//         int v          配置するマップ配列の列数
//         int h          配置するマップ配列の行数
// 戻り値：なし
void TrainLineSdProc::Update(int trainNumSd, int v, int h) {
	// 配置する位置の変数
	float verPos  = -4.5f + 1 * v;
	float horiPos = 4.0f - h * 1;
	float yPos = 5.05f;
	// 線路の種類の数字をm_pTLSObjArrayの配置する線路の要素に入れる
	m_pTLSDObjArray[trainNumSd - 1]->SetLineNum(1);
	// 配置する位置のマトリックスを作る
	MATRIX4X4 trans = XMMatrixTranslation(verPos, yPos, horiPos);
	// 配置する線路の位置をセットする
	m_pTLSDObjArray[trainNumSd - 1]->m_mWorld = trans;
	m_pTLSDObjArray[trainNumSd - 1]->m_mWorldOld = trans;
	// キラキラエフェクトの位置の調整用変数
	float gridAdjust = 0.5f;
	// キラキラエフェクトの位置のセット
	m_pTLSDObjArray[trainNumSd - 1]->GridWorld = XMMatrixTranslation(verPos, yPos, gridAdjust + horiPos);
}
// M.S
// 方向切り替え線路オブジェに情報をセット
// 引  数：int trainNumSt 配置する方向切り替え線路の合計の数
//         int v          配置するマップ配列の列数
//         int h          配置するマップ配列の行数
// 戻り値：無し
void TrainLineCgProc::Update(int trainNumCg, int v, int h) {
	// 配置する位置のマトリックスを作る
	MATRIX4X4 trans;
	// マップ面の回転に合わせて、同じ配列の位置でも配置する位置を変える
		switch (m_pGMain->m_pMapProc->northNow) {
		case 1: // 0度回転
			trans = XMMatrixTranslation(-4.0f + 1 * v, 5.05f, 5.0f - h * 1);
			break;
		case 2: // 右に90度回転
			trans = XMMatrixTranslation(-4.0f + 1 * v, 5.05f, 4.0f - h * 1);
			break;
		case 3: // 右に180度回転
			trans = XMMatrixTranslation(-5.0f + 1 * v, 5.05f, 4.0f - h * 1);
			break;
		case 4: // 右に270度回転
			trans = XMMatrixTranslation(-5.0f + 1 * v, 5.05f, 5.0f - h * 1);
			break;
		}
	// 線路の種類の数字をm_pTCGObjArrayの配置する線路の要素に入れる
	m_pTCGObjArray[trainNumCg - 1]->SetLineNum(2);
	// 配置する線路の位置をセットする
	m_pTCGObjArray[trainNumCg - 1]->m_mWorld = trans;
	m_pTCGObjArray[trainNumCg - 1]->m_mWorldOld = trans;
	// キラキラエフェクトの位置のセット
	m_pTCGObjArray[trainNumCg - 1]->GridWorld = trans;
}
// M.S
// 駅オブジェに情報をセット
// 引  数：int trainNumSt 配置する駅の合計の数
//         int v          配置するマップ配列の列数
//         int h          配置するマップ配列の行数
// 戻り値：無し
void TrainLineStationProc::Update(int trainNumSta, int v, int h) {
	// 配置する位置の変数
	float verPos = -4.5f + 1 * v;
	float horiPos = 4.0f - h * 1;
	float yPos = 5.05f;
	// 線路の種類の数字をm_pTLSObjArrayの配置する線路の要素に入れる
	m_pTLSTAObjArray[trainNumSta - 1]->SetLineNum(1);
	// 配置する位置のマトリックスを作る
	MATRIX4X4 trans = XMMatrixTranslation(verPos, yPos, horiPos);
	// 配置する線路の位置をセットする
	m_pTLSTAObjArray[trainNumSta - 1]->m_mWorld = trans;
	m_pTLSTAObjArray[trainNumSta - 1]->m_mWorldOld = trans;
	// キラキラエフェクトの位置のセット
	m_pTLSTAObjArray[trainNumSta - 1]->GridWorld = XMMatrixTranslation(-4.5f + 1 * v, 5.05f, 0.5f + 4.0f - h * 1);
}
//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// イベントのセット
//
// 引数
//   VECTOR3 vMin         : バウンディングボックス最小値
//   VECTOR3 vMax         : バウンディングボックス最大値
//   MATRIX4X4 mWorld     : バウンディングボックスのワールドマトリックス
//   EVENTKIND nEvtKind   : イベントの種類 eEvtChangeMap:マップ移動, eEvtMoveMap:移動マップの制御
//   int nEvtNo           : イベント番号 eEvtChangeMapのときは移動先のマップ番号、eEvtMoveMapのときは移動マップの要素番号
//   int nEvtOpe1         : eEvtMoveMapのみ。1:移動マップの移動Activeの指定。2:移動マップの移動フラグの指定(省略値0)
//   int nEvtOpe2         : eEvtMoveMapのみ。移動Activeのときは0:非表示 1:表示  移動フラグのときは　0:移動無し　1:平行移動　2:回転　3:拡大縮小(省略値0)
//   int nEvtKeyPush      : 0:バウンディングボックスに接触するとイベント発動、 1:バウンディングボックスに接触して、ENTERキーを押すとイベント発動(省略値0)
//
// 戻り値
//   int セットしたイベント配列の要素番号
//
//-----------------------------------------------------------------------------
int  CMapProc::SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1, int nEvtOpe2, int nEvtKeyPush)
{
	const EVENTMAP      em;

	m_EventMap.push_back(em);

	// バウンディングボックスの設定
	m_EventMap[m_nEvtIdx].m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_EventMap[m_nEvtIdx].m_pBBox->m_mWorld = mWorld;

	// 各項目の設定
	m_EventMap[m_nEvtIdx].m_nEvtCycle = 0;
	m_EventMap[m_nEvtIdx].m_nEvtKind = nEvtKind;
	m_EventMap[m_nEvtIdx].m_nEvtNo = nEvtNo;
	m_EventMap[m_nEvtIdx].m_nEvtOpe1 = nEvtOpe1;
	m_EventMap[m_nEvtIdx].m_nEvtOpe2 = nEvtOpe2;
	m_EventMap[m_nEvtIdx].m_nEvtKeyPush = nEvtKeyPush;

	m_nEvtIdx++;
	return  m_nEvtIdx - 1;
}

//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// イベントの更新・実行
//
//-----------------------------------------------------------------------------
void  CMapProc::UpdateEvent()
{
	VECTOR3 vHit, vNrm;

	for (int i = 0; i < m_EventMap.size(); i++)
	{
		// PCのバウンディングボックスに接触しているかの判定
		if (m_EventMap[i].m_pBBox && m_EventMap[i].m_pBBox->OBBCollisionDetection(m_pGMain->m_pPcProc->GetPcObjPtr()->GetBBox(), &vHit, &vNrm))
		{
			// PCのバウンディングボックスに接触しているとき
			if (m_EventMap[i].m_nEvtCycle == 0)  // イベントサイクルが０のとき(まだ接触していなかったとき)
			{
				if (m_EventMap[i].m_nEvtKeyPush == 1 && !(m_pGMain->m_pDI->CheckKey(KD_DAT, DIK_RETURN) || m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A)))  // Enterキープッシュが必要なとき
				{
					VECTOR3 vPc = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
					vPc.y += 2.0f;
					// PCの頭上に、Enterキープッシュが行われていない事の表示をする
					m_pGMain->m_pFont->Draw3D(vPc, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt, _T("Push Enter Key!"), VECTOR2(0.8f, 0.2f), RGB(255, 0, 0), 1.0f, _T("HGP創英角ｺﾞｼｯｸUB"));
				}
				else {
					// イベント実行
					RunEvent(m_EventMap[i]);
				}
			}
		}
		else {
			// PCのバウンディングボックスに接触していないとき
			if (m_EventMap[i].m_nEvtCycle == 2)  // イベントサイクルが２のとき(既に接触していて終了待ちのとき)
			{
				m_EventMap[i].m_nEvtCycle = 0;  // イベントサイクルを０に戻す
			}
		}
	}
}

//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// イベントの実行
//
// 引数  EVENTMAP& EventMap:イベントマップ
//
//-----------------------------------------------------------------------------
void  CMapProc::RunEvent(EVENTMAP& EventMap)
{
	int i;

	if (EventMap.m_nEvtKind == eEvtChangeMap)   // マップ移動のとき
	{
		switch (EventMap.m_nEvtNo)
		{
		case 1:
			LoadMap1();
			break;
		case 2:
			LoadMap2();
			break;
		case 3:
			LoadMap3();
			break;
		}
	}
	else if (EventMap.m_nEvtKind == eEvtMoveMap)  // 移動マップの制御のとき
	{
		i = EventMap.m_nEvtNo;
		if (EventMap.m_nEvtOpe1 == 1)   // 表示有無に関する処理
		{
			m_MoveMap[i].m_bActive = EventMap.m_nEvtOpe2;
		}
		else if (EventMap.m_nEvtOpe1 == 2)   // 移動に関する処理
		{
			m_MoveMap[i].m_nMoveFlag = EventMap.m_nEvtOpe2;
		}
		EventMap.m_nEvtCycle = 2;  // イベントサイクルを２にする   // -- 2021.4.4
	}
}

//-----------------------------------------------------------------------------
//
// 移動マップの更新
//
// 移動マップの平行移動や回転の更新を行う
// 限界値（上端下端等）に達したときは、反転（change）を行う
// 反転（change）をしたときは、m_nChangeFlagに１が返る
// ループをしないときは反転のタイミングで停止する         // -- 2021.2.4
//
//-----------------------------------------------------------------------------
void CMapProc::UpdateMoveMap()
{
	for (DWORD i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)   // 移動マップの更新処理
		{
			m_MoveMap[i].m_pColMesh->m_mWorldOld = m_MoveMap[i].m_pColMesh->m_mWorld;   // ワールドマトリックス一つ前
			m_MoveMap[i].m_nChangeFlag = 0;      // チェンジフラグのリセット
			if (m_MoveMap[i].m_nMoveFlag == 1)   // 平行移動の処理
			{
				MATRIX4X4 mPosUp;
				mPosUp = XMMatrixTranslation(m_MoveMap[i].m_vUp.x, m_MoveMap[i].m_vUp.y, m_MoveMap[i].m_vUp.z);
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(mPosUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // 移動増分の処理
				if (m_MoveMap[i].m_vUp.x != 0)  // 左右に動かす
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).x < m_MoveMap[i].m_vMin.x ||  // 左右に動かすため右端左端で反転
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).x > m_MoveMap[i].m_vMax.x )
					{
						m_MoveMap[i].m_vUp.x *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.y != 0)  // 上下に動かす
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).y < m_MoveMap[i].m_vMin.y ||  // 上下に動かすため上端下端で反転
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).y > m_MoveMap[i].m_vMax.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.z != 0)  // 前後に動かす
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).z < m_MoveMap[i].m_vMin.z ||  // 前後に動かすため前端後端で反転
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).z > m_MoveMap[i].m_vMax.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 2){   // 回転の処理
				MATRIX4X4 mRotUp;
				if (m_MoveMap[i].m_vUp.x != 0)  // Ｘ回転
				{
					mRotUp = XMMatrixRotationX(XMConvertToRadians(m_MoveMap[i].m_vUp.x));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // Ｘ回転増分の処理
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).x < m_MoveMap[i].m_vMin.x ||  // Ｘ回転するため端で反転
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).x > m_MoveMap[i].m_vMax.x)
					{
						m_MoveMap[i].m_vUp.x *= -1;  // Ｘ回転するため端で反転
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}else if (m_MoveMap[i].m_vUp.y != 0)  // Ｙ回転
				{
					mRotUp = XMMatrixRotationY(XMConvertToRadians(m_MoveMap[i].m_vUp.y));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // Ｘ回転増分の処理
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).y < m_MoveMap[i].m_vMin.y ||  // Ｙ回転するため端で反転
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).y > m_MoveMap[i].m_vMax.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;  // Ｙ回転するため端で反転
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				else if (m_MoveMap[i].m_vUp.z != 0)  // Ｚ回転
				{
					mRotUp = XMMatrixRotationZ(XMConvertToRadians(m_MoveMap[i].m_vUp.z));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // Ｘ回転増分の処理
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).z < m_MoveMap[i].m_vMin.z ||  // Ｚ回転するため端で反転
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).z > m_MoveMap[i].m_vMax.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;  // Ｚ回転するため端で反転
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 3) {   // 拡大縮小の処理      // -- 2019.12.30
				MATRIX4X4 mScaleUp;
				mScaleUp = XMMatrixScaling(m_MoveMap[i].m_vUp.x, m_MoveMap[i].m_vUp.y, m_MoveMap[i].m_vUp.z);
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(mScaleUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // 拡大縮小増分の処理
				VECTOR3 vScaleNow = GetScaleVector(m_MoveMap[i].m_pColMesh->m_mWorld);     // 現在の拡大率を得る
				if (vScaleNow.x < m_MoveMap[i].m_vMin.x ||      // 規定の拡大縮小に達したか
					vScaleNow.x > m_MoveMap[i].m_vMax.x ||
					vScaleNow.y < m_MoveMap[i].m_vMin.y ||
					vScaleNow.y > m_MoveMap[i].m_vMax.y ||
					vScaleNow.z < m_MoveMap[i].m_vMin.z ||
					vScaleNow.z > m_MoveMap[i].m_vMax.z)
				{
					m_MoveMap[i].m_vUp.x = 1 / avoidZero(m_MoveMap[i].m_vUp.x);  // 拡大縮小の反転
					m_MoveMap[i].m_vUp.y = 1 / avoidZero(m_MoveMap[i].m_vUp.y);  // 拡大縮小の反転
					m_MoveMap[i].m_vUp.z = 1 / avoidZero(m_MoveMap[i].m_vUp.z);  // 拡大縮小の反転
					m_MoveMap[i].m_nChangeFlag = 1;
				}
			}
			// ループをしないときの停止判断。反転のタイミングで停止する             // -- 2021.2.4
			if (m_MoveMap[i].m_nLoop == 0 && m_MoveMap[i].m_nChangeFlag == 1)
			{
				m_MoveMap[i].m_nMoveFlag = 0;    // 移動しない
			}
		}
	}
}
//============================================================================
//  マッププロシージャのレンダリング
// 
//    引数　　なし
// 
//    戻り値　なし
//============================================================================
void  CMapProc::Render(void)
{
	int shineFlag = 0;  // レンダーの指定 M.S
	if (m_bActive) {
		// 空のレンダリング
		if (m_SkyMap.size() > 0)
		{
			// 空のレンダリング   陰影をつけないレンダリング 
			// Zバッファを無効化
			m_pGMain->m_pD3D->SetZBuffer(TRUE);
			m_SkyMap[0].m_pMesh->Render(m_SkyMap[0].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);  // 陰影をつけないレンダリング 
		}
		// マップレンダリング
		for (DWORD i = 0; i<m_StageMap.size(); i++)
		{
			//     m_dwMapNo(マップ)が2かつスタート位置の配置物  M.S 
			//     m_dwMapNo(マップ)が3かつ手前の星  M.S 
			if (MapNumGet() == 2 && i == 1 || MapNumGet() == 3 && i == 0) {
				shineFlag = 3; 	// レンダーの指定 M.S
				m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
				shineFlag = 0;  // レンダーの指定を0に戻す M.S
			}		
		    else if (m_StageMap[i].m_nMaterialFlag == 0)  // 通常のブレンドステート
			{
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
			}			
			else if (m_StageMap[i].m_nMaterialFlag == 2)  // ディスプレイスメントマッピング
			{
				// ディスプレイスメントマップレンダリング
				if (m_StageMap[i].m_pMesh) 	m_StageMap[i].m_pMesh->RenderDisplace(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}		
		}
		// 移動マップレンダリング     * このプログラムでは使用していない
		for (DWORD i = 0; i<m_MoveMap.size(); i++)
		{
			if( m_MoveMap[i].m_nMaterialFlag == 0 )  // 通常のブレンドステート
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
			}
			else if( m_MoveMap[i].m_nMaterialFlag == 2 )  // ディスプレイスメントマッピング
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->RenderDisplace(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}
	}
}
// M.S
// 線路のレンダリング
// 引  数：int        trainNumSt    配置する直線線路(縦)の合計の数
//         int        trainNumSd    配置する直線線路(横)の合計の数
//         int        trainNumCg    配置する方向切り替え線路の合計の数
//         int        trainNumSta   配置する駅の合計の数
//         CGameMain* mproc         CGameMainのポインタ
// 戻り値：なし
void TrainLineStProc::RenderLine(int trainNumSt,int trainNumSd,int trainNumCg,
	                             int trainNumSta, CGameMain* mproc){
	// マップレンダリング
	int shineNum = 1;  // レンダーの指定 M.S
	// 直線線路(縦)が配置をされているかどうか
	if (trainNumSt > 0) {
		for (DWORD i = 0; i < trainNumSt; i++)
		{
			// 配置されいてる数レンダリングする
			if (mproc->m_pMapProc->TrainLST->m_pTLSObjArray[i]->m_pMesh) {
				mproc->m_pMapProc->TrainLST->m_pTLSObjArray[i]->m_pMesh->
					Render(mproc->m_pMapProc->TrainLST->m_pTLSObjArray[i]->m_mWorld,
						mproc->m_mView, mproc->m_mProj, mproc->m_vLightDir, mproc->m_vEyePt, shineNum);
			}
		}
	}
	// 直線線路(横)が配置をされているかどうか
	if (trainNumSd > 0) {
		for (DWORD i = 0; i < trainNumSd; i++)
		{
			// 配置されいてる数レンダリングする
			if (mproc->m_pMapProc->TrainLSD->m_pTLSDObjArray[i]->m_pMesh) {
				mproc->m_pMapProc->TrainLSD->m_pTLSDObjArray[i]->m_pMesh->
				Render(mproc->m_pMapProc->TrainLSD->m_pTLSDObjArray[i]->m_mWorld,
				mproc->m_mView, mproc->m_mProj, mproc->m_vLightDir, mproc->m_vEyePt, shineNum);
			}
		}
	}
	// 方向切り替え線路が配置をされているかどうか
	if (trainNumCg > 0) {
		for (DWORD i = 0; i < trainNumCg; i++)
		{
			// 配置されいてる数レンダリングする
			if (mproc->m_pMapProc->TrainLChange->m_pTCGObjArray[i]->m_pMesh) {
				mproc->m_pMapProc->TrainLChange->m_pTCGObjArray[i]->m_pMesh->
				Render(mproc->m_pMapProc->TrainLChange->m_pTCGObjArray[i]->m_mWorld,
				mproc->m_mView, mproc->m_mProj, mproc->m_vLightDir, mproc->m_vEyePt, shineNum);
			}
		}
	}
	// 駅が配置をされているかどうか
	if (trainNumSta > 0) {
		for (DWORD i = 0; i < trainNumSta; i++)
		{
			// 配置されいてる数レンダリングする
			if (mproc->m_pMapProc->TrainLStation->m_pTLSTAObjArray[i]->m_pMesh) {
				mproc->m_pMapProc->TrainLStation->m_pTLSTAObjArray[i]->m_pMesh->
				Render(mproc->m_pMapProc->TrainLStation->m_pTLSTAObjArray[i]->m_mWorld,
    			mproc->m_mView, mproc->m_mProj, mproc->m_vLightDir, mproc->m_vEyePt, shineNum);
			}
		}
	}
}
//============================================================================
//  マッププロシージャのレンダリング その２
// 
//  半透明のマップオブジェクトを描画するため、主ループの最後に実行される
// 
//    引数　　なし
// 
//    戻り値　なし
//============================================================================
void  CMapProc::Render2(void)
{
	int shineFlag = 0;
	if (m_bActive) {

		// マップレンダリング
		for (DWORD i = 0; i<m_StageMap.size(); i++)
		{
			if (MapNumGet() == 3 && (i == 2 || i == 3)) {
				shineFlag = 2;
				m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);
				shineFlag = 0;
			}
			else if (MapNumGet() == 3 && (i == 4 || i == 5)) {
				shineFlag = 4;
				m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);
				shineFlag = 0;
			}
			if (m_StageMap[i].m_nMaterialFlag == 1)  // 透明色のブレンドステート
			{
				// 透明色のレンダリング
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);
			}
		}

		// 移動マップレンダリング     * このプログラムでは使用していない
		for (DWORD i = 0; i<m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_nMaterialFlag == 1)  // 透明色のブレンドステート
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
			}
		}

		// 波のレンダリング
		for (DWORD i = 0; i<m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 3)  
			{
				// 波レンダリング
				if (m_StageMap[i].m_pWave)
					m_StageMap[i].m_pWave->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

	}
}


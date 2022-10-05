//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//		マップ　ヘッダファイル											Map.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include <vector>

// --------------------------------------------------------------------
//
// ステージマップ
//
// --------------------------------------------------------------------

// クラスのプロトタイプ宣言
class TrainLineStObj;
class TrainLineStProc;
class TrainLineSdObj;
class TrainLineSdProc;
class TrainLineCgObj;
class TrainLineCgProc;
class TrainLineStationObj;
class TrainLineStationProc;

struct STAGEMAP
{
	CFbxMesh*				m_pMesh;			// スタティックメッシュへのポインタ
	CWave*					m_pWave;			// 波のメッシュへのポインタ
	MATRIX4X4				m_mWorld;			// メッシュのワールドマトリックス
	int						m_nMaterialFlag;	// マテリアルフラグ　0:通常　1:透明色　2:ディスプレイスメントマッピング 3:波
	CBBox*                  m_pBBox;            // バウンディングボックス

	STAGEMAP()    // コンストラクタ
	{
		Init();
	}
	~STAGEMAP()    // デストラクタ
	{
		// この中でメッシュのDELETEをしてはならない
	}
	void Init()    // 初期化メソッド
	{
		m_pMesh = NULL;
		m_pWave = NULL;
		m_mWorld = XMMatrixIdentity();
		m_nMaterialFlag = 0;
		m_pBBox = NULL;
	}
};
// --------------------------------------------------------------------
//
// 移動マップ            ＊このプログラム中では、使用しない
//
// --------------------------------------------------------------------
struct MOVEMAP
{
	BOOL					m_bActive;			// 移動Active
	CFbxMesh*				m_pMesh;			// スタティックメッシュへのポインタ
	int						m_nMaterialFlag;	// マテリアルフラグ　0:通常　1:透明色　2:ディスプレイスメントマッピング
	CCollision*				m_pColMesh;			// 移動コリジョンメッシュへのポインタ
	int						m_nMoveFlag;		// 移動フラグ　0:移動無し　1:平行移動　2:回転　3:拡大縮小      // -- 2019.12.30
	VECTOR3					m_vUp;				// 移動増分
	VECTOR3					m_vMin;				// 移動最小値
	VECTOR3					m_vMax;				// 移動最大値
	int						m_nChangeFlag;		// 移動が限界値に到達して方向が入れ替わるとき　0:移動中　1:方向チェンジ
	int						m_nLoop;			// 移動を繰り返すか  0:チェンジの箇所で停止し移動フラグを0:移動無しに戻す。 1:移動を繰り返す  // -- 2021.2.4

	MOVEMAP()    // コンストラクタ
	{
		Init();
	}
	~MOVEMAP()    // デストラクタ
	{
		// この中でメッシュのDELETEをしてはならない
	}
	void Init()
	{
		m_bActive = FALSE;
		m_pMesh = NULL;
		m_nMaterialFlag = 0;
		m_pColMesh = NULL;
		m_nMoveFlag = 0;
		m_vUp = VECTOR3(0, 0, 0);
		m_vMin = VECTOR3(-9999, -9999, -9999);
		m_vMax = VECTOR3(9999, 9999, 9999);
		m_nChangeFlag = 0;
		m_nLoop = 1;           // 初期設定はループ        // -- 2021.2.4
	}
};

// --------------------------------------------------------------------
//
// ナビゲーションマップ
//
// --------------------------------------------------------------------
struct NAVIGATIONMAP
{
	VECTOR3 vMin;
	VECTOR3 vMax;
	std::vector<DWORD>  m_dwEnmID;  // 対象となる敵のＩＤ
	NAVIGATIONMAP()    // コンストラクタ
	{
		Init();
	}
	void Init()
	{
		vMin = VECTOR3(0.0f, 0.0f, 0.0f);
		vMax = VECTOR3(0.0f, 0.0f, 0.0f);
	}
};

// --------------------------------------------------------------------    // -- 2021.2.4
//
// イベント
//
// --------------------------------------------------------------------
// イベント種類
enum EVENTKIND
{
	eEvtKindNone = 0,
	eEvtChangeMap = 1,
	eEvtMoveMap = 2
};

struct EVENTMAP
{
	CBBox*    m_pBBox;       // バウンディングボックス
	int       m_nEvtCycle;   // イベントサイクル 0:イベント実行していない 1:イベント実行中（使用していない） 2:イベント終了チェック（接触終わったか）
	EVENTKIND m_nEvtKind;    // イベントの種類 eEvtChangeMap:マップ移動, eEvtMoveMap:移動マップの制御
	int       m_nEvtNo;      // イベント番号 eEvtChangeMapのときは移動先のマップ番号、eEvtMoveMapのときは移動マップの要素番号
	int       m_nEvtOpe1;    // eEvtMoveMapのみ。1:移動マップの移動Activeの指定。2:移動マップの移動フラグの指定
	int       m_nEvtOpe2;    // eEvtMoveMapのみ。移動Activeのときは0:非表示 1:表示  移動フラグのときは　0:移動無し　1:平行移動　2:回転　3:拡大縮小
	int       m_nEvtKeyPush; // 0:バウンディングボックスに接触するとイベント発動、 1:バウンディングボックスに接触して、ENTERキーを押すとイベント発動

	EVENTMAP()    // コンストラクタ
	{
		m_pBBox = NULL;
		m_nEvtCycle = 0;
		m_nEvtKind = eEvtKindNone;
		m_nEvtNo = 0;
		m_nEvtOpe1 = 0;
		m_nEvtOpe2 = 0;
		m_nEvtKeyPush = 0;
	}
	~EVENTMAP()    // デストラクタ
	{
		// この中でメッシュのCBBoxのDELETEをしてはならない
	}
};

//======================================================================
// マップ　プロシージャクラス
//
// (注意)マップ　プロシージャクラスは、基本プロシージャクラスを継承していない
// 
//======================================================================
class CMapProc
{
protected:
    // レイを飛ばす時に使う変数
	VECTOR3 mHit;  // ヒット位置
	VECTOR3 mNor;  // ヒットした時の法線座標
	CGameMain*							m_pGMain;
	DWORD								m_dwMapNo;
	BOOL								m_bActive;

	std::vector<STAGEMAP>				m_SkyMap;			// 空のマップ
	std::vector<STAGEMAP>				m_StageMap;			// ステージのマップ
	CCollision*							m_pColMesh;			// コリジョンメッシュ
	std::vector<MOVEMAP>				m_MoveMap;			// 移動マップ  *このプログラム中では、使用しない
	std::vector<NAVIGATIONMAP>			m_NavMap;			// ナビゲーションマップ
	std::vector<EVENTMAP>				m_EventMap;			// イベントマップ    // -- 2021.2.4
	int									m_nEvtIdx;			// イベント要素番号  // -- 2021.2.4

public:

	void Update();
	void Render();
	void Render2();
	void DestroyAll();
	void LoadMap1();
	void LoadMap2();
	void LoadMap3();
	int isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius);

	void UpdateMoveMap();
	int  SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1 = 0, int nEvtOpe2 = 0, int nEvtKeyPush = 0);    // -- 2021.2.4
	void UpdateEvent();                                                                           // -- 2021.2.4
	void RunEvent(EVENTMAP& EventMap);                                                             // -- 2021.2.4

	BOOL Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal);
	BOOL Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal);
	BOOL Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal);    // -- 2020.12.11

	int  isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius = 0.2f);

	// アクセス関数
	std::vector<NAVIGATIONMAP> GetNavMap() { return m_NavMap; }

	// コンストラクタ（プロシージャの初期化）
	CMapProc(CGameMain*	m_pGMain);
	~CMapProc();
	MATRIX4X4 mMapWorldOld;    // -- 2022.1.18  回転前を保存

	// M.S CMapProcのここから下は追加した変数、関数です
	// M.S ↓--------------------------------------------------------------------
	// アクセス関数
	DWORD MapNumGet() { return m_dwMapNo; }  // マップナンバーの取得
	// マップの位置の取得
	MATRIX4X4 GetStageWorld() { return m_StageMap[0].m_mWorld; }
	// 各面に配置されているBBoxの位置の取得
	MATRIX4X4 GetStageBBox(int num) { return m_pBBoxPosition[num]->m_mWorld; }

	int* MapDynamic();              // 星の動的生成の関数
	int RandomNumMeth();            // ランダム数字の排出関数

	void ResetNewGameMap();    // ゲームループが一周したら変数のリセットをする関数
    // マップ配列記憶用の関数
	void lineMapSet(int oldRotateSurface);
	// 新しい面のマップを読み込む
	void lineMapNew(int RotateSurface);
	// 方向転換線路がマップ配列に入るか、また入った場合その配列の更新
	bool SetChangeBoxJudge(int h, int v);  
	// 方向を決め、その方向に進んだ時の縦横の位置排出
	void DecideDirection();         
	// 方向に進んだ時の縦横の位置排出
	int outStartNum(int up, int down, int left, int right, int startVertical, int startHorizontal);
	void MakeFrontBBox();       // 正面のバウンディンボックスの作成
	void MakeSurfaceBBox();     // 各面のバウンディングボックスの作成
	void SetPosSurfaceBBox();   // 各面のバウンディングボックスの位置セット
	void MapManRotate(MATRIX4X4 old, MATRIX4X4 mYaw);        // 各面の人オブジェクトの回転
	void MapBBoxRotate(MATRIX4X4 old, MATRIX4X4 mYaw);       // 各面のBBoxの回転
	bool SearchFinalPlacementSurface(int bBoxArrayNum);      // BBoxを使用して正面の面を調べる関数
	void BornStarEffect();                  // 星の動的配置表示とエフェクト

	// 星の架け橋をかける関数
	void BuiltStarBridge(VECTOR3 longCursol, VECTOR3 shortCursol);
	void RotateStar();                      // 星の回転をする関数
	void JudgeSurface();                    // 現在の操作面マップを調べる
	void GlitterEffect();                	// 線路のキラキラエフェクトの表示
	void DrawCursorGuide(int h, int v);     // カーソルガイドの表示
	void PlacementStLine(int h, int v);     // 直進線路の配置
	void PlacementCgLine(int h, int v);     // 方向転換線路の配置
	void PlacementStaLine(int h, int v);    // 駅の配置

	// 最後に配置操作したマップ面の保存用関数
	int SearchFinalPlacementSurface();
	// 配置したい方向変換の進む方向と配置可能かどうか見る
	int GetChangeNum(int h, int v, int oldH, int oldV);
	// 方向転換線路配置時のプレイヤー現在地の更新
	void UpadateOldHV(int oldH, int oldV, int h, int v);
	// 次の面への配置になる時の配置位置の管理
	bool AllowEndPlacement(bool onlyArrowJudgeFlag);
	// 星回転時に星に乗っているオブジェクトの回転を行う
	void MapPcRotate(MATRIX4X4 old, MATRIX4X4 mYaw);
	// (配置されているかなどを考えず)位置的に配置できるか判断する関数
	bool ArrowPlacementPos();

	// 星の動的生成で使用する変数
	int startMap[5][5] = { 0 };     // 生成マップ配列	
	int up;                     // 星の動的生成で使う方向変数
	int down;
	int right;
	int left;
	int startVertical;          // 星の動的生成に使用する配列の列
	int startHorizontal;        // 星の動的生成に使用する配列の行
	int ver;        // 星の動的生成に使用する配列の列buf
	int hori;     // 星の動的生成に使用する配列の行buf
	int arrowSwitch[4] = { 0 };     // どの方向が終わったかの判定用配列
	int randomNum;              //RandomNumMeth()で使用する変数

	//線路配置配列マップ
	int lineMap1[10][10] = { 0 };       // 操作用のマップ配列
	int lineMapBuf1[10][10] = { 0 };    // 初期状態でこちら側の面
	int lineMapBuf2[10][10] = { 0 };    // こちら側のその下の面
	int lineMapBuf3[10][10] = { 0 };    // 一番下の面
	int lineMapBuf4[10][10] = { 0 };    // lineMapBuf2の裏側
	int lineMapBuf5[10][10] = { 0 };    // 左側の面
	int lineMapBuf6[10][10] = { 0 };    // 右側の面
	int typeChangeNum;       // 置くことができる配置物の種類の識別数字  1:直線線路が配置可 2:直線線路、方向変更線路が配置可
	int starRotateSwitch;     // 星の回転を一回の操作で一度のみ行うため
	// カーソル位置の表示用BBox
	CBBox*                  m_pBBoxLine[10][10];
	int ChangeButton;                    // 配置物の変更数字 0:直線線路 1:方向転換線路 2:駅
	TrainLineStProc*      TrainLST;      // 縦線路
	TrainLineSdProc*      TrainLSD;      // 横線路
	TrainLineCgProc*      TrainLChange;  // 方向切り替え線路
	TrainLineStationProc* TrainLStation; // 駅

	// 配置した線路数
	int     trainNumSt;  // 縦線路
	int     trainNumSd;  // 横線路
	int     trainNumCg;  // 方向切り替え線路
	int     trainNumSta; // 駅
	int     oldH;        // 新しく配置した配置物の位置(行)
	int     oldV;        // 新しく配置した配置物の位置(列)
	int		LineChangeFlag;     // 0:初期 1:上 2:右 3:下 4:左

	int changeNum;       // 方向転換線路の方向変数1
	int aboutArrow;      // 方向転換線路の方向変数2

	MATRIX4X4 mYawX;  // 星のX回転角度のマトリックス
	MATRIX4X4 mYawZ;  // 星のX回転角度のマトリックス

	POINT  beforePoint;  // 回転をする操作の最初のマウス位置
	POINT  afterPoint;   // 回転をする操作の最後のマウス位置
	POINT  resultPoint;  // beforePointからafterPointを引いた値

	int pointArrow1; // 星の回転角度を求めるための変数
	int pointArrow2;
	int pointArrow3;
	int pointArrow4;

	float sideDegree;   // 星の回転角度の保存(横回転)
	float heightDegree; // 星の回転角度の保存(縦回転)
	CBBox*                  m_pBBoxPosition[6];   // 各面の識別用BBox

	// 各面の回転方向識別用BBox ゲーム画面の初期位置から  
	//   0:カメラから正面 1:カメラ正面から手前 2:正面の反対 3:1の反対画面 4:右側 5:左側
	CBBox*                  m_pBBoxArrow1[4];    // 初期位置:正面(プレイヤー初期位置)
	CBBox*                  m_pBBoxArrow2[4];    // 初期位置:上
	CBBox*                  m_pBBoxArrow3[4];    // 初期位置:裏
	CBBox*                  m_pBBoxArrow4[4];    // 初期位置:下
	CBBox*                  m_pBBoxArrow5[4];    // 初期位置:右
	CBBox*                  m_pBBoxArrow6[4];    // 初期位置:左
	// BBoxを調べる時に飛ばすレイの位置
	VECTOR3         front;
	VECTOR3         back;

	int pointArrowNum1;     // pointArrow変数の計算結果の保存変数
	int pointArrowNum2;

	bool rotateFinish;  // 回転終了処理フラグ
	int surfaceMap;     // 正面にある面の数字
	bool setOk;         // 配列の書き込み、読み込みを順番通りにする変数
	int northNow;       // 操作マップ面の回転方向保存変数

	// カーソル位置をマップ配列用に変換したもの保存変数
	int horiRotate; // 行
	int verRotate;  // 列

	int oldRotateSurface;        // 保存するべき面の数字変数
	int PlacementSurfaceNum;     // 最後に操作したマップ面の保存変数
	bool newSurfacePlacement;    // 次のマップ面への配置許可

	int permissionH; // 次のマップ面への配置許可用のクリック位置変数(行)
	int permissionV; // 次のマップ面への配置許可用のクリック位置変数(列)

	// マップ3の星の架け橋の配置許可
	bool starBridgePermission;  // 星の架け橋配置許可
	bool starBridgeInputFlag;   // クリックしたかフラグ
	bool NearStarCol;           // 手前の星とマウスの接触フラグ
	bool frontStarCol;          // 奥の星とマウスの接触フラグ

	// 人オブジェクトの配置が終わっているか(途中ではないか)
	bool doneManPlacement;
	// マップの回転に合わせたオブジェクトの移動が終わったかどうか
	bool rotateProcessDoneFlag;

	// 人オブジェクトの数を入れる変数
	int arrayHNum;  // 赤
	int arrayMNum;  // 黄
	int arrayLNum;  // 青

	int starBridgeLitingTime;   // 星の架け橋を光らせるカウント変数
	int starBridgePosNum;       // だんだん橋を光らせる為の橋移動用変数
	bool changeButtonWithinRange;  // 配置する線路が範囲内かどうかのフラグ
	int surfaceMapLineJudge;           // 現在の操作面マップ
	bool linePlacementOkFlag;       // 配置処理完了フラグ

	bool SaveRotateSurfaceFlag;    // マップ面の保存、更新完了フラグ
	int* mapStarArrayBuf;                  // 動的生成した星のポインタ
	int mapStarArray[5][5] = { 0 };        // 動的生成した星の配列
	int waitTime;                      // 星生成のエフェクトのタイムカウント
	int saveHori;        // 星生成のエフェクトに使用する配列要素番号(行)
	int saveVer;         // 星生成のエフェクトに使用する配列要素番号(列)
	int starEffectOrder; // 星生成のエフェクトのフェーズ
	int starObjArrayNum; // 発生させた星生成エフェクトの数	
};
//------------------------------------------------
// M.S 線路の抽象基底クラスプロシージャ
//------------------------------------------------
class TrainLineProc {
protected:
	CGameMain*	 m_pGMain;
public:
	CFbxMesh*    m_pMesh;
	CFbxMesh*    GetMesh() { return m_pMesh; }  // メッシュポインタの取得
	// 線路の情報をセット
	virtual void Update(int trainNum, int v, int h) = 0; // 純粋仮装関数
};
//------------------------------------------------
// M.S 線路の抽象基底クラスオブジェ
//------------------------------------------------
class TrainLineObj {
protected:
	int                 LineNum;    // 線路の種類
public:
	CFbxMesh*           m_pMesh;
	MATRIX4X4			m_mWorld;    // 線路の位置
	MATRIX4X4			m_mWorldOld;
	MATRIX4X4           GridWorld;   // キラキラエフェクトの位置
	int                 effectObjNum = 0;
	// 線路の種類変数のセット
	virtual void SetLineNum(int value) { LineNum = value; }
	// 線路の種類変数の取得
	int GetLineNum() { return LineNum; }
};
//------------------------------------------------
// M.S 直線の線路(縦)クラスプロシージャ
//------------------------------------------------
class TrainLineStProc : public TrainLineProc {
protected:
public:
	std::vector<TrainLineStObj*>   m_pTLSObjArray;  // 線路の配列
	// 直線線路オブジェ(縦)に情報をセット
	void Update(int trainNumSt, int v, int h)override; 
	// 線路の描画(全ての線路)
	void RenderLine(int trainNumSt, int trainNumSd, int TrainNumCg, int trainNumSta, CGameMain* mproc);
	TrainLineStProc(CGameMain* pGMain); // コンストラクタ
	~TrainLineStProc();	// デストラクタ
};
//------------------------------------------------
// M.S 直線の線路(縦)クラスオブジェ
//------------------------------------------------
class TrainLineStObj : public TrainLineObj {
protected:
public:
	int stLineMap;  // 配置した面の保存
	// メッシュのセット
	void SetMesh(TrainLineStProc* pProc) { m_pMesh = pProc->GetMesh(); } 
	// 線路の種類変数のセット
	void SetLineNum(int value) override { LineNum = value; } 
	// コンストラクタ
	TrainLineStObj(CGameMain* pGMain);  
	~TrainLineStObj();	// デストラクタ
};
//------------------------------------------------
// M.S 直線の線路(横)クラスプロシージャ
//------------------------------------------------
class TrainLineSdProc : public TrainLineProc {
protected:
public:
	std::vector<TrainLineSdObj*>   m_pTLSDObjArray;  // 線路の配列
	// 直線線路オブジェ(横)に情報をセット
	void Update(int trainNumSd, int v, int h)override;
	TrainLineSdProc(CGameMain* pGMain);  // コンストラクタ
	~TrainLineSdProc();	// デストラクタ
};
//------------------------------------------------
// M.S 直線の線路(横)クラスオブジェ
//------------------------------------------------
class TrainLineSdObj : public TrainLineObj {
protected:
public:
	int sdLineMap;    // 配置した面の保存
	// メッシュのセット
	void SetMesh(TrainLineSdProc* pProc) { m_pMesh = pProc->GetMesh(); }
	// 線路の種類変数のセット
	void SetLineNum(int value) override { LineNum = value; }
	TrainLineSdObj();   // コンストラクタ
	~TrainLineSdObj();	// デストラクタ
};
//------------------------------------------------
// M.S 方向切り替え線路クラスプロシージャ
//------------------------------------------------
class TrainLineCgProc :public TrainLineProc {
protected:
public:
	std::vector<TrainLineCgObj*>   m_pTCGObjArray;  // 線路の配列
	// 方向切り替え線路オブジェに情報をセット
	void Update(int trainNumCg, int v, int h)override;
	// コンストラクタ
	TrainLineCgProc(CGameMain* pGMain);
	~TrainLineCgProc();	// デストラクタ
};
//------------------------------------------------
// M.S 方向切り替え線路クラスオブジェ
//------------------------------------------------
class TrainLineCgObj : public TrainLineObj {
protected:
public:
	int cgLineMap;  // 配置した面の保存
	// メッシュのセット
	void SetMesh(TrainLineCgProc* pProc) { m_pMesh = pProc->GetMesh(); }
	// 線路の種類変数のセット
	void SetLineNum(int value) override { LineNum = value; }
	TrainLineCgObj();   // コンストラクタ
	~TrainLineCgObj();	// デストラクタ
};
//------------------------------------------------
// M.S 駅クラスプロシージャ
//------------------------------------------------
class TrainLineStationProc :public TrainLineProc {
protected:
public:	
	std::vector<TrainLineStationObj*>   m_pTLSTAObjArray;  // 線路の配列
	// 駅オブジェに情報をセット
	void Update(int trainNumSta, int v, int h)override;
	// コンストラクタ
	TrainLineStationProc(CGameMain* pGMain);
	~TrainLineStationProc();	// デストラクタ
};
//------------------------------------------------
// M.S 駅クラスオブジェ
//------------------------------------------------
class TrainLineStationObj : public TrainLineObj {
protected:
public:
	int staLineMap;  // 配置した面の保存
	// メッシュのセット
	void SetMesh(TrainLineStationProc* pProc) { m_pMesh = pProc->GetMesh(); }
	// 線路の種類変数のセット
	void SetLineNum(int value) override { LineNum = value; }
	TrainLineStationObj();  // コンストラクタ
	~TrainLineStationObj();	// デストラクタ
};
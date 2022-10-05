//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//		プレイキャラクター　ヘッダファイル							Playchar.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Map.h"


//======================================================================
// プレイキャラクター　オブジェクトクラス
//======================================================================
class CPcObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;			// Fbxスキンメッシュ
	BASEHOLDITEM        m_nHoldItem;		// 手に持つ武器
	float				m_fLocalRotY;		// ローカル軸(Y軸)    // -- 2018.8.4
	BOOL				m_bSide;			// 横移動モード       // -- 2018.8.4

	float				m_fSpeed;			// 移動速度           // -- 2019.3.5
	float				m_fRotSpeed;		// 回転速度           // -- 2019.3.5
	float				m_fJumpSpeed;		// ジャンプ速度       // -- 2019.3.5
	int                 moveTimes;          // プレイキャラの位置移動の回数
	int                 moveTimesMax;       // １マスで動く回数

public:
	void Update() override;
	void UpdateNormal();       // -- 2019.3.5
	void UpdateNormalMove();   // -- 2019.3.5
	MATRIX4X4 UpdateNormalMoveKeystate(DWORD DIKey);  // -- 2021.1.10
	void UpdateNormalAttack(); // -- 2019.3.5
	void UpdateDamage();       // -- 2019.3.5
	void UpdateDead();         // -- 2019.3.5
	void SetMesh(CPcProc* pProc);
	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る
	void SetLocalRotY(float fRotY) { m_fLocalRotY = fRotY; }   // ローカル軸(Y軸)をセットする
	CFbxMesh*  GetMesh() { return m_pMesh; }
	CPcObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CPcObj();
	MATRIX4X4 mPos;  // ＰＣ移動マトリックス

	// M.S CPcObjのここから下は追加した変数、関数です
	// M.S ↓--------------------------------------------------------------------
	// レイを飛ばす時に使う変数
	VECTOR3 mHit;  // ヒット位置
	VECTOR3 mNor;  // ヒットした時の法線座標
	// アニメーションを停止、再生する関数
	void SetPlayAnim(bool set) { m_AnimStatus.playAnim = set; }
	// PCの描画のみする関数
	void DoRender() { m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, 0); }
	// CPcObjのゲームの初期化をする関数
	void ResetNewGamePcObj();
	// 直線線路の移動処理の関数
	void MoveRight();    // 右方向移動
	void MoveLeft();     // 左方向移動
	void MoveDown();     // 下方向移動
	void MoveUp();       // 上方向移動
	// 方向切り替え線路の移動方向に合わせた変数のセット
	void SetUpRightChangeLineValue();   // 上から右移動
	void SetUpLeftChangeLineValue();    // 上から左移動
	void SetDownRightChangeLineValue(); // 下から右移動
	void SetDownLeftChangeLineValue();  // 下から左移動
	void SetRightUpChangeLineValue();   // 右から上移動
	void SetRightDownChangeLineValue(); // 右から下移動
	void SetLeftUpChangeLineValue();    // 左から上移動
	void SetLeftDownChangeLineValue();  // 左から下移動
	// 方向切り替え線路の移動処理
	void MoveUpRight();    // 上から右移動
	void MoveUpLeft();     // 上から左移動
	void MoveDownRight();  // 下から右移動
	void MoveDownLeft();   // 下から左移動
	void MoveRightUp();    // 右から上移動
	void MoveRightDown();  // 右から下移動
	void MoveLeftUp();     // 左から上移動
	void MoveLeftDown();   // 左から下移動
	// 面の端から次の面へ行く時の移動処理関数
	void MoveEdgePos1();
	void MoveEdgePos2();
	void MoveEdgePos3();
	void MoveEdgePos4();
	void MoveEdgePos5();
	void MoveEdgePos6();
	void SetEdgePos();  // MoveEdgePosを呼んで端から移動した時の位置と回転を求める
	// マップ面の端から次の面へ移動する時の現在地の更新
	void updateEdgeOldHV(int trainDirectionFlag, int oldH, int oldV, int surfaceNum);
	// キャラがいる面の数字や位置を調べる
	int JudgeNowPcMap(VECTOR3 nowPosition, bool onlyFront);
	// upBack、upFrontにレイを飛ばし、そのレイの場所にどこの面がいるのか調べる
	int RayOrderSurfaceBBox(MATRIX4X4 upBack, MATRIX4X4 upFront);

	// ゲームオーバーのアニメフェーズ
	int gameOverAnim;  
	// プレイキャラがいる位置
	int oldHP;  // 初期値は4
	int oldVP;  // 初期値は4
	int changeStepNum;   //方向切り替え線路の時の移動フェーズ 0:移動 1:回転 2:移動
	// 移動方向の変数 
	int upArrow;     // 上は1
	int rightArrow;  // 右は2
	int downArrow;   // 下は3
	int leftArrow;   // 左は4
	bool DoneMove;   	   // 1ループ中に移動をしたかどうかを入れる変数
	VECTOR3 nowPcPos;   // プレイヤキャラの位置
	int nowPcPosMap;    // プレイキャラの位置の数字
	int nowNorth;       // マップ面の回転の数字

   // 方向切り替え線路
	// 配置できない配列の上限値(upper)、下限値(lower)(Hが行、Vが列)
	int lowerLimitH;
	int upperLimitH;
	int upperLimitV;
	int lowerLimitV;
	// 線路配置後の配列の位置
	// Hは行、Vは列、Nearがついているのはプレイキャラから近いマス、ついていないのは離れているマス
	int chPlacementNearH;
	int chPlacementH;
	int chPlacementNearV;
	int chPlacementV;
	int edgePos;                             // プレイキャラが端にいるときの配列の値
	int rotateChar;                          // 方向切り替え線路のプレイキャラの回転変数
	int moveValueH;      	                 // 次の線路までの移動する距離(行)
	int moveValueV;      	                 // 次の線路までの移動する距離(列)
	int loopPlusMoveTimes;                   // ループして進んでいく度にmoveTimesに足す変数
	int changeLineNum;                       // 方向切り替え線路の配列にいれた数字
	int afterChangeLineNum;                  // 方向切り替え線路の通過後に配列にいれる数字
	float chLineMoveTimesMax;  // 最初にまっすぐ進む距離は2マス分なのでmoveTimesMax * 2
	int surfaceNum;            // プレイキャラがいる位置
	bool frontFlag;            // 正面にプレイキャラがいるフラグ  
	int nowPcPosNum;           // 原点から見て(+Y軸が上で-z軸がこちらに向いているの状態) 0:上 1:手前 2:下 3:1の裏 4:右 5:左
	MATRIX4X4 newPcPos;        // マップの面から面に移動する際のプレイヤー位置の調整用変数
	int trainDirectionFlag;    // 向かっている方向の保存

	int needRotateFlag;      // マップの面から面に移動する際のプレイヤー位置に掛ける変数の数の調整用変数
	MATRIX4X4 edgeRotate1;   // マップの面から面に移動する際のプレイヤー位置に掛ける数
	MATRIX4X4 edgeRotate2;
	MATRIX4X4 edgeRotate3;
	bool edgeFlag;           // 端から次の面への移動フラグをfalse

	int gameOverTime;     // ゲームオーバーアニメーションが終わった後のカウント
	int animCount;        // ゲームオーバーアニメーションの調整カウント
	int startTime;        // ゲーム開始までのカウント
	bool startTimeFlag;   // ゲーム開始フラグ
};

//======================================================================
// プレイキャラクター　プロシージャクラス
//======================================================================
class CPcProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;				// Fbxスキンメッシュ
	BASEHOLDITEM        m_nHoldItem;			// 手に持つ武器
	int				    m_nPcNum;

public:
	// アクセス関数
	CFbxMesh*           GetMesh() { return m_pMesh; }		// Fbxスキンメッシュ
	BASEHOLDITEM        GetHoldItem() { return m_nHoldItem; }	// 手に持つアイテムの値
	CPcObj*			    GetPcObjPtr() { return (CPcObj*)GetObjArrayPtr()[0]; }//
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num;  }
	// コンストラクタ
	CPcProc(CGameMain* pGMain);
	virtual	~CPcProc();

	// M.S ここからCPcProcのここから下は自分で書いた変数、関数です
	// M.S ↓--------------------------------------------------------------------
	// ゲームの初期化をする関数(CPcProc)
	void ResetNewGamePc();
	// 絶対値からキャラの上がどこに向いているのか調べる
	void JudgeAbsoluteSize(int kindNum, VECTOR3 pos);
	// 回転の角度を調べる関数
	int JudgeRotateSurface(int surfaceNum, VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// 回転の角度を調べる関数(初期状態で正面の面)
	int JudgeRotateSurfaceUp(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// 回転の角度を調べる関数(初期状態で正面の下の面)
	int JudgeRotateSurfaceUnder(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// 回転の角度を調べる関数(初期状態で正面の裏の面)
	int JudgeRotateSurfaceDown(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// 回転の角度を調べる関数(初期状態で正面の上の面)
	int JudgeRotateSurfaceAbove(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// 回転の角度を調べる関数(初期状態で正面の右の面)
	int JudgeRotateSurfaceRight(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// 回転の角度を調べる関数(初期状態で正面の左の面)
	int JudgeRotateSurfaceLeft(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);

	void lineMapSet(int oldsurfaceNum);     // プレイキャラがいたマップ配列を保存する関数
	void lineMapNew(int surfaceNum);        // プレイキャラがいるマップ配列を持ってくる関数
    // キャラがいる位置のマップ面の回転の角度を調べる関数
	int judgeDirection(int surfaceNum, VECTOR3 pos, int kindNum);

	// レイを飛ばす時に使う変数
	VECTOR3 mHit;  // ヒット位置
	VECTOR3 mNor;  // ヒットした時の法線座標
	// プレイヤーがいる位置の面の回転を調べる用
	bool directrioFlag1;  // 上
	bool directrioFlag2;  // 下
	bool directrioFlag3;  // 右 
	bool directrioFlag4;  // 左
	bool xJudge;   // x軸の値に対応したbool変数
	bool yJudge;   // y軸の値に対応したbool変数
	bool zJudge;   // z軸の値に対応したbool変数
	// プレイヤーの位置が上の場合
	VECTOR3 upFront1;
	VECTOR3 upBack1;
	VECTOR3 downFront1;
	VECTOR3 downBack1;
	VECTOR3 rightFront1;
	VECTOR3 rightBack1;
	VECTOR3 leftFront1;
	VECTOR3 leftBack1;
	// プレイヤーの位置が真ん中
	VECTOR3 upFront2;
	VECTOR3 upBack2;
	VECTOR3 downFront2;
	VECTOR3 downBack2;
	VECTOR3 rightFront2;
	VECTOR3 rightBack2;
	VECTOR3 leftFront2;
	VECTOR3 leftBack2;
	// プレイヤーの位置が下
	VECTOR3 upFront3;
	VECTOR3 upBack3;
	VECTOR3 downFront3;
	VECTOR3 downBack3;
	VECTOR3 rightFront3;
	VECTOR3 rightBack3;
	VECTOR3 leftFront3;
	VECTOR3 leftBack3;
	// プレイヤーの位置が裏の真ん中
	VECTOR3 upFront4;
	VECTOR3 upBack4;
	VECTOR3 downFront4;
	VECTOR3 downBack4;
	VECTOR3 rightFront4;
	VECTOR3 rightBack4;
	VECTOR3 leftFront4;
	VECTOR3 leftBack4;
	// プレイヤーの位置が右
	VECTOR3 upFront5;
	VECTOR3 upBack5;
	VECTOR3 downFront5;
	VECTOR3 downBack5;
	VECTOR3 rightFront5;
	VECTOR3 rightBack5;
	VECTOR3 leftFront5;
	VECTOR3 leftBack5;
	// プレイヤーの位置が左
	VECTOR3 upFront6;
	VECTOR3 upBack6;
	VECTOR3 downFront6;
	VECTOR3 downBack6;
	VECTOR3 rightFront6;
	VECTOR3 rightBack6;
	VECTOR3 leftFront6;
	VECTOR3 leftBack6;
	// 面の回転を保存する変数
	int rotateMapNorthNow;
	// 操作面でない時のプレイヤー移動を保存、参照するマップ配列
	int lineMapSub[10][10] = { 0 };
	// falseならばマップの回転を止める
	bool rotateOkFlag;
	bool oneScreenFlag;      // 1面のみ描画フラグ
	bool initialStart;       // 最初のスタート処理
	int trainStep;           // 移動距離
	int NewSurfaceNum;       // プレイキャラがいる面	
};


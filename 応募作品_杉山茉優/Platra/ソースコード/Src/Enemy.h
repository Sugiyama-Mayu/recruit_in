//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//		敵キャラクター　ヘッダファイル							Enemy.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Map.h"

// 敵のＩＤと発生数
// 
//   ID    :敵のＩＤ。１から順番に振る
//   MAX   :敵オブジェクトの数。（同時発生数）
//   ALLMAX:敵の最大出現数。（復活も含める）
// 
#define  ENM_GOLEM_ID        1
#define  ENM_GOLEM_MAX       6
#define  ENM_GOLEM_ALLMAX    6

#define  ENM_RS_ID           2
#define  ENM_RS_MAX          6
#define  ENM_RS_ALLMAX       6

#define  ENM_BD_ID           3
#define  ENM_BD_MAX          6
#define  ENM_BD_ALLMAX       6

//======================================================================
// 敵ゴーレム　オブジェクトクラス
//======================================================================
class CEnmGolemProc;
class CEnmGolemObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;		// Fbxスキンメッシュ
	BASEHOLDITEM		m_nHoldItem;	// 手に持つアイテム    // -- 2021.2.4
	VECTOR3				m_vTarget;		// ターゲット
	NAVIGATIONMAP		m_Nav;			// ナビゲーションマップ
	
public:
	//
	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmGolemProc* pProc);                 // -- 2021.2.4
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	CEnmGolemObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CEnmGolemObj();	// デストラクタ

	void OutUpPos();  // M.S プレイキャラと人が上にいたとする位置を出す関数
	// M.S 人オブジェクトを描画する関数
	void DoRenderHigh() { m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, 0); }
	// M.S 人オブジェクトのアニメーションの停止、再生
	void SetPlayAnimHigh(bool set) { m_AnimStatus.playAnim = set; }

	bool doneProcess;   // M.S 配置しているかフラグ
	bool alive;          // M.S 未乗車処理フラグ
	int manSurfaceNum;	    // M.S 人オブジェクトがいる面の数字
	int thisManArrayNumber; // M.S 配置した順番の保存
	MATRIX4X4 manRotate;    // M.S プレイキャラの方向を向く回転マトリックス
	MATRIX4X4 manRotateOld; // M.S 向く方向を戻すマトリックス
	bool initialProcess;  // M.S 最初のみの処理フラグ
	// M.S プレイキャラの方向を向かせる角度をマップの回転に合わせて調整する変数
	float initialRotate; 
	// M.S 0:まだ周りに通過済み駅線路がない 1:周りに通過済み駅線路が発生 3:乗り込みアニメーションと処理が終了
	int initialDeadAnim; 
	// M.S 乗車アニメーションのタイムカウント
	int animCount;
	// M.S 乗車アニメーションの時間
	int saveAnimCount;
	// M.S 回転角度フラグ
	bool rotate0;    // M.S 0度
	bool rotate90;   // M.S 90度
	bool rotate180;  // M.S 180度
	bool rotate270;  // M.S 270度
	VECTOR3 pcPos;    // M.S プレイキャラの位置
	VECTOR3 manPos;   // M.S 人オブジェクトの位置
};
// ------------------------------------
// 敵ゴーレム　プロシージャクラス
// ------------------------------------
class CEnmGolemProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbxスキンメッシュ
	BASEHOLDITEM        m_nHoldItem;	// 手に持つアイテム    // -- 2021.2.4	
public:
	void Update() override;
	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbxスキンメッシュ
	BASEHOLDITEM    GetHoldItem() { return m_nHoldItem; }	// 手に持つアイテムの値    // -- 2021.2.4
	CEnmGolemProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CEnmGolemProc();	// デストラクタ

	// M.S 人オブジェクトのポインタの取得
	CEnmGolemObj* GetHighManObjPtr(int i) { return (CEnmGolemObj*)GetObjArrayPtr()[i]; }
	// M.S 人オブジェクトの位置のセット
	void SetWorld(MATRIX4X4 m_mWorld, int i) { m_pObjArray[i]->SetWorld(m_mWorld); }
	// M.S 人オブジェクトの位置の取得
	MATRIX4X4 GetWorld(int i) { return m_pObjArray[i]->GetWorld(); }
	void ResetPlacementMan();  // M.S キャラの最初の配置位置の排出
	// M.S 要素の数字が面の数字
	int numH[6];          // M.S 各面の配置する行が入っている配列
	int numV[6];          // M.S 各面の配置する列が入っている配列
	int PlacementManMap[6] = { 0 };  // M.S 配置完了面の確認配列
	int manNum;                  // M.S 配置済み人数
	bool exclusiveMan;           // M.S 配置中フラグ
	int surfaceNumTarget;        // M.S 調べる面の数字
	bool managementDeadProcess;  // M.S 乗車処理中フラグ
};

//======================================================================
// 敵ＲＳ　オブジェクトクラス
//======================================================================
class CEnmRSProc;
class CEnmRSObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbxスキンメッシュ
	BASEHOLDITEM        m_nHoldItem;	// 手に持つアイテム
	VECTOR3				m_vTarget;	// ターゲット
	NAVIGATIONMAP		m_Nav;		// ナビゲーションマップ

public:
	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmRSProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	CEnmRSObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CEnmRSObj();	// デストラクタ

	void OutUpPos();     // M.S プレイキャラと人が上にいたとする位置を出す関数
	// M.S 人オブジェクトを描画する関数
	void DoRenderMiddle() { m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, 0); }
	// M.S 人オブジェクトのアニメーションの停止、再生
	void SetPlayAnimMiddle(bool set) { m_AnimStatus.playAnim = set; }

	bool doneProcess;        // M.S 配置しているかフラグ
	bool alive;              // M.S 未乗車処理フラグ
	int manSurfaceNum;       // M.S 人オブジェクトがいる面の数字
	int thisManArrayNumber;  // M.S 配置した順番の保存
	MATRIX4X4 manRotate;         // M.S プレイキャラの方向を向く回転マトリックス
	MATRIX4X4 manRotateOld;      // M.S 向く方向を戻すマトリックス
	bool initialProcess;  // M.S 最初のみの処理フラグ
	// M.S プレイキャラの方向を向かせる角度をマップの回転に合わせて調整する変数
	float initialRotate;
	// M.S 0:まだ周りに通過済み駅線路がない 1:周りに通過済み駅線路が発生 3:乗り込みアニメーションと処理が終了
	int initialDeadAnim;      
	// M.S 乗車アニメーションのタイムカウント
	int animCount;
	// M.S 乗車アニメーションの時間
	int saveAnimCount;
	// M.S 回転角度フラグ
	bool rotate0;        // M.S 0度
	bool rotate90;       // M.S 90度
	bool rotate180;      // M.S 180度
	bool rotate270;      // M.S 270度
	VECTOR3 pcPos;       // M.S プレイキャラの位置
	VECTOR3 manPos;      // M.S 人オブジェクトの位置
};
// ------------------------------------
// 敵ＲＳ　プロシージャクラス
// ------------------------------------
class CEnmRSProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbxスキンメッシュ
	BASEHOLDITEM        m_nHoldItem;	// 手に持つアイテム
public:
	void Update() override;
	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbxスキンメッシュ
	BASEHOLDITEM    GetHoldItem() { return m_nHoldItem; }	// 手に持つアイテムの値
	CEnmRSProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CEnmRSProc();	// デストラクタ

	// M.S 人オブジェクトのポインタの取得
	CEnmRSObj* GetMiddleManObjPtr(int i) { return (CEnmRSObj*)GetObjArrayPtr()[i]; }
	// M.S 人オブジェクトの位置のセット
	void SetWorld(MATRIX4X4 m_mWorld, int i) { m_pObjArray[i]->SetWorld(m_mWorld); }
	// M.S 人オブジェクトの位置の取得
	MATRIX4X4 GetWorld(int i) { return m_pObjArray[i]->GetWorld(); }
	void ResetPlacementMan();  // M.S キャラの最初の配置位置の排出

	// M.S 要素の数字が面の数字
	int numH[6];     // M.S 各面の配置する行が入っている配列
	int numV[6];     // M.S 各面の配置する列が入っている配列
	int PlacementManMap[6] = { 0 };    // M.S 配置完了面の確認配列
	int manNum = 0;                    // M.S 配置済み人数
	bool exclusiveMan;             // M.S 配置中フラグ
	int surfaceNumTarget;          // M.S 調べる面の数字
	bool managementDeadProcess;    // M.S 乗車処理中フラグ
};

//======================================================================
// 敵ブルードラゴン　オブジェクトクラス
//======================================================================
class CEnmBdProc;
class CEnmBdObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;		// Fbxスキンメッシュ
	BASEHOLDITEM        m_nHoldItem;	// 手に持つアイテム    // -- 2021.2.4
	VECTOR3				m_vTarget;	// ターゲット
	NAVIGATIONMAP		m_Nav;		// ナビゲーションマップ

public:
	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmBdProc* pProc);    // -- 2021.2.4
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	CEnmBdObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CEnmBdObj();	// デストラクタ

	void OutUpPos(); // M.S プレイキャラと人が上にいたとする位置を出す関数
	// M.S 人オブジェクトを描画する関数
	void DoRenderLow() { m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, 0); }
	// M.S 人オブジェクトのアニメーションの停止、再生
	void SetPlayAnimLow(bool set) { m_AnimStatus.playAnim = set; }

	bool doneProcess;      // M.S 配置しているかフラグ
	bool alive;             // M.S 未乗車処理フラグ
	int manSurfaceNum;         // M.S 人オブジェクトがいる面の数字
	int thisManArrayNumber;    // M.S 配置した順番の保存
	MATRIX4X4 manRotate;           // M.S プレイキャラの方向を向く回転マトリックス
	MATRIX4X4 manRotateOld;        // M.S 向く方向を戻すマトリックス

	bool initialProcess;    // M.S 最初のみの処理フラグ
	// M.S プレイキャラの方向を向かせる角度をマップの回転に合わせて調整する変数
	float initialRotate;
	// M.S 0:まだ周りに通過済み駅線路がない 1:周りに通過済み駅線路が発生 3:乗り込みアニメーションと処理が終了
	int initialDeadAnim;      
	// M.S 乗車アニメーションのタイムカウント
	int animCount;
	// M.S 乗車アニメーションの時間
	int saveAnimCount;
	// M.S 回転角度フラグ
	bool rotate0;    // M.S 0度
	bool rotate90;   // M.S 90度
	bool rotate180;  // M.S 180度
	bool rotate270;  // M.S 270度
	VECTOR3 pcPos;   // M.S プレイキャラの位置
	VECTOR3 manPos;  // M.S 人オブジェクトの位置
	
};
// ------------------------------------
// 敵ブルードラゴン　プロシージャクラス
// ------------------------------------
class CEnmBdProc : public CBaseProc
{
protected:
	CFbxMesh*			m_pMesh;		// Fbxスキンメッシュ
	BASEHOLDITEM		m_nHoldItem;	// 手に持つアイテム    // -- 2021.2.4
public:
	void Update() override;
	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbxスキンメッシュ
	BASEHOLDITEM    GetHoldItem() { return m_nHoldItem; }	// 手に持つアイテムの値    // -- 2021.2.4
	CEnmBdProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CEnmBdProc();	// デストラクタ

	// M.S 人オブジェクトのポインタの取得
	CEnmBdObj* GetLowManObjPtr(int i) { return (CEnmBdObj*)GetObjArrayPtr()[i]; }
	// M.S 人オブジェクトの位置のセット
	void SetWorld(MATRIX4X4 m_mWorld, int i) { m_pObjArray[i]->SetWorld(m_mWorld); }
	// M.S 人オブジェクトの位置の取得
	MATRIX4X4 GetWorld(int i) { return m_pObjArray[i]->GetWorld(); }
	void ResetPlacementMan();   // M.S キャラの最初の配置位置の排出

	// M.S 要素の数字が面の数字
	int numH[6];   // M.S 各面の配置する行が入っている配列
	int numV[6];   // M.S 各面の配置する列が入っている配列
	int PlacementManMap[6] = { 0 };   // M.S 配置完了面の確認配列
	int manNum;                   // M.S 配置済み人数
	bool exclusiveMan;        // M.S 配置中フラグ
	int surfaceNumTarget;         // M.S 調べる面の数字
	bool managementDeadProcess;  // M.S 乗車処理中フラグ
};
//======================================================================
// 敵キャラクター全体のメインプロシージャクラス
//======================================================================
class CEnmProc : public CBaseProc
{
public:
	CEnmGolemProc*		m_pEnmGolemProc; // 赤
	CEnmRSProc*			m_pEnmRSProc;    // 黄
	CEnmBdProc*			m_pEnmBdProc;    // 青
	// M.S 乗車合計人数
	int getLowMan;     // M.S 青
	int getMiddleMan;  // M.S 黄
	int getHighMan;    // M.S 赤
	// M.S 一つの星での乗車人数
	int getLowStageMan;     // M.S 青 
	int getMiddleStageMan;  // M.S 黄
	int getHighStageMan;    // M.S 赤
	// M.S 回転に合わせてセットする角度
	float rotate90angle;
	float rotate180angle;
	float rotate270angle;
	bool rotateOkFlagMan;  // M.S マップの回転を止めるフラグ
public:
	void Update();
	void ResetEnmNum(CBaseProc* pProc=NULL);
	int  CountActiveEnm(CBaseProc* pProc=NULL, int nNum=0);
	CEnmProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CEnmProc() { ; }	// デストラクタ
	void ResetNewGameMan();       // M.S 人キャラ変数のリセット
};


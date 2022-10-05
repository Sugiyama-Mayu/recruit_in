//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２                             ver 3.0        2021.1.11
//
//		カメラ制御
//
//		(視点変更処理・障害物回避処理が入っている)
//
//																Camera.h
//=============================================================================
#pragma once
#include "GameMain.h"

//======================================================================
// カメラ　オブジェクトクラス
//======================================================================
class CCameraObj : public CBaseObj
{
protected:
	int     m_nCtrl;                       // カメラ制御（0:ＴＰＳ視点  1:ＦＰＳ視点）
	MATRIX4X4 m_mBaseWorld;                // 注視点・視点の基点となる基点ワールドマトリックス
	VECTOR3 m_vLocalLookat;                // ローカル注視点ベクトル
	VECTOR3 m_vLocalEye;                   // ローカル視点ベクトル
	VECTOR3 m_vLocalEyeRotDist;            // ローカル視点ベクトルを生成するための角度と変位(TPSのみ)
	VECTOR3 m_vBaseLocalLookatTPS;         // ローカル注視点ベクトル初期値 TPS
	VECTOR3 m_vBaseLocalEyeRotDistTPS;     // ローカル視点ベクトル初期値(角度と変位) TPS
	VECTOR3 m_vBaseLocalLookatFPS;         // ローカル注視点ベクトル初期値 FPS
	VECTOR3 m_vBaseLocalEyeFPS;            // ローカル視点ベクトル初期値 FPS
	VECTOR3 m_vBaseLocalUp;                // ローカル

	VECTOR3 m_vStarLocalEye;               // M.S 星を見るときのカメラ位置
	VECTOR3 m_vStarLocalLookat;            // M.S 星を見るときの注視点
	VECTOR3 m_vTrainRunEyeTPS;             // M.S 線路で進む時のカメラ位置
	VECTOR3 m_vTrainRunLookatTPS;          // M.S 線路で進む時の注視点
	VECTOR3 m_vTrainStarLookat;            // M.S 線路で進む時の俯瞰(注視点)
	VECTOR3 m_vTrainStarEye;               // M.S 線路で進むときの星の俯瞰(カメラ位置)
	VECTOR3 m_vStarBridgeEye;              // M.S 星を見るときのカメラ位置
	VECTOR3 m_vStarBridgeLookat;           // M.S 星を見るときの注視点

public:
	void Update() override;
	void EvasiveObstacle();                // -- 2020.11.19
	void ControlCam();                     // -- 2020.11.19
	void SetLocalEyeTPS(float fRotY, float fRotX, float fDist);
	void SetCamBase();
	int  GetCtrl() { return cameraChangeSwitch; }
	// 0:星の動的生成画面視点 1 : 電車TPS視点 2 : 電車の俯瞰 3星の架け橋画面
	int cameraChangeSwitch; 
	CCameraObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CCameraObj();
};
//======================================================================
// カメラ　プロシージャクラス
//======================================================================
class CCameraProc : public CBaseProc
{
protected:
	;

public:
	CCameraObj*	 GetCameraObjPtr() { return (CCameraObj*)GetObjArrayPtr()[0]; }
	CCameraProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CCameraProc() { ; }
};


//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２                             ver 3.0        2021.1.11
//
//		カメラ制御
//
//		(視点変更処理・障害物回避処理が入っている)
//
//																Camera.cpp
//=============================================================================
#include  "Camera.h"
#include  "Playchar.h"
#include  "Map.h"

//==========================================================================================================================
//
// カメラプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// -------------------------------------------------------------------------------------------------------------------------
CCameraProc::CCameraProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pObjArray.push_back(new CCameraObj(m_pGMain));  // m_pObjArrayにオブジェクトを登録する
}

// --------------------------------------------------------------------------- // -- 2020.11.19
//
// カメラオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CCameraObj::CCameraObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// cameraChangeSwitch 0:星の動的生成画面視点 1:電車TPS視点 2:電車の俯瞰 3星の架け橋画面
	cameraChangeSwitch = 0;    
	// カメラの位置の基点の位置
	m_mBaseWorld = XMMatrixTranslation(0, 0, 0);
	// マップ1で使用する星の動的生成画面視点 
	// 基点ワールドマトリックスからの変位初期値の設定
	// ① 星の俯瞰視点のときの基点ワールドマトリックスからの変位値
	// ・注視点(見る場所)は、変位距離をm_vStarLocalLookatに設定する
	m_vStarLocalLookat = VECTOR3(0.0f, 0.0f, 0.0f);                // 基点との差を0
	//注視点からの増分でカメラの位置を指定
	m_vStarLocalEye.z = -35.0f;  // 変位直線距離 
	m_vStarLocalEye.x = 0.0f;    // 変位角度Ｘ
	m_vStarLocalEye.y = 140.0f;  // 変位角度Ｙ  

	// マップ2で使用する電車TPS視点画面
	// 基点ワールドマトリックスからの変位初期値の設定
	// ① 線路配置ゲーム画面のときの基点ワールドマトリックスからの変位値
	// ・注視点は、変位距離をm_vTrainRunLookatTPSに設定する
	m_vTrainRunLookatTPS = VECTOR3(0.0f, 0.0f, 0.0f);     

	//注視点からの増分でカメラの位置を指定
	m_vTrainRunEyeTPS.z = -4.0f;  // 変位直線距離
	m_vTrainRunEyeTPS.x = 59.0f; // 変位角度Ｘ
	m_vTrainRunEyeTPS.y = 40.0f;   // 変位角度Ｙ

	// マップ2で使用する電車の俯瞰画面
	// 基点ワールドマトリックスからの変位初期値の設定
	// ① 線路配置ゲーム画面のときの基点ワールドマトリックスからの変位値
	// ・注視点は、変位距離をm_vBaseLocalLookatTPSに設定する
	m_vTrainStarLookat = VECTOR3(0.0f, 0.0f, 0.9f);           // 少し斜めから見て立体感を出す

	//注視点からの増分でカメラの位置を指定
	m_vTrainStarEye.z = 0.0f;
	m_vTrainStarEye.x = 0.0f;
	m_vTrainStarEye.y = 90.0f;

	// マップ4で使用する星の架け橋を掛ける画面
	// 基点ワールドマトリックスからの変位初期値の設定
	// ①星の架け橋を掛ける画面のときの基点ワールドマトリックスからの変位値
	// ・注視点は、変位距離をm_vStarBridgeLookatに設定する
	m_vStarBridgeLookat = VECTOR3(0.0f, 0.0f, 10.0f);

	//注視点からの増分でカメラの位置を指定
	m_vStarBridgeEye.z = -3.0f;  // 変位直線距離
	m_vStarBridgeEye.x = 0.0f; // 変位角度Ｘ
	m_vStarBridgeEye.y = 50.0f;   // 変位角度Ｙ

	// カメラ変位初期値を設定する
	SetCamBase();
}
// ---------------------------------------------------------------------------
//
// カメラオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CCameraObj::~CCameraObj()
{
	;
}
//-----------------------------------------------------------------------------  // -- 2020.11.19
// カメラオブジェクトの制御
//
//　ＰＣの動きに合わせてカメラを制御する
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CCameraObj::Update()
{
	// 注視点・視点の基点となる基点ワールドマトリックスの設定
	// ここを変えるとカメラの上下左右変わる 
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);    // 上方位置を絶対座標の上方向とする
	//M.S cameraChangeSwitch 0:星の俯瞰視点 1:電車TPS画面 2:電車の俯瞰 3:星の架け橋画面 
	switch (cameraChangeSwitch) {
	case 0:
		m_mBaseWorld = XMMatrixTranslation(35.0f, 0.0f, -25.0f);
		break;
	case 1:
		// M.S プレイキャラの座標の取得;
		MATRIX4X4 nowPcPos = m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld();
		// M.S m_mBaseWorldの基点をプレイキャラの座標にする;
		m_mBaseWorld = nowPcPos;
		m_vTrainRunLookatTPS = VECTOR3(0.0f, 0.0f, 0.0f);
		// M.S プレイキャラの位置に合わせてカメラの上方位置を決める
		switch (m_pGMain->m_pPcProc->GetPcObjPtr()->nowPcPosNum) {
		case 0:
			vUpVec = VECTOR3(0.0f, 1.0f, 0.0f);
			break;
		case 1:
			vUpVec = VECTOR3(0.0f, 0.0f, -1.0f);
			break;
		case 2:
			vUpVec = VECTOR3(0.0f, -1.0f, 0.0f);
			break;
		case 3:
			vUpVec = VECTOR3(0.0f, 0.0f, 1.0f);
			break;
		case 4:
			vUpVec = VECTOR3(1.0f, 0.0f, 0.0f);
			break;
		case 5:
			vUpVec = VECTOR3(-1.0f, 0.0f, 0.0f);
			break;
		}
		break;
	case 2:
		m_mBaseWorld = XMMatrixTranslation(6.0f, -65.0f, 0.0f);
		break;
	case 3:
		m_mBaseWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
		break;
	}
	// カメラオブジェクトの位置を手動操作
	// また、カメラ制御を変更（ＴＰＳ視点かＦＰＳ視点か）
	SetCamBase();

	// 注視点のベクトルを作成する処理
	// (注視点のローカル座標と基点ワールドマトリックスを掛け合わせ、注視点マトリックスを得る)
	MATRIX4X4 mLookat = XMMatrixTranslationFromVector(m_vLocalLookat) * m_mBaseWorld;
	m_pGMain->m_vLookatPt = GetPositionVector(mLookat);    // 注視点マトリックスから注視点位置を得る

	// カメラ（視点）ベクトルを作成する処理
	// (カメラ（視点）のローカル座標と基点ワールドマトリックスを掛け合わせ、視点マトリックスを得る)
	MATRIX4X4 mEye = XMMatrixTranslationFromVector(m_vLocalEye) * m_mBaseWorld;
	m_pGMain->m_vEyePt = GetPositionVector( mEye );        // 視点マトリックスから視点位置を得る

	// TPS視点の時、障害物を回避する処理
	if (cameraChangeSwitch == 0) EvasiveObstacle();

	// 視点ベクトルと注視点ベクトルからカメラのワールドマトリックスを得る（今は使用していない）
	m_mWorld = GetLookatMatrix(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt);

	// カメラ(視点)の位置、上方向、および注視点を使用して、左手座標系のビュー行列を作成
	m_pGMain->m_mView = XMMatrixLookAtLH(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt, vUpVec);
}
//-----------------------------------------------------------------------------  // -- 2020.11.19
// 障害物を回避する処理
//
// ・視点と注視点との間に障害物があった場合、視点を障害物の前に移動する処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CCameraObj::EvasiveObstacle()
{
	VECTOR3 vHit;
	VECTOR3 vNorm;
	if (m_pGMain->m_pMapProc->Hitcheck(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt, &vHit, &vNorm))   // 障害物との接触チェック
	{
		MATRIX4X4 mTemp;
		mTemp = GetLookatMatrix(vHit, m_pGMain->m_vLookatPt);        // 障害物との接触点から注視位置を見るマトリックス
		mTemp = XMMatrixTranslation(0.0f, 0.0f, 0.01f) * mTemp;      // 障害物との接触点から1cm注視方向に移動した視点位置を得る
		m_pGMain->m_vEyePt = GetPositionVector(mTemp);
	}
}
//-----------------------------------------------------------------------------  // -- 2020.11.19
// カメラオブジェクトの手動操作制御
//
//   カメラオブジェクトの位置を手動で操作する
//   また、カメラ制御を変更（ＴＰＳ視点かＦＰＳ視点か）
//-----------------------
//   引数　　　なし
//------------------------------------------------------
void	CCameraObj::ControlCam()
{
	VECTOR3 nowPcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	const float fRotUp  = 1.5f;     // 角度変更の増分値
	const float fDistUp = 0.05f;    // 距離変更の増分値
	// M.S カメラ変位初期値を設定
	SetCamBase();
}
//----------------------------------------------------------------------------- // -- 2020.11.19
// ＴＰＳのときカメラ位置の設定処理
//
//   m_vLocalEyeRotDist.xとm_vLocalEyeRotDist.yに回転角度、m_vLocalEyeRotDist.zに
//   注視点から視点までの直線距離が入っている、
//   その値に、引数の回転と距離を加算し、その結果を基に、変位値を計算し、
//   その結果をm_vLocalEyeに設定する
//
//   引数	float fRotY : Ｙ回転
//			float fRotX : Ｘ回転
//			float fDist : 距離
//
//   戻り値　なし
//-----------------------------------------------------------------------------
void	CCameraObj::SetLocalEyeTPS(float fRotY, float fRotX, float fDist)
{
	m_vLocalEyeRotDist.x += fRotX;
	m_vLocalEyeRotDist.y += fRotY;
	m_vLocalEyeRotDist.z += fDist;
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(m_vLocalEyeRotDist.y));
	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(m_vLocalEyeRotDist.x));
	MATRIX4X4 mPos  = XMMatrixTranslation(0, 0, m_vLocalEyeRotDist.z);
	mPos = mPos * mRotX * mRotY;
	m_vLocalEye = GetPositionVector(mPos);
}
//----------------------------------------------------------------------------- // -- 2020.11.19
// カメラ変位初期値を設定する処理
//
// ① TPS視点のとき
//    視点は、変位角度と変位直線距離を、一旦m_vLocalEyeRotDistに設定し、
//    その後SetLocalEyeTPS関数によって、m_vLocalEyeに設定する
//    注視点は、変位距離をm_vLocalLookatTPSに設定する
//
// ② FPS視点のとき
//    視点は、変位距離をm_vLocalEyeに設定する
//    注視点は、変位距離をm_vLocalLookatに設定する
//
//   引数	なし
//
//   戻り値　なし
//-----------------------------------------------------------------------------
void	CCameraObj::SetCamBase()
{
	// カメラ変位の初期値を設定する
	//M.S cameraChangeSwitch 0:星の俯瞰視点 1:電車TPS画面 2:電車の俯瞰 3:星の架け橋画面 
	switch (cameraChangeSwitch) {
	case 0:
		m_vLocalEye = m_vStarLocalEye;          // M.S 視点 
		m_vLocalLookat = m_vStarLocalLookat;    // M.S 注視点
		break;
	case 1:
		m_vLocalEyeRotDist = m_vTrainRunEyeTPS; // M.S 視点
		m_vLocalLookat = m_vTrainRunLookatTPS;  // M.S 注視点
		SetLocalEyeTPS(0, 0, 0);  
		break;
	case 2:
		m_vLocalEye = m_vTrainStarEye;          // M.S 視点
		m_vLocalLookat = m_vTrainStarLookat;    // M.S 注視点
		break;
	case 3:
		m_vLocalEye = m_vStarBridgeEye;         // M.S 視点
		m_vLocalLookat = m_vStarBridgeLookat;   // M.S 注視点
		break;			
	}
}
//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//      武器の処理
//																Weapon.cpp
//=============================================================================

#include "Weapon.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Map.h"

//=============================================================================================================================
//
// 武器メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pWeaponShotProc = new CWeaponShotProc(m_pGMain);	// (PC)武器・ショットプロシージャ
	m_pProcArray.push_back(m_pWeaponShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pEWeaponShotProc = new CEWeaponShotProc(m_pGMain); // (敵)武器・ショットプロシージャ
	m_pProcArray.push_back(m_pEWeaponShotProc);     // プロシージャをプロシージャ配列に登録する
} 
// ================================================================================================================================
// 
// 各敵プロシージャ毎の処理
// 
// ================================================================================================================================
//------------------------------------------------------------------------
//
//	武器・ショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEWeaponShotProc::CEWeaponShotProc(CGameMain* pGMain) : CBaseProc(pGMain) //敵
{
	// 武器・ショット
	for (DWORD i = 0; i < WEAPON_ESHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CEWeaponShotObj(m_pGMain)); // m_pObjArrayに武器・ショットオブジェクトを生成する
	}
	m_nWaitTime = m_nMaxwaitTime = 8;
}
CWeaponShotProc::CWeaponShotProc(CGameMain* pGMain) : CBaseProc(pGMain) //PC
{
	// 武器・ショット
	for (DWORD i = 0; i < WEAPON_SHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponShotObj(m_pGMain)); // m_pObjArrayに武器・ショットオブジェクトを生成する
	}
	m_nWaitTime = m_nMaxwaitTime = 8;
}
//-----------------------------------------------------------------------------
BOOL CEWeaponShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) //敵
{
	BOOL bRet = FALSE;
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{			
				m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
				m_pGMain->m_pSeHit->Play();
				bRet = TRUE;		
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
	return bRet;
}
BOOL CWeaponShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) //PC
{
	BOOL bRet = FALSE;
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
	return bRet;
}
//------------------------------------------------------------------------
//
//	武器・ショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEWeaponShotObj::CEWeaponShotObj(CGameMain* pGMain) : CBaseObj(pGMain) //敵
{
	m_pSprite = new CSprite(m_pGMain->m_pWeaponImage, 0, 64, 32, 32); // 武器画像
	m_nAnimNum = 8;
	m_nAtc = 1;
}
CWeaponShotObj::CWeaponShotObj(CGameMain* pGMain) : CBaseObj(pGMain) //PC
{
	m_pSprite = new CSprite(m_pGMain->m_pWeaponImage, 0, 32, 32, 32); // 武器画像
	m_nAnimNum = 8;
	m_nAtc = 2;
}
// ---------------------------------------------------------------------------
//
// 武器・ショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEWeaponShotObj::~CEWeaponShotObj() //敵
{
	SAFE_DELETE(m_pSprite);
}
CWeaponShotObj::~CWeaponShotObj() //PC
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・ショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL CEWeaponShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) //敵
{
	float fSpeed = 8;	// 弾の速さ
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);

	// M.S プレイキャラの位置と弾を打つ位置の差分(X軸)を求める
	VECTOR2 vPcPos;
	vPcPos.x = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().x;
	m_pGMain->sabun = vPcPos.x - m_vPos.x;
	// M.S 差分からプレイキャラの方向へ弾を打つ
	if (m_pGMain->sabun > 0) {
		m_vPosUp = VECTOR2(fSpeed, 0);
	}
	else {
		m_vPosUp = VECTOR2(-fSpeed, 0);
	}
	return TRUE;
}
BOOL CWeaponShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) //PC
{
	float fSpeed = 8;	// 弾の速さ
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);

	if (m_pGMain->strongSSw == true) { // M.S 武器が強化されているかどうか
		m_pSprite = new CSprite(m_pGMain->m_pWeaponImage, 0, 0, 32, 32);
		m_nAtc = 3;
	}
	switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
// 武器・ショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void CEWeaponShotObj::Update() //敵
{
	CMapLine*  pHitmapline = NULL;
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			BOOL swE;
			swE = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			if (swE == TRUE) {
				m_bActive = FALSE;
			}
			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			break;
		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}
		m_vPos += m_vPosUp;
		AnimCountup();
		Draw();
	}
}
void CWeaponShotObj::Update() //PC
{
	CMapLine*  pHitmapline = NULL;
	BOOL swP;

	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
			swP = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			if (swP == TRUE) {
				m_bActive = FALSE;
			}
			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			break;
		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}
		m_vPos += m_vPosUp;
		AnimCountup();
		Draw();
	}
}

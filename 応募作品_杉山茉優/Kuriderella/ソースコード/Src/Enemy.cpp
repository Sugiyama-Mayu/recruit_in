//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		敵の処理
//																Enamy.cpp
//=============================================================================

#include "Enemy.h"
#include "Weapon.h"
#include "Effect.h"
#include "Playchar.h"
#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------
//
// 敵メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEnmWaterProc = new CEnmWaterProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmWaterProc);   // プロシージャをプロシージャ配列に登録する

	m_pEnmTordProc = new CEnmTordProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmTordProc);   // プロシージャをプロシージャ配列に登録する

	m_pEnmWolfProc = new CEnmWolfProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmWolfProc);   // プロシージャをプロシージャ配列に登録する

	m_pEnmFoxProc = new CEnmFoxProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmFoxProc);   // プロシージャをプロシージャ配列に登録する   

	m_pEnmDosProc = new CEnmDosProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmDosProc);   // プロシージャをプロシージャ配列に登録する

	m_pEnmSkyProc = new CEnmSkyProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmSkyProc);   // プロシージャをプロシージャ配列に登録する

	m_pEnmKingProc = new CEnmKingProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmKingProc);   // プロシージャをプロシージャ配列に登録する
}
//============================================================================
//   敵プロシージャとオブジェクトを探索し全てのオブジェクトをノンアクティブにする
//   敵プロシージャの開始フラグをリセットする
//============================================================================
void  CEnmProc::SetNonActive()
{
	// 敵のオブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive( FALSE);
	}
	// 下位のプロシージャポインタ配列の探索
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag( 0 );				// 開始フラグのリセット
		((CEnmProc*)m_pProcArray[i])->SetNonActive();   // 下位のプロシージャの処理（再帰処理）
	}
}
// =====================================================================================================
// 
// 各敵プロシージャ毎の処理
// 
// =====================================================================================================
//------------------------------------------------------------------------
//
//	水の敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmWaterProc::CEnmWaterProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_WATER_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmWaterObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}
// ---------------------------------------------------------------------------
//
// 水の敵プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmWaterProc::Update()
{
	VECTOR2 vPos;
	int nNext;
	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップ　 ( EvtID:3　敵の出現位置,     　EvtNo:0x01	水の敵  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x01, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
}
//------------------------------------------------------------------------
//
//	水の敵オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmWaterObj::CEnmWaterObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S 水の敵のスプライト
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 896, 0, 64, 64);
	m_fAlpha = 0.8f;
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 10000;
	m_nAtc = 1;
}
// ---------------------------------------------------------------------------
//
// 水の敵オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmWaterObj::~CEnmWaterObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 水の敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmWaterObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// 水の敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmWaterObj::Update()
{
	CMapLine* pHitmapline;
	BOOL bRet;
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			break;
		case  DAMAGE:
			m_dwStatus = NORMAL;
			m_pGMain->hank = 1;  // M.S プレイキャラとの接触フラグをたてる		
			break;
		case  DEAD:
			m_dwStatus = NORMAL;
			break;
		}
		AnimCountup();
		Draw();
	}
}
// ===================================================================================================
//------------------------------------------------------------------------
//
//	灰色の敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmTordProc::CEnmTordProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmTordObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}
// ---------------------------------------------------------------------------
//
// 灰色の敵プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmTordProc::Update()
{
	VECTOR2 vPos;
	int nNext;
	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while ( nNext != -1)
		{
			// イベントマップ　 ( EvtID:3　敵の出現位置,     　EvtNo:0x02　灰色の敵  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x02, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
}
//------------------------------------------------------------------------
//
//	灰色の敵オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmTordObj::CEnmTordObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S 灰色の敵のスプライト
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 640, 0, 64, 64);  
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 1;
	m_nAtc = 1;
}
// ---------------------------------------------------------------------------
//
// 灰色の敵オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmTordObj::~CEnmTordObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// 灰色の敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmTordObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// 灰色の敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmTordObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1;
	BOOL bRet;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;を入れずそのまま　NORMAL　の処理を行う
		case  NORMAL:
			switch (m_dwStatusSub)
			{
			case  WALK:
				// 自由移動の処理
				if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}
				// マップ線との接触判定と適切な位置への移動
				bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
				if (!bRet || (pHitmapline && pHitmapline->m_vNormal.y > -0.99f))
				{
					// マップ線の端に来たので左右反転
					if (m_nDirIdx == RIGHT)
					{
						m_nDirIdx = LEFT;
						m_vPosUp.x = -fSpeed;
						m_vPosUp.y = 0;
					}
					else {
						m_nDirIdx = RIGHT;
						m_vPosUp.x = fSpeed;
						m_vPosUp.y = 0;
					}
				}
				break;
			}
			// 増分
			m_vPos += m_vPosUp;
			// ＰＣとのあたり判定
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;
		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			m_pGMain->m_pSeHit->Play(); // ダメージ効果音
			break;

		case  DEAD:
			m_nCnt1--;
			// DEADになり、一定時間たったら表示を消す
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
			}
			else {
				FlashCountup();
			}
			break;
		}
		AnimCountup();
		Draw();
	}
}
// ===================================================================================================

//------------------------------------------------------------------------
//
//	赤色の敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmWolfProc::CEnmWolfProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmWolfObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}
// ---------------------------------------------------------------------------
//
// 赤色の敵プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmWolfProc::Update()
{
	VECTOR2 vPos;
	int  nNext;
	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索 (EvtID:3 敵の出現位置, EvtNo:0x04 赤色の敵)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x04, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
}
//------------------------------------------------------------------------
//
//	赤色の敵オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmWolfObj::CEnmWolfObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S 赤色の敵のスプライト
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 384, 0, 64, 64);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 2;
	m_nAtc = 2;
}
// ---------------------------------------------------------------------------
//
// 赤色の敵オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmWolfObj::~CEnmWolfObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// 赤色の敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmWolfObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// 赤色の敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmWolfObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1;
	BOOL bRet;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;を入れずそのまま　NORMAL　の処理を行う
		case  NORMAL:
			switch (m_dwStatusSub)
			{
			case  WALK:
				// 自由移動の処理
				if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}
				// マップ線との接触判定と適切な位置への移動
				bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
				if (!bRet || (pHitmapline && pHitmapline->m_vNormal.y > -0.99f))
				{
					// マップ線の端に来たので左右反転
					if (m_nDirIdx == RIGHT)
					{
						m_nDirIdx = LEFT;
						m_vPosUp.x = -fSpeed;
						m_vPosUp.y = 0;
					}
					else {
						m_nDirIdx = RIGHT;
						m_vPosUp.x = fSpeed;
						m_vPosUp.y = 0;
					}
				}
				break;
			}
			// 増分
			m_vPos += m_vPosUp;
			// ＰＣとのあたり判定
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;
		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			m_pGMain->m_pSeHit->Play();  // ダメージ効果音
			break;
		case  DEAD:
			m_nCnt1--;
			// DEADになり、一定時間たったら表示を消す
			if (m_nCnt1 <= 0)
			{
				m_pGMain->SilverS += 1; // M.S 銀箔の取得数を+1
				m_bActive = FALSE;
				// M.S 赤色の敵のスプライトに戻す
				m_pSprite = new CSprite(m_pGMain->m_pImageChar, 384, 0, 64, 64);
				m_nAnimNum = 2;  // M.S アニメーション数を戻す
			}
			else {
				m_nAnimNum = 1;  // M.S 取得アイテムの表示はアニメーションなしなので1
				// M.S 取得アイテムの画像に変える
				m_pSprite = new CSprite(m_pGMain->m_pImageSpriteS, 0, 0, 48, 48);
				FlashCountup();
			}
			break;
		}
		AnimCountup();
		Draw();
	}
}
// ===================================================================================================
//------------------------------------------------------------------------
//
//	緑の敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmFoxProc::CEnmFoxProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_FOX_MAX; i++)				//←
	{
		m_pObjArray.push_back(new CEnmFoxObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}
// ---------------------------------------------------------------------------
//
// 緑の敵プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmFoxProc::Update()
{
	VECTOR2 vPos;
	int  nNext;
	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索 (EvtID:3 敵の出現位置, EvtNo:0x08 緑の敵)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x08, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

	}
	m_nStartFlag = 1;  // 一回発させたら、もう発生しない
//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
}
//------------------------------------------------------------------------
//
//	緑の敵オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmFoxObj::CEnmFoxObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S 緑の敵のスプライト
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 512, 0, 64, 64);		
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 6;						
	m_nAtc = 2;							

}
// ---------------------------------------------------------------------------
//
// 緑の敵オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmFoxObj::~CEnmFoxObj()
{
	SAFE_DELETE(m_pSprite);
}
// M.S 引数を0～2の数にする
// 引  数：int   num   numから0～2の数を出す
// 戻り値：int   anum  0～2に変えた数
int	CEnmFoxObj::RandomNumAns(int num) {
	int anum = num % 3;
	return anum;
}
//-----------------------------------------------------------------------------
// 緑の敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL CEnmFoxObj::Start(VECTOR2 vPos)
{	
	srand(time(NULL));  // M.S 乱数の初期化
	num = rand() % 10;  // M.S 乱数の取得、0~9の整数を得る
	returnNum = RandomNumAns(num); // M.S numを0～2の数に変える	
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;	// M.S 反対向き
	m_vPos = vPos;	    // 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
//緑の敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmFoxObj::Update()
{
	if (returnNum == 0) {
		CMapLine*  pHitmapline = NULL;
		float fSpeed = 1;
		BOOL bRet;
		if (m_bActive)
		{
			m_vPosUp = VECTOR2(0, 0);

			switch (m_dwStatus)
			{
			case  FLASH:
				m_nCnt1--;
				if (m_nCnt1 <= 0) {
					ResetStatus();
					ResetAnim();
				}
				else {
					FlashCountup();
				}		// break;を入れずそのまま　NORMAL　の処理を行う
			case  NORMAL:
				switch (m_dwStatusSub)
				{
				case  WALK:
					// 自由移動の処理
					if (m_nDirIdx == RIGHT)
					{
						m_vPosUp.x = fSpeed;
					}
					else {
						m_vPosUp.x = -fSpeed;
					}
					// マップ線との接触判定と適切な位置への移動
					bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
					if (!bRet || (pHitmapline && pHitmapline->m_vNormal.y > -0.99f))
					{
						// マップ線の端に来たので左右反転
						if (m_nDirIdx == RIGHT)
						{
							m_nDirIdx = LEFT;
							m_vPosUp.x = -fSpeed;
							m_vPosUp.y = 0;
						}
						else {
							m_nDirIdx = RIGHT;
							m_vPosUp.x = fSpeed;
							m_vPosUp.y = 0;
						}
					}
					break;
				}
				// 増分
				m_vPos += m_vPosUp;
				// ＰＣとのあたり判定
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				break;
			case  DAMAGE:
				m_nHp -= m_pOtherObj->GetAtc();
				if (m_nHp <= 0) {
					m_dwStatus = DEAD;
					m_nCnt1 = 180;
				}
				else {
					m_dwStatus = FLASH;
					m_nCnt1 = 60;
				}
				m_pGMain->m_pSeHit->Play();  // ダメージ効果音
				break;
			case  DEAD:
				m_nCnt1--;
				// DEADになり、一定時間たったら表示を消す
				if (m_nCnt1 <= 0)
				{
					m_pGMain->GoldS += 1;  // M.S 金箔の取得数を+1
					m_bActive = FALSE;
					// M.S 緑の敵のスプライトに戻す
					m_pSprite = new CSprite(m_pGMain->m_pImageChar, 512, 0, 64, 64);
					m_nAnimNum = 2; // M.S アニメーション数を戻す
				}
				else {
					m_nAnimNum = 1;  // M.S 取得アイテムの表示はアニメーションなしなので1
					// M.S 取得アイテムの画像に変える
					m_pSprite = new CSprite(m_pGMain->m_pImageSpriteS, 0, 0, 48, 48);
					FlashCountup();
				}
				break;
			}
			AnimCountup();
			Draw();
		}	
    }
}	
//------------------------------------------------------------------------
//
//	ドッスンの敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmDosProc::CEnmDosProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_DOS_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmDosObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}
// ---------------------------------------------------------------------------
//
// ドッスンの敵プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmDosProc::Update()
{
	VECTOR2 vPos;
	int nNext;

	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップ (EvtID:3　敵の出現位置, EvtNo:0x2000 ドッスンの敵)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x2000, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
}
//------------------------------------------------------------------------
//
//	ドッスンの敵オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmDosObj::CEnmDosObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S ドッスンの敵のスプライト
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 1024, 0, 64, 64);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 10000;
	m_nAtc = 1;
}
// ---------------------------------------------------------------------------
//
// ドッスンの敵オブジェクトのデストラクタ
//	// ---------------------------------------------------------------------------
CEnmDosObj::~CEnmDosObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ドッスンの敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmDosObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// ドッスンの敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmDosObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1;
	BOOL bRet;
	int am = 0;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;を入れずそのまま　NORMAL　の処理を行う
		case  NORMAL:
			m_vPosUp.x = 0;
			m_vPosUp.y = 0;
			m_nDirIdx = RIGHT;
			bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			// 増分
			m_vPos += m_vPosUp;
			// ＰＣとのあたり判定
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;
		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
				m_pGMain->m_pSeHit->Play();  // ダメージ効果音
				m_pGMain->henk = 1;  // M.S プレイキャラとの接触フラグをたてる
				break;
			}
		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
			}
			else {
				FlashCountup();
			}
			break;
		}
	}
	AnimCountup();
	Draw();
}
//------------------------------------------------------------------------
//
//	ボスの敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmKingProc::CEnmKingProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_KING_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmKingObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}
// ---------------------------------------------------------------------------
//
// ボスの敵プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmKingProc::Update()
{
	VECTOR2 vPos;
	int nNext;
	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップ ( EvtID:3　敵の出現位置, EvtNo:0x40　ボス)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x40, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
}
//------------------------------------------------------------------------
//
//	ボスの敵オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmKingObj::CEnmKingObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S ボスの敵のスプライト
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 768, 0, 64, 64);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 6;
	m_nAtc = 3;
}
// ---------------------------------------------------------------------------
//
// ボスの敵オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmKingObj::~CEnmKingObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ボスの敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmKingObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;
	m_pGMain->m_nEShotWait = eWaitNum;

	return TRUE;
}
//-----------------------------------------------------------------------------
// ボスの敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmKingObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1;
	BOOL bRet;
	VECTOR2 vPcPos;
	// M.S プレイキャラの位置の取得
	vPcPos.x = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().x;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;を入れずそのまま　NORMAL　の処理を行う
		case  NORMAL:
			switch (m_dwStatusSub)
			{
			case  WALK:
				// 自由移動の処理
				// M.S プレイキャラと自分の位置を取得し、プレイキャラの方向に向かう
				if (m_vPos.x > vPcPos.x)   // M.S 自分のX位置の方が大きい場合
				{
					m_nDirIdx = LEFT;      // M.S 左方向へ向かう
					m_vPosUp.x = -fSpeed;
				}
				else { // M.S 自分のX位置の方が小さい場合
					m_nDirIdx = RIGHT;     // M.S 右方向へ向かう
					m_vPosUp.x = fSpeed;
				}
				// マップ線との接触判定と適切な位置への移動
				bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
				if (!bRet || (pHitmapline && pHitmapline->m_vNormal.y > -0.99f))
				{
					// マップ線の端に来たので左右反転
					if (m_nDirIdx == RIGHT)
					{
						m_vPosUp.y = 0;
					}
					else {
						m_vPosUp.y = 0;
					}
					break;
				}
			}
			// M.S 敵からPCに向かって弾を発射
			// M.S 処理の軽量化のため画面外の場合は発射しない
			if (eWaitNum <= 0) {
				if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH) {
				}
				else {
					m_pGMain->m_pWeaponProc->m_pEWeaponShotProc->Start(m_vPos + VECTOR2(20, 20), this, ENM);
					eWaitNum = 40;  // M.S 発射待ち時間の初期化
				}
			}
			if (eWaitNum > 0) {
				eWaitNum--;
			}
			// 増分
			m_vPos += m_vPosUp;
			// ＰＣとのあたり判定
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;
		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			m_pGMain->m_pSeHit->Play();  // ダメージ効果音
			break;
		case  DEAD:
			m_nCnt1--;
			// DEADになり、一定時間たったら表示を消す
			if (m_nCnt1 <= 0)
			{
				m_pGMain->VisionS += 1;  // M.S 幻の砂糖の取得数を+1
				m_bActive = FALSE;
				// M.S ボスのスプライトに戻す
				m_pSprite = new CSprite(m_pGMain->m_pImageChar, 768, 0, 64, 64);
				m_nAnimNum = 2;  // M.S アニメーション数を戻す
			}
			else {
				m_nAnimNum = 1;  // M.S 取得アイテムの表示はアニメーションなしなので1
				// M.S 取得アイテムの画像に変える
				m_pSprite = new CSprite(m_pGMain->m_pImageSpriteV, 0, 0, 48, 48);
				FlashCountup();
			}
			break;
		}
	}
	AnimCountup();
	Draw();
}
//------------------------------------------------------------------------
//
//	水鳥のプロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmSkyProc::CEnmSkyProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_SKY_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmSkyObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}
// ---------------------------------------------------------------------------
//
//  水鳥のプロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmSkyProc::Update()
{
	VECTOR2 vPos;
	int nNext;

	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップ (EvtID:3　敵の出現位置, EvtNo:0x80 水鳥)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x80, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている
}
//------------------------------------------------------------------------
//
//	水鳥のオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmSkyObj::CEnmSkyObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S 水鳥のスプライト
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 1152, 0, 64, 64);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 10000;
	m_nAtc = 0;

}
// ---------------------------------------------------------------------------
//
//  水鳥のオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmSkyObj::~CEnmSkyObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 水鳥のオブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmSkyObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// 水鳥のオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmSkyObj::Update()
{
	CMapLine* pHitmapline = NULL;
	bool bRet = false;
	bool hitCheck = false;
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->ints = 0; // M.S intsの初期化 
			// M.S プレイキャラとの当たり判定を調べる
			hitCheck = m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			// マップ線との接触判定と適切な位置への移動		
		case  DAMAGE:
			if (bRet == true) {  // M.S 各ステージで話す言葉を変える
				// M.S 表示文字を変えるためにそのステージによってintsに値を入れる
				if (m_pGMain->m_pMapProc->m_nMapNo == 0 && hitCheck == true) {
					m_pGMain->ints = 1;
				}
				else if (m_pGMain->m_pMapProc->m_nMapNo == 1 && hitCheck == true) {
					m_pGMain->ints = 2;
				}
				else if (m_pGMain->m_pMapProc->m_nMapNo == 2 && hitCheck == true) {
					m_pGMain->ints = 3;
				}
				else if (m_pGMain->m_pMapProc->m_nMapNo == 3 && hitCheck == true) {
					m_pGMain->ints = 4;
				}
				else if (m_pGMain->m_pMapProc->m_nMapNo == 4 && hitCheck == true) {
					m_pGMain->ints = 5;
				}
			}
			m_dwStatus = NORMAL;
			break;
		case  DEAD:
			m_dwStatus = NORMAL;
			break;
		}
		AnimCountup();
		Draw();
	}
}
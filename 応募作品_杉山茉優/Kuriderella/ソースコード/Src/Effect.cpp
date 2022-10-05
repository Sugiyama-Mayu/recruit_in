//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		映像効果の処理
//																Effect.cpp
//=============================================================================

#include "Effect.h"
#include "Playchar.h"
#include "Map.h"
#include <stdio.h>
#include <string>

//------------------------------------------------------------------------
//
//	映像効果メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEffectBomProc = new CEffectBomProc(m_pGMain);	// 映像効果・爆発プロシージャ
	m_pProcArray.push_back(m_pEffectBomProc);     // プロシージャをプロシージャ配列に登録する

	m_pItemProc = new CItemProc(m_pGMain);				// アイテムプロシージャ
	m_pProcArray.push_back(m_pItemProc);		// プロシージャをプロシージャ配列に登録する
}
//============================================================================
//   プロシージャとオブジェクトを探索し全てのオブジェクトをノンアクティブにする
//   プロシージャの開始フラグをリセットする
//============================================================================
void  CEffectProc::SetNonActive()
{
	//オブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive( FALSE);
	}

	// 下位のプロシージャポインタ配列の探索
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag(0);				// 開始フラグのリセット
		((CEffectProc*)m_pProcArray[i])->SetNonActive();      // 下位のプロシージャの処理（再帰処理）
	}
}
// ================================================================================================================================
// 
// 各映像効果プロシージャ毎の処理
// 
// ================================================================================================================================

//------------------------------------------------------------------------
//
//	映像効果・爆発プロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEffectBomProc::CEffectBomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_BOM_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectBomObj(m_pGMain));	// m_pObjArrayに映像効果・爆発オブジェクトを生成する
	}

}
//-----------------------------------------------------------------------------
// 映像効果・爆発プロシージャの開始
//
//   VECTOR2 vPos    発生位置
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CEffectBomProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive() )
		{
			m_pObjArray[i]->Start(vPos);	// 映像効果・爆発の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}

//------------------------------------------------------------------------
//
//	映像効果・爆発オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEffectBomObj::CEffectBomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 144, 480, 64, 64);
	m_nAnimNum = 7;
}
// ---------------------------------------------------------------------------
//
// 映像効果・爆発オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEffectBomObj::~CEffectBomObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 映像効果・爆発オブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectBomObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_dwStatus = NORMAL;
	m_dwStatusSub = STOP;
	m_dwStatusPhase = 0;

	m_vPos = vPos;	// 発生位置

	m_nAnimIdx = 0;

	return TRUE;
}
//-----------------------------------------------------------------------------
// 映像効果・爆発オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEffectBomObj::Update()
{
	if (m_bActive)
	{
		if (AnimCountup() == 1)
		{
			m_bActive = FALSE;
		}
		Draw();

	}
}
// ==============================================================================================================

// =================================================================================
//------------------------------------------------------------------------
//
//	アイテムプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CItemProc::CItemProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CItemObj(m_pGMain));	// m_pObjArrayにアイテムを生成する
	}
	m_nStartFlag = 0;
}
// M.S 回復のアイテムの発生
//引  数：発生位置
//戻り値：なし
void	CItemProc::RaiseResque(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMRESQUE);
			break;
		}
	}	
}
// M.S ドア(出口)の発生
//引  数：発生位置
//戻り値：なし
void	CItemProc::RaiseDoor(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMDOOR);
			break;
		}
	}
}
// M.S 銀箔の発生
//引  数：発生位置
//戻り値：なし
void	CItemProc::RaiseSilver(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMSILVER);
			break;
		}
	}
}
// M.S 金箔の発生
//引  数：発生位置
//戻り値：なし
void	CItemProc::RaiseGold(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMGOLD);
			break;
		}
	}
}
// M.S 幻の砂糖の発生
//引  数：発生位置
//戻り値：なし
void	CItemProc::RaiseVision(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMVISION);
			break;
		}
	}
}
// M.S おせちドア(ゴール)の発生
//引  数：発生位置
//戻り値：なし
void	CItemProc::RaiseOseti(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMOSETI);
			break;
		}
	}
}
// M.S 強化武器発生
//引  数：発生位置
//戻り値：なし
void	CItemProc::RaiseSt(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMST);
			break;
		}
	}
}
//-----------------------------------------------------------------------------
// アイテムプロシージャの開始
//
//   戻り値　　なし
//-----------------------------------------------------------------------------
void	CItemProc::Update()
{
	VECTOR2 vPos;
	int  nNext;
	if (m_nStartFlag == 0) // 発生させていかどうか
	{
		// イベントマップを探索し、回復を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索 (EvtID:2 アイテムの出現位置, EvtNo:0x10 回復)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x10, vPos, nNext))
			{
				RaiseResque(vPos);
			}
		}
		// イベントマップを探索し、ドア(出口)を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索 (EvtID:2 アイテムの出現位置,EvtNo:0x20 ドア)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x20, vPos, nNext))
			{
				RaiseDoor(vPos);
			}
		}		
		// M.S イベントマップを探索し,銀箔を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// M.S イベントマップの探索 (EvtID:2 アイテムの出現位置, EvtNo:0x100 銀箔)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x100, vPos, nNext))
			{
				RaiseSilver(vPos);
			}
		}
		// M.S イベントマップを探索し,金箔を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// M.S イベントマップの探索 (EvtID:2 アイテムの出現位置, EvtNo:0x200 金箔)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x200, vPos, nNext))
			{
				RaiseGold(vPos);
			}
		}
		// M.S イベントマップを探索し,幻の砂糖を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// M.S イベントマップの探索 (EvtID:2 アイテムの出現位置, EvtNo:0x400 幻の砂糖)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x400, vPos, nNext))
			{
				RaiseVision(vPos);
			}
		}
		// M.S イベントマップを探索し,おせちドア(ゴール)を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索 (EvtID:2 アイテムの出現位置, EvtNo:0x800 おせちドア（ゴール))
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x800, vPos, nNext))
			{
				RaiseOseti(vPos);
			}
		}
		// M.S イベントマップを探索し,おせちドア(ゴール)を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// M.S イベントマップの探索(EvtID:2 アイテムの出現位置, EvtNo:0x1000 強化武器)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x1000, vPos, nNext))
			{
				RaiseSt(vPos);
			}
		}
		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
}

//------------------------------------------------------------------------
//
//	アイテムオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CItemObj::CItemObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite);  // アイテムスプライトのスプライトを作る
	m_nAnimNum = 1;

}
// ---------------------------------------------------------------------------
//
// アイテムオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CItemObj::~CItemObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// アイテムオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   DWORD       dwNo    アイテム種別
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CItemObj::Start(VECTOR2 vPos, DWORD dwNo)
{
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_dwStatusSub = dwNo;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	// スプライトの情報のセット
	switch (m_dwStatusSub)
	{
	case  ITEMRESQUE: // M.S 回復
		m_pSprite->SetSrc(0, 0, 48, 48); 	
		break;
	case  ITEMDOOR:   // M.Sドア
		m_pSprite->SetSrc(240, 0, 48, 48); 
		break;

	case ITEMVISION:  // M.S 幻の砂糖
		m_pSprite->SetSrc(144, 0, 48, 48);
		break;

	case ITEMGOLD:    // M.S 金箔
	case ITEMSILVER:  // M.S 銀箔
		m_pSprite->SetSrc(96, 0, 48, 48);
		break;

	case ITEMOSETI:   // M.S おせちドア（ゴール）
		m_pSprite->SetSrc(192, 0, 48, 48);
		break;
		
	case ITEMST:      // M.S 強化
		m_pSprite->SetSrc(48, 0, 48, 48);
	}

	return TRUE;
}
//-----------------------------------------------------------------------------
// アイテムオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CItemObj::Update()
{
	if (!m_bActive) {
		return;
	}
	if (isCollision(m_pGMain->m_pPcProc->GetPcObjPtr())) // PCとの接触判定
	{
		switch (m_dwStatusSub)
		{
		case  ITEMRESQUE:     // 回復
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetHp(m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp());
			m_pGMain->m_pSePower->Play();
			m_bActive = FALSE;
			break;
		case  ITEMDOOR:      // ドア
			// M.S タスクを完了しているか見る
			if ((m_pGMain->henk == 1) && (m_pGMain->m_pMapProc->m_nMapNo == 0)) {
				doorN = 1;
			}
			if ((m_pGMain->henk == 1) && (m_pGMain->hank == 1)) {
				keyN = 1;
			}
			if ((keyN == 1) && (m_pGMain->m_pMapProc->m_nMapNo == 1)) {
				secondN = 1;
			}
			 // M.S 進化してからでないと、ドアを通れない
			if ((doorN == 1) || (secondN == 1) || (m_pGMain->m_pMapProc->m_nMapNo == 2)
				|| (m_pGMain->m_pMapProc->m_nMapNo == 3) || (m_pGMain->m_pMapProc->m_nMapNo == 4)) {
				if ((m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp() >= 1) && (m_pGMain->m_pPcProc->GetPcNum() >= 0)) {
					m_pGMain->m_pSePower->Play();
					m_pGMain->m_pMapProc->MoveMap();
					m_pGMain->m_pPcProc->AddPcNum(1);
					m_bActive = FALSE;
					doorN = 0;
					secondN = 0;
					if (m_pGMain->m_pPcProc->GetPcNum() > 2) {  // M.S 残機が2(MAX)より多かったら-1
						m_pGMain->m_pPcProc->AddPcNum(-1);
					}
				}
			}
			break;
		case ITEMSILVER:  // M.S 銀箔
			m_pGMain->m_pSePower->Play();
			m_pGMain->SilverS += 1;
			m_bActive = FALSE;
			break;
		case ITEMGOLD:    // M.S 金箔
			m_pGMain->m_pSePower->Play();
			m_pGMain->GoldS += 1;
			m_bActive = FALSE;
			break;
		case ITEMVISION:   // M.S 幻の砂糖
			m_pGMain->m_pSePower->Play();
			m_pGMain->VisionS += 1;
			m_bActive = FALSE;
			break;
		case  ITEMOSETI:   // M.S おせちドア（ゴール）
			m_pGMain->m_dwGameStatus = GAMECLEAR;
			m_pGMain->CR = 1;
			m_pGMain->m_pSePower->Play();
			m_pGMain->m_pPcProc->AddPcNum(1);
			if (m_pGMain->m_pPcProc->GetPcNum() > 2) {  // M.S 残機が2(MAX)より多かったら-1
				m_pGMain->m_pPcProc->AddPcNum(-1);
			}
			m_bActive = FALSE;
			break;
		case ITEMST:   			// M.S アイテム購入の追加：強化武器
			m_pGMain->transactionW = true; // M.S 最初の話
			if (pDI->CheckKey(KD_DAT, DIK_E)) {
				if ((m_pGMain->GoldS >= 1) && (m_pGMain->SilverS >= 5)) { // M.S 買えた時
					m_pGMain->m_pSePower->Play();
					m_pGMain->strongSSw = true;
					m_pGMain->textStr = 1;
					m_pGMain->GoldS -= 1;
					m_pGMain->SilverS -= 5;
					m_pGMain->stS = 1;
					m_bActive = false;
				}
				else if (m_pGMain->textStr != 1) {  // M.S 買えなかったとき
					m_pGMain->textStr = 2;
				}
			}
			break;
		}
	}
	// M.S 武器強化シーン 離れたら最初に戻し、コメント消す
	else if ((!isCollision(m_pGMain->m_pPcProc->GetPcObjPtr())) && (m_pGMain->textStr != 1)) {  
			m_pGMain->transactionW = false;
			m_pGMain->textStr = 0;
	}
	// M.S 武器強化シーン 買った後のコメントを一定時間で消す
	if ((m_pGMain->textStr == 1) && (m_pGMain->transactionW == true)) {  
		m_pGMain->timekon++;    // M.S コメント表示時間カウントを足す
		if (m_pGMain->timekon > 80) {
			m_pGMain->transactionW = false;
		}
	}
	AnimCountup();
	Draw();
}



//=============================================================================
//		２Ｄアクションゲームプログラム
//		Ｃ２ＤＡｃｔ１１４　　　　　　           ver 2.8        2020.2.15
//
//		プレイキャラクターの処理
//																Playchar.cpp
//=============================================================================

#include "Playchar.h"
#include "Weapon.h"
#include "Effect.h"
#include "Map.h"

//------------------------------------------------------------------------
//
//	ＰＣプロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pPcObj = new CPcObj(m_pGMain);
	m_pObjArray.push_back(m_pPcObj);  // m_pObjArrayにオブジェクトを登録する

	m_nMaxPcNum  = m_nPcNum = 2;
}
// ===========================================================================
//------------------------------------------------------------------------
//
//	ＰＣオブジェクトのコンストラクタ	
//
//  引数　CGameMain* pGMain
//
//------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// いが栗(初期)のスプライト
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 0, 0, 64, 64);

	m_vPos = VECTOR2(48, 721 );
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_nDirIdx = RIGHT;
	m_nHp = m_nMaxHp = 3;
	m_nMaxMp = m_nMp = 900;
	m_nAtc = 1;

	m_nShotWait = 0;
}
// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj()
{
	SAFE_DELETE(m_pSprite);
}
//M.S プレイキャラの状態変化の処理
//引  数：なし
//戻り値：なし
void CPcObj::ChangeStatePC() {
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
		m_nMp += 5;  // Mpの自然増加
		if (m_nMp >= m_nMaxMp) {
			m_nMp = m_nMaxMp;
		}
		if (m_pGMain->henk == 1) {
			// M.S 栗のスプライトに変更
			m_pSprite = new CSprite(m_pGMain->m_pImageChar, 128, 0, 64, 64);
		}
		if (m_pGMain->hank == 1 && m_pGMain->henk == 1) {
			// M.S 栗きんとんのスプライトに変更
			m_pSprite = new CSprite(m_pGMain->m_pImageChar, 256, 0, 64, 64);
		}
		break;
	case DAMAGE:
		if (m_pOtherObj->GetAtc() > 0)
		{
			m_nHp -= m_pOtherObj->GetAtc();	// 攻撃を受けたダメージ
			if (m_nHp <= 0)
			{
				m_nHp = 0;
				m_dwStatus = DEAD;		// HPが０なので死亡へ
				m_nCnt1 = 180;			// 死亡フラッシュ中の時間設定
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
		}
		else {
			m_dwStatus = NORMAL;  // 攻撃力なしのときはすぐにNORMALに戻る
		}
		break;
	case DEAD:
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_pGMain->m_pPcProc->AddPcNum(-1);	// ＰＣを一人減らす
			if (m_pGMain->m_pPcProc->GetPcNum() <= 0)	// ＰＣがなくなったのでゲームオーバー
			{
				m_pGMain->m_dwGameStatus = GAMEOVER;
			}
			else {
				m_nHp = m_nMaxHp;
				ResetStatus();
				ResetAnim();
			}
		}
		else {
			FlashCountup();
		}
		break;
	}
}
//-----------------------------------------------------------------------------
// ＰＣオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed     = 5;
	float fJumpPlus  = 4;

	if (!m_bActive) return;
	m_vPosUp = VECTOR2(0, 0);

	ChangeStatePC(); //M.S プレイキャラの状態変化の処理

	// プレイキャラの移動処理
	switch (m_dwStatusSub)
	{
	case  WALK:		// 歩行中の処理
		if (pDI->CheckKey(KD_DAT, DIK_RIGHT))//→キー
		{
			m_vPosUp.x = fSpeed;
			m_nDirIdx = RIGHT;
		}
		if (pDI->CheckKey(KD_DAT, DIK_LEFT))//←キー
		{
			m_vPosUp.x = -fSpeed;
			m_nDirIdx = LEFT;
		}
		// ジャンプ開始
		if (pDI->CheckKey(KD_DAT, DIK_SPACE))//スペースキー
		{	
			m_dwStatusSub = JUMP;
			m_vJumpSpeed.x = m_vPosUp.x;
			m_vJumpSpeed.y = -(fSpeed*2.5 + fJumpPlus);
			m_fJumpTime = 0;
			m_vPosUp.y = m_vJumpSpeed.y;
		}
		else {// 自然落下
			if (pDI->CheckKey(KD_DAT, DIK_DOWN))//↓キー
			{
				m_vPosUp.y = fSpeed;
			}
			else {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = fSpeed / 2;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
			}
		}
		break;
	case  JUMP:		// ジャンプ中の処理
		if (pDI->CheckKey(KD_DAT, DIK_RIGHT))//→キー
		{
			m_vJumpSpeed.x = fSpeed;
			m_nDirIdx = RIGHT;
		}
		if (pDI->CheckKey(KD_DAT, DIK_LEFT))//←キー
		{
			m_vJumpSpeed.x = -fSpeed;
			m_nDirIdx = LEFT;
		}
		m_fJumpTime++;
		m_vPosUp.x = m_vJumpSpeed.x;
		m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
		break;
	}
	// ショットの発射
	if (pDI->CheckKey(KD_DAT, DIK_A))
	{
		if (m_nShotWait <= 0 && m_nMp >= 300) 
		{
			m_pGMain->m_pWeaponProc->m_pWeaponShotProc->
				Start(m_vPos+VECTOR2(20, 20), this, PC);
			m_nShotWait = 10;    // 武器発射のウェイトを掛ける
			m_nMp -= 300;        // M.S MPを減らす
			if (m_nMp < 0) {    
				m_nMp = 0;
			}
		}
	}
	if (m_nShotWait > 0) m_nShotWait--;    // 武器発射のウェイトをカウントダウン

	// マップ線との接触判定と適切な位置への移動
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// マップ線が垂直まではＯＫ
		{
			m_dwStatusSub = WALK;	// マップ線に接触しているときは、ジャンプを歩行に戻す
			m_fJumpTime = 0;
			m_vJumpSpeed.x = m_vJumpSpeed.y = 0;
		}
	}
	// 増分計算
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();
}

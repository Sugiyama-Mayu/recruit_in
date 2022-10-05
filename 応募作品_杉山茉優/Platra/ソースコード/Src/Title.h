//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１２　　　　　　                 ver 3.0        2021.1.11
//		タイトル　ヘッダファイル							Title.h
//=============================================================================
#pragma once

#include "GameMain.h"


// --------------------------------------------------------------------
// タイトル　プロシージャクラス
//// --------------------------------------------------------------------
class CTitleProc
{
public:
	CGameMain*		m_pGMain;
	// 使用するイメージ
	CSpriteImage*   m_pImageTitle;
	CSpriteImage*   m_pImageClear;
	CSpriteImage*   m_pImageOver;
	CSprite*        m_pSprite;
	CSpriteImage*   m_pImageSelect;
	CSpriteImage*   m_pImageOption;
	// M.S 操作説明ページ 
	CSpriteImage*   m_pImagePage1;
	CSpriteImage*   m_pImagePage2;
	CSpriteImage*   m_pImagePage3;
	CSpriteImage*   m_pImagePage4;
	CSpriteImage*   m_pImagePage5;
	CSpriteImage*   m_pImagePage6;
	CSpriteImage*   m_pImagePage7;
	CSpriteImage*   m_pImagePage8;
	// M.S 操作説明ページ移動ボタン
	CSpriteImage*   m_pImagePageButton;
	// M.S オプション画面
	CSpriteImage*   m_pImageOptionNum;
	CSpriteImage*   m_pImageOptionBackButton;
	// M.S リザルト画面
	CSpriteImage*   m_pImageResult;
	CSpriteImage*   m_pImageRanking;
	// M.S セーブ注意表示
	CSpriteImage*   m_pImageSaveWarning;
	CSpriteImage*   m_pImageNoSave;
	// M.S あそびかた、ランキング確認ボタン
	CSpriteImage*   m_pImageGreenButton;

	DWORD           m_dwCntTime;
	DWORD           m_dwStatusPhase;
public:
	void Title();
	bool TitleTitle();
	void GameClear();
	void GameOver();
	bool CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight);
	CTitleProc(CGameMain* pGMain);	// コンストラクタ
	~CTitleProc();

	// M.S タイトルセレクト画面
	bool TitleSelect();
	// M.S あそびかた画面
	bool TitleExplanation();
	// M.S オプション画面
	bool TitleOption();
	// M.S プログラムで使用する数字をオプション画面で設定した数字へ変換
	void ChangeSelect();
	// M.S ランキング確認画面
	void DrawRanking();

	// M.S オプション画面で設定した数字をプログラムで使用する数字に変換
	void ChangeSelectNum(int bgmOrSeNum);
	// M.S オプション画面のボタンの選択処理
	void DrawSelectNum(bool judgeRange, int selectKind);
	// M.S はじめからを選択した時のセーブデータがあると知らせる注意表示
	bool DrawSaveWarning();
	// M.S つづきからを選択した時のセーブデータがないと知らせる注意表示
	void DrawNoSaveDataWarning();
	// M.S あそびかたボタンとランキング確認ボタンの表示、選択処理
	bool DrawHowToPlayRanking();
	// M.S オプション画面の線路数ボタン数字の表示、選択処理
	void SelectLineNum(bool judgeRange, int selectKind, int i);
	// M.S オプション画面の乗車人数ボタン数字の表示、選択処理
	void SelectPassengersNum(bool judgeRange, int selectKind, int i);
	// M.S オプション画面の発射までの待ち時間ボタン数字の表示、選択処理
	void SelectWaitTime(bool judgeRange, int selectKind, int i);
	// M.S オプション画面のBGM音量ボタン数字の表示、選択処理
	void SelectBgm(bool judgeRange, int selectKind, int i);
	// M.S オプション画面のSE音量ボタン数字の表示、選択処理
	void SelectSe(bool judgeRange, int selectKind, int i);
    void DrawExplanationPage(int nowPage); 	// M.S あそびかた画面の選択中ページの表示
	// M.S 通常モードのスコアの表示(画像から表示させる)
	void DrawManScoreNormalMode();
	// M.S ランキングモードのスコアの表示(画像から表示させる)
	void DrawManScoreRankingMode();
	void DrawTotalScore();  // M.S トータルスコアの表示(画像から表示させる)
	void SortRanking();     // M.S ランキングの並べかえ
	void AddRanking();  	// M.S ランキングの追加、表示

	int nTitleSelect;
	int linetrainNum;  // M.S 線路の選択数字
	int passengersNum; // M.S 乗車人数の選択数字
	int waitingTime;   // M.S 待ち時間の選択数字
	int bgmNum;        // M.S BGM音量の選択数字
	int seNum;         // M.S SE音量の選択数字
	int lineTrainSelect;     // M.S 線路の選択決定数字
	int passengersSelect;    // M.S 乗車人数の選択決定数字
	int waitingTimeSelect;  // M.S 待ち時間の選択決定数字
	int bgmSelect;          // M.S BGM音量の選択決定数字
	int seSelect ;           // M.S SE音量の選択決定数字
	int selectedKindNum;     // M.S オプション画面のボタンの列の数字

	int rankingTime;         // M.S ランキング画面のタイムカウント
	int myRanking;           // M.S 自分のランキング
	int totalScore;          // M.S トータルスコア
	bool initialRankingSorting;  // M.S 1度のみランキング並び替えフラグ
	int totalHighManScore;       // M.S 人(赤)の乗車人数スコア
	int totalMiddleManScore;     // M.S 人(黄)の乗車人数スコア
	int totalLowManScore;        // M.S 人(青)の乗車人数スコア
	bool ScoreWriteProcess;  // M.S ファイル書き込みフラグ
	bool saveWarningFlag;    // M.S セーブデータある注意フラグ
	bool noSaveFlag;         // M.S セーブデータない注意フラグ
   int nowPage;                  // M.S 操作説明で選択中のページ

	int gameClearCount;          // M.S ゲームクリアタイムカウント
	int gameOverCount;           // M.S ゲームオーバータイムカウント
    // M.S ゲームクリアの初期サウンド処理
	bool RingSound;   // M.S ゲームクリア、ゲームオーバーサウンド
	bool RingResultSound;  // M.S リザルトサウンド
};

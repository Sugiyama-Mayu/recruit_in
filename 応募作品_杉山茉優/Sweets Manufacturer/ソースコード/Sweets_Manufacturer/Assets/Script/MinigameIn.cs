using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;
// M.S
// ミニゲームの発生処理
public class MinigameIn : MonoBehaviour
{
    public GameObject minigame;   // 発生させるミニゲーム
    public GameObject honntai;    //レーンを流れてるもの
    public GameObject nextSweets; // 次に流すお菓子
    private bool doneMiniGame;    // ミニゲームの発生済みフラグ
    public GameObject minigames;  // ミニゲームを集めたオブジェクト
    public ClickObject clickObject; // プレイヤー挙動スクリプト

    // チョコクラッカーゲームのクラッカーオブジェクト
    public DragDrop cracker1;
    public DragDrop cracker2;
    public DragDrop cracker3;
    public DragDrop cracker4;
    public DragDrop cracker5;
    public DragDrop cracker6;
    public DragDrop cracker7;
    public DragDrop cracker8;
    // ゼリーゲームのオレンジオブジェクト
    public MoveOrange orange1;
    public MoveOrange orange2;
    public MoveOrange orange3;
    public MoveOrange orange4;
    public MoveOrange orange5;
    public MoveOrange orange6;
    // クッキーゲームの型抜き穴オブジェクト
    public CutOutColl cookieCut1;
    public CutOutColl cookieCut2;
    public CutOutColl cookieCut3;
    public CutOutColl cookieCut4;
    // クッキーゲームマネージャーのスクリプト
    public MoveCutOut cookieMana;
    // ベルトコンベアのオブジェクト
    public belt belt1;
    public belt belt2;
    public belt belt3;
    public belt belt4;
    public belt belt5;
    public belt belt6;
    public belt belt7;
    public belt belt8;
    // ミニゲーム管理オブジェクト
    public MinigameIn onlyMinigameIn;
    // ゲーム中に別のゲームを発生させないためのフラグ
    //  ミニゲーム管理オブジェクトで使用
    public bool duringPlay;
    // ステージ数
    public int sceneNum;
    // ミニゲームの最初に表示するゲーム説明テキスト
    public GameObject miniGameText;
    // ミニゲームの終了フラグ
    private bool miniGameResult;
    void Start()
    {
        // 初期化
        miniGameResult = false;
        duringPlay = false;
        doneMiniGame = false;
    }
    // ミニゲームの発生コルーチン
    public IEnumerator MinigameTimer(string tag)
    {
        // ミニゲームが発生済みでなく、ミニゲーム中でないかどうか
        if (doneMiniGame == false && onlyMinigameIn.duringPlay == false)
        {
            // チョコクラッカーゲームかどうか
            if(tag == "ChocoHarden")
            {
                // チョコクラッカーゲームの初期化フラグをtrue
                cracker1.startCracker = true;
                cracker2.startCracker = true;
                cracker3.startCracker = true;
                cracker4.startCracker = true;
                cracker5.startCracker = true;
                cracker6.startCracker = true;
                cracker7.startCracker = true;
                cracker8.startCracker = true;
            }
            // ゼリーゲームかどうか
            if (tag == "OrangeJelly")
            {
                // ゼリーゲームの初期化フラグをtrue
                orange1.startFlag = true;
                orange2.startFlag = true;
                orange3.startFlag = true;
                orange4.startFlag = true;
                orange5.startFlag = true;
                orange6.startFlag = true;
            }
            // クッキーゲームかどうか
            if (tag == "DoughCookie")
            {
                // クッキーゲームの初期化フラグをtrue
                cookieCut1.startFlag = true;
                cookieCut2.startFlag = true;
                cookieCut3.startFlag = true;
                cookieCut4.startFlag = true;
                cookieMana.startFlag = true;
            }
            onlyMinigameIn.duringPlay = true; // ミニゲーム中フラグをtrue
            // オブジェクトを追いかけるフラグをfalse
            clickObject.SetHitObjFlag(false); 
            // お菓子オブジェのタグをミニゲーム済みに変更
            honntai.layer = 10;
            // ベルトコンベアの動きを止める
            MoveBeltFlag(sceneNum, true);
            // カメラ位置をミニゲームの位置にする
            ChangeCamera(1);
            // ミニゲームをアクティブにする
            minigames.SetActive(true);
            minigame.SetActive(true);
            // ミニゲーム説明テキストの表示
            miniGameText.SetActive(true);
            yield return new WaitForSecondsRealtime(0.8f);
            // ミニゲーム説明テキストの非表示
            miniGameText.SetActive(false);
            // ミニゲームの時間(ミニゲームによって分ける)
            if (tag == "CCake" || tag == "CBowl" || tag == "DBowl" 
                || tag == "OBowl" || tag == "ChocoBowl" )
            {
                yield return new WaitForSecondsRealtime(5.0f); 
            }
            else if (tag == "DoughCookie")
            {
                yield return new WaitForSecondsRealtime(7.0f);
            }
            else if (tag == "ChocoHarden" || tag == "OrangeJelly")
            {
                yield return new WaitForSecondsRealtime(10.0f);
            }
            doneMiniGame = true;  // ミニゲームを発生済みにする
            if (tag == "CBowl") 
            {
                GameObject miniGameCam;
                GameManager gameManager;
                // カメラの取得
                miniGameCam = GameObject.Find("Main Camera");
                gameManager = miniGameCam.GetComponent<GameManager>();
                gameManager.tutorialOrder = 5;  // チュートリアルフェーズを設定
            }
            // ミニゲームを非アクティブにする
            minigame.SetActive(false);
            // カメラ位置をプレイヤーがいる位置にする
            ChangeCamera(0);
            // ベルトコンベアを動かす
            MoveBeltFlag(sceneNum, false);
            // ミニゲームが終わっていないかどうか
            if(miniGameResult == false)
            {
                // オブジェクトを終わっていない状態にする
                honntai.layer = 11;    // layerをLiveにセット
                doneMiniGame = false;  // ミニゲームを再び発生させる状態にする
            }
            // ミニゲーム中フラグをfalse
            onlyMinigameIn.duringPlay = false;
        }
        yield break;   
    }
    // 端でのミニゲームの発生
    public IEnumerator edgeMinigameTimer(GameObject edgeObj)
    {
        // ミニゲームが発生済みでなく、ミニゲーム中でなく、タイムオーバー(ゲームオーバー)でないかどうか
        if (doneMiniGame == false && onlyMinigameIn.duringPlay == false && TimeCount.isTimeUp == false)
        {
            // オブジェクトを追いかけるフラグをfalse
            clickObject.SetHitObjFlag(false);
            onlyMinigameIn.duringPlay = true;  // ミニゲーム中フラグをtrue
            // ベルトコンベアの動きを止める
            MoveBeltFlag(sceneNum, true);
            GameObject miniGameCam;
            GameManager gameManager;
            // カメラの取得
            miniGameCam = GameObject.Find("Main Camera");
            gameManager = miniGameCam.GetComponent<GameManager>();
            // カメラ位置をミニゲームの位置にする
            ChangeCamera(1);
            // ミニゲームをアクティブにする
            minigames.SetActive(true);
            minigame.SetActive(true);
            // ミニゲーム説明テキストの表示
            miniGameText.SetActive(true);
            yield return new WaitForSecondsRealtime(0.8f);
            // ミニゲーム説明テキストの非表示
            miniGameText.SetActive(false);
            // ミニゲームの時間
            if (edgeObj.tag == "CCake" || edgeObj.tag == "ChocoBowl" || edgeObj.tag == "OBowl")
            {
                yield return new WaitForSecondsRealtime(5.0f);
            }
            edgeObj.tag = "EndSweets";  // 最後のお菓子のタグにする
            doneMiniGame = true;        // ミニゲーム発生済みにする
            // ミニゲームを非アクティブにする
            minigame.SetActive(false);
            // カメラ位置をプレイヤーがいる位置にする
            ChangeCamera(0);
            // ベルトコンベアを動かす
            MoveBeltFlag(sceneNum, false);
            // ミニゲーム中フラグをfalse
            onlyMinigameIn.duringPlay = false;
            // *端のミニゲームの場合は失敗しても再度ミニゲームを発生させない
            yield break;
        }
    }
    void OnTriggerStay(Collider other)
    {
        // プレイヤーと接触し
        //  タイムオーバー(ゲームオーバー)でなければミニゲームを呼ぶ
        if (other.CompareTag("Player") && TimeCount.isTimeUp == false)
        {
            StartCoroutine("MinigameTimer", this.gameObject.tag);
        }
    }
    void Update()
    {
        // オブジェクトが最後のお菓子タグかどうか
        if(this.gameObject.tag == "EndSweets")
        {
            // オブジェクトを非表示にする
            this.gameObject.SetActive(false);
        }
        // タイムオーバー(ゲームオーバー)かどうか
        if(TimeCount.isTimeUp == true)
        {
            // カメラ位置をプレイキャラのいる面へ戻す
            ChangeCamera(0);
        }
    }
    // ミニゲーム発生済みフラグのゲッター
    // 引  数：なし
    // 戻り値：bool   true 発生済み  false 発生していない
    public bool getDoneMiniGame()
    {
        return doneMiniGame;
    }
    // ミニゲーム発生済みフラグのセッター
    // 引  数：bool   true 発生済み  false 発生していない
    // 戻り値：なし  
    public void SetDoneMiniGame(bool set)
    {
        doneMiniGame = set;
    }
    // ミニゲームの終了フラグのセッター
    // 引  数：bool   true 終了ずみ  false 終了してない
    // 戻り値：なし  
    public void SetMinigameResult(bool set)
    {
        miniGameResult = set;
    }
    // カメラ位置を移動させるGameStatus変数の変更
    // 引  数：int   cameraChangeNum  0 プレイヤーのいる位置へ移動 
    //                                1 ミニゲーム位置へ移動
    // 戻り値：なし 
    public void ChangeCamera(int cameraChangeNum)
    {
        GameObject miniGameCam;
        GameManager gameManager;
        // カメラの取得
        miniGameCam = GameObject.Find("Main Camera");
        gameManager = miniGameCam.GetComponent<GameManager>();
        // カメラの変更変数を変更
        gameManager.GameStatus = cameraChangeNum;
        // カメラ位置を変更
        switch (cameraChangeNum)
        {
            case 0:  // プレイヤーのいる位置へ移動 
                gameManager.ChangeMainPosCamera();
                break;
            case 1:  //  ミニゲーム位置へ移動
                gameManager.ChangeMiniGamePosCamera();
                break;
        }
    }
    // ベルトコンベアの動きの制御
    // 引  数：bool   beltMove  true  ベルトコンベアを動かす
    //                          false ベルトコンベアを止める 
    //         int    sceneNum  1はステージ1 2はステージ2 3はステージ3 4はステージ4
    // 戻り値：なし 
    public void MoveBeltFlag(int sceneNum, bool beltMove)
    {
        switch (sceneNum)
        {
            case 1:  // ステージ1
                belt1.stopBeltMove = beltMove;
                belt2.stopBeltMove = beltMove;
                break;
            case 2:  // ステージ2
                belt1.stopBeltMove = beltMove;
                belt2.stopBeltMove = beltMove;
                belt3.stopBeltMove = beltMove;
                belt4.stopBeltMove = beltMove;
                break;
            case 3:  // ステージ3
                belt1.stopBeltMove = beltMove;
                belt2.stopBeltMove = beltMove;
                belt3.stopBeltMove = beltMove;
                belt4.stopBeltMove = beltMove;
                belt5.stopBeltMove = beltMove;
                belt6.stopBeltMove = beltMove;
                belt7.stopBeltMove = beltMove;
                belt8.stopBeltMove = beltMove;
                break;
            case 4:  // ステージ4
                belt1.stopBeltMove = beltMove;
                belt2.stopBeltMove = beltMove;
                belt3.stopBeltMove = beltMove;
                belt4.stopBeltMove = beltMove;
                belt5.stopBeltMove = beltMove;
                belt6.stopBeltMove = beltMove;
                belt7.stopBeltMove = beltMove;
                belt8.stopBeltMove = beltMove;
                break;
        }
    }
}

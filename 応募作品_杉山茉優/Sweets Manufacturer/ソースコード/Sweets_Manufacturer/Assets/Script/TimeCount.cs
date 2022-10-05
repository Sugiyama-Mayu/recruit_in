using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
// M.S
// 制限時間の管理
public class TimeCount : MonoBehaviour
{
    // 通常モードのタイム
    private float time = 300.0f;
    // 残り時間表示用テキスト
    public Text timeCountText;
    // タイムオーバーフラグ
    static public bool isTimeUp;
    // リザルトシーンから呼ばれるタイム
    int timeLeft;
    // スクリプト変数
    public ResultManager resultManager;
    // テキストに表示させる時間
    int drawTime;
    void Start()
    {
        // 初期化
        isTimeUp = false;
        // ハードモードならば各ステージごとにタイムを設定
        if (GameManager.hardmode == true)
        {
            if (resultManager.GetSceneNum() == 4)  // ステージ4
            {
                time = 420;
            }
            else if (resultManager.GetSceneNum() == 3)  // ステージ3
            {
                time = 370;
            }
            else if(resultManager.GetSceneNum() == 2)  // ステージ2
            {
                time = 370;
            }
            else if(resultManager.GetSceneNum() == 1)   // ステージ1 
            {
                time = 350;
            }
        }
    }
    void Update()
    {
        // タイムをintにキャストして表示用タイムにする
        drawTime = (int)time;
        // ゲームクリアになっていないかどうか
        if (resultManager.GetCallGameClear() == false)
        {
            // タイムオーバーでないかどうか
            if (0 < time)
            {
                // タイムを引く
                time -= Time.deltaTime;
                // intにキャストした時間を表示する
                timeCountText.text = drawTime.ToString();
            }
            // タイムオーバーかどうか
            else if (time <= 0)
            {
                // タイムオーバーフラグをtrue
                isTimeUp = true;
                // timeLeftにゲームオーバー時のタイムをいれる
                timeLeft = (int)time;
            }
        }
        else
        {
            // timeLeftにゲームクリア時のタイムをいれる
            timeLeft = (int)time;
        }
    }
    // タイムのゲッター
    // 引  数：なし
    // 戻り値：int timeLeft   残り時間
    public int GetTime()
    {
        return timeLeft;
    }
}

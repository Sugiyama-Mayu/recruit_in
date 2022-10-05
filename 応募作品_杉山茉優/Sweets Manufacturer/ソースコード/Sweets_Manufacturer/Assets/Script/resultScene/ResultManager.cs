using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
// M.S
// ゲームクリア、ゲームオーバー判定とその処理
public class ResultManager : MonoBehaviour
{
    // ケーキのゲーム成功フラグ
    public bool cakeCreamBowlJudge;
    public bool cakeOvenJudge;
    public bool cakeCutJudge;
    public bool cakeDecorationJudge;
    // チョコクラッカーのゲーム成功フラグ
    public bool chocoBowlJudge;
    public bool chocoCrackerBowlJudge;
    public bool chocoHardenJudge;
    public bool chocoCoolJudge;
    // ゼリーのゲーム成功フラグ
    public bool orangeBowlJudge;
    public bool orangePourJudge;
    public bool orangePutJudge;
    public bool orangeCoolJudge;
    // クッキーのゲーム成功フラグ
    public bool cookieDoughBowlJudge;
    public bool cookieCoolJudge;
    public bool cookieCutOutJudge;
    public bool cookieOvenJudge;
    // 今のステージの数字
    public int nowSeceneNum;
    // ゲームクリアフラグ
    private bool callGameClear;

    public GameObject clearText; // ゲームクリアテキスト
    public GameObject overText;  // ゲームオーバーテキスト
    // スクリプト変数
    public TimeCount timeCount;
    public AudioScript audioScript;
    // 残り時間
    public int time;
    // ステージで流れているお菓子オブジェ
    public GameObject CakeBowl;
    public GameObject Cake;
    public GameObject ChocoBowl;
    public GameObject Choco;
    public GameObject OrangeBowl;
    public GameObject Jelly;
    public GameObject CookieDoughBowl;
    public GameObject Cookie;
    // ゲームクリア後に一定時間経過したかどうかフラグ
    private bool DoneStop;
    // スコア
    private int score;
    // プレイキャラアニメーター
    public Animator animatorChef;
    void Start()
    {
        // 初期化
        cakeCreamBowlJudge = false;
        cakeOvenJudge = false;
        cakeCutJudge = false;
        cakeDecorationJudge = false;
        chocoBowlJudge = false;
        chocoCrackerBowlJudge = false;
        chocoHardenJudge = false;
        chocoCoolJudge = false;
        orangeBowlJudge = false;
        orangePourJudge = false;
        orangePutJudge = false;
        orangeCoolJudge = false;
        cookieDoughBowlJudge = false;
        cookieCoolJudge = false;
        cookieCutOutJudge = false;
        cookieOvenJudge = false;
        callGameClear = false;
        DoneStop = false;
        // リザルトでスコアなどを持っていくためにこのオブジェは残す
        DontDestroyOnLoad(this);
    }
    void Update()
    {
        // 残り時間の取得
        time = timeCount.GetTime();
        // ゲームクリアかどうか判定する
        JudgeClear();
        // タイムオーバーでないかどうか
        if (TimeCount.isTimeUp == false)
        {
            // ゲームクリアフラグがtrueかどうか
            if (callGameClear == true)
            {
                // クリアテキストを表示する
                clearText.SetActive(true);
            }
        }
        else
        {
            // ゲームオーバーBGMにする
            audioScript.SetChangeBGM(3);
            // ゲームオーバーテキストの表示
            overText.SetActive(true);
            switch (nowSeceneNum)
            {
                // 現在のステージのお菓子のタグをゲームオーバーのタグにして
                // お菓子を非アクティブにする
                case 1:  // ケーキ
                    CakeBowl.tag = "OverSweets";
                    Cake.tag = "OverSweets";
                    CakeBowl.SetActive(false);
                    Cake.SetActive(false);
                    break;
                case 2:  // ケーキ、チョコクラッカー
                    CakeBowl.tag = "OverSweets";
                    Cake.tag = "OverSweets";
                    ChocoBowl.tag = "OverSweets";
                    Choco.tag = "OverSweets";
                    CakeBowl.SetActive(false);
                    Cake.SetActive(false);
                    ChocoBowl.SetActive(false);
                    Choco.SetActive(false);
                    break;
                case 3:  // ケーキ、チョコクラッカー、ゼリー
                    CakeBowl.tag = "OverSweets";
                    Cake.tag = "OverSweets";
                    ChocoBowl.tag = "OverSweets";
                    Choco.tag = "OverSweets";
                    OrangeBowl.tag = "OverSweets";
                    Jelly.tag = "OverSweets";
                    CakeBowl.SetActive(false);
                    Cake.SetActive(false);
                    ChocoBowl.SetActive(false);
                    Choco.SetActive(false);
                    OrangeBowl.SetActive(false);
                    Jelly.SetActive(false);
                    break;
                case 4:  // ケーキ、チョコクラッカー、ゼリー、クッキー
                    CakeBowl.tag = "OverSweets";
                    Cake.tag = "OverSweets";
                    ChocoBowl.tag = "OverSweets";
                    Choco.tag = "OverSweets";
                    OrangeBowl.tag = "OverSweets";
                    Jelly.tag = "OverSweets";
                    CookieDoughBowl.tag = "OverSweets";
                    Cookie.tag = "OverSweets";
                    CakeBowl.SetActive(false);
                    Cake.SetActive(false);
                    ChocoBowl.SetActive(false);
                    Choco.SetActive(false);
                    OrangeBowl.SetActive(false);
                    Jelly.SetActive(false);
                    CookieDoughBowl.SetActive(false);
                    Cookie.SetActive(false);
                    break;
            }
        }
    }
    // ゲームをクリアしているか判断し、ゲームクリア処理をする
    // 引  数：なし
    // 戻り値：なし
    void JudgeClear()
    {
        switch (nowSeceneNum)
        {
            // 現在のステージのお菓子のミニゲームが終了(端のゲーム以外は成功)しているかどうか
            case 1:  // ケーキ
                if (ResultCakeGame() == true && Cake.tag == "EndSweets")
                {
                    callGameClear = true;  // ゲームクリアフラグをtrue
                    audioScript.SetChangeBGM(2);  // ゲームクリアBGMにする
                    // スコアを出す
                    score = timeCount.GetTime() * ResultCakeEdgeSuccess();
                    // プレイキャラにクリアアニメーションをさせる
                    animatorChef.SetBool("isClear", true);  
                    StartCoroutine("stopTime");  // 一定時間経過させる
                    // 一定時間経過したかどうか
                    if (DoneStop == true)
                    {
                        // プレイキャラのアニメーションをやめる
                        animatorChef.SetBool("isClear", false);
                        // リザルトシーンを呼ぶ
                        SceneManager.LoadScene("ResultScene");
                    }
                }
                break;
            case 2:  // ケーキ、チョコクラッカー
                if (ResultCakeGame() == true && ResultChocoGame() == true 
                    && Cake.tag == "EndSweets" && Choco.tag == "EndSweets")
                {
                    callGameClear = true;  // ゲームクリアフラグをtrue
                    audioScript.SetChangeBGM(2);  // ゲームクリアBGMにする
                    // スコアを出す
                    score = timeCount.GetTime() * (ResultChocoEdgeSuccess()
                        + ResultCakeEdgeSuccess());
                    // プレイキャラにクリアアニメーションをさせる
                    animatorChef.SetBool("isClear", true);  
                    StartCoroutine("stopTime");  // 一定時間経過させる
                    // 一定時間経過したかどうか
                    if (DoneStop == true)
                    {
                        // プレイキャラのアニメーションをやめる
                        animatorChef.SetBool("isClear", false);
                        // リザルトシーンを呼ぶ
                        SceneManager.LoadScene("ResultScene");
                    }
                }
                break;
            case 3:  // ケーキ、チョコクラッカー、ゼリー
                if (ResultCakeGame() == true && ResultChocoGame() == true 
                    && ResultOrangeGame() == true && Cake.tag == "EndSweets"
                    && Choco.tag == "EndSweets" && Jelly.tag == "EndSweets")
                {
                    callGameClear = true;  // ゲームクリアフラグをtrue
                    audioScript.SetChangeBGM(2);  // ゲームクリアBGMにする
                    // スコアを出す
                    score = timeCount.GetTime() * (ResultOrangeEdgeSuccess()
                        + ResultChocoEdgeSuccess() + ResultCakeEdgeSuccess());
                    // プレイキャラにクリアアニメーションをさせる
                    animatorChef.SetBool("isClear", true); 
                    StartCoroutine("stopTime");  // 一定時間経過させる
                    // 一定時間経過したかどうか
                    if (DoneStop == true)
                    {
                        // プレイキャラのアニメーションをやめる
                        animatorChef.SetBool("isClear", false);
                        // リザルトシーンを呼ぶ
                        SceneManager.LoadScene("ResultScene");
                    }
                }
                break;
            case 4:  // ケーキ、チョコクラッカー、ゼリー、クッキー
                if (ResultCakeGame() == true && ResultChocoGame() == true 
                    && ResultOrangeGame() == true && ResultCookieGame() == true
                    && Cake.tag == "EndSweets" && Choco.tag == "EndSweets" 
                    && Jelly.tag == "EndSweets" && Cookie.tag == "EndSweets")
                {
                    callGameClear = true;  // ゲームクリアフラグをtrue
                    audioScript.SetChangeBGM(2); // ゲームクリアBGMにする
                    // スコアを出す
                    score = timeCount.GetTime() * (ResultCookieEdgeSuccess() 
                        + ResultOrangeEdgeSuccess() + ResultChocoEdgeSuccess()
                        + ResultCakeEdgeSuccess());
                    // プレイキャラにクリアアニメーションをさせる
                    animatorChef.SetBool("isClear", true);
                    StartCoroutine("stopTime");  // 一定時間経過させる
                    // 一定時間経過したかどうか
                    if (DoneStop == true)
                    {
                        // プレイキャラのアニメーションをやめる
                        animatorChef.SetBool("isClear", false);
                        // リザルトシーンを呼ぶ
                        SceneManager.LoadScene("ResultScene");
                    }
                }
                break;
        }
    }
    // 端で発生しないケーキのゲームが成功(終了)しているかどうか調べる
    // 引  数：なし
    // 戻り値：bool   true   終了している
    //                false  終了していない
    private bool ResultCakeGame()
    {
        // 各ゲームが成功しているかどうか
        if(cakeCreamBowlJudge == true && cakeCutJudge == true )
        {
            return true;
        }
        return false;
    }
    // 端で発生するケーキのゲームの成功回数を調べる
    // 引  数：なし
    // 戻り値：int   edgeNum 端で発生するゲームの成功回数+1の数
    public int ResultCakeEdgeSuccess()
    {
        int edgeNum = 1;
        // 成功していたら+1していく
        if (cakeOvenJudge == true)
        {
            edgeNum++;
        }
        if ( cakeDecorationJudge == true)
        {
            edgeNum++;
        }
        return edgeNum;
    }
    // 端で発生しないチョコクラッカーのゲームが成功(終了)しているかどうか調べる
    // 引  数：なし
    // 戻り値：bool   true   終了している
    //                false  終了していない
    private bool ResultChocoGame()
    {
        // 各ゲームが成功しているかどうか
        if (chocoBowlJudge == true  && chocoHardenJudge == true )
        {
            return true;
        }
        return false;
    }
    // 端で発生するチョコクラッカーのゲームの成功回数を調べる
    // 引  数：なし
    // 戻り値：int   edgeNum 端で発生するゲームの成功回数+1の数
    public int ResultChocoEdgeSuccess()
    {
        int edgeNum = 1;
        // 成功していたら+1していく
        if ( chocoCrackerBowlJudge == true)
        {
            edgeNum++;
        }
        if (chocoCoolJudge == true)
        {
            edgeNum++;
        }
        return edgeNum;
    }
    // 端で発生しないゼリーのゲームが成功(終了)しているかどうか調べる
    // 引  数：なし
    // 戻り値：bool   true   終了している
    //                false  終了していない
    private bool ResultOrangeGame()
    {
        // 各ゲームが成功しているかどうか
        if (orangeBowlJudge == true && orangePutJudge == true )
        {
            return true;
        }
        return false;
    }
    // 端で発生するゼリーのゲームの成功回数を調べる
    // 引  数：なし
    // 戻り値：int   edgeNum 端で発生するゲームの成功回数+1の数
    public int ResultOrangeEdgeSuccess()
    {
        int edgeNum = 1;
        // 成功していたら+1していく
        if (orangePourJudge == true)
        {
            edgeNum++;
        }
        if (orangeCoolJudge == true)
        {
            edgeNum++;
        }
        return edgeNum;
    }
    // 端で発生しないクッキーのゲームが成功(終了)しているかどうか調べる
    // 引  数：なし
    // 戻り値：bool   true   終了している
    //                false  終了していない
    private bool ResultCookieGame()
    {
        // 各ゲームが成功しているかどうか
        if (cookieDoughBowlJudge == true && cookieCutOutJudge == true )
        {
            return true;
        }
        return false;

    }
    // 端で発生するクッキーのゲームの成功回数を調べる
    // 引  数：なし
    // 戻り値：int edgeNum   端で発生するゲームの成功回数+1の数
    public int ResultCookieEdgeSuccess()
    {
        int edgeNum = 1;
        // 成功していたら+1していく
        if ( cookieCoolJudge == true)
        {
            edgeNum++;
        }
        if (cookieOvenJudge == true)
        {
            edgeNum++;
        }
        return edgeNum;
    }
    // callGameClearのゲッター(ゲームクリアになったかどうか調べる)
    // 引  数：なし
    // 戻り値：bool callGameClear    true  ゲームクリアになっている
    //                               false ゲームクリアになっていない
    public bool GetCallGameClear()
    {
        return callGameClear;
    }
    // スコアのゲッター
    // 引  数：なし
    // 戻り値：int score    スコアの値
    public int GetScore()
    {
        return score;
    }
    // 現在のステージ数のゲッター
    // 引  数：なし
    // 戻り値：int nowSeceneNum   今のステージの数字
    public int GetSceneNum()
    {
        return nowSeceneNum;
    }
    // 一定時間経過させる
    IEnumerator stopTime()
    {
        yield return new WaitForSecondsRealtime(6.0f);
        // 一定時間経過させたフラグをtrue
        DoneStop = true;
    }
}

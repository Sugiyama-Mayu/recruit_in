using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
// M.S 
// ゲームの結果処理
public class GameResult : MonoBehaviour
{
    // ゲームの結果を持っているオブジェクト
    GameObject resultHaveObj;
    // スコアの値
    int score;
    // ステージの数字
    public int sceneNum;
    // ランク
    private int rankNum;
    // 表示するランクのテキスト
    public Text rankText;
    // 表示する残り制限時間のテキスト
    public Text TimeText;
    // 表示するゲーム内で制作したお菓子
    public GameObject resultCake;
    public GameObject resultChoco;
    public GameObject resultJelly;
    public GameObject resultCookie;
    public GameObject resultGoldCake;
    public GameObject resultGoldChoco;
    public GameObject resultGoldJelly;
    public GameObject resultGoldCookie;
    // 表示する各ステージトロフィーテキストイメージ
    public GameObject stage1Text;
    public GameObject stage2Text;
    public GameObject stage3Text;
    public GameObject stage4Text;
    public GameObject allText;
    // 読み込むファイルのパス
    string filePath;
    // 読み込んだファイルの内容を入れる配列
    int[] readCollectNum = new int[17];
    // 読み込んだ時間
    int time;
    // 金のお菓子の制作フラグ
    bool cakeGold;
    bool chocoGold;
    bool jellyGold;
    bool cookieGold;
    void Start()
    {
        // 時間経過を通常にする
        Time.timeScale = 1;
        // 初期化
        cakeGold = false;
        chocoGold = false;
        jellyGold = false;
        cookieGold = false;
        score = 0;
        // ゲームの結果を読み込む
        resultHaveObj = GameObject.Find("moveSceneObj"); // オブジェクト
        score = resultHaveObj.GetComponent<ResultManager>().GetScore(); // スコア
        // ステージ数
        sceneNum = resultHaveObj.GetComponent<ResultManager>().GetSceneNum();
        time = resultHaveObj.GetComponent<ResultManager>().time; // 残り時間
        // ResultManagerのOFF
        resultHaveObj.GetComponent<ResultManager>().enabled = false;
        Destroy(GameObject.Find("moveSceneObj")); // ゲームの結果オブジェクトの削除
        // お菓子オブジェを非表示にする
        resultCake.SetActive(false);
        resultChoco.SetActive(false);
        resultJelly.SetActive(false);
        resultCookie.SetActive(false);

        filePath = Application.dataPath + "/StreamingAssets/collectFile.txt";
        // ここでコレクション用のファイルの読み込み
        string[] readCollect = File.ReadAllLines(filePath);
        // ここでコレクション用のファイルのintへの変換
        for (int arrayNum = 0; arrayNum < 17; arrayNum++)
        {
            readCollectNum[arrayNum] = int.Parse(readCollect[arrayNum]);
        }
        // 各お菓子の表示フラグとファイル登録変数の変更処理
        RegisterSweets();
        // 残り制限時間を保存
        TimeText.text = time.ToString();
        // ランクをつける
        RankByScore();
        // ステージクリアのファイル登録変数の変更処理
        RegisterSRankStage();
        // オールコンプリートトロフィーの条件を満たしているか
        //  の確認のためにファイルを全て見ていく
        for (int num = 0; num < 16; num++)
        {
            // ファイルに登録されているかどうか
            if (readCollectNum[num] == 1)
            {
                // 全て見終わっているかどうか
                if (num >= 15)
                {
                    // まだファイルに登録されていなければ
                    if (readCollectNum[16] == 0)
                    {
                        // 全てのステージのSランククリアをファイルに書き込む
                        readCollectNum[16] = 1;
                        // 全てのステージクリアトロフィー獲得メッセ―ジの表示
                        allText.SetActive(true);
                    }
                }
            }
            else
            {
                break;
            }
        }
        // 上で書き込んだコレクションデータをファイルへ入力  stringへintを書き換え
        readCollect[0] = readCollectNum[0].ToString(); 
        File.WriteAllText(filePath, readCollect[0] + '\n'); // 一度書き込みデータを消して、書き込む
        for (int i = 1; i < 17; i++)
        {
            readCollect[i] = readCollectNum[i].ToString();  
            File.AppendAllText(filePath, readCollect[i] + '\n'); // 追記していく
        }
    }

    void Update()
    {
        // お菓子の表示
        // もし○○Goldフラグがtrueならば金のお菓子を表示
        // falseならば通常のお菓子の表示
        switch (sceneNum)
        {
            case 1:   // ステージが1ならば
                if (cakeGold == true)
                {
                    resultGoldCake.SetActive(true);
                }
                else
                {
                    resultCake.SetActive(true);
                }
                break;
            case 2:   // ステージが2ならば
                if (cakeGold == true)
                {
                    resultGoldCake.SetActive(true);
                }
                else
                {
                    resultCake.SetActive(true);
                }
                if (chocoGold == true)
                {
                    resultGoldChoco.SetActive(true);
                }
                else
                {
                    resultChoco.SetActive(true);
                }
                break;
            case 3:   // ステージが3ならば
                if (cakeGold == true)
                {
                    resultGoldCake.SetActive(true);
                }
                else
                {
                    resultCake.SetActive(true);
                }
                if (chocoGold == true)
                {
                    resultGoldChoco.SetActive(true);
                }
                else
                {
                    resultChoco.SetActive(true);
                }
                if (jellyGold == true)
                {
                    resultGoldJelly.SetActive(true);
                }
                else
                {
                    resultJelly.SetActive(true);
                }
                break;
            case 4:   // ステージが4ならば
                if (cakeGold == true)
                {
                    resultGoldCake.SetActive(true);
                }
                else
                {
                    resultCake.SetActive(true);
                }
                if (chocoGold == true)
                {
                    resultGoldChoco.SetActive(true);
                }
                else
                {
                    resultChoco.SetActive(true);
                }
                if (jellyGold == true)
                {
                    resultGoldJelly.SetActive(true);
                }
                else
                {
                    resultJelly.SetActive(true);
                }
                if (cookieGold == true)
                {
                    resultGoldCookie.SetActive(true);
                }
                else
                {
                    resultCookie.SetActive(true);
                }
                break;
        }
    }
    // 各お菓子の表示フラグとファイル登録変数の変更処理
    // 引  数：なし
    // 戻り値：なし
    void RegisterSweets()
    {
        // ケーキの出現シーンかどうか
        if (sceneNum == 1 || sceneNum == 2 || sceneNum == 3 || sceneNum == 4)
        {
            // ミニゲームの成功結果が満たされていれば
            if (resultHaveObj.GetComponent<ResultManager>().ResultCakeEdgeSuccess() >= 3)
            {
                // 金のケーキ表示フラグをtrue
                cakeGold = true;
                // まだファイルに登録されていなければ
                if (readCollectNum[1] == 0)
                {
                    // 金のケーキコレクションを1にする
                    readCollectNum[1] = 1;
                }
            }
            else
            {
                if (readCollectNum[0] == 0) // まだファイルに登録されていなければ
                {
                    readCollectNum[0] = 1; // ケーキのコレクションを1
                }
            }
        }
        // チョコクラッカーの出現シーンかどうか
        if (sceneNum == 2 || sceneNum == 3 || sceneNum == 4)
        {
            // ミニゲームの成功結果が満たされていれば
            if (resultHaveObj.GetComponent<ResultManager>().ResultChocoEdgeSuccess() >= 3)
            {
                chocoGold = true; // 金のチョコクラッカー表示フラグをtrue
                if (readCollectNum[3] == 0) // まだファイルに登録されていなければ
                {
                    // 金のチョコクラッカーのコレクションを1にする
                    readCollectNum[3] = 1;
                }
            }
            else
            {
                if (readCollectNum[2] == 0) // まだファイルに登録されていなければ
                {
                    readCollectNum[2] = 1; // チョコクラッカーのコレクションを1
                }
            }
        }
        // ゼリーの出現シーンかどうか
        if (sceneNum == 3 || sceneNum == 4)
        {
            // ミニゲームの成功結果が満たされていれば
            if (resultHaveObj.GetComponent<ResultManager>().ResultOrangeEdgeSuccess() >= 3)
            {
                jellyGold = true; // 金のゼリー表示フラグをtrue
                if (readCollectNum[5] == 0) // まだファイルに登録されていなければ
                {
                    readCollectNum[5] = 1; // 金のゼリーのコレクションを1にする
                }
            }
            else
            {
                if (readCollectNum[4] == 0) // まだファイルに登録されていなければ
                {
                    readCollectNum[4] = 1; // ゼリーのコレクションを1
                }
            }
        }
        // クッキーの出現シーンかどうか
        if (sceneNum == 4)
        {
            // ミニゲームの成功結果が満たされていれば
            if (resultHaveObj.GetComponent<ResultManager>().ResultCookieEdgeSuccess() >= 3)
            {
                cookieGold = true; // 金のクッキー表示フラグをtrue                
                if (readCollectNum[7] == 0) // まだファイルに登録されていなければ
                {
                    readCollectNum[7] = 1; // 金のクッキーのコレクションを1にする
                }
            }
            else
            {
                if (readCollectNum[6] == 0) // まだファイルに登録されていなければ
                {
                    readCollectNum[6] = 1; // クッキーのコレクションを1
                }
            }
        }
    }
    // スコアからランクをつける
    // 引  数：なし
    // 戻り値：なし
    void RankByScore()
    {
        // ステージとスコアによってランクをつける
        // rankNum：1はSランク 2はAランク 3はBランク 4はCランク
        if (sceneNum == 1)  // ステージが1ならば
        {
            if (score > 240 * 3)
            {
                rankNum = 1;
            }
            else if (score > 220 * 3)
            {
                rankNum = 2;
            }
            else if (score > 200 * 3)
            {
                rankNum = 3;
            }
            else
            {
                rankNum = 4;
            }
        }
        else if (sceneNum == 2)  // ステージが2ならば
        {
            if (score > 220 * 6)
            {
                rankNum = 1;
            }
            else if (score > 190 * 6)
            {
                rankNum = 2;
            }
            else if (score > 160 * 6)
            {
                rankNum = 3;
            }
            else
            {
                rankNum = 4;
            }
        }
        else if (sceneNum == 3) // ステージが3ならば
        {
            if (score > 160 * 9)
            {
                rankNum = 1;
            }
            else if (score > 130 * 9)
            {
                rankNum = 2;
            }
            else if (score > 100 * 9)
            {
                rankNum = 3;
            }
            else
            {
                rankNum = 4;
            }
        }
        else if (sceneNum == 4) // ステージが4ならば
        {
            if (score > 150 * 12)
            {
                rankNum = 1;
            }
            else if (score > 120 * 12)
            {
                rankNum = 2;
            }
            else if (score > 90 * 12)
            {
                rankNum = 3;
            }
            else
            {
                rankNum = 4;
            }
        }
        // rankNumによってrankTextに表示ランクを保存
        switch (rankNum)
        {
            case 1:
                rankText.text = "S";
                break;
            case 2:
                rankText.text = "A";
                break;
            case 3:
                rankText.text = "B";
                break;
            case 4:
                rankText.text = "C";
                break;
        }
    }
    // ステージトロフィーの条件を満たしている場合
    // ファイル登録変数の変更、獲得メッセージの表示
    // 引  数：なし
    // 戻り値：なし
    void RegisterSRankStage()
    {
        switch (sceneNum)  // ステージ数
        {
            case 1:  // ステージ1でSランククリアをしたかどうか
                if (cakeGold == true && rankText.text == "S" && GameManager.hardmode == false)
                {
                    // まだファイルに登録されていなければ
                    if (readCollectNum[8] == 0)
                    {
                        // ステージ1のSランククリアをファイルに書き込む
                        readCollectNum[8] = 1;
                        // ステージ1のSランククリアトロフィー獲得メッセ―ジの表示
                        stage1Text.SetActive(true);
                    }
                }
                // ハードモードでステージ1のSランククリアをしたかどうか
                else if (cakeGold == true && rankText.text == "S" && GameManager.hardmode == true)
                {
                    // ステージ1のSランククリアをファイルに書き込む
                    if (readCollectNum[12] == 0)
                    {
                        // ハードモードでステージ1のSランククリアをファイルに書き込む
                        readCollectNum[12] = 1;
                    }
                }
                break;
            case 2:  // ステージ2でSランククリアをしたかどうか
                if (cakeGold == true && chocoGold == true && rankText.text == "S" && GameManager.hardmode == false)
                {
                    // まだファイルに登録されていなければ
                    if (readCollectNum[9] == 0)
                    {
                        // ステージ2のSランククリアをファイルに書き込む
                        readCollectNum[9] = 1;
                        // ステージ2のSランククリアトロフィー獲得メッセ―ジの表示
                        stage2Text.SetActive(true);
                    }
                }
                // ハードモードでステージ2でSランククリアをしたかどうか
                else if (cakeGold == true && chocoGold == true && rankText.text == "S" && GameManager.hardmode == true)
                {
                    // まだファイルに登録されていなければ
                    if (readCollectNum[13] == 0)
                    {
                        // ハードモードでステージ2のSランククリアをファイルに書き込む
                        readCollectNum[13] = 1;
                    }
                }
                break;
            case 3:  // ステージ3でSランククリアをしたかどうか
                if (cakeGold == true && chocoGold == true && jellyGold == true && rankText.text == "S" && GameManager.hardmode == false)
                {
                    // まだファイルに登録されていなければ
                    if (readCollectNum[10] == 0)
                    {
                        // ステージ3のSランククリアをファイルに書き込む
                        readCollectNum[10] = 1;
                        // ステージ3のSランククリアトロフィー獲得メッセ―ジの表示
                        stage3Text.SetActive(true);
                    }
                }
                // ハードモードでステージ3でSランククリアをしたかどうか
                else if (cakeGold == true && chocoGold == true && jellyGold == true && rankText.text == "S" && GameManager.hardmode == true)
                {
                    // まだファイルに登録されていなければ
                    if (readCollectNum[14] == 0)
                    {
                        // ハードモードでステージ3のSランククリアをファイルに書き込む
                        readCollectNum[14] = 1;
                    }
                }
                break;
            case 4:  // ステージ4でSランククリアをしたかどうか
                if (cakeGold == true && chocoGold == true && jellyGold == true && cookieGold == true && rankText.text == "S" && GameManager.hardmode == false)
                {
                    // まだファイルに登録されていなければ
                    if (readCollectNum[11] == 0)
                    {
                        // ステージ4のSランククリアをファイルに書き込む
                        readCollectNum[11] = 1;
                        // ステージ4のSランククリアトロフィー獲得メッセ―ジの表示
                        stage4Text.SetActive(true);
                    }
                }
                // ハードモードでステージ4でSランククリアをしたかどうか
                else if (cakeGold == true && chocoGold == true && jellyGold == true && cookieGold == true && rankText.text == "S" && GameManager.hardmode == true)
                {
                    // まだファイルに登録されていなければ
                    if (readCollectNum[15] == 0)
                    {
                        // ハードモードでステージ4のSランククリアをファイルに書き込む
                        readCollectNum[15] = 1;
                    }
                }
                break;
        }
    }
}


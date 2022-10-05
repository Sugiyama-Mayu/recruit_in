using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
// M.S 
// お菓子がベルトコンベアの端に着いた時のゲームの発生と
// お菓子をベルトコンベアの開始位置に移動する
public class DropObj : MonoBehaviour
{
    // 発生させるミニゲーム
    public GameObject minigame1;
    public GameObject minigame2;
    public GameObject minigame3;
    public GameObject minigame4;
    public GameObject minigame5;
    public GameObject minigame6;
    public GameObject minigame7;
    public GameObject minigame8;
    public GameObject minigame9;
    public GameObject minigame10;
    public GameObject minigame11;

    // 材料オブジェクトの配置位置
    public GameObject fOneLinePos;  // ステージ1

    public GameObject sOneLinePos;  // ステージ2
    public GameObject sTwoLinePos;

    public GameObject tOneLinePos;  // ステージ3
    public GameObject tTwoLinePos;
    public GameObject tThreeLinePos;

    public GameObject foOneLinePos; // ステージ4
    public GameObject foTwoLinePos;
    public GameObject foThreeLinePos;
    public GameObject foFourLinePos;

    public DropObj onlyDropObj;

    // レーン数
    private int laneCount;
    // シーン内のレーンの数
    public int laneMax;
    public static bool moveScene;
    // 次に配置するレーン数字
    public int nextLaneNum;
    // シーンにあるオブジェクトのまとまり
    public GameObject sceneTogether;
    // 各お菓子の最後に端で発生するゲーム
    public MinigameIn cakeDecorationMinigame;
    public MinigameIn hardenChocolateMinigame;
    public MinigameIn crackerChocolateMinigame;
    public MinigameIn orangePourMinigame;
    // ミニゲーム管理オブジェクト
    public MinigameIn onlyMinigameIn;
    // リザルト管理オブジェクト
    public ResultManager resultManager;
    // オーブン、冷蔵庫ゲームのゲーム結果
    public bool returnGamejudge;

    private bool DoneSceneMoveSweets;
    // 接触したお菓子オブジェクト
    private GameObject edgeSweetObj;
    private void Start()
    {
        // 初期化
        DoneSceneMoveSweets = false;
        returnGamejudge = false;
        moveScene = false;
        laneCount = 0;
    }
    private void Update()
    {
        // シーンを移動したてなのかどうか
        if (moveScene == true && DoneSceneMoveSweets == true)
        {   // オーブンゲーム、冷蔵庫ゲームの結果を保存し
            // 最後のお菓子の場合、EndSweetsタグをつける
            DoneSceneMoveSweets = false;
            if (edgeSweetObj.tag == "CBowl")  // [ケーキ]のボウル
            {
                // ミニゲームの結果を保存
                resultManager.cakeOvenJudge = onlyDropObj.returnGamejudge;
            }        
            else if (edgeSweetObj.tag == "ChocoHarden") // [チョコクラッカー]の固めるチョコ
            {
                // ミニゲームの結果を保存
                resultManager.chocoCoolJudge = onlyDropObj.returnGamejudge;
                edgeSweetObj.tag = "EndSweets";
            }
            else if (edgeSweetObj.tag == "OrangeJelly") // [ゼリー]のゼリー
            {
                // ミニゲームの結果を保存
                resultManager.orangeCoolJudge = onlyDropObj.returnGamejudge;
                edgeSweetObj.tag = "EndSweets";
            }
            else if (edgeSweetObj.tag == "DBowl") // [クッキー]のボウル
            {
                // ミニゲームの結果を保存
                resultManager.cookieCoolJudge = onlyDropObj.returnGamejudge;
            }
            else if (edgeSweetObj.tag == "DoughCookie") // [クッキー]の生地
            {
                // ミニゲームの結果を保存
                resultManager.cookieOvenJudge = onlyDropObj.returnGamejudge;
                edgeSweetObj.tag = "EndSweets";
            }
            // ミニゲームの表示を消す
            switch (laneMax) {
                case 1:
                    minigame1.SetActive(false);
                    minigame2.SetActive(false);
                    minigame3.SetActive(false);
                    break;
                case 2:
                    minigame1.SetActive(false);
                    minigame2.SetActive(false);
                    minigame3.SetActive(false);
                    minigame4.SetActive(false);
                    minigame5.SetActive(false);
                    minigame6.SetActive(false);
                    break;
                case 3:
                    minigame1.SetActive(false);
                    minigame2.SetActive(false);
                    minigame3.SetActive(false);
                    minigame4.SetActive(false);
                    minigame5.SetActive(false);
                    minigame6.SetActive(false);
                    minigame7.SetActive(false);
                    minigame8.SetActive(false);
                    minigame9.SetActive(false);
                    break;
                case 4:
                    minigame1.SetActive(false);
                    minigame2.SetActive(false);
                    minigame3.SetActive(false);
                    minigame4.SetActive(false);
                    minigame5.SetActive(false);
                    minigame6.SetActive(false);
                    minigame7.SetActive(false);
                    minigame8.SetActive(false);
                    minigame9.SetActive(false);
                    minigame10.SetActive(false);
                    minigame11.SetActive(false);
                    break;                   
            }
            // ミニゲーム中フラグをfalse
            onlyMinigameIn.duringPlay = false;
            moveScene = false;
        }
    }
    // 端でのミニゲームの発生
    IEnumerator OccurrenceEdgeMinigame(GameObject edgeObj)
    {
        // お菓子によって発生するミニゲームを分ける
        // ミニゲームによってはシーンを呼ぶ
        if (edgeObj.tag == "CBowl")   // [ケーキ]のボウル
        {
            // お菓子オブジェクトの保存
            edgeSweetObj = edgeObj;
            // シーン移動フラグをtrue
            DoneSceneMoveSweets = true;
            SceneManager.LoadScene("OvenScene", LoadSceneMode.Additive);
        }
        else if (edgeObj.tag == "CCake") // [ケーキ]のケーキ
        {
            // ミニゲームの呼び出し
            cakeDecorationMinigame.StartCoroutine("edgeMinigameTimer", edgeObj);
        }
        else if (edgeObj.tag == "ChocoBowl") // [チョコクラッカー]のボウル
        {
            // ミニゲームの呼び出し
            crackerChocolateMinigame.StartCoroutine("edgeMinigameTimer", edgeObj);
        }
        else if (edgeObj.tag == "ChocoHarden") // [チョコクラッカー]の固めるチョコ
        {
            // お菓子オブジェクトの保存
            edgeSweetObj = edgeObj;
            // シーン移動フラグをtrue
            DoneSceneMoveSweets = true;
            // シーン(ミニゲーム)の呼び出し
            SceneManager.LoadScene("CoolScene", LoadSceneMode.Additive);
        }
        else if (edgeObj.tag == "OrangeJelly") // [ゼリー]のゼリー
        {
            // お菓子オブジェクトの保存
            edgeSweetObj = edgeObj;
            // シーン移動フラグをtrue
            DoneSceneMoveSweets = true;
            // シーン(ミニゲーム)の呼び出し
            SceneManager.LoadScene("CoolScene", LoadSceneMode.Additive);
        }
        else if (edgeObj.tag == "OBowl")  // [ゼリー]のボウル
        {
            // ミニゲームの呼び出し
            orangePourMinigame.StartCoroutine("edgeMinigameTimer", edgeObj);
        }
        else if (edgeObj.tag == "DBowl")  // [クッキー]のボウル
        {
            // お菓子オブジェクトの保存
            edgeSweetObj = edgeObj;
            // シーン移動フラグをtrue
            DoneSceneMoveSweets = true;
            // シーン(ミニゲーム)の呼び出し
            SceneManager.LoadScene("CoolScene", LoadSceneMode.Additive);
        }
        else if (edgeObj.tag == "DoughCookie")  // [クッキー]の生地
        {
            // お菓子オブジェクトの保存
            edgeSweetObj = edgeObj;
            // シーン移動フラグをtrue
            DoneSceneMoveSweets = true;
            // シーン(ミニゲーム)の呼び出し
            SceneManager.LoadScene("OvenScene", LoadSceneMode.Additive);
        }
        yield break;
    }
    // 1つのレーンの時、端に材料(お菓子)オブジェクトが接触した際の処理
    // 引  数：GameObject collSweets  接触したオブジェクト
    //         MinigameIn collObj     接触したオブジェクトのMinigameInスクリプト
    // 戻り値：なし
    void CollSweetsLaneNumberOf1(GameObject collSweets, MinigameIn collObj)
    {
        // 接触したものがゲーム済みだったら
        if (collSweets.tag == "CBowl" && collSweets.layer == 10)
        {
            // 端まで来たのでゲームを呼びだす
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            // 今のお菓子を非表示にし、次のお菓子を表示する
            collSweets.SetActive(false);
            collObj.nextSweets.SetActive(true);
            // ベルトコンベアの開始位置にお菓子を移動
            collObj.nextSweets.transform.position = fOneLinePos.transform.position;
            onlyMinigameIn.duringPlay = true;

        }
        else if (collSweets.tag == "CCake" && collSweets.layer == 10)
        {
            // 端まで来たのでゲームを呼びだす
            // 最後のお菓子なので流さない
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            onlyMinigameIn.duringPlay = true;
        }
        else
        {
            // ゲーム済みでなければ、オブジェクトの位置をベルトコンベアの開始位置に移動
            collSweets.transform.position = fOneLinePos.transform.position;

        }
    }
    // 2つのレーンの時、端に材料(お菓子)オブジェクトが接触した際の処理
    // 引  数：GameObject collSweets  接触したオブジェクト
    //         MinigameIn collObj     接触したオブジェクトのMinigameInスクリプト
    // 戻り値：なし
    void CollSweetsLaneNumberOf2(GameObject collSweets, MinigameIn collObj)
    {
        // 接触したものがゲーム済みだったら
        if ((collSweets.tag == "CBowl" || collSweets.tag == "ChocoBowl") && collSweets.layer == 10)
        {
            // 端まで来たのでゲームを呼びだす
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            // 今のお菓子を非表示にし、次のお菓子を表示する
            collSweets.SetActive(false);
            collObj.nextSweets.SetActive(true);
            // 順番にベルトコンベアの開始位置に移動
            if (onlyDropObj.nextLaneNum == 0)
            {
                collObj.nextSweets.transform.position = sOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;
            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collObj.nextSweets.transform.position = sTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
                onlyMinigameIn.duringPlay = true;
            }
        }
        else if ((collSweets.tag == "CCake" || collSweets.tag == "ChocoHarden") && collSweets.layer == 10)
        {
            // 端まで来たのでゲームを呼びだす
            // 最後のお菓子なので流さない
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            onlyMinigameIn.duringPlay = true;
        }
        else
        {
            // ゲーム済みでなければ、オブジェクトの位置をベルトコンベアの開始位置に移動
            if (onlyDropObj.nextLaneNum == 0)
            {
                collSweets.transform.position = sOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collSweets.transform.position = sTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
            }
        }
    }
    // 3つのレーンの時、端に材料(お菓子)オブジェクトが接触した際の処理
    // 引  数：GameObject collSweets  接触したオブジェクト
    //         MinigameIn collObj     接触したオブジェクトのMinigameInスクリプト
    // 戻り値：なし
    void CollSweetsLaneNumberOf3(GameObject collSweets, MinigameIn collObj)
    {
        // 接触したものがゲーム済みだったら
        if ((collSweets.tag == "CBowl" || collSweets.tag == "ChocoBowl" || collSweets.tag == "OBowl") && collSweets.layer == 10)
        {
            // 端まで来たのでゲームを呼びだす
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            // 今のお菓子を非表示にし、次のお菓子を表示する
            collSweets.SetActive(false);
            collObj.nextSweets.SetActive(true);
            // 順番にベルトコンベアの開始位置に移動
            if (onlyDropObj.nextLaneNum == 0)
            {
                collObj.nextSweets.transform.position = tOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;
            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collObj.nextSweets.transform.position = tTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;
            }
            else if (onlyDropObj.nextLaneNum == 2)
            {
                collObj.nextSweets.transform.position = tThreeLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
                onlyMinigameIn.duringPlay = true;
            }
        }
        else if ((collSweets.tag == "CCake" || collSweets.tag == "ChocoHarden" || collSweets.tag == "OrangeJelly") && collSweets.layer == 10)
        {
            // 端まで来たのでゲームを呼びだす
            // 最後のお菓子なので流さない
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            onlyMinigameIn.duringPlay = true;
        }
        else
        {
            // ゲーム済みでなければ、オブジェクトの位置をベルトコンベアの開始位置に移動
            if (onlyDropObj.nextLaneNum == 0)
            {
                collSweets.transform.position = tOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;

            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collSweets.transform.position = tTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum++;

            }
            else if (onlyDropObj.nextLaneNum == 2)
            {
                collSweets.transform.position = tThreeLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;

            }
        }
    }
    // 4つのレーンの時、端に材料(お菓子)オブジェクトが接触した際の処理
    // 引  数：GameObject collSweets  接触したオブジェクト
    //         MinigameIn collObj     接触したオブジェクトのMinigameInスクリプト
    // 戻り値：なし
    void CollSweetsLaneNumberOf4(GameObject collSweets, MinigameIn collObj)
    {
        // 接触したものがゲーム済みだったら
        if ((collSweets.tag == "CBowl" || collSweets.tag == "ChocoBowl" || collSweets.tag == "OBowl" || collSweets.tag == "DBowl") && collSweets.layer == 10)
        {
            // 端まで来たのでゲームを呼びだす
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            // 今のお菓子を非表示にし、次のお菓子を表示する
            collSweets.SetActive(false);
            collObj.nextSweets.SetActive(true);
            // 順番にベルトコンベアの開始位置に移動
            if (onlyDropObj.nextLaneNum == 0)
            {
                collObj.nextSweets.transform.position = foOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;

            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collObj.nextSweets.transform.position = foTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;

            }
            else if (onlyDropObj.nextLaneNum == 2)
            {
                collObj.nextSweets.transform.position = foThreeLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;

            }
            else if (onlyDropObj.nextLaneNum == 3)
            {
                collObj.nextSweets.transform.position = foFourLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
                onlyMinigameIn.duringPlay = true;
            }
        }
        else if ((collSweets.tag == "CCake" || collSweets.tag == "ChocoHarden" || collSweets.tag == "OrangeJelly" || collSweets.tag == "DoughCookie") && collSweets.layer == 10)
        {
            // 端まで来たのでゲームを呼びだす
            // 最後のお菓子なので流さない
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            onlyMinigameIn.duringPlay = true;
        }
        else
        {
            // ゲーム済みでなければ、オブジェクトの位置をベルトコンベアの開始位置に移動
            if (onlyDropObj.nextLaneNum == 0)
            {
                collSweets.transform.position = foOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collSweets.transform.position = foTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
            }
            else if (onlyDropObj.nextLaneNum == 2)
            {
                collSweets.transform.position = foThreeLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
            }
            else if (onlyDropObj.nextLaneNum == 3)
            {
                collSweets.transform.position = foFourLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
            }
        }
    }
    // 端のコリジョンボックスに接触したら
    private void OnTriggerEnter(Collider other)
    {
        // ミニゲーム中でないかどうか
        if (onlyMinigameIn.duringPlay == false) { 
        // ランダムに数字を出す
           int randomNum = Random.Range(0, laneMax);
        // 接触したオブジェクトの情報を読み込む
        GameObject collSweets = GameObject.Find(other.name);
        MinigameIn collObj = other.GetComponent<MinigameIn>();
        // 時間を待つ
        StartCoroutine("StopNextShed");
            if (laneMax == 1)       // ベルトコンベアが1つ 
            {
                CollSweetsLaneNumberOf1(collSweets, collObj); // 接触処理の呼び出し
            }
            else if (laneMax == 2)  // ベルトコンベアが2つ
            {
                CollSweetsLaneNumberOf2(collSweets, collObj); // 接触処理の呼び出し
            }
            else if (laneMax == 3)  // ベルトコンベアが3つ
            {
                CollSweetsLaneNumberOf3(collSweets, collObj); // 接触処理の呼び出し
            }
            else if (laneMax == 4)  // ベルトコンベアが4つ
            {
                CollSweetsLaneNumberOf4(collSweets, collObj); // 接触処理の呼び出し
            }
        }
        // お菓子にかかっていた力を初期化
        other.gameObject.GetComponent<Rigidbody>().velocity = Vector3.zero;
        other.gameObject.GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
    }
    // 待ち時間の発生
    IEnumerator StopNextShed()
    {
        yield return new WaitForSecondsRealtime(3.0f);
    }
}
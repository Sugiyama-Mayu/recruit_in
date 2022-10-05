using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
// M.S
// リザルトシーンでのボタン処理
public class ResultButton : MonoBehaviour
{
    // スクリプト変数
    public GameResult gameResult;
    // タイトルを呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallTitle()
    {
        SceneManager.LoadScene("title");
    }
    // リトライする
    // 引  数：なし
    // 戻り値：なし
    public void CallRetry()
    {
        // 遊んだステージと同じシーンを呼ぶ
        switch (gameResult.sceneNum)
        {
            case 1:
                SceneManager.LoadScene("FirstScene");
                break;
            case 2:
                SceneManager.LoadScene("SecondScene");
                break;
            case 3:
                SceneManager.LoadScene("ThirdScene");
                break;
            case 4:
                SceneManager.LoadScene("ForthScene");
                break;
        }
    }
    // ステージセレクトを呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallStageSelect()
    {
        SceneManager.LoadScene("SelectScene");
    }
}

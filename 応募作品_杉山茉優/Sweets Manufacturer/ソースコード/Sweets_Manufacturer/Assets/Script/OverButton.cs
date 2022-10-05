using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
// M.S
// ゲームオーバー時のボタン処理
public class OverButton : MonoBehaviour
{
    // スクリプト変数
    public ResultManager resultManager;
    // 削除するオブジェクト
    public GameObject destroyObj;
    //タイトルを呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallTitle()
    {
        SceneManager.LoadScene("title");
        Destroy(destroyObj);  // オブジェクトを削除
    }
    // リトライする
    // 引  数：なし
    // 戻り値：なし
    public void CallRetry()
    {
        // 遊んだステージと同じシーンを呼ぶ
        switch (resultManager.nowSeceneNum)
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
        Destroy(destroyObj);  // オブジェクトを削除
    }
    // ステージセレクトを呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallStageSelect()
    {
        SceneManager.LoadScene("SelectScene");
        Destroy(destroyObj);  // オブジェクトを削除
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
// M.S
// ステージセレクトシーンとタイトルシーンでのボタン処理
public class StageSelectTitleButton : MonoBehaviour
{
    // 通常モードとハードモードの切り替えボタン
    public Button modeChangeButton;
    void Start()
    {
        // ハードモードになっていたら
        if(GameManager.hardmode == true)
        {
            // ボタンの色をシアンにする
            modeChangeButton.GetComponent<Image>().color = Color.cyan;
        }
    }
    // セレクトシーンを呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallGameSecen()
    {
        SceneManager.LoadScene("SelectScene");
    }
    // ゲームの終了
    // 引  数：なし
    // 戻り値：なし
    public void ExitGame()
    {
        Application.Quit();
    }
    // ステージ1を呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallMainGame1()
    {
        SceneManager.LoadScene("FirstScene");
    }
    // ステージ2を呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallMainGame2()
    {
        SceneManager.LoadScene("SecondScene");
    }
    // ステージ3を呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallMainGame3()
    {
        SceneManager.LoadScene("ThirdScene");
    }
    // ステージ4を呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallMainGame4()
    {
        SceneManager.LoadScene("ForthScene");
    }
    // コレクションシーンを呼ぶ
    // 引  数：なし
    // 戻り値：なし
    public void CallPictreBook()
    {
        SceneManager.LoadScene("Collect");
    }
    // 通常モード・ハードモードの切り替え
    // 引  数：なし
    // 戻り値：なし
    public void ChangeMode()
    {
        // ハードモードかどうか
        if(GameManager.hardmode == true)
        {
            // 通常モードにする
            GameManager.hardmode = false;
            // ボタンの色を白
            modeChangeButton.GetComponent<Image>().color = Color.white;
        }
        else
        {
            // ハードモードにする
            GameManager.hardmode = true;
            // ボタンの色をシアン
            modeChangeButton.GetComponent<Image>().color = Color.cyan;
        }
    }
}

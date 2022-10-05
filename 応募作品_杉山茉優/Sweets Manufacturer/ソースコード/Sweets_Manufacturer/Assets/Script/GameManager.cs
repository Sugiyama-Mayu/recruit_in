using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// チュートリアルや倍速などの設定
public class GameManager : MonoBehaviour
{
    public int GameStatus = 0;    // カメラ変更数字
    public int tutorialOrder = 0; // チュートリアル表示順番
    public GameObject firstText;  // チュートリアルテキスト1
    public GameObject secondText; // チュートリアルテキスト2
    public GameObject thirdText;  // チュートリアルテキスト3
    public ResultManager resultManager;

    Camera cam;                     // カメラ
    public Vector3 offset;          // カメラの位置変数
    public static bool hardmode;    // ハードモードONフラグ
    private void Start()
    {
        cam = Camera.main;
        // ハードモードの場合、倍速にする
        if (hardmode == true)
        {
            Time.timeScale = 2;
        }
        else
        {
            Time.timeScale = 1;
        }
    }
    void Update()
    {
        // ハードモードではなく、ステージ1の場合
        if (hardmode != true && resultManager.nowSeceneNum == 1) {
            // チュートリアルテキストの表示
            if (tutorialOrder == 0)
            {
                StartCoroutine("FirstText");  
            } else if (tutorialOrder == 2)
            {
                StartCoroutine("SecondText");
            } else if (tutorialOrder == 5)
            {
                StartCoroutine("ThirdText");
            }
        }       
    }    
    // プレイヤーがいる位置にカメラの位置を変える関数
    // 引  数：なし
    // 戻り値：なし
    public void ChangeMiniGamePosCamera()
    {
        if (GameStatus == 1)
        {
            offset = new Vector3(20, 2.3f, 0.2f);
            cam.transform.position = offset;
            cam.transform.rotation = Quaternion.Euler(73, 0, 0);
        }      
    }
    // ミニゲーム位置にカメラの位置を変える関数
    // 引  数：なし
    // 戻り値：なし
    public void ChangeMainPosCamera()
    {
        if (GameStatus == 0)
        {
            // 通常時のカメラの位置
            offset = new Vector3(0, 9.0f, -4.0f);
            cam.transform.position = offset;
            cam.transform.rotation = Quaternion.Euler(70, 0, 0);
        }
    }
    // チュートリアルテキスト1の表示
    IEnumerator FirstText()
    {
        firstText.SetActive(true);
        tutorialOrder = 1;
        Time.timeScale = 0;
        yield return new WaitForSecondsRealtime(5.0f);
        firstText.SetActive(false);
        Time.timeScale = 1;
        tutorialOrder = 2;   
    }
    // チュートリアルテキスト2の表示
    IEnumerator SecondText()
    {
        secondText.SetActive(true);
        tutorialOrder = 3;
        Time.timeScale = 0;
        yield return new WaitForSecondsRealtime(5.0f);
        secondText.SetActive(false);
        Time.timeScale = 1;
        tutorialOrder = 4;
    }
    // チュートリアルテキスト3の表示
    IEnumerator ThirdText()
    {
        thirdText.SetActive(true);
        tutorialOrder = 6;
        Time.timeScale = 0;
        yield return new WaitForSecondsRealtime(5.0f);
        thirdText.SetActive(false);
        Time.timeScale = 1;
        tutorialOrder = 7;
    }
}

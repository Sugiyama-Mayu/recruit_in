using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ゲームプレイ中(ベルトコンベア画面)のBGMの管理
public class AudioScript : MonoBehaviour
{
    public GameObject soundClearBGM;  // クリアBGM
    public GameObject soundOverBGM;   // ゲームオーバーBGM
    public GameObject soundBGM;       // ゲーム中BGM
    // 流すBGMを操作する変数 1：ゲーム中BGM 2：クリアBGM 3：ゲームオーバーBGM
    int audioNum;  
    void Start()
    {
        audioNum = 1;  // 最初はゲーム中BGM
    }
    void Update()
    {
        if(audioNum == 1) {     // ゲーム中BGM
            soundBGM.SetActive(true);
            soundClearBGM.SetActive(false);
            soundOverBGM.SetActive(false);
            audioNum = 0;
        }
        else if(audioNum == 2) // クリアBGM
        {
            soundClearBGM.SetActive(true);
            soundOverBGM.SetActive(false);
            soundBGM.SetActive(false);
            audioNum = 0;
        }
        else if(audioNum == 3) // ゲームオーバーBGM
        {
            soundOverBGM.SetActive(true);
            soundClearBGM.SetActive(false);
            soundBGM.SetActive(false);
            audioNum = 0;
        }
    }
    // BGMの変更変数のセット
    // 引  数：int   num  1：ゲーム中BGM 2：クリアBGM 3：ゲームオーバーBGM
    // 戻り値：なし
    public void SetChangeBGM(int num)
    {
        audioNum = num;
    }
}

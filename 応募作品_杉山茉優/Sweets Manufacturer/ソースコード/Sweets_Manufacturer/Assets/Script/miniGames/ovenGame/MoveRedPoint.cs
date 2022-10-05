using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// オーブン、冷蔵庫のゲージを止めるゲームの
// 目押しの赤い枠の制御スクリプト
public class MoveRedPoint : MonoBehaviour
{
    private int value;
    public GameObject redPosObj;
    public OvenSceneManager ovenOrCoolSceneManager;
    public bool stopButton;
    void Start()
    {
        stopButton = false;
        // ランダムの数字を取得して、ゲーム中の止める位置を決める
        value = Random.Range(1, 3 + 1);
        switch (value)
        {
            case 1:
                redPosObj.transform.position = new Vector3(redPosObj.transform.position.x, redPosObj.transform.position.y, 0.0f);
                break;
            case 2:
                redPosObj.transform.position = new Vector3(redPosObj.transform.position.x, redPosObj.transform.position.y, -0.6f);
                break;
            case 3:
                redPosObj.transform.position = new Vector3(redPosObj.transform.position.x, redPosObj.transform.position.y, -1.3f);
                break;
        }
    }
    // ゲーム成功をtrueにする
    private void OnTriggerStay(Collider other)
    {
        if (stopButton == true)
        {
            if(ovenOrCoolSceneManager.GetNowGameName() == "Ovengame")
            {
                ovenOrCoolSceneManager.setOvenGameSuccess(true);
            }
            else if(ovenOrCoolSceneManager.GetNowGameName() == "CoolGame")
            {
                ovenOrCoolSceneManager.setCoolGameSuccess(true);
            }
        }
    }
}

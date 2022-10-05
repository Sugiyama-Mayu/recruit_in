using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// 型抜きしたクッキーオブジェクトの初期化と
// クッキーの型抜きゲームの当たり判定プログラム(型抜きの穴)
public class CutOutColl : MonoBehaviour
{
    // 抜き型のオブジェクト
    public MoveCutOut moveCutOut;
    // 型抜きしたクッキーのオブジェクト
    public GameObject cutOutDough;
    // 初期化フラグ
    public bool startFlag;
    // 初期位置
    private Vector3 initialPos;
    void Start()
    {
        // 初期位置にこのオブジェクト(型抜きの穴)の発生位置を保存
        initialPos = this.gameObject.transform.position;
        // 初期化フラグをfalse
        startFlag = false;
    }
    void Update()
    {
        // 確認用:ループでこのプログラムを通ったら+1
        moveCutOut.cookieStampNum++;
        // 初期化フラグはtrueかどうか
        if(startFlag == true)
        {
            // 型抜きの穴を非アクティブにする
            this.gameObject.SetActive(false);
            // 初期化フラグをfalse
            startFlag = false;
            // 型抜きしたクッキーの角度を初期化
            cutOutDough.transform.eulerAngles = new Vector3(0.0f, 180.0f, 0.0f);
            // 型抜きしたクッキーを非アクティブにする
            cutOutDough.SetActive(false);
        }
    }
    // オブジェクトと型抜きの穴が接触しているか
    private void OnTriggerEnter(Collider other)
    {
        // 型抜きの穴が抜き型と接触したかどうか
        if (other.gameObject.tag == "CutOut")
        {
            // 型抜きの穴と接触していたらcolListにこのオブジェクトを追加
            moveCutOut.SetCutOutCol(this.gameObject);
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// クッキーの型抜きゲームの当たり判定プログラム(生地)
public class DoughCutOut : MonoBehaviour
{
    // 抜き型のオブジェクト
    public MoveCutOut moveCutOut;
    // オブジェクトと生地が接触しているか
    private void OnTriggerEnter(Collider other)
    {
        // 生地が抜き型と接触したかどうか
        if (other.gameObject.tag == "CutOut")
        {
            // 抜き型と接触していたらcolListにこのオブジェクトを追加
            moveCutOut.SetCutOutCol(this.gameObject);
        }
    }
    void Update()
    {
        // 確認用:ループでこのプログラムを通ったら+1
        moveCutOut.cookieDoughNum++;
    }
}


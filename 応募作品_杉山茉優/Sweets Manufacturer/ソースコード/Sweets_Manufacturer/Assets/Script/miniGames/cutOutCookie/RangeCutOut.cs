using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// クッキーの型抜きゲームの当たり判定プログラム(範囲外領域)
public class RangeCutOut : MonoBehaviour
{
    // 抜き型のオブジェクト
    public MoveCutOut moveCutOut;
    // オブジェクトと範囲外領域が接触しているか
    private void OnTriggerEnter(Collider other)
    {
        // 範囲外領域が抜き型と接触したかどうか
        if (other.gameObject.tag == "CutOut")

        {
            // 抜き型と接触していたらcolListにこのオブジェクトを追加
            moveCutOut.SetCutOutCol(this.gameObject);
        }
    }
    void Update()
    {
        // 確認用:ループでこのプログラムを通ったら+1
        moveCutOut.cookieRange++;
    }
}

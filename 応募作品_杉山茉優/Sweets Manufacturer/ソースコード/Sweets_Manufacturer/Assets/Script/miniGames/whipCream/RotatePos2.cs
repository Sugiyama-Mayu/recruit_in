using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// ボウルを混ぜるゲームの当たり判定2の処理
public class RotatePos2 : MonoBehaviour
{
    // 1回転確認オブジェクト2
    public GameObject rotatePos2;
    // 1回転確認オブジェクト2と泡だて器の当たり判定保存変数
    private bool rotate2;
    // チョコのボウルだった場合のボウル表面を回転させるオブジェクト
    public GameObject chocoPlate;
    // チョコのボウルかどうかフラグ
    public bool isChoco;
    void Start()
    {
        // 初期化
        rotate2 = false;
    }
    private void OnTriggerEnter(Collider other)
    {
        // まだ泡だて器と当たっていないかどうか
        if (rotate2 == false)
        {
            // 当たり判定を保存
            rotate2 = true;
            // チョコのボウルかどうか
            if (isChoco == true)
            {
                // ボウルの表面を回転させる
                chocoPlate.transform.Rotate(0.0f, 90.0f, 0.0f);
            }
        }
    }
    // 1回転確認オブジェクト2の泡だて器との当たり判定のゲッター、セッター
    // ゲッター：bool rotate1   true 当たっている false 当たっていない
    // セッター：bool           true 当たっている false 当たっていない
    public bool RotateTerritoryFlag
    {
        get { return rotate2; }
        set { rotate2 = value; }
    }
}

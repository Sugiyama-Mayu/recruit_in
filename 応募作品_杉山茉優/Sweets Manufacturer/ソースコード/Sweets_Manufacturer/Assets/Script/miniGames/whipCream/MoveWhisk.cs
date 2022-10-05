using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ボウルを混ぜるゲームの泡だて器の移動
public class MoveWhisk : MonoBehaviour
{
    // 泡だて器のオブジェクト
    public GameObject whisk;
    // 泡だて器の初期位置
    private Vector3 initialPos;
    void Start()
    {
        // 泡だて器の初期位置の保存
        initialPos = this.gameObject.transform.position;
    }
    private void Update()
    {
        // 左クリックをしたら
        if (Input.GetMouseButton(0))
        {
            // マウスの位置の取得
            Vector3 mousPos = Input.mousePosition;
            // 3DなのでZ軸を当てはめる
            mousPos.z = 5.0f;
            // マウスの位置を3Dの座標に変更
            Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
            // 泡だて器のY座標を初期位置のY座標にする
            mouseWorldPos.y = initialPos.y;
            // マウスの位置に泡だて器を置く
            whisk.transform.position =
                new Vector3(mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);
        }
    }
}

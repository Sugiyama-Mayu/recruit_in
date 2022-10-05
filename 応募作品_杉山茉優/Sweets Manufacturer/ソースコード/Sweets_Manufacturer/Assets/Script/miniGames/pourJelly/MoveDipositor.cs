using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ディポジッターの移動処理
public class MoveDipositor : MonoBehaviour
{
    // ディポジッターオブジェクト
    public GameObject dipositor;
    private float adjustmentX; // 移動位置の調整X座標
    private float adjustmentY; // 移動位置の調整Z座標
    private void Start()
    {
        adjustmentX = 5.0f; // 移動位置の調整X座標
        adjustmentY = 4.0f; // 移動位置の調整Z座標
    }
    void Update()
    {
        // ディポジッターのボックスコライダーを非アクティブにする
        dipositor.GetComponent<BoxCollider>().enabled = false;
        // マウスの位置の取得
        Vector3 mousPos = Input.mousePosition;
        // 3DなのでZ軸を当てはめる
        mousPos.z = 8.0f;
        // マウスの位置を3Dの座標に変更
        Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
        // ディポジッターの位置の調整
        mouseWorldPos.y = this.gameObject.transform.position.y;
        mouseWorldPos.x = mouseWorldPos.x + adjustmentX;
        mouseWorldPos.z = mouseWorldPos.z + adjustmentY;
        // マウスの位置にディポジッターを置く
        dipositor.transform.position = mouseWorldPos;

        // 左ボタンを押しているかどうか
        if (Input.GetMouseButton(0))
        {
            // ディポジッターのボックスコライダーをアクティブにする
            dipositor.GetComponent<BoxCollider>().enabled = true;
        }
    }
}

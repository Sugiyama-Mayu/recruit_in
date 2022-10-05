using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットゲームのナイフ位置移動プログラム
public class MoveKnife : MonoBehaviour
{
    // ナイフオブジェクト変数
    public GameObject knifeObj;
    void Update()
    {
        // マウスのポジションの取得
        Vector3 mousePos = Input.mousePosition;
        // 3Dの情報にするためのマウスのポジションのZ軸数値の設定
        mousePos.z = 3.0f;
        // マウスポジションを3D座標に変換、mouseWorldに入れる
        Vector3 mouseWorld = Camera.main.ScreenToWorldPoint(mousePos);
        // ナイフオブジェクトの位置をマウスの位置へ更新
        knifeObj.transform.position = new Vector3(mouseWorld.x, knifeObj.transform.position.y, mouseWorld.z);
    }
}

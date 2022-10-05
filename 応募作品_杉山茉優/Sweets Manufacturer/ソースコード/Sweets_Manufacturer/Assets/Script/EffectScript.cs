using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// マウスカーソルエフェクトの発生
public class EffectScript : MonoBehaviour
{
    void Update()
    {
        // マウスカーソルの3Dの位置を取得
        Vector3 mousePos = Input.mousePosition;
        mousePos.z = 10.0f;
        Vector3 mousePosWorld = Camera.main.ScreenToWorldPoint(mousePos);
        // エフェクトをマウスの位置に移動
        mousePosWorld.y = 1.1f;
        this.transform.position = mousePosWorld;
    }
}

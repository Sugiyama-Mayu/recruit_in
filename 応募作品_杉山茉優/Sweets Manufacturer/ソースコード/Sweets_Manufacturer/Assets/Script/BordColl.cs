using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// ベルトコンベアにプレイヤーが当たった時の処理
public class BordColl : MonoBehaviour
{
    // マップの中央の位置の保存のため
    public GameObject mapCenter;
    public GameObject playerObj;
    private ClickObject playerScript;
    private void Start()
    {
      playerScript = playerObj.GetComponent<ClickObject>();
    }   
    // 接触しているかどうか
    private void OnCollisionStay(Collision collision)
    {   // 接触したオブジェクトがプレイキャラかどうか
        if (collision.gameObject.tag == "Player")
        {
            playerScript.SetHitObjFlag(false);  // オブジェクトを追いかけるのをやめる
            // 中央方向へ向く角度を取得
            Vector3 directionVector = playerObj.transform.position - mapCenter.transform.position;
            Quaternion playerRotate = Quaternion.LookRotation(directionVector);
            //オブジェクトの中央方向を向いて進む
            collision.transform.eulerAngles = new Vector3(0.0f, playerRotate.eulerAngles.y, 0.0f);
            collision.transform.position += playerObj.transform.forward * -1 * 0.5f;
        }
    }
}

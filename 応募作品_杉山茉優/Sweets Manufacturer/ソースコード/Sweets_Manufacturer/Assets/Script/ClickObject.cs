using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// プレイヤー挙動スクリプト
public class ClickObject : MonoBehaviour
{
    private RaycastHit hit;
    private GameObject hitObj; // ヒットしたオブジェクト
    private string hitObjName; // ヒットしたオブジェクトの名前
    public GameObject player;  // プレイキャラオブジェクト
    private bool hitObjFlag;   // オブジェクトを追いかけるフラグ
    private float speed;       // プレイキャラの移動スピード
    private string hitObjTag;  // 追いかけるオブジェクトのタグ
    public GameObject mapCenter;  // マップの中央オブジェクト
    public Animator animatorChef; // プレイキャラのアニメーター

    // 対象オブジェクトにタグが設定されてなければ動きません。
    void Start()
    {
        hitObjFlag = false;
        speed = 3.0f;        // 歩くスピード
    }
    void Update()
    {
        if (hitObjFlag == true)
        {
            // オブジェクトがゲーム処理済みなら追いかけるのをやめる
            if (hitObj.layer == 10)
            {
                hitObjFlag = false;
            }
        }

        // 追いかけているオブジェクトがなかったら
        if (hitObjFlag == false)
        {
            // 歩くアニメーションを止める
            animatorChef.SetBool("isWalk", false);
            // 左クリックでオブジェクトとマウスが接触しているか
            if (Input.GetMouseButton(0))
            {
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                Vector3 direction = new Vector3(0.0f, 0.0f, 1.0f);
                // マウスと接触していたら
                if (Physics.Raycast(ray, out hit))
                {
                    // 接触オブジェクトの情報を保存
                    hitObj = hit.collider.gameObject;
                    hitObjName = hit.collider.gameObject.name;
                    // レイヤーがLiveならば
                    // hitObjFlagをtrueにし、ヒットしたオブジェクトの取得
                    if (hitObj.layer == 11 && (hitObj.tag == "CBowl" ||
                        hitObj.tag == "CCake" || hitObj.tag == "OrangeJelly" || 
                        hitObj.tag == "OBowl" || hitObj.tag == "ChocoBowl" ||
                        hitObj.tag == "ChocoHarden" || hitObj.tag == "DBowl" ||
                        hitObj.tag == "DoughCookie"))
                    {
                        hitObjFlag = true;               
                    }
                }
            }
        }

        // オブジェクトを追いかけるフラグがtrueだったら
        if (hitObjFlag == true)
        {
            // 歩くアニメーションをする
            animatorChef.SetBool("isWalk", true);
            // オブジェクト方向へ向く角度を取得
            Vector3 directionVector = player.transform.position - hitObj.transform.position;
            Quaternion playerRotate = Quaternion.LookRotation(directionVector);
            // オブジェクトの方向を向く
            player.transform.eulerAngles = new Vector3(0.0f, playerRotate.eulerAngles.y, 0.0f);
            // オブジェクトの方向へ進む                 
            player.transform.position += transform.forward * -1 * speed * Time.unscaledDeltaTime;
            // オブジェクトのタグを取得
            hitObjTag = hitObj.tag;
        }      
    }
    // オブジェクトを追いかけるフラグのセッター
    public void SetHitObjFlag(bool judge)
    {
        hitObjFlag = judge;
    }
}
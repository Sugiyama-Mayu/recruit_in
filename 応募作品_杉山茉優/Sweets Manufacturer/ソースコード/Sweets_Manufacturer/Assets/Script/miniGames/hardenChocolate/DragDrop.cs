using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// クラッカーをチョコに入れるゲームの
// クラッカーのドラッグ＆ドロップの処理プログラム
public class DragDrop : MonoBehaviour
{
    public bool startCracker;  // M.S クラッカーの位置の初期化フラグ
    Plane plane;
    bool isGrabbing;
    private int isTrigger;     // 0は初期状態 1は設置した 2は設置完了
    public DragDrop cracker1;
    public DragDrop cracker2;
    public DragDrop cracker3;
    public DragDrop cracker4;
    public DragDrop cracker5;
    public DragDrop cracker6;
    public DragDrop cracker7;
    public DragDrop cracker8;
    private GameObject hitObj;
    private Vector3 initialPos; // クラッカーの初期位置の保存変数
    public Chocodrop chocodrop;
    void Start()
    {
        initialPos = this.transform.position;       //  M.S クラッカーの初期位置の保存
        startCracker = false;                       //  M.S クラッカーの位置の初期化フラグをfalse
        plane = new Plane(Vector3.up, Vector3.up);
        isTrigger = 0;
    }
    bool crackerAllRayColl()
    {
        if(cracker1.isGrabbing == false && cracker2.isGrabbing == false 
            && cracker3.isGrabbing == false && cracker4.isGrabbing == false
            && cracker5.isGrabbing == false && cracker6.isGrabbing == false 
            && cracker7.isGrabbing == false && cracker8.isGrabbing == false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Update()
    {
        // M.S クラッカーの位置初期化フラグがtrueでクラッカーのlayerがLiveでタグがcrackerかどうか
        if (startCracker == true && this.gameObject.layer == 11
            && this.gameObject.tag == "cracker")
        {
            this.transform.position = initialPos; // クラッカーの位置を初期位置にセット
            startCracker = false;                 // クラッカーの位置初期化フラグをfalse
        }
        if (Input.GetMouseButton(0) && isGrabbing == false
            && crackerAllRayColl() == true)
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            // マウスの位置の取得
            Vector3 mousPos = Input.mousePosition;
            // 3DなのでZ軸を当てはめる
            mousPos.z = 10.0f;
            // マウスの位置を3Dの座標に変更
            Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, Mathf.Infinity))
            {
                if (hit.collider.gameObject.layer == 11 && hit.collider.gameObject.tag == "cracker")
                {
                    hitObj = hit.collider.gameObject;
                    hitObj.transform.eulerAngles = new Vector3(90.0f, 0.0f, 0.0f);
                    // 運んでいるフラグをtrue
                    isGrabbing = true;
                    // M.S Y座標以外をマウスポジションにする
                    hit.collider.transform.position = new Vector3(mouseWorldPos.x, hitObj.transform.position.y, mouseWorldPos.z);
                    // M.S クラッカーの当たり判定を運んでいる間は消す
                    hitObj.GetComponent<BoxCollider>().enabled = false;
                }
            }
        }
        if (Input.GetMouseButton(0) && isGrabbing == true)
        {
            Vector3 mousPos = Input.mousePosition;
            // 3DなのでZ軸を当てはめる
            mousPos.z = 10.0f;
            // マウスの位置を3Dの座標に変更
            Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
            hitObj.transform.position = new Vector3(mouseWorldPos.x, hitObj.transform.position.y, mouseWorldPos.z);
        }

        if (isGrabbing == true && Input.GetMouseButtonUp(0))
        {
            if (Input.GetMouseButtonUp(0))
            {
                isGrabbing = false;
                // M.S クラッカーの当たり判定をドロップ時に復活させる
                hitObj.GetComponent<BoxCollider>().enabled = true;
            }
        }

    }
    public void SetIsTrigger(int change)
    {
        isTrigger = change;
    }
}

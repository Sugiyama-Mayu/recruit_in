using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// イチゴを飾るゲームのクリック時の
// イチゴとマウスとの当たり判定プログラム
public class Strawpoint : MonoBehaviour
{
    Plane plane;
    bool isGrabbing;
    private bool collBerryJudge;
    Transform cube;
    private int isTrigger;     // 0は初期状態 1は設置した 2は設置完了
    public GameObject Berry;
    Rigidbody movestrawBerryRid;
    public BerryCrear berryclear;
    void Start()
    {
        plane = new Plane(Vector3.up, Vector3.up);
        collBerryJudge = false;
        movestrawBerryRid = Berry.GetComponent<Rigidbody>();
    }
    void Update()
    {
        // マウスの位置の取得
        Vector3 mousPos = Input.mousePosition;
        // 3DなのでZ軸を当てはめる
        mousPos.z = 5.0f;
        // マウスの位置を3Dの座標に変更
        Ray ray = Camera.main.ScreenPointToRay(mousPos);
        RaycastHit hit = new RaycastHit();
        // Vector3 direction = new Vector3(0.0f, 0.0f, 1.0f);
        // マウスと接触していたら
        if (Physics.Raycast(ray, out hit))
        {
            Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
            // Y軸
            mouseWorldPos.y = 3.6f;
            // マウスの位置にする
            this.transform.position = new Vector3(mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);
            // いちごの当たり判定をを消す
            Berry.GetComponent<BoxCollider>().enabled = false;
        }
    }
    private void OnTriggerEnter(Collider other)
    {
        if (isGrabbing == false)
        {
            GameObject Chocobox;
            Chocobox = GameObject.Find("Main Camera");
            collBerryJudge = true;
            isTrigger = 2;
            Berry.layer = 10;
        }

    }
    public void SetIsTrigger(int change)
    {
        isTrigger = change;
    }
}

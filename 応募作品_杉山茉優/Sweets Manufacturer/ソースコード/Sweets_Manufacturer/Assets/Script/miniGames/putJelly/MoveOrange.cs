using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// オレンジの移動・配置処理
public class MoveOrange : MonoBehaviour
{
    // オレンジオブジェクト
    public GameObject orange;
    private RaycastHit hit;
    // レイと当たったオブジェクトをいれる変数
    GameObject hitObj;
    // マウスの位置
    Vector3 mouseWorldPos;
    private float adjustmentY;     // 移動位置の調整Y座標
    private float adjustmentDownY; // 配置位置の調整Y座標
    // 持ち上げられているフラグ
    public bool lift;
    // オレンジの初期位置
    private Vector3 initialObjPos;
    // 初期化フラグ
    public bool startFlag;
    void Start()
    {
        // 初期化
        startFlag = false;
        lift = false;
        initialObjPos = this.gameObject.transform.position;
        adjustmentY = 0.8f;     // 移動位置の調整Y座標
        adjustmentDownY = 0.5f; // 配置位置の調整Y座標
    }
    void Update()
    {
        // 初期化フラグがtrueでまだ配置されていないオレンジかどうか
        if (startFlag == true && this.gameObject.tag == "Orange")
        {
            // オレンジを初期位置に戻す
            this.transform.position = initialObjPos;
            startFlag = false;
        }
        // 左ボタンをクリックしたかどうか
        if (Input.GetMouseButtonDown(0))
        {
            // マウス位置からレイを飛ばす
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            Vector3 direction = new Vector3(0.0f, 0.0f, 1.0f);
            // 飛ばしたレイと接触しているかどうか
            if (Physics.Raycast(ray, out hit))
            {
                // 当たったオブジェクトのタグがまだ配置されていないオレンジかどうか
                if (hit.collider.gameObject.tag == "Orange")
                {
                    // 当たったオブジェクトをhitObjに保存
                    hitObj = hit.collider.gameObject;
                    // 持ち上げられているフラグをtrue
                    lift = true;
                }
            }
        }
        // カーソル位置の取得
        Vector3 mousPos = Input.mousePosition;
        // 3DなのでZ軸を当てはめる
        mousPos.z = 7.0f;
        // マウスの位置を3Dの座標に変更
        Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
        // オレンジのY軸
        mouseWorldPos.y = adjustmentY + initialObjPos.y;
        // 左ボタンを押しているかどうか
        if (Input.GetMouseButton(0))
        {
            // 持ち上げられていて、まだ配置されていないオレンジかどうか
            if (lift == true && hitObj.tag == "Orange")
            {
                // 持ち上げられているオレンジのボックスコライダーを非アクティブにする
                hitObj.GetComponent<BoxCollider>().enabled = false;
                // マウスの位置にオレンジを上げる
                hit.transform.position 
                    = new Vector3(mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);
            }
        }
        // 左ボタンを離したかどうか
        if (Input.GetMouseButtonUp(0))
        {
            // 持ち上げられていて、まだ配置されていないオレンジかどうか
            if (lift == true && hitObj.tag == "Orange")
            {
                // 持ち上げられているフラグをfalse
                lift = false;
                // オレンジのY軸
                mouseWorldPos.y = adjustmentDownY + initialObjPos.y;
                // オレンジを配置する
                hitObj.transform.position 
                    = new Vector3(mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);
                // オレンジのボックスコライダーをアクティブにする
                hitObj.GetComponent<BoxCollider>().enabled = true;
            }
        }
    }
}

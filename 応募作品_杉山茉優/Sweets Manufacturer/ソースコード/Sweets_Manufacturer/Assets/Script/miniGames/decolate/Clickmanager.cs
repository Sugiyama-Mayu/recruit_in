using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// イチゴを飾るゲームのイチゴをクリックの管理プログラム
public class Clickmanager : MonoBehaviour
{
    public string BerryTag = "StrawBerry";
    public BerryCrear berryClear;
    void Start()
    {
    }
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Ray ray = new Ray();
            RaycastHit hit = new RaycastHit();
            ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            //マウスクリックした場所からRayを飛ばし、オブジェクトがあればtrue 
            if (Physics.Raycast(ray.origin, ray.direction, out hit, Mathf.Infinity))
            {
                if (hit.collider.gameObject.CompareTag(BerryTag) && berryClear.Berrycount < 7)
                {
                    hit.collider.gameObject.GetComponent<Clicktarget>().OnUserAction();
                }
            }
        }
    }
}

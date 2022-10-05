using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// ステージセレクトシーンの背景を動かす処理
public class SelectSceneScroll : MonoBehaviour
{
    void Start()
    {        
    }
    void Update()
    {
        float scroll = Mathf.Repeat(Time.time * 0.1f, 1);
        Vector2 offset = new Vector2(scroll, 0);
        GetComponent<Renderer>().sharedMaterial.SetTextureOffset("_MainTex", offset);
    }
}
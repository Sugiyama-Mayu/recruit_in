using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// このスクリプトがアタッチされているオブジェクトに触れると
// プレイヤーは追いかけるのをやめる
public class HitObjJudgeFalse : MonoBehaviour
{
    public ClickObject clickObject;
    // レーンを過ぎていったオブジェクトは追いかけるのをやめる
    private void OnTriggerStay(Collider other)
    {       
        if (other.gameObject.layer == 11)
        {
            clickObject.SetHitObjFlag(false);
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットのコリジョンプログラム
public class CutPos4 : MonoBehaviour
{
    private bool cut4Flag;
    void Start()
    {
        cut4Flag = false;
    }
    // カットポイントと接触したらcut4Flagをtrue
    private void OnTriggerEnter(Collider other)
    {
        cut4Flag = true;
    }
    // cut4Flagのゲッター
    // 引  数:bool cut4Flag
    // 戻り値:なし    
    public bool getCutFlag
    {
        get { return cut4Flag; }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットのコリジョンプログラム
public class CutPos1 : MonoBehaviour
{
    private bool cut1Flag; 
    void Start()
    {
        cut1Flag = false;
    }
    // カットポイントと接触したらcut1Flagをtrue
    private void OnTriggerEnter(Collider other)
    {
        cut1Flag = true;        
    }
    // cut1Flagのゲッター
    // 引  数:bool cut1Flag
    // 戻り値:なし
    public bool getCutFlag
    {
        get { return cut1Flag; }
    }
}

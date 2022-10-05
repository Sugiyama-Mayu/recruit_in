using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットのコリジョンプログラム
public class CutPos5 : MonoBehaviour
{
    private bool cut5Flag;
    void Start()
    {
        cut5Flag = false;
    }
    // カットポイントと接触したらcut5Flagをtrue
    private void OnTriggerEnter(Collider other)
    {
        cut5Flag = true;
    }
    // cut5Flagのゲッター
    // 引  数:bool cut5Flag
    // 戻り値:なし
    public bool getCutFlag
    {
        get { return cut5Flag; }
    }
}

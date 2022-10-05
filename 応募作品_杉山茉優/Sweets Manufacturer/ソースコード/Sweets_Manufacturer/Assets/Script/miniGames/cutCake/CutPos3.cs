using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットのコリジョンプログラム
public class CutPos3 : MonoBehaviour
{
    private bool cut3Flag;
    void Start()
    {
        cut3Flag = false;
    }
    // カットポイントと接触したらcut3Flagをtrue
    private void OnTriggerEnter(Collider other)
    {
        cut3Flag = true;
    }
    // cut3Flagのゲッター
    // 引  数:bool cut3Flag
    // 戻り値:なし
    public bool getCutFlag
    {
        get { return cut3Flag; }
    }
}

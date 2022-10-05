using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットのコリジョンプログラム
public class CutPos6 : MonoBehaviour
{
    private bool cut6Flag;
    void Start()
    {
        cut6Flag = false;
    }
    // カットポイントと接触したらcut6Flagをtrue
    private void OnTriggerEnter(Collider other)
    {
        cut6Flag = true;
    }
    // cut6Flagのゲッター
    // 引  数:bool cut6Flag
    // 戻り値:なし
    public bool getCutFlag
    {
        get { return cut6Flag; }
    }
}

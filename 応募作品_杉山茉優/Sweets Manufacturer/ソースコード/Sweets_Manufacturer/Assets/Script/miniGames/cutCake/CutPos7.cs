using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットのコリジョンプログラム
public class CutPos7 : MonoBehaviour
{
    private bool cut7Flag;
    void Start()
    {
        cut7Flag = false;
    }
    // カットポイントと接触したらcut7Flagをtrue
    private void OnTriggerEnter(Collider other)
    {
        cut7Flag = true;
    }
    // cut7Flagのゲッター
    // 引  数:bool cut7Flag
    // 戻り値:なし
    public bool getCutFlag
    {
        get { return cut7Flag; }
    }
}

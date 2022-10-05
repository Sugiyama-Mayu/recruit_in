using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットのコリジョンプログラム
public class CutPos2 : MonoBehaviour
{
    private bool cut2Flag;
    void Start()
    {
        cut2Flag = false;
    }
    // カットポイントと接触したらcut2Flagをtrue
    private void OnTriggerEnter(Collider other)
    {
        cut2Flag = true;
    }
    // cut2Flagのゲッター
    // 引  数:bool cut2Flag
    // 戻り値:なし
    public bool getCutFlag{
    get { return cut2Flag; }
    }
}

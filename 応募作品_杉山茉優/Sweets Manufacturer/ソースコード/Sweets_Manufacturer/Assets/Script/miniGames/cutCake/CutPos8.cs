using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットのコリジョンプログラム
public class CutPos8 : MonoBehaviour
{
    private bool cut8Flag;
    void Start()
    {
        cut8Flag = false;
    }
    // カットポイントと接触したらcut8Flagをtrue
    private void OnTriggerEnter(Collider other)
    {
        cut8Flag = true;
    }
    // cut8Flagのゲッター
    // 引  数:bool cut8Flag
    // 戻り値:なし
    public bool getCutFlag
    {
        get { return cut8Flag; }
    }
}

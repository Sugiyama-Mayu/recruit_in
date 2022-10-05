using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using UnityEngine.SceneManagement;
// M.S
// コレクションシーンのボタン、選択処理
public class CollectButton : MonoBehaviour
{
    public Collect collect;
    // ケーキオブジェの選択
    // 引  数：なし
    // 戻り値：なし
    public void CakePush()
    {
        collect.collectSelectNum = 0;
    }
    // 金のケーキオブジェの選択
    // 引  数：なし
    // 戻り値：なし
    public void GoldCakePush()
    {
        collect.collectSelectNum = 1;
    }
    // チョコクラッカーの選択
    // 引  数：なし
    // 戻り値：なし
    public void ChocoPush()
    {
        collect.collectSelectNum = 2;
    }
    // 金のチョコクラッカーの選択
    // 引  数：なし
    // 戻り値：なし
    public void GoldChocoPush()
    {
        collect.collectSelectNum = 3;
    }
    // ゼリーの選択
    // 引  数：なし
    // 戻り値：なし
    public void JellyPush()
    {
        collect.collectSelectNum = 4;
    }
    // 金のゼリーの選択
    // 引  数：なし
    // 戻り値：なし
    public void GoldJellyPush()
    {
        collect.collectSelectNum = 5;
    }
    // クッキーの選択
    // 引  数：なし
    // 戻り値：なし
    public void CookiePush()
    {
        collect.collectSelectNum = 6;
    }
    // 金のクッキーの選択
    // 引  数：なし
    // 戻り値：なし
    public void GoldCookiePush()
    {
        collect.collectSelectNum = 7;
    }
    // ステージ1トロフィーの選択
    // 引  数：なし
    // 戻り値：なし
    public void RedTrophyPush()
    {
        collect.collectSelectNum = 8;
    }
    // ステージ2トロフィーの選択
    // 引  数：なし
    // 戻り値：なし
    public void GreenTrophyPush()
    {
        collect.collectSelectNum = 9;
    }
    // ステージ3トロフィーの選択
    // 引  数：なし
    // 戻り値：なし
    public void YellowTrophyPush()
    {
        collect.collectSelectNum = 10;
    }
    // ステージ4トロフィーの選択
    // 引  数：なし
    // 戻り値：なし
    public void BlueTrophyPush()
    {
        collect.collectSelectNum = 11;
    }
    // オールステージトロフィーの選択
    // 引  数：なし
    // 戻り値：なし
    public void CrystalTrophyPush()
    {
        collect.collectSelectNum = 12;
    }
    // コレクションオブジェクト選択の進むボタン
    // 引  数：なし
    // 戻り値：なし
    public void RightButtonPush()
    {
        collect.collectSelectNum++;
        if (collect.collectSelectNum > 12)
        {
            collect.collectSelectNum = 0;
        }
    }
    // コレクションオブジェクト選択の戻るボタン
    // 引  数：なし
    // 戻り値：なし
    public void LeftButtonPush()
    {
        collect.collectSelectNum--;
        if (collect.collectSelectNum < 0)
        {
            collect.collectSelectNum = 12;
        }
    }
    // ゲームセレクトシーンに移る
    // 引  数：なし
    // 戻り値：なし
    public void CallGameSecen()
    {
        SceneManager.LoadScene("SelectScene");
    }
}
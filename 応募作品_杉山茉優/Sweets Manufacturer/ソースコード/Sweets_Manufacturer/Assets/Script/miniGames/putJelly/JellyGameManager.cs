using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// オレンジを配置するゲームのマネージャー
public class JellyGameManager : MonoBehaviour
{
    // 配置したオレンジの数
    public int putOrangeNum;
    // クリアエフェクト
    public ParticleSystem clearEffect;
    // スクリプト変数
    public ResultManager resultManager;
    public MinigameIn miniGameIn;
    // クリアサウンド
    public AudioClip soundClear;
    // オーディオソース
    AudioSource audioSource;
    void Start()
    {
        // 初期化
        putOrangeNum = 0;
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        // 全てのオレンジが配置されているかどうか
        if(putOrangeNum == 6)
        {
            // クリアエフェクトをアクティブにする
            clearEffect.gameObject.SetActive(true);
            // クリアエフェクトの発生
            clearEffect.Play();
            // クリアエフェクトを削除
            Destroy(clearEffect.gameObject, 5.0f);
            // 一度のみクリア処理を行うためputOrangeNumを+1する
            putOrangeNum++;
            // オレンジを配置するゲームクリアフラグをtrue
            resultManager.orangePutJudge = true;
            // ミニゲーム終了フラグをtrue
            miniGameIn.SetMinigameResult(true);
            // クリア効果音
            audioSource.PlayOneShot(soundClear);
        }
        else
        {
        }
    }
}

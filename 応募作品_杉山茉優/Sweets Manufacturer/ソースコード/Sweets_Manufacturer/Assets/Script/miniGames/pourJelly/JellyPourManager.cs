using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ゼリーを注ぐゲームのマネージャー
public class JellyPourManager : MonoBehaviour
{
    // 注ぎ終わったゼリーの数
    public int pourCapCount;
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
        pourCapCount = 0;
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        // 全てのゼリーに注ぎ終わっているかどうか
        if(pourCapCount == 6)
        {
            // クリアエフェクトをアクティブにする
            clearEffect.gameObject.SetActive(true);
            // クリアエフェクトを発生させる
            clearEffect.Play();
            // クリアエフェクトの削除
            Destroy(clearEffect.gameObject, 5.0f);
            // もう一度クリア処理をしないようにpourCapCountを+1する
            pourCapCount++;
            // ゼリーを注ぐゲームクリアフラグをtrue
            resultManager.orangePourJudge = true;
            // ミニゲーム終了フラグをtrue
            miniGameIn.SetMinigameResult(true);
            // クリア効果音の発生
            audioSource.PlayOneShot(soundClear);
        }
        else
        {
        }
    }
}

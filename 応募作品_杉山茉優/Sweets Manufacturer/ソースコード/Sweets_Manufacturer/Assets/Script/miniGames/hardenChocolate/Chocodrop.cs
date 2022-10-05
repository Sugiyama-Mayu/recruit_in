using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// クラッカーをチョコに入れるゲームのクリア処理プログラム
public class Chocodrop : MonoBehaviour
{
    public int dropcount;
    public ParticleSystem clearEffect;   // M.S エフェクトを入れている変数
    public ResultManager resultManager;  // M.S ResultManagerスクリプトを入れる変数
    public MinigameIn miniGameIn;        // M.S MinigameInスクリプトを入れる変数
    public AudioClip soundClear;         // M.S クリアサウンドを入れる変数
    AudioSource audioSource;             // M.S AudioSourceの変数
    void Start()
    {
        // M.S audhioSourceの作成
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        // 全てのタスクをクリアしているかどうか
        if(dropcount == 8)
        {
            // M.S クリアエフェクトをアクティブにする
            clearEffect.gameObject.SetActive(true);
            // M.S クリアエフェクトの発生
            clearEffect.Play();
            // M.S クリアエフェクトの削除
            Destroy(clearEffect.gameObject, 0.5f);
            // クリア処理を二度行わないようにdropcountに+1
            dropcount++;
            // M.S クラッカーをチョコに入れるゲームのクリアフラグをtrue
            resultManager.chocoHardenJudge = true;
            miniGameIn.SetMinigameResult(true);
            // M.S クリア効果音の発生
            audioSource.PlayOneShot(soundClear);
        }
    }
}

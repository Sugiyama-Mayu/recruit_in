using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// クッキ―の型抜きゲームのクリア処理
public class CookieManager : MonoBehaviour
{
    // クリアエフェクト
    public ParticleSystem clearEffect;
    // 型抜きオブジェクト
    public MoveCutOut moveCutOut;
    // スクリプトの変数
    public ResultManager ResultManager;
    public MinigameIn miniGameIn;
    // クリアサウンド
    public AudioClip soundClear;
    // オーディオソース
    AudioSource audioSource;
    // クッキーの型抜きゲームクリア処理済みフラグ
    bool doneClearProcess;
    void Start()
    {
        // 初期化処理
        audioSource = GetComponent<AudioSource>();
        doneClearProcess = false;
    }
    void Update()
    {
        // 全ての型抜きが完了していて、クリア処理をしていないかどうか
        if (moveCutOut.GetCookieCount() == 4 && doneClearProcess == false)
        {
            // クリアエフェクトの生成
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // クリアエフェクトをアクティブにする
            newClearEffect.gameObject.SetActive(true);
            // クリアエフェクトの位置をセット
            newClearEffect.gameObject.transform.position = clearEffect.transform.position;
            // クリアエフェクトを発生
            newClearEffect.Play();
            // クリアエフェクトを削除
            Destroy(newClearEffect.gameObject, 5.0f);
            // クッキ―の型抜きゲームクリアフラグをtrue
            ResultManager.cookieCutOutJudge = true;
            // ミニゲーム終了フラグをtrue
            miniGameIn.SetMinigameResult(true);
            // クリア効果音の発生
            audioSource.PlayOneShot(soundClear);
            // クリア処理済みにする
            doneClearProcess = true;
        }
    }
}
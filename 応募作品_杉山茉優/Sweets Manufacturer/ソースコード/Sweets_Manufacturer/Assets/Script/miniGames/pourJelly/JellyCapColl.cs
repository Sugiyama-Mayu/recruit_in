using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ゼリーを注ぐゲームの注いだ時の判定処理
public class JellyCapColl : MonoBehaviour
{
    //ゼリー側オブジェ
    public GameObject orangeJellyObj;
    // 注いだ時のエフェクト
    public ParticleSystem pourEffect;
    // スクリプト変数
    public JellyPourManager jellyPourManager;
    // 注いだ時のサウンド
    public AudioClip soundTask;
    // オーディオソース
    AudioSource audioSource;
    void Start()
    {
        // 初期化処理
        audioSource = GetComponent<AudioSource>();
    }
    private void OnTriggerEnter(Collider other)
    {
        // 注いだオブジェクトの数が7未満かどうか
        if (jellyPourManager.pourCapCount < 7)
        {
            // ゼリー側オブジェをアクティブにする
            orangeJellyObj.SetActive(true);
            // 注いだオブジェクトの数を+1する
            jellyPourManager.pourCapCount++;
            // 器のボックスコライダーを非アクティブにする
            this.gameObject.GetComponent<BoxCollider>().enabled = false;
            // 注いだ時のエフェクトを生成
            ParticleSystem newParticle = Instantiate(pourEffect);
            // 注いだ時のエフェクトをアクティブにする
            newParticle.gameObject.SetActive(true);
            // 注いだ時のエフェクトの位置をセット
            newParticle.gameObject.transform.position = this.transform.position;
            // 注いだ時のエフェクトの発生
            newParticle.Play();
            // 注いだ時のエフェクトを削除
            Destroy(newParticle.gameObject, 5.0f);
            // 注いだ時の効果音
            audioSource.PlayOneShot(soundTask);
        }
    }
}

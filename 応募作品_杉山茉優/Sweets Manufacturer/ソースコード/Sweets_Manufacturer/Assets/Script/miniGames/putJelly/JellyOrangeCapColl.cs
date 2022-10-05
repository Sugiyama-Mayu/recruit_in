using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// オレンジをゼリーに配置したときの処理
public class JellyOrangeCapColl : MonoBehaviour
{
    // スクリプトの変数
    public JellyGameManager jellyGameManager;
    // 配置時エフェクト
    public ParticleSystem putParticle;
    // 配置時サウンド
    public AudioClip soundTask;
    // オーディオソース
    AudioSource audioSource;
    void Start()
    {
        // 初期化
        audioSource = GetComponent<AudioSource>();
    }
    private void OnTriggerEnter(Collider other)
    {
        // 接触した時に接触オブジェクトのタグがOrangeかどうか
        if (other.gameObject.tag == "Orange")
        {
            // 配置時エフェクトの生成
            ParticleSystem newParticle = Instantiate(putParticle);
            // 配置時エフェクトをアクティブにする
            newParticle.gameObject.SetActive(true);
            // 配置時エフェクトの位置をセット
            newParticle.transform.position = 
                new Vector3(this.transform.position.x, putParticle.transform.position.y, this.transform.position.z);
            // 配置時エフェクトの発生
            newParticle.Play();
            // 配置時エフェクトを削除
            Destroy(newParticle.gameObject, 5.0f);
            // ゼリーのボックスコライダーを非アクティブ
            this.gameObject.GetComponent<BoxCollider>().enabled = false;
            // オレンジをStaticにする
            other.gameObject.isStatic = true;
            // オレンジオブジェのタグを配置済み(DoneOrange)にする
            other.gameObject.tag = "DoneOrange";
            // オレンジの配置数を+1する
            jellyGameManager.putOrangeNum++;
            // オレンジをゼリーの上に配置成功効果音
            audioSource.PlayOneShot(soundTask);
        }
    }
}

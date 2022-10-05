using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S クラッカーをチョコに入れるゲームの
// チョコ側当たり判定処理プログラム
public class ChocoDropJudge : MonoBehaviour
{
    public Chocodrop chocodrop;      // Chocodropスクリプトの変数
    public ParticleSystem putEffect; // チョコに置いた時のエフェクトの変数
    public AudioClip soundTask;      // チョコに置いた時の効果音の変数
    public AudioSource audioSource;  // audioSourceの変数
    // チョコと接触しているかどうか
    private void OnTriggerEnter(Collider other)
    {
        // コリジョンとクラッカーが接触しているかかつ、layerがLiveかどうか
        if (other.tag == "cracker" && other.gameObject.layer == 11)
        {
            // 処理したクラッカーの数を+1
            chocodrop.dropcount++;
            // クラッカーをチョコに刺さった角度にする
            other.transform.eulerAngles = new Vector3(0.0f,0.0f,0.0f);
            // クラッカーのstaticをtrueにする
            other.gameObject.isStatic = true;
            // クラッカーのlayerをDoneにする
            other.gameObject.layer = 10;
            // チョコのボックスコライダーをfalseにする
            this.GetComponent<BoxCollider>().enabled = false;
            // クラッカーをチョコに置いた時のエフェクトをアクティブにする
            putEffect.gameObject.SetActive(true);
            // クラッカーをチョコに置いた時のエフェクトを発生
            putEffect.Play();
            // クラッカーをチョコに置いた時のエフェクトを削除
            Destroy(putEffect.gameObject, 0.5f);
            // クラッカーをチョコに置いた時の効果音を鳴らす
            audioSource.PlayOneShot(soundTask);
            // SinkCrackerコルーチンの発生
            StartCoroutine("SinkCracker", other.gameObject);
        }
    }
    // クラッカーをチョコに置いた後の処理
    IEnumerator SinkCracker(GameObject cracker)
    {
        // 0.5秒待つ
        yield return new WaitForSecondsRealtime(0.5f);
        // クラッカーの位置をよりチョコに鎮める
        cracker.transform.position -= new Vector3(0.0f, 0.5f, 0.0f);
        // ボックスコライダーをfalseしているが
        // 一応チョコの判定オブジェクトを非アクティブする
        this.gameObject.SetActive(false);
    }
}

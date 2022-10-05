using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// イチゴを飾るゲームのクリアの管理プログラム
public class BerryCrear : MonoBehaviour
{
    public int Berrycount;
    public ParticleSystem clearEffect;
    public ResultManager resultManager;
    public MinigameIn miniGameIn;
    public AudioClip soundClear;
    AudioSource audioSource;                        // オーディオソースの作成
    void Start()
    {
        audioSource = GetComponent<AudioSource>();  // オーディオソースの作成
    }

    void Update()
    {
        if (Berrycount == 6)
        {
            Debug.Log("クリア");
            clearEffect.gameObject.SetActive(true);   // M.S エフェクトをアクティブにする
            clearEffect.Play();                       // M.S エフェクトの発生
            resultManager.cakeDecorationJudge = true;
            miniGameIn.SetMinigameResult(true);
            Berrycount++;
            audioSource.PlayOneShot(soundClear);      // M.S 音の発生
        }
    }
}

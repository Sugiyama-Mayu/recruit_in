using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ケーキのカットゲームプログラム
public class CutManager : MonoBehaviour
{
    // カットされたか判断用スクリプト変数
    public CutPos1 cutPos1Sc;
    public CutPos2 cutPos2Sc;
    public CutPos3 cutPos3Sc;
    public CutPos4 cutPos4Sc;
    public CutPos5 cutPos5Sc;
    public CutPos6 cutPos6Sc;
    public CutPos7 cutPos7Sc;
    public CutPos8 cutPos8Sc;

    // カット後アニメーション
    public Animator animatorCakeUp;
    public Animator animatorCakeUnder;
    // ゲーム成功保存変数
    public bool gameSuccess;
    // 発生させるエフェクト
    public ParticleSystem cutEffect;
    public ParticleSystem clearEffect;
    // リザルトスクリプト変数
    public ResultManager resultManager;
    // ミニゲームスクリプト変数
    public MinigameIn miniGameIn;
    // 発生させる音
    public AudioClip soundTask;
    public AudioClip soundClear;
    // オーディオソース
    AudioSource audioSource;
    void Start()
    {// ゲーム成功保存変数をfalseにする
        gameSuccess = false;
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        bool cut1;
        bool cut2;
        bool cut3;
        bool cut4;
        bool cut5;
        bool cut6;
        bool cut7;
        bool cut8;
        // 全てのポジションのカットされたかを取得
        cut1 = cutPos1Sc.getCutFlag;
        cut2 = cutPos2Sc.getCutFlag;
        cut3 = cutPos3Sc.getCutFlag;
        cut4 = cutPos4Sc.getCutFlag;
        cut5 = cutPos5Sc.getCutFlag;
        cut6 = cutPos6Sc.getCutFlag;
        cut7 = cutPos7Sc.getCutFlag;
        cut8 = cutPos8Sc.getCutFlag;
        // 全てのポジションがカットされていたら
        if (cut1 == true && cut2 == true && cut3 == true         
            && cut4 == true && cut5 == true && cut6 == true 
            && cut7 == true && cut8 == true && gameSuccess == false)
        {
            // カットエフェクトの生成
            ParticleSystem newEffect = Instantiate(cutEffect);
            // カットエフェクトをアクティブ
            newEffect.gameObject.SetActive(true);
            // カットエフェクトのポジションのセット
            newEffect.gameObject.transform.position = cutEffect.transform.position;
            // カットエフェクトの発生
            newEffect.Play();
            // カットエフェクトの削除
            Destroy(newEffect.gameObject, 0.5f);
            // カットアニメーションの発生変数をtrue
            animatorCakeUp.SetBool("separateCakeUp", true);
            animatorCakeUnder.SetBool("separateCakeUnder", true);
            // クリアエフェクトの生成
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // クリアエフェクトをアクティブ
            newClearEffect.gameObject.SetActive(true);
            // クリアエフェクトのポジションのセット
            newClearEffect.gameObject.transform.position = clearEffect.transform.position;
            // クリアエフェクトの発生
            newClearEffect.Play();
            // クリアエフェクトの削除
            Destroy(newClearEffect.gameObject, 0.5f);
            // ゲーム成功変数をtrue
            miniGameIn.SetMinigameResult(true);
            gameSuccess = true;       
            resultManager.cakeCutJudge = true;
            // ゲーム成功効果音を鳴らす
            audioSource.PlayOneShot(soundClear);
        }
    }
}
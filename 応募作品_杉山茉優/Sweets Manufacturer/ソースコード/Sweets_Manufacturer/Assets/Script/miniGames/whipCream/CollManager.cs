using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// ボウルを混ぜるゲームの回転した時とクリアした時の処理
public class CollManager : MonoBehaviour
{
    // 回転数
    static int numberOfRotation;
    // ゲームのクリア処理済みフラグ
    public bool gameSuccess;
    // 1回転の確認のためのオブジェクト
    public RotatePos1 rotatePos1;
    public RotatePos2 rotatePos2;
    public RotatePos3 rotatePos3;
    public RotatePos4 rotatePos4;
    // 1回転のエフェクト
    public ParticleSystem rotateEffect;
    // クリアエフェクト
    public ParticleSystem clearEffect;
    // スクリプト変数
    public ResultManager resultManager;
    public MinigameIn miniGameIn;
    // 効果音
    public AudioClip soundTask;
    public AudioClip soundClear;
    // オーディオソース
    AudioSource audioSource;
    // ボール識別変数
    // 1:cakeCreamBowl 2:chocoBowl 3:chocoCrackerBowl 4:orangeBowl 5:cookieDoughBowl
    public int thisBowlNum;   

    void Start()
    {
        // 初期化
        numberOfRotation = 0;
        gameSuccess = false;
        audioSource = GetComponent<AudioSource>();
    }
   
    void Update()
    {
        // 各1回転確認オブジェクトと泡だて器の当たり判定結果を取得
        bool rotate1;
        bool rotate2;
        bool rotate3;
        bool rotate4;
        rotate1 = rotatePos1.RotateTerritoryFlag;
        rotate2 = rotatePos2.RotateTerritoryFlag;
        rotate3 = rotatePos3.RotateTerritoryFlag;
        rotate4 = rotatePos4.RotateTerritoryFlag;
        // すべての1回転確認オブジェクトと接触しているかどうか
        if (rotate1 == true && rotate2 == true && rotate3 == true && rotate4 == true)
        {
            // 次の回転判定のために泡だて器との当たり判定の結果を戻す
            rotatePos1.RotateTerritoryFlag = false;
            rotatePos2.RotateTerritoryFlag = false;
            rotatePos3.RotateTerritoryFlag = false;
            rotatePos4.RotateTerritoryFlag = false;
            // 回転数を+1する
            numberOfRotation++;
            // 1回転エフェクトの作成
            ParticleSystem newEffect = Instantiate(rotateEffect);
            // 1回転エフェクトをアクティブにする
            newEffect.gameObject.SetActive(true);
            // 1回転エフェクトの位置をセット
            newEffect.gameObject.transform.position = rotateEffect.transform.position;
            // 1回転エフェクトを発生
            newEffect.Play();
            // 1回転エフェクトを削除
            Destroy(newEffect.gameObject, 5.0f);
            // 1回転効果音の再生
            audioSource.PlayOneShot(soundTask);
        } 
        // 10回転以上していて、ゲームのクリア処理をしていなかいかどうか
        if (numberOfRotation >= 10 && gameSuccess == false) {
            // 回転数を+1する
            numberOfRotation++;
            // クリアエフェクトの作成
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // クリアエフェクトをアクティブにする
            newClearEffect.gameObject.SetActive(true);
            // クリアエフェクトの位置をセット
            newClearEffect.gameObject.transform.position = clearEffect.transform.position;
            // クリアエフェクトを発生
            newClearEffect.Play();
            // クリアエフェクトを削除
            Destroy(newClearEffect.gameObject, 5.0f);
            // ミニゲームの終了を保存
            miniGameIn.SetMinigameResult(true);  
            // クリア効果音の再生
            audioSource.PlayOneShot(soundClear);
            // ボウルオブジェクトに合わせてゲームクリアの保存をする
            switch (thisBowlNum)
            {
                case 1:  // [ケーキ]のボウル
                    resultManager.cakeCreamBowlJudge = true;
                    break;
                case 2:  // [チョコクラッカー]のチョコのボウル
                    resultManager.chocoBowlJudge = true;
                    break;
                case 3:  // [チョコクラッカー]の生地のボウル
                    resultManager.chocoCrackerBowlJudge = true;
                    break;
                case 4:  // [ゼリー]のボウル
                    resultManager.orangeBowlJudge = true;
                    break;
                case 5:  // [クッキー]のボウル
                    resultManager.cookieDoughBowlJudge = true;
                    break;
            }
            // 二回目のクリア処理をしないよう、ゲームクリア処理済みにする
            gameSuccess = true;
        }
    }
    // 回転数のゲッター
    // 引  数：なし
    // 戻り値：int numberOfRotation  回転数
    public int GetNumberOfRotation
    {
        get { return numberOfRotation; }
    }
}

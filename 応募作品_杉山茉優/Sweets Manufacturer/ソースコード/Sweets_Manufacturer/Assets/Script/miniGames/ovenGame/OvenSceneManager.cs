using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

// オーブン、冷蔵庫のゲージを止めるゲームの制御スクリプト
public class OvenSceneManager : MonoBehaviour
{
    // ゲーム成功かどうかの変数
    public bool ovenSuccess;
    public bool coolSuccess;
    private DropObj dropObjScript;
    private GameObject moveSceneObj;
    private string nowGameName;
    public ParticleSystem clearEffect;
    private bool doneFinishProcess;
    public bool finishGame;
    public AudioClip soundClear;
    AudioSource audioSource;
    public GameObject ovenText;
    public GameObject coolText;

    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        doneFinishProcess = false;
        finishGame = false;
        // M.S ゲームの実行コルーチンを呼ぶ
        if (this.gameObject.name == "Ovengame")
        {
            ovenSuccess = false;
            StartCoroutine("OvenGame");
        }
        else if(this.gameObject.name == "CoolGame")
        {
            coolSuccess = false;
            StartCoroutine("CoolGame");
        }
        nowGameName = this.gameObject.name;
    }
    // ゲームシーンのオブジェクトのアクティブ制御のコルーチン
    public IEnumerator OvenGame()
    {
        Debug.Log("oven");
       //mainsceneのmoveSceneObjを呼ぶ
       moveSceneObj = GameObject.Find("moveSceneObj");
      var mainSceneObj = moveSceneObj.GetComponent<DropObj>();
        // mainSceneのオブジェクトをfalseにする。
       mainSceneObj.sceneTogether.SetActive(false);
       moveSceneObj.SetActive(true);
        // M.S テキストの表示
        ovenText.SetActive(true);
        yield return new WaitForSecondsRealtime(2.0f);
        ovenText.SetActive(false);
        // ミニゲームの時間
        yield return new WaitForSecondsRealtime(4.0f);
        if (ovenSuccess == true)
        {
            // M.Sクリアエフェクトの作成
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // M.Sクリアエフェクトの位置のセット
            newClearEffect.transform.position = new Vector3(0.0f, 4.19f, -0.53f);
            // M.Sクリアエフェクトをアクティブにする
            newClearEffect.gameObject.SetActive(true);
            // M.Sクリアエフェクトの発生
            newClearEffect.Play();
            // M.Sクリアエフェクトの削除
            Destroy(newClearEffect.gameObject, 5.0f);
            // M.Sクリア効果音
            audioSource.PlayOneShot(soundClear);
        }
        yield return new WaitForSecondsRealtime(1.0f);
        // ゲーム終了後、mainSceneのオブジェクトをtrueにする
        mainSceneObj.sceneTogether.SetActive(true);
        // mainSceneのミニゲームをfalseさせる判定をtrue
        DropObj.moveScene = true;
        mainSceneObj.returnGamejudge = ovenSuccess;
        // M.S OvenSceneのアンロード
        SceneManager.UnloadSceneAsync("OvenScene");
         yield break;
    }

    public IEnumerator CoolGame()
    {
        Debug.Log("cool");
        //mainsceneのmoveSceneObjを呼ぶ
        moveSceneObj = GameObject.Find("moveSceneObj");
     var mainSceneObj = moveSceneObj.GetComponent<DropObj>();
        // mainSceneのオブジェクトをfalseにする。
      mainSceneObj.sceneTogether.SetActive(false);
     moveSceneObj.SetActive(true);
        // M.S テキストの表示
        coolText.SetActive(true);
        yield return new WaitForSecondsRealtime(2.0f);
        coolText.SetActive(false);
        // ミニゲームの時間
        yield return new WaitForSecondsRealtime(4.0f);
        if (coolSuccess == true)
        {
            // M.Sクリアエフェクトの作成
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // M.Sクリアエフェクトの位置のセット
            newClearEffect.transform.position = new Vector3(0.0f, 2.51f, -0.533f);
            // M.Sクリアエフェクトをアクティブにする
            newClearEffect.gameObject.SetActive(true);
            // M.Sクリアエフェクトの発生
            newClearEffect.Play();
            // M.Sクリアエフェクトの削除
            Destroy(newClearEffect.gameObject, 5.0f);
            // M.Sクリア効果音
            audioSource.PlayOneShot(soundClear);
        }
        yield return new WaitForSecondsRealtime(1.0f);
        // ゲーム終了後、mainSceneのオブジェクトをtrueにする
       mainSceneObj.sceneTogether.SetActive(true);
        // mainSceneのミニゲームをfalseさせる判定をtrue
        DropObj.moveScene = true;
       mainSceneObj.returnGamejudge = coolSuccess;
        // M.S CoolSceneのアンロード
        SceneManager.UnloadSceneAsync("CoolScene");
        yield break;
    }

    // オーブンゲームの成功、不成功を入れる変数
    // 引  数：bool judge   true 成功  false 不成功
    // 戻り値：なし
    public void setOvenGameSuccess(bool judge){
        ovenSuccess = judge;
    }
    // クールゲームの成功、不成功を入れる変数
    // 引  数：bool judge  true 成功  false 不成功
    // 戻り値：なし
    public void setCoolGameSuccess(bool judge)
    {
        coolSuccess = judge;
    }
    // M.S 現在プレイ中のゲーム(シーン)名の取得
    // 引  数：なし
    // 戻り値：なし
    public string GetNowGameName()
    {
        return nowGameName;
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// イチゴを飾るゲームのイチゴをクリックした時の処理プログラム
[RequireComponent(typeof(Rigidbody))]
public class Clicktarget : MonoBehaviour
{
    Rigidbody rigidBody;
    public ParticleSystem putBerryEffect;
    public GameObject strawpoint;
    public GameObject strawafter;
    public AudioClip soundTask;
    public AudioSource audioSource;
    void Start()
    {
        rigidBody = gameObject.GetComponent<Rigidbody>();
    }
    public void OnUserAction()
    {
        GameObject Berry;
        BerryCrear Berrycrear;
        Berry = GameObject.Find("Clear");
        Berrycrear = Berry.GetComponent<BerryCrear>();
        Berrycrear.Berrycount++;
        audioSource.PlayOneShot(soundTask);                // M.S クリック前のイチゴ表示を消す前に音を鳴らす
        strawafter.SetActive(true);
        strawpoint.SetActive(false);
        ParticleSystem newEffect = Instantiate(putBerryEffect);  // M.S エフェクトの作成
        newEffect.gameObject.SetActive(true);                    // M.S エフェクトをアクティブにする
        // M.S イチゴの位置にエフェクトをセット(Y軸以外)
        newEffect.transform.position = new Vector3(this.transform.position.x, putBerryEffect.transform.position.y, this.transform.position.z);
        newEffect.Play(); // M.S エフェクトの発生
        Destroy(newEffect.gameObject, 5.0f);    // M.S エフェクトの削除
        Debug.Log("イチゴに触った");
    }
}

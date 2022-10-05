using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
// オーブン、クールゲームのボタンを止めるスクリプト
public class StopRedButton : MonoBehaviour
{
    public MoveRedPoint moveRedPoint;
    public ParticleSystem hitEffect;
    public OvenSceneManager ovenSceneManager;
    public AudioClip soundTask;
    AudioSource audioSource;
    public GameObject gauge;

    void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (ovenSceneManager.GetNowGameName() == "Ovengame" && moveRedPoint.stopButton == false)
            {
                // M.S ゲージを操作できるようにする
                gauge.GetComponent<Slider>().interactable = true;
                moveRedPoint.stopButton = true;
                // M.S ボタンを押したエフェクトの作成
                ParticleSystem newEffect = Instantiate(hitEffect);
                // M.S ボタンを押したエフェクトをアクティブにする
                newEffect.gameObject.SetActive(true);
                // M.S ボタンを押したエフェクトの位置をセット
                newEffect.gameObject.transform.position = new Vector3(0.3f, 3.94f, -0.5f);
                // M.S ボタンを押したエフェクトの発生
                newEffect.Play();
                // M.S ボタンを押したエフェクトの削除
                Destroy(newEffect.gameObject, 5.0f);
                // M.S ボタンを押した効果音
                audioSource.PlayOneShot(soundTask);

            }
            else if (ovenSceneManager.GetNowGameName() == "CoolGame" && moveRedPoint.stopButton == false)
            {
                // M.S ゲージを操作できるようにする
                gauge.GetComponent<Slider>().interactable = true;
                moveRedPoint.stopButton = true;
                // M.S ボタンを押したエフェクトの作成
                ParticleSystem newEffect = Instantiate(hitEffect);
                // M.S ボタンを押したエフェクトをアクティブにする
                newEffect.gameObject.SetActive(true);
                // M.S ボタンを押したエフェクトの位置をセット
                newEffect.gameObject.transform.position = new Vector3(0.3f, 2.41f, -0.5f);
                // M.S ボタンを押したエフェクトの発生
                newEffect.Play();
                // M.S ボタンを押したエフェクトの削除
                Destroy(newEffect.gameObject, 5.0f);
                // M.S ボタンを押した効果音
                audioSource.PlayOneShot(soundTask);

            }
            // M.S ゲージを操作できないようにする
            gauge.GetComponent<Slider>().interactable = false;
            // M.S ゲ―ム終了フラグをtrue
            ovenSceneManager.finishGame = true;
        }
    }

    public bool GetStopButton()
    {
        return moveRedPoint.stopButton;
    }
}

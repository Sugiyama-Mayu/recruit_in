using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
// オーブン、冷蔵庫のゲージを止めるゲームの
// 動くゲージの挙動制御スクリプト
public class GaugeMove : MonoBehaviour
{
    public Slider gauge;
    private bool maxValue;
    public StopRedButton stopRedButton;
    void Start()
    {
        gauge.value = 0;
        maxValue = false;
    }
    void Update()
    {   
        if (stopRedButton.GetStopButton() == false)
        {
            //5に達した場合と、0に戻った場合のフラグ切替え
            if (gauge.value == 5)
            {
                maxValue = true;
            }

            if (gauge.value == 0)
            {
                maxValue = false;
            }

            //フラグによるスライダー値の増減
            if (maxValue)
            {
                gauge.value -=4.0f * Time.deltaTime;
            }
            else
            {
                gauge.value += 4.0f * Time.deltaTime;
            }
        }
    }
}


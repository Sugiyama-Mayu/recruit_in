using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// クッキーの型抜き処理や抜き型の動きプログラム
public class MoveCutOut : MonoBehaviour
{
    // 抜き型オブジェクト
    public GameObject CutOut;
    // 型を抜いた数のカウント変数
    private int cookieCount;
    // 型抜きの穴オブジェクト
    public GameObject cutOfOut1;
    public GameObject cutOfOut2;
    public GameObject cutOfOut3;
    public GameObject cutOfOut4;
    // 型抜きしたクッキーのオブジェクト
    public GameObject cutOutDough1;
    public GameObject cutOutDough2;
    public GameObject cutOutDough3;
    public GameObject cutOutDough4;
    // クリック(型抜き)をしたかどうかフラグ
    public bool clickStamp;
    // マウスの位置
    private Vector3 mouseWorldPos;
    private float adjustmentX; // 移動位置の調整X座標
    // ゲームが発生したかどうかフラグ
    private bool doneProcess;
    // 型抜きの穴のプログラムを通ったか確認変数
    public int cookieStampNum;
    // 生地のプログラムを通ったか確認変数
    public int cookieDoughNum;
    // 範囲外領域のプログラムを通ったか確認変数
    public int cookieRange;
    // 型抜きをした時のエフェクト
    public ParticleSystem cutOutEffect;
    // 型抜き成功時の効果音
    public AudioClip soundTask;
    AudioSource audioSource;
    // 初期化フラグ
    public bool startFlag;
    // 抜き型と接触したオブジェクトを追加するリスト
    List<GameObject> colList = new List<GameObject>();
    // この位置を超えたらクッキーを削除する位置変数
    private float cookieDestroyPos;
    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        // 初期化処理
        InitializationProcess();
        // 型抜きの穴を非アクティブにする
        cutOfOut1.SetActive(false);
        cutOfOut2.SetActive(false);
        cutOfOut3.SetActive(false);
        cutOfOut4.SetActive(false);
        // 削除する位置の設定;
        cookieDestroyPos = -15.0f;
        adjustmentX = 2.2f; // 移動位置の調整X座標
    }
    void Update()
    {
        // 初期化フラグがtrueかどうか
        if (startFlag == true)
        {
            // 初期化処理
            InitializationProcess();
            // colListの要素削除
            colList.Clear();
        }
        // 全ての方を抜いていたら+1
        if (cookieCount == 4)
        {
            cookieCount++;
        }
        FollowMousePos(); // マウスに合わせて抜き型を動かす
        // 範囲外領域、型抜きの穴、生地のプログラムを通っているかどうか
        // &クリックしたかどうか
        if (cookieRange >= 4 && cookieStampNum >= cookieCount
            && cookieDoughNum >= 1 && clickStamp == true)
        {
            int colNum = 0;  // 型抜きができないオブジェクトがあると+1する
            bool doughColl = false;  // 生地があるとtrue
            // colListの要素を見る
            foreach (GameObject checkObj in colList)
            {
                if (checkObj.layer == 12) // layerがOutOfRangeかどうか
                {
                    // 型抜きができないのでcolNumに+1
                    colNum++;
                }
                if (checkObj.layer == 13) // layerがWithinDoughかどうか
                {
                    doughColl = true; // 生地なのでdoughCollをtrue
                }
            }
            // colListに要素が無ければ(何も当たっていない)colNumに+1
            if (colList.Count <= 0)
            {
                colNum++;
            }
            // colNumが0以下でdoughCollがtrueかどうか
            if (colNum <= 0 && doughColl == true)
            {
                switch (cookieCount)
                {
                    // 一回目の型抜き
                    case 0:
                        DoFirstCutOutProcess();
                        break;
                    // 二回目の型抜き
                    case 1:
                        DoSecondCutOutProcess();
                        break;
                    // 三回目の型抜き
                    case 2:
                        DoThirdCutOutProcess();
                        break;
                    // 四回目の型抜き
                    case 3:
                        DoFourthCutOutProcess();
                        break;
                }
            }
        }
        // 通ったか確認変数、クリックフラグを初期化
        cookieRange = 0;
        cookieStampNum = 0;
        cookieDoughNum = 0;
        clickStamp = false;
        // colListの全ての要素を削除
        colList.Clear();
        // 型抜きしたクッキーオブジェクト1がアクティブかどうか
        if (cutOutDough1.activeSelf == true)
        {
            // 型抜きしたクッキーオブジェクト1の型抜き後の処理
            DoAfterFirstCutOutProcess();        
        }
        // 型抜きしたクッキーオブジェクト2がアクティブかどうか
        if (cutOutDough2.activeSelf == true)
        {
            // 型抜きしたクッキーオブジェクト2の型抜き後の処理
            DoAfterSecondCutOutProcess();
        }
        // 型抜きしたクッキーオブジェクト3がアクティブかどうか
        if (cutOutDough3.activeSelf == true)
        {
            // 型抜きしたクッキーオブジェクト3の型抜き後の処理
            DoAfterThirdCutOutProcess();
        }
        // 型抜きしたクッキーオブジェクト4がアクティブかどうか
        if (cutOutDough4.activeSelf == true)
        {
            // 型抜きしたクッキーオブジェクト4の型抜き後の処理
            DoAfterFourthCutOutProcess();
        }
    }
    // 接触しているかどうか
    private void OnTriggerStay(Collider other)
    {
        // 左クリックをしたら
        if (Input.GetMouseButtonDown(0))
        {
            colList.Add(other.gameObject);
            // クリックフラグをtrue
            clickStamp = true;
        }
    }
    // 一回目の型抜きをした時の処理
    // 引  数:なし
    // 戻り値:なし
    public void DoFirstCutOutProcess()
    {
        // 型抜きの穴のオブジェクトを抜き型の位置にセット(Y座標以外)
        cutOfOut1.transform.position = new Vector3(CutOut.transform.position.x, cutOfOut1.transform.position.y, CutOut.transform.position.z);
        // 型抜きの穴のオブジェクトをアクティブにする
        cutOfOut1.SetActive(true);
        // 型抜きエフェクトの作成
        ParticleSystem newEffect = Instantiate(cutOutEffect);
        // 型抜きエフェクトをアクティブにする
        newEffect.gameObject.SetActive(true);
        // エフェクトを型抜きの穴の位置にセット
        newEffect.gameObject.transform.position = cutOfOut1.transform.position;
        // エフェクトの発生
        newEffect.Play();
        // エフェクトの削除
        Destroy(newEffect.gameObject, 5.0f);
        // 型抜きの回数を+1
        cookieCount++;
        // 型抜き(タスク)の成功の効果音
        audioSource.PlayOneShot(soundTask);
        // 型抜きしたクッキーのオブジェクトをアクティブにする
        cutOutDough1.SetActive(true);
        // 型抜きしたクッキーのオブジェクトを型抜きの穴オブジェクトの位置にセット(Y座標は以外)
        cutOutDough1.transform.position = new Vector3(cutOfOut1.transform.position.x, cutOutDough1.transform.position.y, cutOfOut1.transform.position.z);
    }
    // 二回目の型抜きをした時の処理
    // 引  数:なし
    // 戻り値:なし
    public void DoSecondCutOutProcess()
    {
        // 型抜きの穴のオブジェクトを抜き型の位置にセット(Y座標以外)
        cutOfOut2.transform.position = new Vector3(CutOut.transform.position.x, cutOfOut2.transform.position.y, CutOut.transform.position.z);
        // 型抜きの穴をアクティブにする
        cutOfOut2.SetActive(true);
        // 型抜きエフェクトの作成
        ParticleSystem newEffect2 = Instantiate(cutOutEffect);
        // 型抜きエフェクトをアクティブにする
        newEffect2.gameObject.SetActive(true);
        // エフェクトを型抜きの穴の位置にセット
        newEffect2.gameObject.transform.position = cutOfOut2.transform.position;
        // エフェクトの発生
        newEffect2.Play();
        // エフェクトの削除
        Destroy(newEffect2.gameObject, 5.0f);
        // 型抜きの回数を+1
        cookieCount++;
        // 型抜き(タスク)の成功の効果音
        audioSource.PlayOneShot(soundTask);
        // 型抜きしたクッキーのオブジェクトをアクティブにする
        cutOutDough2.SetActive(true);
        // 型抜きしたクッキーのオブジェクトを型抜きの穴オブジェクトの位置にセット(Y座標は以外)
        cutOutDough2.transform.position = new Vector3(cutOfOut2.transform.position.x, cutOutDough2.transform.position.y, cutOfOut2.transform.position.z);
    }
    // 三回目の型抜きをした時の処理
    // 引  数:なし
    // 戻り値:なし
    public void DoThirdCutOutProcess()
    {
        // 型抜きの穴のオブジェクトを抜き型の位置にセット(Y座標以外)
        cutOfOut3.transform.position = new Vector3(CutOut.transform.position.x, cutOfOut3.transform.position.y, CutOut.transform.position.z);
        // 型抜きの穴をアクティブにする
        cutOfOut3.SetActive(true);
        // 型抜きエフェクトの作成
        ParticleSystem newEffect3 = Instantiate(cutOutEffect);
        // 型抜きエフェクトをアクティブにする
        newEffect3.gameObject.SetActive(true);
        // エフェクトを型抜きの穴の位置にセット
        newEffect3.gameObject.transform.position = cutOfOut3.transform.position;
        // エフェクトの発生
        newEffect3.Play();
        // エフェクトの削除
        Destroy(newEffect3.gameObject, 5.0f);
        // 型抜きの回数を+
        cookieCount++;
        // 型抜き(タスク)の成功の効果音
        audioSource.PlayOneShot(soundTask);
        // 型抜きしたクッキーのオブジェクトをアクティブにする
        cutOutDough3.SetActive(true);
        // 型抜きしたクッキーのオブジェクトを型抜きの穴オブジェクトの位置にセット(Y座標は以外)
        cutOutDough3.transform.position = new Vector3(cutOfOut3.transform.position.x, cutOutDough3.transform.position.y, cutOfOut3.transform.position.z);
    }
    // 四回目の型抜きをした時の処理
    // 引  数:なし
    // 戻り値:なし
    public void DoFourthCutOutProcess()
    {
        // 型抜きの穴のオブジェクトを抜き型の位置にセット(Y座標以外)
        cutOfOut4.transform.position = new Vector3(CutOut.transform.position.x, cutOfOut1.transform.position.y, CutOut.transform.position.z);
        // 型抜きの穴をアクティブにする
        cutOfOut4.SetActive(true);
        // 型抜きエフェクトの作成
        ParticleSystem newEffect4 = Instantiate(cutOutEffect);
        // 型抜きエフェクトをアクティブにする
        newEffect4.gameObject.SetActive(true);
        // エフェクトを型抜きの穴の位置にセット
        newEffect4.gameObject.transform.position = cutOfOut4.transform.position;
        // エフェクトの発生
        newEffect4.Play();
        // エフェクトの削除
        Destroy(newEffect4.gameObject, 5.0f);
        // 型抜きの回数を+1
        cookieCount++;
        // 型抜き(タスク)の成功の効果音
        audioSource.PlayOneShot(soundTask);
        // 型抜きしたクッキーのオブジェクトをアクティブにする
        cutOutDough4.SetActive(true);
        // 型抜きしたクッキーのオブジェクトを型抜きの穴オブジェクトの位置にセット(Y座標は以外
        cutOutDough4.transform.position = new Vector3(cutOfOut4.transform.position.x, cutOutDough4.transform.position.y, cutOfOut4.transform.position.z);
    }
    // 型抜きしたクッキーオブジェクト1の型抜き後の処理
    // 引  数:なし
    // 戻り値:なし
    public void DoAfterFirstCutOutProcess()
    {
        // 型抜きしたクッキーオブジェクト1のZ座標がcookieDestroyPosより小さいかどうか
        if (cutOutDough1.transform.position.z <= cookieDestroyPos)
        {
            // 型抜きしたクッキーオブジェクト1のZ座標をcookieDestroyPosにする
            cutOutDough1.transform.position = new Vector3(cutOfOut1.transform.position.x, cutOutDough1.transform.position.y, cookieDestroyPos);
            // 型抜きしたクッキーオブジェクト1を非アクティブにする
            cutOutDough1.SetActive(false);
        }
        else
        {
            // 型抜きしたクッキーオブジェクト1のZ座標がcookieDestroyPosになるまで移動させる
            cutOutDough1.transform.position -= new Vector3(0.0f, 0.0f, 10.0f) * Time.deltaTime;
        }
    }
    // 型抜きしたクッキーオブジェクト1の型抜き後の処理
    // 引  数:なし
    // 戻り値:なし
    public void DoAfterSecondCutOutProcess()
    {
        // 型抜きしたクッキーオブジェクト2のZ座標がcookieDestroyPosより小さいかどうか
        if (cutOutDough2.transform.position.z <= cookieDestroyPos)
        {
            // 型抜きしたクッキーオブジェクト2のZ座標をcookieDestroyPosにする
            cutOutDough2.transform.position = new Vector3(cutOfOut2.transform.position.x, cutOutDough2.transform.position.y, cookieDestroyPos);
            // 型抜きしたクッキーオブジェクト2を非アクティブにする
            cutOutDough2.SetActive(false);
        }
        else
        {
            // 型抜きしたクッキーオブジェクト2のZ座標がcookieDestroyPosになるまで移動させる
            cutOutDough2.transform.position -= new Vector3(0.0f, 0.0f, 10.0f) * Time.deltaTime;
        }
    }
    // 型抜きしたクッキーオブジェクト1の型抜き後の処理
    // 引  数:なし
    // 戻り値:なし
    public void DoAfterThirdCutOutProcess()
    {
        // 型抜きしたクッキーオブジェクト3のZ座標がcookieDestroyPosより小さいかどうか
        if (cutOutDough3.transform.position.z <= cookieDestroyPos)
        {
            // 型抜きしたクッキーオブジェクト3のZ座標をcookieDestroyPosにする
            cutOutDough3.transform.position = new Vector3(cutOfOut3.transform.position.x, cutOutDough3.transform.position.y, cookieDestroyPos);
            // 型抜きしたクッキーオブジェクト3を非アクティブにする
            cutOutDough3.SetActive(false);
        }
        else
        {
            // 型抜きしたクッキーオブジェクト3のZ座標がcookieDestroyPosになるまで移動させる
            cutOutDough3.transform.position -= new Vector3(0.0f, 0.0f, 10.0f) * Time.deltaTime;
        }
    }
    // 型抜きしたクッキーオブジェクト1の型抜き後の処理
    // 引  数:なし
    // 戻り値:なし
    public void DoAfterFourthCutOutProcess()
    {
        // 型抜きしたクッキーオブジェクト4のZ座標がcookieDestroyPosより小さいかどうか
        if (cutOutDough4.transform.position.z <= cookieDestroyPos)
        {
            // 型抜きしたクッキーオブジェクト4のZ座標をcookieDestroyPosにする
            cutOutDough4.transform.position = new Vector3(cutOfOut4.transform.position.x, cutOutDough4.transform.position.y, cookieDestroyPos);
            // 型抜きしたクッキーオブジェクト4を非アクティブにする
            cutOutDough4.SetActive(false);

        }
        else
        {
            // 型抜きしたクッキーオブジェクト4のZ座標がcookieDestroyPosになるまで移動させる
            cutOutDough4.transform.position -= new Vector3(0.0f, 0.0f, 10.0f) * Time.deltaTime;
        }
    }
    // colListに要素を追加する関数
    // 引  数:追加したいGameObject
    // 戻り値:なし
    public void SetCutOutCol(GameObject setObj)
    {
        colList.Add(setObj.gameObject);

    }
    // doneProcessをセットする関数
    // 引  数:trueかfalse
    // 戻り値:なし
    public void SetDoneProcess(bool set)
    {
        doneProcess = set;
    }
    // cookieCount(型抜きをした回数)の取得関数
    // 引  数:なし
    // 戻り値:int 型抜きをした回数
    public int GetCookieCount()
    {
        return cookieCount;
    }
    // 初期化用関数
    // 引  数:なし
    // 戻り値:なし
    private void InitializationProcess()
    {
        // 変数を初期化
        cookieCount = 0;
        cookieStampNum = 0;
        cookieDoughNum = 0;
        cookieRange = 0;
        clickStamp = false;
        startFlag = false;
    }
    // マウスに追従させる関数
    // 引  数:なし
    // 戻り値:なし
    private void FollowMousePos()
    {
        // マウスの位置の取得
        Vector3 mousPos = Input.mousePosition;
        // 3D座標にしたいのでZ軸を当てはめる
        mousPos.z = 13.0f;
        // マウスの位置を3Dの座標に変更、mouseWorldPosに入れる
        Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
        // mouseWorldPosのY座標を抜き型オブジェクトのY座標にセット
        mouseWorldPos.y = this.gameObject.transform.position.y;
        // mouseWorldPosのZ座標の設定
        mouseWorldPos.z = mouseWorldPos.z - adjustmentX;
        // 抜き型オブジェクトの位置をセット
        CutOut.transform.position = mouseWorldPos;
    }
}

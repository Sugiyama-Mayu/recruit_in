using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
// M.S
// コレクションシーンの処理
public class Collect : MonoBehaviour
{
    // コレクション記録ファイルのパス
    string filePath;
    // コレクション記録ファイル
    public string[] collectNum;
    int[] collectNumText = new int[17];
    // 選択しているオブジェ数字
    public int collectSelectNum;
    int newSlectNum;
    // 選択していたオブジェ数字
    int oldSelectNum;
    // 右の選択するオブジェクト
    public GameObject cake;
    public GameObject goldCake;
    public GameObject choco;
    public GameObject goldChoco;
    public GameObject jelly;
    public GameObject goldJelly;
    public GameObject cookie;
    public GameObject goldCookie;
    public GameObject redTrophy;
    public GameObject greenTrophy;
    public GameObject yellowTrophy;
    public GameObject blueTrophy;
    public GameObject crystalTrophy;
    // 左の大きく表示されるオブジェクト
    public GameObject cakeBig;
    public GameObject goldCakeBig;
    public GameObject chocoBig;
    public GameObject goldChocoBig;
    public GameObject jellyBig;
    public GameObject goldJellyBig;
    public GameObject cookieBig;
    public GameObject goldCookieBig;
    public GameObject redTrophyBig;
    public GameObject greenTrophyBig;
    public GameObject yellowTrophyBig;
    public GameObject blueTrophyBig;
    public GameObject crystalTrophyBig;
    // オブジェクトの説明オブジェ
    public GameObject cakeText;
    public GameObject goldCakeText;
    public GameObject chocoText;
    public GameObject goldChocoText;
    public GameObject jellyText;
    public GameObject goldJellyText;
    public GameObject cookieText;
    public GameObject goldCookieText;
    public GameObject redTrophyText;
    public GameObject greenTrophyText;
    public GameObject yellowTrophyText;
    public GameObject blueTrophyText;
    public GameObject crystalTrophyText;
    // まだ取得していない表示用
    public GameObject question;
    // 前の選択オブジェ
    public GameObject oldSelectObj;
    public GameObject oldSelectObjText;
    // すべてのアイテムが未取得フラグ
    bool noOldSelectObjFlag;
    void Start()
    {
        oldSelectObj = cakeBig;
        newSlectNum = 0;
        oldSelectNum = 0;
        collectSelectNum = 0;
        noOldSelectObjFlag = true;
        // 保存ファイルのパス
        filePath = Application.dataPath + "/StreamingAssets/collectFile.txt";
        // ファイルの読み込み
        collectNum = File.ReadAllLines(filePath);
        // 選択に合わせてオブジェクトを表示させる
        // 初期の選択値の設定
        DisPlaySmallCollectItem();
        DisPlayBigCollectItem();
    }
    void Update()
    {
        newSlectNum = collectSelectNum;
        // 選択オブジェを回転させる
        oldSelectObj.transform.Rotate(0.0f, 0.25f, 0.0f, Space.World);
        // 別のオブジェクトを選択したら
        if (newSlectNum != oldSelectNum)
        {
            // 取得アイテムがあるかどうか
            if (noOldSelectObjFlag == false)
            {
                // 前の選択オブジェクトを非表示
                oldSelectObj.SetActive(false);
                oldSelectObjText.SetActive(false);
            }
            question.SetActive(false);

            oldSelectNum = newSlectNum;
            // 選択に合わせてオブジェクトを表示させる
            // 選択中オブジェクトの更新
            DisPlayBigCollectItem();
        }
    }
    // ケーキが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigCake()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[0] == "1")
        {
            cakeBig.SetActive(true);  // オブジェクトの表示
            cakeText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = cakeBig;     
            oldSelectObjText = cakeText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false; 
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // 金のケーキが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigGoldCake()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[1] == "1")
        {
            goldCakeBig.SetActive(true);  // オブジェクトの表示
            goldCakeText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = goldCakeBig;
            oldSelectObjText = goldCakeText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // チョコクラッカーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigChocoCracker()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[2] == "1")
        {
            chocoBig.SetActive(true);  // オブジェクトの表示
            chocoText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = chocoBig;
            oldSelectObjText = chocoText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // 金のチョコクラッカーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigGoldChocoCracker()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[3] == "1")
        {
            goldChocoBig.SetActive(true);  // オブジェクトの表示
            goldChocoText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = goldChocoBig;
            oldSelectObjText = goldChocoText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // ゼリーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigJelly()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[4] == "1")
        {
            jellyBig.SetActive(true);  // オブジェクトの表示
            jellyText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = jellyBig;
            oldSelectObjText = jellyText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // 金のゼリーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigGoldJelly()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[5] == "1")
        {
            goldJellyBig.SetActive(true);  // オブジェクトの表示
            goldJellyText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = goldJellyBig;
            oldSelectObjText = goldJellyText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // クッキーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigCookie()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[6] == "1")
        {
            cookieBig.SetActive(true);  // オブジェクトの表示
            cookieText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = cookieBig;
            oldSelectObjText = cookieText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // 金のクッキーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigGoldCookie()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[7] == "1")
        {
            goldCookieBig.SetActive(true);  // オブジェクトの表示
            goldCookieText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = goldCookieBig;
            oldSelectObjText = goldCookieText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // ステージ1のトロフィーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigRedTrophy()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[8] == "1")
        {
            redTrophyBig.SetActive(true);  // オブジェクトの表示
            redTrophyText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = redTrophyBig;
            oldSelectObjText = redTrophyText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // ステージ2のトロフィーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigGreenTrophy()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[9] == "1")
        {
            greenTrophyBig.SetActive(true);  // オブジェクトの表示
            greenTrophyText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = greenTrophyBig;
            oldSelectObjText = greenTrophyText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // ステージ3のトロフィーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigYellowTrophy()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[10] == "1")
        {
            yellowTrophyBig.SetActive(true);  // オブジェクトの表示
            yellowTrophyText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = yellowTrophyBig;
            oldSelectObjText = yellowTrophyText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // ステージ4のトロフィーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigBlueTrophy()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[11] == "1")
        {
            blueTrophyBig.SetActive(true);  // オブジェクトの表示
            blueTrophyText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = blueTrophyBig;
            oldSelectObjText = blueTrophyText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // オールコンプリートのトロフィーが選択中の時に表示する処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigCrystalTrophy()
    {
        // コレクトファイルに登録されているかどうか
        if (collectNum[16] == "1")
        {
            crystalTrophyBig.SetActive(true);     // オブジェクトの表示
            crystalTrophyText.SetActive(true); // 説明テキストの表示
            // 選択中オブジェクトの保存
            oldSelectObj = crystalTrophyBig;
            oldSelectObjText = crystalTrophyText;
            // アイテムを取得しているのでアイテム未取得フラグをfalse
            noOldSelectObjFlag = false;
        }
        else
        {
            // 未取得なので？を表示
            question.SetActive(true);
        }
    }
    // 選択アイテムの表示処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlayBigCollectItem()
    {
        // 選択アイテムを大きく表示させ、説明も表示
        switch (collectSelectNum)
        {
            case 0:
                // ケーキの表示
                DisPlayBigCake();
                break;
            case 1:
                // 金のケーキの表示
                DisPlayBigGoldCake();
                break;
            case 2:
                // チョコクラッカーの表示
                DisPlayBigChocoCracker();
                break;
            case 3:
                // 金のチョコクラッカーの表示
                DisPlayBigGoldChocoCracker();
                break;
            case 4:
                // ゼリーの表示
                DisPlayBigJelly();
                break;
            case 5:
                // 金のゼリーの表示
                DisPlayBigGoldJelly();
                break;
            case 6:
                // クッキーの表示
                DisPlayBigCookie();
                break;
            case 7:
                // 金のクッキーの表示
                DisPlayBigGoldCookie();
                break;
            case 8:
                // ステージ1トロフィーの表示
                DisPlayBigRedTrophy();
                break;
            case 9:
                // ステージ2トロフィーの表示
                DisPlayBigGreenTrophy();
                break;
            case 10:
                // ステージ3トロフィーの表示
                DisPlayBigYellowTrophy();
                break;
            case 11:
                // ステージ4トロフィーの表示
                DisPlayBigBlueTrophy();
                break;
            case 12:
                // オールコンプリートトロフィーの表示
                DisPlayBigCrystalTrophy();
                break;
        }
    }
    // 取得済みアイテムの表示処理
    // 引  数：なし
    // 戻り値：なし
    void DisPlaySmallCollectItem()
    {
        // 後ろから取得アイテムを表示させていき
        // 一番コレクション画面で手前のオブジェクトを選択中にする
        if (collectNum[16] == "1")
        {
            // オールコンプリートトロフィーの表示
            crystalTrophy.SetActive(true);
            collectSelectNum = 12; // 初期選択値の設定
        }
        if (collectNum[11] == "1")
        {
            // ステージ4トロフィーの表示
            blueTrophy.SetActive(true);
            collectSelectNum = 11; // 初期選択値の設定
        }
        if (collectNum[10] == "1")
        {
            // ステージ3トロフィーの表示
            yellowTrophy.SetActive(true);
            collectSelectNum = 10; // 初期選択値の設定
        }
        if (collectNum[9] == "1")
        {
            // ステージ2トロフィーの表示
            greenTrophy.SetActive(true);
            collectSelectNum = 9; // 初期選択値の設定
        }
        if (collectNum[8] == "1")
        {
            // ステージ1トロフィーの表示
            redTrophy.SetActive(true);
            collectSelectNum = 8; // 初期選択値の設定
        }
        if (collectNum[7] == "1")
        {
            // 金のクッキーの表示
            goldCookie.SetActive(true);
            collectSelectNum = 7; // 初期選択値の設定
        }
        if (collectNum[6] == "1")
        {
            // クッキーの表示
            cookie.SetActive(true);
            collectSelectNum = 6; // 初期選択値の設定
        }
        if (collectNum[5] == "1")
        {
            // 金のゼリーの表示
            goldJelly.SetActive(true);
            collectSelectNum = 5; // 初期選択値の設定
        }
        if (collectNum[4] == "1")
        {
            // ゼリーの表示
            jelly.SetActive(true);
            collectSelectNum = 4; // 初期選択値の設定
        }
        if (collectNum[3] == "1")
        {
            // 金のチョコクラッカーの表示
            goldChoco.SetActive(true);
            collectSelectNum = 3; // 初期選択値の設定
        }
        if (collectNum[2] == "1")
        {
            // チョコクラッカーの表示
            choco.SetActive(true);
            collectSelectNum = 2; // 初期選択値の設定
        }
        if (collectNum[1] == "1")
        {
            // 金のケーキの表示
            goldCake.SetActive(true);
            collectSelectNum = 1; // 初期選択値の設定
        }
        if (collectNum[0] == "1")
        {
            // ケーキの表示
            cake.SetActive(true);
            collectSelectNum = 0; // 初期選択値の設定
        }
    }
}
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// ベルトコンベアの動きの処理
public class belt : MonoBehaviour
{
    // ベルトコンベアの動きを制御する変数
    public bool stopBeltMove;
    public float TargetDriveSpeed = 0.0f;
    public float CurrentSpeed { get { return _currentSpeed; } }
    [SerializeField] private float _forcePower = 50f;
    public Vector3 DriveDirection = Vector3.forward;
    private float _currentSpeed = 0;
    private List<Rigidbody> _rigidbodies = new List<Rigidbody>();
    private float scroll;
    private GameObject hitObj;
    public bool hitFlag;
    public DropObj dropObj;
    public int stageNum;
    void Start()
    {
        hitFlag = false;
        stopBeltMove = false;
        DriveDirection = DriveDirection.normalized;
    }

    void FixedUpdate()
    {
        if (stopBeltMove == false)
        {
            switch (stageNum)
            {
                case 1:
                    scroll = Mathf.Repeat(Time.time * 0.065f, 1);
                    break;
                case 2:
                    scroll = Mathf.Repeat(Time.time * 0.1f, 1);
                    break;
                case 3:
                    scroll = Mathf.Repeat(Time.time * 0.2f, 1);
                    break;
                case 4:
                    scroll = Mathf.Repeat(Time.time * 0.15f, 1);
                    break;
            }

            Vector2 offset = new Vector2(scroll, 0);
            GetComponent<Renderer>().sharedMaterial.SetTextureOffset("_MainTex", offset);

            //消滅したオブジェクトは除去する
            _rigidbodies.RemoveAll(r => r == null);

            foreach (var r in _rigidbodies)
            {
                //物体の移動速度のベルトコンベア方向の成分だけを取り出す
                var objectSpeed = Vector3.Dot(r.velocity, DriveDirection);

                //目標値以下なら加速する
                if (objectSpeed < Mathf.Abs(TargetDriveSpeed))
                {
                    r.AddForce(DriveDirection * _forcePower, ForceMode.Acceleration);
                }
            }
            // M.S 接触していたらrigidBodyを削除する
            // 接触時と離れた時のみ追加と削除をすると前の力が残ってしまうため
            // 接触中常時追加と削除をする
            if (hitFlag == true)
            {
                var rigidBody = hitObj.GetComponent<Rigidbody>();
                _rigidbodies.Remove(rigidBody);
                hitFlag = false;
            }
        }
    }
    // M.S 接触中でrigidBodyが削除されていたらrigidBodyを追加する
    void OnCollisionStay(Collision collision)
    {
        if (hitFlag == false)
        {
            var rigidBody = collision.gameObject.GetComponent<Rigidbody>();
            _rigidbodies.Add(rigidBody);
            hitObj = collision.gameObject;  // M.S 接触オブジェクトの保存
            hitFlag = true;
        }
    }
}
// -----------------------------------------------------------------------
// 
// Ｆｂｘスキンメッシュのシェーダー(トゥーンレンダリング)
// 
//                                                      FbxSkinMesh.hlsli
// -----------------------------------------------------------------------
#define MAX_BONE 255

// グローバル変数	
Texture2D g_Texture: register(t0);      // テクスチャーは レジスターt(n)
Texture2D g_NormalTexture : register(t1);     // 法線マップ
Texture2D g_SpecularTexture : register(t3);   // スペキュラーマップ
Texture2D g_ToonTexture : register(t4);       // M.S トゥーンテクスチャ

SamplerState g_samLinear : register(s0); // サンプラーはレジスターs(n)
// コンスタントバッファ
// ワールドから射影までの変換行列・他(b0)
cbuffer global : register(b0)
{
	matrix g_mW;          // ワールド行列
	matrix g_mWV;         // M.S ワールド・ビュー行列
	matrix g_mWVP;        // ワールドから射影までの変換行列
	float4 g_LightDir;    // ライトの方向ベクトル
	float4 g_EyePos;      // 視点位置
	float4 g_Diffuse;     // ディフューズ色	
	float4 g_DrawInfo;    // 各種情報(使っていない)   // -- 2020.12.15
};

// ボーン行列(b1)
cbuffer cbBones : register(b1)
{
	matrix BoneFramePose[MAX_BONE];		// 指定フレームでのメッシュに影響を与える全ての骨のポーズ行列
};

// マテリアルカラーのコンスタントバッファ
cbuffer global : register(b3)               // -- 2020.12.15
{
	float4 g_MatDiffuse = float4(0.5, 0.5, 0.5, 1);   // ディフューズ色	
	float4 g_MatSpecular = float4(0, 0, 0, 0);        // スペキュラ色
};

// スキニング後の頂点・法線が入る
struct Skin
{
	float4 Pos4;
	float3 Normal;
	float3 Tangent; // 接線      // -- 2021.6.11
	float3 Binormal; // 従法線   // -- 2021.6.11
};

// バーテックスシェーダーの入力パラメータ(頂点フォーマットと同一)
struct VS_IN
{
	float3 Pos     : POSITION;		// 頂点座標
	float3 Normal  : NORMAL;		// 法線
	float2 Tex     : TEXCOORD;		// テクセル
	uint4  Bones   : BONE_INDEX;	// ボーンのインデックス
	float4 Weights : BONE_WEIGHT;	// ウェイト
	float3 Tangent : TANGENT; // 接線
	float3 Binormal : BINORMAL; // 従法線

};

// バーテックスシェーダーの出力構造体
// (ピクセルシェーダーの入力となる)
struct VS_OUTPUT
{
	float4 Pos    : SV_POSITION;
	float3 Normal : NORMAL;
	float2 Tex    : TEXCOORD;
	float4 lightTangentSpace : TEXCOORD1; // 接空間に変換されたライトベクトル
	float4 PosWorld:TEXCOORD2;
	float4 ToonUV:TECCOORD3;              // M.Sトゥーンペイントのテクスチャ座標
};

// 接空間行列の逆行列を算出
float4x4 InverseTangentMatrix(float3 tangent, float3 binormal, float3 normal)
{
	tangent = normalize(mul(tangent, (float3x3)g_mW));     // 接線をワールド変換する      // -- 2021.6.11
	binormal = normalize(mul(binormal, (float3x3)g_mW));   // 従法線をワールド変換する
	normal = normalize(mul(normal, (float3x3)g_mW));       // 法線をワールド変換する

	float4x4 mat = { float4(tangent, 0.0f),
		float4(binormal, 0.0f),
		float4(normal, 0.0f),
		{ 0.0f, 0.0f, 0.0f, 1.0f } };

	return transpose(mat); // 転置行列にする
}


// 頂点をスキニング（ボーンによる変形）するサブ関数          // -- 2021.6.11
// （バーテックスシェーダーで使用）
Skin SkinVert(VS_IN In)
{
	Skin Out;
	Out.Pos4 = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Out.Normal = float3(0.0f, 0.0f, 0.0f);
	Out.Tangent = float3(0.0f, 0.0f, 0.0f);
	Out.Binormal = float3(0.0f, 0.0f, 0.0f);

	float4 pos4 = float4(In.Pos, 1);
	float3 normal = In.Normal;
	float3 tangent = In.Tangent;
	float3 binormal = In.Binormal;


	// ボーン0
	uint iBone = In.Bones.x;
	float fWeight = In.Weights.x;
	matrix m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// ボーン1
	iBone = In.Bones.y;
	fWeight = In.Weights.y;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// ボーン2
	iBone = In.Bones.z;
	fWeight = In.Weights.z;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// ボーン3
	iBone = In.Bones.w;
	fWeight = In.Weights.w;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);

	return Out;
}
//
// スペキュラの計算
//
float4 CalcSpecular(float4 Color, float4 texSpecular, float4 PosWorld, float3 Normal, float NMbright)
{
	if (texSpecular.w == 1.0f) // スペキュラマップがあるか
	{
		// ハーフベクトルを使ったスペキュラの計算
		float3 ViewDir = normalize(g_EyePos.xyz - PosWorld.xyz);  // PosWorldからg_EyePosへ向かう視線ベクトル（正規化）
		float3 HalfVec = normalize(g_LightDir.xyz + ViewDir);     // ハーフベクトル（視線ベクトルと光源ベククトルの中間ベクトル）（正規化）

		float Gloss = 4;   // 光沢度係数。指数値が大きいほどスペキュラが狭く強くなる。ここでは4としている。
		float Spec = 2.5f * pow(saturate(dot(HalfVec, Normal)), Gloss);   // スペキュラの計算。後でスペキュラマップ値を掛けるため2.5倍にしておく
		Color.rgb = saturate(Color.rgb + Spec * texSpecular.rgb * NMbright);   // スペキュラにスペキュラマップ値を掛けてカラーに加える。

	}
	return Color;
}

//
// バーテックスシェーダー
//
VS_OUTPUT VS_TOON1(VS_IN In)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4x4 inverseTangentMat;

	Skin vSkinned = SkinVert(In);		// スキニング

	output.Pos = mul(vSkinned.Pos4, g_mWVP);   // 頂点をワールド・ビュー・プロジェクション変換
	output.Normal = mul(vSkinned.Normal, (float3x3)g_mW);    // 法線をワールド変換する
	output.Normal = normalize(output.Normal);               // 法線を正規化する
	// 接空間行列の転置行列を算出
	inverseTangentMat = InverseTangentMatrix(normalize(In.Tangent), normalize(In.Binormal), normalize(In.Normal));   // -- 2021.6.11


	// ライトベクトルを接空間上に変換
	output.lightTangentSpace = mul(float4(g_LightDir.xyz, 1.0), inverseTangentMat);
	output.Tex = In.Tex;         // テクスチャ座標はそのまま出力

	// トゥーンレンダリングの処理
	// トゥーンペイント(陰影)のテクスチャ座標ToonUVを作成する。 
	// 物体表面の明るさ0.01～0.99をテクスチャのU座標にする。
	// (ボーダーラインの位置(0や1)を避けるようにする)
	output.ToonUV.x = min(0.99f, max(0.01f, dot(output.Normal, normalize(g_LightDir.xyz))));

	// M.S トゥーンインク(輪郭線)のテクスチャ座標を求める処理
	// M.S 頂点をワールド・ビュー変換する
	float3 PosWV = normalize(mul(vSkinned.Pos4, g_mWV)).xyz;

	// M.S 法線をワールド・ビュー変換する
	float3 NormalWV = normalize(mul(vSkinned.Normal, (float3x3)g_mWV)).xyz;

	// M.S 内積を求める。内積値に0.5を掛けてから0.5を加算する。この値をテクスチャのV座標とする。
	output.ToonUV.y = dot(PosWV, NormalWV) * 0.5 + 0.5;


	return output;
}

//
// ピクセルシェーダー
//
float4 PS_TOON1(VS_OUTPUT In) : SV_Target
{
	float4 Color;      // 最終出力値
	uint width, height;
	g_Texture.GetDimensions(width, height);  // ディフューズテクスチャのサイズを得る  // -- 2020.12.15
	// テクスチャカラー
	float4 texColor;
	if (width == 0)  // ディフューズテクスチャがないとき  // -- 2020.12.15
	{
		texColor = g_MatDiffuse;      // -- 2020.12.15
	}
	else {
		texColor = g_Texture.Sample(g_samLinear, In.Tex);
	}
	// M.S トゥーンテクスチャの色情報を求める
	float4 texToon = g_ToonTexture.Sample(g_samLinear, In.ToonUV);
	// M.Sトゥーンレンダリング
    // M.S 通常のテクスチャ色(texColor)にトゥーンペイント(ToonUVのサンプラ)を掛け合わせる
	Color.rgb = texColor.rgb * 1.1f * texToon.rgb * g_Diffuse.rgb;    // M.S 少し明るく
	Color.a = texColor.a - (1 - g_Diffuse.a);
	return saturate(Color);
}
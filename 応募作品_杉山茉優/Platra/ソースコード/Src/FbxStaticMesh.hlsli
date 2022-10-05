// -----------------------------------------------------------------------
// 
// Ｆｂｘスタティックメッシュのシェーダー(トゥーンレンダリング)
// 
//                                                    FbxStaticMesh.hlsli
// -----------------------------------------------------------------------

// グローバル変数	
Texture2D g_Texture: register(t0);   //テクスチャーは レジスターt(n)
Texture2D g_NormalTexture : register(t1);     // 法線マップ
Texture2D g_SpecularTexture : register(t3);   // スペキュラーマップ
Texture2D g_ToonTexture : register(t4);       // M.Sトゥーンテクスチャ

SamplerState g_samLinear : register(s0);//サンプラーはレジスターs(n)
//  (コンスタントバッファ)
cbuffer global : register(b0)               // -- 2020.12.15
{
	matrix g_mW;          // ワールド行列
	matrix g_mWV;         // M.S ワールド・ビュー行列
	matrix g_mWVP;        // ワールドから射影までの変換行列
	float4 g_LightDir;    // ライトの方向ベクトル
	float4 g_EyePos;      // 視点位置
	float4 g_Diffuse;     // ディフューズ色	
	float4 g_DrawInfo;    // 各種情報(使っていない)   // -- 2020.12.15
};

// マテリアルカラーのコンスタントバッファ
cbuffer global : register(b3)               // -- 2020.12.15
{
	float4 g_MatDiffuse = float4(0.5, 0.5, 0.5, 1);   // ディフューズ色	
	float4 g_MatSpecular = float4(0, 0, 0, 0);        // スペキュラ色
};

// バーテックスシェーダーの出力構造体
// (ピクセルシェーダーの入力となる)
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
	float3 Normal : NORMAL;
	float4 lightTangentSpace : TEXCOORD1; // 接空間に変換されたライトベクトル
	float4 PosWorld:TEXCOORD2;
	float4 ToonUV:TECCOORD3;              // M.Sトゥーンペイントのテクスチャ座標
};

// 接空間行列の逆行列を算出
float4x4 InverseTangentMatrix(float3 tangent, float3 binormal, float3 normal)
{
	tangent = normalize(mul(tangent, (float3x3)g_mW));     // 接線をワールド変換する    // -- 2021.6.11
	binormal = normalize(mul(binormal, (float3x3)g_mW));   // 従法線をワールド変換する
	normal = normalize(mul(normal, (float3x3)g_mW));       // 法線をワールド変換する

	float4x4 mat = { float4(tangent, 0.0f),
		float4(binormal, 0.0f),
		float4(normal, 0.0f),
		{ 0.0f, 0.0f, 0.0f, 1.0f } };

	return transpose(mat); // 転置行列にする
}

//
// スペキュラの計算
//
float4 CalcSpecular(float4 Color, float4 texSpecular, float4 PosWorld, float3 Normal, float NMbright)
{
	if (texSpecular.w == 1.0f) // スペキュラマップがあるか
	{
		// ハーフベクトルを使ったスペキュラの計算
		float3 ViewDir = normalize( g_EyePos.xyz - PosWorld.xyz);  // PosWorldからg_EyePosへ向かう視線ベクトル（正規化）
		float3 HalfVec = normalize( g_LightDir.xyz + ViewDir);     // ハーフベクトル（視線ベクトルと光源ベククトルの中間ベクトル）（正規化）

		float Gloss = 4;   // 光沢度係数。指数値が大きいほどスペキュラが狭く強くなる。ここでは4としている。
		float Spec = 2.5f * pow( saturate(dot(HalfVec, Normal)), Gloss );   // スペキュラの計算。後でスペキュラマップ値を掛けるため2.5倍にしておく
		Color.rgb = saturate(Color.rgb + Spec * texSpecular.rgb * NMbright);   // スペキュラにスペキュラマップ値を掛けてカラーに加える。

	}
	return Color;
}

//
// バーテックスシェーダー
//
VS_OUTPUT VS(float3 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD, float3 Tangent : TANGENT, float3 Binormal : BINORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 Pos4 = float4(Pos, 1);
	float4x4 inverseTangentMat;

	output.Pos = mul(Pos4, g_mWVP);  // 頂点をワールド・ビュー・プロジェクション変換する
	output.Normal = mul(Normal, (float3x3)g_mW); // 法線をワールド変換する
	output.Normal = normalize(output.Normal);     // 法線を正規化

	// 接線の計算
	// 接空間行列の逆行列を算出
	inverseTangentMat = InverseTangentMatrix(normalize(Tangent), normalize(Binormal), normalize(Normal));

	// ライトベクトルを接空間上に変換
	output.lightTangentSpace = mul(float4(g_LightDir.xyz, 1.0), inverseTangentMat);

	// テクスチャ座標はそのまま出力
	output.Tex = Tex;

	// トゥーンレンダリングの処理
	// トゥーンペイント(陰影)のテクスチャ座標ToonUVを作成する。 
	// 物体表面の明るさ0.01～0.99をテクスチャのU座標にする。
	// (ボーダーラインの位置(0や1)を避けるようにする)
	output.ToonUV.x = min(0.99f, max(0.01f, dot(output.Normal, normalize(g_LightDir.xyz))));

	// M.Sトゥーンインク(輪郭線)のテクスチャ座標を求める処理
	// M.S 頂点をワールド・ビュー変換する
	float3 PosWV = normalize(mul(Pos4, g_mWV)).xyz;

	// M.S 法線をワールド・ビュー変換する
	float3 NormalWV = normalize(mul(Normal, (float3x3)g_mWV)).xyz;

	// M.S 内積を求める。内積値に0.5を掛けてから0.5を加算する。この値をテクスチャのV座標とする。
	// M.S インク部分を増やすため0.52を掛けている
	output.ToonUV.y = dot(PosWV, NormalWV) * 0.5 + 0.52;

	return output;
}

//
// ピクセルシェーダー
//
float4 PS(VS_OUTPUT In) : SV_Target
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
	Color.rgb = texColor.rgb * 1.0f * texToon.rgb * g_Diffuse.rgb;
	Color.a = texColor.a - (1 - g_Diffuse.a);
	return saturate(Color);  // 最終出力値を0～１の範囲に制限する
}

// 型抜き用の透明シェーダ
Shader "Custom/Cutout" {
	Properties{
		_Color("Color", Color) = (1,1,1,1)
	}

		SubShader{
			Tags {"Queue" = "Geometry-1"}

			Pass{
				Zwrite On
				ColorMask 0
			}
	}
}
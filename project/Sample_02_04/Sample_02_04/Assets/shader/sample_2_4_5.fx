//頂点シェーダーへの入力。
struct VSInput{
	float4 pos : POSITION;
};
//頂点シェーダーの出力。
struct VSOutput{
	float4 pos : SV_POSITION;
};
//頂点シェーダー。
//１．引数は変換前の頂点情報。
//２．戻り値は変換後の頂点情報。
VSOutput VSMain(VSInput In) 
{
	VSOutput vsOut = (VSOutput)0;
    //入力された頂点座標を変換せずに出力する。
    vsOut.pos = In.pos;
	return vsOut;
}
//ピクセルシェーダー。
float4 PSMain( VSOutput vsOut ) : SV_Target0
{
	return float4( 1.0f, 0.0f, 0.0f, 1.0f);
}
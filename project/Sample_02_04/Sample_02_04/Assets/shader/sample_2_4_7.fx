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
    //頂点座標を拡大して出力座標に渡す
    vsOut.pos = In.pos;
    vsOut.pos.x *= 1.5f; //X座標を１．５倍にする。
    vsOut.pos.y *= 0.5f; //Y座標を０．５倍にする。
	return vsOut;
}
//ピクセルシェーダー。
float4 PSMain( VSOutput vsOut ) : SV_Target0
{
	return float4( 1.0f, 0.0f, 0.0f, 1.0f);
}
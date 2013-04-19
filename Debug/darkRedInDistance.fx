//--------------------------------------------------------------------------------------
// basicEffect.fx
//--------------------------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;

float TotalTime;

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

struct VS_INPUT
{
    float4 Pos : POSITION;
    float4 Color : COLOR;    
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output;
        
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );    
    output.Pos = mul( output.Pos, Projection );
    output.Color = input.Color;
        
    return output;  
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input ) : SV_Target
{
    float4 newColor = input.Color;

    if (input.Pos.y < 250) {
        newColor[0] = newColor[0] * input.Pos.y / 500;
        newColor[1] = 0;
        newColor[2] = 0;
    }

    return newColor;
}

//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------
technique10 render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}


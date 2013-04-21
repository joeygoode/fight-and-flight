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
    float2 rand1    = float2(input.Pos[0], input.Pos[1]);
    float2 noise    = (frac(sin(dot(rand1 ,float2(12.8291, 78.2331)*2.0)) * 1758.5453));
    float randNoise = abs(noise.x + noise.y) * 0.5;

    // Clone current color first
    float4 color    = input.Color;
    float4 newColor = input.Color;

    float avgColor = (color[0] + color[1] + color[2]) / 3;

    float redDifFromGreen  = abs(input.Color[1] - input.Color[0]);
    float blueDifFromGreen = abs(input.Color[2] - input.Color[0]);

    if (redDifFromGreen > 0.4 || blueDifFromGreen > 0.4) {
        newColor[0] = 0;
        newColor[1] = ((redDifFromGreen + blueDifFromGreen) / 2 + (randNoise / 2));
        newColor[2] = 0;
        return newColor;
    }
    else
        return avgColor * 0.5;
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


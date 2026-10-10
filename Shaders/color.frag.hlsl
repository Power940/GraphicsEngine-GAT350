struct Input
{
    float3 PassPosition : TEXCOORD0;
};

struct Output
{
    float4 Color : SV_Target0;
};

Output main(Input input)
{
    Output output;
    
    float x = saturate((input.PassPosition.x + 1.0f) / 2.0f);
    float y = saturate((input.PassPosition.y + 1.0f) / 2.0f);

    output.Color = float4(
        1.0f - x,
        y,
        x,
        1.0f
    );

    return output;
}

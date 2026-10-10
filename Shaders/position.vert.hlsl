struct Input
{
    float3 position : TEXCOORD0;
};

struct Output
{
    float4 Position : SV_Position;
    float3 PassPosition : TEXCOORD0;
};

Output main(Input input)
{
    Output output;
    if (input.position.x == 0.0f)
    {
        output.Position = float4(input.position.x - 0.5f, input.position.yz, 1.0f);
    }
    else
    {
        output.Position = float4(input.position.x * 0.5f, input.position.yz, 1.0f);
    }
    output.PassPosition = input.position;

    return output;
}
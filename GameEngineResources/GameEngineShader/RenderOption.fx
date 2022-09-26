cbuffer RenderOption : register(b10)
{
    float DeltaTime;
    float SumDeltaTime;
    int Temp0;
    int Temp1;
};

cbuffer Time : register(b9)
{
    float4 Pos;
}
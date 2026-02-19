#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;
layout (location = 3) in vec4 VertexTangent;


uniform vec4 LightPosition;
uniform vec3 Kd, Ld;
uniform mat4 ModelViewMatrix, MVP;
uniform mat3 NormalMatrix;

out vec3 LightIntensity;
out vec3 pos;
out vec2 TexCoord;
out vec3 LightDir;
out vec3 ViewDir;


uniform struct SpotLightInfo
{
    vec4 Position;
    vec3 L;
    vec3 La;
    vec3 Direction;
    float Exponent;
    float Cutoff;
}Spot;


void main()
{
    
    vec3 n = normalize(NormalMatrix * VertexNormal);
    pos=(ModelViewMatrix*vec4(VertexPosition,1.0)).xyz;
    
    vec3 tang = normalize(NormalMatrix * vec3(VertexTangent));

    vec3 binormal = normalize(cross(n,tang)) * VertexTangent.w;

    mat3 toObjectLocal = mat3(
        tang.x, binormal.x, n.x,
        tang.y, binormal.y, n.y,
        tang.z, binormal.z, n.z
    );

    LightDir = toObjectLocal * (Spot.Position.xyz - pos);
    ViewDir = toObjectLocal * normalize(-pos);

    TexCoord = VertexTexCoord;

    gl_Position = MVP*vec4(VertexPosition,1.0);
}


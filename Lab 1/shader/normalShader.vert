#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;
layout (location = 3) in vec4 VertexTangent;


uniform struct LightInfo
{
    vec4 Position;
    vec3 La;
    vec3 L;
}Light;

uniform vec4 LightPosition;
uniform vec3 Kd, Ld;
uniform mat4 ModelViewMatrix, MVP;
uniform mat3 NormalMatrix;

out vec3 LightIntensity;
out vec3 pos;
out vec2 TexCoord;

out vec3 LightDir, ViewDir;


void main()
{
    
    vec3 normal = normalize(NormalMatrix * VertexNormal);
    vec3 tangent = normalize(NormalMatrix*vec3(VertexTangent.xyz));
    vec3 binormal = normalize(cross(normal,tangent)) * VertexTangent.w;
    vec3 pos=(ModelViewMatrix*vec4(VertexPosition,1.0)).xyz;

    mat3 toObjectLocal = mat3(
        tangent.x, binormal.x, normal.x,
        tangent.y, binormal.y, normal.y,
        tangent.z, binormal.z, normal.z
    );


   
    LightDir = toObjectLocal*(Light.Position.xyz-pos);
    ViewDir = toObjectLocal*normalize(-pos);
    TexCoord = VertexTexCoord;

    gl_Position = MVP*vec4(VertexPosition,1.0);
}


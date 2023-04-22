#version 430 core

in vec2 TexCoord;
in vec3 Normal;
in float Height;

out vec4 FragColor;

uniform sampler2D grassTexture;
uniform sampler2D rockTexture;
uniform sampler2D sandTexture;

void main()
{
    vec4 grassColor = texture(grassTexture, TexCoord);
    vec4 rockColor = texture(rockTexture, TexCoord);
    vec4 sandColor = texture(sandTexture, TexCoord);

    float sandThreshold = 0.8;
    float grassThreshold = 4;
    float transitionWidth = 0.6;

    float sandWeight = smoothstep(sandThreshold - transitionWidth, sandThreshold + transitionWidth, Height);
    float grassWeight = smoothstep(grassThreshold - transitionWidth, grassThreshold + transitionWidth, Height);

    vec4 finalColor = mix(sandColor, grassColor, sandWeight);
    finalColor = mix(finalColor, rockColor, grassWeight);

    FragColor = finalColor;
}

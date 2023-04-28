#version 430 core

in vec2 TexCoord;
in vec3 Normal;
in float Height;

out vec4 FragColor;

uniform sampler2D grassTexture;
uniform sampler2D rockTexture;
uniform sampler2D sandTexture;
uniform sampler2D waterTexture;
uniform sampler2D snowTexture;

void main()
{
    vec4 grassColor = texture(grassTexture, TexCoord);
    vec4 rockColor = texture(rockTexture, TexCoord);
    vec4 sandColor = texture(sandTexture, TexCoord);
    vec4 waterColor = texture(waterTexture, TexCoord);
    vec4 snowColor = texture(snowTexture, TexCoord);


    float sandThreshold = 0.7;
    float grassThreshold = 4;
    float waterThreshold = 0.005;
    float rockThreshold = 14;
    float transitionWidth = 0.6;


    float sandWeight = smoothstep(sandThreshold - transitionWidth, sandThreshold + transitionWidth, Height);
    float grassWeight = smoothstep(grassThreshold - transitionWidth, grassThreshold + transitionWidth, Height);
    float waterWeight = smoothstep(waterThreshold - transitionWidth, waterThreshold + transitionWidth, Height);
    float rockWeight = smoothstep(rockThreshold - transitionWidth, rockThreshold + transitionWidth, Height);

    vec4 finalColor = mix(waterColor, sandColor, waterWeight);
    finalColor = mix(finalColor, grassColor, sandWeight);
    finalColor = mix(finalColor, rockColor, grassWeight);
    finalColor = mix(finalColor, snowColor, rockWeight);


    FragColor = finalColor;
}

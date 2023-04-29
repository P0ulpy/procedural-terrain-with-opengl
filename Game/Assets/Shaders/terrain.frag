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

vec3 permute(vec3 x) { return mod(((x*34.0)+1.0)*x, 289.0); }

float simplexNoise(vec2 uv) {
    const vec4 C = vec4(0.211324865405187, 0.366025403784439,
    -0.577350269189626, 0.024390243902439);
    vec2 i  = floor(uv + dot(uv, C.yy));
    vec2 x0 = uv - i + dot(i, C.xx);

    vec2 i1;
    i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
    vec4 x12 = x0.xyxy + C.xxzz;
    x12.xy -= i1;

    i = mod(i, 289.0);
    vec3 p = permute(permute(i.y + vec3(0.0, i1.y, 1.0))
    + i.x + vec3(0.0, i1.x, 1.0));

    vec3 m = max(0.5 - vec3(dot(x0, x0), dot(x12.xy, x12.xy),
    dot(x12.zw, x12.zw)), 0.0);
    m = m*m;
    m = m*m;

    vec3 x = 2.0 * fract(p * C.www) - 1.0;
    vec3 h = abs(x) - 0.5;
    vec3 ox = floor(x + 0.5);
    vec3 a0 = x - ox;

    m *= 1.79284291400159 - 0.85373472095314 * (a0*a0 + h*h);

    vec3 g;
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.yz = a0.yz * x12.xz + h.yz * x12.yw;
    return 130.0 * dot(m, g);
}

void main()
{
    float patchSize = 4;

    vec4 grassColor = texture(grassTexture, TexCoord);
    vec4 rockColor = texture(rockTexture, TexCoord);
    vec4 sandColor = texture(sandTexture, TexCoord);
    vec4 waterColor = texture(waterTexture, TexCoord);
    vec4 snowColor = texture(snowTexture, TexCoord);

    float noise = simplexNoise(TexCoord * patchSize);

    snowColor = mix(snowColor, rockColor*2, noise);

    float sandThreshold = 0.7;
    float grassThreshold = 4;
    float waterThreshold = 0.005;
    float rockThreshold = 20;
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


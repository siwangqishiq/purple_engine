precision highp float;

out vec4 outColor;

in vec4 particleColor;
flat in int particleType;
in float pointSize;

void main() {
    // outColor = vec4(0.2f, 0.6f, 1.0f, 1.0f); // 蓝色
    // outColor = particleColor;

    if(particleType != 1){
        discard;
    }
    
    vec2 center = vec2(0.5f , 0.5f);
    float distance = length(gl_PointCoord - center);
    float radius = 0.5;

    // float alpha = 1.0 - step(radius, distance);
    // if (alpha <= 0.0) 
    //     discard;
    float alpha = smoothstep(radius, radius - 0.05f, distance);
    outColor = vec4(particleColor.rgb,  alpha);
}


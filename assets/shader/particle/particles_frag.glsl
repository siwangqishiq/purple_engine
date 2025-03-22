precision highp float;

out vec4 outColor;
in vec4 particleColor;

void main() {
    // outColor = vec4(0.2f, 0.6f, 1.0f, 1.0f); // 蓝色
    // outColor = particleColor;
    
    vec2 center = vec2(0.5f , 0.5f);
    float distance = length(gl_PointCoord - center);
    float radius = 0.5;

    float alpha = 1.0 - step(radius, distance);
    if (alpha <= 0.0) discard;
    outColor = vec4(particleColor.rgb, alpha);
}


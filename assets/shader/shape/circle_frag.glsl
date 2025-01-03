precision highp float;

uniform vec4 uColor;
uniform int uFillType;
uniform float uStrokenWidth;

in vec2 originPos;
in vec4 circleParams;

out vec4 fragColor;

const int MODE_FILL = 0;
const int MODE_STROKEN = 1;

float sdfCircle(vec2 p , vec2 center , float radius){
    return length(p - center) - radius;
}

void main(){
    vec2 c = vec2(circleParams.xy);
    float radius = circleParams.z;

    float sdfValue = sdfCircle(originPos , c , radius);
    // float smoothSize = min(0.1f , fwidth(sdfValue));

    float smoothSize = max(radius / 64.0f, 0.1f);
    // float sdfAlpha = step(0.0f , -sdfValue);
    float sdfAlpha = smoothstep(-smoothSize, smoothSize, -sdfValue);
    fragColor = vec4(uColor.rgb, uColor.a * sdfAlpha);

    // fragColor = vec4(uColor.rgba);
}
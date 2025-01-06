precision highp float;

uniform vec4 uColor;
uniform int uFillType;
uniform float uStrokenWidth;
uniform float blurRadius;

in vec2 originPos;
in vec4 circleParams;

out vec4 fragColor;

const int FILL = 0;
const int STROKEN = 1;

float SmoothSize = 1.0f;

float sdfCircle(vec2 p , vec2 center , float radius){
    return length(p - center) - radius;
}
float alphaFromSdf(float d, float edge) {
    return smoothstep(edge, -edge, d);
}

void main(){
    vec2 c = vec2(circleParams.xy);
    float radius = circleParams.z;
    SmoothSize = max(0.1f, radius / 60.0f);
    
    float sdfValue = 0.0f;
    if(uFillType == FILL){
        sdfValue = sdfCircle(originPos , c , radius);
        fragColor = vec4(uColor.rgb, uColor.a * alphaFromSdf(sdfValue , SmoothSize));
    }else if(uFillType == STROKEN){
        sdfValue = abs(sdfCircle(originPos , c , radius)) - uStrokenWidth;
        fragColor = vec4(uColor.rgb, uColor.a * alphaFromSdf(sdfValue , SmoothSize));
    }
}
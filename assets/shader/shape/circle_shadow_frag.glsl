precision highp float;

uniform vec4 uColor;
uniform int uFillType;
uniform float uStrokenWidth;

in vec2 originPos;
in vec4 circleParams;

out vec4 fragColor;

const int FILL = 0;
const int STROKEN = 1;

// float SmoothSize = 2.0f;

float sdfUnion(float sd1 , float sd2){
    return min(sd1 , sd2);
}

float sdfSub(float sd1 , float sd2){
    return max(-sd2 , sd1);
}

float sdfCircle(vec2 p , vec2 center , float radius){
    return length(p - center) - radius;
}

float sdfCircleShadow(vec2 p , vec2 center , float radius , float outterRadius) {
    if(length(p - center) <= radius){
        return outterRadius;
    }else{
        return sdfCircle(p , center , outterRadius);
    }

    // float c1 = sdfCircle(p , center , outterRadius);
    // float c2 = sdfCircle(p , center , radius);
    // return sdfSub(c1 , c2);
}

float alphaFromSdf(float d, float edge) {
    return smoothstep(edge, -edge, d);
}

void main(){
    vec2 c = vec2(circleParams.xy);
    float radius = circleParams.z;
    float outterRadius = circleParams.w;
            
    float sdfValue = 0.0f;
    if(uFillType == FILL){
        float dR = outterRadius - radius;
        float edgeValue = sdfCircleShadow(originPos , c , radius , outterRadius);
        fragColor = vec4(uColor.rgb, uColor.a * alphaFromSdf(edgeValue , (outterRadius - radius) / 2.0f));
    }else if(uFillType == STROKEN){
        // sdfValue = abs(sdfCircle(originPos , c , radius)) - uStrokenWidth;
        // fragColor = vec4(uColor.rgb, uColor.a * alphaFromSdf(sdfValue , SmoothSize));
    }

    // fragColor =vec4(1.0f ,1.0f , 0.0f ,1.0f);
}
precision highp float;

uniform vec4 uColor;

in vec2 outPos;
in vec4 outCoords;

out vec4 fragColor;

float rectSdf(vec2 p , vec4 rect){
    // 矩形的四个边界
    float left = rect.x;
    float top = rect.y;
    float width = rect.z;
    float height = rect.w;
    // 计算矩形左右和上下边界与点 p 的距离
    float dx = max(left - p.x, p.x - (left + width));  // 点与矩形左边界或右边界的距离
    float dy = max(top - p.y, p.y - (top - height));  // 点与矩形上边界或下边界的距离
    return length(vec2(dx, dy));  // 返回点到矩形边缘的最短距离
    
    // float left = rect.x;
    // float right = left + rect.z;
    
    // def sdf_rectangle(x, y, x0, y0, w, h):
    // dleft = x-(x0 - w/2)
    // dright = (x0 + w/2)-x
    // dtop = y-(y0 + h/2)
    // dbottom = (y0 - h/2)-y
    // inside_distance = -min(min(dleft, dright), min(dtop, dbottom))
    // outside_distance = min(min(dleft, dright), min(dtop, dbottom))
    // if inside_distance < 0:
    //     return inside_distance
    // else:
    //     return outside_distance
}

// float circleSdf(vec2 p , vec4 rect){
//     float left = rect.x;
//     float top = rect.y;
//     float width = rect.z;
//     float height = rect.w;

//     vec2 center = vec2(left + width/2.0f, top - height/2.0f);
//     float radius = height / 2.0f;
//     return radius - length(p - center);
// }

void main(){
    float sdfValue = rectSdf(outPos , outCoords);
    if(sdfValue > 10.0f){
        sdfValue = 0.0f;
    }
    // float sdfValue = circleSdf(outPos , outCoords);
    float smoothSize = 10.0f;
    float sdfAlpha = (smoothstep(-smoothSize, smoothSize, sdfValue));
    fragColor = vec4(uColor.rgb, uColor.a * sdfAlpha);
    // fragColor = vec4(0.0f , 1.0f , 0.0f , 1.0f);
}
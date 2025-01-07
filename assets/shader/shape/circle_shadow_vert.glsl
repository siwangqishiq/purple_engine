layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aRect;

uniform mat3 transMat;

out vec2 originPos;
out vec4 circleParams;

void main(){
    float depth = aPos.z;
    
    originPos = aPos.xy;
    circleParams = aRect;

    vec3 pos = transMat * vec3(aPos.xy , 1.0f);
    gl_Position = vec4(pos.xy , depth ,1.0f);
}

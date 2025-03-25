
layout(local_size_x = 32) in;

struct Particle{
    vec4 position;
    vec4 velocity;
    vec4 color;
    int type;
    float size;
    vec2 padding;
};

layout(std430, binding = 0) buffer SSBO {
    Particle particleData[];
};

uniform vec2 viewSize;
uniform float dt;

void main(){
    uint idx = gl_GlobalInvocationID.x;
    Particle p = particleData[idx];

    vec2 vel = p.velocity.xy;
    if(p.position.x <= -20.0f || p.position.x >= viewSize.x ){
        vel.x = -vel.x; 
    }
    if(p.position.y <= -20.0f|| p.position.y >= viewSize.y ){
        vel.y = -vel.y;
    }
    
    p.velocity = vec4(vel.xy , 0.0f, 0.0f);
    p.position = p.position + p.velocity * dt;
    particleData[idx] = p;
}   






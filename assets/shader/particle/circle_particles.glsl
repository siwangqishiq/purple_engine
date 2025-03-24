
layout(local_size_x = 32) in;

struct Particle{
    vec3 position;
    float _padding0;
    vec3 velocity;
    float _padding1;
    vec4 color;
};

layout(std430, binding = 0) buffer SSBO {
    Particle particleData[];
};

const float espi = 0.001f;

// uniform int uParticleCount;

void main(){
    uint idx = gl_GlobalInvocationID.x;
    Particle p = particleData[idx];

    vec2 vel = p.velocity.xy;
    if(p.position.x <= -1.0f - espi || p.position.x >= 1.0f + espi){
        vel.x = -vel.x; 
    }
    if(p.position.y <= -1.0f - espi || p.position.y >= 1.0f + espi){
        vel.y = -vel.y;
    }
    
    p.velocity = vec3(vel.xy , 0.0f);
    p.position = p.position + p.velocity;
    particleData[idx] = p;
}   






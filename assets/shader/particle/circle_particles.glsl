
layout(local_size_x = 32, local_size_y = 32 , local_size_z = 1) in;

struct Particle{
    vec2 position;
    vec2 velocity;
};

layout(std430, binding = 0) buffer SSBO {
    Particle particleData[];
};

// uniform int uParticleCount;

void main(){
    uint idx = gl_GlobalInvocationID.x;
    Particle p = particleData[idx];
    vec2 vel = p.velocity;
    if(p.position.x <= -1.0f || p.position.x >= 1.0f){
        vel.x = -1.0f * vel.x; 
    }
    if(p.position.y <= -1.0f || p.position.y >= 1.0f){
        vel.y = -1.0f * vel.y;
    }
    p.velocity = vel;
    p.position = p.position + p.velocity;
    particleData[idx] = p;
}   






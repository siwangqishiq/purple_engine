
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
    p.position = p.position + 0.001f * p.velocity;
    particleData[idx] = p;
}   






struct Particle{
    vec4 position;
    vec4 velocity;
};

layout(std430, binding = 0) buffer ParticleBuffer{
    Particle particles[];
};

layout (local_size_x=16, local_size_y=16 , local_size_z = 4) in;

uniform float deltaTime;
uniform vec3 emitterPosition;
uniform uint maxParticles;

float rand(float seed) {
    return fract(sin(float(seed) * 12.98f) * 43758.5453f);
}

void main(){
    uint id = gl_GlobalInvocationID.x;
    if(id > maxParticles){
        return;
    }

    Particle p = particles[id];
    
    if (p.velocity.w > 0.0f) {
        p.position.xyz += p.velocity.xyz * deltaTime;
        p.velocity.w -= deltaTime;
        if (p.velocity.w <= 0.0f) {
            p.position.w = 0.0f; // 失效
        }
    } else {
        float id_float = float(id);
        p.position = vec4(emitterPosition, 1.0f);
        p.velocity = vec4((
            vec3(rand(id_float), 
                rand(id_float + 1.0f), 
                rand(id_float + 2.0f)) - 0.5f) * 2.0f, 
            1.0f
        );
        p.velocity.w = 1.0f; // 生命时间
    }
    
    particles[id] = p;
}


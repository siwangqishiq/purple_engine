
struct Particle{
    vec3 position;
    float _padding0;
    vec3 velocity;
    float _padding1;
    vec4 color;
};

layout(std430, binding = 0) buffer SSBO {
    Particle particles[];
};

out vec4 particleColor;

void main(){
    Particle p = particles[gl_VertexID];
    gl_Position = vec4(p.position, 1.0f);
    gl_PointSize = 32.0f;
    particleColor = p.color;
}


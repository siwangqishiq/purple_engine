
struct Particle{
    vec2 position;
    vec2 velocity;
};

layout(std430, binding = 0) buffer SSBO {
    Particle particles[];
};

out vec4 particleColor;

void main(){
    gl_Position = vec4(particles[gl_VertexID].position, 0.0, 1.0);
    gl_PointSize = 14.0f;
    particleColor = vec4(1000.0f * (particles[gl_VertexID].velocity), 1.0f , 1.0f);
}


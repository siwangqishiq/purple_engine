
struct Particle{
    vec2 position;
    vec2 velocity;
};

layout(std430, binding = 0) buffer SSBO {
    Particle particles[];
};

void main(){
    gl_Position = vec4(particles[gl_VertexID].position, 0.0, 1.0);
    gl_PointSize = 10.0f;
}


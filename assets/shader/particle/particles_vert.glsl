
struct Particle{
    vec4 position;
    vec4 velocity;
    vec4 color;
    int type;
    float size;
    vec2 padding;
};

layout(std430, binding = 0) buffer SSBO {
    Particle particles[];
};

out vec4 particleColor;
flat out int particleType;
out float pointSize;

uniform float depth;
uniform mat3 transMat;

void main(){
    Particle p = particles[gl_VertexID];
    vec3 pos = transMat * vec3(p.position.xy , 1.0f);
    gl_Position = vec4(pos.xy, depth, 1.0f);
    gl_PointSize = p.size;
    pointSize = p.size;
    particleColor = p.color;
    particleType = p.type;
}


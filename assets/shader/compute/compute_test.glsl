#version 430 core

layout (local_size_x=16, local_size_y=16 , local_size_z = 1) in;

uniform float v[4];

layout (rgba32f, binding = 0) uniform image2D input_image;
layout (rgba32f, binding = 1) uniform image2D output_image;

// shared vec4 mat_shared[16][16];

void main() {
    ivec2 pos=ivec2(gl_GlobalInvocationID.xy);
    // mat_shared[pos.x][pos.y]=imageLoad(input_image,pos);
    barrier();
    vec4 data=imageLoad(input_image,pos);
    data.r=v[0]+data.r + 1.0f;
    data.g=v[1]+data.g + 1.0f;
    data.b=v[2]+data.b + 1.0f;
    data.a=v[3]+data.a;
    
    imageStore(output_image,pos.xy,data);
}




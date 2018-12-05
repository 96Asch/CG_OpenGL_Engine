#version 430 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in TD_DATA {
  vec2 tex0;
  vec3 normal0;
  vec3 world0;
  float vis0;
} inData[];

out TD_DATA {
  vec2 tex0;
  vec3 normal0;
  vec3 world0;
  float vis0;
} outData;

uniform float explodeDistance;
uniform float explodeActive;

vec4 explode(vec4 position, vec3 normal) {
    float magnitude = 2.0;
    vec3 direction = normalize(normal + vec3(0,1,0));
    return position + (vec4(direction, 0.0) * explodeActive * explodeDistance);
}

vec3 GetNormal() {
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}

void emitVertex(int vertex, vec3 normal) {
  gl_Position = explode(gl_in[vertex].gl_Position, normal);
  outData.tex0 = inData[vertex].tex0;
  outData.normal0 = inData[vertex].normal0;
  outData.world0 = inData[vertex].world0;
  outData.vis0 = inData[vertex].vis0;
  EmitVertex();
}

void main() {
    vec3 normal = GetNormal();
    emitVertex(0, normal);
    emitVertex(1, normal);
    emitVertex(2, normal);
    EndPrimitive();
}

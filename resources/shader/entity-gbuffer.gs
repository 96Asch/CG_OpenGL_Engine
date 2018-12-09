#version 430 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in TD_DATA {
  vec3 world0;
  vec2 tex0;
  vec3 normal0;
} inData[];

out TD_DATA {
  vec3 world0;
  vec2 tex0;
  vec3 normal0;
} outData;

float isExplodedTriangle = 0;

uniform float explodeDistance;
uniform float explodeActive;

float when_gt(float x, float y) {
  return max(sign(x - y), 0.0);
}

float when_eq(float x, float y) {
  return 1.0 - abs(sign(x - y));
}

float when_lt(float x, float y) {
  return max(sign(y - x), 0.0);
}


vec4 explode(vec4 position, vec3 normal, float isExploded) {
     vec3 direction = normal * explodeDistance * explodeActive;
    return position + (vec4(direction, 0.0) * isExploded);
}

vec3 GetNormal() {
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}

void emitVertex(int vertex, vec3 normal, float isExploded) {
  vec4 position = explode(gl_in[vertex].gl_Position, normal, isExploded);
  gl_Position = position;
  outData.tex0 = inData[vertex].tex0;
  outData.normal0 = inData[vertex].normal0;
  outData.world0 = inData[vertex].world0;
  EmitVertex();
}

float explodeCondition() {
  float expCondition = explodeDistance * 0.5;
  float t1 = when_lt(inData[0].world0.y, expCondition);
  float t2 = when_lt(inData[1].world0.y, expCondition);
  float t3 = when_lt(inData[2].world0.y, expCondition);
  return when_eq(when_eq(t1,t2), t2);
}

void main() {
    vec3 normal = GetNormal();
    isExplodedTriangle = explodeCondition();
    emitVertex(0, normal, isExplodedTriangle);
    emitVertex(1, normal, isExplodedTriangle);
    emitVertex(2, normal, isExplodedTriangle);
    EndPrimitive();
}

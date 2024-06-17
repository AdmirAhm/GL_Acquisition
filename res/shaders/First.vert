//komentar
#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 initialAngle; 
layout (location = 2) in vec3 initialTranslation; 
layout (location = 3) in vec3 initialColor;
layout (location = 4) in vec3 angle; 
layout (location = 5) in vec3 translation; 
layout (location = 6) in vec3 color;
layout (location = 7) in vec3 multAngle; 
layout (location = 8) in vec3 multTranslation; 
layout (location = 9) in vec3 multColor;

uniform mat4 mvp;
uniform mat4 measurein;


out vec4 fragColorVert;

mat4 rotateX(float angle) 
{
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    return mat4(1.0, 0.0, 0.0, 0.0,
                0.0, cosTheta, -sinTheta, 0.0,
                0.0, sinTheta, cosTheta, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

mat4 rotateY(float angle) 
{
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    return mat4(cosTheta, 0.0, sinTheta, 0.0,
                0.0, 1.0, 0.0, 0.0,
                -sinTheta, 0.0, cosTheta, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

mat4 rotateZ(float angle) 
{
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    return mat4(cosTheta, -sinTheta, 0.0, 0.0,
                sinTheta, cosTheta, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

void main() 
{
  int xind1, xind2, yind1, yind2, zind1, zind2;

  
  xind1=int(floor(angle.x/4));
  xind2=int(floor(angle.x))-4*xind1;
  yind1=int(floor(angle.y/4));
  yind2=int(floor(angle.y))-4*yind1;
  zind1=int(floor(angle.z/4));
  zind2=int(floor(angle.z))-4*zind1;
  mat4 rotation=rotateZ(initialAngle.x+measurein[xind1][xind2]*multAngle.x)*rotateY(initialAngle.y+measurein[yind1][yind2]*multAngle.y)*rotateX(initialAngle.z+measurein[zind1][zind2]*multAngle.z);
  
  xind1=int(floor(translation.x/4));
  xind2=int(floor(translation.x))-4*xind1;
  yind1=int(floor(translation.y/4));
  yind2=int(floor(translation.y))-4*yind1;
  zind1=int(floor(translation.z/4));
  zind2=int(floor(translation.z))-4*zind1;
  vec4 Trans = vec4(initialTranslation.x+measurein[xind1][xind2]*multTranslation.x, initialTranslation.y+measurein[yind1][yind2]*multTranslation.y, initialTranslation.z+measurein[zind1][zind2]*multTranslation.z, 0.0);
  vec4 rotatedAndTranslatedPosition = rotation * vec4(position, 1.0) + Trans;
  
  xind1=int(floor(color.x/4));
  xind2=int(floor(color.x))-4*xind1;
  yind1=int(floor(color.y/4));
  yind2=int(floor(color.y))-4*yind1;
  zind1=int(floor(color.z/4));
  zind2=int(floor(color.z))-4*zind1;
  fragColorVert=vec4(initialColor.x+measurein[xind1][xind2]*multColor.x, initialColor.y+measurein[yind1][yind2]*multColor.y, initialColor.z+measurein[zind1][zind2]*multColor.z, 1.0);

  gl_Position = mvp * rotatedAndTranslatedPosition;
}

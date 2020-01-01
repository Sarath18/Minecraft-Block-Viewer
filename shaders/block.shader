#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
   gl_Position = projection * view * model * position;
   v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

layout(location = 0) out vec4 color;

void main()
{
   vec4 texColor = texture(u_Texture, v_TexCoord);
   color = texColor;
}
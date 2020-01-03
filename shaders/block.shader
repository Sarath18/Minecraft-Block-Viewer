#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;
out vec2 v_TexCoord;

void main()
{
   gl_Position = projection * view * model * position;
   v_TexCoord = texCoord;
   FragPos = vec3(model * position);
   Normal = mat3(transpose(inverse(model))) * normal;
}

#shader fragment
#version 330 core

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

struct Light {
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform int lightingEnabled;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

layout(location = 0) out vec4 color;

void main()
{
   // Apply texture without lighting
   if(lightingEnabled == 0) {
      vec4 texColor = texture(u_Texture, v_TexCoord);
      color = texColor;
   }

   //Phong Shading
   else
   {
      // Ambient
      vec3 ambient = light.ambient * texture(material.diffuse, v_TexCoord).rgb;

      // Diffuse
      vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(light.position - FragPos);
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = light.diffuse * diff * texture(material.diffuse, v_TexCoord).rgb;

      // Specular
      vec3 viewDir = normalize(viewPos - FragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
      vec3 specular = light.specular * spec * texture(material.specular, v_TexCoord).rgb;

      vec3 result = ambient + diffuse + specular;
      color = vec4(result, 1.0);
   }
}
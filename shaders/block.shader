#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec2 specTexCoord;
layout(location = 4) in vec2 breakTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;
out vec2 v_TexCoord;
out vec2 s_TexCoord;
out vec2 b_TexCoord;

void main()
{
   gl_Position = projection * view * model * position;
   v_TexCoord = texCoord;
   s_TexCoord = specTexCoord;
   b_TexCoord = breakTexCoord;
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
in vec2 s_TexCoord;
in vec2 b_TexCoord;

uniform sampler2D u_Texture;
uniform sampler2D breakTexture;
uniform int lightingEnabled;
uniform int isLeaf;
uniform int hasSpecularTexture;
uniform int applyBreakTexture;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

layout(location = 0) out vec4 color;

void main()
{
   float textureAlpha = texture(material.diffuse, v_TexCoord).a;
   if(textureAlpha < 0.1)
      discard;

   vec4 breakColor = texture(breakTexture, b_TexCoord);
   float breakColorAlpha = breakColor.a;

   // Apply texture without lighting
   if(lightingEnabled == 0) {
      vec4 texColor = texture(u_Texture, v_TexCoord);

      if(applyBreakTexture == 1) {
         if (breakColorAlpha > 0.1f) {
            if (breakColorAlpha < 0.5f) {
               texColor.rgb = texColor.rgb * (1 - breakColorAlpha);
            } else {
               texColor = breakColor;
            }
         }
      }

      if(isLeaf == 1)
         color = vec4(0.0, texColor.g, 0.0, textureAlpha);
      else
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

      vec3 specular;
      if(hasSpecularTexture == 1) {
         specular = light.specular * spec * texture(material.specular, s_TexCoord).rgb;
      }
      else
         specular = light.specular * spec * texture(material.specular, v_TexCoord).rgb;


      vec3 result = ambient + diffuse + specular;

      if(applyBreakTexture == 1) {
         if(breakColorAlpha > 0.1f) {
            if(breakColorAlpha < 0.5f) {
               result = result * (1 - breakColorAlpha);
            } else {
               result = breakColor.rgb;
            }
         }
      }

      if(isLeaf == 1)
         color = vec4(0.0, result.g, 0.0, textureAlpha);
      else
         color = vec4(result, textureAlpha);
   }
}
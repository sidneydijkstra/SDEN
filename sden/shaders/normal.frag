#version 330 core

in vec2 fragTextureCoord;
in vec3 fragNormal;
in vec3 fragPosition;

out vec4 color;

uniform sampler2D fragTexture;

uniform vec3 fragObjectColor;
uniform vec3 fragLightColor;
uniform vec3 fragLightPosition;
uniform vec3 fragViewPosition;
uniform bool doLighting;
uniform bool doTexture;

void main()
{

    // get texture
    vec4 textureColor;
    if(doTexture){
       textureColor = texture2D(fragTexture, fragTextureCoord);
    }

    // test if there is a light in the current scene
    if(doLighting){

      // ambient
      float ambientStrength = 0.1f;
      vec3 ambient = ambientStrength * fragLightColor;

      // diffuse
      vec3 norm = normalize(fragNormal);
      vec3 lightDir = normalize(fragLightPosition - fragPosition);
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = diff * fragLightColor;

      // specular
      float specularStrength = 0.5f;
      vec3 viewDir = normalize(fragViewPosition - fragPosition);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
      vec3 specular = specularStrength * spec * fragLightColor;

      // re
      vec3 result;
      if(fragObjectColor == vec3(0.0f, 0.0f, 0.0f)){
        result = (ambient + diffuse + specular);
      }else{
        result = (ambient + diffuse + specular) * fragObjectColor;
      }

      if(doTexture){
        color = vec4(result * textureColor.rgb, textureColor.a);
      }else{
        color = vec4(result, 1.0f);
      }

    }else{
      if(doTexture){
        color = vec4(textureColor.rgb, textureColor.a);
      }else{
        color = vec4(fragObjectColor, 1.0f);
      }
    }
}

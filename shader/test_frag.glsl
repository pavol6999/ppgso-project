#version 330 core
out vec4 FragColor;

in vec3 aNormal;
in vec3 FragPos;
in vec2 texCoords;

// (optional) Texture offset
uniform vec2 TextureOffset;

uniform float Transparency;
uniform sampler2D Texture;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 CameraPosition;

void main()
{
    float specularStrength = 0.5;
    float ambientStrength = 0.1;

    vec3 ambient = ambientStrength * lightColor;
    //vec3 ambient = ambientStrength * vec3(texture(Texture, vec2(texCoords.x, 1.0 - texCoords.y)));

    vec3 norm = normalize(aNormal);
    vec3 lightDir = normalize(lightPos - FragPos);

    vec3 viewDir = normalize(CameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0),16);
    vec3 specular = specularStrength * spec * lightColor;



    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = diff *  vec3(texture(Texture, vec2(texCoords.x, 1.0 - texCoords.y)));
    vec3 diffuse =  diff * lightColor;

    //float d    = length(CameraPosition - FragPos);
    //float attenuation = 1.f / (1.f + 0.09*d + 0.032 * pow(d,2));
    vec3 result =  (ambient + diffuse + specular);
    FragColor = texture(Texture, vec2(texCoords.x, 1.0 - texCoords.y)+ TextureOffset) * vec4(result, 1.f);
    FragColor.a = Transparency;
    //FragColor = texture(Texture, vec2(texCoords.x, 1.0 - texCoords.y)+ TextureOffset) * vec4((diffuse + ambient + specular), 1.f);
}
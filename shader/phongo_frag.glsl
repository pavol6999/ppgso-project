#version 330 core

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light;
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
out vec4 FragColor;

in vec3 aNormal;
in vec3 FragPos;
in vec2 texCoords;

// (optional) Texture offset
uniform vec2 TextureOffset;

uniform float Transparency;
uniform sampler2D Texture;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 CameraPosition;

void main()
{
    //first calculate attenuation
    float distance    = length(CameraPosition - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
        		    light.quadratic * (distance * distance));




    vec3 ambient = light.ambient * material.ambient;


    vec3 norm = normalize(aNormal);
    vec3 lightDir = normalize(lightPos - FragPos);

    vec3 viewDir = normalize(CameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
    vec3 specular = light.specular * ( spec * material.specular);



    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // add attenuation
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result =  (ambient + diffuse + specular);
    FragColor = texture(Texture, vec2(texCoords.x, 1.0 - texCoords.y)+ TextureOffset) * vec4(result, 1.f);
    FragColor.a = Transparency;

}
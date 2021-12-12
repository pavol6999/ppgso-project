#version 330 core

out vec4 FragColor;
//define variables

//define our structure
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
};

struct SpotLight {
    vec3  position;
    vec3  direction;
    float cutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct PointLight {
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
};

struct SunLight {
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
#define NR_POINT_LIGHTS 4

uniform DirectionalLight dirLight;
uniform int spotlightsCount;
uniform SpotLight spotLights[5];
uniform Material material;

uniform SunLight sun;
uniform int lightsCount;
uniform PointLight pointLights[50];
in vec3 aNormal;
in vec3 FragPos;
in vec2 TexCoords;

// (optional) Texture offset
uniform vec2 TextureOffset;
uniform float SceneAge;
uniform float Transparency;
uniform sampler2D Texture;


uniform vec3 CameraPosition;



//define function prototypes

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcSunLight(SunLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

    vec3 norm = normalize(aNormal);
    vec3 viewDir = normalize(CameraPosition - FragPos);
    float dist = length(CameraPosition - FragPos);


    vec3 result = vec3(0.0);

    //calculate sun light
    result += CalcSunLight(sun, norm, FragPos, viewDir);

    // do the same for all point lights
    for(int i = 0; i < lightsCount; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // calculate spotlights in loop



    for(int j = 0; j < spotlightsCount; j++)
            result += CalcSpotLight(spotLights[j], norm, FragPos, viewDir);

    //define fog color
    vec4 fogColor = vec4(190/255.0,196/255.0,147/255.0,1);

    vec4 color = texture(Texture, vec2(TexCoords.x, 1.0 - TexCoords.y)+ TextureOffset) * vec4(result, 1.f);

    if (SceneAge > 3)
        FragColor = color + (fogColor - color) * min(dist / max((1500 - (SceneAge - 3)*120),150),1);
    else
        FragColor = color + (fogColor - color) * min(dist / 1500 ,1);


    FragColor.a = Transparency;
}

vec3 CalcSunLight(SunLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 ambient = max(light.ambient * material.ambient,0.15);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    return (ambient + diffuse + specular);
}


vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{

    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse  * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
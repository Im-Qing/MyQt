varying vec4 oColor;
varying vec2 oTextureCoords;
varying vec3 oNormal;
varying vec3 oFragPos;

uniform bool isObject;
uniform vec3 viewPos;

//材质
struct Material {
    float ambientStrength;      //环境光强度
    float diffuseStrength;      //漫反射强度
    float specularStrength;     //镜面光强度
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 color;
    vec3 direction;
    float cutOff;       //聚光半径值glm::cos(glm::radians(12.5f))
};

uniform Material material;
uniform Light light;

void main(void)
{
    gl_FragColor = oColor;

    //物体光照处理
    if(isObject)
    {
        vec3 lightDir = normalize(light.position - oFragPos);

        float theta = dot(lightDir, normalize(-light.direction));
        if(theta > light.cutOff)    // 执行光照计算
        {
            // 环境光
            vec3 ambient = texture2D(material.diffuse, oTextureCoords).rgb * material.ambientStrength;
            // 漫反射
            vec3 norm = normalize(oNormal);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * texture2D(material.diffuse, oTextureCoords).rgb * material.diffuseStrength;
            // 镜面光
            vec3 viewDir = normalize(viewPos - oFragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
            vec3 specular = spec * texture2D(material.specular, oTextureCoords).rgb * material.specularStrength;
            //叠加
            vec3 result = (ambient + diffuse + specular) * light.color;
            gl_FragColor = vec4(result, 1.0);
        }
        else  // 否则，使用环境光，让场景在聚光之外时不至于完全黑暗
        {
            gl_FragColor = vec4(material.ambientStrength * vec3(texture2D(material.diffuse, oTextureCoords)), 1.0);
        }
    }
}

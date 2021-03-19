// Normal Map shader for simple hame lighting
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

uniform vec3 Ka; // The ambient color of the model's material
uniform vec3 Kd; // The diffuse color of the model's material
uniform vec3 Ks; // The specular color of the model's material
uniform float Ns; // The specular power of the model's material

uniform vec3 AmbientColor; // Ambient color of the light
uniform vec3 LightColor; // Color of the light 
uniform vec3 LightDirection; 

const int MAX_LIGHTS = 4;
uniform int numLights;
uniform vec3 PointLightColor[MAX_LIGHTS];
uniform vec3 PointLightPosition[MAX_LIGHTS];

uniform vec3 CameraPosition; // position of the viewportcamera for the specular calculations

out vec4 FragColor;

vec3 diffuse(vec3 direction, vec3 color, vec3 normal)
{
    return color * max(0, dot(normal, -direction));
}

vec3 specular(vec3 direction, vec3 color, vec3 normal, vec3 view)
{
    vec3 R = reflect(direction, normal);

    // calculate the specular term
    float specTerm = pow(max(0, dot(R, view)), Ns);
    return specTerm * color;
}

void main()
{
    // Make sure the normal and the light directions have been normalized 
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);
    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);

 

    //N = mat3(T,B,N);

    // Calculate the diffuse lighting from sunlight
    vec3 diffuseTotal = diffuse(L, LightColor, N);

    // Calculate  the view vector and the reflection vetor
    vec3 V = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(L, N);

    //float specularTerm = pow(max(0, dot(R, V)), 10);

    // determine the specular total
    vec3 specularTotal = specular(L, LightColor, N, V);

    for (int i = 0; i < numLights; i++)
    {
        vec3 direction = vPosition.xyz - PointLightPosition[i];
        float distance = length(direction);
        direction = direction / distance;

        // Get the light intensity with the inverse square law
        vec3 color = PointLightColor[i] / (distance * distance);

        diffuseTotal += diffuse(direction, color, N);
        specularTotal += specular(direction, color, N, V);
    }

    // Determine the value of the ambient 
    vec3 ambient = AmbientColor * Ka;
    // Determine the value of the diffuse 
    vec3 diffuse = Kd * diffuseTotal; 
    // Dteremine the value of the specular
    vec3 specular = Ks * specularTotal;

    // Output of the final color
    FragColor = vec4(ambient + diffuse + specular, 1);
}
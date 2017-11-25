#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Lighting.glsl"
#include "Fog.glsl"

varying vec3 vNormal;
varying vec3 centralBodyLightDir;

uniform vec3 cBodyColor;
uniform vec3 cBodyCenter;
uniform vec3 cCentralBodyCenter;

void VS()
{
    mat4 modelMatrix = iModelMatrix;
	//TEMPORARY FIX
	modelMatrix[0][0] *= -1;
	modelMatrix[0][1] *= -1;
	modelMatrix[0][2] *= -1;
	modelMatrix[1][0] *= -1;
	modelMatrix[1][1] *= -1;
	modelMatrix[1][2] *= -1;
	modelMatrix[2][0] *= -1;
	modelMatrix[2][1] *= -1;
	modelMatrix[2][2] *= -1;
	modelMatrix[3][0] *= -1;
	modelMatrix[3][1] *= -1;
	modelMatrix[3][2] *= -1;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vNormal = GetWorldNormal(modelMatrix);

    centralBodyLightDir = normalize(cBodyCenter - cCentralBodyCenter);
}

void PS()
{
		//-1 is related to the temporary fix
		float multiplier = max(0, dot(-1*vNormal, centralBodyLightDir));
		vec3 trueColor = multiplier*cBodyColor;
        gl_FragColor = vec4(trueColor, 255);
}

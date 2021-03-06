//uniform vec4 objSpaceScale;
//uniform vec4 eyeSpaceScale;
//uniform vec4 clipSpaceScale;
uniform float var1;
uniform float var2;
uniform float var3;
uniform float var4;

vec4 calcLight() {
	vec3 normal, lightDir;
	vec4 diffuse;

	float NdotL;

	/* first transform the normal into eye space and normalize the result */
	normal = normalize(gl_NormalMatrix * gl_Normal);
	/* now normalize the light's direction. Note that according to the
	OpenGL specification, the light is stored in eye space. Also since
	we're talking about a directional light, the position field is actually
	direction */

	lightDir = normalize(vec3(gl_LightSource[0].position));

	/* compute the cos of the angle between the normal and lights direction.
	The light is directional so the direction is constant for every vertex.
	Since these two are normalized the cosine is the dot product. We also
	need to clamp the result to the [0,1] range. */

	NdotL = max(dot(normal, lightDir), 0.0);

	return vec4(NdotL * gl_LightSource[0].diffuse.rgb,1.);
}

float weird(float t) {
	return cos(sin(cos(t)*2.+0.5)-0.5);
}

vec4 tentacle(float amount, float freq, float offset,  vec4 v)
{	vec4 oldV = v;
	offset=offset*0.05;
	v.x*=sin(oldV.y*freq+offset*0.07);
	v.z*=weird(v.x*freq+offset*0.07);
	v.y*=weird(v.z*freq+offset*0.07);
	v.x*=weird(v.y*freq+offset*0.07);
	v.x*=sin(v.y*freq+offset*0.1);
	v.z*=weird(v.x*freq+offset*0.07);
	v.y*=weird(v.z*freq+offset*0.07);
	v.x*=weird(v.y*freq+offset*0.07);
	v.y*=weird(v.z*freq*0.5+offset*0.04);
	return mix(oldV, v,amount);
}

void main () {
	vec4 light = calcLight();
	float lightAmount=length(light.rgb);
	
	gl_FrontColor =  light * gl_Color;

	vec4 objSpace = tentacle(var1,var2,var3,gl_Vertex);
	//objSpace *= objSpaceScale;
	objSpace.z+=sin(lightAmount*3.14)*var4;

	vec4 eyeSpace = gl_ModelViewMatrix*objSpace;
	//eyeSpace *= eyeSpaceScale;
    
	vec4 clipSpace = gl_ProjectionMatrix*eyeSpace;
	//clipSpace *= clipSpaceScale;


	gl_Position = clipSpace;
	
}

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

void main () {
	



	vec4 light = calcLight();
	float lightAmount=length(light.rgb);
	
	gl_FrontColor =  light * gl_Color;

	vec4 objSpace = gl_Vertex;
	objSpace *= objSpaceScale;
	objSpace.x+=var1 * sin(var3+objSpace.y*var2);
	objSpace.z+=lightAmount*var4;

	vec4 eyeSpace = gl_ModelViewMatrix*objSpace;
	eyeSpace *= eyeSpaceScale;
	vec4 clipSpace = gl_ProjectionMatrix*eyeSpace;
	clipSpace *= clipSpaceScale;


	gl_Position = clipSpace;
	
}
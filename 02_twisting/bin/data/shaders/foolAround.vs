//uniform vec4 objSpaceScale;
//uniform vec4 eyeSpaceScale;
//uniform vec4 clipSpaceScale;
uniform float var1;
uniform float var2;
uniform float var3;

void main () {
	// in the vertex shader, gl_Color is the color value as set per vertex (see patch)

	// in the fragment shader,'gl_Color' will obtain the value of the vertex shader 'gl_FrontColor' variable
	// if it deals with a front-facing primitive
	// otherwise: 'gl_Color' in the fragment shader will obtain the value of 'gl_BackColor' in the vertex shader
	gl_FrontColor = gl_Color;
	
	// this command performs the standard transformations, so the 'object coordinates' of this shape will be transformed
	// into 'clip space' coordinates.
	
	// it basically does the same as: gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

	vec4 objSpace = gl_Vertex;
	//objSpace *= objSpaceScale;
	objSpace.x+= var1 * sin(objSpace.y * var2 );

	vec4 eyeSpace = gl_ModelViewMatrix*objSpace;
	//eyeSpace *= eyeSpaceScale;
	vec4 clipSpace = gl_ProjectionMatrix*eyeSpace;
	//clipSpace *= clipSpaceScale;


	gl_Position = clipSpace;
	
}
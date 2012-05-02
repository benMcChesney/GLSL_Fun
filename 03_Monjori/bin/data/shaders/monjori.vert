


#ifdef GL_ES
precision highp float;
#endif

uniform vec2 resolution;
uniform float time;

uniform float time_factor ; 
uniform float e_factor ; 
uniform float f_factor ; 
uniform float i_factor ; 
uniform float d_factor ; 

uniform vec4 ambient_color ; 

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
	objSpace.x += time * tan(objSpace.y );
	vec4 eyeSpace = gl_ModelViewMatrix*objSpace;
	vec4 clipSpace = gl_ProjectionMatrix*eyeSpace;


	gl_Position = clipSpace;
	
}
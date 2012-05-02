uniform float var1, var2, var3;
uniform float fVar1, fVar2, fVar3;
varying vec4 vPos;

vec4 moduloStripes(vec4 color, float dist) {
	vec4 fc = vPos;	
	float mult=mod(var3+(fc.x*10.)*dist,1.);
	
	// mult=ceil(mult-0.5);  // this is for rounding to 0 or 1
	// mult=1.-mult; 		  // for reversing black and white
	
	return color*mult;
}
vec4 sineStripes(vec4 color, float freq) {
	vec4 fc = gl_FragCoord;
	float mult=sin(fc.x*3.14*freq);
	// now mult goes from -1 to 1, but i want it to go from 0 to 1.
	mult = mult + 1.;
	// now mult goes from 0 to 2
	mult = mult * 0.5;
	// now mult goes from 0 to 1
	return color*mult;
}


void main() {
	vec4 c = gl_Color;
	c = moduloStripes(c,fVar1);
	c = sineStripes(c,fVar2);
	// every fragment shader HAS to write gl_FragColor
	gl_FragColor   	=mix(gl_Color,c,fVar3);
}
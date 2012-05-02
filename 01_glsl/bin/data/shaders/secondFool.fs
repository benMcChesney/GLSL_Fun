uniform float var1;
uniform float var2;
uniform float var3;

void main() {
	// a fragment shader HAS to write gl_FragColor -> this determines the pixel color
	// gl_Color is a value that is set by OpenGL commands, to specifiy the object color
	gl_FragColor = gl_Color; // so this command says that the pixel should have the same color as specified by 
}
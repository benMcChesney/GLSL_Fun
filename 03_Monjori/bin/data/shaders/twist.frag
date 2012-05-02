

uniform vec4 time ; 

uniform float var2;
uniform float var3;
uniform float var4;

uniform vec4 ambientColor ;  

void main() {
	// a fragment shader HAS to write gl_FragColor -> this determines the pixel color
	// gl_Color is a value that is set by OpenGL commands, to specifiy the object color
    //add our ambient light to the gl_Color ; 
    //vec4 composite_color = ambientColor + gl_Color ; 
	//gl_FragColor = composite_color ; // so this command says that the pixel should have the same color as specified by 
    
}
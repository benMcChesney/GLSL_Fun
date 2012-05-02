#version 120

uniform float time;
//uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {
    
	vec2 position = ( gl_FragCoord.xy / resolution.xy ) + mouse / 4.0;
    
	float color = 0.0;
	color += sin( position.x * cos( time / 15.0 ) * 80.0 ) + cos( position.y * cos( time / 15.0 ) * 10.0 );
	color += sin( position.y * sin( time / 10.0 ) * 40.0 ) + cos( position.x * sin( time / 25.0 ) * 40.0 );
	color += sin( position.x * sin( time / 5.0 ) * 10.0 ) + sin( position.y * sin( time / 35.0 ) * 80.0 );
	color *= sin( time / 10.0 ) * 0.5;
    
	gl_FragColor = vec4( vec3( color, color * 0.5, sin( color + time / 2.0 ) * 0.75 ), 2.0 );
    
}

/*
void main(){
	//this is the fragment shader
	//this is where the pixel level drawing happens
	//gl_FragCoord gives us the x and y of the current pixel its drawing
	
	//we grab the x and y and store them in an int
	int xVal = int(gl_FragCoord.x);
	int yVal = int(gl_FragCoord.y);
	
	//we use the mod function to only draw pixels if they are every 2 in x or every 4 in y
	if( mod(xVal, 2) == 0 && mod(yVal, 4) == 0 ){
		gl_FragColor = gl_Color;    
    }
	
}*/
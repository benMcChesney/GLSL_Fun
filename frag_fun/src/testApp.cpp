#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(34, 34, 34);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();
		
	//we load a font and tell OF to make outlines so we can draw it as GL shapes rather than textures
	font.loadFont("type/verdana.ttf", 100, true, false, true, 0.4, 72);
	shader.load("shaders/fragFun.vert", "shaders/tunnel.frag");
	
	doShader = true;	
    
    image1.loadImage( "shaders/text2.jpg" ) ; 
    fbo1.allocate( image1.width , image1.height ) ; 
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(225);
	ofDrawBitmapString("'s' toggles shader", 10, 20);
    
    fbo1.begin( ) ; 
    image1.draw ( 0 , 0 ) ; 
    fbo1.end( ) ; 
    
    ofTexture tex1 = fbo1.getTextureReference();

    ofSetFrameRate( 60 ) ; 
    ofSetVerticalSync( true ) ; 
    
	ofSetColor(245, 58, 135);
	ofFill();
	
	if( doShader ){
		shader.begin();
			//we want to pass in some varrying values to animate our type / color 
			//shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
			//shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
			
			//we also pass in the mouse position 
			//we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped. 
        
        // so here is the trick, important one: 
        // tex1 is the texture from fbo1. 
        // we assign this to texture 0 , i.e. "textBase" in the shader. 
        // this is as drawing into the fbo  image1. (from shader point of view) 
        // so instead of making : 
        // fbo2.draw(0,0) after shader parameters we make this line:  
        shader.setUniformTexture("texBase",   tex1, 0 ); //look that is number 0: and 
        // textures 0 are the ones used do "draw". 
        // so we could do this making fbo1.draw.
        

        
        ofMap( mouseX , 0.0f , ofGetWidth() , 0.0f , 1.0f ) ;   
			//shader.setUniform2f("mouse", ofMap( mouseX , 0.0f , ofGetWidth() , 0.0f , 1.0f ) , 
            //                             ofMap( mouseY , 0.0f , ofGetHeight() , 0.0f , 1.0f ) );
            shader.setUniform1f("time", ofGetElapsedTimef() );
            shader.setUniform2f("resolution", ofGetWidth() , ofGetHeight() ) ; 

	}
	
		//finally draw our text
		//font.drawStringAsShapes("openFrameworks", 90, 260);
    ofSetColor( 255 , 255 , 255 ) ; 
    ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
	
	if( doShader ){
		shader.end();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if( key == 's' ){
		doShader = !doShader;
	}	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(34, 34, 34);
	ofEnableAlphaBlending();
		
	//we load a font and tell OF to make outlines so we can draw it as GL shapes rather than textures
	//font.loadFont("type/verdana.ttf", 100, true, false, true, 0.4, 72);
//	shader.load("shaders/noise.vert", "shaders/noise.frag");

    shader.load("shaders/foolAround_frag.vs", "shaders/foolAround_frag.frag");
    
	doShader = true;	
    
    cam.enableMouseInput() ; 
    cam.setDistance( 250.0f ) ; 
    
    fbo.allocate( ofGetWidth() , ofGetHeight() , GL_RGBA ) ; 
    fbo.begin() ; 
        ofClear( 0 , 0 , 0 , 1.0f ) ; 
    fbo.end() ; 
    
    glEnable( GL_DEPTH_TEST ) ; 
    
    ofSetFrameRate( 60 ) ; 
    ofSetVerticalSync( true ) ; 
    
    
	float dim = 24; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
    
    drawPadding = false; 
    
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    
    gui->addWidgetDown(new ofxUILabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE));         
    gui->addWidgetDown( new ofxUISlider(160,dim, 0.0, 10.0f, var2, "var2")); 
    gui->addWidgetDown(new ofxUISlider(160,dim, 0.0, 255.0, var3, "var3")); 
    gui->addWidgetDown(new ofxUISlider(160,dim, 0.0, 255.0, var4, "var4")); 
    
    gui->addWidgetDown( new ofxUISlider(160,dim, -ofGetWidth(), ofGetWidth() , translate.x, "x")); 
    gui->addWidgetDown( new ofxUISlider(160,dim, -ofGetHeight() , ofGetHeight() , translate.y, "y")); 
    gui->addWidgetDown( new ofxUISlider(160,dim, -2000 , 2000 , translate.z, "z")); 

    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
	
    float var2 , var3 , var4 ; 
    gui->loadSettings("uisettings.xml" ) ; 
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
    if ( name == "var2" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        var2 = slider->getScaledValue(); 
    }
    
    if ( name == "var3" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        var3 = slider->getScaledValue(); 
    }
    
    if ( name == "var4" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        var4 = slider->getScaledValue(); 
    }
    
    if ( name == "x" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        translate.x = slider->getScaledValue(); 
    }
    
    if ( name == "y" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        translate.y = slider->getScaledValue(); 
    }
    
    if ( name == "z" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        translate.z = slider->getScaledValue(); 
    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    glEnable( GL_DEPTH_TEST ) ; 
    
	ofSetColor(225);
	ofDrawBitmapString("'s' toggles shader", 10, 20);

	ofSetColor(245, 58, 135);
	ofFill();
	
    
    //fbo.begin() ; 
        ofEnableAlphaBlending() ;
   // glDisable(GL_DEPTH_TEST) ; 
        ofSetColor( 0 , 0 , 0, 12 ) ; 
    //    ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;
    //glEnable( GL_DEPTH_TEST ) ; 
    ofSetColor( 255 , 255 , 255 ) ;
    cam.begin() ; 
	if( doShader ){
		shader.begin();
        
			//we want to pass in some varrying values to animate our type / color 
			//shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
			//shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
			
        float var1 = 4.3f ; 
            //float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {
            float range = 25.0f ; 
            shader.setUniform1f("var1", var2 ) ;
            shader.setUniform1f("var2", ofGetElapsedTimef() ) ;
            shader.setUniform1f("var3", var3 );
            shader.setUniform1f("var4", var4);
			//we also pass in the mouse position 
			//we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped. 
			//shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
    
   		//finally draw our text
        //font.drawStringAsShapes("openFrameworks", 90, 260);
    }
    
    ofPoint offset = ofPoint( 65.0f , 0.0f , 0.0f ) ;

    
    ofSetColor( 255 , 0 , 0 ) ;
    
    float triangleSize = 35.0f ; 
    float triSize = 35.0f ; 
    
    ofColor col1 = ofColor ( 255 , 0  , 255 ) ; 
    ofColor col2 = ofColor( 0 , 0  , 255 ) ; 
    
    float numSpheres = 6.0f ; 
    ofTranslate( translate.x + ( offset.x * numSpheres ) * -.5f , translate.y  , translate.z ) ; 
    for ( int i = 0 ; i < numSpheres ; i++ ) 
    {
        ofPushMatrix() ; 
        float ratio = (float)i / numSpheres ;  
        ofSetColor( col1.lerp( col2 , ratio ) ) ; 
        
            ofTranslate( offset * (float)i ) ; 
    //        ofTranslate( offset ) ; 
            // ofSphere( 0 , 0 , 0 , 30 ) ; 
         ofScale ( 1  ,1 ,  sin( ofGetElapsedTimef() )  ) ; 
        for ( int p = 0 ; p < 10 ; p ++ ) 
        {
            ofSphere( 0 ,p * -55, 0, 25 ) ; 
        }
        //    ofSetColor( 255 , 0 , 0 ) ;
          //  ofSphere( 0 , 0 , 0 , 25 ) ; //ofNoise( ofGetElapsedTimef() + (float)i * 2.0f ) * 55.0f ); 
/*
        float range = 25 ; 
        for( int l = 0 ; l < 25.0f ; l++ ) 
        {
            ofTriangle( ofRandom( -range, range )  , ofRandom( -range, range )  , ofRandom( -range, range )  , ofRandom( -range, range ) ,  ofRandom( -range, range )  , ofRandom( -range, range )   ) ;
        }
 */
          //  ofSetColor( 0 , 255 , 0 ) ;
           // ofRotateZ( ofGetElapsedTimef() * (float)i ) ; 
           
         //   ofSphere( 0 , 55 , 0 , 25 ) ; // ofNoise( ofGetElapsedTimef() + (float)i * 6.0f ) * 55.0f ) ;  
         // ofSphere( 0 , 150 , 0 , 25 ) ;
        ofPopMatrix() ; 

    }
    
  //  glDisable( GL_DEPTH_TEST ) ; 
    cam.end( ) ;
	if( doShader ){
        shader.end();
	}
  //  glDisable( GL_DEPTH_TEST ) ; 
//    fbo.end() ; 
    
//    glEnable(GL_DEPTH_TEST) ; 
    ofSetColor( 255 , 255 , 255 ) ;
  //  fbo.draw( 0 , 0 ) ; 

    
     gui->saveSettings("uisettings.xml" ) ; 
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


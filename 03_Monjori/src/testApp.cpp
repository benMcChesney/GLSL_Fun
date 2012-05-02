#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(34, 34, 34);
	ofEnableAlphaBlending();
		
    Tweenzor::init() ;
	//we load a font and tell OF to make outlines so we can draw it as GL shapes rather than textures
	//font.loadFont("type/verdana.ttf", 100, true, false, true, 0.4, 72);
//	shader.load("shaders/noise.vert", "shaders/noise.frag");

    shader.load("shaders/monjori.vert", "shaders/monjori.frag" ) ; 
    
	doShader = true;	
    
    cam.disableMouseInput() ; 
    cam.setDistance( 250.0f ) ; 
    
    fbo.allocate( ofGetWidth() , ofGetHeight() , GL_RGBA ) ; 
    fbo.begin() ; 
        ofClear( 0 , 0 , 0 , 1.0f ) ; 
    fbo.end() ; 
    
    glEnable( GL_DEPTH_TEST ) ; 
    
    ofSetFrameRate( 60 ) ; 
    ofSetVerticalSync( true ) ; 
    
    

     timeFactor = 40.0f ; 
     e_factor  = 400.0f ; 
     f_factor  = 400.0f ; 
     i_factor  = 200.0f ; 
     d_factor  = 200.0f ; 
    
    
	float dim = 24; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
    
    drawPadding = false; 
    
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    
    gui->addWidgetDown(new ofxUILabel("Shader Vars", OFX_UI_FONT_LARGE));  
    gui->addWidgetDown( new ofxUISlider( 160 , dim , 50.0f, 950.0f, e_factor  , "E")); 
    gui->addWidgetDown( new ofxUISlider(160,dim , 50.0f, 3050.0f, f_factor  , "F")); 
    gui->addWidgetDown( new ofxUISlider(160,dim , 50.0f, 3050.0f, i_factor  , "I")); 
    gui->addWidgetDown( new ofxUISlider(160,dim , 50.0f, 3050.0f, d_factor  , "D")); 
    gui->addWidgetDown( new ofxUISlider(160,dim , 1.0f , 3000.0f, timeFactor  , "Time")); 
    gui->addWidgetDown( new ofxUISlider(160,dim , 1000.0f , 12000.0f, volumeScale  , "VolumeScale")); 
    
    /*
    gui->addWidgetDown( new ofxUISlider(160,dim, 0.0, 10.0f, var2, "var2")); 
    gui->addWidgetDown(new ofxUISlider(160,dim, 0.0, 255.0, var3, "var3")); 
    gui->addWidgetDown(new ofxUISlider(160,dim, 0.0, 255.0, var4, "var4")); 
    
    gui->addWidgetDown( new ofxUISlider(160,dim, -ofGetWidth(), ofGetWidth() , translate.x, "x")); 
    gui->addWidgetDown( new ofxUISlider(160,dim, -ofGetHeight() , ofGetHeight() , translate.y, "y")); 
    gui->addWidgetDown( new ofxUISlider(160,dim, -2000 , 2000 , translate.z, "z")); 
    */
    gui->addWidgetDown( new ofxUILabel("AMBIENT COLOR", OFX_UI_FONT_LARGE )) ; 
    gui->addWidgetDown( new ofxUISlider(dim,50, -1.0f , 1.0f , ambientColor.x, "R")); 
    gui->addWidgetRight( new ofxUISlider(dim,50, -1.0f , 1.0f , ambientColor.y, "G")); 
    gui->addWidgetRight( new ofxUISlider(dim,50, -1.0f , 1.0f , ambientColor.z, "B")); 
    gui->addWidgetRight( new ofxUISlider(dim,50, -1.0f , 1.0f , ambientColor.w, "A")); 
    
    

    gui->addWidget( new ofxUIToggle(dim, 50, 50 , 50 , state1 , "state1" )) ; 
    gui->addWidget( new ofxUIToggle(dim, 50, 50 , 50 , state2 , "state2" )) ; 
    gui->addWidget( new ofxUIToggle(dim, 50, 50 , 50 , state3 , "state3" )) ; 
    gui->addWidget( new ofxUIToggle(dim, 50, 50 , 50 , state4 , "state4" )) ; 
    
    /*
     timeFactor = 40.0f ; 
     e_factor  = 400.0f ; 
     f_factor  = 400.0f ; 
     i_factor  = 200.0f ; 
     d_factor  = 200.0f ; 
     */
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
	
    float var2 , var3 , var4 ; 
    gui->loadSettings("uisettings.xml" ) ; 
    
    //ofVec3f lightDir ; 
    //ofVec4f ambientColor ; 
    
    soundStream.listDevices();
	
	//if you want to set a different device id 
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 256;
	
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

    state1 = false ;
    state2 = false ;  
    state3 = false ; 
    state4 = false ; 
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
    
    if ( name == "R" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        ambientColor.x = slider->getScaledValue(); 
    }
    
    if ( name == "G" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        ambientColor.y = slider->getScaledValue(); 
    }
    
    if ( name == "B" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        ambientColor.z = slider->getScaledValue(); 
    }
    
    if ( name == "A" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        ambientColor.w = slider->getScaledValue(); 
    }
    
    if ( name == "E" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        e_factor = slider->getScaledValue(); 
    }
    
    if ( name == "F" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        f_factor= slider->getScaledValue(); 
    }

    
    if ( name == "I" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        i_factor= slider->getScaledValue(); 
    }

    
    if ( name == "D" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        d_factor= slider->getScaledValue(); 
    }
    
    if ( name == "Time" )
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        timeFactor = slider->getScaledValue() ; 
    }
    
    if ( name =="VolumeScale" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        volumeScale = slider->getScaledValue() ; 
    }
    
    if ( name == "state1" ) 
    {
        ofxUIToggle *toggle = (ofxUIToggle * ) e.widget ; 
        state1 = toggle->getValue() ; 
    }
    
    if ( name == "state2" ) 
    {
        ofxUIToggle *toggle = (ofxUIToggle * ) e.widget ; 
        state2 = toggle->getValue() ; 
    }
    
    if ( name == "state3" ) 
    {
        ofxUIToggle *toggle = (ofxUIToggle * ) e.widget ; 
        state3 = toggle->getValue() ; 
    }
    
    if ( name == "state4" ) 
    {
        ofxUIToggle *toggle = (ofxUIToggle * ) e.widget ; 
        state4 = toggle->getValue() ; 
    }
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    Tweenzor::update( ofGetElapsedTimeMillis() ) ;
	//lets scale the vol up to a 0-1 range 
	
    Tweenzor::add( &scaledVol , scaledVol , ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true ) , 0.0f , 0.02f , EASE_LINEAR ) ; 
    //scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true );
    
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
    
    ofSetWindowTitle( "FPS: " + ofToString( ofGetFrameRate() ) ) ; 
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
            shader.setUniform1f("time", ofGetElapsedTimef() ) ;
            shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight()  ) ; 
        
        shader.setUniform1f("time_factor", timeFactor ) ; 
        
        float offset =  scaledVol * volumeScale ; 
        
        shader.setUniform1f("e_factor", e_factor + offset ) ; 
        shader.setUniform1f("f_factor", f_factor + offset ) ; 
        shader.setUniform1f("i_factor", i_factor + offset / 2 ) ; 
        shader.setUniform1f("d_factor", d_factor + offset / 2 ) ; 
        
        shader.setUniform4f("ambient_color", ambientColor.x , ambientColor.y , ambientColor.z , ambientColor.w ) ; 
        
        /*
        shader.setUniform1i("state1", state1 ) ; 
        shader.setUniform1i("state2", state2 ) ; 
        shader.setUniform1i("state3", state3 ) ; 
        shader.setUniform1i("state4", state4 ) ; 
         */
        /*
         uniform vec2 resolution;
         uniform float time;*
            shader.setUniform1f("var2", var2 ) ;
            shader.setUniform1f("var3", var3 );
            shader.setUniform1f("var4", var4 );
            shader.setUniform4f("ambientColor", ambientColor.x , ambientColor.y , ambientColor.z , ambientColor.w ) ; 
           // shader.setUniform3f("lightDir", 0.1f , 0.2f, -4.5f ) ; 
			//we also pass in the mouse position 
			//we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped. 
			//shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
    */
   		//finally draw our text
        //font.drawStringAsShapes("openFrameworks", 90, 260);
    }
    /*
    
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
        
        for ( int p = 0 ; p < 10 ; p ++ ) 
        {
            ofSphere( 0 ,p * -55, 0, 25 ) ; 
        }
        ofPopMatrix() ; 

    }
    */
    ofSetColor( 255 , 255 , 255 ) ; 
    ofRect( ofGetWidth()/-2 , ofGetHeight()/-2  , ofGetWidth() , ofGetHeight() ) ; 
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

    //ofSetColor( 255 , 0 , 0 ) ; 
    //ofCircle( 0 , 0, scaledVol * 400.0f ) ; 
     gui->saveSettings("uisettings.xml" ) ; 
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if( key == 's' ){
		doShader = !doShader;
	}	
    
    if( key == 'b' ){
		soundStream.start();
	}
	
	if( key == 'f' ){
		soundStream.stop();
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


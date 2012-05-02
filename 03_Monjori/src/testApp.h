#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxTweenzor.h"

class testApp : public ofBaseApp{
	
	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofTrueTypeFont font;
		ofShader shader;
		bool doShader;
    
        ofEasyCam cam ; 
    
        ofFbo fbo ; 
    
    
    
     ofxUICanvas *gui;   	
     void guiEvent(ofxUIEventArgs &e);
     bool drawPadding; 
     float var2 , var3 , var4 ; 
    
     ofVec3f translate ; 
    
    /*
     
     uniform float timeMultiplier ; 
     uniform float e ; 
     uniform float f ; 
     uniform float i ; 
     uniform float d ; 
     */
    
    float volumeScale ; 
    float timeFactor ; 
    //Shader variables
    float e_factor , f_factor  , i_factor  , d_factor  ; 
    //Lighting
    ofVec3f lightDir ; 
    ofVec4f ambientColor ; 
    
    //Sound input
    void audioIn(float * input, int bufferSize, int nChannels); 
	
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    
    bool state1 , state2 , state3 , state4 ; 
};


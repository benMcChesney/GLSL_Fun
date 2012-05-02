#pragma once

#include "ofMain.h"
#include "ofxUI.h"

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
    
    //Lighting
    ofVec3f lightDir ; 
    ofVec4f ambientColor ; 
};


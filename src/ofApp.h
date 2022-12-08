#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofVideoGrabber vidGrabber;
		ofPixels videoInverted;
		ofTexture videoTexture;
		int camWidth;
		int camHeight;

		int objectCenterX;
		int objectCenterY;
		int binaryPixelCounter;

		int centerX;
		int centerY;

		int middleOfX;

		ofxCvColorImage colorImg;
		ofxCvColorImage hsvImg;

		ofImage original;
		ofImage originalHSV;
		ofImage keyed;
};

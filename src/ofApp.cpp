#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//Setup VideoGrabber
	camWidth = 640;  // try to grab at this size.
	camHeight = 480;

	//get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	

	for (size_t i = 0; i < devices.size(); i++)
	{
		if (devices[i].bAvailable)
		{
			//log the device
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		}
		else
		{
			//log the device and note it as unavailable
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(camWidth, camHeight);
}

//--------------------------------------------------------------
void ofApp::update(){
	//get Pixels from vidGrabber Output
	ofPixelsRef pixelsGreen = vidGrabber.getPixels();
	ofPixelsRef pixelsRed = vidGrabber.getPixels();


	objectCenterX = 0;
	objectCenterY = 0;

	binaryPixelCounter = 0;

	centerX = 0;
	centerY = 0;

	objectCenterXGreen = 0;
	objectCenterYGreen = 0;
	binaryPixelCounterGreen = 0;

	centerXGreen = 0;
	centerYGreen =0;

	ofPixelsRef redPixels = trackRedPixels(pixelsRed);
	ofPixelsRef greenPixels = trackGreenPixels(pixelsGreen);

	

	//get center coordinates for greatest mass of red
	if (objectCenterX > 0)
		centerX = objectCenterX / binaryPixelCounter;

	if (objectCenterY > 0)
		centerY = objectCenterY / binaryPixelCounter;

	cout << "X: " << centerX << " Y: " << centerY << endl;

	
	
	//draw small crosshair, original pixel is in the middle
	for (size_t i = 0; i < 10; i++) {
		redPixels.setColor(centerX + i, centerY, ofColor::green);
		redPixels.setColor(centerX - i, centerY, ofColor::green);
		redPixels.setColor(centerX, centerY + i, ofColor::green);
		redPixels.setColor(centerX, centerY - i, ofColor::green);
	}
	//draw small crosshair for green, original pixel is in the middle
	for (size_t ii = 0; ii < 10; ii++) {
		greenPixels.setColor(centerXGreen + ii, centerYGreen, ofColor::green);
		greenPixels.setColor(centerXGreen - ii, centerYGreen, ofColor::green);
		greenPixels.setColor(centerXGreen, centerYGreen + ii, ofColor::green);
		greenPixels.setColor(centerXGreen, centerYGreen - ii, ofColor::green);
	}

	//sets whats left as keyed image
	keyed.setFromPixels(redPixels);

	ofBackground(100, 100, 100);
	vidGrabber.update();
	keyed.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(20, 20);
	keyed.draw(vidGrabber.getWidth(), 20);

}


	


ofPixelsRef ofApp::trackRedPixels(ofPixelsRef pixels) {
	for (int y = 0; y < vidGrabber.getHeight(); y++) {
		for (int x = 0; x < vidGrabber.getWidth(); x++)
		{
			//get Color from Frame and convert to HUE
			ofColor color = pixels.getColor(x, y);
			float hueAngle = color.getHueAngle();
			float hueSaturation = color.getSaturation();

			//delete everything but highly saturated red pixels

			if (((340 <= hueAngle) || (hueAngle <= 14)) && (hueSaturation >= 200))
			{
				pixels.setColor(x, y, ofColor::darkRed);
				objectCenterX += x;
				objectCenterY += y;
				binaryPixelCounter++;
				cout << "Weißer Pixel" << endl;
			}
			else {
				pixels.setColor(x, y, ofColor::black);
			}
		}
	}
	return pixels;
}

ofPixelsRef ofApp::trackGreenPixels(ofPixelsRef pixels) {
	for (int y = 0; y < vidGrabber.getHeight(); y++) {
		for (int x = 0; x < vidGrabber.getWidth(); x++)
		{
			//get Color from Frame and convert to HUE
			ofColor color = pixels.getColor(x, y);
			float hueAngle = color.getHueAngle();
			float hueSaturation = color.getSaturation();

			//delete everything but highly saturated red pixels

			if (((160 <= hueAngle) || (hueAngle <= 110)) && (hueSaturation >= 200))
			{
				pixels.setColor(x, y, ofColor::forestGreen);
				objectCenterXGreen += x;
				objectCenterYGreen += y;
				binaryPixelCounterGreen++;
			}
			else {
				pixels.setColor(x, y, ofColor::black);
			}
		}
	}
	return pixels;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	vector<glm::vec3> noise_locations;
	for (int i = 0; i < 6; i++) {

		noise_locations.push_back(glm::vec3(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -800, 800), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -800, 800), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -800, 800)));
	}

	int span = 72;
	for (int x = ofGetWidth() * -0.5; x <= ofGetWidth() * 0.5; x += span) {

		for (int y = ofGetHeight() * -0.5; y <= ofGetHeight() * 0.5; y += span) {

			for (int z = -360; z <= 360; z += span) {

				auto location = glm::vec3(x, y, z);
				auto draw_flag = true;
				for (auto& noise_location : noise_locations) {

					if (glm::distance(location, noise_location) < 250) {

						draw_flag = false;
						break;
					}
				}

				if (draw_flag) {

					ofFill();
					ofSetColor(39);
					ofDrawBox(location, span * 0.85);

					ofNoFill();
					ofSetColor(239);
					ofDrawBox(location, span * 0.86);
				}
			}
		}
	}

	ofFill();
	ofSetColor(39);
	for (auto& noise_location : noise_locations) {

		ofDrawSphere(noise_location, 50);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
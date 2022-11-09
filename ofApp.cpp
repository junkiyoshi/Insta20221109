#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(0.5);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 4);
	this->base_mesh = ico_sphere.getMesh();
	this->draw_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->draw_mesh.clear();

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int k = 0; k < 1; k++) {

		for (auto v : this->base_mesh.getVertices()) {

			for (int i = 0; i < 16; i++) {

				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0025, noise_seed.x + ofGetFrameNum() * 0.015)), 0, 1, -15, 15) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0025, noise_seed.y + ofGetFrameNum() * 0.015)), 0, 1, -15, 15) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0025, noise_seed.z + ofGetFrameNum() * 0.015)), 0, 1, -15, 15) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

				v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;

				this->draw_mesh.addVertex(v);
				this->draw_mesh.addColor(ofColor(255));

				if (i > 0) {

					this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 1);
					this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 2);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.6666666666666666);

	this->draw_mesh.draw();
	
	ofSetColor(0);
	ofDrawSphere(245);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
/*
 * headTracking.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: dantheman
 */

#include "headTracking.h"

headTracking::headTracking() {
	mTmpHeadView.set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	mEkfToHeadTracker.set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	ofQuaternion rotation = ofQuaternion(90, 1, 0, 0);
	mEkfToHeadTracker.setRotate(rotation);
}

headTracking::~headTracking() {

}

void headTracking::setup() {
	ofxAccelerometer.setup();
	ofxRegisterAccelEvents(this);
	ofLog() << "headTracking setup" << endl;
}

ofMatrix4x4 headTracking::getLastHeadView(ofMatrix4x4  headView) {
//	ofLog() << "headTracking getLastHeadView" << endl;
	float secondsSinceLastGyroEvent = (ofGetElapsedTimeMicros()
			- mLastGyroEventTimeNanos) * 0.0000000001;

	float secondsToPredictForward = secondsSinceLastGyroEvent
			+ 0.03333333333333333;
	ofMatrix4x4 mat = mTracker.getPredictedGLMatrix(secondsToPredictForward);
	for (int i = 0; i < 16; i++) {
		mTmpHeadView.getPtr()[i] = ((float) mat.getPtr()[i]);
	}

	mEkfToHeadTracker = headView * mTmpHeadView;
	return mEkfToHeadTracker;
}

void headTracking::accelerationChanged(SensorEvent & event) {
	processSensorEvent(event);
}

void headTracking::gyroChanged(SensorEvent & event) {
	processSensorEvent(event);
}

void headTracking::processSensorEvent(SensorEvent event) {
	long timeNanos = ofGetElapsedTimeMicros();
	ofLog() << "headTracking processSensorEvent" << endl;
	mTmpRotatedEvent.x = (-event.reading.y);
	mTmpRotatedEvent.y = event.reading.x;
	mTmpRotatedEvent.z = event.reading.z;

	if (event.type == ACCEL) {
		mTracker.processAcc(event.reading, event.timestamp);
	} else if (event.type == GYRO) {
		mLastGyroEventTimeNanos = timeNanos;
		mTracker.processGyro(mTmpRotatedEvent, event.timestamp);
	}

}
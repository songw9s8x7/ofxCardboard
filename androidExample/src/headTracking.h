/*
 * headTracking.h
 *
 *  Created on: Feb 24, 2015
 *      Author: dantheman
 */

#pragma once
#include "ofMain.h"
#include "OrientationEKF.h"
#include "ofxAccelerometer.h"
class headTracking {
public:
	headTracking();
	virtual ~headTracking();
	void setup();
	ofMatrix4x4 getLastHeadView(ofMatrix4x4 headView);
    void processSensorEvent(SensorEvent event);
    void accelerationChanged(SensorEvent & event);
    void gyroChanged(SensorEvent & event);
    void reset();
    OrientationEKF mTracker;
private:
    ofMatrix4x4 mEkfToHeadTracker;
    vector<float> mTmpHeadView;
    ofVec3f mTmpRotatedEvent;
    bool mTracking;

    long mLastGyroEventTimeNanos;
};



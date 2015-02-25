/*
 * OrientationEKF.h
 *
 *  Created on: Feb 24, 2015
 *      Author: dantheman
 */

#pragma once
#include "ofMain.h"
#include "So3Util.h"
class OrientationEKF {
public:
	OrientationEKF();
	virtual ~OrientationEKF();
	void reset();
	bool isReady();
	float getHeadingDegrees();
	void setHeadingDegrees(float heading);
	void processGyro(vector<float> gyro, long sensorTimeStamp);
	void processAcc(vector<float> acc, long sensorTimeStamp);
	void processMag(vector<float> mag, long sensorTimeStamp);

	ofMatrix4x4 getGLMatrix();
	ofMatrix4x4 getPredictedGLMatrix(float secondsAfterLastGyroEvent);

private:
	void mult(ofMatrix3x3 a, ofVec3f v, ofVec3f& result);
	ofMatrix4x4 glMatrixFromSo3(ofMatrix3x3 so3);
	void filterGyroTimestep(float timeStep);
	void updateCovariancesAfterMotion();
	void accObservationFunctionForNumericalJacobian(
			ofMatrix3x3 so3SensorFromWorldPred, ofVec3f& result);
	void magObservationFunctionForNumericalJacobian(
			ofMatrix3x3 so3SensorFromWorldPred, ofVec3f& result);
	void arrayAssign(vector<vector<float> > data, ofMatrix3x3 m);

	ofMatrix3x3 so3SensorFromWorld;
	ofMatrix3x3 so3LastMotion;
	ofMatrix3x3 mP;
	ofMatrix3x3 mQ;
	ofMatrix3x3 mR;
	ofMatrix3x3 mRaccel;
	ofMatrix3x3 mS;
	ofMatrix3x3 mH;
	ofMatrix3x3 mK;
	ofVec3f mNu;
	ofVec3f mz;
	ofVec3f mh;
	ofVec3f mu;
	ofVec3f mx;
	ofVec3f down;
	ofVec3f north;
	ofMatrix3x3 getPredictedGLMatrixTempM1;
	ofMatrix3x3 getPredictedGLMatrixTempM2;
	ofVec3f getPredictedGLMatrixTempV1;
	ofMatrix3x3 setHeadingDegreesTempM1;
	ofMatrix3x3 processGyroTempM1;
	ofMatrix3x3 processGyroTempM2;
	ofMatrix3x3 processAccTempM1;
	ofMatrix3x3 processAccTempM2;
	ofMatrix3x3 processAccTempM3;
	ofMatrix3x3 processAccTempM4;
	ofMatrix3x3 processAccTempM5;
	ofVec3f processAccTempV1;
	ofVec3f processAccTempV2;
	ofVec3f processAccVDelta;
	ofVec3f processMagTempV1;
	ofVec3f processMagTempV2;
	ofVec3f processMagTempV3;
	ofVec3f processMagTempV4;
	ofVec3f processMagTempV5;
	ofMatrix3x3 processMagTempM1;
	ofMatrix3x3 processMagTempM2;
	ofMatrix3x3 processMagTempM4;
	ofMatrix3x3 processMagTempM5;
	ofMatrix3x3 processMagTempM6;
	ofMatrix3x3 updateCovariancesAfterMotionTempM1;
	ofMatrix3x3 updateCovariancesAfterMotionTempM2;
	ofMatrix3x3 accObservationFunctionForNumericalJacobianTempM;
	ofMatrix3x3 magObservationFunctionForNumericalJacobianTempM;

	long sensorTimeStampGyro;
	long sensorTimeStampAcc;
	long sensorTimeStampMag;
	vector<float> lastGyro;
	float filteredGyroTimestep;
	bool timestepFilterInit;
	int numGyroTimestepSamples;
	bool gyroFilterValid;
	So3Util So3;
};


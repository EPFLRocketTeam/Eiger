/* gps_ekf: TinyEKF test case using You Chong's GPS example:
 * 
 *   http://www.mathworks.com/matlabcentral/fileexchange/31487-extended-kalman-filter-ekf--for-gps
 * 
 * Reads file gps.csv of satellite data and writes file ekf.csv of mean-subtracted estimated positions.
 *
 *
 * References:
 *
 * 1. R G Brown, P Y C Hwang, "Introduction to random signals and applied 
 * Kalman filtering : with MATLAB exercises and solutions",1996
 *
 * 2. Pratap Misra, Per Enge, "Global Positioning System Signals, 
 * Measurements, and Performance(Second Edition)",2006
 * 
 * Copyright (C) 2015 Simon D. Levy
 *
 * MIT License
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

#include "ekf/tinyekf_config.h"
#include "ekf/tiny_ekf.h"
#include "cmsis_os.h"
#include "CAN_communication.h"

float IMUb[6];
float zdata[4];

extern volatile int IMU_avail;

// positioning interval
//static const float T = 1;

/*static void blkfill(ekf_t * ekf, const float * a, int off)
 {
 off *= 2;

 ekf->Q[off]   [off]   = a[0];
 ekf->Q[off]   [off+1] = a[1];
 ekf->Q[off+1] [off]   = a[2];
 ekf->Q[off+1] [off+1] = a[3];
 }*/

static void init(ekf_t * ekf) {
	// Set Q, see [1]
	/*const float Sf    = 36;
	 const float Sg    = 0.01;
	 const float sigma = 5;         // state transition variance
	 const float Qb[4] = {Sf*T+Sg*T*T*T/3, Sg*T*T/2, Sg*T*T/2, Sg*T};
	 const float Qxyz[4] = {sigma*sigma*T*T*T/3, sigma*sigma*T*T/2, sigma*sigma*T*T/2, sigma*sigma*T};*/

	float Qtmp[81] = { 1.3085e-08, 9.2466e-25, 6.6028e-26, 9.8168e-07,
			6.9357e-23, 4.9523e-24, 0, 0, 0, -6.4641e-26, 1.3083e-08,
			-3.9941e-25, -4.8495e-24, 9.8132e-07, -2.9957e-23, 0, 0, 0,
			7.9888e-25, -5.9826e-25, 1.3081e-08, 5.9934e-23, -4.4875e-23,
			9.8116e-07, 0, 0, 0, .8168e-07, 6.937e-23, 4.9536e-24, 9.8168e-05,
			6.9363e-21, 4.9529e-22, 0, 0, 0, -4.8486e-24, 9.8132e-07,
			-2.996e-23, -4.849e-22, 9.8132e-05, -2.9959e-21, 0, 0, 0,
			5.9918e-23, -4.4872e-23, 9.8116e-07, 5.9926e-21, -4.4874e-21,
			9.8116e-05, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0002, 1.4035e-20,
			8.6736e-21, 0, 0, 0, 0, 0, 0, 2.4938e-21, 0.0002, 0, 0, 0, 0, 0, 0,
			0, 9.5501e-21, -1.2369e-20, 0.0002 };
	int i, j;
	for (i = 0; i < 9; i++) {
		ekf->x[i] = 0;
		for (j = 0; j < 9; j++)
			ekf->Q[i][j] = Qtmp[i * 9 + j];
	}

	/*
	 blkfill(ekf, Qxyz, 0);
	 blkfill(ekf, Qxyz, 1);
	 blkfill(ekf, Qxyz, 2);
	 blkfill(ekf, Qb,   3);
	 */

	// initial covariances of state noise, measurement noise
	float P0[9] = { 2, 2, 2, 1, 1, 1, 0.1, 0.1, 0.1 };
	float R0[4] = { 100, 100, 10, 10 }; //accuracy of the GPS and baro

	for (i = 0; i < 9; ++i)
		ekf->P[i][i] = P0[i];

	for (i = 0; i < 4; ++i)
		ekf->R[i][i] = R0[i];

}

/*static void model(ekf_t * ekf, float SV[4][3])
 {

 int i, j;

 for (j=0; j<8; j+=2) {
 ekf->fx[j] = ekf->x[j] + T * ekf->x[j+1];
 ekf->fx[j+1] = ekf->x[j+1];
 }

 for (j=0; j<8; ++j)
 ekf->F[j][j] = 1;

 for (j=0; j<4; ++j)
 ekf->F[2*j][2*j+1] = T;

 float dx[4][3];

 for (i=0; i<4; ++i) {
 ekf->hx[i] = 0;
 for (j=0; j<3; ++j) {
 float d = ekf->fx[j*2] - SV[i][j];
 dx[i][j] = d;
 ekf->hx[i] += d*d;
 }
 ekf->hx[i] = pow(ekf->hx[i], 0.5) + ekf->fx[6];

 }

 for (i=0; i<4; ++i) {
 for (j=0; j<3; ++j)
 ekf->H[i][j*2]  = dx[i][j] / ekf->hx[i];
 ekf->H[i][6] = 1;
 }
 }*/

//static void readline(char * line, FILE * fp)
//{
//    fgets(line, 1000, fp);
//}
/*static void readdata(FILE * fp, float SV_Pos[4][3], float SV_Rho[4])
 {
 char line[1000];

 readline(line, fp);

 char * p = strtok(line, ",");

 int i, j;

 for (i=0; i<4; ++i)
 for (j=0; j<3; ++j) {
 SV_Pos[i][j] = atof(p);
 p = strtok(NULL, ",");
 }

 for (j=0; j<4; ++j) {
 SV_Rho[j] = atof(p);
 p = strtok(NULL, ",");
 }
 }*/

//static void readdata2(FILE * fp, float IMUb[6], float zdata[4])
//{
//    char line[1000];
//
//    readline(line, fp);
//
//    char * p = strtok(line, ",");
//
//    int i, j;
//
//    for (i=0; i<6; ++i) {
//        IMUb[i] = atof(p);
//        p = strtok(NULL, ",");
//    }
//
//    for (j=0; j<4; ++j) {
//        zdata[j] = atof(p);
//        p = strtok(NULL, ",");
//    }
//}
/*static void skipline(FILE * fp)
 {
 char line[1000];
 readline(line, fp);
 }*/

//void error(const char * msg)
//{
//    fprintf(stderr, "%s\n", msg);
//}
void TK_kalman() {
	// Do generic EKF initialization
	ekf_t ekf;
	ekf_init(&ekf, Nsta, Mobs);

	// Do local initialization
	init(&ekf);
	//printf("%f, %f, %f, %f, %f, %f\n", ekf.x[0], ekf.x[1], ekf.x[2],ekf.x[3], ekf.x[4], ekf.x[5]);

	// Open input data file
	//FILE * ifp = fopen("gps.csv", "r");
//    FILE * datafp = fopen("data.csv", "r");
	// Skip CSV header
	//skipline(ifp);

	double IMUmd[6];
	float IMUm[6];
	// Make a place to store the data from the file and the output of the EKF
	/*float SV_Pos[4][3];
	 float SV_Rho[4];*/
	//float Pos_KF[25][3];
	// true
	float F11[9][9];
	float dt = 0.1; // fix at 10 Hz
	double sp, sr, sy, cp, cr, cy;
	int isGPSHere = 5;

	// Open output CSV file and write header
//    const char * OUTFILE = "ekf.csv";
//    FILE * ofp = fopen(OUTFILE, "w");
//    fprintf(ofp, "pX,pY,pZ,vX,vY,vZ\n");

	int j, k;
	for (j = 0; j < 9; j++)
		for (k = 0; k < 9; k++)
			F11[j][k] = 0;
	for (j = 0; j < 6; j++) {
		IMUb[j] = 0;
	}

	// Loop till no more data
	//IMUb[] acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z //zdata gps_x, gps_y, gps_z, alt

	while (1) {

		//readdata(ifp, SV_Pos, SV_Rho);
		// true model 4 rocket
//        readdata2(datafp, IMUb, zdata);
		//TODO: Add data
		if (IMU_avail == 1) {
			IMU_avail = 0;
			//getting the data of the captor in the mapping frame IMUb to IMUm
			sr = sin(ekf.x[6]); //roll
			sp = sin(ekf.x[7]); //pitch
			sy = sin(ekf.x[8]); //yaw
			cr = cos(ekf.x[6]); //roll
			cp = cos(ekf.x[7]); //pitch
			cy = cos(ekf.x[8]); //yaw

			IMUmd[0] = cp * cy * IMUb[0] + (sr * sp * cy + cr * sy) * IMUb[1]
					+ (-cr * sp * cy + sr * sy) * IMUb[2];
			IMUmd[1] = -cp * sy * IMUb[0] + (-sr * sp * sy + cr * cy) * IMUb[1]
					+ (cr * sp * sy + sr * cy) * IMUb[2];
			IMUmd[2] = sp * IMUb[0] - sr * cp * IMUb[1] + cr * cp * IMUb[2];

			IMUmd[3] = cp * cy * IMUb[3] + (sr * sp * cy + cr * sy) * IMUb[4]
					+ (-cr * sp * cy + sr * sy) * IMUb[5];
			IMUmd[4] = -cp * sy * IMUb[3] + (-sr * sp * sy + cr * cy) * IMUb[4]
					+ (cr * sp * sy + sr * cy) * IMUb[5];
			IMUmd[5] = sp * IMUb[3] - sr * cp * IMUb[4] + cr * cp * IMUb[5];

			IMUm[0] = (float) IMUmd[0];
			IMUm[1] = (float) IMUmd[1];
			IMUm[2] = (float) IMUmd[2] - 9.81;
			IMUm[3] = (float) IMUmd[3];
			IMUm[4] = (float) IMUmd[4];
			IMUm[5] = (float) IMUmd[5];

			//fill fx
			ekf.fx[6] = ekf.x[6] + IMUm[3] * dt;
			ekf.fx[7] = ekf.x[7] + IMUm[4] * dt;
			ekf.fx[8] = ekf.x[8] + IMUm[5] * dt;
			ekf.fx[3] = ekf.x[3] + IMUm[0] * dt;
			ekf.fx[4] = ekf.x[4] + IMUm[1] * dt;
			ekf.fx[5] = ekf.x[5] + IMUm[2] * dt;
			ekf.fx[0] = ekf.x[0] + ekf.x[3] * dt;
			ekf.fx[1] = ekf.x[1] + ekf.x[4] * dt;
			ekf.fx[2] = ekf.x[2] + ekf.x[5] * dt;

			//fill F
			F11[0][3] = 1 * dt;
			F11[1][4] = 1 * dt;
			F11[2][5] = 1 * dt;
			F11[3][7] = -IMUm[2] * dt;
			F11[3][8] = IMUm[1] * dt;
			F11[4][6] = IMUm[2] * dt;
			F11[4][8] = -IMUm[0] * dt;
			F11[5][6] = -IMUm[1] * dt;
			F11[5][7] = IMUm[0] * dt;

			mat_exp(F11, ekf.F, 9); //2nd order taylor, exact since F11^3 = 0

			//fill hx
			ekf.hx[0] = ekf.fx[0];
			ekf.hx[1] = ekf.fx[1];
			ekf.hx[2] = ekf.fx[2];
			ekf.hx[3] = ekf.fx[2];

			if (isGPSHere >= 5) { // go for the kalman
				//fill H
				ekf.H[0][0] = 1;
				ekf.H[1][1] = 1;
				ekf.H[2][2] = 1;
				ekf.H[3][2] = 1;
				ekf_step(&ekf, zdata);
				ekf.x[6] = 0; // force orientation pointing up
				ekf.x[7] = 0;
				ekf.x[8] = 0;
				isGPSHere = 0;
			} else { //simple INS
				//fill H
				ekf.H[0][0] = 0;
				ekf.H[1][1] = 0;
				ekf.H[2][2] = 0;
				ekf.H[3][2] = 1;
				ekf_step(&ekf, zdata);
				//isGPSHere++;
			}

			// grab positions, ignoring velocities
			/*for (k=0; k<3; k++)
			 Pos_KF[j][k] = ekf.x[k];*/

//        fprintf(ofp,"%f, %f, %f, %f, %f, %f\n", ekf.x[0], ekf.x[1], ekf.x[2],ekf.x[3], ekf.x[4], ekf.x[5]);
			//printf("%f, %f, %f, %f, %f, %f\n", ekf.x[0], ekf.x[1], ekf.x[2],ekf.x[3], ekf.x[4], ekf.x[5]);
			//printf("%f, %f, %f, %f, %f, %f, %f, %f, %f, %f \n", IMUb[0], IMUb[1],IMUb[2],IMUb[3],IMUb[4],IMUb[5],zdata[0],zdata[1],zdata[2],zdata[3]);

			//send estimate to the CAN
			can_setFrame((int32_t) (1000 * ekf.x[0]), DATA_ID_KALMAN_X, HAL_GetTick());
			can_setFrame((int32_t) (1000 * ekf.x[1]), DATA_ID_KALMAN_Y, HAL_GetTick());
			can_setFrame((int32_t) (1000 * ekf.x[2]), DATA_ID_KALMAN_Z, HAL_GetTick());
			can_setFrame((int32_t) (1000 * ekf.x[3]), DATA_ID_KALMAN_VX, HAL_GetTick());
			can_setFrame((int32_t) (1000 * ekf.x[4]), DATA_ID_KALMAN_VY, HAL_GetTick());
			can_setFrame((int32_t) (1000 * ekf.x[5]), DATA_ID_KALMAN_VZ, HAL_GetTick());
			can_setFrame((int32_t) (1000 * ekf.x[6]), DATA_ID_KALMAN_YAW, HAL_GetTick()); //todo check
			can_setFrame((int32_t) (1000 * ekf.x[7]), DATA_ID_KALMAN_PITCH, HAL_GetTick()); //todo check
			can_setFrame((int32_t) (1000 * ekf.x[8]), DATA_ID_KALMAN_ROLL, HAL_GetTick()); //todo check
			osDelay(100);
		}
		else {
			osDelay(10);
		}
	}

	// Compute means of filtered positions
	/*float mean_Pos_KF[3] = {0, 0, 0};
	 for (j=0; j<25; ++j)
	 for (k=0; k<3; ++k)
	 mean_Pos_KF[k] += Pos_KF[j][k];
	 for (k=0; k<3; ++k)
	 mean_Pos_KF[k] /= 25;


	 // Dump filtered positions minus their means
	 for (j=0; j<25; ++j) {
	 fprintf(ofp, "%f,%f,%f\n",
	 Pos_KF[j][0]-mean_Pos_KF[0], Pos_KF[j][1]-mean_Pos_KF[1], Pos_KF[j][2]-mean_Pos_KF[2]);
	 } */
	/*for(j=0;j<8;j++){
	 for(k=0;k<8;k++)
	 printf("%f, ", ekf.Q[j][k]*10000);
	 printf("\n");
	 }*/

	// Done!
//    fclose(datafp);
//    fclose(ofp);
//    printf("Wrote file %s\n", OUTFILE);
//    return 0;
}

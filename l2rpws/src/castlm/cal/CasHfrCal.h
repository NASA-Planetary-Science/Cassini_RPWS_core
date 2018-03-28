#ifndef CasHfrCal_h
#define CasHfrCal_h

#ifdef __cplusplus
extern "C" {
#endif



/* 
  RPWS Cassini High Frequency Receiver Calibration File


Modification List:
  March 26f, 2003 raj 
    copy the new calibration file dated December 16, 1999 into a header
    file for static inclusion into the program.

  March 30, 2003 raj
    add another row to the A1 HF2 constants table to support blast hfr mode

  April 1, 2003 raj
    Add the instrument cycle timing information 

*/



#include "CasHfrA1HF1.h"
#include "CasHfrA1HF2.h"


/* A1,A2,A3  calibration constants for Band A,B,C,HF1,HF2 */
static float A123[8][4]={
/*  A1     A2     A3     A3 (att. on) */
{  166.37f, 73.20f, -0.01f,  136.27f },  /* Ex Band A */
{  164.84f, 73.16f,  3.21f,  134.84f },  /* Ez Band A */
{  168.48f, 85.61f,  0.08f,  138.38f },  /* Ex Band B */
{  168.70f, 85.03f,  1.31f,  138.70f },  /* Ez Band B */
{  168.43f, 82.58f,  0.01f,  138.33f },  /* Ex Band C */
{  169.46f, 82.30f,  0.00f,  139.46f },  /* Ez Band C */
{    0.00f, 94.81f,  0.00f,    0.00f },  /* Ex Band HF */
{    0.00f, 96.76f,  0.00f,    0.00f }   /* Ez Band HF */
};



static float dBcalABC_08[12][8];
static float dbcal_08[8][12]={
/*  
         Band A                  Band B                  Band C
 +X    -X   +/-X   Z     +X    -X   +/-X   Z     +X    -X   +/-X   Z    */
{ 70.26f,70.87f,70.57f,70.51f,71.41f,71.58f,71.49f,71.24f,69.66f,69.63f,69.65f,69.21f },
{ 69.92f,70.26f,70.09f,70.21f,71.92f,71.98f,71.95f,71.84f,69.14f,69.11f,69.12f,68.84f },
{ 69.39f,69.74f,69.56f,69.76f,71.53f,71.48f,71.50f,71.46f,68.42f,68.31f,68.36f,68.20f },
{ 69.06f,69.40f,69.23f,69.29f,70.58f,70.55f,70.57f,70.56f,67.73f,67.68f,67.70f,67.65f },
{ 68.87f,68.99f,68.93f,69.08f,69.39f,69.40f,69.40f,69.40f,67.16f,67.16f,67.16f,67.20f },
{ 68.85f,68.89f,68.87f,68.92f,68.43f,68.43f,68.43f,68.42f,66.94f,66.93f,66.94f,67.10f },
{ 68.93f,68.82f,68.88f,68.81f,67.38f,67.38f,67.38f,67.37f,66.71f,66.68f,66.69f,66.87f },
{ 67.70f,67.53f,67.61f,67.52f,65.87f,65.82f,65.84f,65.92f,65.08f,65.16f,65.12f,65.21f }
};



static float dBcalABC_16[12][16];
static float dbcal_16[16][12]={
/*  
         Band A                  Band B                  Band C
 +X    -X   +/-X   Z     +X    -X   +/-X   Z     +X    -X   +/-X   Z    */
{ 73.01f,73.58f,73.30f,73.23f,73.74f,73.91f,73.82f,73.49f,75.33f,75.29f,75.31f,74.79f },
{ 72.71f,73.36f,73.04f,73.03f,74.38f,74.54f,74.46f,74.29f,75.31f,75.29f,75.30f,74.82f },
{ 72.64f,73.04f,72.84f,72.90f,74.54f,74.63f,74.59f,74.46f,74.85f,74.80f,74.83f,74.48f },
{ 72.48f,72.76f,72.62f,72.77f,74.49f,74.52f,74.51f,74.44f,74.50f,74.48f,74.49f,74.21f },
{ 72.22f,72.57f,72.40f,72.54f,74.26f,74.28f,74.27f,74.20f,74.10f,74.03f,74.07f,73.86f },
{ 72.02f,72.37f,72.20f,72.29f,73.87f,73.76f,73.81f,73.77f,73.71f,73.54f,73.63f,73.48f },
{ 71.83f,72.25f,72.04f,72.17f,73.40f,73.34f,73.37f,73.37f,73.41f,73.32f,73.37f,73.31f },
{ 71.68f,71.94f,71.81f,71.94f,72.76f,72.76f,72.76f,72.76f,73.05f,73.02f,73.04f,72.98f },
{ 71.42f,71.68f,71.55f,71.72f,72.25f,72.26f,72.25f,72.25f,72.74f,72.75f,72.75f,72.76f },
{ 71.49f,71.46f,71.48f,71.61f,71.86f,71.87f,71.86f,71.86f,72.59f,72.58f,72.59f,72.65f },
{ 71.46f,71.49f,71.48f,71.58f,71.28f,71.27f,71.28f,71.26f,72.51f,72.42f,72.47f,72.62f },
{ 71.48f,71.52f,71.50f,71.53f,70.66f,70.67f,70.67f,70.66f,72.36f,72.44f,72.40f,72.54f },
{ 71.65f,71.47f,71.56f,71.49f,70.11f,70.08f,70.10f,70.10f,72.49f,72.46f,72.48f,72.55f },
{ 71.61f,71.56f,71.59f,71.47f,69.61f,69.64f,69.63f,69.61f,72.33f,72.29f,72.31f,72.47f },
{ 71.32f,71.10f,71.21f,71.07f,69.10f,69.07f,69.09f,69.10f,71.44f,71.47f,71.45f,71.60f },
{ 69.69f,69.56f,69.63f,69.59f,67.91f,67.84f,67.87f,67.96f,69.73f,69.85f,69.79f,69.85f }
};



static float dBcalABC_32[12][32];
static float dbcal_32[32][12]={
/*  
         Band A                  Band B                  Band C
 +X    -X   +/-X   Z     +X    -X   +/-X   Z     +X    -X   +/-X   Z    */
{ 75.39f,76.01f,75.71f,75.63f,75.34f,75.58f,75.46f,75.18f,77.09f,77.10f,77.09f,76.57f },
{ 75.39f,75.92f,75.66f,75.61f,75.92f,76.04f,75.98f,75.72f,77.25f,77.16f,77.21f,76.75f },
{ 75.24f,75.91f,75.57f,75.55f,76.18f,76.33f,76.26f,76.04f,77.21f,77.15f,77.18f,76.73f },
{ 75.15f,75.77f,75.42f,75.46f,76.36f,76.54f,76.45f,76.29f,77.03f,77.06f,77.05f,76.63f },
{ 75.11f,75.57f,75.28f,75.32f,76.56f,76.65f,76.61f,76.46f,76.88f,76.87f,76.88f,76.49f },
{ 75.03f,75.39f,75.18f,75.23f,76.55f,76.64f,76.59f,76.47f,76.67f,76.59f,76.63f,76.28f },
{ 74.92f,75.20f,75.06f,75.14f,76.50f,76.49f,76.50f,76.42f,76.42f,76.35f,76.38f,76.06f },
{ 74.92f,75.20f,75.06f,75.12f,76.36f,76.45f,76.40f,76.33f,76.12f,76.16f,76.14f,75.87f },
{ 74.80f,75.11f,74.96f,75.06f,76.29f,76.29f,76.29f,76.20f,75.94f,75.89f,75.91f,75.69f },
{ 74.63f,75.03f,74.83f,74.94f,76.07f,76.12f,76.10f,76.05f,75.73f,75.63f,75.68f,75.46f },
{ 74.52f,74.88f,74.71f,74.84f,75.90f,75.85f,75.88f,75.84f,75.55f,75.38f,75.47f,75.28f },
{ 74.41f,74.76f,74.59f,74.74f,75.74f,75.55f,75.65f,75.61f,75.31f,75.17f,75.23f,75.15f },
{ 74.33f,74.75f,74.54f,74.70f,75.48f,75.33f,75.40f,75.39f,75.16f,75.08f,75.12f,75.03f },
{ 74.24f,74.67f,74.46f,74.62f,75.17f,75.19f,75.18f,75.18f,75.00f,74.92f,74.96f,74.89f },
{ 74.15f,74.45f,74.30f,74.47f,75.01f,75.00f,75.01f,74.99f,74.85f,74.82f,74.83f,74.77f },
{ 74.03f,74.25f,74.14f,74.32f,74.80f,74.82f,74.81f,74.82f,74.72f,74.68f,74.70f,74.65f },
{ 73.97f,74.22f,74.09f,74.27f,74.50f,74.52f,74.51f,74.51f,74.57f,74.59f,74.58f,74.55f },
{ 73.83f,74.11f,73.97f,74.14f,74.17f,74.18f,74.17f,74.16f,74.57f,74.58f,74.57f,74.58f },
{ 73.89f,73.89f,73.89f,74.04f,73.92f,73.92f,73.92f,73.91f,74.37f,74.42f,74.40f,74.44f },
{ 73.93f,73.87f,73.90f,74.02f,73.63f,73.65f,73.64f,73.64f,74.36f,74.30f,74.33f,74.40f },
{ 73.90f,73.96f,73.93f,74.04f,73.33f,73.35f,73.34f,73.33f,74.37f,74.22f,74.29f,74.41f },
{ 73.88f,73.88f,73.88f,73.97f,73.09f,73.06f,73.08f,73.08f,74.26f,74.24f,74.25f,74.42f },
{ 73.86f,73.86f,73.86f,73.92f,72.72f,72.76f,72.74f,72.74f,74.24f,74.25f,74.24f,74.39f },
{ 73.84f,73.91f,73.88f,73.88f,72.52f,72.49f,72.50f,72.51f,74.17f,74.30f,74.24f,74.39f },
{ 74.06f,73.81f,73.94f,73.93f,72.24f,72.23f,72.23f,72.23f,74.25f,74.28f,74.27f,74.42f },
{ 74.07f,73.97f,74.02f,73.96f,72.07f,72.02f,72.05f,72.04f,74.28f,74.20f,74.24f,74.41f },
{ 74.21f,74.08f,74.14f,74.02f,71.87f,71.89f,71.88f,71.86f,74.12f,74.17f,74.14f,74.30f },
{ 74.03f,74.05f,74.04f,73.92f,71.62f,71.65f,71.64f,71.63f,73.96f,73.85f,73.91f,74.09f },
{ 73.98f,73.72f,73.85f,73.70f,71.27f,71.29f,71.28f,71.29f,73.56f,73.54f,73.55f,73.70f },
{ 73.59f,73.41f,73.50f,73.37f,70.87f,70.79f,70.83f,70.86f,72.89f,72.98f,72.93f,73.05f },
{ 72.67f,72.54f,72.61f,72.54f,70.19f,70.19f,70.19f,70.28f,72.01f,72.10f,72.06f,72.15f },
{ 71.60f,71.47f,71.54f,71.53f,69.33f,69.19f,69.24f,69.39f,70.75f,70.91f,70.83f,70.93f }
};



static float dBcalHF[8][8];
static float dbcalhf[8][8]={
/*  
   1 filter      2 filter      4 filter      8 filter
  x      z      x      z      x      z      x      z   */
{ 68.23f, 68.23f, 72.16f, 72.11f, 75.14f, 75.12f, 77.26f, 77.36f },
{  0.00f,  0.00f, 72.10f, 72.19f, 75.48f, 75.39f, 78.14f, 78.00f },
{  0.00f,  0.00f,  0.00f,  0.00f, 75.65f, 75.70f, 77.69f, 77.57f },
{  0.00f,  0.00f,  0.00f,  0.00f, 74.81f, 75.00f, 78.15f, 78.05f },
{  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, 78.22f, 78.23f },
{  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, 77.90f, 77.96f },
{  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, 77.54f, 77.62f },
{  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, 76.99f, 77.27f }
};



/* ABC Instrument Cycle Times in Milliseconds */
/*     1E              2E a|c                2Eac               2Edf
    No. Filters       No. Filters         No. Filters       No. Filters
    8   16   32       8   16    32        8   16   32       8   16   32 */
static float ABC_CycleTime[4][4][3]={
{{ 273.f, 264.f, 242.f}, { 364.f, 365.5f, 356.f}, { 399.f, 395.f, 378.f}, { 896.f, 892.f, 864.f}},
{{ 546.f, 530.f, 504.f}, { 728.f, 733.0f, 737.f}, { 798.f, 792.f, 782.f}, {1690.f,1680.f,1660.f}},
{{1089.f,1056.f,1008.f}, {1456.f,1464.5f,1474.f}, {1596.f,1580.f,1560.f}, {3280.f,3260.f,3220.f}},
{{2180.f,2110.f,2003.f}, {2905.f,2925.0f,2945.f}, {3192.f,3160.f,3120.f}, {6420.f,6400.f,6340.f}}
};



/*  The initial step of HF1 or for Freeze mode */
/*  1E     2E   2E a|c  2Eac   2Edf                               */
static float HF1_InitStepTime[4][5]={
{  21.2f,  24.5f,  25.8f,  27.4f,  56.8f },  /*  20mS Integration Time */
{  36.4f,  42.8f,  45.7f,  49.0f,  98.0f },  /*  40mS Integration Time */
{  66.8f,  80.0f,  85.9f,  91.8f, 181.0f },  /*  80mS Integration Time */
{ 128.3f, 154.0f, 165.5f, 178.0f, 347.4f }   /* 160mS Integration Time */
};



/*  The preceeding steps of HF1 */
/*  1E     2E   2E a|c  2Eac   2Edf                               */
static float HF1_PrecStepTime[4][5]={
{  20.1f,  23.1f,  24.6f,  26.2f,  50.4f },  /*  20mS Integration Time */
{  34.7f,  41.9f,  41.45f, 47.5f,  90.2f },  /*  40mS Integration Time */
{  65.5f,  78.2f,  84.1f,  91.2f, 171.7f },  /*  80mS Integration Time */
{ 125.9f, 153.6f, 163.3f, 175.7f, 336.7f }   /* 160mS Integration Time */
};



/*  The initial step of HF2 or for Freeze mode */
/*  1E   2E   2E a|c  2Eac  2Edf                               */
static float HF2_InitStepTime[4][5]={
{ 12.5f, 14.2f, 14.75f, 15.6f,  34.9f },  /* 10mS Integration Time */
{ 20.2f, 23.5f, 24.9f,  26.4f,  55.5f },  /* 20mS Integration Time */
{ 35.3f, 42.f,  44.9f,  47.6f,  96.1f },  /* 40mS Integration Time */
{ 65.7f, 79.f,  84.8f,  90.5f, 178.f   }  /* 80mS Integration Time */
};



/*  The preceeding steps of HF2 */
/*  1E     2E   2E a|c  2Eac   2Edf                               */
static float HF2_PrecStepTime[4][5]={
{ 12.3f, 13.9f, 14.75f, 15.2f,  29.6f },  /* 10mS Integration Time */
{ 20.3f, 23.4f, 25.f,   26.2f,  50.3f },  /* 20mS Integration Time */
{ 35.2f, 41.4f, 44.3f,  47.3f,  90.4f },  /* 40mS Integration Time */
{ 66.f,  78.f,  84.5f,  89.5f, 172.f   }  /* 80mS Integration Time */
};



/* Frequencies for Bands ABC */
static float CasHfr_BandA_Freq[3][32];
static float CasHfr_BandB_Freq[3][32];
static float CasHfr_BandC_Freq[3][32];




/* Bandwidth for hfr...
static float CasHfr_Bandwidth[3][32];
*/






#ifdef __cplusplus
}  /* Close scope of 'extern "C" declaration */
#endif

#endif  /* CasHfrCal_h */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'flightControlSystem'.
 *
 * Model version                  : 1.572
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Thu Dec 10 23:13:52 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 9
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "flightControlSystem.h"
#include "rtwtypes.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

  flightControlSystem_step();

  /* Get model outputs here */
  OverrunFlag--;
}

#define UNUSED(x)                      x = x

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(void)
{
  float modelBaseRate = 0.005;
  float systemClock = 416;

  /* Initialize variables */
  stopRequested = false;
  runModel = false;
  UNUSED(modelBaseRate);
  UNUSED(systemClock);
  rtmSetErrorStatus(flightControlSystem_M, 0);
  flightControlSystem_initialize();
  ;
  runModel =
    rtmGetErrorStatus(flightControlSystem_M) == (NULL);
  ;
  while (runModel) {
    rt_OneStep();
    stopRequested = !(
                      rtmGetErrorStatus(flightControlSystem_M) == (NULL));
    runModel = !(stopRequested);
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  flightControlSystem_terminate();
  ;
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

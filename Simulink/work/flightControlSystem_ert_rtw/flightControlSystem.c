/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: flightControlSystem.c
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
#include "flightControlSystem_private.h"

/* Exported block signals */
CommandBus cmd_inport;                 /* '<Root>/AC cmd' */
SensorsBus sensor_inport;              /* '<Root>/Sensors' */
real32_T motors_outport[4];            /* '<Root>/Flight Control System' */
uint8_T flag_outport;                  /* '<Root>/Flight Control System' */

/* Block signals (default storage) */
B_flightControlSystem_T flightControlSystem_B;

/* Block states (default storage) */
DW_flightControlSystem_T flightControlSystem_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_flightControlSystem_T flightControlSystem_PrevZCX;

/* Real-time model */
static RT_MODEL_flightControlSystem_T flightControlSystem_M_;
RT_MODEL_flightControlSystem_T *const flightControlSystem_M =
  &flightControlSystem_M_;

/* Forward declaration for local functions */
static real32_T flightControlSystem_norm(const real32_T x[2]);
static boolean_T flightControlSystem_isequal(real_T varargin_1, real_T
  varargin_2);
static real_T flightControlSystem_norm_da(const real_T x[3],
  B_FlightControlSystem_flightControlSystem_T *localB);
static real32_T flightControlSystem_norm_d(const real32_T x[3]);
static real32_T flightControlSystem_angdiff(real32_T x, real32_T y);
static real_T flightControlSystem_wrapToPi(real_T theta,
  B_FlightControlSystem_flightControlSystem_T *localB);

/*
 * Output and update for action system:
 *    '<S3>/Geofencing error'
 *    '<S3>/estimator//Optical flow error'
 *    '<S3>/No optical flow '
 *    '<S3>/Ultrasound improper'
 */
void flightControlSystem_Geofencingerror(uint8_T *rty_Out1,
  P_Geofencingerror_flightControlSystem_T *localP)
{
  /* SignalConversion generated from: '<S223>/Out1' incorporates:
   *  Constant: '<S223>/Constant'
   */
  *rty_Out1 = localP->Constant_Value;
}

/* Output and update for atomic system: '<S1>/Logging' */
void flightControlSystem_Logging(const CommandBus
  *rtu_ReferenceValueServerBus_Inport_4, const SensorsBus *rtu_Sensors_Inport_5)
{
  int32_T rtb_DataTypeConversion3_e;
  int32_T rtb_DataTypeConversion7;
  real32_T rtb_DataTypeConversion11;
  real32_T rtb_DataTypeConversion9;

  /* DataTypeConversion: '<S4>/Data Type Conversion3' */
  rtb_DataTypeConversion3_e =
    rtu_ReferenceValueServerBus_Inport_4->controlModePosVSOrient;

  /* DataTypeConversion: '<S4>/Data Type Conversion7' */
  rtb_DataTypeConversion7 = rtu_ReferenceValueServerBus_Inport_4->takeoff_flag;

  /* DataTypeConversion: '<S4>/Data Type Conversion9' */
  rtb_DataTypeConversion9 = (real32_T)
    rtu_ReferenceValueServerBus_Inport_4->live_time_ticks;

  /* DataTypeConversion: '<S4>/Data Type Conversion11' */
  rtb_DataTypeConversion11 = rtu_Sensors_Inport_5->VisionSensors.usePosVIS_flag;
}

/*
 * System initialize for enable system:
 *    '<S339>/MeasurementUpdate'
 *    '<S391>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_Init(real32_T rty_Lykyhatkk1[2],
  P_MeasurementUpdate_flightControlSystem_T *localP)
{
  /* SystemInitialize for Outport: '<S368>/L*(y[k]-yhat[k|k-1])' */
  rty_Lykyhatkk1[0] = localP->Lykyhatkk1_Y0;
  rty_Lykyhatkk1[1] = localP->Lykyhatkk1_Y0;
}

/*
 * Disable for enable system:
 *    '<S339>/MeasurementUpdate'
 *    '<S391>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_Disable(real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate_flightControlSystem_T *localDW,
  P_MeasurementUpdate_flightControlSystem_T *localP)
{
  /* Outputs for Enabled SubSystem: '<S339>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S368>/Enable'
   */
  /* Disable for Outport: '<S368>/L*(y[k]-yhat[k|k-1])' */
  rty_Lykyhatkk1[0] = localP->Lykyhatkk1_Y0;
  rty_Lykyhatkk1[1] = localP->Lykyhatkk1_Y0;

  /* End of Outputs for SubSystem: '<S339>/MeasurementUpdate' */
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S339>/MeasurementUpdate'
 *    '<S391>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate(boolean_T rtu_Enable, const real32_T
  rtu_Lk[2], real32_T rtu_yk, const real32_T rtu_Ck[2], const real32_T
  rtu_xhatkk1[2], real32_T rtu_Dk, real32_T rtu_uk, real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate_flightControlSystem_T *localDW,
  P_MeasurementUpdate_flightControlSystem_T *localP)
{
  real32_T rtb_Sum_d;

  /* Outputs for Enabled SubSystem: '<S339>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S368>/Enable'
   */
  if (rtu_Enable) {
    localDW->MeasurementUpdate_MODE = true;

    /* Sum: '<S368>/Sum' incorporates:
     *  Product: '<S368>/C[k]*xhat[k|k-1]'
     *  Product: '<S368>/D[k]*u[k]'
     *  Sum: '<S368>/Add1'
     */
    rtb_Sum_d = rtu_yk - ((rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] * rtu_xhatkk1
      [1]) + rtu_Dk * rtu_uk);

    /* Product: '<S368>/Product3' */
    rty_Lykyhatkk1[0] = rtu_Lk[0] * rtb_Sum_d;
    rty_Lykyhatkk1[1] = rtu_Lk[1] * rtb_Sum_d;
  } else {
    if (localDW->MeasurementUpdate_MODE) {
      flightControlSystem_MeasurementUpdate_Disable(rty_Lykyhatkk1, localDW,
        localP);
    }
  }

  /* End of Outputs for SubSystem: '<S339>/MeasurementUpdate' */
}

/*
 * System initialize for enable system:
 *    '<S346>/Enabled Subsystem'
 *    '<S398>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_Init(real32_T rty_deltax[2],
  P_EnabledSubsystem_flightControlSystem_T *localP)
{
  /* SystemInitialize for Outport: '<S370>/deltax' */
  rty_deltax[0] = localP->deltax_Y0;
  rty_deltax[1] = localP->deltax_Y0;
}

/*
 * Disable for enable system:
 *    '<S346>/Enabled Subsystem'
 *    '<S398>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_Disable(real32_T rty_deltax[2],
  DW_EnabledSubsystem_flightControlSystem_T *localDW,
  P_EnabledSubsystem_flightControlSystem_T *localP)
{
  /* Outputs for Enabled SubSystem: '<S346>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S370>/Enable'
   */
  /* Disable for Outport: '<S370>/deltax' */
  rty_deltax[0] = localP->deltax_Y0;
  rty_deltax[1] = localP->deltax_Y0;

  /* End of Outputs for SubSystem: '<S346>/Enabled Subsystem' */
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S346>/Enabled Subsystem'
 *    '<S398>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem(boolean_T rtu_Enable, const real32_T
  rtu_Mk[2], const real32_T rtu_Ck[2], real32_T rtu_yk, const real32_T
  rtu_xhatkk1[2], real32_T rty_deltax[2],
  DW_EnabledSubsystem_flightControlSystem_T *localDW,
  P_EnabledSubsystem_flightControlSystem_T *localP)
{
  real32_T rtb_Add1;

  /* Outputs for Enabled SubSystem: '<S346>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S370>/Enable'
   */
  if (rtu_Enable) {
    localDW->EnabledSubsystem_MODE = true;

    /* Sum: '<S370>/Add1' incorporates:
     *  Product: '<S370>/Product'
     */
    rtb_Add1 = rtu_yk - (rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] * rtu_xhatkk1[1]);

    /* Product: '<S370>/Product2' */
    rty_deltax[0] = rtu_Mk[0] * rtb_Add1;
    rty_deltax[1] = rtu_Mk[1] * rtb_Add1;
  } else {
    if (localDW->EnabledSubsystem_MODE) {
      flightControlSystem_EnabledSubsystem_Disable(rty_deltax, localDW, localP);
    }
  }

  /* End of Outputs for SubSystem: '<S346>/Enabled Subsystem' */
}

real32_T rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T tmp;
  real32_T tmp_0;
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else {
    tmp = fabsf(u0);
    tmp_0 = fabsf(u1);
    if (rtIsInfF(u1)) {
      if (tmp == 1.0F) {
        y = 1.0F;
      } else if (tmp > 1.0F) {
        if (u1 > 0.0F) {
          y = (rtInfF);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = (rtInfF);
      }
    } else if (tmp_0 == 0.0F) {
      y = 1.0F;
    } else if (tmp_0 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = sqrtf(u0);
    } else if ((u0 < 0.0F) && (u1 > floorf(u1))) {
      y = (rtNaNF);
    } else {
      y = powf(u0, u1);
    }
  }

  return y;
}

static real32_T flightControlSystem_norm(const real32_T x[2])
{
  real32_T absxk;
  real32_T scale;
  real32_T t;
  real32_T y;
  scale = 1.29246971E-26F;
  absxk = fabsf(x[0]);
  if (absxk > 1.29246971E-26F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.29246971E-26F;
    y = t * t;
  }

  absxk = fabsf(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrtf(y);
}

real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  int32_T u0_0;
  int32_T u1_0;
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    if (u0 > 0.0F) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0F) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2f((real32_T)u0_0, (real32_T)u1_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = atan2f(u0, u1);
  }

  return y;
}

static boolean_T flightControlSystem_isequal(real_T varargin_1, real_T
  varargin_2)
{
  boolean_T p;
  p = false;
  if (varargin_1 == varargin_2) {
    p = true;
  }

  return p;
}

static real_T flightControlSystem_norm_da(const real_T x[3],
  B_FlightControlSystem_flightControlSystem_T *localB)
{
  real_T y;
  localB->scale = 3.3121686421112381E-170;
  localB->absxk = fabs(x[0]);
  if (localB->absxk > 3.3121686421112381E-170) {
    y = 1.0;
    localB->scale = localB->absxk;
  } else {
    localB->t = localB->absxk / 3.3121686421112381E-170;
    y = localB->t * localB->t;
  }

  localB->absxk = fabs(x[1]);
  if (localB->absxk > localB->scale) {
    localB->t = localB->scale / localB->absxk;
    y = y * localB->t * localB->t + 1.0;
    localB->scale = localB->absxk;
  } else {
    localB->t = localB->absxk / localB->scale;
    y += localB->t * localB->t;
  }

  localB->absxk = fabs(x[2]);
  if (localB->absxk > localB->scale) {
    localB->t = localB->scale / localB->absxk;
    y = y * localB->t * localB->t + 1.0;
    localB->scale = localB->absxk;
  } else {
    localB->t = localB->absxk / localB->scale;
    y += localB->t * localB->t;
  }

  return localB->scale * sqrt(y);
}

static real32_T flightControlSystem_norm_d(const real32_T x[3])
{
  real32_T absxk;
  real32_T scale;
  real32_T t;
  real32_T y;
  scale = 1.29246971E-26F;
  absxk = fabsf(x[0]);
  if (absxk > 1.29246971E-26F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.29246971E-26F;
    y = t * t;
  }

  absxk = fabsf(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabsf(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrtf(y);
}

static real32_T flightControlSystem_angdiff(real32_T x, real32_T y)
{
  real32_T delta;
  real32_T q;
  real32_T thetaWrap;
  boolean_T rEQ0;
  delta = y - x;
  if (fabsf(delta) > 3.1415926535897931) {
    if (rtIsNaNF(delta + 3.14159274F) || rtIsInfF(delta + 3.14159274F)) {
      thetaWrap = (rtNaNF);
    } else if (delta + 3.14159274F == 0.0F) {
      thetaWrap = 0.0F;
    } else {
      thetaWrap = fmodf(delta + 3.14159274F, 6.28318548F);
      rEQ0 = (thetaWrap == 0.0F);
      if (!rEQ0) {
        q = fabsf((delta + 3.14159274F) / 6.28318548F);
        rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);
      }

      if (rEQ0) {
        thetaWrap = 0.0F;
      } else {
        if (delta + 3.14159274F < 0.0F) {
          thetaWrap += 6.28318548F;
        }
      }
    }

    if ((thetaWrap == 0.0F) && (delta + 3.14159274F > 0.0F)) {
      thetaWrap = 6.28318548F;
    }

    delta = thetaWrap - 3.14159274F;
  }

  return delta;
}

static real_T flightControlSystem_wrapToPi(real_T theta,
  B_FlightControlSystem_flightControlSystem_T *localB)
{
  real_T b_theta;
  boolean_T rEQ0;
  b_theta = theta;
  if (fabs(theta) > 3.1415926535897931) {
    if (rtIsNaN(theta + 3.1415926535897931) || rtIsInf(theta +
         3.1415926535897931)) {
      localB->thetaWrap = (rtNaN);
    } else if (theta + 3.1415926535897931 == 0.0) {
      localB->thetaWrap = 0.0;
    } else {
      localB->thetaWrap = fmod(theta + 3.1415926535897931, 6.2831853071795862);
      rEQ0 = (localB->thetaWrap == 0.0);
      if (!rEQ0) {
        localB->q_d = fabs((theta + 3.1415926535897931) / 6.2831853071795862);
        rEQ0 = !(fabs(localB->q_d - floor(localB->q_d + 0.5)) >
                 2.2204460492503131E-16 * localB->q_d);
      }

      if (rEQ0) {
        localB->thetaWrap = 0.0;
      } else {
        if (theta + 3.1415926535897931 < 0.0) {
          localB->thetaWrap += 6.2831853071795862;
        }
      }
    }

    localB->b_j = localB->thetaWrap;
    if ((localB->thetaWrap == 0.0) && (theta + 3.1415926535897931 > 0.0)) {
      localB->b_j = 6.2831853071795862;
    }

    b_theta = localB->b_j - 3.1415926535897931;
  }

  return b_theta;
}

/* System initialize for atomic system: '<Root>/Flight Control System' */
void flightControlSystem_FlightControlSystem_Init
  (B_FlightControlSystem_flightControlSystem_T *localB,
   DW_FlightControlSystem_flightControlSystem_T *localDW,
   P_FlightControlSystem_flightControlSystem_T *localP,
   ZCE_FlightControlSystem_flightControlSystem_T *localZCE)
{
  int32_T i;
  uint8_T Merge;

  /* InitializeConditions for DiscreteIntegrator: '<S317>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = localP->DiscreteTimeIntegrator_IC;

  /* InitializeConditions for Delay: '<S319>/MemoryX' */
  localDW->icLoad = 1U;

  /* InitializeConditions for DiscreteFir: '<S253>/FIR_IMUaccel' */
  for (i = 0; i < 15; i++) {
    localDW->FIR_IMUaccel_states[i] = localP->FIR_IMUaccel_InitialStates;
  }

  /* End of InitializeConditions for DiscreteFir: '<S253>/FIR_IMUaccel' */

  /* InitializeConditions for Delay: '<S371>/MemoryX' */
  localDW->icLoad_m = 1U;

  /* InitializeConditions for UnitDelay: '<S506>/Output' */
  localDW->Output_DSTATE = localP->Output_InitialCondition;

  /* InitializeConditions for Delay: '<S251>/Delay2' */
  localDW->Delay2_DSTATE = localP->Delay2_InitialCondition;

  /* InitializeConditions for Delay: '<S255>/MemoryX' */
  localDW->icLoad_f = 1U;

  /* InitializeConditions for DiscreteFilter: '<S256>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[0] =
    localP->pressureFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S256>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[0] = localP->sonarFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S256>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[1] =
    localP->pressureFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S256>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[1] = localP->sonarFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S256>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[2] =
    localP->pressureFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S256>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[2] = localP->sonarFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S253>/LPF Fcutoff = 40Hz1' */
  localDW->LPFFcutoff40Hz1_states = localP->LPFFcutoff40Hz1_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S253>/LPF Fcutoff = 40Hz' */
  localDW->LPFFcutoff40Hz_states = localP->LPFFcutoff40Hz_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S253>/IIR_IMUgyro_r' */
  for (i = 0; i < 5; i++) {
    localDW->IIR_IMUgyro_r_states[i] = localP->IIR_IMUgyro_r_InitialStates;
  }

  /* End of InitializeConditions for DiscreteFilter: '<S253>/IIR_IMUgyro_r' */

  /* InitializeConditions for UnitDelay: '<S426>/Output' */
  localDW->Output_DSTATE_o = localP->Output_InitialCondition_b;

  /* InitializeConditions for DiscreteFilter: '<S434>/IIRgyroz' */
  for (i = 0; i < 10; i++) {
    localDW->IIRgyroz_states[i] = localP->IIRgyroz_InitialStates;
  }

  /* End of InitializeConditions for DiscreteFilter: '<S434>/IIRgyroz' */

  /* InitializeConditions for Delay: '<S435>/MemoryX' */
  localDW->icLoad_a = 1U;

  /* InitializeConditions for DiscreteIntegrator: '<S431>/SimplyIntegrateVelocity' */
  localDW->SimplyIntegrateVelocity_PrevResetState = 2;

  /* InitializeConditions for UnitDelay: '<S245>/Output' */
  localDW->Output_DSTATE_a = localP->Output_InitialCondition_k;

  /* InitializeConditions for UnitDelay: '<S442>/UD'
   *
   * Block description for '<S442>/UD':
   *
   *  Store in Global RAM
   */
  localDW->UD_DSTATE[0] = localP->DiscreteDerivative_ICPrevScaledInput;

  /* InitializeConditions for Delay: '<S430>/Delay' */
  localDW->Delay_DSTATE[0] = localP->Delay_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S431>/SimplyIntegrateVelocity' */
  localDW->SimplyIntegrateVelocity_DSTATE[0] =
    localP->SimplyIntegrateVelocity_IC;

  /* InitializeConditions for Delay: '<S6>/Delay1' */
  localDW->Delay1_DSTATE[0] = localP->Delay1_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S98>/Integrator' */
  localDW->Integrator_DSTATE[0] =
    localP->Velocitycontroller_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteTransferFcn: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller' */
  localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[0] =
    localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_i;

  /* InitializeConditions for DiscreteIntegrator: '<S198>/Integrator' */
  localDW->Integrator_DSTATE_k[0] =
    localP->Angularvelocitycontrolloop_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S193>/Filter' */
  localDW->Filter_DSTATE[0] =
    localP->Angularvelocitycontrolloop_InitialConditionForFilter;

  /* InitializeConditions for UnitDelay: '<S442>/UD'
   *
   * Block description for '<S442>/UD':
   *
   *  Store in Global RAM
   */
  localDW->UD_DSTATE[1] = localP->DiscreteDerivative_ICPrevScaledInput;

  /* InitializeConditions for Delay: '<S430>/Delay' */
  localDW->Delay_DSTATE[1] = localP->Delay_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S431>/SimplyIntegrateVelocity' */
  localDW->SimplyIntegrateVelocity_DSTATE[1] =
    localP->SimplyIntegrateVelocity_IC;

  /* InitializeConditions for Delay: '<S6>/Delay1' */
  localDW->Delay1_DSTATE[1] = localP->Delay1_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S98>/Integrator' */
  localDW->Integrator_DSTATE[1] =
    localP->Velocitycontroller_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteTransferFcn: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller' */
  localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[1] =
    localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_i;

  /* InitializeConditions for DiscreteIntegrator: '<S198>/Integrator' */
  localDW->Integrator_DSTATE_k[1] =
    localP->Angularvelocitycontrolloop_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S193>/Filter' */
  localDW->Filter_DSTATE[1] =
    localP->Angularvelocitycontrolloop_InitialConditionForFilter;

  /* InitializeConditions for Delay: '<S226>/Delay One Step' */
  localDW->DelayOneStep_DSTATE = localP->DelayOneStep_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S222>/Output' */
  localDW->Output_DSTATE_a3 = localP->Output_InitialCondition_c;

  /* SystemInitialize for Enabled SubSystem: '<S346>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_Init(localB->Product2_n,
    &localP->EnabledSubsystem_m);

  /* End of SystemInitialize for SubSystem: '<S346>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S398>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_Init(localB->Product2_p,
    &localP->EnabledSubsystem_i);

  /* End of SystemInitialize for SubSystem: '<S398>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S283>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S307>/Product2' incorporates:
   *  Outport: '<S307>/deltax'
   */
  localB->Product2[0] = localP->deltax_Y0;
  localB->Product2[1] = localP->deltax_Y0;

  /* End of SystemInitialize for SubSystem: '<S283>/Enabled Subsystem' */

  /* SystemInitialize for Triggered SubSystem: '<S423>/Triggered Subsystem' */
  /* SystemInitialize for Outport: '<S427>/Out1' incorporates:
   *  Inport: '<S427>/In1'
   */
  localB->In1_f = localP->Out1_Y0_k;

  /* End of SystemInitialize for SubSystem: '<S423>/Triggered Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S473>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S502>/Product3' incorporates:
   *  Outport: '<S502>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3_a[0] = localP->Lykyhatkk1_Y0_f;

  /* End of SystemInitialize for SubSystem: '<S473>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S480>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S504>/Product2' incorporates:
   *  Outport: '<S504>/deltax'
   */
  localB->Product2_k[0] = localP->deltax_Y0_l;

  /* End of SystemInitialize for SubSystem: '<S480>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S473>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S502>/Product3' incorporates:
   *  Outport: '<S502>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3_a[1] = localP->Lykyhatkk1_Y0_f;

  /* End of SystemInitialize for SubSystem: '<S473>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S480>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S504>/Product2' incorporates:
   *  Outport: '<S504>/deltax'
   */
  localB->Product2_k[1] = localP->deltax_Y0_l;

  /* End of SystemInitialize for SubSystem: '<S480>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S473>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S502>/Product3' incorporates:
   *  Outport: '<S502>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3_a[2] = localP->Lykyhatkk1_Y0_f;

  /* End of SystemInitialize for SubSystem: '<S473>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S480>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S504>/Product2' incorporates:
   *  Outport: '<S504>/deltax'
   */
  localB->Product2_k[2] = localP->deltax_Y0_l;

  /* End of SystemInitialize for SubSystem: '<S480>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S473>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S502>/Product3' incorporates:
   *  Outport: '<S502>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3_a[3] = localP->Lykyhatkk1_Y0_f;

  /* End of SystemInitialize for SubSystem: '<S473>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S480>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S504>/Product2' incorporates:
   *  Outport: '<S504>/deltax'
   */
  localB->Product2_k[3] = localP->deltax_Y0_l;

  /* End of SystemInitialize for SubSystem: '<S480>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S238>/Waypoint follower' */
  /* SystemInitialize for Triggered SubSystem: '<S247>/Latch the status' */
  /* SystemInitialize for Outport: '<S250>/Complete' incorporates:
   *  Inport: '<S250>/In1'
   */
  localB->In1 = localP->Complete_Y0;

  /* End of SystemInitialize for SubSystem: '<S247>/Latch the status' */

  /* Start for MATLABSystem: '<S247>/UAV Waypoint Follower' */
  localDW->obj.LastWaypointFlag = false;
  localDW->obj.StartFlag = true;
  localDW->obj.LookaheadFactor = 1.01;
  localDW->obj.isInitialized = 1;

  /* InitializeConditions for MATLABSystem: '<S247>/UAV Waypoint Follower' */
  localDW->obj.WaypointIndex = 1.0;
  for (i = 0; i < 16; i++) {
    /* Start for MATLABSystem: '<S247>/UAV Waypoint Follower' */
    localDW->obj.WaypointsInternal[i] = (rtNaN);

    /* InitializeConditions for MATLABSystem: '<S247>/UAV Waypoint Follower' */
    localDW->obj.WaypointsInternal[i] = (rtNaN);
  }

  /* SystemInitialize for DataTypeConversion: '<S247>/Data Type  Conversion' incorporates:
   *  Outport: '<S247>/To controller'
   */
  localB->DataTypeConversion[0] = localP->Tocontroller_Y0;
  localB->DataTypeConversion[1] = localP->Tocontroller_Y0;
  localB->DataTypeConversion[2] = localP->Tocontroller_Y0;

  /* SystemInitialize for MATLABSystem: '<S247>/UAV Waypoint Follower' incorporates:
   *  Outport: '<S247>/To yaw'
   */
  localB->UAVWaypointFollower_o3 = localP->Toyaw_Y0;

  /* End of SystemInitialize for SubSystem: '<S238>/Waypoint follower' */

  /* SystemInitialize for Triggered SubSystem: '<S239>/Latch the status' */
  /* SystemInitialize for Outport: '<S241>/Out1' incorporates:
   *  Inport: '<S241>/In1'
   */
  localB->In1_j = localP->Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S239>/Latch the status' */

  /* SystemInitialize for Triggered SubSystem: '<S237>/Triggered Subsystem' */
  /* SystemInitialize for SignalConversion generated from: '<S244>/X' incorporates:
   *  Outport: '<S244>/X'
   */
  localB->BufferToMakeInportVirtual_InsertedFor_X_at_inport_0 = localP->X_Y0;

  /* SystemInitialize for SignalConversion generated from: '<S244>/Y' incorporates:
   *  Outport: '<S244>/Y'
   */
  localB->BufferToMakeInportVirtual_InsertedFor_Y_at_inport_0 = localP->Y_Y0;
  localZCE->TriggeredSubsystem_Trig_ZCE_k = ZERO_ZCSIG;

  /* End of SystemInitialize for SubSystem: '<S237>/Triggered Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S391>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_Init(localB->Product3_n,
    &localP->MeasurementUpdate_j);

  /* End of SystemInitialize for SubSystem: '<S391>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S339>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_Init(localB->Product3_k,
    &localP->MeasurementUpdate_d);

  /* End of SystemInitialize for SubSystem: '<S339>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S277>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S305>/Product3' incorporates:
   *  Outport: '<S305>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[0] = localP->Lykyhatkk1_Y0;
  localB->Product3[1] = localP->Lykyhatkk1_Y0;

  /* End of SystemInitialize for SubSystem: '<S277>/MeasurementUpdate' */
  /* SystemInitialize for Merge: '<S3>/Merge' */
  Merge = localP->Merge_InitialOutput;

  /* Start for MATLABSystem: '<S239>/UAV Orbit Follower' */
  localDW->obj_f.isInitialized = 1;
  localDW->obj_f.PrevResetSignal = 0.0F;
  localDW->obj_f.NumCircles = 0.0;

  /* InitializeConditions for MATLABSystem: '<S239>/UAV Orbit Follower' */
  localDW->obj_f.OrbitRadiusInternal = (rtNaNF);
  localDW->obj_f.PrevResetSignal *= 0.0F;
  localDW->obj_f.NumCircles *= 0.0;

  /* Start for MATLABSystem: '<S239>/UAV Orbit Follower' */
  localDW->obj_f.PrevPosition[0] = 0.0F;

  /* InitializeConditions for MATLABSystem: '<S239>/UAV Orbit Follower' */
  localDW->obj_f.OrbitCenterInternal[0] = (rtNaNF);
  localDW->obj_f.PrevPosition[0] *= 0.0F;

  /* Start for MATLABSystem: '<S239>/UAV Orbit Follower' */
  localDW->obj_f.PrevPosition[1] = 0.0F;

  /* InitializeConditions for MATLABSystem: '<S239>/UAV Orbit Follower' */
  localDW->obj_f.OrbitCenterInternal[1] = (rtNaNF);
  localDW->obj_f.PrevPosition[1] *= 0.0F;

  /* Start for MATLABSystem: '<S239>/UAV Orbit Follower' */
  localDW->obj_f.PrevPosition[2] = 0.0F;

  /* InitializeConditions for MATLABSystem: '<S239>/UAV Orbit Follower' */
  localDW->obj_f.OrbitCenterInternal[2] = (rtNaNF);
  localDW->obj_f.PrevPosition[2] *= 0.0F;
  localDW->obj_f.StartFlag = true;
  localDW->obj_f.SelectTurnDirectionFlag = true;
  localDW->obj_f.TurnDirectionInternal = 1.0;
  localDW->obj_f.OrbitRadiusFlag = 0U;
  localDW->obj_f.LookaheadDistFlag = 0U;
}

/* Outputs for atomic system: '<Root>/Flight Control System' */
void flightControlSystem_FlightControlSystem(const CommandBus
  *rtu_ReferenceValueServerCmds, const SensorsBus *rtu_Sensors, real32_T
  rty_motorCmds[4], uint8_T *rty_Flag,
  B_FlightControlSystem_flightControlSystem_T *localB,
  DW_FlightControlSystem_flightControlSystem_T *localDW,
  P_FlightControlSystem_flightControlSystem_T *localP,
  ZCE_FlightControlSystem_flightControlSystem_T *localZCE)
{
  /* local block i/o variables */
  real32_T rtb_DataTypeConversion;
  real32_T acc1;
  real32_T rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;
  real32_T rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;
  real32_T rtb_Reshape9to3x3columnmajor_tmp;
  real32_T turnVector_idx_1;
  uint8_T Merge;
  uint8_T status;
  boolean_T exitg1;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T p;
  boolean_T rtb_Compare_cy;
  boolean_T rtb_Compare_l;
  boolean_T rtb_DataTypeConversionEnable;
  boolean_T rtb_DataTypeConversionEnable_a;
  boolean_T rtb_DataTypeConversionEnable_j;
  boolean_T rtb_DataTypeConversionEnable_m;

  /* Delay: '<S319>/MemoryX' incorporates:
   *  Constant: '<S319>/X0'
   *  Reshape: '<S319>/ReshapeX0'
   */
  if (localDW->icLoad != 0) {
    localDW->MemoryX_DSTATE_n[0] = localP->X0_Value_f[0];
    localDW->MemoryX_DSTATE_n[1] = localP->X0_Value_f[1];
  }

  /* Delay: '<S319>/MemoryX' */
  localB->rtb_MemoryX_l_b[0] = localDW->MemoryX_DSTATE_n[0];
  localB->rtb_MemoryX_l_b[1] = localDW->MemoryX_DSTATE_n[1];

  /* Bias: '<S253>/Assuming that the  preflight calibration was done at level orientation' incorporates:
   *  DataTypeConversion: '<S253>/Data Type Conversion'
   */
  for (localB->i = 0; localB->i < 6; localB->i++) {
    localB->inverseIMU_gain[localB->i] = rtu_Sensors->SensorCalibration
      [localB->i] +
      localP->
      Assumingthatthepreflightcalibrationwasdoneatlevelorientation_Bi[localB->i];
  }

  /* End of Bias: '<S253>/Assuming that the  preflight calibration was done at level orientation' */

  /* Sum: '<S253>/Sum1' */
  localB->Abs = localB->inverseIMU_gain[0];
  localB->acc1 = localB->inverseIMU_gain[1];
  localB->single_b = localB->inverseIMU_gain[2];
  localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1 =
    localB->inverseIMU_gain[3];
  acc1 = localB->inverseIMU_gain[4];
  rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 =
    localB->inverseIMU_gain[5];
  localB->inverseIMU_gain[0] = rtu_Sensors->HALSensors.HAL_acc_SI.x -
    localB->Abs;
  localB->inverseIMU_gain[1] = rtu_Sensors->HALSensors.HAL_acc_SI.y -
    localB->acc1;
  localB->inverseIMU_gain[2] = rtu_Sensors->HALSensors.HAL_acc_SI.z -
    localB->single_b;
  localB->inverseIMU_gain[3] = rtu_Sensors->HALSensors.HAL_gyro_SI.x -
    localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1;
  localB->inverseIMU_gain[4] = rtu_Sensors->HALSensors.HAL_gyro_SI.y - acc1;
  localB->inverseIMU_gain[5] = rtu_Sensors->HALSensors.HAL_gyro_SI.z -
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;
  for (localB->i = 0; localB->i < 6; localB->i++) {
    /* Gain: '<S253>/inverseIMU_gain' */
    localB->inverseIMU_gain[localB->i] *= localP->inverseIMU_gain_Gain[localB->i];
  }

  /* DiscreteFir: '<S253>/FIR_IMUaccel' */
  localB->acc1 = localB->inverseIMU_gain[0] * localP->FIR_IMUaccel_Coefficients
    [0];
  localB->cff = 1;
  localB->i = localDW->FIR_IMUaccel_circBuf;
  while (localB->i < 5) {
    localB->acc1 += localDW->FIR_IMUaccel_states[localB->i] *
      localP->FIR_IMUaccel_Coefficients[localB->cff];
    localB->cff++;
    localB->i++;
  }

  localB->i = 0;
  while (localB->i < localDW->FIR_IMUaccel_circBuf) {
    localB->acc1 += localDW->FIR_IMUaccel_states[localB->i] *
      localP->FIR_IMUaccel_Coefficients[localB->cff];
    localB->cff++;
    localB->i++;
  }

  localB->FIR_IMUaccel[0] = localB->acc1;
  localB->acc1 = localB->inverseIMU_gain[1] * localP->FIR_IMUaccel_Coefficients
    [0];
  localB->cff = 1;
  localB->i = localDW->FIR_IMUaccel_circBuf;
  while (localB->i < 5) {
    localB->acc1 += localDW->FIR_IMUaccel_states[localB->i + 5] *
      localP->FIR_IMUaccel_Coefficients[localB->cff];
    localB->cff++;
    localB->i++;
  }

  localB->i = 0;
  while (localB->i < localDW->FIR_IMUaccel_circBuf) {
    localB->acc1 += localDW->FIR_IMUaccel_states[localB->i + 5] *
      localP->FIR_IMUaccel_Coefficients[localB->cff];
    localB->cff++;
    localB->i++;
  }

  localB->FIR_IMUaccel[1] = localB->acc1;
  localB->acc1 = localB->inverseIMU_gain[2] * localP->FIR_IMUaccel_Coefficients
    [0];
  localB->cff = 1;
  localB->i = localDW->FIR_IMUaccel_circBuf;
  while (localB->i < 5) {
    localB->acc1 += localDW->FIR_IMUaccel_states[localB->i + 10] *
      localP->FIR_IMUaccel_Coefficients[localB->cff];
    localB->cff++;
    localB->i++;
  }

  localB->i = 0;
  while (localB->i < localDW->FIR_IMUaccel_circBuf) {
    localB->acc1 += localDW->FIR_IMUaccel_states[localB->i + 10] *
      localP->FIR_IMUaccel_Coefficients[localB->cff];
    localB->cff++;
    localB->i++;
  }

  localB->FIR_IMUaccel[2] = localB->acc1;

  /* Gain: '<S315>/Gain2' */
  localB->single_b = localP->Gain2_Gain * localB->FIR_IMUaccel[0];

  /* Trigonometry: '<S315>/Trigonometric Function1' */
  if (localB->single_b > 1.0F) {
    localB->single_b = 1.0F;
  } else {
    if (localB->single_b < -1.0F) {
      localB->single_b = -1.0F;
    }
  }

  /* Trigonometry: '<S315>/Trigonometric Function1' */
  localB->TrigonometricFunction1 = asinf(localB->single_b);

  /* Reshape: '<S319>/Reshapey' */
  localB->rtb_Reshapey_d_b = localB->TrigonometricFunction1;

  /* Math: '<S318>/Math Function' incorporates:
   *  Constant: '<S318>/Constant'
   *  DataTypeConversion: '<S318>/Data Type Conversion2'
   *  DiscreteFir: '<S253>/FIR_IMUaccel'
   */
  localB->Abs = floorf(localP->Constant_Value_o);
  if ((localB->FIR_IMUaccel[0] < 0.0F) && (localP->Constant_Value_o >
       localB->Abs)) {
    localB->single_b = -rt_powf_snf(-localB->FIR_IMUaccel[0],
      localP->Constant_Value_o);
  } else {
    localB->single_b = rt_powf_snf(localB->FIR_IMUaccel[0],
      localP->Constant_Value_o);
  }

  if ((localB->FIR_IMUaccel[1] < 0.0F) && (localP->Constant_Value_o >
       localB->Abs)) {
    localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1 =
      -rt_powf_snf(-localB->FIR_IMUaccel[1], localP->Constant_Value_o);
  } else {
    localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1 = rt_powf_snf
      (localB->FIR_IMUaccel[1], localP->Constant_Value_o);
  }

  if ((localB->acc1 < 0.0F) && (localP->Constant_Value_o > localB->Abs)) {
    acc1 = -rt_powf_snf(-localB->acc1, localP->Constant_Value_o);
  } else {
    acc1 = rt_powf_snf(localB->acc1, localP->Constant_Value_o);
  }

  /* End of Math: '<S318>/Math Function' */

  /* Sqrt: '<S318>/Sqrt' incorporates:
   *  Sum: '<S318>/Sum of Elements'
   */
  localB->single_b = sqrtf((localB->single_b +
    localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1) + acc1);

  /* Logic: '<S252>/Logical Operator' incorporates:
   *  Constant: '<S313>/Constant'
   *  Constant: '<S314>/Constant'
   *  RelationalOperator: '<S313>/Compare'
   *  RelationalOperator: '<S314>/Compare'
   */
  localB->LogicalOperator = (int16_T)((localB->single_b >
    localP->CompareToConstant_const) && (localB->single_b <
    localP->CompareToConstant1_const));

  /* DataTypeConversion: '<S319>/DataTypeConversionEnable' */
  rtb_DataTypeConversionEnable = (localB->LogicalOperator != 0);

  /* DataTypeConversion: '<S363>/Conversion' incorporates:
   *  Constant: '<S320>/KalmanGainM'
   */
  localB->rtb_Conversion_a_n[0] = (real32_T)localP->KalmanGainM_Value[0];
  localB->rtb_Conversion_a_n[1] = (real32_T)localP->KalmanGainM_Value[1];

  /* Outputs for Enabled SubSystem: '<S346>/Enabled Subsystem' */
  /* Constant: '<S319>/C' */
  flightControlSystem_EnabledSubsystem(rtb_DataTypeConversionEnable,
    localB->rtb_Conversion_a_n, localP->C_Value_p, localB->rtb_Reshapey_d_b,
    localB->rtb_MemoryX_l_b, localB->Product2_n, &localDW->EnabledSubsystem_m,
    &localP->EnabledSubsystem_m);

  /* End of Outputs for SubSystem: '<S346>/Enabled Subsystem' */

  /* Sum: '<S346>/Add' */
  localB->single_b = localB->Product2_n[0] + localB->rtb_MemoryX_l_b[0];

  /* Delay: '<S371>/MemoryX' incorporates:
   *  Constant: '<S371>/X0'
   *  Reshape: '<S371>/ReshapeX0'
   */
  if (localDW->icLoad_m != 0) {
    localDW->MemoryX_DSTATE_g[0] = localP->X0_Value_f2[0];
    localDW->MemoryX_DSTATE_g[1] = localP->X0_Value_f2[1];
  }

  /* Delay: '<S371>/MemoryX' */
  localB->rtb_MemoryX_m_l[0] = localDW->MemoryX_DSTATE_g[0];
  localB->rtb_MemoryX_m_l[1] = localDW->MemoryX_DSTATE_g[1];

  /* Trigonometry: '<S316>/Trigonometric Function' incorporates:
   *  DiscreteFir: '<S253>/FIR_IMUaccel'
   *  Product: '<S316>/Divide'
   */
  localB->TrigonometricFunction = atanf(localB->FIR_IMUaccel[1] / localB->acc1);

  /* Reshape: '<S371>/Reshapey' */
  localB->rtb_Reshapey_o_j = localB->TrigonometricFunction;

  /* DataTypeConversion: '<S371>/DataTypeConversionEnable' */
  rtb_DataTypeConversionEnable_a = (localB->LogicalOperator != 0);

  /* DataTypeConversion: '<S415>/Conversion' incorporates:
   *  Constant: '<S372>/KalmanGainM'
   */
  localB->rtb_Conversion_g_o[0] = (real32_T)localP->KalmanGainM_Value_j[0];
  localB->rtb_Conversion_g_o[1] = (real32_T)localP->KalmanGainM_Value_j[1];

  /* Outputs for Enabled SubSystem: '<S398>/Enabled Subsystem' */
  /* Constant: '<S371>/C' */
  flightControlSystem_EnabledSubsystem(rtb_DataTypeConversionEnable_a,
    localB->rtb_Conversion_g_o, localP->C_Value_o, localB->rtb_Reshapey_o_j,
    localB->rtb_MemoryX_m_l, localB->Product2_p, &localDW->EnabledSubsystem_i,
    &localP->EnabledSubsystem_i);

  /* End of Outputs for SubSystem: '<S398>/Enabled Subsystem' */

  /* Sum: '<S398>/Add' */
  localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1 =
    localB->Product2_p[0] + localB->rtb_MemoryX_m_l[0];

  /* Trigonometry: '<S257>/sincos' incorporates:
   *  DiscreteIntegrator: '<S317>/Discrete-Time Integrator'
   *  MATLAB Function: '<S8>/Position error transformation (Earth to Body frame)'
   *  MATLABSystem: '<S239>/UAV Orbit Follower'
   *  Sum: '<S346>/Add'
   *  Sum: '<S398>/Add'
   *  Trigonometry: '<S438>/sincos'
   *  Trigonometry: '<S509>/sincos'
   */
  rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 = sinf
    (localDW->DiscreteTimeIntegrator_DSTATE);
  rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 = cosf
    (localDW->DiscreteTimeIntegrator_DSTATE);
  acc1 = sinf(localB->single_b);
  localB->Gain_h = cosf(localB->single_b);
  localB->rtb_sincos_o2_n_idx_1 = sinf
    (localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1);
  localB->Abs = cosf
    (localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1);

  /* Fcn: '<S257>/Fcn11' incorporates:
   *  Trigonometry: '<S257>/sincos'
   */
  localB->Reshape9to3x3columnmajor[0] = localB->Gain_h *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S257>/Fcn21' incorporates:
   *  Fcn: '<S257>/Fcn22'
   *  Trigonometry: '<S257>/sincos'
   */
  rtb_Reshape9to3x3columnmajor_tmp = localB->rtb_sincos_o2_n_idx_1 * acc1;
  localB->Reshape9to3x3columnmajor[1] = rtb_Reshape9to3x3columnmajor_tmp *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 -
    localB->Abs *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S257>/Fcn31' incorporates:
   *  Fcn: '<S257>/Fcn32'
   *  Trigonometry: '<S257>/sincos'
   */
  localB->DataTypeConversion2 = localB->Abs * acc1;
  localB->Reshape9to3x3columnmajor[2] = localB->DataTypeConversion2 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 +
    localB->rtb_sincos_o2_n_idx_1 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S257>/Fcn12' incorporates:
   *  Trigonometry: '<S257>/sincos'
   */
  localB->Reshape9to3x3columnmajor[3] = localB->Gain_h *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S257>/Fcn22' incorporates:
   *  Trigonometry: '<S257>/sincos'
   */
  localB->Reshape9to3x3columnmajor[4] = rtb_Reshape9to3x3columnmajor_tmp *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 +
    localB->Abs *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S257>/Fcn32' incorporates:
   *  Trigonometry: '<S257>/sincos'
   */
  localB->Reshape9to3x3columnmajor[5] = localB->DataTypeConversion2 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 -
    localB->rtb_sincos_o2_n_idx_1 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S257>/Fcn13' incorporates:
   *  Trigonometry: '<S257>/sincos'
   */
  localB->Reshape9to3x3columnmajor[6] = -acc1;

  /* Fcn: '<S257>/Fcn23' incorporates:
   *  Trigonometry: '<S257>/sincos'
   */
  localB->Reshape9to3x3columnmajor[7] = localB->rtb_sincos_o2_n_idx_1 *
    localB->Gain_h;

  /* Fcn: '<S257>/Fcn33' incorporates:
   *  Trigonometry: '<S257>/sincos'
   */
  localB->Reshape9to3x3columnmajor[8] = localB->Abs * localB->Gain_h;

  /* Fcn: '<S438>/Fcn11' */
  localB->Reshape9to3x3columnmajor_h[0] = localB->Gain_h *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S438>/Fcn21' incorporates:
   *  Fcn: '<S438>/Fcn22'
   */
  rtb_Reshape9to3x3columnmajor_tmp = localB->rtb_sincos_o2_n_idx_1 * acc1;
  localB->Reshape9to3x3columnmajor_h[1] = rtb_Reshape9to3x3columnmajor_tmp *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 -
    localB->Abs *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S438>/Fcn31' incorporates:
   *  Fcn: '<S438>/Fcn32'
   */
  localB->DataTypeConversion2 = localB->Abs * acc1;
  localB->Reshape9to3x3columnmajor_h[2] = localB->DataTypeConversion2 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 +
    localB->rtb_sincos_o2_n_idx_1 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S438>/Fcn12' */
  localB->Reshape9to3x3columnmajor_h[3] = localB->Gain_h *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S438>/Fcn22' */
  localB->Reshape9to3x3columnmajor_h[4] = rtb_Reshape9to3x3columnmajor_tmp *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 +
    localB->Abs *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S438>/Fcn32' */
  localB->Reshape9to3x3columnmajor_h[5] = localB->DataTypeConversion2 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 -
    localB->rtb_sincos_o2_n_idx_1 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S438>/Fcn13' */
  localB->Reshape9to3x3columnmajor_h[6] = -acc1;

  /* Fcn: '<S438>/Fcn23' */
  localB->Reshape9to3x3columnmajor_h[7] = localB->rtb_sincos_o2_n_idx_1 *
    localB->Gain_h;

  /* Fcn: '<S438>/Fcn33' */
  localB->Reshape9to3x3columnmajor_h[8] = localB->Abs * localB->Gain_h;

  /* Fcn: '<S509>/Fcn11' */
  localB->MathFunction_o[0] = localB->Gain_h *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S509>/Fcn21' incorporates:
   *  Fcn: '<S509>/Fcn22'
   */
  rtb_Reshape9to3x3columnmajor_tmp = localB->rtb_sincos_o2_n_idx_1 * acc1;
  localB->MathFunction_o[1] = rtb_Reshape9to3x3columnmajor_tmp *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 -
    localB->Abs *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S509>/Fcn31' incorporates:
   *  Fcn: '<S509>/Fcn32'
   */
  localB->DataTypeConversion2 = localB->Abs * acc1;
  localB->MathFunction_o[2] = localB->DataTypeConversion2 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 +
    localB->rtb_sincos_o2_n_idx_1 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S509>/Fcn12' */
  localB->MathFunction_o[3] = localB->Gain_h *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* Fcn: '<S509>/Fcn22' */
  localB->MathFunction_o[4] = rtb_Reshape9to3x3columnmajor_tmp *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 +
    localB->Abs *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S509>/Fcn32' */
  localB->MathFunction_o[5] = localB->DataTypeConversion2 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 -
    localB->rtb_sincos_o2_n_idx_1 *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* Fcn: '<S509>/Fcn13' */
  localB->MathFunction_o[6] = -acc1;

  /* Fcn: '<S509>/Fcn23' */
  localB->MathFunction_o[7] = localB->rtb_sincos_o2_n_idx_1 * localB->Gain_h;

  /* Fcn: '<S509>/Fcn33' */
  localB->MathFunction_o[8] = localB->Abs * localB->Gain_h;

  /* Math: '<S431>/Math Function' */
  for (localB->i = 0; localB->i < 3; localB->i++) {
    localB->rtb_MathFunction_o_c[3 * localB->i] = localB->MathFunction_o
      [localB->i];
    localB->rtb_MathFunction_o_c[3 * localB->i + 1] = localB->
      MathFunction_o[localB->i + 3];
    localB->rtb_MathFunction_o_c[3 * localB->i + 2] = localB->
      MathFunction_o[localB->i + 6];
  }

  for (localB->i = 0; localB->i < 9; localB->i++) {
    localB->MathFunction_o[localB->i] = localB->rtb_MathFunction_o_c[localB->i];
  }

  /* End of Math: '<S431>/Math Function' */
  for (localB->i = 0; localB->i < 8; localB->i++) {
    /* DataTypeConversion: '<S497>/Conversion' incorporates:
     *  Constant: '<S454>/KalmanGainM'
     */
    localB->rtb_Conversion_bc_c[localB->i] = (real32_T)
      localP->KalmanGainM_Value_c[localB->i];

    /* DataTypeConversion: '<S496>/Conversion' incorporates:
     *  Constant: '<S454>/KalmanGainL'
     */
    localB->rtb_Conversion_f_k[localB->i] = (real32_T)localP->
      KalmanGainL_Value[localB->i];
  }

  /* UnitDelay: '<S506>/Output' */
  localB->rtb_Output_c = localDW->Output_DSTATE;

  /* RelationalOperator: '<S258>/Compare' incorporates:
   *  Constant: '<S258>/Constant'
   *  Delay: '<S251>/Delay2'
   */
  localB->Compare = (localDW->Delay2_DSTATE > localP->outlierBelowFloor_const);

  /* Delay: '<S255>/MemoryX' incorporates:
   *  Constant: '<S255>/X0'
   *  DataTypeConversion: '<S255>/DataTypeConversionReset'
   *  Reshape: '<S255>/ReshapeX0'
   */
  if (localB->Compare) {
    localDW->icLoad_f = 1U;
  }

  if (localDW->icLoad_f != 0) {
    localDW->MemoryX_DSTATE[0] = localP->X0_Value[0];
    localDW->MemoryX_DSTATE[1] = localP->X0_Value[1];
  }

  /* Gain: '<S251>/invertzaxisGain' */
  localB->invertzaxisGain = (real_T)localP->invertzaxisGain_Gain *
    rtu_Sensors->HALSensors.HAL_ultrasound_SI.altitude;

  /* Saturate: '<S256>/SaturationSonar' */
  if (localB->invertzaxisGain > -flightControlSystem_P.Sensors.altSensorMin) {
    localB->Switch1_o = -flightControlSystem_P.Sensors.altSensorMin;
  } else if (localB->invertzaxisGain < localP->SaturationSonar_LowerSat) {
    localB->Switch1_o = localP->SaturationSonar_LowerSat;
  } else {
    localB->Switch1_o = localB->invertzaxisGain;
  }

  /* End of Saturate: '<S256>/SaturationSonar' */

  /* RelationalOperator: '<S311>/Compare' incorporates:
   *  Abs: '<S256>/Absestdiff'
   *  Constant: '<S311>/Constant'
   *  Delay: '<S251>/Delay2'
   *  Sum: '<S256>/Add'
   */
  rtb_Compare_l = (fabs(localDW->Delay2_DSTATE - localB->Switch1_o) <=
                   localP->outlierJump_const);

  /* DiscreteFilter: '<S256>/pressureFilter_IIR' incorporates:
   *  DataTypeConversion: '<S253>/Data Type Conversion'
   *  Gain: '<S251>/prsToAltGain'
   *  Sum: '<S253>/Sum2'
   */
  localDW->pressureFilter_IIR_tmp =
    ((((rtu_Sensors->HALSensors.HAL_pressure_SI.pressure -
        rtu_Sensors->SensorCalibration[6]) * localP->prsToAltGain_Gain -
       localP->pressureFilter_IIR_DenCoef[1] *
       localDW->pressureFilter_IIR_states[0]) -
      localP->pressureFilter_IIR_DenCoef[2] * localDW->
      pressureFilter_IIR_states[1]) - localP->pressureFilter_IIR_DenCoef[3] *
     localDW->pressureFilter_IIR_states[2]) / localP->
    pressureFilter_IIR_DenCoef[0];
  acc1 = ((localP->pressureFilter_IIR_NumCoef[0] *
           localDW->pressureFilter_IIR_tmp + localP->pressureFilter_IIR_NumCoef
           [1] * localDW->pressureFilter_IIR_states[0]) +
          localP->pressureFilter_IIR_NumCoef[2] *
          localDW->pressureFilter_IIR_states[1]) +
    localP->pressureFilter_IIR_NumCoef[3] * localDW->pressureFilter_IIR_states[2];

  /* RelationalOperator: '<S309>/Compare' incorporates:
   *  Abs: '<S256>/Absestdiff1'
   *  Constant: '<S309>/Constant'
   *  Delay: '<S251>/Delay2'
   *  DiscreteFilter: '<S256>/pressureFilter_IIR'
   *  Sum: '<S256>/Add1'
   */
  rtb_Compare_cy = (fabs(acc1 - localDW->Delay2_DSTATE) >=
                    localP->currentEstimateVeryOffFromPressure_const);

  /* DiscreteFilter: '<S256>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_tmp = (((localB->invertzaxisGain -
    localP->sonarFilter_IIR_DenCoef[1] * localDW->sonarFilter_IIR_states[0]) -
    localP->sonarFilter_IIR_DenCoef[2] * localDW->sonarFilter_IIR_states[1]) -
    localP->sonarFilter_IIR_DenCoef[3] * localDW->sonarFilter_IIR_states[2]) /
    localP->sonarFilter_IIR_DenCoef[0];

  /* Sum: '<S256>/Add2' incorporates:
   *  Delay: '<S251>/Delay2'
   *  DiscreteFilter: '<S256>/sonarFilter_IIR'
   */
  localDW->Delay2_DSTATE = (((localP->sonarFilter_IIR_NumCoef[0] *
    localDW->sonarFilter_IIR_tmp + localP->sonarFilter_IIR_NumCoef[1] *
    localDW->sonarFilter_IIR_states[0]) + localP->sonarFilter_IIR_NumCoef[2] *
    localDW->sonarFilter_IIR_states[1]) + localP->sonarFilter_IIR_NumCoef[3] *
    localDW->sonarFilter_IIR_states[2]) - localDW->Delay2_DSTATE;

  /* Abs: '<S256>/Absestdiff2' incorporates:
   *  Delay: '<S251>/Delay2'
   */
  localDW->Delay2_DSTATE = fabs(localDW->Delay2_DSTATE);

  /* Logic: '<S256>/nicemeasurementor newupdateneeded' incorporates:
   *  Constant: '<S308>/Constant'
   *  Constant: '<S310>/Constant'
   *  Delay: '<S251>/Delay2'
   *  Logic: '<S256>/NOT'
   *  Logic: '<S256>/findingoutliers'
   *  Logic: '<S256>/newupdateneeded'
   *  RelationalOperator: '<S308>/Compare'
   *  RelationalOperator: '<S310>/Compare'
   */
  localB->nicemeasurementornewupdateneeded = (rtb_Compare_l &&
    (localB->invertzaxisGain < -flightControlSystem_P.Sensors.altSensorMin) &&
    ((!rtb_Compare_cy) || (!(localDW->Delay2_DSTATE >=
    localP->currentStateVeryOffsonarflt_const))));

  /* DataTypeConversion: '<S255>/DataTypeConversionEnable' */
  rtb_DataTypeConversionEnable_j = localB->nicemeasurementornewupdateneeded;

  /* DataTypeConversion: '<S300>/Conversion' incorporates:
   *  Constant: '<S259>/KalmanGainM'
   */
  localB->rtb_Conversion_g1[0] = localP->KalmanGainM_Value_n[0];
  localB->rtb_Conversion_g1[1] = localP->KalmanGainM_Value_n[1];

  /* Outputs for Enabled SubSystem: '<S283>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S307>/Enable'
   */
  if (rtb_DataTypeConversionEnable_j) {
    localDW->EnabledSubsystem_MODE_m = true;

    /* Sum: '<S307>/Add1' incorporates:
     *  Constant: '<S255>/C'
     *  Delay: '<S255>/MemoryX'
     *  Product: '<S307>/Product'
     *  Reshape: '<S255>/Reshapey'
     */
    localB->Switch1_o = localB->invertzaxisGain - (localP->C_Value[0] *
      localDW->MemoryX_DSTATE[0] + localP->C_Value[1] * localDW->MemoryX_DSTATE
      [1]);

    /* Product: '<S307>/Product2' */
    localB->Product2[0] = localB->rtb_Conversion_g1[0] * localB->Switch1_o;
    localB->Product2[1] = localB->rtb_Conversion_g1[1] * localB->Switch1_o;
  } else {
    if (localDW->EnabledSubsystem_MODE_m) {
      /* Disable for Product: '<S307>/Product2' incorporates:
       *  Outport: '<S307>/deltax'
       */
      localB->Product2[0] = localP->deltax_Y0;
      localB->Product2[1] = localP->deltax_Y0;
      localDW->EnabledSubsystem_MODE_m = false;
    }
  }

  /* End of Outputs for SubSystem: '<S283>/Enabled Subsystem' */

  /* Reshape: '<S255>/Reshapexhat' incorporates:
   *  Delay: '<S255>/MemoryX'
   *  Sum: '<S283>/Add'
   */
  localB->Reshapexhat[0] = localB->Product2[0] + localDW->MemoryX_DSTATE[0];
  localB->Reshapexhat[1] = localB->Product2[1] + localDW->MemoryX_DSTATE[1];

  /* DataTypeConversion: '<S251>/Data Type Conversion' */
  rtb_DataTypeConversion = (real32_T)localB->Reshapexhat[0];

  /* Switch: '<S436>/Switch' incorporates:
   *  Constant: '<S505>/Constant'
   *  Gain: '<S436>/opticalFlowErrorCorrect'
   *  Product: '<S436>/ '
   *  RelationalOperator: '<S505>/Compare'
   */
  if (localB->rtb_Output_c < localP->CompareToConstant_const_d) {
    localB->Switch_d[0] = rtu_Sensors->VisionSensors.opticalFlow_data[0];
    localB->Switch_d[1] = rtu_Sensors->VisionSensors.opticalFlow_data[1];
    localB->Switch_d[2] = rtu_Sensors->VisionSensors.opticalFlow_data[2];
  } else {
    /* Gain: '<S436>/Gain' */
    localB->Gain_h = localP->Gain_Gain_d * rtb_DataTypeConversion;
    localB->Switch_d[0] = rtu_Sensors->VisionSensors.opticalFlow_data[0] *
      localB->Gain_h * localP->opticalFlowErrorCorrect_Gain;
    localB->Switch_d[1] = rtu_Sensors->VisionSensors.opticalFlow_data[1] *
      localB->Gain_h * localP->opticalFlowErrorCorrect_Gain;
    localB->Switch_d[2] = rtu_Sensors->VisionSensors.opticalFlow_data[2] *
      localB->Gain_h * localP->opticalFlowErrorCorrect_Gain;
  }

  /* End of Switch: '<S436>/Switch' */

  /* Abs: '<S433>/Abs' */
  localB->Abs = fabsf(rtb_DataTypeConversion);

  /* DiscreteTransferFcn: '<S253>/LPF Fcutoff = 40Hz1' */
  localDW->LPFFcutoff40Hz1_tmp = (localB->inverseIMU_gain[3] -
    localP->LPFFcutoff40Hz1_DenCoef[1] * localDW->LPFFcutoff40Hz1_states) /
    localP->LPFFcutoff40Hz1_DenCoef[0];

  /* DiscreteTransferFcn: '<S253>/LPF Fcutoff = 40Hz1' */
  localB->p = localP->LPFFcutoff40Hz1_NumCoef[0] * localDW->LPFFcutoff40Hz1_tmp
    + localP->LPFFcutoff40Hz1_NumCoef[1] * localDW->LPFFcutoff40Hz1_states;

  /* DiscreteTransferFcn: '<S253>/LPF Fcutoff = 40Hz' */
  localDW->LPFFcutoff40Hz_tmp = (localB->inverseIMU_gain[4] -
    localP->LPFFcutoff40Hz_DenCoef[1] * localDW->LPFFcutoff40Hz_states) /
    localP->LPFFcutoff40Hz_DenCoef[0];

  /* DiscreteTransferFcn: '<S253>/LPF Fcutoff = 40Hz' */
  localB->q = localP->LPFFcutoff40Hz_NumCoef[0] * localDW->LPFFcutoff40Hz_tmp +
    localP->LPFFcutoff40Hz_NumCoef[1] * localDW->LPFFcutoff40Hz_states;

  /* DiscreteFilter: '<S253>/IIR_IMUgyro_r' */
  rtb_Reshape9to3x3columnmajor_tmp = localB->inverseIMU_gain[5];
  localB->denIdx = 1;
  for (localB->i = 0; localB->i < 5; localB->i++) {
    rtb_Reshape9to3x3columnmajor_tmp -= localP->IIR_IMUgyro_r_DenCoef
      [localB->denIdx] * localDW->IIR_IMUgyro_r_states[localB->i];
    localB->denIdx++;
  }

  localDW->IIR_IMUgyro_r_tmp = rtb_Reshape9to3x3columnmajor_tmp /
    localP->IIR_IMUgyro_r_DenCoef[0];
  rtb_Reshape9to3x3columnmajor_tmp = localP->IIR_IMUgyro_r_NumCoef[0] *
    localDW->IIR_IMUgyro_r_tmp;
  localB->denIdx = 1;
  for (localB->i = 0; localB->i < 5; localB->i++) {
    rtb_Reshape9to3x3columnmajor_tmp += localP->IIR_IMUgyro_r_NumCoef
      [localB->denIdx] * localDW->IIR_IMUgyro_r_states[localB->i];
    localB->denIdx++;
  }

  /* UnitDelay: '<S426>/Output' */
  localB->rtb_Output_g_m = localDW->Output_DSTATE_o;

  /* RelationalOperator: '<S425>/Compare' incorporates:
   *  Constant: '<S425>/Constant'
   */
  rtb_Compare_l = (localB->rtb_Output_g_m == localP->CompareToConstant_const_n);

  /* Outputs for Triggered SubSystem: '<S423>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S427>/Trigger'
   */
  if (((localZCE->TriggeredSubsystem_Trig_ZCE == 1) != (int32_T)rtb_Compare_l) &&
      (localZCE->TriggeredSubsystem_Trig_ZCE != 3)) {
    /* Inport: '<S427>/In1' */
    localB->In1_f = rtu_Sensors->HALSensors.HAL_gyro_SI.temperature;
  }

  localZCE->TriggeredSubsystem_Trig_ZCE = rtb_Compare_l;

  /* End of Outputs for SubSystem: '<S423>/Triggered Subsystem' */

  /* ManualSwitch: '<S423>/Disable temperature compensation' incorporates:
   *  Constant: '<S423>/Constant'
   *  Gain: '<S423>/Gain'
   *  Sum: '<S423>/Subtract'
   */
  if (localP->Disabletemperaturecompensation_CurrentSetting == 1) {
    localB->Switch1_o = (rtu_Sensors->HALSensors.HAL_gyro_SI.temperature -
                         localB->In1_f) * localP->Gain_Gain_a;
  } else {
    localB->Switch1_o = localP->Constant_Value_g;
  }

  /* End of ManualSwitch: '<S423>/Disable temperature compensation' */

  /* Sum: '<S423>/Subtract1' incorporates:
   *  DataTypeConversion: '<S423>/Data Type Conversion1'
   *  DiscreteFilter: '<S253>/IIR_IMUgyro_r'
   */
  localB->r = rtb_Reshape9to3x3columnmajor_tmp - (real32_T)localB->Switch1_o;

  /* Sum: '<S252>/Subtract' incorporates:
   *  Sum: '<S346>/Add'
   *  Sum: '<S398>/Add'
   */
  localB->Gain_h = localB->p - (localB->Product2_p[1] + localB->rtb_MemoryX_m_l
    [1]);
  localB->rtb_sincos_o2_n_idx_1 = localB->q - (localB->Product2_n[1] +
    localB->rtb_MemoryX_l_b[1]);

  /* Sum: '<S430>/angular velocity compensation' incorporates:
   *  Gain: '<S433>/Gain1'
   *  Product: '<S433>/prod'
   */
  localB->angularvelocitycompensation[0] = localP->Gain1_Gain * (localB->Abs *
    localB->rtb_sincos_o2_n_idx_1) + localB->Switch_d[0];
  localB->angularvelocitycompensation[1] = localB->Switch_d[1] + localB->Abs *
    localB->Gain_h;

  /* SignalConversion generated from: '<S434>/IIRgyroz' */
  localB->Integrator_g[0] = localB->p;
  localB->Integrator_g[1] = localB->q;
  for (localB->cff = 0; localB->cff < 2; localB->cff++) {
    /* DiscreteFilter: '<S434>/IIRgyroz' */
    localB->memOffset = localB->cff * 5;
    rtb_Reshape9to3x3columnmajor_tmp = localB->Integrator_g[localB->cff];
    localB->denIdx = 1;
    for (localB->i = 0; localB->i < 5; localB->i++) {
      rtb_Reshape9to3x3columnmajor_tmp -= localDW->IIRgyroz_states
        [localB->memOffset + localB->i] * localP->IIRgyroz_DenCoef
        [localB->denIdx];
      localB->denIdx++;
    }

    localDW->IIRgyroz_tmp[localB->cff] = rtb_Reshape9to3x3columnmajor_tmp /
      localP->IIRgyroz_DenCoef[0];
    rtb_Reshape9to3x3columnmajor_tmp = localP->IIRgyroz_NumCoef[0] *
      localDW->IIRgyroz_tmp[localB->cff];
    localB->denIdx = 1;
    for (localB->i = 0; localB->i < 5; localB->i++) {
      rtb_Reshape9to3x3columnmajor_tmp += localDW->IIRgyroz_states
        [localB->memOffset + localB->i] * localP->IIRgyroz_NumCoef
        [localB->denIdx];
      localB->denIdx++;
    }

    /* SampleTimeMath: '<S442>/TSamp' incorporates:
     *  DiscreteFilter: '<S434>/IIRgyroz'
     *
     * About '<S442>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    localB->TSamp[localB->cff] = rtb_Reshape9to3x3columnmajor_tmp *
      localP->TSamp_WtEt;

    /* Sum: '<S442>/Diff' incorporates:
     *  UnitDelay: '<S442>/UD'
     *
     * Block description for '<S442>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S442>/UD':
     *
     *  Store in Global RAM
     */
    localB->rtb_Diff_b[localB->cff] = localB->TSamp[localB->cff] -
      localDW->UD_DSTATE[localB->cff];

    /* DiscreteFilter: '<S434>/IIRgyroz' incorporates:
     *  Delay: '<S430>/Delay'
     *  Sum: '<S434>/Add'
     */
    localB->IntegralGain_a[localB->cff] = localB->Switch_d[localB->cff] -
      localDW->Delay_DSTATE[localB->cff];
  }

  /* Abs: '<S434>/Abs' incorporates:
   *  Abs: '<S434>/Abs4'
   */
  localB->Abs = fabsf(localB->p);

  /* Abs: '<S434>/Abs1' incorporates:
   *  Abs: '<S434>/Abs5'
   */
  rtb_Reshape9to3x3columnmajor_tmp = fabsf(localB->q);

  /* Logic: '<S434>/Logical Operator3' incorporates:
   *  Abs: '<S434>/Abs'
   *  Abs: '<S434>/Abs1'
   *  Abs: '<S434>/Abs2'
   *  Abs: '<S434>/Abs3'
   *  Abs: '<S434>/Abs6'
   *  Abs: '<S434>/Abs7'
   *  Abs: '<S434>/Abs8'
   *  Abs: '<S434>/Abs9'
   *  Constant: '<S443>/Constant'
   *  Constant: '<S444>/Constant'
   *  Constant: '<S445>/Constant'
   *  Constant: '<S446>/Constant'
   *  Constant: '<S447>/Constant'
   *  Constant: '<S448>/Constant'
   *  Constant: '<S449>/Constant'
   *  Constant: '<S450>/Constant'
   *  Constant: '<S451>/Constant'
   *  Constant: '<S452>/Constant'
   *  Constant: '<S453>/Constant'
   *  Logic: '<S434>/Logical Operator'
   *  Logic: '<S434>/Logical Operator1'
   *  Logic: '<S434>/Logical Operator2'
   *  RelationalOperator: '<S443>/Compare'
   *  RelationalOperator: '<S444>/Compare'
   *  RelationalOperator: '<S445>/Compare'
   *  RelationalOperator: '<S446>/Compare'
   *  RelationalOperator: '<S447>/Compare'
   *  RelationalOperator: '<S448>/Compare'
   *  RelationalOperator: '<S449>/Compare'
   *  RelationalOperator: '<S450>/Compare'
   *  RelationalOperator: '<S451>/Compare'
   *  RelationalOperator: '<S452>/Compare'
   *  RelationalOperator: '<S453>/Compare'
   */
  localB->LogicalOperator3 = ((((fabsf(localB->single_b) <= localP->maxp_const) &&
    (fabsf(localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1) <=
     localP->maxq_const) && (localB->Abs <= localP->maxw1_const) &&
    (rtb_Reshape9to3x3columnmajor_tmp <= localP->maxw2_const) && (fabsf
    (localB->rtb_Diff_b[0]) <= localP->maxdw1_const) && (fabsf
    (localB->rtb_Diff_b[1]) <= localP->maxdw2_const)) || ((localB->Abs <=
    localP->maxp2_const) && (rtb_Reshape9to3x3columnmajor_tmp <=
    localP->maxq2_const))) && (fabsf(localB->IntegralGain_a[0]) <=
    localP->maxw3_const) && (fabsf(localB->IntegralGain_a[1]) <=
    localP->maxw4_const) && (rtb_DataTypeConversion <=
    localP->minHeightforOF_const));

  /* DataTypeConversion: '<S435>/DataTypeConversionEnable' */
  rtb_DataTypeConversionEnable_m = localB->LogicalOperator3;

  /* RelationalOperator: '<S437>/Compare' incorporates:
   *  Constant: '<S437>/Constant'
   */
  rtb_Compare_l = (rtb_DataTypeConversion <=
                   localP->DeactivateAccelerationIfOFisnotusedduetolowaltitude_const);

  /* Logic: '<S432>/Logical Operator' incorporates:
   *  Constant: '<S439>/Constant'
   *  Constant: '<S440>/Constant'
   *  RelationalOperator: '<S439>/Compare'
   *  RelationalOperator: '<S440>/Compare'
   */
  rtb_Compare_cy = ((localB->Switch_d[0] !=
                     localP->donotuseaccifopticalflowneveravailableNoteOF60HzbutZOHto200_con)
                    || (localB->Switch_d[1] !=
                        localP->donotuseaccifopticalflowneveravailableNoteOF60HzbutZOHto2001_co));

  /* Sum: '<S432>/Add' incorporates:
   *  Constant: '<S432>/gravity'
   *  Product: '<S432>/Product1'
   *  Reshape: '<S441>/Reshape (9) to [3x3] column-major'
   */
  for (localB->i = 0; localB->i < 3; localB->i++) {
    localB->rtb_FIR_IMUaccel_b[localB->i] = localB->FIR_IMUaccel[localB->i] -
      ((localB->Reshape9to3x3columnmajor_h[localB->i + 3] *
        localP->gravity_Value[1] + localB->Reshape9to3x3columnmajor_h[localB->i]
        * localP->gravity_Value[0]) + localB->Reshape9to3x3columnmajor_h
       [localB->i + 6] * localP->gravity_Value[2]);
  }

  /* End of Sum: '<S432>/Add' */

  /* Product: '<S432>/Product' incorporates:
   *  Gain: '<S432>/gainaccinput1'
   */
  localB->Product[0] = (real32_T)(localP->gainaccinput1_Gain *
    localB->rtb_FIR_IMUaccel_b[0]) * (real32_T)rtb_Compare_cy * (real32_T)
    rtb_Compare_l;
  localB->Product[1] = (real32_T)(localP->gainaccinput1_Gain *
    localB->rtb_FIR_IMUaccel_b[1]) * (real32_T)rtb_Compare_cy * (real32_T)
    rtb_Compare_l;

  /* Delay: '<S435>/MemoryX' incorporates:
   *  Constant: '<S435>/X0'
   *  Reshape: '<S435>/ReshapeX0'
   */
  if (localDW->icLoad_a != 0) {
    localDW->MemoryX_DSTATE_d[0] = localP->X0_Value_d[0];
    localDW->MemoryX_DSTATE_d[1] = localP->X0_Value_d[1];
    localDW->MemoryX_DSTATE_d[2] = localP->X0_Value_d[2];
    localDW->MemoryX_DSTATE_d[3] = localP->X0_Value_d[3];
  }

  /* DataTypeConversion: '<S469>/Conversion' incorporates:
   *  Delay: '<S435>/MemoryX'
   */
  localB->rtb_Conversion_e_f[0] = localDW->MemoryX_DSTATE_d[0];
  localB->rtb_Conversion_e_f[1] = localDW->MemoryX_DSTATE_d[1];
  localB->rtb_Conversion_e_f[2] = localDW->MemoryX_DSTATE_d[2];
  localB->rtb_Conversion_e_f[3] = localDW->MemoryX_DSTATE_d[3];

  /* Outputs for Enabled SubSystem: '<S473>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S502>/Enable'
   */
  if (rtb_DataTypeConversionEnable_m) {
    localDW->MeasurementUpdate_MODE = true;

    /* Product: '<S502>/C[k]*xhat[k|k-1]' incorporates:
     *  Constant: '<S435>/C'
     */
    for (localB->i = 0; localB->i < 2; localB->i++) {
      localB->Abs = localP->C_Value_c[localB->i + 6] *
        localB->rtb_Conversion_e_f[3] + (localP->C_Value_c[localB->i + 4] *
        localB->rtb_Conversion_e_f[2] + (localP->C_Value_c[localB->i + 2] *
        localB->rtb_Conversion_e_f[1] + localP->C_Value_c[localB->i] *
        localB->rtb_Conversion_e_f[0]));
      localB->IntegralGain_a[localB->i] = localB->Abs;
    }

    /* End of Product: '<S502>/C[k]*xhat[k|k-1]' */

    /* Sum: '<S502>/Sum' incorporates:
     *  Constant: '<S435>/D'
     *  Product: '<S502>/D[k]*u[k]'
     *  Reshape: '<S435>/Reshapeu'
     *  Reshape: '<S435>/Reshapey'
     *  Sum: '<S502>/Add1'
     */
    localB->Abs = localB->angularvelocitycompensation[0] - ((localP->D_Value_o[0]
      * localB->Product[0] + localP->D_Value_o[2] * localB->Product[1]) +
      localB->IntegralGain_a[0]);
    localB->distToCenter = localB->angularvelocitycompensation[1] -
      ((localP->D_Value_o[1] * localB->Product[0] + localP->D_Value_o[3] *
        localB->Product[1]) + localB->IntegralGain_a[1]);
    for (localB->i = 0; localB->i < 4; localB->i++) {
      /* Product: '<S502>/Product3' incorporates:
       *  DataTypeConversion: '<S496>/Conversion'
       */
      localB->Product3_a[localB->i] = 0.0F;
      localB->Product3_a[localB->i] += localB->rtb_Conversion_f_k[localB->i] *
        localB->Abs;
      localB->Product3_a[localB->i] += localB->rtb_Conversion_f_k[localB->i + 4]
        * localB->distToCenter;
    }
  } else {
    if (localDW->MeasurementUpdate_MODE) {
      /* Disable for Product: '<S502>/Product3' incorporates:
       *  Outport: '<S502>/L*(y[k]-yhat[k|k-1])'
       */
      localB->Product3_a[0] = localP->Lykyhatkk1_Y0_f;
      localB->Product3_a[1] = localP->Lykyhatkk1_Y0_f;
      localB->Product3_a[2] = localP->Lykyhatkk1_Y0_f;
      localB->Product3_a[3] = localP->Lykyhatkk1_Y0_f;
      localDW->MeasurementUpdate_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<S473>/MeasurementUpdate' */

  /* Product: '<S473>/B[k]*u[k]' incorporates:
   *  Constant: '<S435>/B'
   *  Reshape: '<S435>/Reshapeu'
   */
  for (localB->i = 0; localB->i < 4; localB->i++) {
    localB->fv[localB->i] = localP->B_Value_g[localB->i + 4] * localB->Product[1]
      + localP->B_Value_g[localB->i] * localB->Product[0];
  }

  /* End of Product: '<S473>/B[k]*u[k]' */
  for (localB->i = 0; localB->i < 4; localB->i++) {
    /* Product: '<S473>/A[k]*xhat[k|k-1]' incorporates:
     *  Constant: '<S435>/A'
     */
    localB->Abs = localP->A_Value_g[localB->i + 12] * localB->
      rtb_Conversion_e_f[3] + (localP->A_Value_g[localB->i + 8] *
      localB->rtb_Conversion_e_f[2] + (localP->A_Value_g[localB->i + 4] *
      localB->rtb_Conversion_e_f[1] + localP->A_Value_g[localB->i] *
      localB->rtb_Conversion_e_f[0]));

    /* Reshape: '<S473>/Reshape' incorporates:
     *  Sum: '<S473>/Add'
     */
    localB->Reshape_l[localB->i] = (localB->fv[localB->i] + localB->Abs) +
      localB->Product3_a[localB->i];
  }

  /* Outputs for Enabled SubSystem: '<S480>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S504>/Enable'
   */
  if (rtb_DataTypeConversionEnable_m) {
    localDW->EnabledSubsystem_MODE = true;

    /* Sum: '<S504>/Add1' incorporates:
     *  Constant: '<S435>/C'
     *  Delay: '<S435>/MemoryX'
     *  Product: '<S504>/Product'
     *  Reshape: '<S435>/Reshapey'
     */
    for (localB->i = 0; localB->i < 2; localB->i++) {
      localB->IntegralGain_a[localB->i] = localB->
        angularvelocitycompensation[localB->i] - (((localP->C_Value_c[localB->i
        + 2] * localDW->MemoryX_DSTATE_d[1] + localP->C_Value_c[localB->i] *
        localDW->MemoryX_DSTATE_d[0]) + localP->C_Value_c[localB->i + 4] *
        localDW->MemoryX_DSTATE_d[2]) + localP->C_Value_c[localB->i + 6] *
        localDW->MemoryX_DSTATE_d[3]);
    }

    /* End of Sum: '<S504>/Add1' */
    for (localB->i = 0; localB->i < 4; localB->i++) {
      /* Product: '<S504>/Product2' incorporates:
       *  DataTypeConversion: '<S497>/Conversion'
       */
      localB->Product2_k[localB->i] = 0.0F;
      localB->Product2_k[localB->i] += localB->rtb_Conversion_bc_c[localB->i] *
        localB->IntegralGain_a[0];
      localB->Product2_k[localB->i] += localB->rtb_Conversion_bc_c[localB->i + 4]
        * localB->IntegralGain_a[1];
    }
  } else {
    if (localDW->EnabledSubsystem_MODE) {
      /* Disable for Product: '<S504>/Product2' incorporates:
       *  Outport: '<S504>/deltax'
       */
      localB->Product2_k[0] = localP->deltax_Y0_l;
      localB->Product2_k[1] = localP->deltax_Y0_l;
      localB->Product2_k[2] = localP->deltax_Y0_l;
      localB->Product2_k[3] = localP->deltax_Y0_l;
      localDW->EnabledSubsystem_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<S480>/Enabled Subsystem' */

  /* Reshape: '<S435>/Reshapexhat' incorporates:
   *  Delay: '<S435>/MemoryX'
   *  Sum: '<S480>/Add'
   */
  localB->Reshapexhat_d[0] = localB->Product2_k[0] + localDW->MemoryX_DSTATE_d[0];
  localB->Reshapexhat_d[1] = localB->Product2_k[1] + localDW->MemoryX_DSTATE_d[1];
  localB->Reshapexhat_d[2] = localB->Product2_k[2] + localDW->MemoryX_DSTATE_d[2];
  localB->Reshapexhat_d[3] = localB->Product2_k[3] + localDW->MemoryX_DSTATE_d[3];

  /* DiscreteIntegrator: '<S431>/SimplyIntegrateVelocity' incorporates:
   *  Constant: '<S1>/controlModePosVsOrient'
   */
  if (localP->controlModePosVsOrient_Value &&
      (localDW->SimplyIntegrateVelocity_PrevResetState <= 0)) {
    localDW->SimplyIntegrateVelocity_DSTATE[0] =
      localP->SimplyIntegrateVelocity_IC;
    localDW->SimplyIntegrateVelocity_DSTATE[1] =
      localP->SimplyIntegrateVelocity_IC;
  }

  /* DiscreteIntegrator: '<S431>/SimplyIntegrateVelocity' */
  localB->SimplyIntegrateVelocity[0] = localDW->SimplyIntegrateVelocity_DSTATE[0];
  localB->SimplyIntegrateVelocity[1] = localDW->SimplyIntegrateVelocity_DSTATE[1];

  /* UnitDelay: '<S245>/Output' */
  localB->rtb_Output_l_n = localDW->Output_DSTATE_a;

  /* RelationalOperator: '<S246>/Compare' incorporates:
   *  Constant: '<S246>/Constant'
   */
  rtb_Compare_l = (localB->rtb_Output_l_n > localP->Wait5seconds_const);

  /* Outputs for Enabled SubSystem: '<S238>/Waypoint follower' incorporates:
   *  EnablePort: '<S247>/Enable'
   */
  if (rtb_Compare_l) {
    /* MATLABSystem: '<S247>/UAV Waypoint Follower' incorporates:
     *  Constant: '<S247>/Look ahead distance'
     *  Constant: '<S247>/Waypoints'
     *  DataTypeConversion: '<S247>/Data Type  Conversion3'
     *  DiscreteIntegrator: '<S317>/Discrete-Time Integrator'
     */
    localB->rtb_DataTypeConversion3_idx_2 = localP->Lookaheaddistance_Value;
    localDW->obj.LookaheadDistFlag = 0U;
    if (localP->Lookaheaddistance_Value < 0.1) {
      localB->rtb_DataTypeConversion3_idx_2 = 0.1;
      localDW->obj.LookaheadDistFlag = 1U;
    }

    localDW->obj.InitialPose[0] = 0.0;
    localDW->obj.InitialPose[1] = 0.0;
    localDW->obj.InitialPose[2] = 0.0;
    localDW->obj.InitialPose[3] = 0.0;
    rtb_Compare_cy = false;
    p = true;
    localB->i = 0;
    exitg1 = false;
    while ((!exitg1) && (localB->i < 16)) {
      if ((localDW->obj.WaypointsInternal[localB->i] ==
           flightControlSystem_P.puntosObjetivo[localB->i]) || (rtIsNaN
           (localDW->obj.WaypointsInternal[localB->i]) && rtIsNaN
           (flightControlSystem_P.puntosObjetivo[localB->i]))) {
        localB->i++;
      } else {
        p = false;
        exitg1 = true;
      }
    }

    if (p) {
      rtb_Compare_cy = true;
    }

    if (!rtb_Compare_cy) {
      memcpy(&localDW->obj.WaypointsInternal[0],
             &flightControlSystem_P.puntosObjetivo[0], sizeof(real_T) << 4U);
      localDW->obj.WaypointIndex = 1.0;
    }

    localB->dv[3] = (rtNaN);
    localB->dv[7] = (rtNaN);
    localB->dv[11] = (rtNaN);
    for (localB->i = 0; localB->i < 3; localB->i++) {
      localB->cff = localB->i << 2;
      localB->Switch1_o = flightControlSystem_P.puntosObjetivo[localB->cff + 1];
      localB->dv[localB->cff] = localB->Switch1_o;
      localB->rtb_DataTypeConversion3_idx_1 =
        flightControlSystem_P.puntosObjetivo[localB->cff + 2];
      localB->dv[localB->cff + 1] = localB->rtb_DataTypeConversion3_idx_1;
      localB->rtb_DataTypeConversion3_idx_3 =
        flightControlSystem_P.puntosObjetivo[localB->cff + 3];
      localB->dv[localB->cff + 2] = localB->rtb_DataTypeConversion3_idx_3;
      localB->x[localB->cff] = (flightControlSystem_P.puntosObjetivo[localB->cff]
        != localB->dv[localB->cff]);
      localB->x[localB->cff + 1] = (localB->Switch1_o != localB->dv[localB->cff
        + 1]);
      localB->x[localB->cff + 2] = (localB->rtb_DataTypeConversion3_idx_1 !=
        localB->dv[localB->cff + 2]);
      localB->x[localB->cff + 3] = (localB->rtb_DataTypeConversion3_idx_3 !=
        localB->dv[localB->cff + 3]);
    }

    localB->b_l[0] = false;
    localB->b_l[1] = false;
    localB->b_l[2] = false;
    localB->b_l[3] = false;
    localB->i = 1;
    exitg1 = false;
    while ((!exitg1) && (localB->i <= 9)) {
      if (!localB->x[localB->i - 1]) {
        localB->i += 4;
      } else {
        localB->b_l[0] = true;
        exitg1 = true;
      }
    }

    localB->i = 2;
    exitg1 = false;
    while ((!exitg1) && (localB->i <= 10)) {
      if (!localB->x[localB->i - 1]) {
        localB->i += 4;
      } else {
        localB->b_l[1] = true;
        exitg1 = true;
      }
    }

    localB->i = 3;
    exitg1 = false;
    while ((!exitg1) && (localB->i <= 11)) {
      if (!localB->x[localB->i - 1]) {
        localB->i += 4;
      } else {
        localB->b_l[2] = true;
        exitg1 = true;
      }
    }

    localB->i = 4;
    exitg1 = false;
    while ((!exitg1) && (localB->i <= 12)) {
      if (!localB->x[localB->i - 1]) {
        localB->i += 4;
      } else {
        localB->b_l[3] = true;
        exitg1 = true;
      }
    }

    localB->cff = 0;
    localB->memOffset = 0;
    for (localB->i = 0; localB->i < 4; localB->i++) {
      if (localB->b_l[localB->i]) {
        localB->cff++;
        localB->c_data[localB->memOffset] = localB->i + 1;
        localB->memOffset++;
      }
    }

    for (localB->i = 0; localB->i < localB->cff; localB->i++) {
      localB->memOffset = localB->c_data[localB->i];
      localB->b_waypointsIn_data[localB->i] =
        flightControlSystem_P.puntosObjetivo[localB->memOffset - 1];
      localB->b_waypointsIn_data[localB->i + localB->cff] =
        flightControlSystem_P.puntosObjetivo[localB->memOffset + 3];
    }

    for (localB->i = 0; localB->i < localB->cff; localB->i++) {
      localB->b_waypointsIn_data[localB->i + (localB->cff << 1)] =
        flightControlSystem_P.puntosObjetivo[localB->c_data[localB->i] + 7];
    }

    for (localB->i = 0; localB->i < localB->cff; localB->i++) {
      localB->b_waypointsIn_data[localB->i + localB->cff * 3] =
        flightControlSystem_P.puntosObjetivo[localB->c_data[localB->i] + 11];
    }

    localDW->obj.NumWaypoints = localB->cff;
    localDW->obj.LookaheadDistance = localB->rtb_DataTypeConversion3_idx_2;
    if (localB->cff == 0) {
      localB->dist = localB->SimplyIntegrateVelocity[0];
      localB->b = localB->SimplyIntegrateVelocity[1];
      localB->y = rtb_DataTypeConversion;
      localB->UAVWaypointFollower_o3 = localDW->DiscreteTimeIntegrator_DSTATE;
      status = 1U;
    } else {
      guard1 = false;
      if (localB->cff == 1) {
        if (localDW->obj.StartFlag) {
          localDW->obj.InitialPose[0] = localB->SimplyIntegrateVelocity[0];
          localDW->obj.InitialPose[1] = localB->SimplyIntegrateVelocity[1];
          localDW->obj.InitialPose[2] = rtb_DataTypeConversion;
          localDW->obj.InitialPose[3] = localDW->DiscreteTimeIntegrator_DSTATE;
        }

        localB->rtb_FIR_IMUaccel_b[0] = localB->b_waypointsIn_data[0] -
          localB->SimplyIntegrateVelocity[0];
        localB->rtb_FIR_IMUaccel_b[1] = localB->b_waypointsIn_data[1] -
          localB->SimplyIntegrateVelocity[1];
        localB->rtb_FIR_IMUaccel_b[2] = localB->b_waypointsIn_data[2] -
          rtb_DataTypeConversion;
        if (flightControlSystem_norm_da(localB->rtb_FIR_IMUaccel_b, localB) <
            1.4901161193847656E-8) {
          localB->dist = localB->SimplyIntegrateVelocity[0];
          localB->b = localB->SimplyIntegrateVelocity[1];
          localB->y = rtb_DataTypeConversion;
          localB->UAVWaypointFollower_o3 =
            localDW->DiscreteTimeIntegrator_DSTATE;
          status = 1U;
          localDW->obj.StartFlag = false;
        } else {
          localDW->obj.StartFlag = false;
          localB->appendedWaypoints_data[0] = localDW->obj.InitialPose[0];
          localB->appendedWaypoints_data[2] = localDW->obj.InitialPose[1];
          localB->appendedWaypoints_data[4] = localDW->obj.InitialPose[2];
          localB->appendedWaypoints_data[6] =
            flightControlSystem_P.puntosObjetivo[localB->c_data[0] + 11];
          if (0 <= localB->cff - 1) {
            memcpy(&localB->appendedWaypoints_data[1],
                   &localB->b_waypointsIn_data[0], localB->cff * sizeof(real_T));
          }

          for (localB->i = 0; localB->i < localB->cff; localB->i++) {
            localB->appendedWaypoints_data[localB->i + 3] =
              localB->b_waypointsIn_data[localB->i + localB->cff];
          }

          for (localB->i = 0; localB->i < localB->cff; localB->i++) {
            localB->appendedWaypoints_data[localB->i + 5] =
              localB->b_waypointsIn_data[(localB->cff << 1) + localB->i];
          }

          for (localB->i = 0; localB->i < localB->cff; localB->i++) {
            localB->appendedWaypoints_data[localB->i + 7] =
              localB->b_waypointsIn_data[localB->cff * 3 + localB->i];
          }

          localDW->obj.NumWaypoints = 2.0;
          localB->i = 2;
          localB->cff = ((localB->cff + 1) << 2) - 1;
          if (0 <= localB->cff) {
            memcpy(&localB->waypoints_data[0], &localB->appendedWaypoints_data[0],
                   (localB->cff + 1) * sizeof(real_T));
          }

          guard1 = true;
        }
      } else {
        localB->i = localB->cff;
        localB->cff = (localB->cff << 2) - 1;
        if (0 <= localB->cff) {
          memcpy(&localB->waypoints_data[0], &localB->b_waypointsIn_data[0],
                 (localB->cff + 1) * sizeof(real_T));
        }

        guard1 = true;
      }

      if (guard1) {
        if (flightControlSystem_isequal(localDW->obj.WaypointIndex,
             localDW->obj.NumWaypoints)) {
          localDW->obj.LastWaypointFlag = true;
          localDW->obj.WaypointIndex--;
        }

        localDW->obj.InitYaw = localB->waypoints_data[(localB->i * 3 + (int32_T)
          localDW->obj.WaypointIndex) - 1];
        localDW->obj.FinalYaw = localB->waypoints_data[((int32_T)
          (localDW->obj.WaypointIndex + 1.0) + localB->i * 3) - 1];
        localB->Switch1[0] = localB->SimplyIntegrateVelocity[0] -
          localB->waypoints_data[(int32_T)(localDW->obj.WaypointIndex + 1.0) - 1];
        localB->Switch1[1] = localB->SimplyIntegrateVelocity[1] -
          localB->waypoints_data[((int32_T)(localDW->obj.WaypointIndex + 1.0) +
          localB->i) - 1];
        localB->cff = localB->i << 1;
        localB->Switch1[2] = rtb_DataTypeConversion - localB->waypoints_data
          [((int32_T)(localDW->obj.WaypointIndex + 1.0) + localB->cff) - 1];
        localB->Switch1_o = flightControlSystem_norm_da(localB->Switch1, localB);
        guard2 = false;
        if (localB->Switch1_o <= 0.2) {
          guard2 = true;
        } else {
          localB->rtb_FIR_IMUaccel_b[0] = localB->waypoints_data[(int32_T)
            (localDW->obj.WaypointIndex + 1.0) - 1] - localB->waypoints_data
            [(int32_T)localDW->obj.WaypointIndex - 1];
          localB->rtb_FIR_IMUaccel_b[1] = localB->waypoints_data[((int32_T)
            (localDW->obj.WaypointIndex + 1.0) + localB->i) - 1] -
            localB->waypoints_data[((int32_T)localDW->obj.WaypointIndex +
            localB->i) - 1];
          localB->rtb_FIR_IMUaccel_b[2] = localB->waypoints_data[((int32_T)
            (localDW->obj.WaypointIndex + 1.0) + localB->cff) - 1] -
            localB->waypoints_data[(localB->cff + (int32_T)
            localDW->obj.WaypointIndex) - 1];
          localB->rtb_DataTypeConversion3_idx_1 = flightControlSystem_norm_da
            (localB->rtb_FIR_IMUaccel_b, localB);
          localB->Switch1_o = ((localB->waypoints_data[((int32_T)
            (localDW->obj.WaypointIndex + 1.0) + localB->i) - 1] -
                                localB->waypoints_data[((int32_T)
            localDW->obj.WaypointIndex + localB->i) - 1]) /
                               localB->rtb_DataTypeConversion3_idx_1 *
                               (localB->Switch1[1] / localB->Switch1_o) +
                               (localB->waypoints_data[(int32_T)
                                (localDW->obj.WaypointIndex + 1.0) - 1] -
                                localB->waypoints_data[(int32_T)
                                localDW->obj.WaypointIndex - 1]) /
                               localB->rtb_DataTypeConversion3_idx_1 *
                               (localB->Switch1[0] / localB->Switch1_o)) +
            (localB->waypoints_data[((int32_T)(localDW->obj.WaypointIndex + 1.0)
              + localB->cff) - 1] - localB->waypoints_data[(localB->cff +
              (int32_T)localDW->obj.WaypointIndex) - 1]) /
            localB->rtb_DataTypeConversion3_idx_1 * (localB->Switch1[2] /
            localB->Switch1_o);
          if (localB->Switch1_o < 0.0) {
            localB->Switch1_o = -1.0;
          } else if (localB->Switch1_o > 0.0) {
            localB->Switch1_o = 1.0;
          } else if (localB->Switch1_o == 0.0) {
            localB->Switch1_o = 0.0;
          } else {
            localB->Switch1_o = (rtNaN);
          }

          if (localB->Switch1_o >= 0.0) {
            guard2 = true;
          } else {
            localB->Switch1[0] = localB->waypoints_data[(int32_T)
              localDW->obj.WaypointIndex - 1];
            localB->Switch1_o = localB->waypoints_data[(int32_T)
              (localDW->obj.WaypointIndex + 1.0) - 1];
            localB->Switch1[1] = localB->waypoints_data[((int32_T)
              localDW->obj.WaypointIndex + localB->i) - 1];
            localB->rtb_DataTypeConversion3_idx_1 = localB->waypoints_data
              [((int32_T)(localDW->obj.WaypointIndex + 1.0) + localB->i) - 1];
            localB->Switch1[2] = localB->waypoints_data[((localB->i << 1) +
              (int32_T)localDW->obj.WaypointIndex) - 1];
            localB->rtb_DataTypeConversion3_idx_2 = localB->waypoints_data
              [((int32_T)(localDW->obj.WaypointIndex + 1.0) + (localB->i << 1))
              - 1];
          }
        }

        if (guard2) {
          localDW->obj.WaypointIndex++;
          if (flightControlSystem_isequal(localDW->obj.WaypointIndex,
               localDW->obj.NumWaypoints)) {
            localDW->obj.LastWaypointFlag = true;
            localDW->obj.WaypointIndex--;
          }

          localDW->obj.InitYaw = localB->waypoints_data[(localB->i * 3 +
            (int32_T)localDW->obj.WaypointIndex) - 1];
          localDW->obj.FinalYaw = localB->waypoints_data[((int32_T)
            (localDW->obj.WaypointIndex + 1.0) + localB->i * 3) - 1];
          localB->Switch1[0] = localB->waypoints_data[(int32_T)
            localDW->obj.WaypointIndex - 1];
          localB->Switch1_o = localB->waypoints_data[(int32_T)
            (localDW->obj.WaypointIndex + 1.0) - 1];
          localB->Switch1[1] = localB->waypoints_data[((int32_T)
            localDW->obj.WaypointIndex + localB->i) - 1];
          localB->rtb_DataTypeConversion3_idx_1 = localB->waypoints_data
            [((int32_T)(localDW->obj.WaypointIndex + 1.0) + localB->i) - 1];
          localB->Switch1[2] = localB->waypoints_data[(localB->cff + (int32_T)
            localDW->obj.WaypointIndex) - 1];
          localB->rtb_DataTypeConversion3_idx_2 = localB->waypoints_data
            [((int32_T)(localDW->obj.WaypointIndex + 1.0) + localB->cff) - 1];
        }

        localB->lambda_tmp_tmp = localB->Switch1_o - localB->Switch1[0];
        localB->rtb_DataTypeConversion3_tmp = localB->SimplyIntegrateVelocity[0]
          - localB->Switch1[0];
        localB->rtb_FIR_IMUaccel_b[0] = localB->rtb_DataTypeConversion3_tmp;
        localB->rtb_DataTypeConversion3_p[0] = localB->SimplyIntegrateVelocity[0]
          - localB->Switch1_o;
        localB->rtb_DataTypeConversion3_idx_3 =
          localB->rtb_DataTypeConversion3_idx_1 - localB->Switch1[1];
        localB->rtb_DataTypeConversion3_tmp_n = localB->SimplyIntegrateVelocity
          [1] - localB->Switch1[1];
        localB->rtb_FIR_IMUaccel_b[1] = localB->rtb_DataTypeConversion3_tmp_n;
        localB->rtb_DataTypeConversion3_p[1] = localB->SimplyIntegrateVelocity[1]
          - localB->rtb_DataTypeConversion3_idx_1;
        localB->lambda_tmp_tmp_p = localB->rtb_DataTypeConversion3_idx_2 -
          localB->Switch1[2];
        localB->dist = rtb_DataTypeConversion - localB->Switch1[2];
        localB->rtb_DataTypeConversion3_tmp_l = localB->dist *
          localB->lambda_tmp_tmp_p;
        localB->rtb_FIR_IMUaccel_b[2] = localB->dist;
        localB->rtb_DataTypeConversion3_p[2] = rtb_DataTypeConversion -
          localB->rtb_DataTypeConversion3_idx_2;
        localB->lambda = (localB->rtb_DataTypeConversion3_tmp_l +
                          (localB->rtb_DataTypeConversion3_tmp_n *
                           localB->rtb_DataTypeConversion3_idx_3 +
                           localB->rtb_DataTypeConversion3_tmp *
                           localB->lambda_tmp_tmp)) / (localB->lambda_tmp_tmp_p *
          localB->lambda_tmp_tmp_p + (localB->rtb_DataTypeConversion3_idx_3 *
          localB->rtb_DataTypeConversion3_idx_3 + localB->lambda_tmp_tmp *
          localB->lambda_tmp_tmp));
        localB->rtb_DataTypeConversion3_c[0] = localB->SimplyIntegrateVelocity[0]
          - (localB->lambda_tmp_tmp * localB->lambda + localB->Switch1[0]);
        localB->rtb_DataTypeConversion3_c[1] = localB->SimplyIntegrateVelocity[1]
          - (localB->rtb_DataTypeConversion3_idx_3 * localB->lambda +
             localB->Switch1[1]);
        localB->rtb_DataTypeConversion3_c[2] = rtb_DataTypeConversion -
          (localB->lambda_tmp_tmp_p * localB->lambda + localB->Switch1[2]);
        if (localB->lambda < 0.0) {
          localB->dist = flightControlSystem_norm_da(localB->rtb_FIR_IMUaccel_b,
            localB);
        } else if (localB->lambda > 1.0) {
          localB->dist = flightControlSystem_norm_da
            (localB->rtb_DataTypeConversion3_p, localB);
        } else {
          localB->dist = flightControlSystem_norm_da
            (localB->rtb_DataTypeConversion3_c, localB);
        }

        if (localDW->obj.LastWaypointFlag) {
          localB->lambda = (((localB->SimplyIntegrateVelocity[0] -
                              localB->Switch1[0]) * (localB->Switch1_o -
            localB->Switch1[0]) + (localB->SimplyIntegrateVelocity[1] -
            localB->Switch1[1]) * (localB->rtb_DataTypeConversion3_idx_1 -
            localB->Switch1[1])) + (rtb_DataTypeConversion - localB->Switch1[2])
                            * (localB->rtb_DataTypeConversion3_idx_2 -
                               localB->Switch1[2])) / (((localB->Switch1_o -
            localB->Switch1[0]) * (localB->Switch1_o - localB->Switch1[0]) +
            (localB->rtb_DataTypeConversion3_idx_1 - localB->Switch1[1]) *
            (localB->rtb_DataTypeConversion3_idx_1 - localB->Switch1[1])) +
            (localB->rtb_DataTypeConversion3_idx_2 - localB->Switch1[2]) *
            (localB->rtb_DataTypeConversion3_idx_2 - localB->Switch1[2]));
          localB->rtb_FIR_IMUaccel_b[0] = localB->SimplyIntegrateVelocity[0] -
            (localB->lambda * localB->lambda_tmp_tmp + localB->Switch1[0]);
          localB->rtb_FIR_IMUaccel_b[1] = localB->SimplyIntegrateVelocity[1] -
            (localB->lambda * localB->rtb_DataTypeConversion3_idx_3 +
             localB->Switch1[1]);
          localB->rtb_FIR_IMUaccel_b[2] = rtb_DataTypeConversion -
            (localB->lambda * localB->lambda_tmp_tmp_p + localB->Switch1[2]);
          localB->dist = flightControlSystem_norm_da(localB->rtb_FIR_IMUaccel_b,
            localB);
        }

        localB->y = fabs(localB->dist);
        if ((!rtIsInf(localB->y)) && (!rtIsNaN(localB->y))) {
          if (localB->y <= 2.2250738585072014E-308) {
            localB->b = 4.94065645841247E-324;
            localB->y = 4.94065645841247E-324;
          } else {
            frexp(localB->y, &localB->b_exponent_a);
            localB->b = ldexp(1.0, localB->b_exponent_a - 53);
            frexp(localB->y, &localB->b_exponent_j);
            localB->y = ldexp(1.0, localB->b_exponent_j - 53);
          }
        } else {
          localB->b = (rtNaN);
          localB->y = (rtNaN);
        }

        if (localDW->obj.LookaheadDistance <= fmax(sqrt(localB->b), 5.0 *
             localB->y) + localB->dist) {
          localDW->obj.LookaheadDistance = localDW->obj.LookaheadFactor *
            localB->dist;
        }

        localB->y = localB->Switch1[0] - localB->SimplyIntegrateVelocity[0];
        localB->lambda = localB->Switch1[1] - localB->SimplyIntegrateVelocity[1];
        localB->dist = ((localB->Switch1_o - localB->Switch1[0]) *
                        (localB->Switch1_o - localB->Switch1[0]) +
                        (localB->rtb_DataTypeConversion3_idx_1 - localB->
                         Switch1[1]) * (localB->rtb_DataTypeConversion3_idx_1 -
          localB->Switch1[1])) + (localB->rtb_DataTypeConversion3_idx_2 -
          localB->Switch1[2]) * (localB->rtb_DataTypeConversion3_idx_2 -
          localB->Switch1[2]);
        localB->r_idx_2_tmp = localB->Switch1[2] - rtb_DataTypeConversion;
        localB->b = ((localB->lambda_tmp_tmp * localB->y +
                      localB->rtb_DataTypeConversion3_idx_3 * localB->lambda) +
                     localB->lambda_tmp_tmp_p * localB->r_idx_2_tmp) * 2.0;
        localB->y = sqrt(localB->b * localB->b - (((localB->y * localB->y +
          localB->lambda * localB->lambda) + localB->r_idx_2_tmp *
          localB->r_idx_2_tmp) - localDW->obj.LookaheadDistance *
          localDW->obj.LookaheadDistance) * (4.0 * localB->dist));
        localB->y = fmax((-localB->b + localB->y) / 2.0 / localB->dist,
                         (-localB->b - localB->y) / 2.0 / localB->dist);
        localB->dist = (1.0 - localB->y) * localB->Switch1[0] + localB->y *
          localB->Switch1_o;
        localB->b = (1.0 - localB->y) * localB->Switch1[1] + localB->y *
          localB->rtb_DataTypeConversion3_idx_1;
        localB->y = (1.0 - localB->y) * localB->Switch1[2] + localB->y *
          localB->rtb_DataTypeConversion3_idx_2;
        localB->lambda = ((localB->rtb_DataTypeConversion3_tmp *
                           localB->lambda_tmp_tmp +
                           localB->rtb_DataTypeConversion3_tmp_n *
                           localB->rtb_DataTypeConversion3_idx_3) +
                          localB->rtb_DataTypeConversion3_tmp_l) /
          (((localB->Switch1_o - localB->Switch1[0]) * (localB->Switch1_o -
             localB->Switch1[0]) + (localB->rtb_DataTypeConversion3_idx_1 -
             localB->Switch1[1]) * (localB->rtb_DataTypeConversion3_idx_1 -
             localB->Switch1[1])) + (localB->rtb_DataTypeConversion3_idx_2 -
            localB->Switch1[2]) * (localB->rtb_DataTypeConversion3_idx_2 -
            localB->Switch1[2]));
        rtb_Compare_cy = (localB->lambda < 0.0);
        p = (localB->lambda > 1.0);
        if (rtb_Compare_cy) {
          localB->lambda_tmp_tmp = localB->Switch1[0];
        } else if (p) {
          localB->lambda_tmp_tmp = localB->Switch1_o;
        } else {
          localB->lambda_tmp_tmp = localB->lambda_tmp_tmp * localB->lambda +
            localB->Switch1[0];
        }

        localB->rtb_FIR_IMUaccel_b[0] = localB->lambda_tmp_tmp - localB->
          Switch1[0];
        localB->rtb_DataTypeConversion3_p[0] = localB->Switch1[0] -
          localB->Switch1_o;
        if (rtb_Compare_cy) {
          localB->lambda_tmp_tmp = localB->Switch1[1];
        } else if (p) {
          localB->lambda_tmp_tmp = localB->rtb_DataTypeConversion3_idx_1;
        } else {
          localB->lambda_tmp_tmp = localB->rtb_DataTypeConversion3_idx_3 *
            localB->lambda + localB->Switch1[1];
        }

        localB->rtb_FIR_IMUaccel_b[1] = localB->lambda_tmp_tmp - localB->
          Switch1[1];
        localB->rtb_DataTypeConversion3_p[1] = localB->Switch1[1] -
          localB->rtb_DataTypeConversion3_idx_1;
        if (rtb_Compare_cy) {
          localB->lambda = localB->Switch1[2];
        } else if (p) {
          localB->lambda = localB->rtb_DataTypeConversion3_idx_2;
        } else {
          localB->lambda = localB->lambda_tmp_tmp_p * localB->lambda +
            localB->Switch1[2];
        }

        localB->rtb_FIR_IMUaccel_b[2] = localB->lambda - localB->Switch1[2];
        localB->rtb_DataTypeConversion3_p[2] = localB->Switch1[2] -
          localB->rtb_DataTypeConversion3_idx_2;
        localB->UAVWaypointFollower_o3 = flightControlSystem_wrapToPi
          (flightControlSystem_norm_da(localB->rtb_FIR_IMUaccel_b, localB) /
           flightControlSystem_norm_da(localB->rtb_DataTypeConversion3_p, localB)
           * flightControlSystem_wrapToPi(localDW->obj.FinalYaw -
            localDW->obj.InitYaw, localB) + localDW->obj.InitYaw, localB);
        if (fabs(localB->UAVWaypointFollower_o3 - -3.1415926535897931) <
            1.4901161193847656E-8) {
          localB->UAVWaypointFollower_o3 = 3.1415926535897931;
        }

        status = 0U;
        rtb_Compare_cy = false;
        if (localDW->obj.LastWaypointFlag) {
          rtb_Compare_cy = true;
        }

        if (rtb_Compare_cy) {
          status = 1U;
        }

        localDW->obj.LastWaypointFlag = false;
      }
    }

    /* DataTypeConversion: '<S247>/Data Type  Conversion' incorporates:
     *  MATLABSystem: '<S247>/UAV Waypoint Follower'
     */
    localB->DataTypeConversion[0] = (real32_T)localB->dist;
    localB->DataTypeConversion[1] = (real32_T)localB->b;
    localB->DataTypeConversion[2] = (real32_T)localB->y;

    /* Outputs for Triggered SubSystem: '<S247>/Latch the status' incorporates:
     *  TriggerPort: '<S250>/Trigger'
     */
    /* MATLABSystem: '<S247>/UAV Waypoint Follower' incorporates:
     *  Constant: '<S247>/Constant'
     *  Inport: '<S250>/In1'
     */
    if ((status > 0) && (localZCE->Latchthestatus_Trig_ZCE != 1)) {
      localB->In1 = localP->Constant_Value;
    }

    localZCE->Latchthestatus_Trig_ZCE = (ZCSigState)(status > 0);

    /* End of Outputs for SubSystem: '<S247>/Latch the status' */
  }

  /* End of Outputs for SubSystem: '<S238>/Waypoint follower' */

  /* MATLABSystem: '<S239>/UAV Orbit Follower' incorporates:
   *  Constant: '<S239>/ Center'
   *  Constant: '<S239>/Clockwise Orbit'
   *  Constant: '<S239>/Lookahead Distance'
   *  Constant: '<S239>/Orbit Radius'
   *  DiscreteIntegrator: '<S317>/Discrete-Time Integrator'
   *  SignalConversion generated from: '<S239>/UAV Orbit Follower'
   */
  localB->DataTypeConversion2 = localP->OrbitRadius_Value;
  localDW->obj_f.OrbitRadiusFlag = 0U;
  if (localP->OrbitRadius_Value <= 1.0F) {
    localB->DataTypeConversion2 = 1.0F;
    localDW->obj_f.OrbitRadiusFlag = 1U;
  }

  localB->distToCenter = localP->LookaheadDistance_Value;
  localDW->obj_f.LookaheadDistFlag = 0U;
  if (localP->LookaheadDistance_Value < 0.1) {
    localB->distToCenter = 0.1F;
    localDW->obj_f.LookaheadDistFlag = 1U;
  }

  localB->Abs = localB->SimplyIntegrateVelocity[0] - localP->Center_Value_e[0];
  localB->IntegralGain_a[0] = localB->Abs;
  rtb_Reshape9to3x3columnmajor_tmp = localB->SimplyIntegrateVelocity[1] -
    localP->Center_Value_e[1];
  localB->IntegralGain_a[1] = rtb_Reshape9to3x3columnmajor_tmp;
  if (flightControlSystem_norm(localB->IntegralGain_a) < 2.47032822920623E-323)
  {
    localB->Switch_d[0] = localB->DataTypeConversion2 *
      rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 +
      localB->SimplyIntegrateVelocity[0];
    localB->Switch_d[1] = localB->DataTypeConversion2 *
      rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 +
      localB->SimplyIntegrateVelocity[1];
    localB->Switch_d[2] = localP->Center_Value_e[2];
    localB->Abs = localDW->DiscreteTimeIntegrator_DSTATE;
    localB->Switch1_o = localDW->obj_f.NumCircles;
  } else {
    rtb_Compare_cy = false;
    p = true;
    localB->i = 0;
    exitg1 = false;
    while ((!exitg1) && (localB->i < 3)) {
      if ((localDW->obj_f.OrbitCenterInternal[localB->i] ==
           localP->Center_Value_e[localB->i]) || (rtIsNaNF
           (localDW->obj_f.OrbitCenterInternal[localB->i]) && rtIsNaNF
           (localP->Center_Value_e[localB->i]))) {
        localB->i++;
      } else {
        p = false;
        exitg1 = true;
      }
    }

    if (p) {
      rtb_Compare_cy = true;
    }

    guard1 = false;
    if (!rtb_Compare_cy) {
      guard1 = true;
    } else {
      rtb_Compare_cy = false;
      if ((localDW->obj_f.OrbitRadiusInternal == localB->DataTypeConversion2) ||
          (rtIsNaNF(localDW->obj_f.OrbitRadiusInternal) && rtIsNaNF
           (localB->DataTypeConversion2))) {
        rtb_Compare_cy = true;
      }

      if (!rtb_Compare_cy) {
        guard1 = true;
      }
    }

    if (guard1) {
      localDW->obj_f.NumCircles = 0.0;
      localDW->obj_f.OrbitCenterInternal[0] = localP->Center_Value_e[0];
      localDW->obj_f.OrbitCenterInternal[1] = localP->Center_Value_e[1];
      localDW->obj_f.OrbitCenterInternal[2] = localP->Center_Value_e[2];
      localDW->obj_f.OrbitRadiusInternal = localB->DataTypeConversion2;
      localDW->obj_f.SelectTurnDirectionFlag = true;
    }

    if (localB->distToCenter >= localB->DataTypeConversion2) {
      localDW->obj_f.LookaheadDistance = 0.9F * localB->DataTypeConversion2;
    } else {
      localDW->obj_f.LookaheadDistance = localB->distToCenter;
    }

    localB->xyLookaheadPoint[0] = localB->Abs;
    localB->xyLookaheadPoint[1] = rtb_Reshape9to3x3columnmajor_tmp;
    localB->distToCenter = sqrtf(rtb_Reshape9to3x3columnmajor_tmp *
      rtb_Reshape9to3x3columnmajor_tmp + localB->Abs * localB->Abs);
    localB->y2 = localB->DataTypeConversion2 + localDW->obj_f.LookaheadDistance;
    localB->x2 = fabsf(localB->y2);
    rtb_Compare_cy = !rtIsInfF(localB->x2);
    p = !rtIsNaNF(localB->x2);
    if (rtb_Compare_cy && p) {
      if (localB->x2 <= 1.17549435E-38F) {
        localB->b_h = 1.4013E-45F;
      } else {
        frexpf(localB->x2, &localB->b_exponent);
        localB->b_h = ldexpf(1.0F, localB->b_exponent - 24);
      }
    } else {
      localB->b_h = (rtNaNF);
    }

    guard1 = false;
    if (localB->distToCenter >= localB->y2 - 5.0F * localB->b_h) {
      guard1 = true;
    } else {
      if (rtb_Compare_cy && p) {
        if (localB->x2 <= 1.17549435E-38F) {
          localB->b_h = 1.4013E-45F;
        } else {
          frexpf(localB->x2, &localB->b_exponent_f);
          localB->b_h = ldexpf(1.0F, localB->b_exponent_f - 24);
        }
      } else {
        localB->b_h = (rtNaNF);
      }

      if (localB->distToCenter <= (localB->DataTypeConversion2 -
           localDW->obj_f.LookaheadDistance) + 5.0F * localB->b_h) {
        guard1 = true;
      } else {
        if (localDW->obj_f.StartFlag) {
          localDW->obj_f.PrevPosition[0] = localB->SimplyIntegrateVelocity[0];
          localDW->obj_f.PrevPosition[1] = localB->SimplyIntegrateVelocity[1];
          localDW->obj_f.StartFlag = false;
        }

        localB->IntegralGain_a[0] = localB->Abs;
        localB->IntegralGain_a[1] = rtb_Reshape9to3x3columnmajor_tmp;
        localB->d = flightControlSystem_norm(localB->IntegralGain_a);
        localB->b_h = localDW->obj_f.LookaheadDistance *
          localDW->obj_f.LookaheadDistance;
        localB->a = ((localB->b_h - localB->DataTypeConversion2 *
                      localB->DataTypeConversion2) + localB->d * localB->d) /
          (2.0F * localB->d);
        localB->DataTypeConversion2 = localP->Center_Value_e[0] -
          localB->SimplyIntegrateVelocity[0];
        localB->x2 = localB->DataTypeConversion2 * localB->a / localB->d +
          localB->SimplyIntegrateVelocity[0];
        localB->distToCenter = localP->Center_Value_e[1] -
          localB->SimplyIntegrateVelocity[1];
        localB->y2 = localB->distToCenter * localB->a / localB->d +
          localB->SimplyIntegrateVelocity[1];
        localB->a = sqrtf(localB->b_h - localB->a * localB->a);
        localB->turnInternal = localB->distToCenter * localB->a / localB->d;
        localB->b_h = localB->x2 - localB->turnInternal;
        localB->x2 += localB->turnInternal;
        localB->a = localB->DataTypeConversion2 * localB->a / localB->d;
        localB->d = localB->a + localB->y2;
        localB->a = localB->y2 - localB->a;
        if ((localP->ClockwiseOrbit_Value == 0.0F) &&
            (!localDW->obj_f.SelectTurnDirectionFlag)) {
          localB->turnInternal = (real32_T)localDW->obj_f.TurnDirectionInternal;
        } else {
          localB->turnInternal = localP->ClockwiseOrbit_Value;
        }

        localB->y2 = localDW->obj_f.PrevPosition[0] - localP->Center_Value_e[0];
        turnVector_idx_1 = localDW->obj_f.PrevPosition[1] -
          localP->Center_Value_e[1];
        localB->Switch_d[0] = localB->y2;
        localB->Switch_d[1] = turnVector_idx_1;
        localB->Switch_d[2] = 0.0F;
        localB->sincos_o2[0] = localB->Abs;
        localB->sincos_o2[1] = rtb_Reshape9to3x3columnmajor_tmp;
        localB->sincos_o2[2] = 0.0F;
        if (localB->turnInternal < 0.0F) {
          localB->Switch_d[0] = localB->Abs;
          localB->sincos_o2[0] = localB->y2;
          localB->Switch_d[1] = rtb_Reshape9to3x3columnmajor_tmp;
          localB->sincos_o2[1] = turnVector_idx_1;
          localB->Switch_d[2] = 0.0F;
          localB->sincos_o2[2] = 0.0F;
          localB->turnInternal = -1.0F;
        } else if (localB->turnInternal > 0.0F) {
          localB->turnInternal = 1.0F;
        } else if (localB->turnInternal == 0.0F) {
          localB->turnInternal = 0.0F;
        } else {
          localB->turnInternal = (rtNaNF);
        }

        localB->y2 = flightControlSystem_norm_d(localB->Switch_d);
        rtb_Reshape9to3x3columnmajor_tmp = flightControlSystem_norm_d
          (localB->sincos_o2);
        localB->Switch_d[0] /= localB->y2;
        localB->sincos_o2[0] /= rtb_Reshape9to3x3columnmajor_tmp;
        localB->Switch_d[1] /= localB->y2;
        localB->sincos_o2[1] /= rtb_Reshape9to3x3columnmajor_tmp;
        localB->Abs = localB->Switch_d[0] * localB->sincos_o2[1] -
          localB->Switch_d[1] * localB->sincos_o2[0];
        rtb_Reshape9to3x3columnmajor_tmp = (localB->Switch_d[0] *
          localB->sincos_o2[0] + localB->Switch_d[1] * localB->sincos_o2[1]) +
          0.0F / localB->y2 * (0.0F / rtb_Reshape9to3x3columnmajor_tmp);
        localDW->obj_f.PrevPosition[0] = localB->SimplyIntegrateVelocity[0];
        localDW->obj_f.PrevPosition[1] = localB->SimplyIntegrateVelocity[1];
        localDW->obj_f.PrevPosition[2] = rtb_DataTypeConversion;
        localDW->obj_f.NumCircles += rt_atan2f_snf(localB->Abs,
          rtb_Reshape9to3x3columnmajor_tmp) / 2.0F / 3.14159274F;
        localB->Switch1_o = localDW->obj_f.NumCircles;
        switch ((int32_T)localB->turnInternal) {
         case 1:
          if ((localB->b_h - localB->SimplyIntegrateVelocity[0]) *
              localB->distToCenter - (localB->d -
               localB->SimplyIntegrateVelocity[1]) * localB->DataTypeConversion2
              > 0.0F) {
            localB->xyLookaheadPoint[0] = localB->b_h;
            localB->xyLookaheadPoint[1] = localB->d;
          } else {
            localB->xyLookaheadPoint[0] = localB->x2;
            localB->xyLookaheadPoint[1] = localB->a;
          }
          break;

         case -1:
          if ((localB->b_h - localB->SimplyIntegrateVelocity[0]) *
              localB->distToCenter - (localB->d -
               localB->SimplyIntegrateVelocity[1]) * localB->DataTypeConversion2
              < 0.0F) {
            localB->xyLookaheadPoint[0] = localB->b_h;
            localB->xyLookaheadPoint[1] = localB->d;
          } else {
            localB->xyLookaheadPoint[0] = localB->x2;
            localB->xyLookaheadPoint[1] = localB->a;
          }
          break;

         default:
          if (fabsf(flightControlSystem_angdiff(rt_atan2f_snf(localB->d -
                 localB->SimplyIntegrateVelocity[1], localB->b_h -
                 localB->SimplyIntegrateVelocity[0]),
                localDW->DiscreteTimeIntegrator_DSTATE)) < fabsf
              (flightControlSystem_angdiff(rt_atan2f_snf(localB->a -
                 localB->SimplyIntegrateVelocity[1], localB->x2 -
                 localB->SimplyIntegrateVelocity[0]),
                localDW->DiscreteTimeIntegrator_DSTATE))) {
            localB->xyLookaheadPoint[0] = localB->b_h;
            localB->xyLookaheadPoint[1] = localB->d;
          } else {
            localB->xyLookaheadPoint[0] = localB->x2;
            localB->xyLookaheadPoint[1] = localB->a;
          }

          if ((localB->xyLookaheadPoint[0] - localB->SimplyIntegrateVelocity[0])
              * localB->distToCenter - (localB->xyLookaheadPoint[1] -
               localB->SimplyIntegrateVelocity[1]) * localB->DataTypeConversion2
              > 0.0F) {
            localDW->obj_f.TurnDirectionInternal = 1.0;
          } else {
            localDW->obj_f.TurnDirectionInternal = -1.0;
          }

          localDW->obj_f.SelectTurnDirectionFlag = false;
          break;
        }

        localB->Abs = rt_atan2f_snf(localB->distToCenter,
          localB->DataTypeConversion2);
      }
    }

    if (guard1) {
      localB->y2 = flightControlSystem_norm(localB->xyLookaheadPoint);
      localB->xyLookaheadPoint[0] = localB->Abs / localB->y2 *
        localB->DataTypeConversion2 + localP->Center_Value_e[0];
      localB->Abs = rtb_Reshape9to3x3columnmajor_tmp / localB->y2 *
        localB->DataTypeConversion2 + localP->Center_Value_e[1];
      localB->xyLookaheadPoint[1] = localB->Abs;
      localB->Abs = rt_atan2f_snf(localB->Abs - localB->SimplyIntegrateVelocity
        [1], localB->xyLookaheadPoint[0] - localB->SimplyIntegrateVelocity[0]);
      localB->Switch1_o = localDW->obj_f.NumCircles;
    }

    localB->Switch_d[0] = localB->xyLookaheadPoint[0];
    localB->Switch_d[1] = localB->xyLookaheadPoint[1];
    localB->Switch_d[2] = localP->Center_Value_e[2];
  }

  /* RelationalOperator: '<S240>/Compare' incorporates:
   *  Constant: '<S240>/Constant'
   *  MATLABSystem: '<S239>/UAV Orbit Follower'
   */
  rtb_Compare_cy = (localB->Switch1_o > localP->Completefourcircles_const);

  /* Outputs for Triggered SubSystem: '<S239>/Latch the status' incorporates:
   *  TriggerPort: '<S241>/Trigger'
   */
  if (rtb_Compare_cy && (localZCE->Latchthestatus_Trig_ZCE_d != 1)) {
    /* Inport: '<S241>/In1' incorporates:
     *  Constant: '<S239>/Clockwise Orbit1'
     */
    localB->In1_j = localP->ClockwiseOrbit1_Value;
  }

  localZCE->Latchthestatus_Trig_ZCE_d = rtb_Compare_cy;

  /* End of Outputs for SubSystem: '<S239>/Latch the status' */

  /* Sum: '<S239>/Sum' incorporates:
   *  Constant: '<S239>/Clockwise Orbit2'
   *  MATLABSystem: '<S239>/UAV Orbit Follower'
   */
  localB->Abs -= localP->ClockwiseOrbit2_Value;

  /* MATLAB Function: '<S239>/MATLAB Function' incorporates:
   *  DiscreteIntegrator: '<S317>/Discrete-Time Integrator'
   */
  if (localB->Abs < -1.0F) {
    localB->Abs += 6.28318548F;
  }

  if ((localDW->DiscreteTimeIntegrator_DSTATE > 5.15) && (localB->Abs < 0.0F)) {
    localB->Abs = 5.28F;
  }

  /* End of MATLAB Function: '<S239>/MATLAB Function' */

  /* Switch: '<S5>/Switch1' incorporates:
   *  Constant: '<S5>/opMode'
   *  MATLABSystem: '<S239>/UAV Orbit Follower'
   *  Switch: '<S235>/Switch2'
   */
  if (flightControlSystem_P.modoOperacion > localP->Switch1_Threshold_n) {
    /* Switch: '<S238>/Switch1' incorporates:
     *  Constant: '<S238>/Final Point'
     *  Constant: '<S238>/Startup Waypoints'
     *  Switch: '<S238>/Switch'
     */
    if (localB->In1 > localP->Switch1_Threshold) {
      localB->Switch1[0] = flightControlSystem_P.puntoFinal[0];
      localB->Switch1[1] = flightControlSystem_P.puntoFinal[1];
      localB->Switch1[2] = flightControlSystem_P.puntoFinal[2];
    } else if (rtb_Compare_l) {
      /* Switch: '<S238>/Switch' incorporates:
       *  DataTypeConversion: '<S247>/Data Type  Conversion'
       *  Switch: '<S238>/Switch1'
       */
      localB->Switch1[0] = localB->DataTypeConversion[0];
      localB->Switch1[1] = localB->DataTypeConversion[1];
      localB->Switch1[2] = localB->DataTypeConversion[2];
    } else {
      localB->Switch1[0] = localP->StartupWaypoints_Value[0];
      localB->Switch1[1] = localP->StartupWaypoints_Value[1];
      localB->Switch1[2] = localP->StartupWaypoints_Value[2];
    }

    /* End of Switch: '<S238>/Switch1' */
    localB->Switch1_o = localB->Switch1[0];
    localB->rtb_DataTypeConversion3_idx_1 = localB->Switch1[1];
    localB->rtb_DataTypeConversion3_idx_2 = localB->Switch1[2];

    /* Switch: '<S238>/Switch2' incorporates:
     *  Constant: '<S238>/Final Yaw'
     *  Switch: '<S5>/Switch1'
     */
    if (localB->In1 > localP->Switch2_Threshold) {
      localB->rtb_DataTypeConversion3_idx_3 = flightControlSystem_P.yawFinal;
    } else {
      localB->rtb_DataTypeConversion3_idx_3 = localB->UAVWaypointFollower_o3;
    }

    /* End of Switch: '<S238>/Switch2' */
  } else if (localB->In1_j > localP->Switch2_Threshold_e) {
    /* Switch: '<S235>/Switch2' incorporates:
     *  Constant: '<S235>/ Center'
     *  Constant: '<S235>/yaw'
     *  Switch: '<S5>/Switch1'
     */
    localB->Switch1_o = localP->Center_Value[0];
    localB->rtb_DataTypeConversion3_idx_1 = localP->Center_Value[1];
    localB->rtb_DataTypeConversion3_idx_2 = localP->Center_Value[2];
    localB->rtb_DataTypeConversion3_idx_3 = localP->yaw_Value;
  } else {
    localB->Switch1_o = localB->Switch_d[0];
    localB->rtb_DataTypeConversion3_idx_1 = localB->Switch_d[1];
    localB->rtb_DataTypeConversion3_idx_2 = localB->Switch_d[2];
    localB->rtb_DataTypeConversion3_idx_3 = localB->Abs;
  }

  /* End of Switch: '<S5>/Switch1' */

  /* Logic: '<S236>/OR' incorporates:
   *  BusAssignment: '<S1>/Control Mode Update'
   *  Constant: '<S243>/Constant'
   *  RelationalOperator: '<S243>/Compare'
   */
  rtb_Compare_l = ((rtu_ReferenceValueServerCmds->time_remaining <=
                    localP->ComparewithStoptime_const) ||
                   rtu_ReferenceValueServerCmds->land_drone);

  /* SignalConversion generated from: '<S251>/Product1' incorporates:
   *  Delay: '<S6>/Delay1'
   */
  localB->lambda_tmp_tmp_p = localDW->Delay1_DSTATE[0];
  localB->lambda_tmp_tmp = localDW->Delay1_DSTATE[1];
  localB->rtb_DataTypeConversion3_tmp = localB->Reshapexhat[1];

  /* Product: '<S251>/Product1' incorporates:
   *  Reshape: '<S312>/Reshape (9) to [3x3] column-major'
   */
  for (localB->i = 0; localB->i < 3; localB->i++) {
    localB->rtb_FIR_IMUaccel_b[localB->i] = localB->
      Reshape9to3x3columnmajor[localB->i + 6] *
      localB->rtb_DataTypeConversion3_tmp + (localB->
      Reshape9to3x3columnmajor[localB->i + 3] * localB->lambda_tmp_tmp +
      localB->Reshape9to3x3columnmajor[localB->i] * localB->lambda_tmp_tmp_p);
  }

  /* End of Product: '<S251>/Product1' */

  /* DataTypeConversion: '<S251>/Data Type Conversion2' */
  localB->DataTypeConversion2 = (real32_T)localB->rtb_FIR_IMUaccel_b[2];

  /* Outputs for Triggered SubSystem: '<S237>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S244>/Trigger'
   */
  if (rtb_Compare_l && (localZCE->TriggeredSubsystem_Trig_ZCE_k != 1)) {
    /* SignalConversion generated from: '<S244>/X' */
    localB->BufferToMakeInportVirtual_InsertedFor_X_at_inport_0 =
      localB->SimplyIntegrateVelocity[0];

    /* SignalConversion generated from: '<S244>/Y' */
    localB->BufferToMakeInportVirtual_InsertedFor_Y_at_inport_0 =
      localB->SimplyIntegrateVelocity[1];
  }

  localZCE->TriggeredSubsystem_Trig_ZCE_k = rtb_Compare_l;

  /* End of Outputs for SubSystem: '<S237>/Triggered Subsystem' */

  /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
   *  Constant: '<S237>/Landing look-ahead distance'
   *  Logic: '<S5>/NOT'
   *  Sum: '<S237>/Add'
   */
  if (rtb_Compare_l) {
    localB->Switch1[0] =
      localB->BufferToMakeInportVirtual_InsertedFor_X_at_inport_0;
    localB->Switch1[1] =
      localB->BufferToMakeInportVirtual_InsertedFor_Y_at_inport_0;
    localB->Switch1[2] = rtb_DataTypeConversion +
      localP->Landinglookaheaddistance_Value;
  } else {
    localB->Switch1[0] = localB->Switch1_o;
    localB->Switch1[1] = localB->rtb_DataTypeConversion3_idx_1;
    localB->Switch1[2] = localB->rtb_DataTypeConversion3_idx_2;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch' */

  /* BusAssignment: '<S5>/Bus  Assignment1' incorporates:
   *  BusAssignment: '<S1>/Control Mode Update'
   *  Constant: '<S1>/controlModePosVsOrient'
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   */
  localB->rtb_BusAssignment1_m.controlModePosVSOrient =
    localP->controlModePosVsOrient_Value;
  localB->rtb_BusAssignment1_m.pos_ref[0] = (real32_T)localB->Switch1[0];
  localB->rtb_BusAssignment1_m.pos_ref[1] = (real32_T)localB->Switch1[1];
  localB->rtb_BusAssignment1_m.pos_ref[2] = (real32_T)localB->Switch1[2];
  localB->rtb_BusAssignment1_m.takeoff_flag =
    rtu_ReferenceValueServerCmds->takeoff_flag;
  localB->rtb_BusAssignment1_m.live_time_ticks =
    rtu_ReferenceValueServerCmds->live_time_ticks;
  localB->rtb_BusAssignment1_m.land_drone =
    rtu_ReferenceValueServerCmds->land_drone;
  localB->rtb_BusAssignment1_m.time_remaining =
    rtu_ReferenceValueServerCmds->time_remaining;

  /* BusAssignment: '<S5>/Bus  Assignment1' incorporates:
   *  Constant: '<S5>/pitch'
   *  Constant: '<S5>/roll'
   *  DataTypeConversion: '<S5>/Data Type Conversion1'
   */
  localB->rtb_BusAssignment1_m.orient_ref[0] = (real32_T)
    localB->rtb_DataTypeConversion3_idx_3;
  localB->rtb_BusAssignment1_m.orient_ref[1] = (real32_T)localP->roll_Value;
  localB->rtb_BusAssignment1_m.orient_ref[2] = (real32_T)localP->pitch_Value;

  /* Sum: '<S8>/Sum1' */
  localB->distToCenter = localB->rtb_BusAssignment1_m.pos_ref[0] -
    localB->SimplyIntegrateVelocity[0];
  localB->b_h = localB->rtb_BusAssignment1_m.pos_ref[1] -
    localB->SimplyIntegrateVelocity[1];

  /* Saturate: '<S55>/Saturation' incorporates:
   *  Gain: '<S53>/Proportional Gain'
   *  MATLAB Function: '<S8>/Position error transformation (Earth to Body frame)'
   */
  localB->Abs = (rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0
                 * localB->distToCenter +
                 rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1
                 * localB->b_h) * localP->Positioncontroller_P;
  if (localB->Abs > localP->Positioncontroller_UpperSaturationLimit) {
    localB->Abs = localP->Positioncontroller_UpperSaturationLimit;
  } else {
    if (localB->Abs < localP->Positioncontroller_LowerSaturationLimit) {
      localB->Abs = localP->Positioncontroller_LowerSaturationLimit;
    }
  }

  /* Sum: '<S8>/Sum19' incorporates:
   *  Gain: '<S53>/Proportional Gain'
   */
  rtb_Reshape9to3x3columnmajor_tmp = localB->Abs - localB->Reshapexhat_d[0];

  /* Sum: '<S107>/Sum' incorporates:
   *  DiscreteIntegrator: '<S98>/Integrator'
   *  Gain: '<S103>/Proportional Gain'
   */
  localB->Switch_h[0] = localP->Velocitycontroller_P *
    rtb_Reshape9to3x3columnmajor_tmp + localDW->Integrator_DSTATE[0];

  /* Saturate: '<S105>/Saturation' */
  if (localB->Switch_h[0] > localP->Velocitycontroller_UpperSaturationLimit) {
    localB->Abs = localP->Velocitycontroller_UpperSaturationLimit;
  } else if (localB->Switch_h[0] <
             localP->Velocitycontroller_LowerSaturationLimit) {
    localB->Abs = localP->Velocitycontroller_LowerSaturationLimit;
  } else {
    localB->Abs = localB->Switch_h[0];
  }

  /* DiscreteTransferFcn: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller' */
  localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_n[0] =
    (localB->Abs -
     localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_e[1] *
     localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[0])
    / localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_e[0];

  /* Sum: '<S8>/Sum19' incorporates:
   *  Gain: '<S53>/Proportional Gain'
   */
  localB->IntegralGain_a[0] = rtb_Reshape9to3x3columnmajor_tmp;

  /* Saturate: '<S55>/Saturation' incorporates:
   *  Gain: '<S53>/Proportional Gain'
   *  MATLAB Function: '<S8>/Position error transformation (Earth to Body frame)'
   */
  localB->Abs =
    (-rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 *
     localB->distToCenter +
     rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 *
     localB->b_h) * localP->Positioncontroller_P;
  if (localB->Abs > localP->Positioncontroller_UpperSaturationLimit) {
    localB->Abs = localP->Positioncontroller_UpperSaturationLimit;
  } else {
    if (localB->Abs < localP->Positioncontroller_LowerSaturationLimit) {
      localB->Abs = localP->Positioncontroller_LowerSaturationLimit;
    }
  }

  /* Sum: '<S8>/Sum19' incorporates:
   *  Gain: '<S53>/Proportional Gain'
   */
  rtb_Reshape9to3x3columnmajor_tmp = localB->Abs - localB->Reshapexhat_d[1];

  /* Sum: '<S107>/Sum' incorporates:
   *  DiscreteIntegrator: '<S98>/Integrator'
   *  Gain: '<S103>/Proportional Gain'
   */
  localB->Switch_h[1] = localP->Velocitycontroller_P *
    rtb_Reshape9to3x3columnmajor_tmp + localDW->Integrator_DSTATE[1];

  /* Saturate: '<S105>/Saturation' */
  if (localB->Switch_h[1] > localP->Velocitycontroller_UpperSaturationLimit) {
    localB->Abs = localP->Velocitycontroller_UpperSaturationLimit;
  } else if (localB->Switch_h[1] <
             localP->Velocitycontroller_LowerSaturationLimit) {
    localB->Abs = localP->Velocitycontroller_LowerSaturationLimit;
  } else {
    localB->Abs = localB->Switch_h[1];
  }

  /* DiscreteTransferFcn: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller' */
  localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_n[1] =
    (localB->Abs -
     localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_e[1] *
     localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[1])
    / localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_e[0];

  /* Switch: '<S2>/Switch_refAtt' incorporates:
   *  DiscreteTransferFcn: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller'
   *  Gain: '<S8>/Gain'
   */
  if (localB->rtb_BusAssignment1_m.controlModePosVSOrient) {
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 =
      (localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[0]
       * localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_n
       [0] +
       localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[1]
       * localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle
       [0]) * localP->Gain_Gain[0];
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 =
      (localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[0]
       * localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_n
       [1] +
       localP->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[1]
       * localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle
       [1]) * localP->Gain_Gain[1];
  } else {
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 =
      localB->rtb_BusAssignment1_m.orient_ref[1];
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 =
      localB->rtb_BusAssignment1_m.orient_ref[2];
  }

  /* End of Switch: '<S2>/Switch_refAtt' */

  /* Sum: '<S9>/Sum19' incorporates:
   *  Gain: '<S153>/Proportional Gain'
   */
  rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 =
    (rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 -
     localB->single_b) * localP->Anglecontrolloop_P;

  /* Sum: '<S9>/Sum1' incorporates:
   *  Gain: '<S153>/Proportional Gain'
   *  Sum: '<S9>/Sum19'
   */
  rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 -=
    localB->rtb_sincos_o2_n_idx_1;
  rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 =
    (rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 -
     localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1) *
    localP->Anglecontrolloop_P - localB->Gain_h;

  /* Gain: '<S201>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S193>/Filter'
   *  Gain: '<S192>/Derivative Gain'
   *  Sum: '<S193>/SumD'
   */
  localB->FilterCoefficient[0] = (localP->Angularvelocitycontrolloop_D[0] *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0 -
    localDW->Filter_DSTATE[0]) * localP->Angularvelocitycontrolloop_N[0];

  /* Sum: '<S207>/Sum' incorporates:
   *  DiscreteIntegrator: '<S198>/Integrator'
   *  Gain: '<S192>/Derivative Gain'
   *  Gain: '<S203>/Proportional Gain'
   */
  localB->Switch[0] = (localP->Angularvelocitycontrolloop_P[0] *
                       rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0
                       + localDW->Integrator_DSTATE_k[0]) +
    localB->FilterCoefficient[0];

  /* Gain: '<S201>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S193>/Filter'
   *  Gain: '<S192>/Derivative Gain'
   *  Sum: '<S193>/SumD'
   */
  localB->FilterCoefficient[1] = (localP->Angularvelocitycontrolloop_D[1] *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1 -
    localDW->Filter_DSTATE[1]) * localP->Angularvelocitycontrolloop_N[1];

  /* Sum: '<S207>/Sum' incorporates:
   *  DiscreteIntegrator: '<S198>/Integrator'
   *  Gain: '<S192>/Derivative Gain'
   *  Gain: '<S203>/Proportional Gain'
   */
  localB->Switch[1] = (localP->Angularvelocitycontrolloop_P[1] *
                       rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1
                       + localDW->Integrator_DSTATE_k[1]) +
    localB->FilterCoefficient[1];

  /* MultiPortSwitch: '<S2>/Multiport Switch' incorporates:
   *  Constant: '<S2>/Zero'
   *  Constant: '<S2>/Zero1'
   *  Constant: '<S317>/Constant'
   *  DiscreteIntegrator: '<S317>/Discrete-Time Integrator'
   *  Gain: '<S10>/D_yaw'
   *  Gain: '<S10>/P_yaw'
   *  Sum: '<S10>/Sum1'
   *  Sum: '<S10>/Sum2'
   *  Sum: '<S252>/Subtract'
   */
  if ((int32_T)localP->Zero1_Value == 0) {
    localB->single_b = localP->Zero_Value;
    localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1 =
      localP->Zero_Value;
    localB->Gain_h = localP->Zero_Value;
    localB->rtb_sincos_o2_n_idx_1 = localP->Zero_Value;
  } else {
    /* Sum: '<S11>/Sum4' incorporates:
     *  Constant: '<S11>/w0'
     *  DataTypeConversion: '<S251>/Data Type Conversion2'
     *  Gain: '<S11>/D_z'
     *  Gain: '<S11>/P_z'
     *  Gain: '<S11>/P_z1'
     *  Sum: '<S11>/Sum15'
     *  Sum: '<S11>/Sum3'
     */
    localB->rtb_sincos_o2_n_idx_1 = ((localB->rtb_BusAssignment1_m.pos_ref[2] -
      rtb_DataTypeConversion) * localP->P_z_Gain - localP->D_z_Gain * (real32_T)
      localB->rtb_FIR_IMUaccel_b[2]) + localP->P_z1_Gain * localP->w0_Value;

    /* Saturate: '<S205>/Saturation' */
    if (localB->Switch[0] >
        localP->Angularvelocitycontrolloop_UpperSaturationLimit) {
      localB->single_b = localP->Angularvelocitycontrolloop_UpperSaturationLimit;
    } else if (localB->Switch[0] <
               localP->Angularvelocitycontrolloop_LowerSaturationLimit) {
      localB->single_b = localP->Angularvelocitycontrolloop_LowerSaturationLimit;
    } else {
      localB->single_b = localB->Switch[0];
    }

    if (localB->Switch[1] >
        localP->Angularvelocitycontrolloop_UpperSaturationLimit) {
      localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1 =
        localP->Angularvelocitycontrolloop_UpperSaturationLimit;
    } else if (localB->Switch[1] <
               localP->Angularvelocitycontrolloop_LowerSaturationLimit) {
      localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1 =
        localP->Angularvelocitycontrolloop_LowerSaturationLimit;
    } else {
      localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1 =
        localB->Switch[1];
    }

    /* End of Saturate: '<S205>/Saturation' */
    localB->Gain_h = (localB->rtb_BusAssignment1_m.orient_ref[0] -
                      localDW->DiscreteTimeIntegrator_DSTATE) *
      localP->P_yaw_Gain - (localB->r - localP->Constant_Value_gu) *
      localP->D_yaw_Gain;

    /* Saturate: '<S11>/SaturationThrust' incorporates:
     *  Constant: '<S317>/Constant'
     *  DiscreteIntegrator: '<S317>/Discrete-Time Integrator'
     *  Gain: '<S10>/D_yaw'
     *  Gain: '<S10>/P_yaw'
     *  Sum: '<S10>/Sum1'
     *  Sum: '<S10>/Sum2'
     *  Sum: '<S252>/Subtract'
     */
    if (localB->rtb_sincos_o2_n_idx_1 > localP->SaturationThrust_UpperSat) {
      localB->rtb_sincos_o2_n_idx_1 = localP->SaturationThrust_UpperSat;
    } else {
      if (localB->rtb_sincos_o2_n_idx_1 < localP->SaturationThrust_LowerSat) {
        localB->rtb_sincos_o2_n_idx_1 = localP->SaturationThrust_LowerSat;
      }
    }

    /* End of Saturate: '<S11>/SaturationThrust' */
  }

  /* End of MultiPortSwitch: '<S2>/Multiport Switch' */

  /* Switch: '<S13>/Environment Switch' incorporates:
   *  Constant: '<S13>/Switch Control'
   *  Sum: '<S7>/Add'
   */
  if (!localP->SwitchControl_Value) {
    /* ManualSwitch: '<S7>/Manual Switch' incorporates:
     *  Constant: '<S7>/Pitch correction'
     *  Constant: '<S7>/zero correction'
     */
    if (localP->ManualSwitch_CurrentSetting == 1) {
      localB->Abs = localP->Pitchcorrection_Value;
    } else {
      localB->Abs = localP->zerocorrection_Value;
    }

    /* End of ManualSwitch: '<S7>/Manual Switch' */
    localB->single_b += localB->Abs;
  }

  /* End of Switch: '<S13>/Environment Switch' */
  for (localB->i = 0; localB->i < 4; localB->i++) {
    /* Product: '<S7>/Product' incorporates:
     *  Constant: '<S7>/TorqueTotalThrustToThrustPerMotor'
     *  SignalConversion generated from: '<S7>/Product'
     */
    rty_motorCmds[localB->i] = 0.0F;
    rty_motorCmds[localB->i] += localP->
      TorqueTotalThrustToThrustPerMotor_Value[localB->i] *
      localB->rtb_sincos_o2_n_idx_1;
    rty_motorCmds[localB->i] += localP->
      TorqueTotalThrustToThrustPerMotor_Value[localB->i + 4] * localB->Gain_h;
    rty_motorCmds[localB->i] += localP->
      TorqueTotalThrustToThrustPerMotor_Value[localB->i + 8] * localB->single_b;
    rty_motorCmds[localB->i] += localP->
      TorqueTotalThrustToThrustPerMotor_Value[localB->i + 12] *
      localB->rtb_TmpSignalConversionAtUAVOrbitFollowerInport1_idx_1;

    /* Gain: '<S12>/ThrustToMotorCommand' */
    rty_motorCmds[localB->i] *= localP->ThrustToMotorCommand_Gain;

    /* Saturate: '<S12>/Saturation5' */
    localB->Abs = rty_motorCmds[localB->i];
    if (localB->Abs > localP->Saturation5_UpperSat) {
      rty_motorCmds[localB->i] = localP->Saturation5_UpperSat;
    } else if (localB->Abs < localP->Saturation5_LowerSat) {
      rty_motorCmds[localB->i] = localP->Saturation5_LowerSat;
    } else {
      rty_motorCmds[localB->i] = localB->Abs;
    }

    /* End of Saturate: '<S12>/Saturation5' */

    /* Gain: '<S12>/MotorDirections' */
    rty_motorCmds[localB->i] *= localP->MotorDirections_Gain[localB->i];
  }

  /* SignalConversion generated from: '<S431>/Product' */
  localB->Abs = localB->Reshapexhat_d[0];
  localB->distToCenter = localB->Reshapexhat_d[1];
  for (localB->i = 0; localB->i < 3; localB->i++) {
    /* Product: '<S431>/Product' incorporates:
     *  Math: '<S431>/Math Function'
     *  SignalConversion generated from: '<S431>/Product'
     */
    localB->Product_k[localB->i] = 0.0F;
    localB->Product_k[localB->i] += localB->MathFunction_o[localB->i] *
      localB->Abs;
    localB->Product_k[localB->i] += localB->MathFunction_o[localB->i + 3] *
      localB->distToCenter;
    localB->Product_k[localB->i] += localB->MathFunction_o[localB->i + 6] *
      localB->DataTypeConversion2;
  }

  for (localB->i = 0; localB->i < 3; localB->i++) {
    /* Sum: '<S251>/Sum' incorporates:
     *  Constant: '<S251>/gravity'
     *  DiscreteFir: '<S253>/FIR_IMUaccel'
     *  Math: '<S251>/Math Function'
     *  Product: '<S251>/Product'
     *  Reshape: '<S312>/Reshape (9) to [3x3] column-major'
     */
    localB->Sum[localB->i] = ((localB->Reshape9to3x3columnmajor[3 * localB->i +
      1] * localB->FIR_IMUaccel[1] + localB->Reshape9to3x3columnmajor[3 *
      localB->i] * localB->FIR_IMUaccel[0]) + localB->Reshape9to3x3columnmajor[3
      * localB->i + 2] * localB->acc1) + localP->gravity_Value_k[localB->i];
  }

  /* DataTypeConversion: '<S387>/Conversion' */
  localB->rtb_Conversion_nc_l[0] = localB->rtb_MemoryX_m_l[0];
  localB->rtb_Conversion_nc_l[1] = localB->rtb_MemoryX_m_l[1];

  /* Reshape: '<S371>/Reshapeu' */
  localB->rtb_Reshapeu_b_e = localB->p;

  /* DataTypeConversion: '<S414>/Conversion' incorporates:
   *  Constant: '<S372>/KalmanGainL'
   */
  localB->rtb_Conversion_nr_d[0] = (real32_T)localP->KalmanGainL_Value_n[0];
  localB->rtb_Conversion_nr_d[1] = (real32_T)localP->KalmanGainL_Value_n[1];

  /* Outputs for Enabled SubSystem: '<S391>/MeasurementUpdate' */
  /* Constant: '<S371>/C' incorporates:
   *  Constant: '<S371>/D'
   */
  flightControlSystem_MeasurementUpdate(rtb_DataTypeConversionEnable_a,
    localB->rtb_Conversion_nr_d, localB->rtb_Reshapey_o_j, localP->C_Value_o,
    localB->rtb_Conversion_nc_l, localP->D_Value_f, localB->rtb_Reshapeu_b_e,
    localB->Product3_n, &localDW->MeasurementUpdate_j,
    &localP->MeasurementUpdate_j);

  /* End of Outputs for SubSystem: '<S391>/MeasurementUpdate' */

  /* Reshape: '<S391>/Reshape' incorporates:
   *  Constant: '<S371>/A'
   *  Constant: '<S371>/B'
   *  Product: '<S391>/A[k]*xhat[k|k-1]'
   *  Product: '<S391>/B[k]*u[k]'
   *  Product: '<S420>/Product3'
   *  Sum: '<S391>/Add'
   */
  localB->Reshape_n[0] = ((localP->A_Value_b[0] * localB->rtb_Conversion_nc_l[0]
    + localP->A_Value_b[2] * localB->rtb_Conversion_nc_l[1]) + localP->
    B_Value_p[0] * localB->rtb_Reshapeu_b_e) + localB->Product3_n[0];
  localB->Reshape_n[1] = ((localP->A_Value_b[1] * localB->rtb_Conversion_nc_l[0]
    + localP->A_Value_b[3] * localB->rtb_Conversion_nc_l[1]) + localP->
    B_Value_p[1] * localB->rtb_Reshapeu_b_e) + localB->Product3_n[1];

  /* DataTypeConversion: '<S335>/Conversion' */
  localB->rtb_Conversion_c_g[0] = localB->rtb_MemoryX_l_b[0];
  localB->rtb_Conversion_c_g[1] = localB->rtb_MemoryX_l_b[1];

  /* Reshape: '<S319>/Reshapeu' */
  localB->rtb_Reshapeu_gu_d = localB->q;

  /* DataTypeConversion: '<S362>/Conversion' incorporates:
   *  Constant: '<S320>/KalmanGainL'
   */
  localB->rtb_Conversion_l_d[0] = (real32_T)localP->KalmanGainL_Value_e[0];
  localB->rtb_Conversion_l_d[1] = (real32_T)localP->KalmanGainL_Value_e[1];

  /* Outputs for Enabled SubSystem: '<S339>/MeasurementUpdate' */
  /* Constant: '<S319>/C' incorporates:
   *  Constant: '<S319>/D'
   */
  flightControlSystem_MeasurementUpdate(rtb_DataTypeConversionEnable,
    localB->rtb_Conversion_l_d, localB->rtb_Reshapey_d_b, localP->C_Value_p,
    localB->rtb_Conversion_c_g, localP->D_Value_n, localB->rtb_Reshapeu_gu_d,
    localB->Product3_k, &localDW->MeasurementUpdate_d,
    &localP->MeasurementUpdate_d);

  /* End of Outputs for SubSystem: '<S339>/MeasurementUpdate' */

  /* Reshape: '<S339>/Reshape' incorporates:
   *  Constant: '<S319>/A'
   *  Constant: '<S319>/B'
   *  Product: '<S339>/A[k]*xhat[k|k-1]'
   *  Product: '<S339>/B[k]*u[k]'
   *  Product: '<S368>/Product3'
   *  Sum: '<S339>/Add'
   */
  localB->Reshape_m[0] = ((localP->A_Value_l[0] * localB->rtb_Conversion_c_g[0]
    + localP->A_Value_l[2] * localB->rtb_Conversion_c_g[1]) + localP->B_Value_n
    [0] * localB->rtb_Reshapeu_gu_d) + localB->Product3_k[0];
  localB->Reshape_m[1] = ((localP->A_Value_l[1] * localB->rtb_Conversion_c_g[0]
    + localP->A_Value_l[3] * localB->rtb_Conversion_c_g[1]) + localP->B_Value_n
    [1] * localB->rtb_Reshapeu_gu_d) + localB->Product3_k[1];

  /* DataTypeConversion: '<S273>/Conversion' incorporates:
   *  Delay: '<S255>/MemoryX'
   */
  localB->rtb_Conversion_d_g[0] = localDW->MemoryX_DSTATE[0];

  /* DataTypeConversion: '<S299>/Conversion' incorporates:
   *  Constant: '<S259>/KalmanGainL'
   */
  localB->rtb_Conversion_j_m[0] = localP->KalmanGainL_Value_k[0];

  /* DataTypeConversion: '<S273>/Conversion' incorporates:
   *  Delay: '<S255>/MemoryX'
   */
  localB->rtb_Conversion_d_g[1] = localDW->MemoryX_DSTATE[1];

  /* DataTypeConversion: '<S299>/Conversion' incorporates:
   *  Constant: '<S259>/KalmanGainL'
   */
  localB->rtb_Conversion_j_m[1] = localP->KalmanGainL_Value_k[1];

  /* Outputs for Enabled SubSystem: '<S277>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S305>/Enable'
   */
  if (rtb_DataTypeConversionEnable_j) {
    localDW->MeasurementUpdate_MODE_h = true;

    /* Product: '<S305>/D[k]*u[k]' incorporates:
     *  Constant: '<S255>/D'
     *  Delay: '<S251>/Delay2'
     *  Reshape: '<S255>/Reshapeu'
     */
    localDW->Delay2_DSTATE = localP->D_Value * localB->Sum[2];

    /* Sum: '<S305>/Sum' incorporates:
     *  Constant: '<S255>/C'
     *  Delay: '<S251>/Delay2'
     *  Product: '<S305>/C[k]*xhat[k|k-1]'
     *  Reshape: '<S255>/Reshapey'
     *  Sum: '<S305>/Add1'
     */
    localB->Switch1_o = localB->invertzaxisGain - ((localP->C_Value[0] *
      localB->rtb_Conversion_d_g[0] + localP->C_Value[1] *
      localB->rtb_Conversion_d_g[1]) + localDW->Delay2_DSTATE);

    /* Product: '<S305>/Product3' */
    localB->Product3[0] = localB->rtb_Conversion_j_m[0] * localB->Switch1_o;
    localB->Product3[1] = localB->rtb_Conversion_j_m[1] * localB->Switch1_o;
  } else {
    if (localDW->MeasurementUpdate_MODE_h) {
      /* Disable for Product: '<S305>/Product3' incorporates:
       *  Outport: '<S305>/L*(y[k]-yhat[k|k-1])'
       */
      localB->Product3[0] = localP->Lykyhatkk1_Y0;
      localB->Product3[1] = localP->Lykyhatkk1_Y0;
      localDW->MeasurementUpdate_MODE_h = false;
    }
  }

  /* End of Outputs for SubSystem: '<S277>/MeasurementUpdate' */

  /* Reshape: '<S277>/Reshape' incorporates:
   *  Constant: '<S255>/A'
   *  Constant: '<S255>/B'
   *  Product: '<S277>/A[k]*xhat[k|k-1]'
   *  Product: '<S277>/B[k]*u[k]'
   *  Product: '<S305>/Product3'
   *  Reshape: '<S255>/Reshapeu'
   *  Sum: '<S277>/Add'
   */
  localB->Reshape[0] = ((localP->A_Value[0] * localB->rtb_Conversion_d_g[0] +
    localP->A_Value[2] * localB->rtb_Conversion_d_g[1]) + localP->B_Value[0] *
                        localB->Sum[2]) + localB->Product3[0];

  /* Gain: '<S189>/ZeroGain' */
  localB->acc1 = localP->ZeroGain_Gain * localB->Switch[0];

  /* DeadZone: '<S191>/DeadZone' */
  if (localB->Switch[0] >
      localP->Angularvelocitycontrolloop_UpperSaturationLimit) {
    localB->Switch[0] -= localP->Angularvelocitycontrolloop_UpperSaturationLimit;
  } else if (localB->Switch[0] >=
             localP->Angularvelocitycontrolloop_LowerSaturationLimit) {
    localB->Switch[0] = 0.0F;
  } else {
    localB->Switch[0] -= localP->Angularvelocitycontrolloop_LowerSaturationLimit;
  }

  /* RelationalOperator: '<S189>/NotEqual' */
  rtb_Compare_cy = (localB->acc1 != localB->Switch[0]);

  /* Signum: '<S189>/SignPreSat' */
  if (localB->Switch[0] < 0.0F) {
    localB->Switch[0] = -1.0F;
  } else if (localB->Switch[0] > 0.0F) {
    localB->Switch[0] = 1.0F;
  } else if (localB->Switch[0] == 0.0F) {
    localB->Switch[0] = 0.0F;
  } else {
    localB->Switch[0] = (rtNaNF);
  }

  /* Gain: '<S195>/Integral Gain' */
  localB->single_b = localP->Angularvelocitycontrolloop_I[0] *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_0;

  /* DataTypeConversion: '<S189>/DataTypeConv1' incorporates:
   *  Logic: '<S189>/AND3'
   */
  localB->Abs = floorf(localB->Switch[0]);
  if (rtIsNaNF(localB->Abs) || rtIsInfF(localB->Abs)) {
    localB->Abs = 0.0F;
  } else {
    localB->Abs = fmodf(localB->Abs, 256.0F);
  }

  /* Signum: '<S189>/SignPreIntegrator' */
  if (localB->single_b < 0.0F) {
    localB->y2 = -1.0F;
  } else if (localB->single_b > 0.0F) {
    localB->y2 = 1.0F;
  } else if (localB->single_b == 0.0F) {
    localB->y2 = 0.0F;
  } else {
    localB->y2 = (rtNaNF);
  }

  /* DataTypeConversion: '<S189>/DataTypeConv2' */
  if (rtIsNaNF(localB->y2)) {
    localB->acc1 = 0.0F;
  } else {
    localB->acc1 = fmodf(localB->y2, 256.0F);
  }

  /* Switch: '<S189>/Switch' incorporates:
   *  DataTypeConversion: '<S189>/DataTypeConv1'
   *  DataTypeConversion: '<S189>/DataTypeConv2'
   *  Logic: '<S189>/AND3'
   *  RelationalOperator: '<S189>/Equal1'
   */
  if (rtb_Compare_cy && ((localB->Abs < 0.0F ? (int32_T)(int8_T)-(int8_T)
                          (uint8_T)-localB->Abs : (int32_T)(int8_T)(uint8_T)
                          localB->Abs) == (localB->acc1 < 0.0F ? (int32_T)
        (int8_T)-(int8_T)(uint8_T)-localB->acc1 : (int32_T)(int8_T)(uint8_T)
        localB->acc1))) {
    /* Switch: '<S189>/Switch' incorporates:
     *  Constant: '<S189>/Constant1'
     */
    localB->Switch[0] = localP->Constant1_Value;
  } else {
    /* Switch: '<S189>/Switch' */
    localB->Switch[0] = localB->single_b;
  }

  /* Gain: '<S89>/ZeroGain' */
  localB->single_b = localP->ZeroGain_Gain_a * localB->Switch_h[0];

  /* DeadZone: '<S91>/DeadZone' */
  if (localB->Switch_h[0] > localP->Velocitycontroller_UpperSaturationLimit) {
    localB->Switch_h[0] -= localP->Velocitycontroller_UpperSaturationLimit;
  } else if (localB->Switch_h[0] >=
             localP->Velocitycontroller_LowerSaturationLimit) {
    localB->Switch_h[0] = 0.0F;
  } else {
    localB->Switch_h[0] -= localP->Velocitycontroller_LowerSaturationLimit;
  }

  /* RelationalOperator: '<S89>/NotEqual' */
  rtb_Compare_cy = (localB->single_b != localB->Switch_h[0]);

  /* Signum: '<S89>/SignPreSat' */
  if (localB->Switch_h[0] < 0.0F) {
    localB->Switch_h[0] = -1.0F;
  } else if (localB->Switch_h[0] > 0.0F) {
    localB->Switch_h[0] = 1.0F;
  } else if (localB->Switch_h[0] == 0.0F) {
    localB->Switch_h[0] = 0.0F;
  } else {
    localB->Switch_h[0] = (rtNaNF);
  }

  /* Gain: '<S95>/Integral Gain' */
  localB->single_b = localP->Velocitycontroller_I * localB->IntegralGain_a[0];

  /* DataTypeConversion: '<S89>/DataTypeConv1' incorporates:
   *  Logic: '<S89>/AND3'
   */
  localB->Abs = floorf(localB->Switch_h[0]);
  if (rtIsNaNF(localB->Abs) || rtIsInfF(localB->Abs)) {
    localB->Abs = 0.0F;
  } else {
    localB->Abs = fmodf(localB->Abs, 256.0F);
  }

  /* Signum: '<S89>/SignPreIntegrator' */
  if (localB->single_b < 0.0F) {
    localB->y2 = -1.0F;
  } else if (localB->single_b > 0.0F) {
    localB->y2 = 1.0F;
  } else if (localB->single_b == 0.0F) {
    localB->y2 = 0.0F;
  } else {
    localB->y2 = (rtNaNF);
  }

  /* DataTypeConversion: '<S89>/DataTypeConv2' */
  if (rtIsNaNF(localB->y2)) {
    localB->acc1 = 0.0F;
  } else {
    localB->acc1 = fmodf(localB->y2, 256.0F);
  }

  /* Switch: '<S89>/Switch' incorporates:
   *  DataTypeConversion: '<S89>/DataTypeConv1'
   *  DataTypeConversion: '<S89>/DataTypeConv2'
   *  Logic: '<S89>/AND3'
   *  RelationalOperator: '<S89>/Equal1'
   */
  if (rtb_Compare_cy && ((localB->Abs < 0.0F ? (int32_T)(int8_T)-(int8_T)
                          (uint8_T)-localB->Abs : (int32_T)(int8_T)(uint8_T)
                          localB->Abs) == (localB->acc1 < 0.0F ? (int32_T)
        (int8_T)-(int8_T)(uint8_T)-localB->acc1 : (int32_T)(int8_T)(uint8_T)
        localB->acc1))) {
    /* Switch: '<S89>/Switch' incorporates:
     *  Constant: '<S89>/Constant1'
     */
    localB->Switch_h[0] = localP->Constant1_Value_k;
  } else {
    /* Switch: '<S89>/Switch' */
    localB->Switch_h[0] = localB->single_b;
  }

  /* Reshape: '<S277>/Reshape' incorporates:
   *  Constant: '<S255>/A'
   *  Constant: '<S255>/B'
   *  Product: '<S277>/A[k]*xhat[k|k-1]'
   *  Product: '<S277>/B[k]*u[k]'
   *  Product: '<S305>/Product3'
   *  Reshape: '<S255>/Reshapeu'
   *  Sum: '<S277>/Add'
   */
  localB->Reshape[1] = ((localP->A_Value[1] * localB->rtb_Conversion_d_g[0] +
    localP->A_Value[3] * localB->rtb_Conversion_d_g[1]) + localP->B_Value[1] *
                        localB->Sum[2]) + localB->Product3[1];

  /* Gain: '<S189>/ZeroGain' */
  localB->acc1 = localP->ZeroGain_Gain * localB->Switch[1];

  /* DeadZone: '<S191>/DeadZone' */
  if (localB->Switch[1] >
      localP->Angularvelocitycontrolloop_UpperSaturationLimit) {
    localB->Switch[1] -= localP->Angularvelocitycontrolloop_UpperSaturationLimit;
  } else if (localB->Switch[1] >=
             localP->Angularvelocitycontrolloop_LowerSaturationLimit) {
    localB->Switch[1] = 0.0F;
  } else {
    localB->Switch[1] -= localP->Angularvelocitycontrolloop_LowerSaturationLimit;
  }

  /* RelationalOperator: '<S189>/NotEqual' */
  rtb_Compare_cy = (localB->acc1 != localB->Switch[1]);

  /* Signum: '<S189>/SignPreSat' */
  if (localB->Switch[1] < 0.0F) {
    localB->Switch[1] = -1.0F;
  } else if (localB->Switch[1] > 0.0F) {
    localB->Switch[1] = 1.0F;
  } else if (localB->Switch[1] == 0.0F) {
    localB->Switch[1] = 0.0F;
  } else {
    localB->Switch[1] = (rtNaNF);
  }

  /* Gain: '<S195>/Integral Gain' */
  localB->single_b = localP->Angularvelocitycontrolloop_I[1] *
    rtb_LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncon_1;

  /* DataTypeConversion: '<S189>/DataTypeConv1' incorporates:
   *  Logic: '<S189>/AND3'
   */
  localB->Abs = floorf(localB->Switch[1]);
  if (rtIsNaNF(localB->Abs) || rtIsInfF(localB->Abs)) {
    localB->Abs = 0.0F;
  } else {
    localB->Abs = fmodf(localB->Abs, 256.0F);
  }

  /* Signum: '<S189>/SignPreIntegrator' */
  if (localB->single_b < 0.0F) {
    localB->y2 = -1.0F;
  } else if (localB->single_b > 0.0F) {
    localB->y2 = 1.0F;
  } else if (localB->single_b == 0.0F) {
    localB->y2 = 0.0F;
  } else {
    localB->y2 = (rtNaNF);
  }

  /* DataTypeConversion: '<S189>/DataTypeConv2' */
  if (rtIsNaNF(localB->y2)) {
    localB->acc1 = 0.0F;
  } else {
    localB->acc1 = fmodf(localB->y2, 256.0F);
  }

  /* Switch: '<S189>/Switch' incorporates:
   *  DataTypeConversion: '<S189>/DataTypeConv1'
   *  DataTypeConversion: '<S189>/DataTypeConv2'
   *  Logic: '<S189>/AND3'
   *  RelationalOperator: '<S189>/Equal1'
   */
  if (rtb_Compare_cy && ((localB->Abs < 0.0F ? (int32_T)(int8_T)-(int8_T)
                          (uint8_T)-localB->Abs : (int32_T)(int8_T)(uint8_T)
                          localB->Abs) == (localB->acc1 < 0.0F ? (int32_T)
        (int8_T)-(int8_T)(uint8_T)-localB->acc1 : (int32_T)(int8_T)(uint8_T)
        localB->acc1))) {
    /* Switch: '<S189>/Switch' incorporates:
     *  Constant: '<S189>/Constant1'
     */
    localB->Switch[1] = localP->Constant1_Value;
  } else {
    /* Switch: '<S189>/Switch' */
    localB->Switch[1] = localB->single_b;
  }

  /* Gain: '<S89>/ZeroGain' */
  localB->single_b = localP->ZeroGain_Gain_a * localB->Switch_h[1];

  /* DeadZone: '<S91>/DeadZone' */
  if (localB->Switch_h[1] > localP->Velocitycontroller_UpperSaturationLimit) {
    localB->Switch_h[1] -= localP->Velocitycontroller_UpperSaturationLimit;
  } else if (localB->Switch_h[1] >=
             localP->Velocitycontroller_LowerSaturationLimit) {
    localB->Switch_h[1] = 0.0F;
  } else {
    localB->Switch_h[1] -= localP->Velocitycontroller_LowerSaturationLimit;
  }

  /* RelationalOperator: '<S89>/NotEqual' */
  rtb_Compare_cy = (localB->single_b != localB->Switch_h[1]);

  /* Signum: '<S89>/SignPreSat' */
  if (localB->Switch_h[1] < 0.0F) {
    localB->Switch_h[1] = -1.0F;
  } else if (localB->Switch_h[1] > 0.0F) {
    localB->Switch_h[1] = 1.0F;
  } else if (localB->Switch_h[1] == 0.0F) {
    localB->Switch_h[1] = 0.0F;
  } else {
    localB->Switch_h[1] = (rtNaNF);
  }

  /* Gain: '<S95>/Integral Gain' */
  localB->single_b = localP->Velocitycontroller_I *
    rtb_Reshape9to3x3columnmajor_tmp;

  /* DataTypeConversion: '<S89>/DataTypeConv1' incorporates:
   *  Logic: '<S89>/AND3'
   */
  localB->Abs = floorf(localB->Switch_h[1]);
  if (rtIsNaNF(localB->Abs) || rtIsInfF(localB->Abs)) {
    localB->Abs = 0.0F;
  } else {
    localB->Abs = fmodf(localB->Abs, 256.0F);
  }

  /* Signum: '<S89>/SignPreIntegrator' */
  if (localB->single_b < 0.0F) {
    localB->y2 = -1.0F;
  } else if (localB->single_b > 0.0F) {
    localB->y2 = 1.0F;
  } else if (localB->single_b == 0.0F) {
    localB->y2 = 0.0F;
  } else {
    localB->y2 = (rtNaNF);
  }

  /* DataTypeConversion: '<S89>/DataTypeConv2' */
  if (rtIsNaNF(localB->y2)) {
    localB->acc1 = 0.0F;
  } else {
    localB->acc1 = fmodf(localB->y2, 256.0F);
  }

  /* Switch: '<S89>/Switch' incorporates:
   *  DataTypeConversion: '<S89>/DataTypeConv1'
   *  DataTypeConversion: '<S89>/DataTypeConv2'
   *  Logic: '<S89>/AND3'
   *  RelationalOperator: '<S89>/Equal1'
   */
  if (rtb_Compare_cy && ((localB->Abs < 0.0F ? (int32_T)(int8_T)-(int8_T)
                          (uint8_T)-localB->Abs : (int32_T)(int8_T)(uint8_T)
                          localB->Abs) == (localB->acc1 < 0.0F ? (int32_T)
        (int8_T)-(int8_T)(uint8_T)-localB->acc1 : (int32_T)(int8_T)(uint8_T)
        localB->acc1))) {
    /* Switch: '<S89>/Switch' incorporates:
     *  Constant: '<S89>/Constant1'
     */
    localB->Switch_h[1] = localP->Constant1_Value_k;
  } else {
    /* Switch: '<S89>/Switch' */
    localB->Switch_h[1] = localB->single_b;
  }

  /* Outputs for Atomic SubSystem: '<S1>/Logging' */
  flightControlSystem_Logging(&localB->rtb_BusAssignment1_m, rtu_Sensors);

  /* End of Outputs for SubSystem: '<S1>/Logging' */

  /* Switch: '<S226>/Switch' incorporates:
   *  Constant: '<S226>/ '
   *  Constant: '<S226>/  F'
   */
  if (localP->F_Value) {
    localB->Switch1_o = rtu_Sensors->VisionSensors.opticalFlow_data[2];
    localB->rtb_DataTypeConversion3_idx_1 =
      rtu_Sensors->VisionSensors.opticalFlow_data[2];
  } else {
    localB->Switch1_o = localP->_Value;
    localB->rtb_DataTypeConversion3_idx_1 = localP->_Value;
  }

  /* End of Switch: '<S226>/Switch' */

  /* Sum: '<S226>/Add' incorporates:
   *  Constant: '<S233>/Constant'
   *  DataTypeConversion: '<S226>/   '
   *  Delay: '<S226>/Delay One Step'
   *  Product: '<S226>/  '
   *  RelationalOperator: '<S233>/Compare'
   */
  localDW->DelayOneStep_DSTATE = (real_T)(localB->rtb_DataTypeConversion3_idx_1 ==
    localP->Checkerrorcondition_const) * localDW->DelayOneStep_DSTATE + (real_T)
    (localB->Switch1_o == localP->Checkerrorcondition_const);

  /* Switch: '<S226>/Switch1' incorporates:
   *  Constant: '<S226>/ Disable OF check'
   *  Constant: '<S232>/Constant'
   *  Delay: '<S226>/Delay One Step'
   *  RelationalOperator: '<S232>/Compare'
   */
  if (rtb_Compare_l) {
    localB->Switch1_o = localP->DisableOFcheck_Value;
  } else {
    localB->Switch1_o = (localDW->DelayOneStep_DSTATE >
                         localP->u0continuousOFerrors_const);
  }

  /* End of Switch: '<S226>/Switch1' */

  /* DataTypeConversion: '<S3>/Data Type Conversion1' incorporates:
   *  Abs: '<S3>/Abs2'
   *  Abs: '<S3>/Abs3'
   *  Abs: '<S3>/Abs4'
   *  Abs: '<S3>/Abs5'
   *  Constant: '<S218>/Constant'
   *  Constant: '<S219>/Constant'
   *  Constant: '<S220>/Constant'
   *  Constant: '<S221>/Constant'
   *  Gain: '<S3>/Gain'
   *  Gain: '<S3>/Gain1'
   *  Logic: '<S3>/Logical Operator1'
   *  Logic: '<S3>/Logical Operator2'
   *  Logic: '<S3>/Logical Operator3'
   *  RelationalOperator: '<S218>/Compare'
   *  RelationalOperator: '<S219>/Compare'
   *  RelationalOperator: '<S220>/Compare'
   *  RelationalOperator: '<S221>/Compare'
   *  Sum: '<S3>/Subtract'
   *  Sum: '<S3>/Subtract1'
   */
  *rty_Flag = (uint8_T)(((fabsf(rtu_Sensors->VisionSensors.opticalFlow_data[0]) >
    localP->CompareToConstant4_const) && (fabsf(localP->Gain_Gain_i *
    rtu_Sensors->VisionSensors.opticalFlow_data[0] - localB->Reshapexhat_d[0]) >
    localP->CompareToConstant2_const)) || ((fabsf(localP->Gain1_Gain_l *
    rtu_Sensors->VisionSensors.opticalFlow_data[1] - localB->Reshapexhat_d[1]) >
    localP->CompareToConstant3_const) && (fabsf
    (rtu_Sensors->VisionSensors.opticalFlow_data[1]) >
    localP->CompareToConstant5_const)));

  /* If: '<S3>/If' incorporates:
   *  Abs: '<S215>/Abs  '
   *  Abs: '<S3>/Abs'
   *  Abs: '<S3>/Abs1'
   *  Constant: '<S215>/  F'
   *  Constant: '<S215>/0.5 meters'
   *  Constant: '<S216>/Constant'
   *  Constant: '<S217>/Constant'
   *  DataTypeConversion: '<S226>/Data Type Conversion2'
   *  Logic: '<S3>/Logical Operator'
   *  RelationalOperator: '<S215>/GreaterThan  '
   *  RelationalOperator: '<S216>/Compare'
   *  RelationalOperator: '<S217>/Compare'
   *  Switch: '<S215>/         '
   */
  if ((fabsf(localB->SimplyIntegrateVelocity[0]) >
       localP->CompareToConstant_const_m) || (fabsf
       (localB->SimplyIntegrateVelocity[1]) > localP->CompareToConstant1_const_g))
  {
    /* Outputs for IfAction SubSystem: '<S3>/Geofencing error' incorporates:
     *  ActionPort: '<S223>/Action Port'
     */
    flightControlSystem_Geofencingerror(&Merge, &localP->Geofencingerror);

    /* End of Outputs for SubSystem: '<S3>/Geofencing error' */
  } else if (*rty_Flag > 0) {
    /* Outputs for IfAction SubSystem: '<S3>/estimator//Optical flow error' incorporates:
     *  ActionPort: '<S228>/Action Port'
     */
    flightControlSystem_Geofencingerror(&Merge,
      &localP->estimatorOpticalflowerror);

    /* End of Outputs for SubSystem: '<S3>/estimator//Optical flow error' */
  } else {
    /* DataTypeConversion: '<S226>/Data Type Conversion2' */
    localB->rtb_DataTypeConversion3_idx_1 = fabs(localB->Switch1_o);
    if (localB->rtb_DataTypeConversion3_idx_1 < 4.503599627370496E+15) {
      if (localB->rtb_DataTypeConversion3_idx_1 >= 0.5) {
        localB->Switch1_o = floor(localB->Switch1_o + 0.5);
      } else {
        localB->Switch1_o *= 0.0;
      }
    }

    if (rtIsNaN(localB->Switch1_o) || rtIsInf(localB->Switch1_o)) {
      localB->Switch1_o = 0.0;
    } else {
      localB->Switch1_o = fmod(localB->Switch1_o, 256.0);
    }

    if ((localB->Switch1_o < 0.0 ? (int32_T)(uint8_T)-(int8_T)(uint8_T)
         -localB->Switch1_o : (int32_T)(uint8_T)localB->Switch1_o) > 0) {
      /* Outputs for IfAction SubSystem: '<S3>/No optical flow ' incorporates:
       *  ActionPort: '<S224>/Action Port'
       */
      flightControlSystem_Geofencingerror(&Merge, &localP->Noopticalflow);

      /* End of Outputs for SubSystem: '<S3>/No optical flow ' */
    } else {
      if (localP->F_Value_j) {
        /* Switch: '<S215>/         ' incorporates:
         *  DiscreteFilter: '<S256>/pressureFilter_IIR'
         *  Sum: '<S3>/Difference between  sonar and pressure'
         */
        localB->Abs = rtb_DataTypeConversion - acc1;
      } else {
        /* Switch: '<S215>/         ' incorporates:
         *  Constant: '<S215>/    '
         */
        localB->Abs = localP->_Value_p;
      }

      if (fabsf(localB->Abs) > localP->u5meters_Value) {
        /* Outputs for IfAction SubSystem: '<S3>/Ultrasound improper' incorporates:
         *  ActionPort: '<S227>/Action Port'
         */
        flightControlSystem_Geofencingerror(&Merge, &localP->Ultrasoundimproper);

        /* End of Outputs for SubSystem: '<S3>/Ultrasound improper' */
      }
    }
  }

  /* End of If: '<S3>/If' */

  /* Sum: '<S248>/FixPt Sum1' incorporates:
   *  Constant: '<S248>/FixPt Constant'
   */
  localB->rtb_FixPtSum1_i = localB->rtb_Output_l_n + localP->FixPtConstant_Value;

  /* Switch: '<S249>/FixPt Switch' incorporates:
   *  Constant: '<S249>/Constant'
   *  UnitDelay: '<S245>/Output'
   */
  if (localB->rtb_FixPtSum1_i > localP->WrapToZero_Threshold) {
    localDW->Output_DSTATE_a = localP->Constant_Value_d;
  } else {
    localDW->Output_DSTATE_a = localB->rtb_FixPtSum1_i;
  }

  /* End of Switch: '<S249>/FixPt Switch' */

  /* Sum: '<S428>/FixPt Sum1' incorporates:
   *  Constant: '<S428>/FixPt Constant'
   */
  localB->rtb_FixPtSum1_n_n = localB->rtb_Output_g_m +
    localP->FixPtConstant_Value_f;

  /* Switch: '<S429>/FixPt Switch' incorporates:
   *  Constant: '<S429>/Constant'
   *  UnitDelay: '<S426>/Output'
   */
  if (localB->rtb_FixPtSum1_n_n > localP->WrapToZero_Threshold_h) {
    localDW->Output_DSTATE_o = localP->Constant_Value_a;
  } else {
    localDW->Output_DSTATE_o = localB->rtb_FixPtSum1_n_n;
  }

  /* End of Switch: '<S429>/FixPt Switch' */

  /* Sum: '<S507>/FixPt Sum1' incorporates:
   *  Constant: '<S507>/FixPt Constant'
   */
  localB->rtb_FixPtSum1_a_o = localB->rtb_Output_c +
    localP->FixPtConstant_Value_f5;

  /* Switch: '<S508>/FixPt Switch' incorporates:
   *  Constant: '<S508>/Constant'
   *  UnitDelay: '<S506>/Output'
   */
  if (localB->rtb_FixPtSum1_a_o > localP->WrapToZero_Threshold_d) {
    localDW->Output_DSTATE = localP->Constant_Value_k;
  } else {
    localDW->Output_DSTATE = localB->rtb_FixPtSum1_a_o;
  }

  /* End of Switch: '<S508>/FixPt Switch' */

  /* Constant: '<S3>/Constant' */
  *rty_Flag = localP->Constant_Value_c;

  /* UnitDelay: '<S222>/Output' */
  localB->rtb_Output_d_o = localDW->Output_DSTATE_a3;

  /* Sum: '<S229>/FixPt Sum1' incorporates:
   *  Constant: '<S229>/FixPt Constant'
   */
  localB->rtb_FixPtSum1_at_j = localB->rtb_Output_d_o +
    localP->FixPtConstant_Value_d;

  /* Switch: '<S230>/FixPt Switch' incorporates:
   *  Constant: '<S230>/Constant'
   *  UnitDelay: '<S222>/Output'
   */
  if (localB->rtb_FixPtSum1_at_j > localP->WrapToZero_Threshold_e) {
    localDW->Output_DSTATE_a3 = localP->Constant_Value_l;
  } else {
    localDW->Output_DSTATE_a3 = localB->rtb_FixPtSum1_at_j;
  }

  /* End of Switch: '<S230>/FixPt Switch' */
}

/* Update for atomic system: '<Root>/Flight Control System' */
void flightControlSystem_FlightControlSystem_Update
  (B_FlightControlSystem_flightControlSystem_T *localB,
   DW_FlightControlSystem_flightControlSystem_T *localDW,
   P_FlightControlSystem_flightControlSystem_T *localP)
{
  int32_T k;
  int32_T memOffset;

  /* Update for DiscreteIntegrator: '<S317>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE +=
    localP->DiscreteTimeIntegrator_gainval * localB->r;

  /* Update for Delay: '<S319>/MemoryX' */
  localDW->icLoad = 0U;
  localDW->MemoryX_DSTATE_n[0] = localB->Reshape_m[0];
  localDW->MemoryX_DSTATE_n[1] = localB->Reshape_m[1];

  /* Update for DiscreteFir: '<S253>/FIR_IMUaccel' */
  /* Update circular buffer index */
  localDW->FIR_IMUaccel_circBuf--;
  if (localDW->FIR_IMUaccel_circBuf < 0) {
    localDW->FIR_IMUaccel_circBuf = 4;
  }

  /* Update circular buffer */
  localDW->FIR_IMUaccel_states[localDW->FIR_IMUaccel_circBuf] =
    localB->inverseIMU_gain[0];
  localDW->FIR_IMUaccel_states[localDW->FIR_IMUaccel_circBuf + 5] =
    localB->inverseIMU_gain[1];
  localDW->FIR_IMUaccel_states[localDW->FIR_IMUaccel_circBuf + 10] =
    localB->inverseIMU_gain[2];

  /* End of Update for DiscreteFir: '<S253>/FIR_IMUaccel' */

  /* Update for Delay: '<S371>/MemoryX' */
  localDW->icLoad_m = 0U;

  /* Update for Delay: '<S251>/Delay2' */
  localDW->Delay2_DSTATE = localB->Reshapexhat[0];

  /* Update for Delay: '<S255>/MemoryX' */
  localDW->icLoad_f = 0U;

  /* Update for Delay: '<S371>/MemoryX' */
  localDW->MemoryX_DSTATE_g[0] = localB->Reshape_n[0];

  /* Update for Delay: '<S255>/MemoryX' */
  localDW->MemoryX_DSTATE[0] = localB->Reshape[0];

  /* Update for DiscreteFilter: '<S256>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[2] = localDW->pressureFilter_IIR_states[1];

  /* Update for DiscreteFilter: '<S256>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[2] = localDW->sonarFilter_IIR_states[1];

  /* Update for Delay: '<S371>/MemoryX' */
  localDW->MemoryX_DSTATE_g[1] = localB->Reshape_n[1];

  /* Update for Delay: '<S255>/MemoryX' */
  localDW->MemoryX_DSTATE[1] = localB->Reshape[1];

  /* Update for DiscreteFilter: '<S256>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[1] = localDW->pressureFilter_IIR_states[0];

  /* Update for DiscreteFilter: '<S256>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[1] = localDW->sonarFilter_IIR_states[0];

  /* Update for DiscreteFilter: '<S256>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[0] = localDW->pressureFilter_IIR_tmp;

  /* Update for DiscreteFilter: '<S256>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[0] = localDW->sonarFilter_IIR_tmp;

  /* Update for DiscreteTransferFcn: '<S253>/LPF Fcutoff = 40Hz1' */
  localDW->LPFFcutoff40Hz1_states = localDW->LPFFcutoff40Hz1_tmp;

  /* Update for DiscreteTransferFcn: '<S253>/LPF Fcutoff = 40Hz' */
  localDW->LPFFcutoff40Hz_states = localDW->LPFFcutoff40Hz_tmp;

  /* Update for DiscreteFilter: '<S253>/IIR_IMUgyro_r' */
  localDW->IIR_IMUgyro_r_states[4] = localDW->IIR_IMUgyro_r_states[3];
  localDW->IIR_IMUgyro_r_states[3] = localDW->IIR_IMUgyro_r_states[2];
  localDW->IIR_IMUgyro_r_states[2] = localDW->IIR_IMUgyro_r_states[1];
  localDW->IIR_IMUgyro_r_states[1] = localDW->IIR_IMUgyro_r_states[0];
  localDW->IIR_IMUgyro_r_states[0] = localDW->IIR_IMUgyro_r_tmp;
  for (k = 0; k < 2; k++) {
    /* Update for DiscreteFilter: '<S434>/IIRgyroz' */
    memOffset = k * 5;
    localDW->IIRgyroz_states[memOffset + 4] = localDW->IIRgyroz_states[memOffset
      + 3];
    localDW->IIRgyroz_states[memOffset + 3] = localDW->IIRgyroz_states[memOffset
      + 2];
    localDW->IIRgyroz_states[memOffset + 2] = localDW->IIRgyroz_states[memOffset
      + 1];
    localDW->IIRgyroz_states[memOffset + 1] = localDW->IIRgyroz_states[memOffset];
    localDW->IIRgyroz_states[memOffset] = localDW->IIRgyroz_tmp[k];

    /* Update for UnitDelay: '<S442>/UD'
     *
     * Block description for '<S442>/UD':
     *
     *  Store in Global RAM
     */
    localDW->UD_DSTATE[k] = localB->TSamp[k];

    /* Update for Delay: '<S430>/Delay' */
    localDW->Delay_DSTATE[k] = localB->Reshapexhat_d[k];
  }

  /* Update for Delay: '<S435>/MemoryX' */
  localDW->icLoad_a = 0U;
  localDW->MemoryX_DSTATE_d[0] = localB->Reshape_l[0];
  localDW->MemoryX_DSTATE_d[1] = localB->Reshape_l[1];
  localDW->MemoryX_DSTATE_d[2] = localB->Reshape_l[2];
  localDW->MemoryX_DSTATE_d[3] = localB->Reshape_l[3];

  /* Update for DiscreteIntegrator: '<S431>/SimplyIntegrateVelocity' incorporates:
   *  Constant: '<S1>/controlModePosVsOrient'
   */
  localDW->SimplyIntegrateVelocity_PrevResetState = (int8_T)
    localP->controlModePosVsOrient_Value;
  localDW->SimplyIntegrateVelocity_DSTATE[0] +=
    localP->SimplyIntegrateVelocity_gainval * localB->Product_k[0];

  /* Update for Delay: '<S6>/Delay1' */
  localDW->Delay1_DSTATE[0] = localB->Reshapexhat_d[0];

  /* Update for DiscreteIntegrator: '<S98>/Integrator' */
  localDW->Integrator_DSTATE[0] += localP->Integrator_gainval * localB->
    Switch_h[0];

  /* Update for DiscreteTransferFcn: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller' */
  localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[0] =
    localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_n[0];

  /* Update for DiscreteIntegrator: '<S198>/Integrator' */
  localDW->Integrator_DSTATE_k[0] += localP->Integrator_gainval_h *
    localB->Switch[0];

  /* Update for DiscreteIntegrator: '<S193>/Filter' */
  localDW->Filter_DSTATE[0] += localP->Filter_gainval *
    localB->FilterCoefficient[0];

  /* Update for DiscreteIntegrator: '<S431>/SimplyIntegrateVelocity' */
  localDW->SimplyIntegrateVelocity_DSTATE[1] +=
    localP->SimplyIntegrateVelocity_gainval * localB->Product_k[1];

  /* Update for Delay: '<S6>/Delay1' */
  localDW->Delay1_DSTATE[1] = localB->Reshapexhat_d[1];

  /* Update for DiscreteIntegrator: '<S98>/Integrator' */
  localDW->Integrator_DSTATE[1] += localP->Integrator_gainval * localB->
    Switch_h[1];

  /* Update for DiscreteTransferFcn: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller' */
  localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle[1] =
    localDW->LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_n[1];

  /* Update for DiscreteIntegrator: '<S198>/Integrator' */
  localDW->Integrator_DSTATE_k[1] += localP->Integrator_gainval_h *
    localB->Switch[1];

  /* Update for DiscreteIntegrator: '<S193>/Filter' */
  localDW->Filter_DSTATE[1] += localP->Filter_gainval *
    localB->FilterCoefficient[1];
}

/* Model step function */
void flightControlSystem_step(void)
{
  uint8_T rtb_Constant;

  /* Outputs for Atomic SubSystem: '<Root>/Flight Control System' */

  /* Inport: '<Root>/AC cmd' incorporates:
   *  Inport: '<Root>/Sensors'
   */
  flightControlSystem_FlightControlSystem(&cmd_inport, &sensor_inport,
    flightControlSystem_B.rtb_MotorDirections_m, &rtb_Constant,
    &flightControlSystem_B.FlightControlSystem,
    &flightControlSystem_DW.FlightControlSystem,
    &flightControlSystem_P.FlightControlSystem,
    &flightControlSystem_PrevZCX.FlightControlSystem);

  /* End of Outputs for SubSystem: '<Root>/Flight Control System' */

  /* SignalConversion generated from: '<Root>/Flight Control System' */
  motors_outport[0] = flightControlSystem_B.rtb_MotorDirections_m[0];
  motors_outport[1] = flightControlSystem_B.rtb_MotorDirections_m[1];
  motors_outport[2] = flightControlSystem_B.rtb_MotorDirections_m[2];
  motors_outport[3] = flightControlSystem_B.rtb_MotorDirections_m[3];

  /* SignalConversion generated from: '<Root>/Flight Control System' */
  flag_outport = rtb_Constant;

  /* Update for Atomic SubSystem: '<Root>/Flight Control System' */
  flightControlSystem_FlightControlSystem_Update
    (&flightControlSystem_B.FlightControlSystem,
     &flightControlSystem_DW.FlightControlSystem,
     &flightControlSystem_P.FlightControlSystem);

  /* End of Update for SubSystem: '<Root>/Flight Control System' */
}

/* Model initialize function */
void flightControlSystem_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  flightControlSystem_P.FlightControlSystem.SaturationSonar_LowerSat =
    rtMinusInf;
  flightControlSystem_PrevZCX.FlightControlSystem.Latchthestatus_Trig_ZCE_d =
    POS_ZCSIG;
  flightControlSystem_PrevZCX.FlightControlSystem.Latchthestatus_Trig_ZCE =
    POS_ZCSIG;
  flightControlSystem_PrevZCX.FlightControlSystem.TriggeredSubsystem_Trig_ZCE =
    UNINITIALIZED_ZCSIG;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Flight Control System' */
  flightControlSystem_FlightControlSystem_Init
    (&flightControlSystem_B.FlightControlSystem,
     &flightControlSystem_DW.FlightControlSystem,
     &flightControlSystem_P.FlightControlSystem,
     &flightControlSystem_PrevZCX.FlightControlSystem);

  /* End of SystemInitialize for SubSystem: '<Root>/Flight Control System' */
}

/* Model terminate function */
void flightControlSystem_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: flightControlSystem_private.h
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

#ifndef RTW_HEADER_flightControlSystem_private_h_
#define RTW_HEADER_flightControlSystem_private_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "flightControlSystem.h"

/* Imported (extern) pointer block signals */
extern uint8_T *imRGB;                 /* '<Root>/Image Data' */
extern real32_T rt_powf_snf(real32_T u0, real32_T u1);
extern real32_T rt_atan2f_snf(real32_T u0, real32_T u1);
extern void flightControlSystem_Geofencingerror(uint8_T *rty_Out1,
  P_Geofencingerror_flightControlSystem_T *localP);
extern void flightControlSystem_Logging(const CommandBus
  *rtu_ReferenceValueServerBus_Inport_4, const SensorsBus *rtu_Sensors_Inport_5);
extern void flightControlSystem_MeasurementUpdate_Init(real32_T rty_Lykyhatkk1[2],
  P_MeasurementUpdate_flightControlSystem_T *localP);
extern void flightControlSystem_MeasurementUpdate_Disable(real32_T
  rty_Lykyhatkk1[2], DW_MeasurementUpdate_flightControlSystem_T *localDW,
  P_MeasurementUpdate_flightControlSystem_T *localP);
extern void flightControlSystem_MeasurementUpdate(boolean_T rtu_Enable, const
  real32_T rtu_Lk[2], real32_T rtu_yk, const real32_T rtu_Ck[2], const real32_T
  rtu_xhatkk1[2], real32_T rtu_Dk, real32_T rtu_uk, real32_T rty_Lykyhatkk1[2],
  DW_MeasurementUpdate_flightControlSystem_T *localDW,
  P_MeasurementUpdate_flightControlSystem_T *localP);
extern void flightControlSystem_EnabledSubsystem_Init(real32_T rty_deltax[2],
  P_EnabledSubsystem_flightControlSystem_T *localP);
extern void flightControlSystem_EnabledSubsystem_Disable(real32_T rty_deltax[2],
  DW_EnabledSubsystem_flightControlSystem_T *localDW,
  P_EnabledSubsystem_flightControlSystem_T *localP);
extern void flightControlSystem_EnabledSubsystem(boolean_T rtu_Enable, const
  real32_T rtu_Mk[2], const real32_T rtu_Ck[2], real32_T rtu_yk, const real32_T
  rtu_xhatkk1[2], real32_T rty_deltax[2],
  DW_EnabledSubsystem_flightControlSystem_T *localDW,
  P_EnabledSubsystem_flightControlSystem_T *localP);
extern void flightControlSystem_FlightControlSystem_Init
  (B_FlightControlSystem_flightControlSystem_T *localB,
   DW_FlightControlSystem_flightControlSystem_T *localDW,
   P_FlightControlSystem_flightControlSystem_T *localP,
   ZCE_FlightControlSystem_flightControlSystem_T *localZCE);
extern void flightControlSystem_FlightControlSystem_Update
  (B_FlightControlSystem_flightControlSystem_T *localB,
   DW_FlightControlSystem_flightControlSystem_T *localDW,
   P_FlightControlSystem_flightControlSystem_T *localP);
extern void flightControlSystem_FlightControlSystem(const CommandBus
  *rtu_ReferenceValueServerCmds, const SensorsBus *rtu_Sensors, real32_T
  rty_motorCmds[4], uint8_T *rty_Flag,
  B_FlightControlSystem_flightControlSystem_T *localB,
  DW_FlightControlSystem_flightControlSystem_T *localDW,
  P_FlightControlSystem_flightControlSystem_T *localP,
  ZCE_FlightControlSystem_flightControlSystem_T *localZCE);

#endif                           /* RTW_HEADER_flightControlSystem_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

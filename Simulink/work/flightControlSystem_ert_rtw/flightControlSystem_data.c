/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: flightControlSystem_data.c
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

/* Block parameters (default storage) */
P_flightControlSystem_T flightControlSystem_P = {
  /* Variable: Sensors
   * Referenced by:
   *   '<S256>/SaturationSonar'
   *   '<S308>/Constant'
   */
  {
    { 1.00596, 1.00383, 0.99454 },

    { 0.99861, 1.00644, 0.99997 },

    {
      { 0.0, 0.0, 0.0 },

      { 0.0, 0.0, 0.0 },
      190.0,
      0.707,

      { 1.00596, 0.0, 0.0, 0.0, 1.00383, 0.0, 0.0, 0.0, 0.99454 },

      { 0.09, -0.06, 0.33699999999999974 },

      { -50.0, -50.0, -50.0, 50.0, 50.0, 50.0 },
      190.0,
      0.707,

      { 0.99861, 0.0, 0.0, 0.0, 1.00644, 0.0, 0.0, 0.0, 0.99997 },

      { -0.0095, -0.0075, 0.0015 },

      { 0.0, 0.0, 0.0 },

      { -10.0, -10.0, -10.0, 10.0, 10.0, 10.0 },

      { 41.0, 41.0, 41.0, 41.0, 41.0, 41.0 },

      { 0.8, 0.8, 0.8, 0.025, 0.025, 0.025 },

      { 0.00021831529882618725, 0.00018641345254680647, 0.00037251068300213613,
        1.0651514622688397e-8, 1.3021327403798377e-8, 1.1929474437781302e-8 }
    },

    {
      1.0,
      41.0
    },
    -99.0,
    -9.0,

    {
      { -99.0, 0.0, 0.0, -9.0 },
      0.0,

      { 3.5, 70.0 }
    },
    1.0,
    1.225,
    12.01725,
    101270.95,

    { 0.99407531114557246, 0.99618461293246863, 1.0054899752649467,
      1.0013919347893572, 0.99360120821906917, 1.0000300009000269 },
    0.44,
    1.0
  },

  /* Variable: modoOperacion
   * Referenced by: '<S5>/opMode'
   */
  1.0,

  /* Variable: puntoFinal
   * Referenced by: '<S238>/Final Point'
   */
  { -0.5, 1.0, -0.9 },

  /* Variable: puntosObjetivo
   * Referenced by: '<S247>/Waypoints'
   */
  { 0.0, 1.0, 1.0, -0.5, 0.0, 0.0, 1.1, 1.0, -0.9, -0.9, -0.9, -0.9, 0.0, 0.0,
    1.5882496193148399, 1.5882496193148399 },

  /* Variable: yawFinal
   * Referenced by: '<S238>/Final Yaw'
   */
  1.5882496193148399,

  /* Start of '<Root>/Flight Control System' */
  {
    /* Mask Parameter: outlierBelowFloor_const
     * Referenced by: '<S258>/Constant'
     */
    0.0,

    /* Mask Parameter: outlierJump_const
     * Referenced by: '<S311>/Constant'
     */
    0.1,

    /* Mask Parameter: currentEstimateVeryOffFromPressure_const
     * Referenced by: '<S309>/Constant'
     */
    0.8,

    /* Mask Parameter: currentStateVeryOffsonarflt_const
     * Referenced by: '<S310>/Constant'
     */
    0.4,

    /* Mask Parameter: Completefourcircles_const
     * Referenced by: '<S240>/Constant'
     */
    1.0,

    /* Mask Parameter: ComparewithStoptime_const
     * Referenced by: '<S243>/Constant'
     */
    5.0,

    /* Mask Parameter: Checkerrorcondition_const
     * Referenced by: '<S233>/Constant'
     */
    -1.0,

    /* Mask Parameter: u0continuousOFerrors_const
     * Referenced by: '<S232>/Constant'
     */
    50.0,

    /* Mask Parameter: Angularvelocitycontrolloop_D
     * Referenced by: '<S192>/Derivative Gain'
     */
    { 0.00012F, 9.72E-5F },

    /* Mask Parameter: Angularvelocitycontrolloop_I
     * Referenced by: '<S195>/Integral Gain'
     */
    { 0.006F, 0.00486F },

    /* Mask Parameter: Velocitycontroller_I
     * Referenced by: '<S95>/Integral Gain'
     */
    0.1F,

    /* Mask Parameter: DiscreteDerivative_ICPrevScaledInput
     * Referenced by: '<S442>/UD'
     */
    0.0F,

    /* Mask Parameter: Angularvelocitycontrolloop_InitialConditionForFilter
     * Referenced by: '<S193>/Filter'
     */
    0.0F,

    /* Mask Parameter: Velocitycontroller_InitialConditionForIntegrator
     * Referenced by: '<S98>/Integrator'
     */
    0.0F,

    /* Mask Parameter: Angularvelocitycontrolloop_InitialConditionForIntegrator
     * Referenced by: '<S198>/Integrator'
     */
    0.0F,

    /* Mask Parameter: Positioncontroller_LowerSaturationLimit
     * Referenced by: '<S55>/Saturation'
     */
    -0.5F,

    /* Mask Parameter: Velocitycontroller_LowerSaturationLimit
     * Referenced by:
     *   '<S105>/Saturation'
     *   '<S91>/DeadZone'
     */
    -0.34906584F,

    /* Mask Parameter: Angularvelocitycontrolloop_LowerSaturationLimit
     * Referenced by:
     *   '<S205>/Saturation'
     *   '<S191>/DeadZone'
     */
    -0.02F,

    /* Mask Parameter: Angularvelocitycontrolloop_N
     * Referenced by: '<S201>/Filter Coefficient'
     */
    { 70.0F, 70.0F },

    /* Mask Parameter: Positioncontroller_P
     * Referenced by: '<S53>/Proportional Gain'
     */
    0.7F,

    /* Mask Parameter: Velocitycontroller_P
     * Referenced by: '<S103>/Proportional Gain'
     */
    0.2F,

    /* Mask Parameter: Anglecontrolloop_P
     * Referenced by: '<S153>/Proportional Gain'
     */
    3.5F,

    /* Mask Parameter: Angularvelocitycontrolloop_P
     * Referenced by: '<S203>/Proportional Gain'
     */
    { 0.00288F, 0.00243F },

    /* Mask Parameter: Positioncontroller_UpperSaturationLimit
     * Referenced by: '<S55>/Saturation'
     */
    0.5F,

    /* Mask Parameter: Velocitycontroller_UpperSaturationLimit
     * Referenced by:
     *   '<S105>/Saturation'
     *   '<S91>/DeadZone'
     */
    0.34906584F,

    /* Mask Parameter: Angularvelocitycontrolloop_UpperSaturationLimit
     * Referenced by:
     *   '<S205>/Saturation'
     *   '<S191>/DeadZone'
     */
    0.02F,

    /* Mask Parameter: Checkifthedroneis03maboveground_const
     * Referenced by: '<S231>/Constant'
     */
    -0.3F,

    /* Mask Parameter: CompareToConstant_const
     * Referenced by: '<S313>/Constant'
     */
    6.867F,

    /* Mask Parameter: CompareToConstant1_const
     * Referenced by: '<S314>/Constant'
     */
    12.753F,

    /* Mask Parameter: maxp_const
     * Referenced by: '<S445>/Constant'
     */
    0.6F,

    /* Mask Parameter: maxq_const
     * Referenced by: '<S447>/Constant'
     */
    0.6F,

    /* Mask Parameter: maxw1_const
     * Referenced by: '<S449>/Constant'
     */
    7.0F,

    /* Mask Parameter: maxw2_const
     * Referenced by: '<S450>/Constant'
     */
    7.0F,

    /* Mask Parameter: maxdw1_const
     * Referenced by: '<S443>/Constant'
     */
    80.0F,

    /* Mask Parameter: maxdw2_const
     * Referenced by: '<S444>/Constant'
     */
    80.0F,

    /* Mask Parameter: maxp2_const
     * Referenced by: '<S446>/Constant'
     */
    0.5F,

    /* Mask Parameter: maxq2_const
     * Referenced by: '<S448>/Constant'
     */
    0.5F,

    /* Mask Parameter: maxw3_const
     * Referenced by: '<S451>/Constant'
     */
    5.0F,

    /* Mask Parameter: maxw4_const
     * Referenced by: '<S452>/Constant'
     */
    5.0F,

    /* Mask Parameter: minHeightforOF_const
     * Referenced by: '<S453>/Constant'
     */
    -0.4F,

    /* Mask Parameter: DeactivateAccelerationIfOFisnotusedduetolowaltitude_const
     * Referenced by: '<S437>/Constant'
     */
    -0.4F,

    /* Mask Parameter: donotuseaccifopticalflowneveravailableNoteOF60HzbutZOHto200_con
     * Referenced by: '<S439>/Constant'
     */
    0.0F,

    /* Mask Parameter: donotuseaccifopticalflowneveravailableNoteOF60HzbutZOHto2001_co
     * Referenced by: '<S440>/Constant'
     */
    0.0F,

    /* Mask Parameter: CompareToConstant_const_m
     * Referenced by: '<S216>/Constant'
     */
    10.0F,

    /* Mask Parameter: CompareToConstant1_const_g
     * Referenced by: '<S217>/Constant'
     */
    10.0F,

    /* Mask Parameter: CompareToConstant2_const
     * Referenced by: '<S218>/Constant'
     */
    6.0F,

    /* Mask Parameter: CompareToConstant4_const
     * Referenced by: '<S220>/Constant'
     */
    0.01F,

    /* Mask Parameter: CompareToConstant3_const
     * Referenced by: '<S219>/Constant'
     */
    6.0F,

    /* Mask Parameter: CompareToConstant5_const
     * Referenced by: '<S221>/Constant'
     */
    0.01F,

    /* Mask Parameter: WrapToZero_Threshold
     * Referenced by: '<S249>/FixPt Switch'
     */
    4294967295U,

    /* Mask Parameter: WrapToZero_Threshold_h
     * Referenced by: '<S429>/FixPt Switch'
     */
    4294967295U,

    /* Mask Parameter: WrapToZero_Threshold_d
     * Referenced by: '<S508>/FixPt Switch'
     */
    4294967295U,

    /* Mask Parameter: WrapToZero_Threshold_e
     * Referenced by: '<S230>/FixPt Switch'
     */
    4294967295U,

    /* Mask Parameter: CompareToConstant_const_d
     * Referenced by: '<S505>/Constant'
     */
    800U,

    /* Mask Parameter: CompareToConstant_const_n
     * Referenced by: '<S425>/Constant'
     */
    1U,

    /* Mask Parameter: Wait5seconds_const
     * Referenced by: '<S246>/Constant'
     */
    1000U,

    /* Expression: 0
     * Referenced by: '<S226>/ Disable OF check'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S226>/ '
     */
    0.0,

    /* Computed Parameter: Complete_Y0
     * Referenced by: '<S250>/Complete'
     */
    0.0,

    /* Computed Parameter: Toyaw_Y0
     * Referenced by: '<S247>/To yaw'
     */
    0.0,

    /* Expression: .25
     * Referenced by: '<S247>/Look ahead distance'
     */
    0.25,

    /* Expression: 1
     * Referenced by: '<S247>/Constant'
     */
    1.0,

    /* Expression: [0 0 -1]
     * Referenced by: '<S238>/Startup Waypoints'
     */
    { 0.0, 0.0, -1.0 },

    /* Expression: 0
     * Referenced by: '<S238>/Switch1'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S238>/Switch2'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S305>/L*(y[k]-yhat[k|k-1])'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S307>/deltax'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S423>/Constant'
     */
    0.0,

    /* Expression: pInitialization.M
     * Referenced by: '<S320>/KalmanGainM'
     */
    { 0.0011869299883620552, -3.2868164179443354E-5 },

    /* Expression: pInitialization.M
     * Referenced by: '<S372>/KalmanGainM'
     */
    { 0.0011869299883620552, -3.2868164179443354E-5 },

    /* Expression: pInitialization.M
     * Referenced by: '<S454>/KalmanGainM'
     */
    { 0.066408162001371535, 0.0, -0.021605460397771489, 0.0, 0.0,
      0.066408162001371535, 0.0, -0.021605460397771493 },

    /* Expression: pInitialization.L
     * Referenced by: '<S454>/KalmanGainL'
     */
    { 0.066516189303360354, 5.23402355848703E-19, -0.021605460397771867,
      -4.8628553107267881E-19, 4.3622439914025292E-18, 0.066516189303360354,
      -4.5659075919712689E-17, -0.021605460397771864 },

    /* Expression: 0
     * Referenced by: '<S251>/Delay2'
     */
    0.0,

    /* Expression: pInitialization.X0
     * Referenced by: '<S255>/X0'
     */
    { -0.046, 0.0 },

    /* Expression: -inf
     * Referenced by: '<S256>/SaturationSonar'
     */
    0.0,

    /* Expression: Estimator.alt.filterSonarNum
     * Referenced by: '<S256>/sonarFilter_IIR'
     */
    { 3.7568380197861018E-6, 1.1270514059358305E-5, 1.1270514059358305E-5,
      3.7568380197861018E-6 },

    /* Expression: Estimator.alt.filterSonarDen
     * Referenced by: '<S256>/sonarFilter_IIR'
     */
    { 1.0, -2.9371707284498907, 2.8762997234793319, -0.939098940325283 },

    /* Expression: 0
     * Referenced by: '<S256>/sonarFilter_IIR'
     */
    0.0,

    /* Expression: pInitialization.M
     * Referenced by: '<S259>/KalmanGainM'
     */
    { 0.02624142064187163, 0.0697767360714917 },

    /* Expression: pInitialization.C
     * Referenced by: '<S255>/C'
     */
    { 1.0, 0.0 },

    /* Expression: [0 0 -g]
     * Referenced by: '<S432>/gravity'
     */
    { 0.0, 0.0, -9.81 },

    /* Expression: 1
     * Referenced by: '<S432>/gainaccinput1'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<S5>/Switch1'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S5>/roll'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S5>/pitch'
     */
    0.0,

    /* Expression: pInitialization.A
     * Referenced by: '<S255>/A'
     */
    { 1.0, 0.0, 0.005, 1.0 },

    /* Expression: [0 0 g]
     * Referenced by: '<S251>/gravity'
     */
    { 0.0, 0.0, 9.81 },

    /* Expression: pInitialization.L
     * Referenced by: '<S372>/KalmanGainL'
     */
    { 0.0011870943291829544, -3.2868164179443428E-5 },

    /* Expression: pInitialization.L
     * Referenced by: '<S320>/KalmanGainL'
     */
    { 0.0011870943291829544, -3.2868164179443428E-5 },

    /* Expression: pInitialization.B
     * Referenced by: '<S255>/B'
     */
    { 0.0, 0.005 },

    /* Expression: pInitialization.D
     * Referenced by: '<S255>/D'
     */
    0.0,

    /* Expression: pInitialization.L
     * Referenced by: '<S259>/KalmanGainL'
     */
    { 0.026590304322229058, 0.06977673607149236 },

    /* Expression: 0.0
     * Referenced by: '<S226>/Delay One Step'
     */
    0.0,

    /* Expression: 0.5
     * Referenced by: '<S215>/0.5 meters'
     */
    0.5,

    /* Expression: pInitialization.Z
     * Referenced by: '<S454>/CovarianceZ'
     */
    { 1.3281632400274306, 0.0, -0.43210920795542973, 0.0, 0.0,
      1.3281632400274306, 0.0, -0.43210920795542984, -0.43210920795542979, 0.0,
      6.14734986237778, 0.0, 0.0, -0.43210920795542984, 0.0, 6.14734986237778 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S259>/CovarianceZ'
     */
    { 0.0026241420641871633, 0.0069776736071491688, 0.0069776736071491688,
      0.037607692935055337 },

    /* Expression: pInitialization.P0
     * Referenced by: '<S255>/P0'
     */
    { 0.0026948589925820388, 0.0071657120718244521, 0.0071657120718244521,
      0.03810769293505533 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S320>/CovarianceZ'
     */
    { 1097.3834951572255, -30.388465402591859, -30.388465402591855,
      7.2223686232128914 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S372>/CovarianceZ'
     */
    { 1097.3834951572255, -30.388465402591859, -30.388465402591855,
      7.2223686232128914 },

    /* Expression: pInitialization.G
     * Referenced by: '<S255>/G'
     */
    { 0.0, 1.0 },

    /* Expression: 200*3
     * Referenced by: '<S3>/Wait  3 Seconds'
     */
    600.0,

    /* Expression: pInitialization.H
     * Referenced by: '<S255>/H'
     */
    0.0,

    /* Expression: pInitialization.N
     * Referenced by: '<S255>/N'
     */
    0.0,

    /* Expression: pInitialization.Q
     * Referenced by: '<S255>/Q'
     */
    0.0005,

    /* Expression: pInitialization.R
     * Referenced by: '<S255>/R'
     */
    0.1,

    /* Computed Parameter: Pitchcorrection_Value
     * Referenced by: '<S7>/Pitch correction'
     */
    0.002F,

    /* Computed Parameter: zerocorrection_Value
     * Referenced by: '<S7>/zero correction'
     */
    0.0F,

    /* Computed Parameter: Zero_Value
     * Referenced by: '<S2>/Zero'
     */
    0.0F,

    /* Computed Parameter: D_yaw_Gain
     * Referenced by: '<S10>/D_yaw'
     */
    0.0012F,

    /* Computed Parameter: P_yaw_Gain
     * Referenced by: '<S10>/P_yaw'
     */
    0.004F,

    /* Computed Parameter: D_z_Gain
     * Referenced by: '<S11>/D_z'
     */
    0.33F,

    /* Computed Parameter: P_z_Gain
     * Referenced by: '<S11>/P_z'
     */
    0.34F,

    /* Computed Parameter: P_z1_Gain
     * Referenced by: '<S11>/P_z1'
     */
    1.15F,

    /* Computed Parameter: SaturationThrust_UpperSat
     * Referenced by: '<S11>/SaturationThrust'
     */
    1.20204329F,

    /* Computed Parameter: SaturationThrust_LowerSat
     * Referenced by: '<S11>/SaturationThrust'
     */
    -1.20204329F,

    /* Computed Parameter: Gain_Gain
     * Referenced by: '<S8>/Gain'
     */
    { -1.0F, 1.0F },

    /* Computed Parameter: _Value_p
     * Referenced by: '<S215>/    '
     */
    0.0F,

    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S241>/Out1'
     */
    0.0F,

    /* Computed Parameter: X_Y0
     * Referenced by: '<S244>/X'
     */
    0.0F,

    /* Computed Parameter: Y_Y0
     * Referenced by: '<S244>/Y'
     */
    0.0F,

    /* Computed Parameter: Tocontroller_Y0
     * Referenced by: '<S247>/To controller'
     */
    0.0F,

    /* Computed Parameter: Landinglookaheaddistance_Value
     * Referenced by: '<S237>/Landing look-ahead distance'
     */
    0.2F,

    /* Computed Parameter: Center_Value
     * Referenced by: '<S235>/ Center'
     */
    { 0.5F, 0.5F, -1.0F },

    /* Computed Parameter: yaw_Value
     * Referenced by: '<S235>/yaw'
     */
    5.28F,

    /* Computed Parameter: Switch2_Threshold_e
     * Referenced by: '<S235>/Switch2'
     */
    0.0F,

    /* Computed Parameter: Gain_Gain_a
     * Referenced by: '<S423>/Gain'
     */
    0.00228F,

    /* Computed Parameter: Out1_Y0_k
     * Referenced by: '<S427>/Out1'
     */
    0.0F,

    /* Computed Parameter: Lykyhatkk1_Y0_f
     * Referenced by: '<S502>/L*(y[k]-yhat[k|k-1])'
     */
    0.0F,

    /* Computed Parameter: deltax_Y0_l
     * Referenced by: '<S504>/deltax'
     */
    0.0F,

    /* Computed Parameter: Gain_Gain_d
     * Referenced by: '<S436>/Gain'
     */
    -1.0F,

    /* Computed Parameter: opticalFlowErrorCorrect_Gain
     * Referenced by: '<S436>/opticalFlowErrorCorrect'
     */
    1.15F,

    /* Expression: Controller.Q2Ts
     * Referenced by: '<S7>/TorqueTotalThrustToThrustPerMotor'
     */
    { 0.25F, 0.25F, 0.25F, 0.25F, 103.573624F, -103.573624F, 103.573624F,
      -103.573624F, -5.66592F, -5.66592F, 5.66592F, 5.66592F, -5.66592F,
      5.66592F, 5.66592F, -5.66592F },

    /* Computed Parameter: A_Value_g
     * Referenced by: '<S435>/A'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, -0.005F, 0.0F, 1.0F, 0.0F,
      0.0F, -0.005F, 0.0F, 1.0F },

    /* Computed Parameter: DiscreteTimeIntegrator_gainval
     * Referenced by: '<S317>/Discrete-Time Integrator'
     */
    0.005F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC
     * Referenced by: '<S317>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: X0_Value_f
     * Referenced by: '<S319>/X0'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: Assumingthatthepreflightcalibrationwasdoneatlevelorientation_Bi
     * Referenced by: '<S253>/Assuming that the  preflight calibration was done at level orientation'
     */
    { 0.0F, 0.0F, 9.81F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: inverseIMU_gain_Gain
     * Referenced by: '<S253>/inverseIMU_gain'
     */
    { 0.994075298F, 0.996184587F, 1.00549F, 1.00139189F, 0.993601203F, 1.00003F
    },

    /* Computed Parameter: FIR_IMUaccel_InitialStates
     * Referenced by: '<S253>/FIR_IMUaccel'
     */
    0.0F,

    /* Computed Parameter: FIR_IMUaccel_Coefficients
     * Referenced by: '<S253>/FIR_IMUaccel'
     */
    { 0.0264077242F, 0.140531361F, 0.33306092F, 0.33306092F, 0.140531361F,
      0.0264077242F },

    /* Computed Parameter: Gain2_Gain
     * Referenced by: '<S315>/Gain2'
     */
    0.101936802F,

    /* Computed Parameter: Constant_Value_o
     * Referenced by: '<S318>/Constant'
     */
    2.0F,

    /* Computed Parameter: C_Value_p
     * Referenced by: '<S319>/C'
     */
    { 1.0F, 0.0F },

    /* Computed Parameter: X0_Value_f2
     * Referenced by: '<S371>/X0'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: C_Value_o
     * Referenced by: '<S371>/C'
     */
    { 1.0F, 0.0F },

    /* Computed Parameter: C_Value_c
     * Referenced by: '<S435>/C'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: B_Value_g
     * Referenced by: '<S435>/B'
     */
    { 0.005F, 0.0F, 0.0F, 0.0F, 0.0F, 0.005F, 0.0F, 0.0F },

    /* Computed Parameter: invertzaxisGain_Gain
     * Referenced by: '<S251>/invertzaxisGain'
     */
    -1.0F,

    /* Computed Parameter: prsToAltGain_Gain
     * Referenced by: '<S251>/prsToAltGain'
     */
    0.0832137167F,

    /* Computed Parameter: pressureFilter_IIR_NumCoef
     * Referenced by: '<S256>/pressureFilter_IIR'
     */
    { 3.75683794E-6F, 1.12705138E-5F, 1.12705138E-5F, 3.75683794E-6F },

    /* Computed Parameter: pressureFilter_IIR_DenCoef
     * Referenced by: '<S256>/pressureFilter_IIR'
     */
    { 1.0F, -2.93717074F, 2.87629962F, -0.939098954F },

    /* Computed Parameter: pressureFilter_IIR_InitialStates
     * Referenced by: '<S256>/pressureFilter_IIR'
     */
    0.0F,

    /* Computed Parameter: LPFFcutoff40Hz1_NumCoef
     * Referenced by: '<S253>/LPF Fcutoff = 40Hz1'
     */
    { 1.0F, 1.0F },

    /* Computed Parameter: LPFFcutoff40Hz1_DenCoef
     * Referenced by: '<S253>/LPF Fcutoff = 40Hz1'
     */
    { 2.5915494F, -0.591549456F },

    /* Computed Parameter: LPFFcutoff40Hz1_InitialStates
     * Referenced by: '<S253>/LPF Fcutoff = 40Hz1'
     */
    0.0F,

    /* Computed Parameter: LPFFcutoff40Hz_NumCoef
     * Referenced by: '<S253>/LPF Fcutoff = 40Hz'
     */
    { 1.0F, 1.0F },

    /* Computed Parameter: LPFFcutoff40Hz_DenCoef
     * Referenced by: '<S253>/LPF Fcutoff = 40Hz'
     */
    { 2.5915494F, -0.591549456F },

    /* Computed Parameter: LPFFcutoff40Hz_InitialStates
     * Referenced by: '<S253>/LPF Fcutoff = 40Hz'
     */
    0.0F,

    /* Computed Parameter: IIR_IMUgyro_r_NumCoef
     * Referenced by: '<S253>/IIR_IMUgyro_r'
     */
    { 0.282124132F, 1.27253926F, 2.42084408F, 2.42084408F, 1.27253926F,
      0.282124132F },

    /* Computed Parameter: IIR_IMUgyro_r_DenCoef
     * Referenced by: '<S253>/IIR_IMUgyro_r'
     */
    { 1.0F, 2.22871494F, 2.52446198F, 1.57725322F, 0.54102242F, 0.0795623958F },

    /* Computed Parameter: IIR_IMUgyro_r_InitialStates
     * Referenced by: '<S253>/IIR_IMUgyro_r'
     */
    0.0F,

    /* Computed Parameter: Constant_Value_gu
     * Referenced by: '<S317>/Constant'
     */
    0.0F,

    /* Computed Parameter: Gain1_Gain
     * Referenced by: '<S433>/Gain1'
     */
    -1.0F,

    /* Computed Parameter: IIRgyroz_NumCoef
     * Referenced by: '<S434>/IIRgyroz'
     */
    { 0.282124132F, 1.27253926F, 2.42084408F, 2.42084408F, 1.27253926F,
      0.282124132F },

    /* Computed Parameter: IIRgyroz_DenCoef
     * Referenced by: '<S434>/IIRgyroz'
     */
    { 1.0F, 2.22871494F, 2.52446198F, 1.57725322F, 0.54102242F, 0.0795623958F },

    /* Computed Parameter: IIRgyroz_InitialStates
     * Referenced by: '<S434>/IIRgyroz'
     */
    0.0F,

    /* Computed Parameter: TSamp_WtEt
     * Referenced by: '<S442>/TSamp'
     */
    200.0F,

    /* Computed Parameter: Delay_InitialCondition
     * Referenced by: '<S430>/Delay'
     */
    0.0F,

    /* Computed Parameter: D_Value_o
     * Referenced by: '<S435>/D'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: X0_Value_d
     * Referenced by: '<S435>/X0'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: SimplyIntegrateVelocity_gainval
     * Referenced by: '<S431>/SimplyIntegrateVelocity'
     */
    0.005F,

    /* Computed Parameter: SimplyIntegrateVelocity_IC
     * Referenced by: '<S431>/SimplyIntegrateVelocity'
     */
    0.0F,

    /* Computed Parameter: Zero1_Value
     * Referenced by: '<S2>/Zero1'
     */
    1.0F,

    /* Computed Parameter: OrbitRadius_Value
     * Referenced by: '<S239>/Orbit Radius'
     */
    0.4F,

    /* Computed Parameter: ClockwiseOrbit_Value
     * Referenced by: '<S239>/Clockwise Orbit'
     */
    1.0F,

    /* Computed Parameter: LookaheadDistance_Value
     * Referenced by: '<S239>/Lookahead Distance'
     */
    0.3F,

    /* Computed Parameter: Center_Value_e
     * Referenced by: '<S239>/ Center'
     */
    { 0.5F, 0.5F, -1.0F },

    /* Computed Parameter: ClockwiseOrbit1_Value
     * Referenced by: '<S239>/Clockwise Orbit1'
     */
    1.0F,

    /* Computed Parameter: ClockwiseOrbit2_Value
     * Referenced by: '<S239>/Clockwise Orbit2'
     */
    1.57079637F,

    /* Computed Parameter: Delay1_InitialCondition
     * Referenced by: '<S6>/Delay1'
     */
    0.0F,

    /* Computed Parameter: Integrator_gainval
     * Referenced by: '<S98>/Integrator'
     */
    0.005F,

    /* Computed Parameter: LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrolle
     * Referenced by: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller'
     */
    { 1.0F, 1.0F },

    /* Computed Parameter: LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_e
     * Referenced by: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller'
     */
    { 8.95774746F, -6.95774698F },

    /* Computed Parameter: LPF8HzCutoffFiltertoavoidoscillationsinducedbypositioncontrol_i
     * Referenced by: '<S8>/LPF 8Hz Cutoff Filter to avoid oscillations  induced by position controller'
     */
    0.0F,

    /* Computed Parameter: Integrator_gainval_h
     * Referenced by: '<S198>/Integrator'
     */
    0.005F,

    /* Computed Parameter: Filter_gainval
     * Referenced by: '<S193>/Filter'
     */
    0.005F,

    /* Computed Parameter: w0_Value
     * Referenced by: '<S11>/w0'
     */
    -0.61803F,

    /* Computed Parameter: ThrustToMotorCommand_Gain
     * Referenced by: '<S12>/ThrustToMotorCommand'
     */
    -1530.72681F,

    /* Expression: Vehicle.Motor.maxLimit
     * Referenced by: '<S12>/Saturation5'
     */
    500.0F,

    /* Expression: Vehicle.Motor.minLimit
     * Referenced by: '<S12>/Saturation5'
     */
    10.0F,

    /* Computed Parameter: MotorDirections_Gain
     * Referenced by: '<S12>/MotorDirections'
     */
    { 1.0F, -1.0F, 1.0F, -1.0F },

    /* Computed Parameter: A_Value_l
     * Referenced by: '<S319>/A'
     */
    { 1.0F, 0.0F, -0.005F, 1.0F },

    /* Computed Parameter: A_Value_b
     * Referenced by: '<S371>/A'
     */
    { 1.0F, 0.0F, -0.005F, 1.0F },

    /* Computed Parameter: B_Value_p
     * Referenced by: '<S371>/B'
     */
    { 0.005F, 0.0F },

    /* Computed Parameter: D_Value_f
     * Referenced by: '<S371>/D'
     */
    0.0F,

    /* Computed Parameter: B_Value_n
     * Referenced by: '<S319>/B'
     */
    { 0.005F, 0.0F },

    /* Computed Parameter: D_Value_n
     * Referenced by: '<S319>/D'
     */
    0.0F,

    /* Computed Parameter: ZeroGain_Gain
     * Referenced by: '<S189>/ZeroGain'
     */
    0.0F,

    /* Computed Parameter: Constant1_Value
     * Referenced by: '<S189>/Constant1'
     */
    0.0F,

    /* Computed Parameter: ZeroGain_Gain_a
     * Referenced by: '<S89>/ZeroGain'
     */
    0.0F,

    /* Computed Parameter: Constant1_Value_k
     * Referenced by: '<S89>/Constant1'
     */
    0.0F,

    /* Computed Parameter: Gain_Gain_i
     * Referenced by: '<S3>/Gain'
     */
    1.0F,

    /* Computed Parameter: Gain1_Gain_l
     * Referenced by: '<S3>/Gain1'
     */
    1.0F,

    /* Computed Parameter: P0_Value_n
     * Referenced by: '<S435>/P0'
     */
    { 1.42263806F, 0.0F, -0.462845951F, 0.0F, 0.0F, 1.42263806F, 0.0F,
      -0.462845951F, -0.462845951F, 0.0F, 6.15735F, 0.0F, 0.0F, -0.462845951F,
      0.0F, 6.15735F },

    /* Computed Parameter: G_Value_h
     * Referenced by: '<S435>/G'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: Q_Value_g
     * Referenced by: '<S435>/Q'
     */
    { 0.09F, 0.0F, 0.0F, 0.0F, 0.0F, 0.09F, 0.0F, 0.0F, 0.0F, 0.0F, 0.01F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.01F },

    /* Computed Parameter: H_Value_l
     * Referenced by: '<S435>/H'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: N_Value_g
     * Referenced by: '<S435>/N'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: P0_Value_m
     * Referenced by: '<S319>/P0'
     */
    { 1098.6875F, -30.4245777F, -30.4245777F, 7.22336864F },

    /* Computed Parameter: G_Value_l
     * Referenced by: '<S319>/G'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: Q_Value_c
     * Referenced by: '<S319>/Q'
     */
    { 1.0F, 0.0F, 0.0F, 0.001F },

    /* Computed Parameter: P0_Value_j
     * Referenced by: '<S371>/P0'
     */
    { 1098.6875F, -30.4245777F, -30.4245777F, 7.22336864F },

    /* Computed Parameter: G_Value_a
     * Referenced by: '<S371>/G'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: Q_Value_e
     * Referenced by: '<S371>/Q'
     */
    { 1.0F, 0.0F, 0.0F, 0.001F },

    /* Computed Parameter: R_Value_o
     * Referenced by: '<S435>/R'
     */
    { 20.0F, 0.0F, 0.0F, 20.0F },

    /* Computed Parameter: H_Value_f
     * Referenced by: '<S319>/H'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: N_Value_c
     * Referenced by: '<S319>/N'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: H_Value_p
     * Referenced by: '<S371>/H'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: N_Value_i
     * Referenced by: '<S371>/N'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: R_Value_a
     * Referenced by: '<S319>/R'
     */
    924556.188F,

    /* Computed Parameter: R_Value_e
     * Referenced by: '<S371>/R'
     */
    924556.188F,

    /* Computed Parameter: Output_InitialCondition
     * Referenced by: '<S506>/Output'
     */
    0U,

    /* Computed Parameter: Output_InitialCondition_b
     * Referenced by: '<S426>/Output'
     */
    0U,

    /* Computed Parameter: Output_InitialCondition_k
     * Referenced by: '<S245>/Output'
     */
    0U,

    /* Computed Parameter: FixPtConstant_Value
     * Referenced by: '<S248>/FixPt Constant'
     */
    1U,

    /* Computed Parameter: Constant_Value_d
     * Referenced by: '<S249>/Constant'
     */
    0U,

    /* Computed Parameter: FixPtConstant_Value_f
     * Referenced by: '<S428>/FixPt Constant'
     */
    1U,

    /* Computed Parameter: Constant_Value_a
     * Referenced by: '<S429>/Constant'
     */
    0U,

    /* Computed Parameter: FixPtConstant_Value_f5
     * Referenced by: '<S507>/FixPt Constant'
     */
    1U,

    /* Computed Parameter: Constant_Value_k
     * Referenced by: '<S508>/Constant'
     */
    0U,

    /* Computed Parameter: FixPtConstant_Value_d
     * Referenced by: '<S229>/FixPt Constant'
     */
    1U,

    /* Computed Parameter: Output_InitialCondition_c
     * Referenced by: '<S222>/Output'
     */
    0U,

    /* Computed Parameter: Constant_Value_l
     * Referenced by: '<S230>/Constant'
     */
    0U,

    /* Computed Parameter: controlModePosVsOrient_Value
     * Referenced by: '<S1>/controlModePosVsOrient'
     */
    1,

    /* Expression: switch_mode
     * Referenced by: '<S13>/Switch Control'
     */
    0,

    /* Computed Parameter: F_Value
     * Referenced by: '<S226>/  F'
     */
    0,

    /* Computed Parameter: F_Value_j
     * Referenced by: '<S215>/  F'
     */
    0,

    /* Computed Parameter: ManualSwitch_CurrentSetting
     * Referenced by: '<S7>/Manual Switch'
     */
    0U,

    /* Computed Parameter: Landed_Value
     * Referenced by: '<S225>/Landed'
     */
    255U,

    /* Computed Parameter: No_error_Value
     * Referenced by: '<S225>/No_error'
     */
    0U,

    /* Computed Parameter: Disabletemperaturecompensation_CurrentSetting
     * Referenced by: '<S423>/Disable temperature compensation'
     */
    1U,

    /* Computed Parameter: Merge_InitialOutput
     * Referenced by: '<S3>/Merge'
     */
    0U,

    /* Computed Parameter: Constant_Value_c
     * Referenced by: '<S3>/Constant'
     */
    0U,

    /* Start of '<S398>/Enabled Subsystem' */
    {
      /* Computed Parameter: deltax_Y0
       * Referenced by: '<S422>/deltax'
       */
      0.0F
    }
    ,

    /* End of '<S398>/Enabled Subsystem' */

    /* Start of '<S391>/MeasurementUpdate' */
    {
      /* Computed Parameter: Lykyhatkk1_Y0
       * Referenced by: '<S420>/L*(y[k]-yhat[k|k-1])'
       */
      0.0F
    }
    ,

    /* End of '<S391>/MeasurementUpdate' */

    /* Start of '<S346>/Enabled Subsystem' */
    {
      /* Computed Parameter: deltax_Y0
       * Referenced by: '<S370>/deltax'
       */
      0.0F
    }
    ,

    /* End of '<S346>/Enabled Subsystem' */

    /* Start of '<S339>/MeasurementUpdate' */
    {
      /* Computed Parameter: Lykyhatkk1_Y0
       * Referenced by: '<S368>/L*(y[k]-yhat[k|k-1])'
       */
      0.0F
    }
    ,

    /* End of '<S339>/MeasurementUpdate' */

    /* Start of '<S3>/Ultrasound improper' */
    {
      /* Computed Parameter: Constant_Value
       * Referenced by: '<S227>/Constant'
       */
      88U
    }
    ,

    /* End of '<S3>/Ultrasound improper' */

    /* Start of '<S3>/No optical flow ' */
    {
      /* Computed Parameter: Constant_Value
       * Referenced by: '<S224>/Constant'
       */
      69U
    }
    ,

    /* End of '<S3>/No optical flow ' */

    /* Start of '<S3>/estimator//Optical flow error' */
    {
      /* Computed Parameter: Constant_Value
       * Referenced by: '<S228>/Constant'
       */
      99U
    }
    ,

    /* End of '<S3>/estimator//Optical flow error' */

    /* Start of '<S3>/Geofencing error' */
    {
      /* Computed Parameter: Constant_Value
       * Referenced by: '<S223>/Constant'
       */
      1U
    }
    /* End of '<S3>/Geofencing error' */
  }
  /* End of '<Root>/Flight Control System' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

---
layout: default
---

[back](./)

# ProSim Data Elements

The following table is a list of the ProSim data elements at the simulator *sends* to a TCP client

This is table is extracted from the ProSim AR XML interface. This is available on port 8080 of the ProSim Systems server. For example

    http://192.168.2.2:8080/xml?query=ids

| Name | Description | Type | Options |
|------|:------------|:-----|:--------|
|A_ASP_ADF_1_VOLUME| ASP ADF 1 vol volume | ANALOG | |
|A_ASP_ADF_2_VOLUME| ASP ADF 2 vol volume | ANALOG | |
|A_ASP_MARKER_VOLUME| ASP Marker vol volume | ANALOG | |
|A_ASP_NAV_1_VOLUME| ASP NAV 1 vol volume | ANALOG | |
|A_ASP_NAV_2_VOLUME| ASP NAV 2 vol volume | ANALOG | |
|A_ASP_PA_VOLUME| ASP PA vol volume | ANALOG | |
|A_ASP_SPKR_VOLUME| ASP Spkr vol volume | ANALOG | |
|A_ASP_VHF_1_VOLUME| ASP VHF 1 vol volume | ANALOG | |
|A_ASP_VHF_2_VOLUME| ASP VHF 2 vol volume | ANALOG | |
|A_ASP2_ADF_1_VOLUME| ASP FO ADF 1 vol volume | ANALOG | |
|A_ASP2_ADF_2_VOLUME| ASP FO ADF 2 vol volume | ANALOG | |
|A_ASP2_MARKER_VOLUME| ASP FO Marker vol volume | ANALOG | |
|A_ASP2_NAV_1_VOLUME| ASP FO NAV 1 vol volume | ANALOG | |
|A_ASP2_NAV_2_VOLUME| ASP FO NAV 2 vol volume | ANALOG | |
|A_ASP2_PA_VOLUME| ASP FO PA vol volume | ANALOG | |
|A_ASP2_SPKR_VOLUME| ASP FO Spkr vol volume | ANALOG | |
|A_ASP2_VHF_1_VOLUME| ASP FO VHF 1 vol volume | ANALOG | |
|A_ASP2_VHF_2_VOLUME| ASP FO VHF 2 vol volume | ANALOG | |
|A_ASP3_ADF_1_VOLUME| ASP OBS ADF 1 vol volume | ANALOG | |
|A_ASP3_ADF_2_VOLUME| ASP OBS ADF 2 vol volume | ANALOG | |
|A_ASP3_MARKER_VOLUME| ASP OBS Marker vol volume | ANALOG | |
|A_ASP3_NAV_1_VOLUME| ASP OBS NAV 1 vol volume | ANALOG | |
|A_ASP3_NAV_2_VOLUME| ASP OBS NAV 2 vol volume | ANALOG | |
|A_ASP3_PA_VOLUME| ASP OBS PA vol volume | ANALOG | |
|A_ASP3_SPKR_VOLUME| ASP OBS Spkr vol volume | ANALOG | |
|A_ASP3_VHF_1_VOLUME| ASP OBS VHF 1 vol volume | ANALOG | |
|A_ASP3_VHF_2_VOLUME| ASP OBS VHF 2 vol volume | ANALOG | |
|A_CDU1_BRIGHTNESS| CDU 1 brightness | ANALOG | |
|A_CDU2_BRIGHTNESS| CDU 2 brightness | ANALOG | |
|A_FC_AILERON_CAPT|  |  | |
|A_FC_AILERON_FO|  |  | |
|A_FC_ELEVATOR_CAPT|  |  | |
|A_FC_ELEVATOR_FO|  |  | |
|A_FC_RUDDER_CAPT|  |  | |
|A_FC_RUDDER_FO|  |  | |
|A_FC_TILLER_CAPT|  |  | |
|A_FC_TILLER_FO|  |  | |
|A_FC_TOEBRAKE_LEFT_CAPT|  |  | |
|A_FC_TOEBRAKE_LEFT_FO|  |  | |
|A_FC_TOEBRAKE_RIGHT_CAPT|  |  | |
|A_FC_TOEBRAKE_RIGHT_FO|  |  | |
|A_FLAP| Flap input | ANALOG | |
|A_MIP_BRIGHTNESS_DU_L| Lower DU Brightness | ANALOG | |
|A_MIP_BRIGHTNESS_DU_U| Upper DU Brightness | ANALOG | |
|A_MIP_BRIGHTNESS_LI| Left Inboard Brightness | ANALOG | |
|A_MIP_BRIGHTNESS_LI_INNER|  |  | |
|A_MIP_BRIGHTNESS_LO| Left Outboard Brightness | ANALOG | |
|A_MIP_BRIGHTNESS_RI| Right Inboard Brightness | ANALOG | |
|A_MIP_BRIGHTNESS_RI_INNER|  |  | |
|A_MIP_BRIGHTNESS_RO| Right Outboard Brightness | ANALOG | |
|A_MIP_PANEL| Panel lights | ANALOG | |
|A_RMP1_SENSE| RMP Capt sense | ANALOG | |
|A_RMP2_SENSE| RMP F/O sense | ANALOG | |
|A_SPEEDBRAKE| Speedbrake input | ANALOG | |
|A_THROTTLE_LEFT| Throttle input left | ANALOG | |
|A_THROTTLE_REVERSE_LEFT| Throttle reverser input left | ANALOG | |
|A_THROTTLE_REVERSE_RIGHT| Throttle reverser input right | ANALOG | |
|A_THROTTLE_RIGHT| Throttle input right | ANALOG | |
|A_WR_GAIN| Weather Radar Gain | ANALOG | |
|A_WR_TILT| Weather Radar Tilt | ANALOG | |
|B_ABOVE_TRANSITION_ALTITUDE| Above transition altitude | GATE | |
|B_AC_POWER| AC Power | GATE | |
|B_APU_RUNNING| APU running | GATE | |
|B_APU_STARTING| APU starting | GATE | |
|B_APU_STOPPING| APU stopping | GATE | |
|B_ASP_ALT| ASP ASP Alt Out | GATE | |
|B_ASP_BOOM| ASP ASP Boom Out | GATE | |
|B_ASP_IC| ASP ASP IC Out | GATE | |
|B_ASP_MASK| ASP ASP Mask Out | GATE | |
|B_ASP_NORM| ASP ASP Norm Out | GATE | |
|B_ASP_RT| ASP ASP RT Out | GATE | |
|B_ASP2_ALT| ASP FO ASP Alt Out | GATE | |
|B_ASP2_BOOM| ASP FO ASP Boom Out | GATE | |
|B_ASP2_IC| ASP FO ASP IC Out | GATE | |
|B_ASP2_MASK| ASP FO ASP Mask Out | GATE | |
|B_ASP2_NORM| ASP FO ASP Norm Out | GATE | |
|B_ASP2_RT| ASP FO ASP RT Out | GATE | |
|B_ASP3_ALT| ASP OBS ASP Alt Out | GATE | |
|B_ASP3_BOOM| ASP OBS ASP Boom Out | GATE | |
|B_ASP3_IC| ASP OBS ASP IC Out | GATE | |
|B_ASP3_MASK| ASP OBS ASP Mask Out | GATE | |
|B_ASP3_NORM| ASP OBS ASP Norm Out | GATE | |
|B_ASP3_RT| ASP OBS ASP RT Out | GATE | |
|B_ATTEND_ACTIVE| Attend active | GATE | |
|B_BRAKING| Braking | GATE | |
|B_DC_POWER| DC Power | GATE | |
|B_DOME_LIGHT_BRIGHT| Domelight bright | GATE | |
|B_DOME_LIGHT_DIM| Domelight dim | GATE | |
|B_DOME_LIGHT_MASTER| Domelight master | GATE | |
|B_EMERGENY_LIGHTS| Emergency exit lights | GATE | |
|B_FIRE_HANDLE_APU_LOCK| Fire handle unlock APU | GATE | |
|B_FIRE_HANDLE_LEFT_LOCK| Fire handle unlock Engine 1 | GATE | |
|B_FIRE_HANDLE_RIGHT_LOCK| Fire handle unlock Engine 2 | GATE | |
|B_FLAP_0| Flap gate up | GATE | |
|B_FLAP_1| Flap gate 1 | GATE | |
|B_FLAP_10| Flap gate 10 | GATE | |
|B_FLAP_15| Flap gate 15 | GATE | |
|B_FLAP_2| Flap gate 2 | GATE | |
|B_FLAP_25| Flap gate 25 | GATE | |
|B_FLAP_30| Flap gate 30 | GATE | |
|B_FLAP_40| Flap gate 40 | GATE | |
|B_FLAP_5| Flap gate 5 | GATE | |
|B_FLIGHTDECK_DOOR_LOCK|  |  | |
|B_FMA_PITCH_ALT_ACQ| FMA pitch mode ALT ACQ  | GATE | |
|B_FMA_PITCH_ALT_HOLD| FMA pitch mode ALT HOLD | GATE | |
|B_FMA_PITCH_FLARE| FMA pitch mode FLARE | GATE | |
|B_FMA_PITCH_GP| FMA pitch mode G/P | GATE | |
|B_FMA_PITCH_GS| FMA pitch mode G/S | GATE | |
|B_FMA_PITCH_MCP_SPD| FMA pitch mode MCP_SPD | GATE | |
|B_FMA_PITCH_TOGA| FMA pitch mode TOGA | GATE | |
|B_FMA_PITCH_VNAV_ALT| FMA pitch mode VNAV ALT  | GATE | |
|B_FMA_PITCH_VNAV_PATH| FMA pitch mode VNAV PATH | GATE | |
|B_FMA_PITCH_VNAV_SPD| FMA pitch mode VNAV SPD  | GATE | |
|B_FMA_PITCH_VS| FMA pitch mode V/S | GATE | |
|B_FMA_ROLL_BACKCOURSE| FMA roll mode HDG BACKCOURSE | GATE | |
|B_FMA_ROLL_FAC| FMA roll mode HDG FAC | GATE | |
|B_FMA_ROLL_HDG_SEL| FMA roll mode HDG SEL | GATE | |
|B_FMA_ROLL_LNAV| FMA roll mode HDG LNAV | GATE | |
|B_FMA_ROLL_VOR_LOC| FMA roll mode HDG VOR/LOG | GATE | |
|B_FMA_THRUST_ARM| FMA thrust mode ARM | GATE | |
|B_FMA_THRUST_FMC_SPD| FMA thrust mode FMC_SPD | GATE | |
|B_FMA_THRUST_GA| FMA thrust mode GA | GATE | |
|B_FMA_THRUST_MCP_SPD| FMA thrust mode MCP_SPD | GATE | |
|B_FMA_THRUST_N1| FMA thrust mode N1 | GATE | |
|B_FMA_THRUST_RETARD| FMA thrust mode RETARD | GATE | |
|B_FMA_THRUST_THR_HOLD| FMA thrust mode THR_HLD | GATE | |
|B_GEAR_HANDLE_RELEASE| Gear handle release solenoid | GATE | |
|B_GEAR_WIND| Gear wind | GATE | |
|B_GROUND_GATE| Ground gate | GATE | |
|B_HYDRAULICS_AVAILABLE| Hydraulics available | GATE | |
|B_HYDRAULICS_AVAILABLE_A| Hydraulics A available | GATE | |
|B_HYDRAULICS_AVAILABLE_B| Hydraulics B available | GATE | |
|B_INNER_MARKER| Inner marker | GATE | |
|B_IRS1_ATTITUDE| IRS 1 attitude | GATE | |
|B_IRS1_HEADING| IRS 1 heading | GATE | |
|B_IRS1_POSITION| IRS 1 position | GATE | |
|B_IRS2_ATTITUDE| IRS 2 attitude | GATE | |
|B_IRS2_HEADING| IRS 2 heading | GATE | |
|B_IRS2_POSITION| IRS 2 position | GATE | |
|B_KTS80| 80kts | GATE | |
|B_LIGHT_MASTER_DIM| Master Dim | GATE | |
|B_LIGHT_TEST| Light test | GATE | |
|B_MCP_AT_DISCONNECT_SOLENOID| A/T disconnect solenoid | GATE | |
|B_MCP_AT_HOLD_SOLENOID| A/T hold solenoid | GATE | |
|B_MCP_SPEED_FLASHING_A| MCP Speed flashing A | GATE | |
|B_MCP_SPEED_FLASHING_B| MCP Speed flashing B | GATE | |
|B_MIDDLE_MARKER| Middle marker | GATE | |
|B_MIP_AUTOBRAKE_RESET| Autobrake reset | GATE | |
|B_NO_SMOKING_SIGN| No smoking sign | GATE | |
|B_NOSEWHEEL_ROTATING| Nosewheel rotating | GATE | |
|B_OUTER_MARKER| Outer marker | GATE | |
|B_OVERHEAD_BACKLIGHT_MASTER| Overhead backlight master | GATE | |
|B_PACK_1_OPERATING| Pack L operating | GATE | |
|B_PACK_2_OPERATING| Pack R operating | GATE | |
|B_PANEL_LIGHT_CAPTAIN| Panel lights captain | GATE | |
|B_PANEL_LIGHT_CONTROL_STAND| Panel lights control stand | GATE | |
|B_PANEL_LIGHT_FLOOD| Panel lights flood | GATE | |
|B_PANEL_LIGHT_FO| Panel lights F/O | GATE | |
|B_PARKING_BRAKE_HOLD| Parking brake hold | GATE | |
|B_PARKING_BRAKE_RELEASE| Parking brake release | GATE | |
|B_PED_RUDDER_TRIM_IND_OFF| Rudder trim indicator OFF Flag | GATE | |
|B_PITCH_CMD| Autopilot pitch CMD | GATE | |
|B_PITCH_CWS| Autopilot pitch CWS | GATE | |
|B_PRESSURE_LOSS_HIGH| Pressure loss high | GATE | |
|B_PRESSURE_LOSS_LOW| Pressure loss low | GATE | |
|B_PRESSURISATION_DASHED| Pressurisation display dashed out | GATE | |
|B_PRESSURISATION_DISPLAY_POWER| Pressurisation display power | GATE | |
|B_RECIRCULATION_FAN_1| Recirc Fan L running | GATE | |
|B_RECIRCULATION_FAN_2| Recirc Fan R running | GATE | |
|B_ROLL_CMD| Autopilot roll CMD | GATE | |
|B_ROLL_CWS| Autopilot roll CWS | GATE | |
|B_SEATBELT_SIGN| Seatbelt sign | GATE | |
|B_SPEED_BRAKE| Speedbrake extended | GATE | |
|B_SPEED_BRAKE_AIR| Speedbrake extended in air | GATE | |
|B_SPEED_BRAKE_DEPLOY| Speedbrake autodeploy | GATE | |
|B_SPEED_BRAKE_RESTOW| Speedbrake autorestow | GATE | |
|B_STARTER_PB_SOLENOID_1| Starter 1 pushback solenoid | GATE | |
|B_STARTER_PB_SOLENOID_2| Starter 2 pushback solenoid | GATE | |
|B_STARTER_SOLENOID_1| Starter 1 solenoid | GATE | |
|B_STARTER_SOLENOID_2| Starter 2 solenoid | GATE | |
|B_STICKSHAKER| Stick shaker | GATE | |
|B_STICKSHAKER_FO| Stick shaker F/O | GATE | |
|B_THROTTLE_SERVO_POWER_LEFT| Throttle Servo Power left | GATE | |
|B_THROTTLE_SERVO_POWER_RIGHT| Throttle Servo Power right | GATE | |
|B_TRIM_MOTOR_DOWN| Trim motor down | GATE | |
|B_TRIM_MOTOR_UP| Trim motor up | GATE | |
|B_USER_1| User 1 out | GATE | |
|B_USER_10| User 10 out | GATE | |
|B_USER_11| User 11 out | GATE | |
|B_USER_12| User 12 out | GATE | |
|B_USER_13| User 13 out | GATE | |
|B_USER_14| User 14 out | GATE | |
|B_USER_15| User 15 out | GATE | |
|B_USER_16| User 16 out | GATE | |
|B_USER_17| User 17 out | GATE | |
|B_USER_18| User 18 out | GATE | |
|B_USER_19| User 19 out | GATE | |
|B_USER_2| User 2 out | GATE | |
|B_USER_20| User 20 out | GATE | |
|B_USER_3| User 3 out | GATE | |
|B_USER_4| User 4 out | GATE | |
|B_USER_5| User 5 out | GATE | |
|B_USER_6| User 6 out | GATE | |
|B_USER_7| User 7 out | GATE | |
|B_USER_8| User 8 out | GATE | |
|B_USER_9| User 9 out | GATE | |
|B_V1| V1 | GATE | |
|B_V2| V2 | GATE | |
|B_VR| VRotate | GATE | |
|B_WING_ANTI_ICE_HOLD_ACTUATOR| Wing Anti-Ice hold actuator | GATE | |
|B_WING_ANTI_ICE_OFF_ACTUATOR| Wing Anti-Ice off actuator | GATE | |
|B_WIPER_HIGH_L| Wiper left High | GATE | |
|B_WIPER_HIGH_R| Wiper right High | GATE | |
|B_WIPER_INT_L| Wiper left Int | GATE | |
|B_WIPER_INT_R| Wiper right Int | GATE | |
|B_WIPER_LOW_L| Wiper left Low | GATE | |
|B_WIPER_LOW_R| Wiper right Low | GATE | |
|B_YAW_DAMPER_HOLD_ACTUATOR| Yaw damper hold actuator | GATE | |
|B_YAW_DAMPER_OFF_ACTUATOR| Yaw damper off actuator | GATE | |
|CB_P18_1_B7_GPWS_115|  |  | |
|CB_P6_3_B7_CROSSFEED_28|  |  | |
|D_OH_ELEC| Electric Panel | LCD | |
|D_OH_IRS| IRS Display | LCD | |
|E_FLIGHTALT| Flight alt in encoder | ENCODER | |
|E_LANDALT| Land alt in encoder | ENCODER | |
|E_MCP_ALT| MCP ALT VAL encoder | ENCODER | |
|E_MCP_COURSE1| MCP COURSE 1 VAL encoder | ENCODER | |
|E_MCP_COURSE2| MCP COURSE 2 VAL encoder | ENCODER | |
|E_MCP_EFIS1_BARO| EFIS 1 baro | ENCODER | |
|E_MCP_EFIS1_MINIMUMS| EFIS 1 minimums | ENCODER | |
|E_MCP_EFIS2_BARO| EFIS 2 baro | ENCODER | |
|E_MCP_EFIS2_MINIMUMS| EFIS 2 minimums | ENCODER | |
|E_MCP_HEADING| MCP HEADING VAL encoder | ENCODER | |
|E_MCP_SPEED| MCP SPEED VAL encoder | ENCODER | |
|E_MCP_VS| MCP V/S VAL encoder | ENCODER | |
|E_MIP_CHRONO_CAPT_ENCODER| Chrono capt encoder | ENCODER | |
|E_MIP_CHRONO_FO_ENCODER| Chrono f/o encoder | ENCODER | |
|E_MIP_ISFD_BARO| ISFD baro encoder | ENCODER | |
|E_MIP_N1_SET| N1 SET Rotary | ENCODER | |
|E_MIP_SPD_REF| SPD REF Rotary | ENCODER | |
|E_MIP_STANDBY_ALTIMETER_QNH| Standby altimeter QNH momentary | SWITCH | Center,Up,Down,Up fast,Down fast|
|E_RADIO_ADF1_HUNDREDS| Radio ADF1 hundreds active | ENCODER | |
|E_RADIO_ADF1_INNER| Radio ADF1 inner shaft | ENCODER | |
|E_RADIO_ADF1_INNER_ACTIVE| Radio ADF1 inner shaft active | ENCODER | |
|E_RADIO_ADF1_OUTER| Radio ADF1 outer shaft | ENCODER | |
|E_RADIO_ADF1_OUTER_ACTIVE| Radio ADF1 outer shaft active | ENCODER | |
|E_RADIO_ADF2_HUNDREDS| Radio ADF2 hundreds active | ENCODER | |
|E_RADIO_ADF2_INNER| Radio ADF2 inner shaft | ENCODER | |
|E_RADIO_ADF2_INNER_ACTIVE| Radio ADF2 inner shaft active | ENCODER | |
|E_RADIO_ADF2_OUTER| Radio ADF2 outer shaft | ENCODER | |
|E_RADIO_ADF2_OUTER_ACTIVE| Radio ADF2 outer shaft active | ENCODER | |
|E_RADIO_COM1_INNER| Radio COM1 inner shaft | ENCODER | |
|E_RADIO_COM1_OUTER| Radio COM1 outer shaft | ENCODER | |
|E_RADIO_COM2_INNER| Radio COM2 inner shaft | ENCODER | |
|E_RADIO_COM2_OUTER| Radio COM2 outer shaft | ENCODER | |
|E_RADIO_COM3_INNER| Radio COM3 inner shaft | ENCODER | |
|E_RADIO_COM3_OUTER| Radio COM3 outer shaft | ENCODER | |
|E_RADIO_NAV1_INNER| Radio NAV1 inner shaft | ENCODER | |
|E_RADIO_NAV1_OUTER| Radio NAV1 outer shaft | ENCODER | |
|E_RADIO_NAV2_INNER| Radio NAV2 inner shaft | ENCODER | |
|E_RADIO_NAV2_OUTER| Radio NAV2 outer shaft | ENCODER | |
|E_RADIO_RMP1_INNER| RMP Capt inner encoder | ENCODER | |
|E_RADIO_RMP1_OUTER| RMP Capt outer encoder | ENCODER | |
|E_RADIO_RMP2_INNER| RMP F/O inner encoder | ENCODER | |
|E_RADIO_RMP2_OUTER| RMP F/O outer encoder | ENCODER | |
|E_RADIO_XPDR_INNER_LEFT| Radio XPDR inner shaft left | ENCODER | |
|E_RADIO_XPDR_INNER_RIGHT| Radio XPDR inner shaft right | ENCODER | |
|E_RADIO_XPDR_OUTER_LEFT| Radio XPDR outer shaft left | ENCODER | |
|E_RADIO_XPDR_OUTER_RIGHT| Radio XPDR outer shaft right | ENCODER | |
|F_GPWS|  |  | |
|G_MIP_BRAKE_PRESSURE| Brake pressure | GAUGE | |
|G_MIP_FLAP| Flap | GAUGE | |
|G_MIP_FLAP_RIGHT| Flap right | GAUGE | |
|G_MIP_STDBY_ALTIMETER| Standby altimeter | GAUGE | |
|G_MIP_STDBY_ATT_BANK| Standby Attitude bank | GAUGE | |
|G_MIP_STDBY_ATT_PITCH| Standby Attitude pitch | GAUGE | |
|G_MIP_STDBY_BARBERPOLE| Standby barberpole | GAUGE | |
|G_MIP_STDBY_GLIDESLOPE| Standby Glideslope | GAUGE | |
|G_MIP_STDBY_LOCALISER| Standby Localiser | GAUGE | |
|G_MIP_STDBY_SPEED| Standby speed | GAUGE | |
|G_MIP_WET_COMPASS| Wet compass | GAUGE | |
|G_MIP_YAW_DAMPER| Yaw damper gauge | GAUGE | |
|G_OH_CABIN_ALT| Cabin altitude | GAUGE | |
|G_OH_CABIN_VSI| Cabin VSI | GAUGE | |
|G_OH_CREW_OXYGEN| Oxygen pressure | GAUGE | |
|G_OH_DUCT_PRESS_L| Pressure Left | GAUGE | |
|G_OH_DUCT_PRESS_R| Pressure Right | GAUGE | |
|G_OH_EGT| APU | GAUGE | |
|G_OH_FUEL_TEMP| Fuel Temperature | GAUGE | |
|G_OH_OUTFLOW_VALVE| Outflow valve position | GAUGE | |
|G_OH_PRESS_DIFF| Pressure differential | GAUGE | |
|G_OH_TEMPERATURE| Cabin temperature | GAUGE | |
|G_PED_ELEV_TRIM| Elevator trim gauge | GAUGE | |
|G_PED_RUDDER_TRIM| Rudder trim gauge | GAUGE | |
|G_SPEEDBRAKE| Speedbrake servo | GAUGE | |
|G_THROTTLE_LEFT| Throttle Servo left | GAUGE | |
|G_THROTTLE_RIGHT| Throttle Servo right | GAUGE | |
|I_ASP_ADF_1_REC| ASP ADF 1 vol | INDICATOR | |
|I_ASP_ADF_2_REC| ASP ADF 2 vol | INDICATOR | |
|I_ASP_MARKER_REC| ASP Marker vol | INDICATOR | |
|I_ASP_NAV_1_REC| ASP NAV 1 vol | INDICATOR | |
|I_ASP_NAV_2_REC| ASP NAV 2 vol | INDICATOR | |
|I_ASP_PA_REC| ASP PA vol | INDICATOR | |
|I_ASP_SPKR_REC| ASP Spkr vol | INDICATOR | |
|I_ASP_VHF_1_REC| ASP VHF 1 vol | INDICATOR | |
|I_ASP_VHF_1_SEND| ASP VHF 1 mic | INDICATOR | |
|I_ASP_VHF_2_REC| ASP VHF 2 vol | INDICATOR | |
|I_ASP_VHF_2_SEND| ASP VHF 2 mic | INDICATOR | |
|I_ASP2_ADF_1_REC| ASP FO ADF 1 vol | INDICATOR | |
|I_ASP2_ADF_2_REC| ASP FO ADF 2 vol | INDICATOR | |
|I_ASP2_MARKER_REC| ASP FO Marker vol | INDICATOR | |
|I_ASP2_NAV_1_REC| ASP FO NAV 1 vol | INDICATOR | |
|I_ASP2_NAV_2_REC| ASP FO NAV 2 vol | INDICATOR | |
|I_ASP2_PA_REC| ASP FO PA vol | INDICATOR | |
|I_ASP2_SPKR_REC| ASP FO Spkr vol | INDICATOR | |
|I_ASP2_VHF_1_REC| ASP FO VHF 1 vol | INDICATOR | |
|I_ASP2_VHF_1_SEND| ASP FO VHF 1 mic | INDICATOR | |
|I_ASP2_VHF_2_REC| ASP FO VHF 2 vol | INDICATOR | |
|I_ASP2_VHF_2_SEND| ASP FO VHF 2 mic | INDICATOR | |
|I_ASP3_ADF_1_REC| ASP OBS ADF 1 vol | INDICATOR | |
|I_ASP3_ADF_2_REC| ASP OBS ADF 2 vol | INDICATOR | |
|I_ASP3_MARKER_REC| ASP OBS Marker vol | INDICATOR | |
|I_ASP3_NAV_1_REC| ASP OBS NAV 1 vol | INDICATOR | |
|I_ASP3_NAV_2_REC| ASP OBS NAV 2 vol | INDICATOR | |
|I_ASP3_PA_REC| ASP OBS PA vol | INDICATOR | |
|I_ASP3_SPKR_REC| ASP OBS Spkr vol | INDICATOR | |
|I_ASP3_VHF_1_REC| ASP OBS VHF 1 vol | INDICATOR | |
|I_ASP3_VHF_1_SEND| ASP OBS VHF 1 mic | INDICATOR | |
|I_ASP3_VHF_2_REC| ASP OBS VHF 2 vol | INDICATOR | |
|I_ASP3_VHF_2_SEND| ASP OBS VHF 2 mic | INDICATOR | |
|I_CDU1_CALL| CDU CALL light | INDICATOR | |
|I_CDU1_EXEC| CDU EXEC light | INDICATOR | |
|I_CDU1_FAIL| CDU FAIL light | INDICATOR | |
|I_CDU1_MSG| CDU MSG light | INDICATOR | |
|I_CDU1_OFFSET| CDU OFFSET light | INDICATOR | |
|I_CDU2_CALL| CDU2 CALL light | INDICATOR | |
|I_CDU2_EXEC| CDU2 EXEC light | INDICATOR | |
|I_CDU2_FAIL| CDU2 FAIL light | INDICATOR | |
|I_CDU2_MSG| CDU2 MSG light | INDICATOR | |
|I_CDU2_OFFSET| CDU2 OFFSET light | INDICATOR | |
|I_DOOR_AUTO_UNLOCK| Door auto unlock | INDICATOR | |
|I_DOOR_LOCK_FAIL| Door lock fail | INDICATOR | |
|I_FIRE_1| Engine 1 fire handle light | INDICATOR | |
|I_FIRE_2| Engine 2 fire handle light | INDICATOR | |
|I_FIRE_APU| APU fire handle light | INDICATOR | |
|I_FIRE_APU_BOTTLE_DISCHARGE| APU bottle discharged | INDICATOR | |
|I_FIRE_APU_DET_INOPT| Fire APU Det Inop | INDICATOR | |
|I_FIRE_CARGO_AFT| Cargo fire indicator aft | INDICATOR | |
|I_FIRE_CARGO_AFT_EXT| Cargo fire ext light aft | INDICATOR | |
|I_FIRE_CARGO_ARMED_AFT| Cargo fire armed aft | INDICATOR | |
|I_FIRE_CARGO_ARMED_FWD| Cargo fire armed fwd | INDICATOR | |
|I_FIRE_CARGO_DETECTOR_FAULT| Cargo fire detector fault | INDICATOR | |
|I_FIRE_CARGO_DISCH| Cargo fire disch light | INDICATOR | |
|I_FIRE_CARGO_FWD| Cargo fire indicator fwd | INDICATOR | |
|I_FIRE_CARGO_FWD_EXT| Cargo fire ext light fwd | INDICATOR | |
|I_FIRE_ENG_1_OVT| Engine 1 overheat | INDICATOR | |
|I_FIRE_ENG_2_OVT| Engine 2 overheat | INDICATOR | |
|I_FIRE_FAULT| Fire Fault | INDICATOR | |
|I_FIRE_L_BOTTLE_DISCHARGE| L bottle discharged | INDICATOR | |
|I_FIRE_R_BOTTLE_DISCHARGE| R bottle discharged | INDICATOR | |
|I_FIRE_TEST_APU| APU bottle indicator | INDICATOR | |
|I_FIRE_TEST_L| L bottle indicator | INDICATOR | |
|I_FIRE_TEST_R| R bottle indicator | INDICATOR | |
|I_FIRE_WHEEL_WELL_OVT| Fire Wheel well | INDICATOR | |
|I_FW_CP| Fire warning 1 | INDICATOR | |
|I_FW_FO| Fire warning 2 | INDICATOR | |
|I_MC_AIRCOND| Warn AIR_COND | INDICATOR | |
|I_MC_ANTIICE| Warn ANTI_ICE | INDICATOR | |
|I_MC_APU| Warn APU | INDICATOR | |
|I_MC_CP| Master caution 1 | INDICATOR | |
|I_MC_DOORS| Warn DOORS | INDICATOR | |
|I_MC_ELEC| Warn ELEC | INDICATOR | |
|I_MC_ENG| Warn ENG | INDICATOR | |
|I_MC_FLT_CONT| Warn FLT_CONT | INDICATOR | |
|I_MC_FO| Master caution 2 | INDICATOR | |
|I_MC_FUEL| Warn FUEL | INDICATOR | |
|I_MC_HYDRAULICS| Warn HYD | INDICATOR | |
|I_MC_IRS| Warn IRS | INDICATOR | |
|I_MC_OVERHEAD| Warn OVERHEAD | INDICATOR | |
|I_MC_OVHT| Warn OVHT_DET | INDICATOR | |
|I_MCP_ALT_HOLD| MCP Alt hold | INDICATOR | |
|I_MCP_APP| MCP APP | INDICATOR | |
|I_MCP_AT| MCP A/T | INDICATOR | |
|I_MCP_CMD_A| MCP CMD A | INDICATOR | |
|I_MCP_CMD_B| MCP CMD B | INDICATOR | |
|I_MCP_CWS_A| MCP CWS A | INDICATOR | |
|I_MCP_CWS_B| MCP CWS B | INDICATOR | |
|I_MCP_FCCA| MCP FCC A Master | INDICATOR | |
|I_MCP_FCCB| MCP FCC B Master | INDICATOR | |
|I_MCP_HDG_SEL| MCP HDG SEL | INDICATOR | |
|I_MCP_LNAV| MCP LNAV | INDICATOR | |
|I_MCP_LVLCHANGE| MCP Level Change | INDICATOR | |
|I_MCP_N1| MCP N1 | INDICATOR | |
|I_MCP_SPEED| MCP Speed | INDICATOR | |
|I_MCP_VNAV| MCP VNAV | INDICATOR | |
|I_MCP_VORLOC| MCP VOR/LOC | INDICATOR | |
|I_MCP_VS| MCP V/S | INDICATOR | |
|I_MIP_ANTI_SKID_INOP| Anti skid INOP | INDICATOR | |
|I_MIP_ASA_APA_1| ASA A/P Amber Capt | INDICATOR | |
|I_MIP_ASA_APA_2| ASA A/P Amber F/O | INDICATOR | |
|I_MIP_ASA_APR_1| ASA A/P Red Capt | INDICATOR | |
|I_MIP_ASA_APR_2| ASA A/P Red F/O | INDICATOR | |
|I_MIP_ASA_ATA_1| ASA A/T Amber Capt | INDICATOR | |
|I_MIP_ASA_ATA_2| ASA A/T Amber F/O | INDICATOR | |
|I_MIP_ASA_ATR_1| ASA A/T Red Capt | INDICATOR | |
|I_MIP_ASA_ATR_2| ASA A/T Red F/O | INDICATOR | |
|I_MIP_ASA_FMC_1| ASA FMC Capt | INDICATOR | |
|I_MIP_ASA_FMC_2| ASA FMC F/O | INDICATOR | |
|I_MIP_AUTOBRAKE_DISARM| Autobrake disarm | INDICATOR | |
|I_MIP_AUTOLAND| Autoland | INDICATOR | |
|I_MIP_BELOW_GS_CP| Below GS CP | INDICATOR | |
|I_MIP_BELOW_GS_FO| Below GS FO | INDICATOR | |
|I_MIP_BRAKE_TEMP| Brake Temp | INDICATOR | |
|I_MIP_CABIN_ALTITUDE| Cabin altitude indicator | INDICATOR | |
|I_MIP_FLAP_LOAD_RELIEF| Flap load relief | INDICATOR | |
|I_MIP_GEAR_LEFT_DOWN| Gear left | INDICATOR | |
|I_MIP_GEAR_LEFT_TRANSIT| Gear left transit | INDICATOR | |
|I_MIP_GEAR_NOSE_DOWN| Gear nose | INDICATOR | |
|I_MIP_GEAR_NOSE_TRANSIT| Gear nose transit | INDICATOR | |
|I_MIP_GEAR_RIGHT_DOWN| Gear right | INDICATOR | |
|I_MIP_GEAR_RIGHT_TRANSIT| Gear right transit | INDICATOR | |
|I_MIP_GPWS_INOP| GPWS Inop | INDICATOR | |
|I_MIP_LE_FLAP_EXT| LE Flap Extend | INDICATOR | |
|I_MIP_LE_FLAP_TRANSIT| LE Flap Transit | INDICATOR | |
|I_MIP_PARKING_BRAKE| Parking brake | INDICATOR | |
|I_MIP_RUNWAY_INOP| Runway Inop | INDICATOR | |
|I_MIP_SPEEDBRAKE_DO_NOT_ARM| Speed brake do not arm | INDICATOR | |
|I_MIP_SPOILER_ARMED| Spoiler Armed | INDICATOR | |
|I_MIP_SPOILER_EXTEND| Spoiler Extend | INDICATOR | |
|I_MIP_STAB_OUT_OF_TRIM| Stab out of trim | INDICATOR | |
|I_MIP_TAKEOFF_CONFIG| Takeoff config | INDICATOR | |
|I_NONE|  |  | |
|I_OH_ALPHA_VANE1| Alpha Vane Heat L | INDICATOR | |
|I_OH_ALPHA_VANE2| Alpha Vane Heat R | INDICATOR | |
|I_OH_APU_FAULT| APU FAULT | INDICATOR | |
|I_OH_APU_GEN_OFF| APU GEN OFF BUS | INDICATOR | |
|I_OH_APU_LOW_OIL_PRESSURE| APU Low oil pressure | INDICATOR | |
|I_OH_APU_MAINT| APU Maint | INDICATOR | |
|I_OH_APU_OVERSPEED| APU Overspeed | INDICATOR | |
|I_OH_ATTEND| Attend call | INDICATOR | |
|I_OH_AUTO_SLAT| Auto slat Fail | INDICATOR | |
|I_OH_AUX_PITOT| auxPitot Heat | INDICATOR | |
|I_OH_BATT_DISCHARGE| Bat discharge | INDICATOR | |
|I_OH_BLEED_TRIP_L| Bleed trip off 1 | INDICATOR | |
|I_OH_BLEED_TRIP_R| Bleed trip off 2 | INDICATOR | |
|I_OH_CAPT_PITOT| Capt Pitot Heat | INDICATOR | |
|I_OH_CO_PITOT| Copilot Pitot Heat | INDICATOR | |
|I_OH_COWL_AI_L| Cowl Anti-Ice L | INDICATOR | |
|I_OH_COWL_AI_R| Cowl Anti-Ice R | INDICATOR | |
|I_OH_COWL_VALVE_L| Cowl valve open L | INDICATOR | |
|I_OH_COWL_VALVE_R| Cowl valve open R | INDICATOR | |
|I_OH_CROSSFEED| Crossfeed indicator | INDICATOR | |
|I_OH_DOOR_AFT_CARGO| Door Aft Cargo | INDICATOR | |
|I_OH_DOOR_AFT_ENTRY| Door Aft Entry | INDICATOR | |
|I_OH_DOOR_AFT_SERVICE| Door Aft Service | INDICATOR | |
|I_OH_DOOR_AIRSTAIRS| Door Air Stairs | INDICATOR | |
|I_OH_DOOR_EQUIP| Door Equip | INDICATOR | |
|I_OH_DOOR_FWD_CARGO| Door Fwd Cargo | INDICATOR | |
|I_OH_DOOR_FWD_ENTRY| Door Fwd entry | INDICATOR | |
|I_OH_DOOR_FWD_SERVICE| Door Fwd Service | INDICATOR | |
|I_OH_DOOR_LEFT_AFT_OVERWING| Door Left Aft Overwing | INDICATOR | |
|I_OH_DOOR_LEFT_FWD_OVERWING| Door Left Fwd Overwing | INDICATOR | |
|I_OH_DOOR_RIGHT_AFT_OVERWING| Door Right Aft Overwing | INDICATOR | |
|I_OH_DOOR_RIGHT_FWD_OVERWING| Door Right Fwd Overwing | INDICATOR | |
|I_OH_DRIVE1| Drive 1 | INDICATOR | |
|I_OH_DRIVE2| Drive 2 | INDICATOR | |
|I_OH_DUALBLEED| Dual bleed | INDICATOR | |
|I_OH_EEC_ALTN1| EEC Altn left | INDICATOR | |
|I_OH_EEC_ALTN2| EEC Altn right | INDICATOR | |
|I_OH_EEC1| EEC On left | INDICATOR | |
|I_OH_EEC2| EEC On right | INDICATOR | |
|I_OH_ELEC| ELEC | INDICATOR | |
|I_OH_ELEC_HYD_PUMP_1| Hyd ELEC1 LP | INDICATOR | |
|I_OH_ELEC_HYD_PUMP_2| Hyd ELEC2 LP | INDICATOR | |
|I_OH_ELEC_HYD_PUMP_OVHT_1| Hyd ELEC1 OVHT | INDICATOR | |
|I_OH_ELEC_HYD_PUMP_OVHT_2| Hyd ELEC2 OVHT | INDICATOR | |
|I_OH_ELEV_PITOT1| Elev pitot Heat L | INDICATOR | |
|I_OH_ELEV_PITOT2| Elev pitot Heat R | INDICATOR | |
|I_OH_ELT| ELT | INDICATOR | |
|I_OH_EMERG_EXIT_LIGHTS| Emerg Exit Lights not armed | INDICATOR | |
|I_OH_ENG_HYD_PUMP_L| Hyd ENG1 LP | INDICATOR | |
|I_OH_ENG_HYD_PUMP_R| Hyd ENG2 LP | INDICATOR | |
|I_OH_ENG_VALVE_CLOSED_L| ENG Valve Closed L | INDICATOR | |
|I_OH_ENG_VALVE_CLOSED_R| ENG Valve Closed R | INDICATOR | |
|I_OH_ENGINE_CONTROL1| Engine control left | INDICATOR | |
|I_OH_ENGINE_CONTROL2| Engine control right | INDICATOR | |
|I_OH_EQUIP_COOLING_EXHAUST| Equip cooling exhaust Off | INDICATOR | |
|I_OH_EQUIP_COOLING_SUPPLY| Equip cooling supply Off | INDICATOR | |
|I_OH_FEEL_DIFF_PRESS| Feel Diff Press | INDICATOR | |
|I_OH_FILTER_BYPASS1| Filter Bypass L | INDICATOR | |
|I_OH_FILTER_BYPASS2| Filter Bypass R | INDICATOR | |
|I_OH_FLIGHT_REC| Flight recorder off | INDICATOR | |
|I_OH_FLT_CTRL_LOW_PRESS_A| FLT Control low pressure A | INDICATOR | |
|I_OH_FLT_CTRL_LOW_PRESS_B| FLT Control low pressure B | INDICATOR | |
|I_OH_FUEL_PUMP_CL| Fuel Center Left LP | INDICATOR | |
|I_OH_FUEL_PUMP_CR| Fuel Center Right LP | INDICATOR | |
|I_OH_FUEL_PUMP_LA| Fuel Left Aft LP | INDICATOR | |
|I_OH_FUEL_PUMP_LF| Fuel Left Fwd LP | INDICATOR | |
|I_OH_FUEL_PUMP_RA| Fuel Right Aft LP | INDICATOR | |
|I_OH_FUEL_PUMP_RF| Fuel Right Fwd LP | INDICATOR | |
|I_OH_GEAR_LEFT_DOWN| Gear left aft oh | INDICATOR | |
|I_OH_GEAR_NOSE_DOWN| Gear nose aft ovh | INDICATOR | |
|I_OH_GEAR_RIGHT_DOWN| Gear right aft ovh | INDICATOR | |
|I_OH_GEN_BUS_OFF1| GEN BUS OFF 1 | INDICATOR | |
|I_OH_GEN_BUS_OFF2| GEN BUS OFF 2 | INDICATOR | |
|I_OH_GLS| GLS | INDICATOR | |
|I_OH_GPS| GPS | INDICATOR | |
|I_OH_GROUND_POWER_AVAILABLE| Grd Pwr available | INDICATOR | |
|I_OH_HYD_STBY_LOW_PRESS| Hyd standby low pressure | INDICATOR | |
|I_OH_HYD_STBY_LOW_QUANT| Hyd standby low quantity | INDICATOR | |
|I_OH_ILS| ILS | INDICATOR | |
|I_OH_IRS_ALIGN_L| IRS left align | INDICATOR | |
|I_OH_IRS_ALIGN_R| IRS right align | INDICATOR | |
|I_OH_IRS_CLR_KEY| IRS Keypad CLR cue | INDICATOR | |
|I_OH_IRS_DCFAIL_L| IRS left DC Fail | INDICATOR | |
|I_OH_IRS_DCFAIL_R| IRS right DC Fail | INDICATOR | |
|I_OH_IRS_DOT1| IRS Panel dot 1 | INDICATOR | |
|I_OH_IRS_DOT2| IRS Panel dot 2 | INDICATOR | |
|I_OH_IRS_DOT3| IRS Panel dot 3 | INDICATOR | |
|I_OH_IRS_DOT4| IRS Panel dot 4 | INDICATOR | |
|I_OH_IRS_DOT5| IRS Panel dot 5 | INDICATOR | |
|I_OH_IRS_DOT6| IRS Panel dot 6 | INDICATOR | |
|I_OH_IRS_ENT_KEY| IRS Keypad ENT cue | INDICATOR | |
|I_OH_IRS_FAULT_L| IRS left Fault | INDICATOR | |
|I_OH_IRS_FAULT_R| IRS right Fault | INDICATOR | |
|I_OH_IRS_ONDC_L| IRS left On DC | INDICATOR | |
|I_OH_IRS_ONDC_R| IRS right On DC | INDICATOR | |
|I_OH_LAV_SMOKE| Lavatory smoke | INDICATOR | |
|I_OH_LEDEVICES_EXT_FLAP1| Flaps extended 1 | INDICATOR | |
|I_OH_LEDEVICES_EXT_FLAP2| Flaps extended 2 | INDICATOR | |
|I_OH_LEDEVICES_EXT_FLAP3| Flaps extended 3 | INDICATOR | |
|I_OH_LEDEVICES_EXT_FLAP4| Flaps extended 4 | INDICATOR | |
|I_OH_LEDEVICES_EXT_SLAT1| Slats extended 1 | INDICATOR | |
|I_OH_LEDEVICES_EXT_SLAT2| Slats extended 2 | INDICATOR | |
|I_OH_LEDEVICES_EXT_SLAT3| Slats extended 3 | INDICATOR | |
|I_OH_LEDEVICES_EXT_SLAT4| Slats extended 4 | INDICATOR | |
|I_OH_LEDEVICES_EXT_SLAT5| Slats extended 5 | INDICATOR | |
|I_OH_LEDEVICES_EXT_SLAT6| Slats extended 6 | INDICATOR | |
|I_OH_LEDEVICES_EXT_SLAT7| Slats extended 7 | INDICATOR | |
|I_OH_LEDEVICES_EXT_SLAT8| Slats extended 8 | INDICATOR | |
|I_OH_LEDEVICES_FULLEXT_SLAT1| Slats fullExtended 1 | INDICATOR | |
|I_OH_LEDEVICES_FULLEXT_SLAT2| Slats fullExtended 2 | INDICATOR | |
|I_OH_LEDEVICES_FULLEXT_SLAT3| Slats fullExtended 3 | INDICATOR | |
|I_OH_LEDEVICES_FULLEXT_SLAT4| Slats fullExtended 4 | INDICATOR | |
|I_OH_LEDEVICES_FULLEXT_SLAT5| Slats fullExtended 5 | INDICATOR | |
|I_OH_LEDEVICES_FULLEXT_SLAT6| Slats fullExtended 6 | INDICATOR | |
|I_OH_LEDEVICES_FULLEXT_SLAT7| Slats fullExtended 7 | INDICATOR | |
|I_OH_LEDEVICES_FULLEXT_SLAT8| Slats fullExtended 8 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_FLAP1| Flaps transit 1 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_FLAP2| Flaps transit 2 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_FLAP3| Flaps transit 3 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_FLAP4| Flaps transit 4 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_SLAT1| Slats transit 1 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_SLAT2| Slats transit 2 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_SLAT3| Slats transit 3 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_SLAT4| Slats transit 4 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_SLAT5| Slats transit 5 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_SLAT6| Slats transit 6 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_SLAT7| Slats transit 7 | INDICATOR | |
|I_OH_LEDEVICES_TRANS_SLAT8| Slats transit 8 | INDICATOR | |
|I_OH_MACH_TRIM| Mach Trim Fail | INDICATOR | |
|I_OH_PACK_L| Pack L | INDICATOR | |
|I_OH_PACK_R| Pack R | INDICATOR | |
|I_OH_PASS_OXY_ON| Pass oxy on | INDICATOR | |
|I_OH_PRES_ALTN| Pressurization altn | INDICATOR | |
|I_OH_PRES_AUTO_FAIL| Pressurization auto fail | INDICATOR | |
|I_OH_PRES_MANUAL| Pressurization manual | INDICATOR | |
|I_OH_PRES_OFFSCHED| Off sched descent | INDICATOR | |
|I_OH_PSEU| PSEU | INDICATOR | |
|I_OH_RAMDOOR_L| Ram door full open L | INDICATOR | |
|I_OH_RAMDOOR_R| Ram door full open R | INDICATOR | |
|I_OH_REVERSER1| Reverser left | INDICATOR | |
|I_OH_REVERSER2| Reverser right | INDICATOR | |
|I_OH_SOURCE_OFF1| Source OFF 1 | INDICATOR | |
|I_OH_SOURCE_OFF2| Source OFF 2 | INDICATOR | |
|I_OH_SPAR_VALVE_CLOSED_L| SPAR Valve Closed L | INDICATOR | |
|I_OH_SPAR_VALVE_CLOSED_R| SPAR Valve Closed R | INDICATOR | |
|I_OH_SPEED_TRIM| Speed Trim Fail | INDICATOR | |
|I_OH_STDBY_POWER_OFF| Standby pwr off | INDICATOR | |
|I_OH_STDBY_RUD_ON| Stdby Rud On | INDICATOR | |
|I_OH_TEMP_PROBE| tempProbe Heat | INDICATOR | |
|I_OH_TR_UNIT| TR UNIT | INDICATOR | |
|I_OH_TRANS_OFF1| Transfer bus OFF 1 | INDICATOR | |
|I_OH_TRANS_OFF2| Transfer bus OFF 2 | INDICATOR | |
|I_OH_VOICE_RECORDER_STATUS| Voice recorder status | INDICATOR | |
|I_OH_WAI_VALVE_L| WAI L Valve Open | INDICATOR | |
|I_OH_WAI_VALVE_R| WAI R Valve Open | INDICATOR | |
|I_OH_WINDOW_HEAT_FL| Window heat FWD L on | INDICATOR | |
|I_OH_WINDOW_HEAT_FR| Window heat FWD R on | INDICATOR | |
|I_OH_WINDOW_HEAT_OVT_FL| Window heat FWD L overheat | INDICATOR | |
|I_OH_WINDOW_HEAT_OVT_FR| Window heat FWD R overheat | INDICATOR | |
|I_OH_WINDOW_HEAT_OVT_SL| Window heat Side L overheat | INDICATOR | |
|I_OH_WINDOW_HEAT_OVT_SR| Window heat Side R overheat | INDICATOR | |
|I_OH_WINDOW_HEAT_SL| Window heat Side L on | INDICATOR | |
|I_OH_WINDOW_HEAT_SR| Window heat Side R on | INDICATOR | |
|I_OH_WINGBODY_OVT_L| Wing-body overheat 1 | INDICATOR | |
|I_OH_WINGBODY_OVT_R| Wing-body overheat 2 | INDICATOR | |
|I_OH_YAW_DAMPER| Yaw damper | INDICATOR | |
|I_OH_ZONE_TEMP_AFT| Zone temp AFT CAB | INDICATOR | |
|I_OH_ZONE_TEMP_CONT| Zone temp CONT CAB | INDICATOR | |
|I_OH_ZONE_TEMP_FWD| Zone temp FWD CAB | INDICATOR | |
|I_RADIO_HF1_AM| HF1 AM modulation | INDICATOR | |
|I_RADIO_HF2_AM| HF2 AM modulation | INDICATOR | |
|I_RMP1_ADF| RMP Capt ADF indicator | INDICATOR | |
|I_RMP1_AM| RMP Capt AM | INDICATOR | |
|I_RMP1_HF1| RMP Capt HF1 indicator | INDICATOR | |
|I_RMP1_HF2| RMP Capt HF2 indicator | INDICATOR | |
|I_RMP1_NAV1| RMP Capt NAV1 indicator | INDICATOR | |
|I_RMP1_NAV2| RMP Capt NAV2 indicator | INDICATOR | |
|I_RMP1_OFFSIDE_TUNING| RMP Capt offside tuning | INDICATOR | |
|I_RMP1_VHF1| RMP Capt VHF1 indicator | INDICATOR | |
|I_RMP1_VHF2| RMP Capt VHF2 indicator | INDICATOR | |
|I_RMP1_VHF3| RMP Capt VHF3 indicator | INDICATOR | |
|I_RMP2_ADF| RMP F/O ADF indicator | INDICATOR | |
|I_RMP2_AM| RMP F/O AM | INDICATOR | |
|I_RMP2_HF1| RMP F/O HF1 indicator | INDICATOR | |
|I_RMP2_HF2| RMP F/O HF2 indicator | INDICATOR | |
|I_RMP2_NAV1| RMP F/O NAV1 indicator | INDICATOR | |
|I_RMP2_NAV2| RMP F/O NAV2 indicator | INDICATOR | |
|I_RMP2_OFFSIDE_TUNING| RMP F/O offside tuning | INDICATOR | |
|I_RMP2_VHF1| RMP F/O VHF1 indicator | INDICATOR | |
|I_RMP2_VHF2| RMP F/O VHF2 indicator | INDICATOR | |
|I_RMP2_VHF3| RMP F/O VHF3 indicator | INDICATOR | |
|I_XPDR_FAIL|  |  | |
|N_ELEC_PANEL_LOWER_CENTER| Electric Panel Lower center | NUMERICAL | |
|N_ELEC_PANEL_LOWER_LEFT| Electric Panel Lower left | NUMERICAL | |
|N_ELEC_PANEL_LOWER_RIGHT| Electric Panel Lower right | NUMERICAL | |
|N_ELEC_PANEL_UPPER_CENTER| Electric Panel Upper center | NUMERICAL | |
|N_ELEC_PANEL_UPPER_LEFT| Electric Panel Upper left | NUMERICAL | |
|N_ELEC_PANEL_UPPER_RIGHT| Electric Panel Upper right | NUMERICAL | |
|N_FREQ_ADF1| Radio freq ADF1 | NUMERICAL | |
|N_FREQ_ADF2| Radio freq ADF2 | NUMERICAL | |
|N_FREQ_COM1| Radio freq COM1 | NUMERICAL | |
|N_FREQ_COM2| Radio freq COM2 | NUMERICAL | |
|N_FREQ_COM3| Radio freq COM3 | NUMERICAL | |
|N_FREQ_HF1| Radio freq HF1 | NUMERICAL | |
|N_FREQ_HF2| Radio freq HF2 | NUMERICAL | |
|N_FREQ_NAV1| Radio freq NAV1 | NUMERICAL | |
|N_FREQ_NAV2| Radio freq NAV2 | NUMERICAL | |
|N_FREQ_STANDBY_ADF1| Radio standby freq ADF1 | NUMERICAL | |
|N_FREQ_STANDBY_ADF2| Radio standby freq ADF2 | NUMERICAL | |
|N_FREQ_STANDBY_COM1| Radio standby freq COM1 | NUMERICAL | |
|N_FREQ_STANDBY_COM2| Radio standby freq COM2 | NUMERICAL | |
|N_FREQ_STANDBY_COM3| Radio standby freq COM3 | NUMERICAL | |
|N_FREQ_STANDBY_HF1| Radio standby freq HF1 | NUMERICAL | |
|N_FREQ_STANDBY_HF2| Radio standby freq HF2 | NUMERICAL | |
|N_FREQ_STANDBY_NAV1| Radio standby freq NAV1 | NUMERICAL | |
|N_FREQ_STANDBY_NAV2| Radio standby freq NAV2 | NUMERICAL | |
|N_FREQ_STANDBY_XPDR2| Radio standby freq XPDR2 | NUMERICAL | |
|N_FREQ_XPDR| Radio freq XPDR | NUMERICAL | |
|N_FREQ_XPDR2| Radio freq XPDR2 | NUMERICAL | |
|N_FUEL_FLOW_1| Fuel Flow left | NUMERICAL | |
|N_FUEL_FLOW_2| Fuel Flow right | NUMERICAL | |
|N_IRS_DISP_LEFT| IRS Display left number | NUMERICAL | |
|N_IRS_DISP_RIGHT| IRS Display right number | NUMERICAL | |
|N_MCP_ALT| MCP ALT VAL output | NUMERICAL | |
|N_MCP_COURSE1| MCP COURSE 1 VAL output | NUMERICAL | |
|N_MCP_COURSE2| MCP COURSE 2 VAL output | NUMERICAL | |
|N_MCP_HEADING| MCP HEADING VAL output | NUMERICAL | |
|N_MCP_SPEED| MCP SPEED VAL output | NUMERICAL | |
|N_MCP_VS| MCP V/S VAL output | NUMERICAL | |
|N_MIP_FLAP_GAUGE_LEFT| Flap numerical | NUMERICAL | |
|N_MIP_FLAP_GAUGE_RIGHT| Flap right numerical | NUMERICAL | |
|N_OH_FLIGHT_ALT| Cruise alt | NUMERICAL | |
|N_OH_LAND_ALT| Land alt | NUMERICAL | |
|N_RADIO_ADF1_MODE| ADF1 mode | NUMERICAL | |
|N_RADIO_ADF2_MODE| ADF2 mode | NUMERICAL | |
|N_RADIO_ALTITUDE| Radio altitude | NUMERICAL | |
|N_RMP1_ACT_MODE| RMP Capt active mode | NUMERICAL | |
|N_RMP1_ACT_VALUE| RMP Capt active value | NUMERICAL | |
|N_RMP1_STDBY_MODE| RMP Capt standby mode | NUMERICAL | |
|N_RMP1_STDBY_VALUE| RMP Capt standby value | NUMERICAL | |
|N_RMP2_ACT_MODE| RMP F/O active mode | NUMERICAL | |
|N_RMP2_ACT_VALUE| RMP F/O active value | NUMERICAL | |
|N_RMP2_STDBY_MODE| RMP F/O standby mode | NUMERICAL | |
|N_RMP2_STDBY_VALUE| RMP F/O standby value | NUMERICAL | |
|N_TRIM_MOTOR_VALUE| Trim motor value | NUMERICAL | |
|R_ADF1_ACTIVE| Radio freq input ADF1 | ANALOG | |
|R_ADF1_STANDBY| Radio standby freq input ADF1 | ANALOG | |
|R_ADF2_ACTIVE| Radio freq input ADF2 | ANALOG | |
|R_ADF2_STANDBY| Radio standby freq input ADF2 | ANALOG | |
|R_COM1_ACTIVE| Radio freq input COM1 | ANALOG | |
|R_COM1_STANDBY| Radio standby freq input COM1 | ANALOG | |
|R_COM2_ACTIVE| Radio freq input COM2 | ANALOG | |
|R_COM2_STANDBY| Radio standby freq input COM2 | ANALOG | |
|R_COM3_ACTIVE| Radio freq input COM3 | ANALOG | |
|R_COM3_STANDBY| Radio standby freq input COM3 | ANALOG | |
|R_HF1_ACTIVE| Radio freq input HF1 | ANALOG | |
|R_HF2_ACTIVE| Radio freq input HF2 | ANALOG | |
|R_NAV1_ACTIVE| Radio freq input NAV1 | ANALOG | |
|R_NAV1_STANDBY| Radio standby freq input NAV1 | ANALOG | |
|R_NAV2_ACTIVE| Radio freq input NAV2 | ANALOG | |
|R_NAV2_STANDBY| Radio standby freq input NAV2 | ANALOG | |
|R_XPDR| Radio freq input XPDR | ANALOG | |
|R_XPDR2| Radio freq input XPDR2 | ANALOG | |
|S_ADF1_TFC| Radio TFR ADF1 | SWITCH | Normal,Pushed|
|S_ADF2_TFC| Radio TFR ADF2 | SWITCH | Normal,Pushed|
|S_AILERON_TRIM| Aileron trim | SWITCH | Center,Left,Right|
|S_ASA_AP1| ASA A/P reset Capt | SWITCH | Off,Pushed|
|S_ASA_AP2| ASA A/P reset F/O | SWITCH | Off,Pushed|
|S_ASA_AT1| ASA A/T reset Capt | SWITCH | Off,Pushed|
|S_ASA_AT2| ASA A/T reset F/O | SWITCH | Off,Pushed|
|S_ASA_FMC1| ASA FMC reset Capt | SWITCH | Off,Pushed|
|S_ASA_FMC2| ASA FMC reset F/O | SWITCH | Off,Pushed|
|S_ASA_TEST_1| ASA Test Capt | SWITCH | Off,1,2|
|S_ASA_TEST_2| ASA Test F/O | SWITCH | Off,1,2|
|S_ASP_ADF_1_REC| ASP ADF 1 vol | SWITCH | Off,Pushed|
|S_ASP_ADF_1_REC_LATCH| ASP ADF 1 vol latch | SWITCH | Off,On|
|S_ASP_ADF_2_REC| ASP ADF 2 vol | SWITCH | Off,Pushed|
|S_ASP_ADF_2_REC_LATCH| ASP ADF 2 vol latch | SWITCH | Off,On|
|S_ASP_ALT| ASP Alternate Selected | SWITCH | Off,On|
|S_ASP_BOOM| ASP Boom Selected | SWITCH | Off,On|
|S_ASP_IC| ASP IC Selected | SWITCH | Off,On|
|S_ASP_MARKER_REC| ASP Marker vol | SWITCH | Off,Pushed|
|S_ASP_MARKER_REC_LATCH| ASP Marker vol latch | SWITCH | Off,On|
|S_ASP_MASK| ASP Mask Selected | SWITCH | Off,On|
|S_ASP_NAV_1_REC| ASP NAV 1 vol | SWITCH | Off,Pushed|
|S_ASP_NAV_1_REC_LATCH| ASP NAV 1 vol latch | SWITCH | Off,On|
|S_ASP_NAV_2_REC| ASP NAV 2 vol | SWITCH | Off,Pushed|
|S_ASP_NAV_2_REC_LATCH| ASP NAV 2 vol latch | SWITCH | Off,On|
|S_ASP_NORM| ASP Normal Selected | SWITCH | Off,On|
|S_ASP_PA_REC| ASP PA vol | SWITCH | Off,Pushed|
|S_ASP_PA_REC_LATCH| ASP PA vol latch | SWITCH | Off,On|
|S_ASP_RT| ASP RT Selected | SWITCH | Off,On|
|S_ASP_SIGNAL_FILTER| ASP filter mode | SWITCH | B,V,R|
|S_ASP_SPKR_REC| ASP Spkr vol | SWITCH | Off,Pushed|
|S_ASP_SPKR_REC_LATCH| ASP Spkr vol latch | SWITCH | Off,On|
|S_ASP_VHF_1_REC| ASP VHF 1 vol | SWITCH | Off,Pushed|
|S_ASP_VHF_1_REC_LATCH| ASP VHF 1 vol latch | SWITCH | Off,On|
|S_ASP_VHF_1_SEND| ASP VHF 1 mic | SWITCH | Off,Pushed|
|S_ASP_VHF_1_SEND_LATCH| ASP VHF 1 mic latch | SWITCH | Off,On|
|S_ASP_VHF_2_REC| ASP VHF 2 vol | SWITCH | Off,Pushed|
|S_ASP_VHF_2_REC_LATCH| ASP VHF 2 vol latch | SWITCH | Off,On|
|S_ASP_VHF_2_SEND| ASP VHF 2 mic | SWITCH | Off,Pushed|
|S_ASP_VHF_2_SEND_LATCH| ASP VHF 2 mic latch | SWITCH | Off,On|
|S_ASP2_ADF_1_REC| ASP FO ADF 1 vol | SWITCH | Off,Pushed|
|S_ASP2_ADF_1_REC_LATCH| ASP FO ADF 1 vol latch | SWITCH | Off,On|
|S_ASP2_ADF_2_REC| ASP FO ADF 2 vol | SWITCH | Off,Pushed|
|S_ASP2_ADF_2_REC_LATCH| ASP FO ADF 2 vol latch | SWITCH | Off,On|
|S_ASP2_ALT| ASP FO Alternate Selected | SWITCH | Off,On|
|S_ASP2_BOOM| ASP FO Boom Selected | SWITCH | Off,On|
|S_ASP2_IC| ASP FO IC Selected | SWITCH | Off,On|
|S_ASP2_MARKER_REC| ASP FO Marker vol | SWITCH | Off,Pushed|
|S_ASP2_MARKER_REC_LATCH| ASP FO Marker vol latch | SWITCH | Off,On|
|S_ASP2_MASK| ASP FO Mask Selected | SWITCH | Off,On|
|S_ASP2_NAV_1_REC| ASP FO NAV 1 vol | SWITCH | Off,Pushed|
|S_ASP2_NAV_1_REC_LATCH| ASP FO NAV 1 vol latch | SWITCH | Off,On|
|S_ASP2_NAV_2_REC| ASP FO NAV 2 vol | SWITCH | Off,Pushed|
|S_ASP2_NAV_2_REC_LATCH| ASP FO NAV 2 vol latch | SWITCH | Off,On|
|S_ASP2_NORM| ASP FO Normal Selected | SWITCH | Off,On|
|S_ASP2_PA_REC| ASP FO PA vol | SWITCH | Off,Pushed|
|S_ASP2_PA_REC_LATCH| ASP FO PA vol latch | SWITCH | Off,On|
|S_ASP2_RT| ASP FO RT Selected | SWITCH | Off,On|
|S_ASP2_SIGNAL_FILTER| ASP2 filter mode | SWITCH | B,V,R|
|S_ASP2_SPKR_REC| ASP FO Spkr vol | SWITCH | Off,Pushed|
|S_ASP2_SPKR_REC_LATCH| ASP FO Spkr vol latch | SWITCH | Off,On|
|S_ASP2_VHF_1_REC| ASP FO VHF 1 vol | SWITCH | Off,Pushed|
|S_ASP2_VHF_1_REC_LATCH| ASP FO VHF 1 vol latch | SWITCH | Off,On|
|S_ASP2_VHF_1_SEND| ASP FO VHF 1 mic | SWITCH | Off,Pushed|
|S_ASP2_VHF_1_SEND_LATCH| ASP FO VHF 1 mic latch | SWITCH | Off,On|
|S_ASP2_VHF_2_REC| ASP FO VHF 2 vol | SWITCH | Off,Pushed|
|S_ASP2_VHF_2_REC_LATCH| ASP FO VHF 2 vol latch | SWITCH | Off,On|
|S_ASP2_VHF_2_SEND| ASP FO VHF 2 mic | SWITCH | Off,Pushed|
|S_ASP2_VHF_2_SEND_LATCH| ASP FO VHF 2 mic latch | SWITCH | Off,On|
|S_ASP3_ADF_1_REC| ASP OBS ADF 1 vol | SWITCH | Off,Pushed|
|S_ASP3_ADF_1_REC_LATCH| ASP OBS ADF 1 vol latch | SWITCH | Off,On|
|S_ASP3_ADF_2_REC| ASP OBS ADF 2 vol | SWITCH | Off,Pushed|
|S_ASP3_ADF_2_REC_LATCH| ASP OBS ADF 2 vol latch | SWITCH | Off,On|
|S_ASP3_ALT| ASP OBS Alternate Selected | SWITCH | Off,On|
|S_ASP3_BOOM| ASP OBS Boom Selected | SWITCH | Off,On|
|S_ASP3_IC| ASP OBS IC Selected | SWITCH | Off,On|
|S_ASP3_MARKER_REC| ASP OBS Marker vol | SWITCH | Off,Pushed|
|S_ASP3_MARKER_REC_LATCH| ASP OBS Marker vol latch | SWITCH | Off,On|
|S_ASP3_MASK| ASP OBS Mask Selected | SWITCH | Off,On|
|S_ASP3_NAV_1_REC| ASP OBS NAV 1 vol | SWITCH | Off,Pushed|
|S_ASP3_NAV_1_REC_LATCH| ASP OBS NAV 1 vol latch | SWITCH | Off,On|
|S_ASP3_NAV_2_REC| ASP OBS NAV 2 vol | SWITCH | Off,Pushed|
|S_ASP3_NAV_2_REC_LATCH| ASP OBS NAV 2 vol latch | SWITCH | Off,On|
|S_ASP3_NORM| ASP OBS Normal Selected | SWITCH | Off,On|
|S_ASP3_PA_REC| ASP OBS PA vol | SWITCH | Off,Pushed|
|S_ASP3_PA_REC_LATCH| ASP OBS PA vol latch | SWITCH | Off,On|
|S_ASP3_RT| ASP OBS RT Selected | SWITCH | Off,On|
|S_ASP3_SIGNAL_FILTER| ASP3 filter mode | SWITCH | B,V,R|
|S_ASP3_SPKR_REC| ASP OBS Spkr vol | SWITCH | Off,Pushed|
|S_ASP3_SPKR_REC_LATCH| ASP OBS Spkr vol latch | SWITCH | Off,On|
|S_ASP3_VHF_1_REC| ASP OBS VHF 1 vol | SWITCH | Off,Pushed|
|S_ASP3_VHF_1_REC_LATCH| ASP OBS VHF 1 vol latch | SWITCH | Off,On|
|S_ASP3_VHF_1_SEND| ASP OBS VHF 1 mic | SWITCH | Off,Pushed|
|S_ASP3_VHF_1_SEND_LATCH| ASP OBS VHF 1 mic latch | SWITCH | Off,On|
|S_ASP3_VHF_2_REC| ASP OBS VHF 2 vol | SWITCH | Off,Pushed|
|S_ASP3_VHF_2_REC_LATCH| ASP OBS VHF 2 vol latch | SWITCH | Off,On|
|S_ASP3_VHF_2_SEND| ASP OBS VHF 2 mic | SWITCH | Off,Pushed|
|S_ASP3_VHF_2_SEND_LATCH| ASP OBS VHF 2 mic latch | SWITCH | Off,On|
|S_CDU1_KEY_0|  |  | |
|S_CDU1_KEY_1|  |  | |
|S_CDU1_KEY_2|  |  | |
|S_CDU1_KEY_3|  |  | |
|S_CDU1_KEY_4|  |  | |
|S_CDU1_KEY_5|  |  | |
|S_CDU1_KEY_6|  |  | |
|S_CDU1_KEY_7|  |  | |
|S_CDU1_KEY_8|  |  | |
|S_CDU1_KEY_9|  |  | |
|S_CDU1_KEY_A|  |  | |
|S_CDU1_KEY_B|  |  | |
|S_CDU1_KEY_C|  |  | |
|S_CDU1_KEY_CLB|  |  | |
|S_CDU1_KEY_CLEAR|  |  | |
|S_CDU1_KEY_CLEARLINE|  |  | |
|S_CDU1_KEY_CRZ|  |  | |
|S_CDU1_KEY_D|  |  | |
|S_CDU1_KEY_DEL|  |  | |
|S_CDU1_KEY_DEP_ARR|  |  | |
|S_CDU1_KEY_DES|  |  | |
|S_CDU1_KEY_DOT|  |  | |
|S_CDU1_KEY_E|  |  | |
|S_CDU1_KEY_EXEC|  |  | |
|S_CDU1_KEY_F|  |  | |
|S_CDU1_KEY_FIX|  |  | |
|S_CDU1_KEY_G|  |  | |
|S_CDU1_KEY_H|  |  | |
|S_CDU1_KEY_HOLD|  |  | |
|S_CDU1_KEY_I|  |  | |
|S_CDU1_KEY_INIT_REF|  |  | |
|S_CDU1_KEY_J|  |  | |
|S_CDU1_KEY_K|  |  | |
|S_CDU1_KEY_L|  |  | |
|S_CDU1_KEY_LEGS|  |  | |
|S_CDU1_KEY_LSK1L|  |  | |
|S_CDU1_KEY_LSK1R|  |  | |
|S_CDU1_KEY_LSK2L|  |  | |
|S_CDU1_KEY_LSK2R|  |  | |
|S_CDU1_KEY_LSK3L|  |  | |
|S_CDU1_KEY_LSK3R|  |  | |
|S_CDU1_KEY_LSK4L|  |  | |
|S_CDU1_KEY_LSK4R|  |  | |
|S_CDU1_KEY_LSK5L|  |  | |
|S_CDU1_KEY_LSK5R|  |  | |
|S_CDU1_KEY_LSK6L|  |  | |
|S_CDU1_KEY_LSK6R|  |  | |
|S_CDU1_KEY_M|  |  | |
|S_CDU1_KEY_MENU|  |  | |
|S_CDU1_KEY_MINUS|  |  | |
|S_CDU1_KEY_N|  |  | |
|S_CDU1_KEY_N1_LIMIT|  |  | |
|S_CDU1_KEY_NEXT_PAGE|  |  | |
|S_CDU1_KEY_O|  |  | |
|S_CDU1_KEY_P|  |  | |
|S_CDU1_KEY_PREV_PAGE|  |  | |
|S_CDU1_KEY_PROG|  |  | |
|S_CDU1_KEY_Q|  |  | |
|S_CDU1_KEY_R|  |  | |
|S_CDU1_KEY_RTE|  |  | |
|S_CDU1_KEY_S|  |  | |
|S_CDU1_KEY_SLASH|  |  | |
|S_CDU1_KEY_SPACE|  |  | |
|S_CDU1_KEY_T|  |  | |
|S_CDU1_KEY_U|  |  | |
|S_CDU1_KEY_V|  |  | |
|S_CDU1_KEY_W|  |  | |
|S_CDU1_KEY_X|  |  | |
|S_CDU1_KEY_Y|  |  | |
|S_CDU1_KEY_Z|  |  | |
|S_CDU2_KEY_0|  |  | |
|S_CDU2_KEY_1|  |  | |
|S_CDU2_KEY_2|  |  | |
|S_CDU2_KEY_3|  |  | |
|S_CDU2_KEY_4|  |  | |
|S_CDU2_KEY_5|  |  | |
|S_CDU2_KEY_6|  |  | |
|S_CDU2_KEY_7|  |  | |
|S_CDU2_KEY_8|  |  | |
|S_CDU2_KEY_9|  |  | |
|S_CDU2_KEY_A|  |  | |
|S_CDU2_KEY_B|  |  | |
|S_CDU2_KEY_C|  |  | |
|S_CDU2_KEY_CLB|  |  | |
|S_CDU2_KEY_CLEAR|  |  | |
|S_CDU2_KEY_CLEARLINE|  |  | |
|S_CDU2_KEY_CRZ|  |  | |
|S_CDU2_KEY_D|  |  | |
|S_CDU2_KEY_DEL|  |  | |
|S_CDU2_KEY_DEP_ARR|  |  | |
|S_CDU2_KEY_DES|  |  | |
|S_CDU2_KEY_DOT|  |  | |
|S_CDU2_KEY_E|  |  | |
|S_CDU2_KEY_EXEC|  |  | |
|S_CDU2_KEY_F|  |  | |
|S_CDU2_KEY_FIX|  |  | |
|S_CDU2_KEY_G|  |  | |
|S_CDU2_KEY_H|  |  | |
|S_CDU2_KEY_HOLD|  |  | |
|S_CDU2_KEY_I|  |  | |
|S_CDU2_KEY_INIT_REF|  |  | |
|S_CDU2_KEY_J|  |  | |
|S_CDU2_KEY_K|  |  | |
|S_CDU2_KEY_L|  |  | |
|S_CDU2_KEY_LEGS|  |  | |
|S_CDU2_KEY_LSK1L|  |  | |
|S_CDU2_KEY_LSK1R|  |  | |
|S_CDU2_KEY_LSK2L|  |  | |
|S_CDU2_KEY_LSK2R|  |  | |
|S_CDU2_KEY_LSK3L|  |  | |
|S_CDU2_KEY_LSK3R|  |  | |
|S_CDU2_KEY_LSK4L|  |  | |
|S_CDU2_KEY_LSK4R|  |  | |
|S_CDU2_KEY_LSK5L|  |  | |
|S_CDU2_KEY_LSK5R|  |  | |
|S_CDU2_KEY_LSK6L|  |  | |
|S_CDU2_KEY_LSK6R|  |  | |
|S_CDU2_KEY_M|  |  | |
|S_CDU2_KEY_MENU|  |  | |
|S_CDU2_KEY_MINUS|  |  | |
|S_CDU2_KEY_N|  |  | |
|S_CDU2_KEY_N1_LIMIT|  |  | |
|S_CDU2_KEY_NEXT_PAGE|  |  | |
|S_CDU2_KEY_O|  |  | |
|S_CDU2_KEY_P|  |  | |
|S_CDU2_KEY_PREV_PAGE|  |  | |
|S_CDU2_KEY_PROG|  |  | |
|S_CDU2_KEY_Q|  |  | |
|S_CDU2_KEY_R|  |  | |
|S_CDU2_KEY_RTE|  |  | |
|S_CDU2_KEY_S|  |  | |
|S_CDU2_KEY_SLASH|  |  | |
|S_CDU2_KEY_SPACE|  |  | |
|S_CDU2_KEY_T|  |  | |
|S_CDU2_KEY_U|  |  | |
|S_CDU2_KEY_V|  |  | |
|S_CDU2_KEY_W|  |  | |
|S_CDU2_KEY_X|  |  | |
|S_CDU2_KEY_Y|  |  | |
|S_CDU2_KEY_Z|  |  | |
|S_COM1_TFC| Radio TFR COM1 | SWITCH | Normal,Pushed|
|S_COM2_TFC| Radio TFR COM2 | SWITCH | Normal,Pushed|
|S_COM3_TFC| Radio TFR COM3 | SWITCH | Normal,Pushed|
|S_CONTROL_LOADING_POWER|  |  | |
|S_DOOR_AUTO_UNLOCK_TEST| Door auto unlock test | SWITCH | Normal,Pushed|
|S_DOOR_LOCK_FAIL_TEST| Door lock fail test | SWITCH | Normal,Pushed|
|S_ELEV_TRIM| Elevator trim CPT 1 | SWITCH | Center,Up,Down|
|S_ELEV_TRIM_FO| Elevator trim F/O 1 | SWITCH | Center,Up,Down|
|S_ELEV_TRIM_FO2| Elevator trim F/O 2 | SWITCH | Center,Up,Down|
|S_ELEV_TRIM2| Elevator trim CPT 2 | SWITCH | Center,Up,Down|
|S_FC_TOEBRAKE_LEFT_CAPT|  |  | |
|S_FC_TOEBRAKE_LEFT_FO|  |  | |
|S_FC_TOEBRAKE_RIGHT_CAPT|  |  | |
|S_FC_TOEBRAKE_RIGHT_FO|  |  | |
|S_FIRE_BELL_CUTOUT| Bell cutout | SWITCH | Off,Pushed|
|S_FIRE_CARGO_ARM_AFT| Cargo fire arm aft | SWITCH | Off,Pushed|
|S_FIRE_CARGO_ARM_AFT_LATCHED| Cargo fire arm aft latch | SWITCH | Off,On|
|S_FIRE_CARGO_ARM_FWD| Cargo fire arm fwd | SWITCH | Off,Pushed|
|S_FIRE_CARGO_ARM_FWD_LATCHED| Cargo fire arm fwd latch | SWITCH | Off,On|
|S_FIRE_CARGO_DET_AFT| Cargo fire aft selector | SWITCH | Norm,A,B|
|S_FIRE_CARGO_DET_FWD| Cargo fire fwd selector | SWITCH | Norm,A,B|
|S_FIRE_CARGO_DISCH| Cargo fire disch | SWITCH | Off,Pushed|
|S_FIRE_CARGO_EXT_AFT_PTT| Cargo fire ext aft PTT | SWITCH | Normal,Pushed|
|S_FIRE_CARGO_EXT_FWD_PTT| Cargo fire ext fwd PTT | SWITCH | Normal,Pushed|
|S_FIRE_CARGO_TEST| Cargo fire test | SWITCH | Off,Pushed|
|S_FIRE_CUTOUT_CP| Fire warning 1 | SWITCH | Off,Pushed|
|S_FIRE_CUTOUT_FO| Fire warning 2 | SWITCH | Off,Pushed|
|S_FIRE_EXT_TEST| Fire Ext test | SWITCH | Off,1,2|
|S_FIRE_FAULT_TEST| Ovht test | SWITCH | Off,Fault/Inop,Ovht/Fire|
|S_FIRE_HANDLE_APU| Fire handle APU | SWITCH | Off,Left,Right|
|S_FIRE_HANDLE1| Fire handle Engine 1 | SWITCH | Off,Left,Right|
|S_FIRE_HANDLE2| Fire handle Engine 2 | SWITCH | Off,Left,Right|
|S_FIRE_OVHT_DET1| Ovht Det left | SWITCH | Normal,A,B|
|S_FIRE_OVHT_DET2| Ovht Det right | SWITCH | Normal,A,B|
|S_FIRE_PULL_APU| Fire handle pull APU | SWITCH | Normal,Pull|
|S_FIRE_PULL1| Fire handle pull Engine 1 | SWITCH | Normal,Pull|
|S_FIRE_PULL2| Fire handle pull Engine 2 | SWITCH | Normal,Pull|
|S_FLIGHT_DEK_DOOR| Flt Deck door | SWITCH | AUTO,UNLKD,DENY|
|S_GPWS_FLAP_INHIBIT| Flap inhibit | SWITCH | Norm,Inhibit|
|S_GPWS_GEAR_INHIBIT| Gear inhibit | SWITCH | Norm,Inhibit|
|S_GPWS_RUNWAY_INHIBIT| Runway inhibit | SWITCH | Norm,Inhibit|
|S_GPWS_SYS_TEST| GPWS Sys test | SWITCH | Off,Pushed|
|S_GPWS_TERRAIN_INHIBIT| Terrain inhibit | SWITCH | Norm,Inhibit|
|S_MC_ACK_CP| Master caution 1 | SWITCH | Off,Pushed|
|S_MC_ACK_FO| Master caution 2 | SWITCH | Off,Pushed|
|S_MCP_ALT_HOLD| MCP Alt hold | SWITCH | Off,Pushed|
|S_MCP_ALT_INT| MCP Alt Int | SWITCH | Off,Pushed|
|S_MCP_AP_DISENGAGE| MCP AP Disengage | SWITCH | Normal,Disengage|
|S_MCP_APP| MCP APP | SWITCH | Off,Pushed|
|S_MCP_AT| MCP AT Arm | SWITCH | Off,Arm|
|S_MCP_BANK_LIMIT| MCP Bank limit | SWITCH | 25,30,10,15,20|
|S_MCP_CMD_A| MCP CMD A | SWITCH | Off,Pushed|
|S_MCP_CMD_B| MCP CMD B | SWITCH | Off,Pushed|
|S_MCP_CO| MCP C/O | SWITCH | Off,Pushed|
|S_MCP_CWS_A| MCP CWS A | SWITCH | Off,Pushed|
|S_MCP_CWS_B| MCP CWS B | SWITCH | Off,Pushed|
|S_MCP_EFIS1_ARPT| EFIS 1 ARPT | SWITCH | Off,Pushed|
|S_MCP_EFIS1_BARO| EFIS 1 baro momentary | SWITCH | Center,Up,Down,Up fast,Down fast|
|S_MCP_EFIS1_BARO_MODE| EFIS 1 Baro mode | SWITCH | Inch,HPa|
|S_MCP_EFIS1_BARO_STD| EFIS 1 Baro STD | SWITCH | Off,Pushed|
|S_MCP_EFIS1_CTR| EFIS 1 CTR | SWITCH | Off,Pushed|
|S_MCP_EFIS1_DATA| EFIS 1 DATA | SWITCH | Off,Pushed|
|S_MCP_EFIS1_FPV| EFIS 1 FPV | SWITCH | Off,Pushed|
|S_MCP_EFIS1_MINIMUMS| EFIS 1 minimums momentary | SWITCH | Center,Up,Down,Up fast,Down fast|
|S_MCP_EFIS1_MINIMUMS_MODE| EFIS 1 Minimums mode | SWITCH | Radio,Baro|
|S_MCP_EFIS1_MINIMUMS_RESET| EFIS 1 MINS Reset | SWITCH | Off,Pushed|
|S_MCP_EFIS1_MODE| EFIS 1 Mode | SWITCH | APP,VOR,MAP,PLN|
|S_MCP_EFIS1_MTRS| EFIS 1 MTRS | SWITCH | Off,Pushed|
|S_MCP_EFIS1_POS| EFIS 1 POS | SWITCH | Off,Pushed|
|S_MCP_EFIS1_RANGE| EFIS 1 Range | SWITCH | 5,10,20,40,80,160,320,640|
|S_MCP_EFIS1_SEL1| EFIS 1 Selector 1 | SWITCH | OFF,VOR 1,ADF 1|
|S_MCP_EFIS1_SEL2| EFIS 1 Selector 2 | SWITCH | OFF,VOR 2,ADF 2|
|S_MCP_EFIS1_STA| EFIS 1 STA | SWITCH | Off,Pushed|
|S_MCP_EFIS1_TERR| EFIS 1 TERR | SWITCH | Off,Pushed|
|S_MCP_EFIS1_TFC| EFIS 1 TFC | SWITCH | Off,Pushed|
|S_MCP_EFIS1_WPT| EFIS 1 WPT | SWITCH | Off,Pushed|
|S_MCP_EFIS1_WXR| EFIS 1 WXR | SWITCH | Off,Pushed|
|S_MCP_EFIS2_ARPT| EFIS 2 ARPT | SWITCH | Off,Pushed|
|S_MCP_EFIS2_BARO| EFIS 2 baro momentary | SWITCH | Center,Up,Down,Up fast,Down fast|
|S_MCP_EFIS2_BARO_MODE| EFIS 2 Baro mode | SWITCH | Inch,HPa|
|S_MCP_EFIS2_BARO_STD| EFIS 2 Baro STD | SWITCH | Off,Pushed|
|S_MCP_EFIS2_CTR| EFIS 2 CTR | SWITCH | Off,Pushed|
|S_MCP_EFIS2_DATA| EFIS 2 DATA | SWITCH | Off,Pushed|
|S_MCP_EFIS2_FPV| EFIS 2 FPV | SWITCH | Off,Pushed|
|S_MCP_EFIS2_MINIMUMS| EFIS 2 minimums momentary | SWITCH | Center,Up,Down,Up fast,Down fast|
|S_MCP_EFIS2_MINIMUMS_MODE| EFIS 2 Minimums mode | SWITCH | Radio,Baro|
|S_MCP_EFIS2_MINIMUMS_RESET| EFIS 2 MINS Reset | SWITCH | Off,Pushed|
|S_MCP_EFIS2_MODE| EFIS 2 Mode | SWITCH | APP,VOR,MAP,PLN|
|S_MCP_EFIS2_MTRS| EFIS 2 MTRS | SWITCH | Off,Pushed|
|S_MCP_EFIS2_POS| EFIS 2 POS | SWITCH | Off,Pushed|
|S_MCP_EFIS2_RANGE| EFIS 2 Range | SWITCH | 5,10,20,40,80,160,320,640|
|S_MCP_EFIS2_SEL1| EFIS 2 Selector 1 | SWITCH | OFF,VOR 1,ADF 1|
|S_MCP_EFIS2_SEL2| EFIS 2 Selector 2 | SWITCH | OFF,VOR 2,ADF 2|
|S_MCP_EFIS2_STA| EFIS 2 STA | SWITCH | Off,Pushed|
|S_MCP_EFIS2_TERR| EFIS 2 TERR | SWITCH | Off,Pushed|
|S_MCP_EFIS2_TFC| EFIS 2 TFC | SWITCH | Off,Pushed|
|S_MCP_EFIS2_WPT| EFIS 2 WPT | SWITCH | Off,Pushed|
|S_MCP_EFIS2_WXR| EFIS 2 WXR | SWITCH | Off,Pushed|
|S_MCP_FD1| MCP Captain F/D | SWITCH | Off,On|
|S_MCP_FD2| MCP F/O F/D | SWITCH | Off,On|
|S_MCP_HDG_SEL| MCP Heading sel | SWITCH | Off,Pushed|
|S_MCP_HEADING|  |  | |
|S_MCP_LEVEL_CHANGE| MCP Level change | SWITCH | Off,Pushed|
|S_MCP_LNAV| MCP LNAV | SWITCH | Off,Pushed|
|S_MCP_N1| MCP N1 | SWITCH | Off,Pushed|
|S_MCP_SPEED| MCP Speed hold | SWITCH | Off,Pushed|
|S_MCP_SPEED_INT| MCP Speed Int | SWITCH | Off,Pushed|
|S_MCP_VNAV| MCP VNAV | SWITCH | Off,Pushed|
|S_MCP_VORLOC| MCP VOR/LOC | SWITCH | Off,Pushed|
|S_MCP_VS| MCP V/S | SWITCH | Off,Pushed|
|S_MFD_ENG| MFD ENG | SWITCH | Normal,Pushed|
|S_MFD_SYS| MFD SYS | SWITCH | Normal,Pushed|
|S_MIP_AUTOBRAKE| Autobrake | SWITCH | Off,RTO,1,2,3,Max|
|S_MIP_CHRONO_CAPT_ALTERNATE| Chrono capt alternate control | SWITCH | Run,Hold,Reset|
|S_MIP_CHRONO_CAPT_CHR| Chrono capt CHR | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_CAPT_DATE_TIME| Chrono capt Date/Time | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_CAPT_ET| Chrono capt ET | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_CAPT_MINUS| Chrono capt - | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_CAPT_PLUS| Chrono capt + | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_CAPT_RESET| Chrono capt RESET | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_CAPT_SET| Chrono capt SET | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_FO_ALTERNATE| Chrono f/o alternate control | SWITCH | Run,Hold,Reset|
|S_MIP_CHRONO_FO_CHR| Chrono f/o CHR | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_FO_DATE_TIME| Chrono f/o Date/Time | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_FO_ET| Chrono f/o ET | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_FO_MINUS| Chrono f/o - | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_FO_PLUS| Chrono f/o + | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_FO_RESET| Chrono f/o RESET | SWITCH | Normal,Pushed|
|S_MIP_CHRONO_FO_SET| Chrono f/o SET | SWITCH | Normal,Pushed|
|S_MIP_CLOCK_CAPT| Clock Captain | SWITCH | Normal,Pushed|
|S_MIP_CLOCK_FO| Clock F/O | SWITCH | Normal,Pushed|
|S_MIP_FUELFLOW| Fuel flow | SWITCH | Rate,Used,Reset|
|S_MIP_GEAR| Gear | SWITCH | Off,Down,Up|
|S_MIP_GEAR_OVERRIDE| Gear handle lock override | SWITCH | Normal,Override|
|S_MIP_GS_PUSH_INHIBIT| Glideslope push to inhibit | SWITCH | Normal,Pushed|
|S_MIP_GS_PUSH_INHIBIT_FO| Glideslope push to inhibit F/O | SWITCH | Normal,Pushed|
|S_MIP_ISFD_APP| ISFD APP | SWITCH | Off,Pushed|
|S_MIP_ISFD_BARO_STD| ISFD baro STD | SWITCH | Off,Pushed|
|S_MIP_ISFD_HP_INCH| ISFD HP/IN | SWITCH | Off,Pushed|
|S_MIP_ISFD_MINUS| ISFD - | SWITCH | Off,Pushed|
|S_MIP_ISFD_PLUS| ISFD + | SWITCH | Off,Pushed|
|S_MIP_ISFD_RST| ISFD RST | SWITCH | Off,Pushed|
|S_MIP_LIGHTTEST| Light Test | SWITCH | Bright,Dim,Test|
|S_MIP_LOWER_DU_CAPT| Lower DU Capt | SWITCH | Norm,ND,Eng Pri|
|S_MIP_LOWER_DU_FO| Lower DU FO | SWITCH | Norm,ND,Eng Pri|
|S_MIP_MAIN_DU_CAPT| Main Panel DUs Capt | SWITCH | Norm,Outbd PFD,Eng Pri,PFD,MFD|
|S_MIP_MAIN_DU_FO| Main Panel DUs FO | SWITCH | Norm,Outbd PFD,Eng Pri,PFD,MFD|
|S_MIP_N1_SET| N1 SET | SWITCH | AUTO,1,2,Both|
|S_MIP_N1_SET_VALUE| N1 SET Rotary momentary | SWITCH | Center,Up,Down,Up fast,Down fast|
|S_MIP_NOSEWHEEL_STEERING| Nose wheel steering | SWITCH | Normal,Alternate|
|S_MIP_PARKING_BRAKE| Parking brake | SWITCH | Off,On|
|S_MIP_RMI_CAPT_NAV1| Standby RMI NAV1 mode | SWITCH | VOR,ADF|
|S_MIP_RMI_CAPT_NAV2| Standby RMI NAV2 mode | SWITCH | VOR,ADF|
|S_MIP_RMI_FO_NAV1| Standby RMI NAV1 mode F/O | SWITCH | VOR,ADF|
|S_MIP_RMI_FO_NAV2| Standby RMI NAV2 mode F/O | SWITCH | VOR,ADF|
|S_MIP_SPD_REF_VALUE| SPD REF Rotary momentary | SWITCH | Center,Up,Down,Up fast,Down fast|
|S_MIP_SPDREF| SPD REF | SWITCH | AUTO,V1,VR,WT,VREF,BUG,SET|
|S_MIP_STANDBY_ATTITUDE_MODE| Standby Attitude Mode | SWITCH | APP,OFF,BCRS|
|S_NAV1_TFC| Radio TFR NAV1 | SWITCH | Normal,Pushed|
|S_NAV2_TFC| Radio TFR NAV2 | SWITCH | Normal,Pushed|
|S_OH_AIR_TEMP_SELECTOR| Air Temp Selector | SWITCH | CONT CAB,DUCT FWD,DUCT AFT,CAB FWD,CAB AFT,R,L|
|S_OH_ALT_FLAP_CTRL| Alternate flaps ctrl | SWITCH | Off,Up,Down|
|S_OH_ALT_FLAPS| Alternate flaps | SWITCH | Off,Arm|
|S_OH_ALT_HORN_CUTOUT| Alt horn cutout | SWITCH | Off,Pushed|
|S_OH_APU| APU switch | SWITCH | Off,On,Start|
|S_OH_ATTEND| Attend | SWITCH | Off,Pushed|
|S_OH_BATTERY| Battery switch | SWITCH | Off,On|
|S_OH_BLEED_APU| Bleed APU | SWITCH | Off,On|
|S_OH_BLEED_L| Bleed 1 | SWITCH | Off,On|
|S_OH_BLEED_OVT_TEST| OVHT test | SWITCH | Off,On|
|S_OH_BLEED_R| Bleed 2 | SWITCH | Off,On|
|S_OH_BUS_TRANSFER| Bus transfer switch | SWITCH | Off,Auto|
|S_OH_CROSSFEED| Crossfeed | SWITCH | Off,On|
|S_OH_DISCONNECT1| Disconnect 1 | SWITCH | Normal,Off|
|S_OH_DISCONNECT2| Disconnect 2 | SWITCH | Normal,Off|
|S_OH_DISP_PAN| Display Control Panel | SWITCH | Normal,Both on 1,Both on 2|
|S_OH_DISPLAY_SOURCE| Display source | SWITCH | Auto,All on 1,All on 2|
|S_OH_EEC1| EEC left | SWITCH | Off,Pushed|
|S_OH_EEC1_LATCH| EEC left latch | SWITCH | Off,On|
|S_OH_EEC2| EEC right | SWITCH | Off,Pushed|
|S_OH_EEC2_LATCH| EEC right latch | SWITCH | Off,On|
|S_OH_ELEC_AC| Elec Pnl AC | SWITCH | STBY PWR,GRD PWR,GEN1,APU GEN,GEN2,INV,TEST|
|S_OH_ELEC_DC| Elec Pnl DC | SWITCH | STBY PWR,BAT BUS,BAT,AUX BAT,TR1,TR2,TR3,TEST|
|S_OH_ELEC_HYD_PUMP_1| Hyd ELEC1 | SWITCH | Off,On|
|S_OH_ELEC_HYD_PUMP_2| Hyd ELEC2 | SWITCH | Off,On|
|S_OH_ELEC_MAINT| Elec maint | SWITCH | Off,Pushed|
|S_OH_ELT| ELT | SWITCH | Armed,On|
|S_OH_EMERG_EXIT_LIGHTS| Emer Exit Lights | SWITCH | Off,Armed,On|
|S_OH_ENG_HYD_PUMP_L| Hyd ENG1 | SWITCH | Off,On|
|S_OH_ENG_HYD_PUMP_R| Hyd ENG2 | SWITCH | Off,On|
|S_OH_ENG_START_L| Start 1 | SWITCH | Off,GRD,CONT,FLT|
|S_OH_ENG_START_R| Start 2 | SWITCH | Off,GRD,CONT,FLT|
|S_OH_ENGINE_AI1| Eng Anti-Ice 1 | SWITCH | Off,On|
|S_OH_ENGINE_AI2| Eng Anti-Ice 2 | SWITCH | Off,On|
|S_OH_EQUIP_COOLING_EXHAUST| Equip cooling exhaust | SWITCH | Normal,Alternate|
|S_OH_EQUIP_COOLING_SUPPLY| Equip cooling supply | SWITCH | Normal,Alternate|
|S_OH_FLIGHT_REC| Flight recorder | SWITCH | Normal,Test|
|S_OH_FLT_CTRL_A| Flt Ctrl A | SWITCH | Off,Stby Rud,A On|
|S_OH_FLT_CTRL_B| Flt Ctrl B | SWITCH | Off,Stby Rud,B On|
|S_OH_FMC| FMC | SWITCH | Normal,Both on L,Both on R|
|S_OH_FUEL_PUMP_CL| Fuel Center Left | SWITCH | Off,On|
|S_OH_FUEL_PUMP_CR| Fuel Center Right | SWITCH | Off,On|
|S_OH_FUEL_PUMP_LA| Fuel Left Aft | SWITCH | Off,On|
|S_OH_FUEL_PUMP_LF| Fuel Left Fwd | SWITCH | Off,On|
|S_OH_FUEL_PUMP_RA| Fuel Right Aft | SWITCH | Off,On|
|S_OH_FUEL_PUMP_RF| Fuel Right Fwd | SWITCH | Off,On|
|S_OH_GALLEY| Galley | SWITCH | Off,On|
|S_OH_GROUND_CALL| Ground call | SWITCH | Off,On|
|S_OH_GROUND_POWER| Ground Power | SWITCH | Off,Center,On|
|S_OH_IGNITION_SELECT| Ignition select | SWITCH | Both,Left,Right|
|S_OH_IRS_DISP_SEL| IRS Disp Sel | SWITCH | TK/GS,Test,PPOS,Wind,HDG/STS|
|S_OH_IRS_KEY_0| IRS Keypad 0 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_1| IRS Keypad 1 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_2| IRS Keypad 2 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_3| IRS Keypad 3 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_4| IRS Keypad 4 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_5| IRS Keypad 5 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_6| IRS Keypad 6 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_7| IRS Keypad 7 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_8| IRS Keypad 8 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_9| IRS Keypad 9 | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_CLR| IRS Keypad CLR | SWITCH | Off,Pushed|
|S_OH_IRS_KEY_ENT| IRS Keypad ENT | SWITCH | Off,Pushed|
|S_OH_IRS_SEL| IRS | SWITCH | Normal,Both on L,Both on R|
|S_OH_IRS_SEL_L| IRS left | SWITCH | Nav,Off,Align,Att|
|S_OH_IRS_SEL_R| IRS right | SWITCH | Nav,Off,Align,Att|
|S_OH_IRS_SYS_DISP| IRS SYS DSPL | SWITCH | Left,Right|
|S_OH_LEDEVICES_TEST| LE Devices test | SWITCH | Off,Pushed|
|S_OH_LIGHT_ANTI_COLLISION| Lights Anti collision | SWITCH | Off,On|
|S_OH_LIGHT_DOME| Dome light | SWITCH | Dim,Off,Bright|
|S_OH_LIGHT_LOGO| Lights Logo | SWITCH | Off,On|
|S_OH_LIGHT_MAIN_FIXED1| Light Main Fixed L | SWITCH | Off,On|
|S_OH_LIGHT_MAIN_FIXED2| Light Main Fixed R | SWITCH | Off,On|
|S_OH_LIGHT_MAIN_RET1| Light Main Retract L | SWITCH | Off,On|
|S_OH_LIGHT_MAIN_RET2| Light Main Retract R | SWITCH | Off,On|
|S_OH_LIGHT_POSITION| Lights Position | SWITCH | Off,On|
|S_OH_LIGHT_RWY1| Lights Runway turnoff L | SWITCH | Off,On|
|S_OH_LIGHT_RWY2| Lights Runway turnoff R | SWITCH | Off,On|
|S_OH_LIGHT_STROBE| Lights Strobe | SWITCH | Off,On|
|S_OH_LIGHT_STROBE_STEADY| Lights Strobe && Steady | SWITCH | Strobe && Steady,Off,Steady|
|S_OH_LIGHT_TAXI| Lights Taxi | SWITCH | Off,On|
|S_OH_LIGHT_WHEEL_WELL| Lights Wheel well | SWITCH | Off,On|
|S_OH_LIGHT_WING| Lights Wing | SWITCH | Off,On|
|S_OH_MACH_WARNING_TEST_1| Mach Airspeed warning test no1 | SWITCH | Off,Pushed|
|S_OH_MACH_WARNING_TEST_2| Mach Airspeed warning test no2 | SWITCH | Off,Pushed|
|S_OH_NO_SMOKING| No Smoking | SWITCH | Off,Auto,On|
|S_OH_OUTFLOW_VALVE| Outflow valve | SWITCH | Off,Open,Close|
|S_OH_PACK_L| Pack 1 | SWITCH | Off,Auto,High|
|S_OH_PACK_R| Pack 2 | SWITCH | Off,Auto,High|
|S_OH_PASS_OXY| Pass oxygen | SWITCH | Normal,On|
|S_OH_PNEUMATIC_ISOLATION| Pneumatic Isolation switch | SWITCH | Auto,Close,Open|
|S_OH_PRESS_MODE| Pressurization | SWITCH | Auto,Altn,Man|
|S_OH_PROBE_HEAT_A| Probe heat A | SWITCH | Off,On|
|S_OH_PROBE_HEAT_B| Probe heat B | SWITCH | Off,On|
|S_OH_RECIRC_L| Recirc Fan L | SWITCH | Off,Auto|
|S_OH_RECIRC_R| Recirc Fan R | SWITCH | Off,Auto|
|S_OH_SEATBELT| Seatbelt | SWITCH | Off,Auto,On|
|S_OH_SOURCE_APU1| APU GEN 1 | SWITCH | Center,Off,On|
|S_OH_SOURCE_APU2| APU GEN 2 | SWITCH | Center,Off,On|
|S_OH_SOURCE_GEN1| GEN 1 | SWITCH | Center,Off,On|
|S_OH_SOURCE_GEN2| GEN 2 | SWITCH | Center,Off,On|
|S_OH_SPOILER_A| Spoiler A | SWITCH | Off,On|
|S_OH_SPOILER_B| Spoiler B | SWITCH | Off,On|
|S_OH_STALL_TEST_1| Stall test 1 | SWITCH | Off,Pushed|
|S_OH_STALL_TEST_2| Stall test 2 | SWITCH | Off,Pushed|
|S_OH_STANDBY_POWER| Standby power switch | SWITCH | Auto,Off,Bat|
|S_OH_TAT_TEST| TAT test | SWITCH | Off,Pushed|
|S_OH_TRIMAIR| Trim air | SWITCH | Off,On|
|S_OH_TRIP_RESET| Trip reset | SWITCH | Off,On|
|S_OH_VHF_NAV| VHF NAV | SWITCH | Normal,Both on 1,Both on 2|
|S_OH_VOICE_RECORDER_TEST| Voice recorder test | SWITCH | Off,Pushed|
|S_OH_WAI| Wing Anti-Ice | SWITCH | Off,On|
|S_OH_WINDOW_HEAT_FL| Window heat FWD L | SWITCH | Off,On|
|S_OH_WINDOW_HEAT_FR| Window heat FWD R | SWITCH | Off,On|
|S_OH_WINDOW_HEAT_SL| Window heat Side L | SWITCH | Off,On|
|S_OH_WINDOW_HEAT_SR| Window heat Side R | SWITCH | Off,On|
|S_OH_WINDOW_HEAT_TEST| Window heat test | SWITCH | Center,OVHT,PWR TEST|
|S_OH_WIPER_L| Wiper left | SWITCH | Park,Int,Low,High|
|S_OH_WIPER_R| Wiper right | SWITCH | Park,Int,Low,High|
|S_OH_YAW_DAMPER| Yaw damper | SWITCH | Off,On|
|S_PEDESTAL_STAB_TRIM_OVERRIDE| Stab trim override | SWITCH | Normal,Override|
|S_RADIO_ADF1_MODE| ADF1 mode switch | SWITCH | Off,Antenna,ADF|
|S_RADIO_ADF2_MODE| ADF2 mode switch | SWITCH | Off,Antenna,ADF|
|S_RADIO_XPDR_SELECTOR_1| Radio XPDR selector 1 | SWITCH | Off,0,1,2,3,4,5,6,7|
|S_RADIO_XPDR_SELECTOR_2| Radio XPDR selector 2 | SWITCH | Off,0,1,2,3,4,5,6,7|
|S_RADIO_XPDR_SELECTOR_3| Radio XPDR selector 3 | SWITCH | Off,0,1,2,3,4,5,6,7|
|S_RADIO_XPDR_SELECTOR_4| Radio XPDR selector 4 | SWITCH | Off,0,1,2,3,4,5,6,7|
|S_RECALL_CP| Recall 1 | SWITCH | Off,Pushed|
|S_RECALL_FO| Recall 2 | SWITCH | Off,Pushed|
|S_RMP1_ADF| RMP Capt ADF | SWITCH | Normal,Pushed|
|S_RMP1_AM| RMP Capt AM | SWITCH | Normal,Pushed|
|S_RMP1_HF1| RMP Capt HF1 | SWITCH | Normal,Pushed|
|S_RMP1_HF2| RMP Capt HF2 | SWITCH | Normal,Pushed|
|S_RMP1_NAV_1| RMP Capt NAV1 | SWITCH | Normal,Pushed|
|S_RMP1_NAV_2| RMP Capt NAV2 | SWITCH | Normal,Pushed|
|S_RMP1_PANEL_OFF| RMP Capt panel off | SWITCH | Normal,Pushed|
|S_RMP1_VHF1| RMP Capt VHF1 | SWITCH | Normal,Pushed|
|S_RMP1_VHF2| RMP Capt VHF2 | SWITCH | Normal,Pushed|
|S_RMP1_VHF3| RMP Capt VHF3 | SWITCH | Normal,Pushed|
|S_RMP1_XFER| RMP Capt transfer | SWITCH | Normal,Pushed|
|S_RMP2_ADF| RMP F/O ADF | SWITCH | Normal,Pushed|
|S_RMP2_AM| RMP F/O AM | SWITCH | Normal,Pushed|
|S_RMP2_HF1| RMP F/O HF1 | SWITCH | Normal,Pushed|
|S_RMP2_HF2| RMP F/O HF2 | SWITCH | Normal,Pushed|
|S_RMP2_NAV_1| RMP F/O NAV1 | SWITCH | Normal,Pushed|
|S_RMP2_NAV_2| RMP F/O NAV2 | SWITCH | Normal,Pushed|
|S_RMP2_PANEL_OFF| RMP F/O panel off | SWITCH | Normal,Pushed|
|S_RMP2_VHF1| RMP F/O VHF1 | SWITCH | Normal,Pushed|
|S_RMP2_VHF2| RMP F/O VHF2 | SWITCH | Normal,Pushed|
|S_RMP2_VHF3| RMP F/O VHF3 | SWITCH | Normal,Pushed|
|S_RMP2_XFER| RMP F/O transfer | SWITCH | Normal,Pushed|
|S_RUDDER_TRIM| Rudder trim | SWITCH | Center,Left,Right|
|S_TCAS_HOR_RANGE| TCAS horizontal range | SWITCH | Max,5,10,20|
|S_TCAS_VERT_RANGE| TCAS vertical range | SWITCH | Normal,Above,Below|
|S_THROTTLE_AT_DISENGAGE| AT Disengage | SWITCH | Off,Pushed|
|S_THROTTLE_AT_DISENGAGE_2| AT Disengage 2nd switch | SWITCH | Off,Pushed|
|S_THROTTLE_FLAP| Flap | SWITCH | Up,1,2,5,10,15,25,30,40|
|S_THROTTLE_FUEL_CUTOFF1| Fuel cutoff left | SWITCH | Idle,Cutoff|
|S_THROTTLE_FUEL_CUTOFF2| Fuel cutoff right | SWITCH | Idle,Cutoff|
|S_THROTTLE_GEAR_WARNING_CUTOUT| Gear horn cutout | SWITCH | Off,Pushed|
|S_THROTTLE_STAB_TRIM_AP| Stab trim main auto pilot | SWITCH | Normal,Cutout|
|S_THROTTLE_STAB_TRIM_ELEC| Stab trim main elec | SWITCH | Normal,Cutout|
|S_THROTTLE_TOGA| TOGA | SWITCH | Off,Pushed|
|S_THROTTLE_TOGA_2| TOGA 2nd switch | SWITCH | Off,Pushed|
|S_WR_MODE| Weather Radar Mode | SWITCH | WX+T,WX,WXR(VAR),MAP,TEST|
|S_XPDR_IDENT| XPDR Ident | SWITCH | Normal,Pushed|
|S_XPDR_MODE| TCAS | SWITCH | Stdby,Alt rptg off,XPDR,TA,TA/RA,Test|
|S_XPDR_OPERATION| XPDR operation | SWITCH | Auto,Standby,On|
|S_XPDR_TEST| TCAS TEST | SWITCH | Normal,Pushed|
|S_YOKE_AP_DISCONNECT_CAPT| AP Disconnect Yoke Capt | SWITCH | Normal,Pushed|
|S_YOKE_AP_DISCONNECT_FO| AP Disconnect Yoke F/O | SWITCH | Normal,Pushed|
|V_MCP_ALT| MCP ALT VAL | ANALOG | |
|V_MCP_COURSE1| MCP COURSE 1 VAL | ANALOG | |
|V_MCP_COURSE2| MCP COURSE 2 VAL | ANALOG | |
|V_MCP_HEADING| MCP HEADING VAL | ANALOG | |
|V_MCP_SPEED| MCP SPEED VAL | ANALOG | |
|V_MCP_VS| MCP V/S VAL | ANALOG | |
|V_OH_AFTCAB| AFT CAB selector | ANALOG | |
|V_OH_CONTCAB| CONT CAB selector | ANALOG | |
|V_OH_FLTALT| Flight alt in | ANALOG | |
|V_OH_FWDCAB| FWD CAB selector | ANALOG | |
|V_OH_LANDALT| Land alt in | ANALOG | |

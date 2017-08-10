---
layout: noHeaderDefault
---

[back](./)

# ProSim Data Elements

The following table is a list of the ProSim data elements at the simulator *sends* to a TCP client

This is table is extracted from the ProSim AR XML interface. This is available on port 8080 of the ProSim Systems server. For example

    http://192.168.2.2:8080/xml?query=ids

| id | Name | Description | Type | Options | Data Type |
|----|------|:------------|:-----|:--------|------|
| 0|A_ASP_ADF_1_VOLUME| ASP ADF 1 vol volume | ANALOG | |char|
| 1|A_ASP_ADF_2_VOLUME| ASP ADF 2 vol volume | ANALOG | |char|
| 2|A_ASP_MARKER_VOLUME| ASP Marker vol volume | ANALOG | |char|
| 3|A_ASP_NAV_1_VOLUME| ASP NAV 1 vol volume | ANALOG | |char|
| 4|A_ASP_NAV_2_VOLUME| ASP NAV 2 vol volume | ANALOG | |char|
| 5|A_ASP_PA_VOLUME| ASP PA vol volume | ANALOG | |char|
| 6|A_ASP_SPKR_VOLUME| ASP Spkr vol volume | ANALOG | |char|
| 7|A_ASP_VHF_1_VOLUME| ASP VHF 1 vol volume | ANALOG | |char|
| 8|A_ASP_VHF_2_VOLUME| ASP VHF 2 vol volume | ANALOG | |char|
| 9|A_ASP2_ADF_1_VOLUME| ASP FO ADF 1 vol volume | ANALOG | |char|
| 10|A_ASP2_ADF_2_VOLUME| ASP FO ADF 2 vol volume | ANALOG | |char|
| 11|A_ASP2_MARKER_VOLUME| ASP FO Marker vol volume | ANALOG | |char|
| 12|A_ASP2_NAV_1_VOLUME| ASP FO NAV 1 vol volume | ANALOG | |char|
| 13|A_ASP2_NAV_2_VOLUME| ASP FO NAV 2 vol volume | ANALOG | |char|
| 14|A_ASP2_PA_VOLUME| ASP FO PA vol volume | ANALOG | |char|
| 15|A_ASP2_SPKR_VOLUME| ASP FO Spkr vol volume | ANALOG | |char|
| 16|A_ASP2_VHF_1_VOLUME| ASP FO VHF 1 vol volume | ANALOG | |char|
| 17|A_ASP2_VHF_2_VOLUME| ASP FO VHF 2 vol volume | ANALOG | |char|
| 18|A_ASP3_ADF_1_VOLUME| ASP OBS ADF 1 vol volume | ANALOG | |char|
| 19|A_ASP3_ADF_2_VOLUME| ASP OBS ADF 2 vol volume | ANALOG | |char|
| 20|A_ASP3_MARKER_VOLUME| ASP OBS Marker vol volume | ANALOG | |char|
| 21|A_ASP3_NAV_1_VOLUME| ASP OBS NAV 1 vol volume | ANALOG | |char|
| 22|A_ASP3_NAV_2_VOLUME| ASP OBS NAV 2 vol volume | ANALOG | |char|
| 23|A_ASP3_PA_VOLUME| ASP OBS PA vol volume | ANALOG | |char|
| 24|A_ASP3_SPKR_VOLUME| ASP OBS Spkr vol volume | ANALOG | |char|
| 25|A_ASP3_VHF_1_VOLUME| ASP OBS VHF 1 vol volume | ANALOG | |char|
| 26|A_ASP3_VHF_2_VOLUME| ASP OBS VHF 2 vol volume | ANALOG | |char|
| 27|A_CDU1_BRIGHTNESS| CDU 1 brightness | ANALOG | |char|
| 28|A_CDU2_BRIGHTNESS| CDU 2 brightness | ANALOG | |char|
| 29|A_FC_AILERON_CAPT|  |  | ||
| 30|A_FC_AILERON_FO|  |  | ||
| 31|A_FC_ELEVATOR_CAPT|  |  | ||
| 32|A_FC_ELEVATOR_FO|  |  | ||
| 33|A_FC_RUDDER_CAPT|  |  | ||
| 34|A_FC_RUDDER_FO|  |  | ||
| 35|A_FC_TILLER_CAPT|  |  | ||
| 36|A_FC_TILLER_FO|  |  | ||
| 37|A_FC_TOEBRAKE_LEFT_CAPT|  |  | ||
| 38|A_FC_TOEBRAKE_LEFT_FO|  |  | ||
| 39|A_FC_TOEBRAKE_RIGHT_CAPT|  |  | ||
| 40|A_FC_TOEBRAKE_RIGHT_FO|  |  | ||
| 41|A_FLAP| Flap input | ANALOG | |char|
| 42|A_MIP_BRIGHTNESS_DU_L| Lower DU Brightness | ANALOG | |char|
| 43|A_MIP_BRIGHTNESS_DU_U| Upper DU Brightness | ANALOG | |char|
| 44|A_MIP_BRIGHTNESS_LI| Left Inboard Brightness | ANALOG | |char|
| 45|A_MIP_BRIGHTNESS_LI_INNER|  |  | ||
| 46|A_MIP_BRIGHTNESS_LO| Left Outboard Brightness | ANALOG | |char|
| 47|A_MIP_BRIGHTNESS_RI| Right Inboard Brightness | ANALOG | |char|
| 48|A_MIP_BRIGHTNESS_RI_INNER|  |  | ||
| 49|A_MIP_BRIGHTNESS_RO| Right Outboard Brightness | ANALOG | |char|
| 50|A_MIP_PANEL| Panel lights | ANALOG | |char|
| 51|A_RMP1_SENSE| RMP Capt sense | ANALOG | |char|
| 52|A_RMP2_SENSE| RMP F/O sense | ANALOG | |char|
| 53|A_SPEEDBRAKE| Speedbrake input | ANALOG | |char|
| 54|A_THROTTLE_LEFT| Throttle input left | ANALOG | |char|
| 55|A_THROTTLE_REVERSE_LEFT| Throttle reverser input left | ANALOG | |char|
| 56|A_THROTTLE_REVERSE_RIGHT| Throttle reverser input right | ANALOG | |char|
| 57|A_THROTTLE_RIGHT| Throttle input right | ANALOG | |char|
| 58|A_WR_GAIN| Weather Radar Gain | ANALOG | |char|
| 59|A_WR_TILT| Weather Radar Tilt | ANALOG | |char|
| 60|B_ABOVE_TRANSITION_ALTITUDE| Above transition altitude | GATE | |bool|
| 61|B_AC_POWER| AC Power | GATE | |bool|
| 62|B_APU_RUNNING| APU running | GATE | |bool|
| 63|B_APU_STARTING| APU starting | GATE | |bool|
| 64|B_APU_STOPPING| APU stopping | GATE | |bool|
| 65|B_ASP_ALT| ASP ASP Alt Out | GATE | |bool|
| 66|B_ASP_BOOM| ASP ASP Boom Out | GATE | |bool|
| 67|B_ASP_IC| ASP ASP IC Out | GATE | |bool|
| 68|B_ASP_MASK| ASP ASP Mask Out | GATE | |bool|
| 69|B_ASP_NORM| ASP ASP Norm Out | GATE | |bool|
| 70|B_ASP_RT| ASP ASP RT Out | GATE | |bool|
| 71|B_ASP2_ALT| ASP FO ASP Alt Out | GATE | |bool|
| 72|B_ASP2_BOOM| ASP FO ASP Boom Out | GATE | |bool|
| 73|B_ASP2_IC| ASP FO ASP IC Out | GATE | |bool|
| 74|B_ASP2_MASK| ASP FO ASP Mask Out | GATE | |bool|
| 75|B_ASP2_NORM| ASP FO ASP Norm Out | GATE | |bool|
| 76|B_ASP2_RT| ASP FO ASP RT Out | GATE | |bool|
| 77|B_ASP3_ALT| ASP OBS ASP Alt Out | GATE | |bool|
| 78|B_ASP3_BOOM| ASP OBS ASP Boom Out | GATE | |bool|
| 79|B_ASP3_IC| ASP OBS ASP IC Out | GATE | |bool|
| 80|B_ASP3_MASK| ASP OBS ASP Mask Out | GATE | |bool|
| 81|B_ASP3_NORM| ASP OBS ASP Norm Out | GATE | |bool|
| 82|B_ASP3_RT| ASP OBS ASP RT Out | GATE | |bool|
| 83|B_ATTEND_ACTIVE| Attend active | GATE | |bool|
| 84|B_BRAKING| Braking | GATE | |bool|
| 85|B_DC_POWER| DC Power | GATE | |bool|
| 86|B_DOME_LIGHT_BRIGHT| Domelight bright | GATE | |bool|
| 87|B_DOME_LIGHT_DIM| Domelight dim | GATE | |bool|
| 88|B_DOME_LIGHT_MASTER| Domelight master | GATE | |bool|
| 89|B_EMERGENY_LIGHTS| Emergency exit lights | GATE | |bool|
| 90|B_FIRE_HANDLE_APU_LOCK| Fire handle unlock APU | GATE | |bool|
| 91|B_FIRE_HANDLE_LEFT_LOCK| Fire handle unlock Engine 1 | GATE | |bool|
| 92|B_FIRE_HANDLE_RIGHT_LOCK| Fire handle unlock Engine 2 | GATE | |bool|
| 93|B_FLAP_0| Flap gate up | GATE | |bool|
| 94|B_FLAP_1| Flap gate 1 | GATE | |bool|
| 95|B_FLAP_10| Flap gate 10 | GATE | |bool|
| 96|B_FLAP_15| Flap gate 15 | GATE | |bool|
| 97|B_FLAP_2| Flap gate 2 | GATE | |bool|
| 98|B_FLAP_25| Flap gate 25 | GATE | |bool|
| 99|B_FLAP_30| Flap gate 30 | GATE | |bool|
| 100|B_FLAP_40| Flap gate 40 | GATE | |bool|
| 101|B_FLAP_5| Flap gate 5 | GATE | |bool|
| 102|B_FLIGHTDECK_DOOR_LOCK|  |  | ||
| 103|B_FMA_PITCH_ALT_ACQ| FMA pitch mode ALT ACQ  | GATE | |bool|
| 104|B_FMA_PITCH_ALT_HOLD| FMA pitch mode ALT HOLD | GATE | |bool|
| 105|B_FMA_PITCH_FLARE| FMA pitch mode FLARE | GATE | |bool|
| 106|B_FMA_PITCH_GP| FMA pitch mode G/P | GATE | |bool|
| 107|B_FMA_PITCH_GS| FMA pitch mode G/S | GATE | |bool|
| 108|B_FMA_PITCH_MCP_SPD| FMA pitch mode MCP_SPD | GATE | |bool|
| 109|B_FMA_PITCH_TOGA| FMA pitch mode TOGA | GATE | |bool|
| 110|B_FMA_PITCH_VNAV_ALT| FMA pitch mode VNAV ALT  | GATE | |bool|
| 111|B_FMA_PITCH_VNAV_PATH| FMA pitch mode VNAV PATH | GATE | |bool|
| 112|B_FMA_PITCH_VNAV_SPD| FMA pitch mode VNAV SPD  | GATE | |bool|
| 113|B_FMA_PITCH_VS| FMA pitch mode V/S | GATE | |bool|
| 114|B_FMA_ROLL_BACKCOURSE| FMA roll mode HDG BACKCOURSE | GATE | |bool|
| 115|B_FMA_ROLL_FAC| FMA roll mode HDG FAC | GATE | |bool|
| 116|B_FMA_ROLL_HDG_SEL| FMA roll mode HDG SEL | GATE | |bool|
| 117|B_FMA_ROLL_LNAV| FMA roll mode HDG LNAV | GATE | |bool|
| 118|B_FMA_ROLL_VOR_LOC| FMA roll mode HDG VOR/LOG | GATE | |bool|
| 119|B_FMA_THRUST_ARM| FMA thrust mode ARM | GATE | |bool|
| 120|B_FMA_THRUST_FMC_SPD| FMA thrust mode FMC_SPD | GATE | |bool|
| 121|B_FMA_THRUST_GA| FMA thrust mode GA | GATE | |bool|
| 122|B_FMA_THRUST_MCP_SPD| FMA thrust mode MCP_SPD | GATE | |bool|
| 123|B_FMA_THRUST_N1| FMA thrust mode N1 | GATE | |bool|
| 124|B_FMA_THRUST_RETARD| FMA thrust mode RETARD | GATE | |bool|
| 125|B_FMA_THRUST_THR_HOLD| FMA thrust mode THR_HLD | GATE | |bool|
| 126|B_GEAR_HANDLE_RELEASE| Gear handle release solenoid | GATE | |bool|
| 127|B_GEAR_WIND| Gear wind | GATE | |bool|
| 128|B_GROUND_GATE| Ground gate | GATE | |bool|
| 129|B_HYDRAULICS_AVAILABLE| Hydraulics available | GATE | |bool|
| 130|B_HYDRAULICS_AVAILABLE_A| Hydraulics A available | GATE | |bool|
| 131|B_HYDRAULICS_AVAILABLE_B| Hydraulics B available | GATE | |bool|
| 132|B_INNER_MARKER| Inner marker | GATE | |bool|
| 133|B_IRS1_ATTITUDE| IRS 1 attitude | GATE | |bool|
| 134|B_IRS1_HEADING| IRS 1 heading | GATE | |bool|
| 135|B_IRS1_POSITION| IRS 1 position | GATE | |bool|
| 136|B_IRS2_ATTITUDE| IRS 2 attitude | GATE | |bool|
| 137|B_IRS2_HEADING| IRS 2 heading | GATE | |bool|
| 138|B_IRS2_POSITION| IRS 2 position | GATE | |bool|
| 139|B_KTS80| 80kts | GATE | |bool|
| 140|B_LIGHT_MASTER_DIM| Master Dim | GATE | |bool|
| 141|B_LIGHT_TEST| Light test | GATE | |bool|
| 142|B_MCP_AT_DISCONNECT_SOLENOID| A/T disconnect solenoid | GATE | |bool|
| 143|B_MCP_AT_HOLD_SOLENOID| A/T hold solenoid | GATE | |bool|
| 144|B_MCP_SPEED_FLASHING_A| MCP Speed flashing A | GATE | |bool|
| 145|B_MCP_SPEED_FLASHING_B| MCP Speed flashing B | GATE | |bool|
| 146|B_MIDDLE_MARKER| Middle marker | GATE | |bool|
| 147|B_MIP_AUTOBRAKE_RESET| Autobrake reset | GATE | |bool|
| 148|B_NO_SMOKING_SIGN| No smoking sign | GATE | |bool|
| 149|B_NOSEWHEEL_ROTATING| Nosewheel rotating | GATE | |bool|
| 150|B_OUTER_MARKER| Outer marker | GATE | |bool|
| 151|B_OVERHEAD_BACKLIGHT_MASTER| Overhead backlight master | GATE | |bool|
| 152|B_PACK_1_OPERATING| Pack L operating | GATE | |bool|
| 153|B_PACK_2_OPERATING| Pack R operating | GATE | |bool|
| 154|B_PANEL_LIGHT_CAPTAIN| Panel lights captain | GATE | |bool|
| 155|B_PANEL_LIGHT_CONTROL_STAND| Panel lights control stand | GATE | |bool|
| 156|B_PANEL_LIGHT_FLOOD| Panel lights flood | GATE | |bool|
| 157|B_PANEL_LIGHT_FO| Panel lights F/O | GATE | |bool|
| 158|B_PARKING_BRAKE_HOLD| Parking brake hold | GATE | |bool|
| 159|B_PARKING_BRAKE_RELEASE| Parking brake release | GATE | |bool|
| 160|B_PED_RUDDER_TRIM_IND_OFF| Rudder trim indicator OFF Flag | GATE | |bool|
| 161|B_PITCH_CMD| Autopilot pitch CMD | GATE | |bool|
| 162|B_PITCH_CWS| Autopilot pitch CWS | GATE | |bool|
| 163|B_PRESSURE_LOSS_HIGH| Pressure loss high | GATE | |bool|
| 164|B_PRESSURE_LOSS_LOW| Pressure loss low | GATE | |bool|
| 165|B_PRESSURISATION_DASHED| Pressurisation display dashed out | GATE | |bool|
| 166|B_PRESSURISATION_DISPLAY_POWER| Pressurisation display power | GATE | |bool|
| 167|B_RECIRCULATION_FAN_1| Recirc Fan L running | GATE | |bool|
| 168|B_RECIRCULATION_FAN_2| Recirc Fan R running | GATE | |bool|
| 169|B_ROLL_CMD| Autopilot roll CMD | GATE | |bool|
| 170|B_ROLL_CWS| Autopilot roll CWS | GATE | |bool|
| 171|B_SEATBELT_SIGN| Seatbelt sign | GATE | |bool|
| 172|B_SPEED_BRAKE| Speedbrake extended | GATE | |bool|
| 173|B_SPEED_BRAKE_AIR| Speedbrake extended in air | GATE | |bool|
| 174|B_SPEED_BRAKE_DEPLOY| Speedbrake autodeploy | GATE | |bool|
| 175|B_SPEED_BRAKE_RESTOW| Speedbrake autorestow | GATE | |bool|
| 176|B_STARTER_PB_SOLENOID_1| Starter 1 pushback solenoid | GATE | |bool|
| 177|B_STARTER_PB_SOLENOID_2| Starter 2 pushback solenoid | GATE | |bool|
| 178|B_STARTER_SOLENOID_1| Starter 1 solenoid | GATE | |bool|
| 179|B_STARTER_SOLENOID_2| Starter 2 solenoid | GATE | |bool|
| 180|B_STICKSHAKER| Stick shaker | GATE | |bool|
| 181|B_STICKSHAKER_FO| Stick shaker F/O | GATE | |bool|
| 182|B_THROTTLE_SERVO_POWER_LEFT| Throttle Servo Power left | GATE | |bool|
| 183|B_THROTTLE_SERVO_POWER_RIGHT| Throttle Servo Power right | GATE | |bool|
| 184|B_TRIM_MOTOR_DOWN| Trim motor down | GATE | |bool|
| 185|B_TRIM_MOTOR_UP| Trim motor up | GATE | |bool|
| 186|B_USER_1| User 1 out | GATE | |bool|
| 187|B_USER_10| User 10 out | GATE | |bool|
| 188|B_USER_11| User 11 out | GATE | |bool|
| 189|B_USER_12| User 12 out | GATE | |bool|
| 190|B_USER_13| User 13 out | GATE | |bool|
| 191|B_USER_14| User 14 out | GATE | |bool|
| 192|B_USER_15| User 15 out | GATE | |bool|
| 193|B_USER_16| User 16 out | GATE | |bool|
| 194|B_USER_17| User 17 out | GATE | |bool|
| 195|B_USER_18| User 18 out | GATE | |bool|
| 196|B_USER_19| User 19 out | GATE | |bool|
| 197|B_USER_2| User 2 out | GATE | |bool|
| 198|B_USER_20| User 20 out | GATE | |bool|
| 199|B_USER_3| User 3 out | GATE | |bool|
| 200|B_USER_4| User 4 out | GATE | |bool|
| 201|B_USER_5| User 5 out | GATE | |bool|
| 202|B_USER_6| User 6 out | GATE | |bool|
| 203|B_USER_7| User 7 out | GATE | |bool|
| 204|B_USER_8| User 8 out | GATE | |bool|
| 205|B_USER_9| User 9 out | GATE | |bool|
| 206|B_V1| V1 | GATE | |bool|
| 207|B_V2| V2 | GATE | |bool|
| 208|B_VR| VRotate | GATE | |bool|
| 209|B_WING_ANTI_ICE_HOLD_ACTUATOR| Wing Anti-Ice hold actuator | GATE | |bool|
| 210|B_WING_ANTI_ICE_OFF_ACTUATOR| Wing Anti-Ice off actuator | GATE | |bool|
| 211|B_WIPER_HIGH_L| Wiper left High | GATE | |bool|
| 212|B_WIPER_HIGH_R| Wiper right High | GATE | |bool|
| 213|B_WIPER_INT_L| Wiper left Int | GATE | |bool|
| 214|B_WIPER_INT_R| Wiper right Int | GATE | |bool|
| 215|B_WIPER_LOW_L| Wiper left Low | GATE | |bool|
| 216|B_WIPER_LOW_R| Wiper right Low | GATE | |bool|
| 217|B_YAW_DAMPER_HOLD_ACTUATOR| Yaw damper hold actuator | GATE | |bool|
| 218|B_YAW_DAMPER_OFF_ACTUATOR| Yaw damper off actuator | GATE | |bool|
| 219|CB_P18_1_B7_GPWS_115|  |  | ||
| 220|CB_P6_3_B7_CROSSFEED_28|  |  | ||
| 221|D_OH_ELEC| Electric Panel | LCD | ||
| 222|D_OH_IRS| IRS Display | LCD | ||
| 223|E_FLIGHTALT| Flight alt in encoder | ENCODER | |signed int|
| 224|E_LANDALT| Land alt in encoder | ENCODER | |signed int|
| 225|E_MCP_ALT| MCP ALT VAL encoder | ENCODER | |signed int|
| 226|E_MCP_COURSE1| MCP COURSE 1 VAL encoder | ENCODER | |signed int|
| 227|E_MCP_COURSE2| MCP COURSE 2 VAL encoder | ENCODER | |signed int|
| 228|E_MCP_EFIS1_BARO| EFIS 1 baro | ENCODER | |signed int|
| 229|E_MCP_EFIS1_MINIMUMS| EFIS 1 minimums | ENCODER | |signed int|
| 230|E_MCP_EFIS2_BARO| EFIS 2 baro | ENCODER | |signed int|
| 231|E_MCP_EFIS2_MINIMUMS| EFIS 2 minimums | ENCODER | |signed int|
| 232|E_MCP_HEADING| MCP HEADING VAL encoder | ENCODER | |signed int|
| 233|E_MCP_SPEED| MCP SPEED VAL encoder | ENCODER | |signed int|
| 234|E_MCP_VS| MCP V/S VAL encoder | ENCODER | |signed int|
| 235|E_MIP_CHRONO_CAPT_ENCODER| Chrono capt encoder | ENCODER | |signed int|
| 236|E_MIP_CHRONO_FO_ENCODER| Chrono f/o encoder | ENCODER | |signed int|
| 237|E_MIP_ISFD_BARO| ISFD baro encoder | ENCODER | |signed int|
| 238|E_MIP_N1_SET| N1 SET Rotary | ENCODER | |signed int|
| 239|E_MIP_SPD_REF| SPD REF Rotary | ENCODER | |signed int|
| 240|E_MIP_STANDBY_ALTIMETER_QNH| Standby altimeter QNH momentary | SWITCH | Center,Up,Down,Up fast,Down fast|char*|
| 241|E_RADIO_ADF1_HUNDREDS| Radio ADF1 hundreds active | ENCODER | |signed int|
| 242|E_RADIO_ADF1_INNER| Radio ADF1 inner shaft | ENCODER | |signed int|
| 243|E_RADIO_ADF1_INNER_ACTIVE| Radio ADF1 inner shaft active | ENCODER | |signed int|
| 244|E_RADIO_ADF1_OUTER| Radio ADF1 outer shaft | ENCODER | |signed int|
| 245|E_RADIO_ADF1_OUTER_ACTIVE| Radio ADF1 outer shaft active | ENCODER | |signed int|
| 246|E_RADIO_ADF2_HUNDREDS| Radio ADF2 hundreds active | ENCODER | |signed int|
| 247|E_RADIO_ADF2_INNER| Radio ADF2 inner shaft | ENCODER | |signed int|
| 248|E_RADIO_ADF2_INNER_ACTIVE| Radio ADF2 inner shaft active | ENCODER | |signed int|
| 249|E_RADIO_ADF2_OUTER| Radio ADF2 outer shaft | ENCODER | |signed int|
| 250|E_RADIO_ADF2_OUTER_ACTIVE| Radio ADF2 outer shaft active | ENCODER | |signed int|
| 251|E_RADIO_COM1_INNER| Radio COM1 inner shaft | ENCODER | |signed int|
| 252|E_RADIO_COM1_OUTER| Radio COM1 outer shaft | ENCODER | |signed int|
| 253|E_RADIO_COM2_INNER| Radio COM2 inner shaft | ENCODER | |signed int|
| 254|E_RADIO_COM2_OUTER| Radio COM2 outer shaft | ENCODER | |signed int|
| 255|E_RADIO_COM3_INNER| Radio COM3 inner shaft | ENCODER | |signed int|
| 256|E_RADIO_COM3_OUTER| Radio COM3 outer shaft | ENCODER | |signed int|
| 257|E_RADIO_NAV1_INNER| Radio NAV1 inner shaft | ENCODER | |signed int|
| 258|E_RADIO_NAV1_OUTER| Radio NAV1 outer shaft | ENCODER | |signed int|
| 259|E_RADIO_NAV2_INNER| Radio NAV2 inner shaft | ENCODER | |signed int|
| 260|E_RADIO_NAV2_OUTER| Radio NAV2 outer shaft | ENCODER | |signed int|
| 261|E_RADIO_RMP1_INNER| RMP Capt inner encoder | ENCODER | |signed int|
| 262|E_RADIO_RMP1_OUTER| RMP Capt outer encoder | ENCODER | |signed int|
| 263|E_RADIO_RMP2_INNER| RMP F/O inner encoder | ENCODER | |signed int|
| 264|E_RADIO_RMP2_OUTER| RMP F/O outer encoder | ENCODER | |signed int|
| 265|E_RADIO_XPDR_INNER_LEFT| Radio XPDR inner shaft left | ENCODER | |signed int|
| 266|E_RADIO_XPDR_INNER_RIGHT| Radio XPDR inner shaft right | ENCODER | |signed int|
| 267|E_RADIO_XPDR_OUTER_LEFT| Radio XPDR outer shaft left | ENCODER | |signed int|
| 268|E_RADIO_XPDR_OUTER_RIGHT| Radio XPDR outer shaft right | ENCODER | |signed int|
| 269|F_GPWS|  |  | ||
| 270|G_MIP_BRAKE_PRESSURE| Brake pressure | GAUGE | |float|
| 271|G_MIP_FLAP| Flap | GAUGE | |float|
| 272|G_MIP_FLAP_RIGHT| Flap right | GAUGE | |float|
| 273|G_MIP_STDBY_ALTIMETER| Standby altimeter | GAUGE | |float|
| 274|G_MIP_STDBY_ATT_BANK| Standby Attitude bank | GAUGE | |float|
| 275|G_MIP_STDBY_ATT_PITCH| Standby Attitude pitch | GAUGE | |float|
| 276|G_MIP_STDBY_BARBERPOLE| Standby barberpole | GAUGE | |float|
| 277|G_MIP_STDBY_GLIDESLOPE| Standby Glideslope | GAUGE | |float|
| 278|G_MIP_STDBY_LOCALISER| Standby Localiser | GAUGE | |float|
| 279|G_MIP_STDBY_SPEED| Standby speed | GAUGE | |float|
| 280|G_MIP_WET_COMPASS| Wet compass | GAUGE | |float|
| 281|G_MIP_YAW_DAMPER| Yaw damper gauge | GAUGE | |float|
| 282|G_OH_CABIN_ALT| Cabin altitude | GAUGE | |float|
| 283|G_OH_CABIN_VSI| Cabin VSI | GAUGE | |float|
| 284|G_OH_CREW_OXYGEN| Oxygen pressure | GAUGE | |float|
| 285|G_OH_DUCT_PRESS_L| Pressure Left | GAUGE | |float|
| 286|G_OH_DUCT_PRESS_R| Pressure Right | GAUGE | |float|
| 287|G_OH_EGT| APU | GAUGE | |float|
| 288|G_OH_FUEL_TEMP| Fuel Temperature | GAUGE | |float|
| 289|G_OH_OUTFLOW_VALVE| Outflow valve position | GAUGE | |float|
| 290|G_OH_PRESS_DIFF| Pressure differential | GAUGE | |float|
| 291|G_OH_TEMPERATURE| Cabin temperature | GAUGE | |float|
| 292|G_PED_ELEV_TRIM| Elevator trim gauge | GAUGE | |float|
| 293|G_PED_RUDDER_TRIM| Rudder trim gauge | GAUGE | |float|
| 294|G_SPEEDBRAKE| Speedbrake servo | GAUGE | |float|
| 295|G_THROTTLE_LEFT| Throttle Servo left | GAUGE | |float|
| 296|G_THROTTLE_RIGHT| Throttle Servo right | GAUGE | |float|
| 297|I_ASP_ADF_1_REC| ASP ADF 1 vol | INDICATOR | |bool|
| 298|I_ASP_ADF_2_REC| ASP ADF 2 vol | INDICATOR | |bool|
| 299|I_ASP_MARKER_REC| ASP Marker vol | INDICATOR | |bool|
| 300|I_ASP_NAV_1_REC| ASP NAV 1 vol | INDICATOR | |bool|
| 301|I_ASP_NAV_2_REC| ASP NAV 2 vol | INDICATOR | |bool|
| 302|I_ASP_PA_REC| ASP PA vol | INDICATOR | |bool|
| 303|I_ASP_SPKR_REC| ASP Spkr vol | INDICATOR | |bool|
| 304|I_ASP_VHF_1_REC| ASP VHF 1 vol | INDICATOR | |bool|
| 305|I_ASP_VHF_1_SEND| ASP VHF 1 mic | INDICATOR | |bool|
| 306|I_ASP_VHF_2_REC| ASP VHF 2 vol | INDICATOR | |bool|
| 307|I_ASP_VHF_2_SEND| ASP VHF 2 mic | INDICATOR | |bool|
| 308|I_ASP2_ADF_1_REC| ASP FO ADF 1 vol | INDICATOR | |bool|
| 309|I_ASP2_ADF_2_REC| ASP FO ADF 2 vol | INDICATOR | |bool|
| 310|I_ASP2_MARKER_REC| ASP FO Marker vol | INDICATOR | |bool|
| 311|I_ASP2_NAV_1_REC| ASP FO NAV 1 vol | INDICATOR | |bool|
| 312|I_ASP2_NAV_2_REC| ASP FO NAV 2 vol | INDICATOR | |bool|
| 313|I_ASP2_PA_REC| ASP FO PA vol | INDICATOR | |bool|
| 314|I_ASP2_SPKR_REC| ASP FO Spkr vol | INDICATOR | |bool|
| 315|I_ASP2_VHF_1_REC| ASP FO VHF 1 vol | INDICATOR | |bool|
| 316|I_ASP2_VHF_1_SEND| ASP FO VHF 1 mic | INDICATOR | |bool|
| 317|I_ASP2_VHF_2_REC| ASP FO VHF 2 vol | INDICATOR | |bool|
| 318|I_ASP2_VHF_2_SEND| ASP FO VHF 2 mic | INDICATOR | |bool|
| 319|I_ASP3_ADF_1_REC| ASP OBS ADF 1 vol | INDICATOR | |bool|
| 320|I_ASP3_ADF_2_REC| ASP OBS ADF 2 vol | INDICATOR | |bool|
| 321|I_ASP3_MARKER_REC| ASP OBS Marker vol | INDICATOR | |bool|
| 322|I_ASP3_NAV_1_REC| ASP OBS NAV 1 vol | INDICATOR | |bool|
| 323|I_ASP3_NAV_2_REC| ASP OBS NAV 2 vol | INDICATOR | |bool|
| 324|I_ASP3_PA_REC| ASP OBS PA vol | INDICATOR | |bool|
| 325|I_ASP3_SPKR_REC| ASP OBS Spkr vol | INDICATOR | |bool|
| 326|I_ASP3_VHF_1_REC| ASP OBS VHF 1 vol | INDICATOR | |bool|
| 327|I_ASP3_VHF_1_SEND| ASP OBS VHF 1 mic | INDICATOR | |bool|
| 328|I_ASP3_VHF_2_REC| ASP OBS VHF 2 vol | INDICATOR | |bool|
| 329|I_ASP3_VHF_2_SEND| ASP OBS VHF 2 mic | INDICATOR | |bool|
| 330|I_CDU1_CALL| CDU CALL light | INDICATOR | |bool|
| 331|I_CDU1_EXEC| CDU EXEC light | INDICATOR | |bool|
| 332|I_CDU1_FAIL| CDU FAIL light | INDICATOR | |bool|
| 333|I_CDU1_MSG| CDU MSG light | INDICATOR | |bool|
| 334|I_CDU1_OFFSET| CDU OFFSET light | INDICATOR | |bool|
| 335|I_CDU2_CALL| CDU2 CALL light | INDICATOR | |bool|
| 336|I_CDU2_EXEC| CDU2 EXEC light | INDICATOR | |bool|
| 337|I_CDU2_FAIL| CDU2 FAIL light | INDICATOR | |bool|
| 338|I_CDU2_MSG| CDU2 MSG light | INDICATOR | |bool|
| 339|I_CDU2_OFFSET| CDU2 OFFSET light | INDICATOR | |bool|
| 340|I_DOOR_AUTO_UNLOCK| Door auto unlock | INDICATOR | |bool|
| 341|I_DOOR_LOCK_FAIL| Door lock fail | INDICATOR | |bool|
| 342|I_FIRE_1| Engine 1 fire handle light | INDICATOR | |bool|
| 343|I_FIRE_2| Engine 2 fire handle light | INDICATOR | |bool|
| 344|I_FIRE_APU| APU fire handle light | INDICATOR | |bool|
| 345|I_FIRE_APU_BOTTLE_DISCHARGE| APU bottle discharged | INDICATOR | |bool|
| 346|I_FIRE_APU_DET_INOPT| Fire APU Det Inop | INDICATOR | |bool|
| 347|I_FIRE_CARGO_AFT| Cargo fire indicator aft | INDICATOR | |bool|
| 348|I_FIRE_CARGO_AFT_EXT| Cargo fire ext light aft | INDICATOR | |bool|
| 349|I_FIRE_CARGO_ARMED_AFT| Cargo fire armed aft | INDICATOR | |bool|
| 350|I_FIRE_CARGO_ARMED_FWD| Cargo fire armed fwd | INDICATOR | |bool|
| 351|I_FIRE_CARGO_DETECTOR_FAULT| Cargo fire detector fault | INDICATOR | |bool|
| 352|I_FIRE_CARGO_DISCH| Cargo fire disch light | INDICATOR | |bool|
| 353|I_FIRE_CARGO_FWD| Cargo fire indicator fwd | INDICATOR | |bool|
| 354|I_FIRE_CARGO_FWD_EXT| Cargo fire ext light fwd | INDICATOR | |bool|
| 355|I_FIRE_ENG_1_OVT| Engine 1 overheat | INDICATOR | |bool|
| 356|I_FIRE_ENG_2_OVT| Engine 2 overheat | INDICATOR | |bool|
| 357|I_FIRE_FAULT| Fire Fault | INDICATOR | |bool|
| 358|I_FIRE_L_BOTTLE_DISCHARGE| L bottle discharged | INDICATOR | |bool|
| 359|I_FIRE_R_BOTTLE_DISCHARGE| R bottle discharged | INDICATOR | |bool|
| 360|I_FIRE_TEST_APU| APU bottle indicator | INDICATOR | |bool|
| 361|I_FIRE_TEST_L| L bottle indicator | INDICATOR | |bool|
| 362|I_FIRE_TEST_R| R bottle indicator | INDICATOR | |bool|
| 363|I_FIRE_WHEEL_WELL_OVT| Fire Wheel well | INDICATOR | |bool|
| 364|I_FW_CP| Fire warning 1 | INDICATOR | |bool|
| 365|I_FW_FO| Fire warning 2 | INDICATOR | |bool|
| 366|I_MC_AIRCOND| Warn AIR_COND | INDICATOR | |bool|
| 367|I_MC_ANTIICE| Warn ANTI_ICE | INDICATOR | |bool|
| 368|I_MC_APU| Warn APU | INDICATOR | |bool|
| 369|I_MC_CP| Master caution 1 | INDICATOR | |bool|
| 370|I_MC_DOORS| Warn DOORS | INDICATOR | |bool|
| 371|I_MC_ELEC| Warn ELEC | INDICATOR | |bool|
| 372|I_MC_ENG| Warn ENG | INDICATOR | |bool|
| 373|I_MC_FLT_CONT| Warn FLT_CONT | INDICATOR | |bool|
| 374|I_MC_FO| Master caution 2 | INDICATOR | |bool|
| 375|I_MC_FUEL| Warn FUEL | INDICATOR | |bool|
| 376|I_MC_HYDRAULICS| Warn HYD | INDICATOR | |bool|
| 377|I_MC_IRS| Warn IRS | INDICATOR | |bool|
| 378|I_MC_OVERHEAD| Warn OVERHEAD | INDICATOR | |bool|
| 379|I_MC_OVHT| Warn OVHT_DET | INDICATOR | |bool|
| 380|I_MCP_ALT_HOLD| MCP Alt hold | INDICATOR | |bool|
| 381|I_MCP_APP| MCP APP | INDICATOR | |bool|
| 382|I_MCP_AT| MCP A/T | INDICATOR | |bool|
| 383|I_MCP_CMD_A| MCP CMD A | INDICATOR | |bool|
| 384|I_MCP_CMD_B| MCP CMD B | INDICATOR | |bool|
| 385|I_MCP_CWS_A| MCP CWS A | INDICATOR | |bool|
| 386|I_MCP_CWS_B| MCP CWS B | INDICATOR | |bool|
| 387|I_MCP_FCCA| MCP FCC A Master | INDICATOR | |bool|
| 388|I_MCP_FCCB| MCP FCC B Master | INDICATOR | |bool|
| 389|I_MCP_HDG_SEL| MCP HDG SEL | INDICATOR | |bool|
| 390|I_MCP_LNAV| MCP LNAV | INDICATOR | |bool|
| 391|I_MCP_LVLCHANGE| MCP Level Change | INDICATOR | |bool|
| 392|I_MCP_N1| MCP N1 | INDICATOR | |bool|
| 393|I_MCP_SPEED| MCP Speed | INDICATOR | |bool|
| 394|I_MCP_VNAV| MCP VNAV | INDICATOR | |bool|
| 395|I_MCP_VORLOC| MCP VOR/LOC | INDICATOR | |bool|
| 396|I_MCP_VS| MCP V/S | INDICATOR | |bool|
| 397|I_MIP_ANTI_SKID_INOP| Anti skid INOP | INDICATOR | |bool|
| 398|I_MIP_ASA_APA_1| ASA A/P Amber Capt | INDICATOR | |bool|
| 399|I_MIP_ASA_APA_2| ASA A/P Amber F/O | INDICATOR | |bool|
| 400|I_MIP_ASA_APR_1| ASA A/P Red Capt | INDICATOR | |bool|
| 401|I_MIP_ASA_APR_2| ASA A/P Red F/O | INDICATOR | |bool|
| 402|I_MIP_ASA_ATA_1| ASA A/T Amber Capt | INDICATOR | |bool|
| 403|I_MIP_ASA_ATA_2| ASA A/T Amber F/O | INDICATOR | |bool|
| 404|I_MIP_ASA_ATR_1| ASA A/T Red Capt | INDICATOR | |bool|
| 405|I_MIP_ASA_ATR_2| ASA A/T Red F/O | INDICATOR | |bool|
| 406|I_MIP_ASA_FMC_1| ASA FMC Capt | INDICATOR | |bool|
| 407|I_MIP_ASA_FMC_2| ASA FMC F/O | INDICATOR | |bool|
| 408|I_MIP_AUTOBRAKE_DISARM| Autobrake disarm | INDICATOR | |bool|
| 409|I_MIP_AUTOLAND| Autoland | INDICATOR | |bool|
| 410|I_MIP_BELOW_GS_CP| Below GS CP | INDICATOR | |bool|
| 411|I_MIP_BELOW_GS_FO| Below GS FO | INDICATOR | |bool|
| 412|I_MIP_BRAKE_TEMP| Brake Temp | INDICATOR | |bool|
| 413|I_MIP_CABIN_ALTITUDE| Cabin altitude indicator | INDICATOR | |bool|
| 414|I_MIP_FLAP_LOAD_RELIEF| Flap load relief | INDICATOR | |bool|
| 415|I_MIP_GEAR_LEFT_DOWN| Gear left | INDICATOR | |bool|
| 416|I_MIP_GEAR_LEFT_TRANSIT| Gear left transit | INDICATOR | |bool|
| 417|I_MIP_GEAR_NOSE_DOWN| Gear nose | INDICATOR | |bool|
| 418|I_MIP_GEAR_NOSE_TRANSIT| Gear nose transit | INDICATOR | |bool|
| 419|I_MIP_GEAR_RIGHT_DOWN| Gear right | INDICATOR | |bool|
| 420|I_MIP_GEAR_RIGHT_TRANSIT| Gear right transit | INDICATOR | |bool|
| 421|I_MIP_GPWS_INOP| GPWS Inop | INDICATOR | |bool|
| 422|I_MIP_LE_FLAP_EXT| LE Flap Extend | INDICATOR | |bool|
| 423|I_MIP_LE_FLAP_TRANSIT| LE Flap Transit | INDICATOR | |bool|
| 424|I_MIP_PARKING_BRAKE| Parking brake | INDICATOR | |bool|
| 425|I_MIP_RUNWAY_INOP| Runway Inop | INDICATOR | |bool|
| 426|I_MIP_SPEEDBRAKE_DO_NOT_ARM| Speed brake do not arm | INDICATOR | |bool|
| 427|I_MIP_SPOILER_ARMED| Spoiler Armed | INDICATOR | |bool|
| 428|I_MIP_SPOILER_EXTEND| Spoiler Extend | INDICATOR | |bool|
| 429|I_MIP_STAB_OUT_OF_TRIM| Stab out of trim | INDICATOR | |bool|
| 430|I_MIP_TAKEOFF_CONFIG| Takeoff config | INDICATOR | |bool|
| 431|I_NONE|  |  | ||
| 432|I_OH_ALPHA_VANE1| Alpha Vane Heat L | INDICATOR | |bool|
| 433|I_OH_ALPHA_VANE2| Alpha Vane Heat R | INDICATOR | |bool|
| 434|I_OH_APU_FAULT| APU FAULT | INDICATOR | |bool|
| 435|I_OH_APU_GEN_OFF| APU GEN OFF BUS | INDICATOR | |bool|
| 436|I_OH_APU_LOW_OIL_PRESSURE| APU Low oil pressure | INDICATOR | |bool|
| 437|I_OH_APU_MAINT| APU Maint | INDICATOR | |bool|
| 438|I_OH_APU_OVERSPEED| APU Overspeed | INDICATOR | |bool|
| 439|I_OH_ATTEND| Attend call | INDICATOR | |bool|
| 440|I_OH_AUTO_SLAT| Auto slat Fail | INDICATOR | |bool|
| 441|I_OH_AUX_PITOT| auxPitot Heat | INDICATOR | |bool|
| 442|I_OH_BATT_DISCHARGE| Bat discharge | INDICATOR | |bool|
| 443|I_OH_BLEED_TRIP_L| Bleed trip off 1 | INDICATOR | |bool|
| 444|I_OH_BLEED_TRIP_R| Bleed trip off 2 | INDICATOR | |bool|
| 445|I_OH_CAPT_PITOT| Capt Pitot Heat | INDICATOR | |bool|
| 446|I_OH_CO_PITOT| Copilot Pitot Heat | INDICATOR | |bool|
| 447|I_OH_COWL_AI_L| Cowl Anti-Ice L | INDICATOR | |bool|
| 448|I_OH_COWL_AI_R| Cowl Anti-Ice R | INDICATOR | |bool|
| 449|I_OH_COWL_VALVE_L| Cowl valve open L | INDICATOR | |bool|
| 450|I_OH_COWL_VALVE_R| Cowl valve open R | INDICATOR | |bool|
| 451|I_OH_CROSSFEED| Crossfeed indicator | INDICATOR | |bool|
| 452|I_OH_DOOR_AFT_CARGO| Door Aft Cargo | INDICATOR | |bool|
| 453|I_OH_DOOR_AFT_ENTRY| Door Aft Entry | INDICATOR | |bool|
| 454|I_OH_DOOR_AFT_SERVICE| Door Aft Service | INDICATOR | |bool|
| 455|I_OH_DOOR_AIRSTAIRS| Door Air Stairs | INDICATOR | |bool|
| 456|I_OH_DOOR_EQUIP| Door Equip | INDICATOR | |bool|
| 457|I_OH_DOOR_FWD_CARGO| Door Fwd Cargo | INDICATOR | |bool|
| 458|I_OH_DOOR_FWD_ENTRY| Door Fwd entry | INDICATOR | |bool|
| 459|I_OH_DOOR_FWD_SERVICE| Door Fwd Service | INDICATOR | |bool|
| 460|I_OH_DOOR_LEFT_AFT_OVERWING| Door Left Aft Overwing | INDICATOR | |bool|
| 461|I_OH_DOOR_LEFT_FWD_OVERWING| Door Left Fwd Overwing | INDICATOR | |bool|
| 462|I_OH_DOOR_RIGHT_AFT_OVERWING| Door Right Aft Overwing | INDICATOR | |bool|
| 463|I_OH_DOOR_RIGHT_FWD_OVERWING| Door Right Fwd Overwing | INDICATOR | |bool|
| 464|I_OH_DRIVE1| Drive 1 | INDICATOR | |bool|
| 465|I_OH_DRIVE2| Drive 2 | INDICATOR | |bool|
| 466|I_OH_DUALBLEED| Dual bleed | INDICATOR | |bool|
| 467|I_OH_EEC_ALTN1| EEC Altn left | INDICATOR | |bool|
| 468|I_OH_EEC_ALTN2| EEC Altn right | INDICATOR | |bool|
| 469|I_OH_EEC1| EEC On left | INDICATOR | |bool|
| 470|I_OH_EEC2| EEC On right | INDICATOR | |bool|
| 471|I_OH_ELEC| ELEC | INDICATOR | |bool|
| 472|I_OH_ELEC_HYD_PUMP_1| Hyd ELEC1 LP | INDICATOR | |bool|
| 473|I_OH_ELEC_HYD_PUMP_2| Hyd ELEC2 LP | INDICATOR | |bool|
| 474|I_OH_ELEC_HYD_PUMP_OVHT_1| Hyd ELEC1 OVHT | INDICATOR | |bool|
| 475|I_OH_ELEC_HYD_PUMP_OVHT_2| Hyd ELEC2 OVHT | INDICATOR | |bool|
| 476|I_OH_ELEV_PITOT1| Elev pitot Heat L | INDICATOR | |bool|
| 477|I_OH_ELEV_PITOT2| Elev pitot Heat R | INDICATOR | |bool|
| 478|I_OH_ELT| ELT | INDICATOR | |bool|
| 479|I_OH_EMERG_EXIT_LIGHTS| Emerg Exit Lights not armed | INDICATOR | |bool|
| 480|I_OH_ENG_HYD_PUMP_L| Hyd ENG1 LP | INDICATOR | |bool|
| 481|I_OH_ENG_HYD_PUMP_R| Hyd ENG2 LP | INDICATOR | |bool|
| 482|I_OH_ENG_VALVE_CLOSED_L| ENG Valve Closed L | INDICATOR | |bool|
| 483|I_OH_ENG_VALVE_CLOSED_R| ENG Valve Closed R | INDICATOR | |bool|
| 484|I_OH_ENGINE_CONTROL1| Engine control left | INDICATOR | |bool|
| 485|I_OH_ENGINE_CONTROL2| Engine control right | INDICATOR | |bool|
| 486|I_OH_EQUIP_COOLING_EXHAUST| Equip cooling exhaust Off | INDICATOR | |bool|
| 487|I_OH_EQUIP_COOLING_SUPPLY| Equip cooling supply Off | INDICATOR | |bool|
| 488|I_OH_FEEL_DIFF_PRESS| Feel Diff Press | INDICATOR | |bool|
| 489|I_OH_FILTER_BYPASS1| Filter Bypass L | INDICATOR | |bool|
| 490|I_OH_FILTER_BYPASS2| Filter Bypass R | INDICATOR | |bool|
| 491|I_OH_FLIGHT_REC| Flight recorder off | INDICATOR | |bool|
| 492|I_OH_FLT_CTRL_LOW_PRESS_A| FLT Control low pressure A | INDICATOR | |bool|
| 493|I_OH_FLT_CTRL_LOW_PRESS_B| FLT Control low pressure B | INDICATOR | |bool|
| 494|I_OH_FUEL_PUMP_CL| Fuel Center Left LP | INDICATOR | |bool|
| 495|I_OH_FUEL_PUMP_CR| Fuel Center Right LP | INDICATOR | |bool|
| 496|I_OH_FUEL_PUMP_LA| Fuel Left Aft LP | INDICATOR | |bool|
| 497|I_OH_FUEL_PUMP_LF| Fuel Left Fwd LP | INDICATOR | |bool|
| 498|I_OH_FUEL_PUMP_RA| Fuel Right Aft LP | INDICATOR | |bool|
| 499|I_OH_FUEL_PUMP_RF| Fuel Right Fwd LP | INDICATOR | |bool|
| 500|I_OH_GEAR_LEFT_DOWN| Gear left aft oh | INDICATOR | |bool|
| 501|I_OH_GEAR_NOSE_DOWN| Gear nose aft ovh | INDICATOR | |bool|
| 502|I_OH_GEAR_RIGHT_DOWN| Gear right aft ovh | INDICATOR | |bool|
| 503|I_OH_GEN_BUS_OFF1| GEN BUS OFF 1 | INDICATOR | |bool|
| 504|I_OH_GEN_BUS_OFF2| GEN BUS OFF 2 | INDICATOR | |bool|
| 505|I_OH_GLS| GLS | INDICATOR | |bool|
| 506|I_OH_GPS| GPS | INDICATOR | |bool|
| 507|I_OH_GROUND_POWER_AVAILABLE| Grd Pwr available | INDICATOR | |bool|
| 508|I_OH_HYD_STBY_LOW_PRESS| Hyd standby low pressure | INDICATOR | |bool|
| 509|I_OH_HYD_STBY_LOW_QUANT| Hyd standby low quantity | INDICATOR | |bool|
| 510|I_OH_ILS| ILS | INDICATOR | |bool|
| 511|I_OH_IRS_ALIGN_L| IRS left align | INDICATOR | |bool|
| 512|I_OH_IRS_ALIGN_R| IRS right align | INDICATOR | |bool|
| 513|I_OH_IRS_CLR_KEY| IRS Keypad CLR cue | INDICATOR | |bool|
| 514|I_OH_IRS_DCFAIL_L| IRS left DC Fail | INDICATOR | |bool|
| 515|I_OH_IRS_DCFAIL_R| IRS right DC Fail | INDICATOR | |bool|
| 516|I_OH_IRS_DOT1| IRS Panel dot 1 | INDICATOR | |bool|
| 517|I_OH_IRS_DOT2| IRS Panel dot 2 | INDICATOR | |bool|
| 518|I_OH_IRS_DOT3| IRS Panel dot 3 | INDICATOR | |bool|
| 519|I_OH_IRS_DOT4| IRS Panel dot 4 | INDICATOR | |bool|
| 520|I_OH_IRS_DOT5| IRS Panel dot 5 | INDICATOR | |bool|
| 521|I_OH_IRS_DOT6| IRS Panel dot 6 | INDICATOR | |bool|
| 522|I_OH_IRS_ENT_KEY| IRS Keypad ENT cue | INDICATOR | |bool|
| 523|I_OH_IRS_FAULT_L| IRS left Fault | INDICATOR | |bool|
| 524|I_OH_IRS_FAULT_R| IRS right Fault | INDICATOR | |bool|
| 525|I_OH_IRS_ONDC_L| IRS left On DC | INDICATOR | |bool|
| 526|I_OH_IRS_ONDC_R| IRS right On DC | INDICATOR | |bool|
| 527|I_OH_LAV_SMOKE| Lavatory smoke | INDICATOR | |bool|
| 528|I_OH_LEDEVICES_EXT_FLAP1| Flaps extended 1 | INDICATOR | |bool|
| 529|I_OH_LEDEVICES_EXT_FLAP2| Flaps extended 2 | INDICATOR | |bool|
| 530|I_OH_LEDEVICES_EXT_FLAP3| Flaps extended 3 | INDICATOR | |bool|
| 531|I_OH_LEDEVICES_EXT_FLAP4| Flaps extended 4 | INDICATOR | |bool|
| 532|I_OH_LEDEVICES_EXT_SLAT1| Slats extended 1 | INDICATOR | |bool|
| 533|I_OH_LEDEVICES_EXT_SLAT2| Slats extended 2 | INDICATOR | |bool|
| 534|I_OH_LEDEVICES_EXT_SLAT3| Slats extended 3 | INDICATOR | |bool|
| 535|I_OH_LEDEVICES_EXT_SLAT4| Slats extended 4 | INDICATOR | |bool|
| 536|I_OH_LEDEVICES_EXT_SLAT5| Slats extended 5 | INDICATOR | |bool|
| 537|I_OH_LEDEVICES_EXT_SLAT6| Slats extended 6 | INDICATOR | |bool|
| 538|I_OH_LEDEVICES_EXT_SLAT7| Slats extended 7 | INDICATOR | |bool|
| 539|I_OH_LEDEVICES_EXT_SLAT8| Slats extended 8 | INDICATOR | |bool|
| 540|I_OH_LEDEVICES_FULLEXT_SLAT1| Slats fullExtended 1 | INDICATOR | |bool|
| 541|I_OH_LEDEVICES_FULLEXT_SLAT2| Slats fullExtended 2 | INDICATOR | |bool|
| 542|I_OH_LEDEVICES_FULLEXT_SLAT3| Slats fullExtended 3 | INDICATOR | |bool|
| 543|I_OH_LEDEVICES_FULLEXT_SLAT4| Slats fullExtended 4 | INDICATOR | |bool|
| 544|I_OH_LEDEVICES_FULLEXT_SLAT5| Slats fullExtended 5 | INDICATOR | |bool|
| 545|I_OH_LEDEVICES_FULLEXT_SLAT6| Slats fullExtended 6 | INDICATOR | |bool|
| 546|I_OH_LEDEVICES_FULLEXT_SLAT7| Slats fullExtended 7 | INDICATOR | |bool|
| 547|I_OH_LEDEVICES_FULLEXT_SLAT8| Slats fullExtended 8 | INDICATOR | |bool|
| 548|I_OH_LEDEVICES_TRANS_FLAP1| Flaps transit 1 | INDICATOR | |bool|
| 549|I_OH_LEDEVICES_TRANS_FLAP2| Flaps transit 2 | INDICATOR | |bool|
| 550|I_OH_LEDEVICES_TRANS_FLAP3| Flaps transit 3 | INDICATOR | |bool|
| 551|I_OH_LEDEVICES_TRANS_FLAP4| Flaps transit 4 | INDICATOR | |bool|
| 552|I_OH_LEDEVICES_TRANS_SLAT1| Slats transit 1 | INDICATOR | |bool|
| 553|I_OH_LEDEVICES_TRANS_SLAT2| Slats transit 2 | INDICATOR | |bool|
| 554|I_OH_LEDEVICES_TRANS_SLAT3| Slats transit 3 | INDICATOR | |bool|
| 555|I_OH_LEDEVICES_TRANS_SLAT4| Slats transit 4 | INDICATOR | |bool|
| 556|I_OH_LEDEVICES_TRANS_SLAT5| Slats transit 5 | INDICATOR | |bool|
| 557|I_OH_LEDEVICES_TRANS_SLAT6| Slats transit 6 | INDICATOR | |bool|
| 558|I_OH_LEDEVICES_TRANS_SLAT7| Slats transit 7 | INDICATOR | |bool|
| 559|I_OH_LEDEVICES_TRANS_SLAT8| Slats transit 8 | INDICATOR | |bool|
| 560|I_OH_MACH_TRIM| Mach Trim Fail | INDICATOR | |bool|
| 561|I_OH_PACK_L| Pack L | INDICATOR | |bool|
| 562|I_OH_PACK_R| Pack R | INDICATOR | |bool|
| 563|I_OH_PASS_OXY_ON| Pass oxy on | INDICATOR | |bool|
| 564|I_OH_PRES_ALTN| Pressurization altn | INDICATOR | |bool|
| 565|I_OH_PRES_AUTO_FAIL| Pressurization auto fail | INDICATOR | |bool|
| 566|I_OH_PRES_MANUAL| Pressurization manual | INDICATOR | |bool|
| 567|I_OH_PRES_OFFSCHED| Off sched descent | INDICATOR | |bool|
| 568|I_OH_PSEU| PSEU | INDICATOR | |bool|
| 569|I_OH_RAMDOOR_L| Ram door full open L | INDICATOR | |bool|
| 570|I_OH_RAMDOOR_R| Ram door full open R | INDICATOR | |bool|
| 571|I_OH_REVERSER1| Reverser left | INDICATOR | |bool|
| 572|I_OH_REVERSER2| Reverser right | INDICATOR | |bool|
| 573|I_OH_SOURCE_OFF1| Source OFF 1 | INDICATOR | |bool|
| 574|I_OH_SOURCE_OFF2| Source OFF 2 | INDICATOR | |bool|
| 575|I_OH_SPAR_VALVE_CLOSED_L| SPAR Valve Closed L | INDICATOR | |bool|
| 576|I_OH_SPAR_VALVE_CLOSED_R| SPAR Valve Closed R | INDICATOR | |bool|
| 577|I_OH_SPEED_TRIM| Speed Trim Fail | INDICATOR | |bool|
| 578|I_OH_STDBY_POWER_OFF| Standby pwr off | INDICATOR | |bool|
| 579|I_OH_STDBY_RUD_ON| Stdby Rud On | INDICATOR | |bool|
| 580|I_OH_TEMP_PROBE| tempProbe Heat | INDICATOR | |bool|
| 581|I_OH_TR_UNIT| TR UNIT | INDICATOR | |bool|
| 582|I_OH_TRANS_OFF1| Transfer bus OFF 1 | INDICATOR | |bool|
| 583|I_OH_TRANS_OFF2| Transfer bus OFF 2 | INDICATOR | |bool|
| 584|I_OH_VOICE_RECORDER_STATUS| Voice recorder status | INDICATOR | |bool|
| 585|I_OH_WAI_VALVE_L| WAI L Valve Open | INDICATOR | |bool|
| 586|I_OH_WAI_VALVE_R| WAI R Valve Open | INDICATOR | |bool|
| 587|I_OH_WINDOW_HEAT_FL| Window heat FWD L on | INDICATOR | |bool|
| 588|I_OH_WINDOW_HEAT_FR| Window heat FWD R on | INDICATOR | |bool|
| 589|I_OH_WINDOW_HEAT_OVT_FL| Window heat FWD L overheat | INDICATOR | |bool|
| 590|I_OH_WINDOW_HEAT_OVT_FR| Window heat FWD R overheat | INDICATOR | |bool|
| 591|I_OH_WINDOW_HEAT_OVT_SL| Window heat Side L overheat | INDICATOR | |bool|
| 592|I_OH_WINDOW_HEAT_OVT_SR| Window heat Side R overheat | INDICATOR | |bool|
| 593|I_OH_WINDOW_HEAT_SL| Window heat Side L on | INDICATOR | |bool|
| 594|I_OH_WINDOW_HEAT_SR| Window heat Side R on | INDICATOR | |bool|
| 595|I_OH_WINGBODY_OVT_L| Wing-body overheat 1 | INDICATOR | |bool|
| 596|I_OH_WINGBODY_OVT_R| Wing-body overheat 2 | INDICATOR | |bool|
| 597|I_OH_YAW_DAMPER| Yaw damper | INDICATOR | |bool|
| 598|I_OH_ZONE_TEMP_AFT| Zone temp AFT CAB | INDICATOR | |bool|
| 599|I_OH_ZONE_TEMP_CONT| Zone temp CONT CAB | INDICATOR | |bool|
| 600|I_OH_ZONE_TEMP_FWD| Zone temp FWD CAB | INDICATOR | |bool|
| 601|I_RADIO_HF1_AM| HF1 AM modulation | INDICATOR | |bool|
| 602|I_RADIO_HF2_AM| HF2 AM modulation | INDICATOR | |bool|
| 603|I_RMP1_ADF| RMP Capt ADF indicator | INDICATOR | |bool|
| 604|I_RMP1_AM| RMP Capt AM | INDICATOR | |bool|
| 605|I_RMP1_HF1| RMP Capt HF1 indicator | INDICATOR | |bool|
| 606|I_RMP1_HF2| RMP Capt HF2 indicator | INDICATOR | |bool|
| 607|I_RMP1_NAV1| RMP Capt NAV1 indicator | INDICATOR | |bool|
| 608|I_RMP1_NAV2| RMP Capt NAV2 indicator | INDICATOR | |bool|
| 609|I_RMP1_OFFSIDE_TUNING| RMP Capt offside tuning | INDICATOR | |bool|
| 610|I_RMP1_VHF1| RMP Capt VHF1 indicator | INDICATOR | |bool|
| 611|I_RMP1_VHF2| RMP Capt VHF2 indicator | INDICATOR | |bool|
| 612|I_RMP1_VHF3| RMP Capt VHF3 indicator | INDICATOR | |bool|
| 613|I_RMP2_ADF| RMP F/O ADF indicator | INDICATOR | |bool|
| 614|I_RMP2_AM| RMP F/O AM | INDICATOR | |bool|
| 615|I_RMP2_HF1| RMP F/O HF1 indicator | INDICATOR | |bool|
| 616|I_RMP2_HF2| RMP F/O HF2 indicator | INDICATOR | |bool|
| 617|I_RMP2_NAV1| RMP F/O NAV1 indicator | INDICATOR | |bool|
| 618|I_RMP2_NAV2| RMP F/O NAV2 indicator | INDICATOR | |bool|
| 619|I_RMP2_OFFSIDE_TUNING| RMP F/O offside tuning | INDICATOR | |bool|
| 620|I_RMP2_VHF1| RMP F/O VHF1 indicator | INDICATOR | |bool|
| 621|I_RMP2_VHF2| RMP F/O VHF2 indicator | INDICATOR | |bool|
| 622|I_RMP2_VHF3| RMP F/O VHF3 indicator | INDICATOR | |bool|
| 623|I_XPDR_FAIL|  |  | ||
| 624|N_ELEC_PANEL_LOWER_CENTER| Electric Panel Lower center | NUMERICAL | |int|
| 625|N_ELEC_PANEL_LOWER_LEFT| Electric Panel Lower left | NUMERICAL | |int|
| 626|N_ELEC_PANEL_LOWER_RIGHT| Electric Panel Lower right | NUMERICAL | |int|
| 627|N_ELEC_PANEL_UPPER_CENTER| Electric Panel Upper center | NUMERICAL | |int|
| 628|N_ELEC_PANEL_UPPER_LEFT| Electric Panel Upper left | NUMERICAL | |int|
| 629|N_ELEC_PANEL_UPPER_RIGHT| Electric Panel Upper right | NUMERICAL | |int|
| 630|N_FREQ_ADF1| Radio freq ADF1 | NUMERICAL | |int|
| 631|N_FREQ_ADF2| Radio freq ADF2 | NUMERICAL | |int|
| 632|N_FREQ_COM1| Radio freq COM1 | NUMERICAL | |int|
| 633|N_FREQ_COM2| Radio freq COM2 | NUMERICAL | |int|
| 634|N_FREQ_COM3| Radio freq COM3 | NUMERICAL | |int|
| 635|N_FREQ_HF1| Radio freq HF1 | NUMERICAL | |int|
| 636|N_FREQ_HF2| Radio freq HF2 | NUMERICAL | |int|
| 637|N_FREQ_NAV1| Radio freq NAV1 | NUMERICAL | |int|
| 638|N_FREQ_NAV2| Radio freq NAV2 | NUMERICAL | |int|
| 639|N_FREQ_STANDBY_ADF1| Radio standby freq ADF1 | NUMERICAL | |int|
| 640|N_FREQ_STANDBY_ADF2| Radio standby freq ADF2 | NUMERICAL | |int|
| 641|N_FREQ_STANDBY_COM1| Radio standby freq COM1 | NUMERICAL | |int|
| 642|N_FREQ_STANDBY_COM2| Radio standby freq COM2 | NUMERICAL | |int|
| 643|N_FREQ_STANDBY_COM3| Radio standby freq COM3 | NUMERICAL | |int|
| 644|N_FREQ_STANDBY_HF1| Radio standby freq HF1 | NUMERICAL | |int|
| 645|N_FREQ_STANDBY_HF2| Radio standby freq HF2 | NUMERICAL | |int|
| 646|N_FREQ_STANDBY_NAV1| Radio standby freq NAV1 | NUMERICAL | |int|
| 647|N_FREQ_STANDBY_NAV2| Radio standby freq NAV2 | NUMERICAL | |int|
| 648|N_FREQ_STANDBY_XPDR2| Radio standby freq XPDR2 | NUMERICAL | |int|
| 649|N_FREQ_XPDR| Radio freq XPDR | NUMERICAL | |int|
| 650|N_FREQ_XPDR2| Radio freq XPDR2 | NUMERICAL | |int|
| 651|N_FUEL_FLOW_1| Fuel Flow left | NUMERICAL | |int|
| 652|N_FUEL_FLOW_2| Fuel Flow right | NUMERICAL | |int|
| 653|N_IRS_DISP_LEFT| IRS Display left number | NUMERICAL | |int|
| 654|N_IRS_DISP_RIGHT| IRS Display right number | NUMERICAL | |int|
| 655|N_MCP_ALT| MCP ALT VAL output | NUMERICAL | |int|
| 656|N_MCP_COURSE1| MCP COURSE 1 VAL output | NUMERICAL | |int|
| 657|N_MCP_COURSE2| MCP COURSE 2 VAL output | NUMERICAL | |int|
| 658|N_MCP_HEADING| MCP HEADING VAL output | NUMERICAL | |int|
| 659|N_MCP_SPEED| MCP SPEED VAL output | NUMERICAL | |int|
| 660|N_MCP_VS| MCP V/S VAL output | NUMERICAL | |int|
| 661|N_MIP_FLAP_GAUGE_LEFT| Flap numerical | NUMERICAL | |int|
| 662|N_MIP_FLAP_GAUGE_RIGHT| Flap right numerical | NUMERICAL | |int|
| 663|N_OH_FLIGHT_ALT| Cruise alt | NUMERICAL | |int|
| 664|N_OH_LAND_ALT| Land alt | NUMERICAL | |int|
| 665|N_RADIO_ADF1_MODE| ADF1 mode | NUMERICAL | |int|
| 666|N_RADIO_ADF2_MODE| ADF2 mode | NUMERICAL | |int|
| 667|N_RADIO_ALTITUDE| Radio altitude | NUMERICAL | |int|
| 668|N_RMP1_ACT_MODE| RMP Capt active mode | NUMERICAL | |int|
| 669|N_RMP1_ACT_VALUE| RMP Capt active value | NUMERICAL | |int|
| 670|N_RMP1_STDBY_MODE| RMP Capt standby mode | NUMERICAL | |int|
| 671|N_RMP1_STDBY_VALUE| RMP Capt standby value | NUMERICAL | |int|
| 672|N_RMP2_ACT_MODE| RMP F/O active mode | NUMERICAL | |int|
| 673|N_RMP2_ACT_VALUE| RMP F/O active value | NUMERICAL | |int|
| 674|N_RMP2_STDBY_MODE| RMP F/O standby mode | NUMERICAL | |int|
| 675|N_RMP2_STDBY_VALUE| RMP F/O standby value | NUMERICAL | |int|
| 676|N_TRIM_MOTOR_VALUE| Trim motor value | NUMERICAL | |int|
| 677|R_ADF1_ACTIVE| Radio freq input ADF1 | ANALOG | |char|
| 678|R_ADF1_STANDBY| Radio standby freq input ADF1 | ANALOG | |char|
| 679|R_ADF2_ACTIVE| Radio freq input ADF2 | ANALOG | |char|
| 680|R_ADF2_STANDBY| Radio standby freq input ADF2 | ANALOG | |char|
| 681|R_COM1_ACTIVE| Radio freq input COM1 | ANALOG | |char|
| 682|R_COM1_STANDBY| Radio standby freq input COM1 | ANALOG | |char|
| 683|R_COM2_ACTIVE| Radio freq input COM2 | ANALOG | |char|
| 684|R_COM2_STANDBY| Radio standby freq input COM2 | ANALOG | |char|
| 685|R_COM3_ACTIVE| Radio freq input COM3 | ANALOG | |char|
| 686|R_COM3_STANDBY| Radio standby freq input COM3 | ANALOG | |char|
| 687|R_HF1_ACTIVE| Radio freq input HF1 | ANALOG | |char|
| 688|R_HF2_ACTIVE| Radio freq input HF2 | ANALOG | |char|
| 689|R_NAV1_ACTIVE| Radio freq input NAV1 | ANALOG | |char|
| 690|R_NAV1_STANDBY| Radio standby freq input NAV1 | ANALOG | |char|
| 691|R_NAV2_ACTIVE| Radio freq input NAV2 | ANALOG | |char|
| 692|R_NAV2_STANDBY| Radio standby freq input NAV2 | ANALOG | |char|
| 693|R_XPDR| Radio freq input XPDR | ANALOG | |char|
| 694|R_XPDR2| Radio freq input XPDR2 | ANALOG | |char|
| 695|S_ADF1_TFC| Radio TFR ADF1 | SWITCH | Normal,Pushed|char*|
| 696|S_ADF2_TFC| Radio TFR ADF2 | SWITCH | Normal,Pushed|char*|
| 697|S_AILERON_TRIM| Aileron trim | SWITCH | Center,Left,Right|char*|
| 698|S_ASA_AP1| ASA A/P reset Capt | SWITCH | Off,Pushed|char*|
| 699|S_ASA_AP2| ASA A/P reset F/O | SWITCH | Off,Pushed|char*|
| 700|S_ASA_AT1| ASA A/T reset Capt | SWITCH | Off,Pushed|char*|
| 701|S_ASA_AT2| ASA A/T reset F/O | SWITCH | Off,Pushed|char*|
| 702|S_ASA_FMC1| ASA FMC reset Capt | SWITCH | Off,Pushed|char*|
| 703|S_ASA_FMC2| ASA FMC reset F/O | SWITCH | Off,Pushed|char*|
| 704|S_ASA_TEST_1| ASA Test Capt | SWITCH | Off,1,2|char*|
| 705|S_ASA_TEST_2| ASA Test F/O | SWITCH | Off,1,2|char*|
| 706|S_ASP_ADF_1_REC| ASP ADF 1 vol | SWITCH | Off,Pushed|char*|
| 707|S_ASP_ADF_1_REC_LATCH| ASP ADF 1 vol latch | SWITCH | Off,On|char*|
| 708|S_ASP_ADF_2_REC| ASP ADF 2 vol | SWITCH | Off,Pushed|char*|
| 709|S_ASP_ADF_2_REC_LATCH| ASP ADF 2 vol latch | SWITCH | Off,On|char*|
| 710|S_ASP_ALT| ASP Alternate Selected | SWITCH | Off,On|char*|
| 711|S_ASP_BOOM| ASP Boom Selected | SWITCH | Off,On|char*|
| 712|S_ASP_IC| ASP IC Selected | SWITCH | Off,On|char*|
| 713|S_ASP_MARKER_REC| ASP Marker vol | SWITCH | Off,Pushed|char*|
| 714|S_ASP_MARKER_REC_LATCH| ASP Marker vol latch | SWITCH | Off,On|char*|
| 715|S_ASP_MASK| ASP Mask Selected | SWITCH | Off,On|char*|
| 716|S_ASP_NAV_1_REC| ASP NAV 1 vol | SWITCH | Off,Pushed|char*|
| 717|S_ASP_NAV_1_REC_LATCH| ASP NAV 1 vol latch | SWITCH | Off,On|char*|
| 718|S_ASP_NAV_2_REC| ASP NAV 2 vol | SWITCH | Off,Pushed|char*|
| 719|S_ASP_NAV_2_REC_LATCH| ASP NAV 2 vol latch | SWITCH | Off,On|char*|
| 720|S_ASP_NORM| ASP Normal Selected | SWITCH | Off,On|char*|
| 721|S_ASP_PA_REC| ASP PA vol | SWITCH | Off,Pushed|char*|
| 722|S_ASP_PA_REC_LATCH| ASP PA vol latch | SWITCH | Off,On|char*|
| 723|S_ASP_RT| ASP RT Selected | SWITCH | Off,On|char*|
| 724|S_ASP_SIGNAL_FILTER| ASP filter mode | SWITCH | B,V,R|char*|
| 725|S_ASP_SPKR_REC| ASP Spkr vol | SWITCH | Off,Pushed|char*|
| 726|S_ASP_SPKR_REC_LATCH| ASP Spkr vol latch | SWITCH | Off,On|char*|
| 727|S_ASP_VHF_1_REC| ASP VHF 1 vol | SWITCH | Off,Pushed|char*|
| 728|S_ASP_VHF_1_REC_LATCH| ASP VHF 1 vol latch | SWITCH | Off,On|char*|
| 729|S_ASP_VHF_1_SEND| ASP VHF 1 mic | SWITCH | Off,Pushed|char*|
| 730|S_ASP_VHF_1_SEND_LATCH| ASP VHF 1 mic latch | SWITCH | Off,On|char*|
| 731|S_ASP_VHF_2_REC| ASP VHF 2 vol | SWITCH | Off,Pushed|char*|
| 732|S_ASP_VHF_2_REC_LATCH| ASP VHF 2 vol latch | SWITCH | Off,On|char*|
| 733|S_ASP_VHF_2_SEND| ASP VHF 2 mic | SWITCH | Off,Pushed|char*|
| 734|S_ASP_VHF_2_SEND_LATCH| ASP VHF 2 mic latch | SWITCH | Off,On|char*|
| 735|S_ASP2_ADF_1_REC| ASP FO ADF 1 vol | SWITCH | Off,Pushed|char*|
| 736|S_ASP2_ADF_1_REC_LATCH| ASP FO ADF 1 vol latch | SWITCH | Off,On|char*|
| 737|S_ASP2_ADF_2_REC| ASP FO ADF 2 vol | SWITCH | Off,Pushed|char*|
| 738|S_ASP2_ADF_2_REC_LATCH| ASP FO ADF 2 vol latch | SWITCH | Off,On|char*|
| 739|S_ASP2_ALT| ASP FO Alternate Selected | SWITCH | Off,On|char*|
| 740|S_ASP2_BOOM| ASP FO Boom Selected | SWITCH | Off,On|char*|
| 741|S_ASP2_IC| ASP FO IC Selected | SWITCH | Off,On|char*|
| 742|S_ASP2_MARKER_REC| ASP FO Marker vol | SWITCH | Off,Pushed|char*|
| 743|S_ASP2_MARKER_REC_LATCH| ASP FO Marker vol latch | SWITCH | Off,On|char*|
| 744|S_ASP2_MASK| ASP FO Mask Selected | SWITCH | Off,On|char*|
| 745|S_ASP2_NAV_1_REC| ASP FO NAV 1 vol | SWITCH | Off,Pushed|char*|
| 746|S_ASP2_NAV_1_REC_LATCH| ASP FO NAV 1 vol latch | SWITCH | Off,On|char*|
| 747|S_ASP2_NAV_2_REC| ASP FO NAV 2 vol | SWITCH | Off,Pushed|char*|
| 748|S_ASP2_NAV_2_REC_LATCH| ASP FO NAV 2 vol latch | SWITCH | Off,On|char*|
| 749|S_ASP2_NORM| ASP FO Normal Selected | SWITCH | Off,On|char*|
| 750|S_ASP2_PA_REC| ASP FO PA vol | SWITCH | Off,Pushed|char*|
| 751|S_ASP2_PA_REC_LATCH| ASP FO PA vol latch | SWITCH | Off,On|char*|
| 752|S_ASP2_RT| ASP FO RT Selected | SWITCH | Off,On|char*|
| 753|S_ASP2_SIGNAL_FILTER| ASP2 filter mode | SWITCH | B,V,R|char*|
| 754|S_ASP2_SPKR_REC| ASP FO Spkr vol | SWITCH | Off,Pushed|char*|
| 755|S_ASP2_SPKR_REC_LATCH| ASP FO Spkr vol latch | SWITCH | Off,On|char*|
| 756|S_ASP2_VHF_1_REC| ASP FO VHF 1 vol | SWITCH | Off,Pushed|char*|
| 757|S_ASP2_VHF_1_REC_LATCH| ASP FO VHF 1 vol latch | SWITCH | Off,On|char*|
| 758|S_ASP2_VHF_1_SEND| ASP FO VHF 1 mic | SWITCH | Off,Pushed|char*|
| 759|S_ASP2_VHF_1_SEND_LATCH| ASP FO VHF 1 mic latch | SWITCH | Off,On|char*|
| 760|S_ASP2_VHF_2_REC| ASP FO VHF 2 vol | SWITCH | Off,Pushed|char*|
| 761|S_ASP2_VHF_2_REC_LATCH| ASP FO VHF 2 vol latch | SWITCH | Off,On|char*|
| 762|S_ASP2_VHF_2_SEND| ASP FO VHF 2 mic | SWITCH | Off,Pushed|char*|
| 763|S_ASP2_VHF_2_SEND_LATCH| ASP FO VHF 2 mic latch | SWITCH | Off,On|char*|
| 764|S_ASP3_ADF_1_REC| ASP OBS ADF 1 vol | SWITCH | Off,Pushed|char*|
| 765|S_ASP3_ADF_1_REC_LATCH| ASP OBS ADF 1 vol latch | SWITCH | Off,On|char*|
| 766|S_ASP3_ADF_2_REC| ASP OBS ADF 2 vol | SWITCH | Off,Pushed|char*|
| 767|S_ASP3_ADF_2_REC_LATCH| ASP OBS ADF 2 vol latch | SWITCH | Off,On|char*|
| 768|S_ASP3_ALT| ASP OBS Alternate Selected | SWITCH | Off,On|char*|
| 769|S_ASP3_BOOM| ASP OBS Boom Selected | SWITCH | Off,On|char*|
| 770|S_ASP3_IC| ASP OBS IC Selected | SWITCH | Off,On|char*|
| 771|S_ASP3_MARKER_REC| ASP OBS Marker vol | SWITCH | Off,Pushed|char*|
| 772|S_ASP3_MARKER_REC_LATCH| ASP OBS Marker vol latch | SWITCH | Off,On|char*|
| 773|S_ASP3_MASK| ASP OBS Mask Selected | SWITCH | Off,On|char*|
| 774|S_ASP3_NAV_1_REC| ASP OBS NAV 1 vol | SWITCH | Off,Pushed|char*|
| 775|S_ASP3_NAV_1_REC_LATCH| ASP OBS NAV 1 vol latch | SWITCH | Off,On|char*|
| 776|S_ASP3_NAV_2_REC| ASP OBS NAV 2 vol | SWITCH | Off,Pushed|char*|
| 777|S_ASP3_NAV_2_REC_LATCH| ASP OBS NAV 2 vol latch | SWITCH | Off,On|char*|
| 778|S_ASP3_NORM| ASP OBS Normal Selected | SWITCH | Off,On|char*|
| 779|S_ASP3_PA_REC| ASP OBS PA vol | SWITCH | Off,Pushed|char*|
| 780|S_ASP3_PA_REC_LATCH| ASP OBS PA vol latch | SWITCH | Off,On|char*|
| 781|S_ASP3_RT| ASP OBS RT Selected | SWITCH | Off,On|char*|
| 782|S_ASP3_SIGNAL_FILTER| ASP3 filter mode | SWITCH | B,V,R|char*|
| 783|S_ASP3_SPKR_REC| ASP OBS Spkr vol | SWITCH | Off,Pushed|char*|
| 784|S_ASP3_SPKR_REC_LATCH| ASP OBS Spkr vol latch | SWITCH | Off,On|char*|
| 785|S_ASP3_VHF_1_REC| ASP OBS VHF 1 vol | SWITCH | Off,Pushed|char*|
| 786|S_ASP3_VHF_1_REC_LATCH| ASP OBS VHF 1 vol latch | SWITCH | Off,On|char*|
| 787|S_ASP3_VHF_1_SEND| ASP OBS VHF 1 mic | SWITCH | Off,Pushed|char*|
| 788|S_ASP3_VHF_1_SEND_LATCH| ASP OBS VHF 1 mic latch | SWITCH | Off,On|char*|
| 789|S_ASP3_VHF_2_REC| ASP OBS VHF 2 vol | SWITCH | Off,Pushed|char*|
| 790|S_ASP3_VHF_2_REC_LATCH| ASP OBS VHF 2 vol latch | SWITCH | Off,On|char*|
| 791|S_ASP3_VHF_2_SEND| ASP OBS VHF 2 mic | SWITCH | Off,Pushed|char*|
| 792|S_ASP3_VHF_2_SEND_LATCH| ASP OBS VHF 2 mic latch | SWITCH | Off,On|char*|
| 793|S_CDU1_KEY_0|  |  | ||
| 794|S_CDU1_KEY_1|  |  | ||
| 795|S_CDU1_KEY_2|  |  | ||
| 796|S_CDU1_KEY_3|  |  | ||
| 797|S_CDU1_KEY_4|  |  | ||
| 798|S_CDU1_KEY_5|  |  | ||
| 799|S_CDU1_KEY_6|  |  | ||
| 800|S_CDU1_KEY_7|  |  | ||
| 801|S_CDU1_KEY_8|  |  | ||
| 802|S_CDU1_KEY_9|  |  | ||
| 803|S_CDU1_KEY_A|  |  | ||
| 804|S_CDU1_KEY_B|  |  | ||
| 805|S_CDU1_KEY_C|  |  | ||
| 806|S_CDU1_KEY_CLB|  |  | ||
| 807|S_CDU1_KEY_CLEAR|  |  | ||
| 808|S_CDU1_KEY_CLEARLINE|  |  | ||
| 809|S_CDU1_KEY_CRZ|  |  | ||
| 810|S_CDU1_KEY_D|  |  | ||
| 811|S_CDU1_KEY_DEL|  |  | ||
| 812|S_CDU1_KEY_DEP_ARR|  |  | ||
| 813|S_CDU1_KEY_DES|  |  | ||
| 814|S_CDU1_KEY_DOT|  |  | ||
| 815|S_CDU1_KEY_E|  |  | ||
| 816|S_CDU1_KEY_EXEC|  |  | ||
| 817|S_CDU1_KEY_F|  |  | ||
| 818|S_CDU1_KEY_FIX|  |  | ||
| 819|S_CDU1_KEY_G|  |  | ||
| 820|S_CDU1_KEY_H|  |  | ||
| 821|S_CDU1_KEY_HOLD|  |  | ||
| 822|S_CDU1_KEY_I|  |  | ||
| 823|S_CDU1_KEY_INIT_REF|  |  | ||
| 824|S_CDU1_KEY_J|  |  | ||
| 825|S_CDU1_KEY_K|  |  | ||
| 826|S_CDU1_KEY_L|  |  | ||
| 827|S_CDU1_KEY_LEGS|  |  | ||
| 828|S_CDU1_KEY_LSK1L|  |  | ||
| 829|S_CDU1_KEY_LSK1R|  |  | ||
| 830|S_CDU1_KEY_LSK2L|  |  | ||
| 831|S_CDU1_KEY_LSK2R|  |  | ||
| 832|S_CDU1_KEY_LSK3L|  |  | ||
| 833|S_CDU1_KEY_LSK3R|  |  | ||
| 834|S_CDU1_KEY_LSK4L|  |  | ||
| 835|S_CDU1_KEY_LSK4R|  |  | ||
| 836|S_CDU1_KEY_LSK5L|  |  | ||
| 837|S_CDU1_KEY_LSK5R|  |  | ||
| 838|S_CDU1_KEY_LSK6L|  |  | ||
| 839|S_CDU1_KEY_LSK6R|  |  | ||
| 840|S_CDU1_KEY_M|  |  | ||
| 841|S_CDU1_KEY_MENU|  |  | ||
| 842|S_CDU1_KEY_MINUS|  |  | ||
| 843|S_CDU1_KEY_N|  |  | ||
| 844|S_CDU1_KEY_N1_LIMIT|  |  | ||
| 845|S_CDU1_KEY_NEXT_PAGE|  |  | ||
| 846|S_CDU1_KEY_O|  |  | ||
| 847|S_CDU1_KEY_P|  |  | ||
| 848|S_CDU1_KEY_PREV_PAGE|  |  | ||
| 849|S_CDU1_KEY_PROG|  |  | ||
| 850|S_CDU1_KEY_Q|  |  | ||
| 851|S_CDU1_KEY_R|  |  | ||
| 852|S_CDU1_KEY_RTE|  |  | ||
| 853|S_CDU1_KEY_S|  |  | ||
| 854|S_CDU1_KEY_SLASH|  |  | ||
| 855|S_CDU1_KEY_SPACE|  |  | ||
| 856|S_CDU1_KEY_T|  |  | ||
| 857|S_CDU1_KEY_U|  |  | ||
| 858|S_CDU1_KEY_V|  |  | ||
| 859|S_CDU1_KEY_W|  |  | ||
| 860|S_CDU1_KEY_X|  |  | ||
| 861|S_CDU1_KEY_Y|  |  | ||
| 862|S_CDU1_KEY_Z|  |  | ||
| 863|S_CDU2_KEY_0|  |  | ||
| 864|S_CDU2_KEY_1|  |  | ||
| 865|S_CDU2_KEY_2|  |  | ||
| 866|S_CDU2_KEY_3|  |  | ||
| 867|S_CDU2_KEY_4|  |  | ||
| 868|S_CDU2_KEY_5|  |  | ||
| 869|S_CDU2_KEY_6|  |  | ||
| 870|S_CDU2_KEY_7|  |  | ||
| 871|S_CDU2_KEY_8|  |  | ||
| 872|S_CDU2_KEY_9|  |  | ||
| 873|S_CDU2_KEY_A|  |  | ||
| 874|S_CDU2_KEY_B|  |  | ||
| 875|S_CDU2_KEY_C|  |  | ||
| 876|S_CDU2_KEY_CLB|  |  | ||
| 877|S_CDU2_KEY_CLEAR|  |  | ||
| 878|S_CDU2_KEY_CLEARLINE|  |  | ||
| 879|S_CDU2_KEY_CRZ|  |  | ||
| 880|S_CDU2_KEY_D|  |  | ||
| 881|S_CDU2_KEY_DEL|  |  | ||
| 882|S_CDU2_KEY_DEP_ARR|  |  | ||
| 883|S_CDU2_KEY_DES|  |  | ||
| 884|S_CDU2_KEY_DOT|  |  | ||
| 885|S_CDU2_KEY_E|  |  | ||
| 886|S_CDU2_KEY_EXEC|  |  | ||
| 887|S_CDU2_KEY_F|  |  | ||
| 888|S_CDU2_KEY_FIX|  |  | ||
| 889|S_CDU2_KEY_G|  |  | ||
| 890|S_CDU2_KEY_H|  |  | ||
| 891|S_CDU2_KEY_HOLD|  |  | ||
| 892|S_CDU2_KEY_I|  |  | ||
| 893|S_CDU2_KEY_INIT_REF|  |  | ||
| 894|S_CDU2_KEY_J|  |  | ||
| 895|S_CDU2_KEY_K|  |  | ||
| 896|S_CDU2_KEY_L|  |  | ||
| 897|S_CDU2_KEY_LEGS|  |  | ||
| 898|S_CDU2_KEY_LSK1L|  |  | ||
| 899|S_CDU2_KEY_LSK1R|  |  | ||
| 900|S_CDU2_KEY_LSK2L|  |  | ||
| 901|S_CDU2_KEY_LSK2R|  |  | ||
| 902|S_CDU2_KEY_LSK3L|  |  | ||
| 903|S_CDU2_KEY_LSK3R|  |  | ||
| 904|S_CDU2_KEY_LSK4L|  |  | ||
| 905|S_CDU2_KEY_LSK4R|  |  | ||
| 906|S_CDU2_KEY_LSK5L|  |  | ||
| 907|S_CDU2_KEY_LSK5R|  |  | ||
| 908|S_CDU2_KEY_LSK6L|  |  | ||
| 909|S_CDU2_KEY_LSK6R|  |  | ||
| 910|S_CDU2_KEY_M|  |  | ||
| 911|S_CDU2_KEY_MENU|  |  | ||
| 912|S_CDU2_KEY_MINUS|  |  | ||
| 913|S_CDU2_KEY_N|  |  | ||
| 914|S_CDU2_KEY_N1_LIMIT|  |  | ||
| 915|S_CDU2_KEY_NEXT_PAGE|  |  | ||
| 916|S_CDU2_KEY_O|  |  | ||
| 917|S_CDU2_KEY_P|  |  | ||
| 918|S_CDU2_KEY_PREV_PAGE|  |  | ||
| 919|S_CDU2_KEY_PROG|  |  | ||
| 920|S_CDU2_KEY_Q|  |  | ||
| 921|S_CDU2_KEY_R|  |  | ||
| 922|S_CDU2_KEY_RTE|  |  | ||
| 923|S_CDU2_KEY_S|  |  | ||
| 924|S_CDU2_KEY_SLASH|  |  | ||
| 925|S_CDU2_KEY_SPACE|  |  | ||
| 926|S_CDU2_KEY_T|  |  | ||
| 927|S_CDU2_KEY_U|  |  | ||
| 928|S_CDU2_KEY_V|  |  | ||
| 929|S_CDU2_KEY_W|  |  | ||
| 930|S_CDU2_KEY_X|  |  | ||
| 931|S_CDU2_KEY_Y|  |  | ||
| 932|S_CDU2_KEY_Z|  |  | ||
| 933|S_COM1_TFC| Radio TFR COM1 | SWITCH | Normal,Pushed|char*|
| 934|S_COM2_TFC| Radio TFR COM2 | SWITCH | Normal,Pushed|char*|
| 935|S_COM3_TFC| Radio TFR COM3 | SWITCH | Normal,Pushed|char*|
| 936|S_CONTROL_LOADING_POWER|  |  | ||
| 937|S_DOOR_AUTO_UNLOCK_TEST| Door auto unlock test | SWITCH | Normal,Pushed|char*|
| 938|S_DOOR_LOCK_FAIL_TEST| Door lock fail test | SWITCH | Normal,Pushed|char*|
| 939|S_ELEV_TRIM| Elevator trim CPT 1 | SWITCH | Center,Up,Down|char*|
| 940|S_ELEV_TRIM_FO| Elevator trim F/O 1 | SWITCH | Center,Up,Down|char*|
| 941|S_ELEV_TRIM_FO2| Elevator trim F/O 2 | SWITCH | Center,Up,Down|char*|
| 942|S_ELEV_TRIM2| Elevator trim CPT 2 | SWITCH | Center,Up,Down|char*|
| 943|S_FC_TOEBRAKE_LEFT_CAPT|  |  | ||
| 944|S_FC_TOEBRAKE_LEFT_FO|  |  | ||
| 945|S_FC_TOEBRAKE_RIGHT_CAPT|  |  | ||
| 946|S_FC_TOEBRAKE_RIGHT_FO|  |  | ||
| 947|S_FIRE_BELL_CUTOUT| Bell cutout | SWITCH | Off,Pushed|char*|
| 948|S_FIRE_CARGO_ARM_AFT| Cargo fire arm aft | SWITCH | Off,Pushed|char*|
| 949|S_FIRE_CARGO_ARM_AFT_LATCHED| Cargo fire arm aft latch | SWITCH | Off,On|char*|
| 950|S_FIRE_CARGO_ARM_FWD| Cargo fire arm fwd | SWITCH | Off,Pushed|char*|
| 951|S_FIRE_CARGO_ARM_FWD_LATCHED| Cargo fire arm fwd latch | SWITCH | Off,On|char*|
| 952|S_FIRE_CARGO_DET_AFT| Cargo fire aft selector | SWITCH | Norm,A,B|char*|
| 953|S_FIRE_CARGO_DET_FWD| Cargo fire fwd selector | SWITCH | Norm,A,B|char*|
| 954|S_FIRE_CARGO_DISCH| Cargo fire disch | SWITCH | Off,Pushed|char*|
| 955|S_FIRE_CARGO_EXT_AFT_PTT| Cargo fire ext aft PTT | SWITCH | Normal,Pushed|char*|
| 956|S_FIRE_CARGO_EXT_FWD_PTT| Cargo fire ext fwd PTT | SWITCH | Normal,Pushed|char*|
| 957|S_FIRE_CARGO_TEST| Cargo fire test | SWITCH | Off,Pushed|char*|
| 958|S_FIRE_CUTOUT_CP| Fire warning 1 | SWITCH | Off,Pushed|char*|
| 959|S_FIRE_CUTOUT_FO| Fire warning 2 | SWITCH | Off,Pushed|char*|
| 960|S_FIRE_EXT_TEST| Fire Ext test | SWITCH | Off,1,2|char*|
| 961|S_FIRE_FAULT_TEST| Ovht test | SWITCH | Off,Fault/Inop,Ovht/Fire|char*|
| 962|S_FIRE_HANDLE_APU| Fire handle APU | SWITCH | Off,Left,Right|char*|
| 963|S_FIRE_HANDLE1| Fire handle Engine 1 | SWITCH | Off,Left,Right|char*|
| 964|S_FIRE_HANDLE2| Fire handle Engine 2 | SWITCH | Off,Left,Right|char*|
| 965|S_FIRE_OVHT_DET1| Ovht Det left | SWITCH | Normal,A,B|char*|
| 966|S_FIRE_OVHT_DET2| Ovht Det right | SWITCH | Normal,A,B|char*|
| 967|S_FIRE_PULL_APU| Fire handle pull APU | SWITCH | Normal,Pull|char*|
| 968|S_FIRE_PULL1| Fire handle pull Engine 1 | SWITCH | Normal,Pull|char*|
| 969|S_FIRE_PULL2| Fire handle pull Engine 2 | SWITCH | Normal,Pull|char*|
| 970|S_FLIGHT_DEK_DOOR| Flt Deck door | SWITCH | AUTO,UNLKD,DENY|char*|
| 971|S_GPWS_FLAP_INHIBIT| Flap inhibit | SWITCH | Norm,Inhibit|char*|
| 972|S_GPWS_GEAR_INHIBIT| Gear inhibit | SWITCH | Norm,Inhibit|char*|
| 973|S_GPWS_RUNWAY_INHIBIT| Runway inhibit | SWITCH | Norm,Inhibit|char*|
| 974|S_GPWS_SYS_TEST| GPWS Sys test | SWITCH | Off,Pushed|char*|
| 975|S_GPWS_TERRAIN_INHIBIT| Terrain inhibit | SWITCH | Norm,Inhibit|char*|
| 976|S_MC_ACK_CP| Master caution 1 | SWITCH | Off,Pushed|char*|
| 977|S_MC_ACK_FO| Master caution 2 | SWITCH | Off,Pushed|char*|
| 978|S_MCP_ALT_HOLD| MCP Alt hold | SWITCH | Off,Pushed|char*|
| 979|S_MCP_ALT_INT| MCP Alt Int | SWITCH | Off,Pushed|char*|
| 980|S_MCP_AP_DISENGAGE| MCP AP Disengage | SWITCH | Normal,Disengage|char*|
| 981|S_MCP_APP| MCP APP | SWITCH | Off,Pushed|char*|
| 982|S_MCP_AT| MCP AT Arm | SWITCH | Off,Arm|char*|
| 983|S_MCP_BANK_LIMIT| MCP Bank limit | SWITCH | 25,30,10,15,20|char*|
| 984|S_MCP_CMD_A| MCP CMD A | SWITCH | Off,Pushed|char*|
| 985|S_MCP_CMD_B| MCP CMD B | SWITCH | Off,Pushed|char*|
| 986|S_MCP_CO| MCP C/O | SWITCH | Off,Pushed|char*|
| 987|S_MCP_CWS_A| MCP CWS A | SWITCH | Off,Pushed|char*|
| 988|S_MCP_CWS_B| MCP CWS B | SWITCH | Off,Pushed|char*|
| 989|S_MCP_EFIS1_ARPT| EFIS 1 ARPT | SWITCH | Off,Pushed|char*|
| 990|S_MCP_EFIS1_BARO| EFIS 1 baro momentary | SWITCH | Center,Up,Down,Up fast,Down fast|char*|
| 991|S_MCP_EFIS1_BARO_MODE| EFIS 1 Baro mode | SWITCH | Inch,HPa|char*|
| 992|S_MCP_EFIS1_BARO_STD| EFIS 1 Baro STD | SWITCH | Off,Pushed|char*|
| 993|S_MCP_EFIS1_CTR| EFIS 1 CTR | SWITCH | Off,Pushed|char*|
| 994|S_MCP_EFIS1_DATA| EFIS 1 DATA | SWITCH | Off,Pushed|char*|
| 995|S_MCP_EFIS1_FPV| EFIS 1 FPV | SWITCH | Off,Pushed|char*|
| 996|S_MCP_EFIS1_MINIMUMS| EFIS 1 minimums momentary | SWITCH | Center,Up,Down,Up fast,Down fast|char*|
| 997|S_MCP_EFIS1_MINIMUMS_MODE| EFIS 1 Minimums mode | SWITCH | Radio,Baro|char*|
| 998|S_MCP_EFIS1_MINIMUMS_RESET| EFIS 1 MINS Reset | SWITCH | Off,Pushed|char*|
| 999|S_MCP_EFIS1_MODE| EFIS 1 Mode | SWITCH | APP,VOR,MAP,PLN|char*|
| 1000|S_MCP_EFIS1_MTRS| EFIS 1 MTRS | SWITCH | Off,Pushed|char*|
| 1001|S_MCP_EFIS1_POS| EFIS 1 POS | SWITCH | Off,Pushed|char*|
| 1002|S_MCP_EFIS1_RANGE| EFIS 1 Range | SWITCH | 5,10,20,40,80,160,320,640|char*|
| 1003|S_MCP_EFIS1_SEL1| EFIS 1 Selector 1 | SWITCH | OFF,VOR 1,ADF 1|char*|
| 1004|S_MCP_EFIS1_SEL2| EFIS 1 Selector 2 | SWITCH | OFF,VOR 2,ADF 2|char*|
| 1005|S_MCP_EFIS1_STA| EFIS 1 STA | SWITCH | Off,Pushed|char*|
| 1006|S_MCP_EFIS1_TERR| EFIS 1 TERR | SWITCH | Off,Pushed|char*|
| 1007|S_MCP_EFIS1_TFC| EFIS 1 TFC | SWITCH | Off,Pushed|char*|
| 1008|S_MCP_EFIS1_WPT| EFIS 1 WPT | SWITCH | Off,Pushed|char*|
| 1009|S_MCP_EFIS1_WXR| EFIS 1 WXR | SWITCH | Off,Pushed|char*|
| 1010|S_MCP_EFIS2_ARPT| EFIS 2 ARPT | SWITCH | Off,Pushed|char*|
| 1011|S_MCP_EFIS2_BARO| EFIS 2 baro momentary | SWITCH | Center,Up,Down,Up fast,Down fast|char*|
| 1012|S_MCP_EFIS2_BARO_MODE| EFIS 2 Baro mode | SWITCH | Inch,HPa|char*|
| 1013|S_MCP_EFIS2_BARO_STD| EFIS 2 Baro STD | SWITCH | Off,Pushed|char*|
| 1014|S_MCP_EFIS2_CTR| EFIS 2 CTR | SWITCH | Off,Pushed|char*|
| 1015|S_MCP_EFIS2_DATA| EFIS 2 DATA | SWITCH | Off,Pushed|char*|
| 1016|S_MCP_EFIS2_FPV| EFIS 2 FPV | SWITCH | Off,Pushed|char*|
| 1017|S_MCP_EFIS2_MINIMUMS| EFIS 2 minimums momentary | SWITCH | Center,Up,Down,Up fast,Down fast|char*|
| 1018|S_MCP_EFIS2_MINIMUMS_MODE| EFIS 2 Minimums mode | SWITCH | Radio,Baro|char*|
| 1019|S_MCP_EFIS2_MINIMUMS_RESET| EFIS 2 MINS Reset | SWITCH | Off,Pushed|char*|
| 1020|S_MCP_EFIS2_MODE| EFIS 2 Mode | SWITCH | APP,VOR,MAP,PLN|char*|
| 1021|S_MCP_EFIS2_MTRS| EFIS 2 MTRS | SWITCH | Off,Pushed|char*|
| 1022|S_MCP_EFIS2_POS| EFIS 2 POS | SWITCH | Off,Pushed|char*|
| 1023|S_MCP_EFIS2_RANGE| EFIS 2 Range | SWITCH | 5,10,20,40,80,160,320,640|char*|
| 1024|S_MCP_EFIS2_SEL1| EFIS 2 Selector 1 | SWITCH | OFF,VOR 1,ADF 1|char*|
| 1025|S_MCP_EFIS2_SEL2| EFIS 2 Selector 2 | SWITCH | OFF,VOR 2,ADF 2|char*|
| 1026|S_MCP_EFIS2_STA| EFIS 2 STA | SWITCH | Off,Pushed|char*|
| 1027|S_MCP_EFIS2_TERR| EFIS 2 TERR | SWITCH | Off,Pushed|char*|
| 1028|S_MCP_EFIS2_TFC| EFIS 2 TFC | SWITCH | Off,Pushed|char*|
| 1029|S_MCP_EFIS2_WPT| EFIS 2 WPT | SWITCH | Off,Pushed|char*|
| 1030|S_MCP_EFIS2_WXR| EFIS 2 WXR | SWITCH | Off,Pushed|char*|
| 1031|S_MCP_FD1| MCP Captain F/D | SWITCH | Off,On|char*|
| 1032|S_MCP_FD2| MCP F/O F/D | SWITCH | Off,On|char*|
| 1033|S_MCP_HDG_SEL| MCP Heading sel | SWITCH | Off,Pushed|char*|
| 1034|S_MCP_HEADING|  |  | ||
| 1035|S_MCP_LEVEL_CHANGE| MCP Level change | SWITCH | Off,Pushed|char*|
| 1036|S_MCP_LNAV| MCP LNAV | SWITCH | Off,Pushed|char*|
| 1037|S_MCP_N1| MCP N1 | SWITCH | Off,Pushed|char*|
| 1038|S_MCP_SPEED| MCP Speed hold | SWITCH | Off,Pushed|char*|
| 1039|S_MCP_SPEED_INT| MCP Speed Int | SWITCH | Off,Pushed|char*|
| 1040|S_MCP_VNAV| MCP VNAV | SWITCH | Off,Pushed|char*|
| 1041|S_MCP_VORLOC| MCP VOR/LOC | SWITCH | Off,Pushed|char*|
| 1042|S_MCP_VS| MCP V/S | SWITCH | Off,Pushed|char*|
| 1043|S_MFD_ENG| MFD ENG | SWITCH | Normal,Pushed|char*|
| 1044|S_MFD_SYS| MFD SYS | SWITCH | Normal,Pushed|char*|
| 1045|S_MIP_AUTOBRAKE| Autobrake | SWITCH | Off,RTO,1,2,3,Max|char*|
| 1046|S_MIP_CHRONO_CAPT_ALTERNATE| Chrono capt alternate control | SWITCH | Run,Hold,Reset|char*|
| 1047|S_MIP_CHRONO_CAPT_CHR| Chrono capt CHR | SWITCH | Normal,Pushed|char*|
| 1048|S_MIP_CHRONO_CAPT_DATE_TIME| Chrono capt Date/Time | SWITCH | Normal,Pushed|char*|
| 1049|S_MIP_CHRONO_CAPT_ET| Chrono capt ET | SWITCH | Normal,Pushed|char*|
| 1050|S_MIP_CHRONO_CAPT_MINUS| Chrono capt - | SWITCH | Normal,Pushed|char*|
| 1051|S_MIP_CHRONO_CAPT_PLUS| Chrono capt + | SWITCH | Normal,Pushed|char*|
| 1052|S_MIP_CHRONO_CAPT_RESET| Chrono capt RESET | SWITCH | Normal,Pushed|char*|
| 1053|S_MIP_CHRONO_CAPT_SET| Chrono capt SET | SWITCH | Normal,Pushed|char*|
| 1054|S_MIP_CHRONO_FO_ALTERNATE| Chrono f/o alternate control | SWITCH | Run,Hold,Reset|char*|
| 1055|S_MIP_CHRONO_FO_CHR| Chrono f/o CHR | SWITCH | Normal,Pushed|char*|
| 1056|S_MIP_CHRONO_FO_DATE_TIME| Chrono f/o Date/Time | SWITCH | Normal,Pushed|char*|
| 1057|S_MIP_CHRONO_FO_ET| Chrono f/o ET | SWITCH | Normal,Pushed|char*|
| 1058|S_MIP_CHRONO_FO_MINUS| Chrono f/o - | SWITCH | Normal,Pushed|char*|
| 1059|S_MIP_CHRONO_FO_PLUS| Chrono f/o + | SWITCH | Normal,Pushed|char*|
| 1060|S_MIP_CHRONO_FO_RESET| Chrono f/o RESET | SWITCH | Normal,Pushed|char*|
| 1061|S_MIP_CHRONO_FO_SET| Chrono f/o SET | SWITCH | Normal,Pushed|char*|
| 1062|S_MIP_CLOCK_CAPT| Clock Captain | SWITCH | Normal,Pushed|char*|
| 1063|S_MIP_CLOCK_FO| Clock F/O | SWITCH | Normal,Pushed|char*|
| 1064|S_MIP_FUELFLOW| Fuel flow | SWITCH | Rate,Used,Reset|char*|
| 1065|S_MIP_GEAR| Gear | SWITCH | Off,Down,Up|char*|
| 1066|S_MIP_GEAR_OVERRIDE| Gear handle lock override | SWITCH | Normal,Override|char*|
| 1067|S_MIP_GS_PUSH_INHIBIT| Glideslope push to inhibit | SWITCH | Normal,Pushed|char*|
| 1068|S_MIP_GS_PUSH_INHIBIT_FO| Glideslope push to inhibit F/O | SWITCH | Normal,Pushed|char*|
| 1069|S_MIP_ISFD_APP| ISFD APP | SWITCH | Off,Pushed|char*|
| 1070|S_MIP_ISFD_BARO_STD| ISFD baro STD | SWITCH | Off,Pushed|char*|
| 1071|S_MIP_ISFD_HP_INCH| ISFD HP/IN | SWITCH | Off,Pushed|char*|
| 1072|S_MIP_ISFD_MINUS| ISFD - | SWITCH | Off,Pushed|char*|
| 1073|S_MIP_ISFD_PLUS| ISFD + | SWITCH | Off,Pushed|char*|
| 1074|S_MIP_ISFD_RST| ISFD RST | SWITCH | Off,Pushed|char*|
| 1075|S_MIP_LIGHTTEST| Light Test | SWITCH | Bright,Dim,Test|char*|
| 1076|S_MIP_LOWER_DU_CAPT| Lower DU Capt | SWITCH | Norm,ND,Eng Pri|char*|
| 1077|S_MIP_LOWER_DU_FO| Lower DU FO | SWITCH | Norm,ND,Eng Pri|char*|
| 1078|S_MIP_MAIN_DU_CAPT| Main Panel DUs Capt | SWITCH | Norm,Outbd PFD,Eng Pri,PFD,MFD|char*|
| 1079|S_MIP_MAIN_DU_FO| Main Panel DUs FO | SWITCH | Norm,Outbd PFD,Eng Pri,PFD,MFD|char*|
| 1080|S_MIP_N1_SET| N1 SET | SWITCH | AUTO,1,2,Both|char*|
| 1081|S_MIP_N1_SET_VALUE| N1 SET Rotary momentary | SWITCH | Center,Up,Down,Up fast,Down fast|char*|
| 1082|S_MIP_NOSEWHEEL_STEERING| Nose wheel steering | SWITCH | Normal,Alternate|char*|
| 1083|S_MIP_PARKING_BRAKE| Parking brake | SWITCH | Off,On|char*|
| 1084|S_MIP_RMI_CAPT_NAV1| Standby RMI NAV1 mode | SWITCH | VOR,ADF|char*|
| 1085|S_MIP_RMI_CAPT_NAV2| Standby RMI NAV2 mode | SWITCH | VOR,ADF|char*|
| 1086|S_MIP_RMI_FO_NAV1| Standby RMI NAV1 mode F/O | SWITCH | VOR,ADF|char*|
| 1087|S_MIP_RMI_FO_NAV2| Standby RMI NAV2 mode F/O | SWITCH | VOR,ADF|char*|
| 1088|S_MIP_SPD_REF_VALUE| SPD REF Rotary momentary | SWITCH | Center,Up,Down,Up fast,Down fast|char*|
| 1089|S_MIP_SPDREF| SPD REF | SWITCH | AUTO,V1,VR,WT,VREF,BUG,SET|char*|
| 1090|S_MIP_STANDBY_ATTITUDE_MODE| Standby Attitude Mode | SWITCH | APP,OFF,BCRS|char*|
| 1091|S_NAV1_TFC| Radio TFR NAV1 | SWITCH | Normal,Pushed|char*|
| 1092|S_NAV2_TFC| Radio TFR NAV2 | SWITCH | Normal,Pushed|char*|
| 1093|S_OH_AIR_TEMP_SELECTOR| Air Temp Selector | SWITCH | CONT CAB,DUCT FWD,DUCT AFT,CAB FWD,CAB AFT,R,L|char*|
| 1094|S_OH_ALT_FLAP_CTRL| Alternate flaps ctrl | SWITCH | Off,Up,Down|char*|
| 1095|S_OH_ALT_FLAPS| Alternate flaps | SWITCH | Off,Arm|char*|
| 1096|S_OH_ALT_HORN_CUTOUT| Alt horn cutout | SWITCH | Off,Pushed|char*|
| 1097|S_OH_APU| APU switch | SWITCH | Off,On,Start|char*|
| 1098|S_OH_ATTEND| Attend | SWITCH | Off,Pushed|char*|
| 1099|S_OH_BATTERY| Battery switch | SWITCH | Off,On|char*|
| 1100|S_OH_BLEED_APU| Bleed APU | SWITCH | Off,On|char*|
| 1101|S_OH_BLEED_L| Bleed 1 | SWITCH | Off,On|char*|
| 1102|S_OH_BLEED_OVT_TEST| OVHT test | SWITCH | Off,On|char*|
| 1103|S_OH_BLEED_R| Bleed 2 | SWITCH | Off,On|char*|
| 1104|S_OH_BUS_TRANSFER| Bus transfer switch | SWITCH | Off,Auto|char*|
| 1105|S_OH_CROSSFEED| Crossfeed | SWITCH | Off,On|char*|
| 1106|S_OH_DISCONNECT1| Disconnect 1 | SWITCH | Normal,Off|char*|
| 1107|S_OH_DISCONNECT2| Disconnect 2 | SWITCH | Normal,Off|char*|
| 1108|S_OH_DISP_PAN| Display Control Panel | SWITCH | Normal,Both on 1,Both on 2|char*|
| 1109|S_OH_DISPLAY_SOURCE| Display source | SWITCH | Auto,All on 1,All on 2|char*|
| 1110|S_OH_EEC1| EEC left | SWITCH | Off,Pushed|char*|
| 1111|S_OH_EEC1_LATCH| EEC left latch | SWITCH | Off,On|char*|
| 1112|S_OH_EEC2| EEC right | SWITCH | Off,Pushed|char*|
| 1113|S_OH_EEC2_LATCH| EEC right latch | SWITCH | Off,On|char*|
| 1114|S_OH_ELEC_AC| Elec Pnl AC | SWITCH | STBY PWR,GRD PWR,GEN1,APU GEN,GEN2,INV,TEST|char*|
| 1115|S_OH_ELEC_DC| Elec Pnl DC | SWITCH | STBY PWR,BAT BUS,BAT,AUX BAT,TR1,TR2,TR3,TEST|char*|
| 1116|S_OH_ELEC_HYD_PUMP_1| Hyd ELEC1 | SWITCH | Off,On|char*|
| 1117|S_OH_ELEC_HYD_PUMP_2| Hyd ELEC2 | SWITCH | Off,On|char*|
| 1118|S_OH_ELEC_MAINT| Elec maint | SWITCH | Off,Pushed|char*|
| 1119|S_OH_ELT| ELT | SWITCH | Armed,On|char*|
| 1120|S_OH_EMERG_EXIT_LIGHTS| Emer Exit Lights | SWITCH | Off,Armed,On|char*|
| 1121|S_OH_ENG_HYD_PUMP_L| Hyd ENG1 | SWITCH | Off,On|char*|
| 1122|S_OH_ENG_HYD_PUMP_R| Hyd ENG2 | SWITCH | Off,On|char*|
| 1123|S_OH_ENG_START_L| Start 1 | SWITCH | Off,GRD,CONT,FLT|char*|
| 1124|S_OH_ENG_START_R| Start 2 | SWITCH | Off,GRD,CONT,FLT|char*|
| 1125|S_OH_ENGINE_AI1| Eng Anti-Ice 1 | SWITCH | Off,On|char*|
| 1126|S_OH_ENGINE_AI2| Eng Anti-Ice 2 | SWITCH | Off,On|char*|
| 1127|S_OH_EQUIP_COOLING_EXHAUST| Equip cooling exhaust | SWITCH | Normal,Alternate|char*|
| 1128|S_OH_EQUIP_COOLING_SUPPLY| Equip cooling supply | SWITCH | Normal,Alternate|char*|
| 1129|S_OH_FLIGHT_REC| Flight recorder | SWITCH | Normal,Test|char*|
| 1130|S_OH_FLT_CTRL_A| Flt Ctrl A | SWITCH | Off,Stby Rud,A On|char*|
| 1131|S_OH_FLT_CTRL_B| Flt Ctrl B | SWITCH | Off,Stby Rud,B On|char*|
| 1132|S_OH_FMC| FMC | SWITCH | Normal,Both on L,Both on R|char*|
| 1133|S_OH_FUEL_PUMP_CL| Fuel Center Left | SWITCH | Off,On|char*|
| 1134|S_OH_FUEL_PUMP_CR| Fuel Center Right | SWITCH | Off,On|char*|
| 1135|S_OH_FUEL_PUMP_LA| Fuel Left Aft | SWITCH | Off,On|char*|
| 1136|S_OH_FUEL_PUMP_LF| Fuel Left Fwd | SWITCH | Off,On|char*|
| 1137|S_OH_FUEL_PUMP_RA| Fuel Right Aft | SWITCH | Off,On|char*|
| 1138|S_OH_FUEL_PUMP_RF| Fuel Right Fwd | SWITCH | Off,On|char*|
| 1139|S_OH_GALLEY| Galley | SWITCH | Off,On|char*|
| 1140|S_OH_GROUND_CALL| Ground call | SWITCH | Off,On|char*|
| 1141|S_OH_GROUND_POWER| Ground Power | SWITCH | Off,Center,On|char*|
| 1142|S_OH_IGNITION_SELECT| Ignition select | SWITCH | Both,Left,Right|char*|
| 1143|S_OH_IRS_DISP_SEL| IRS Disp Sel | SWITCH | TK/GS,Test,PPOS,Wind,HDG/STS|char*|
| 1144|S_OH_IRS_KEY_0| IRS Keypad 0 | SWITCH | Off,Pushed|char*|
| 1145|S_OH_IRS_KEY_1| IRS Keypad 1 | SWITCH | Off,Pushed|char*|
| 1146|S_OH_IRS_KEY_2| IRS Keypad 2 | SWITCH | Off,Pushed|char*|
| 1147|S_OH_IRS_KEY_3| IRS Keypad 3 | SWITCH | Off,Pushed|char*|
| 1148|S_OH_IRS_KEY_4| IRS Keypad 4 | SWITCH | Off,Pushed|char*|
| 1149|S_OH_IRS_KEY_5| IRS Keypad 5 | SWITCH | Off,Pushed|char*|
| 1150|S_OH_IRS_KEY_6| IRS Keypad 6 | SWITCH | Off,Pushed|char*|
| 1151|S_OH_IRS_KEY_7| IRS Keypad 7 | SWITCH | Off,Pushed|char*|
| 1152|S_OH_IRS_KEY_8| IRS Keypad 8 | SWITCH | Off,Pushed|char*|
| 1153|S_OH_IRS_KEY_9| IRS Keypad 9 | SWITCH | Off,Pushed|char*|
| 1154|S_OH_IRS_KEY_CLR| IRS Keypad CLR | SWITCH | Off,Pushed|char*|
| 1155|S_OH_IRS_KEY_ENT| IRS Keypad ENT | SWITCH | Off,Pushed|char*|
| 1156|S_OH_IRS_SEL| IRS | SWITCH | Normal,Both on L,Both on R|char*|
| 1157|S_OH_IRS_SEL_L| IRS left | SWITCH | Nav,Off,Align,Att|char*|
| 1158|S_OH_IRS_SEL_R| IRS right | SWITCH | Nav,Off,Align,Att|char*|
| 1159|S_OH_IRS_SYS_DISP| IRS SYS DSPL | SWITCH | Left,Right|char*|
| 1160|S_OH_LEDEVICES_TEST| LE Devices test | SWITCH | Off,Pushed|char*|
| 1161|S_OH_LIGHT_ANTI_COLLISION| Lights Anti collision | SWITCH | Off,On|char*|
| 1162|S_OH_LIGHT_DOME| Dome light | SWITCH | Dim,Off,Bright|char*|
| 1163|S_OH_LIGHT_LOGO| Lights Logo | SWITCH | Off,On|char*|
| 1164|S_OH_LIGHT_MAIN_FIXED1| Light Main Fixed L | SWITCH | Off,On|char*|
| 1165|S_OH_LIGHT_MAIN_FIXED2| Light Main Fixed R | SWITCH | Off,On|char*|
| 1166|S_OH_LIGHT_MAIN_RET1| Light Main Retract L | SWITCH | Off,On|char*|
| 1167|S_OH_LIGHT_MAIN_RET2| Light Main Retract R | SWITCH | Off,On|char*|
| 1168|S_OH_LIGHT_POSITION| Lights Position | SWITCH | Off,On|char*|
| 1169|S_OH_LIGHT_RWY1| Lights Runway turnoff L | SWITCH | Off,On|char*|
| 1170|S_OH_LIGHT_RWY2| Lights Runway turnoff R | SWITCH | Off,On|char*|
| 1171|S_OH_LIGHT_STROBE| Lights Strobe | SWITCH | Off,On|char*|
| 1172|S_OH_LIGHT_STROBE_STEADY| Lights Strobe && Steady | SWITCH | Strobe && Steady,Off,Steady|char*|
| 1173|S_OH_LIGHT_TAXI| Lights Taxi | SWITCH | Off,On|char*|
| 1174|S_OH_LIGHT_WHEEL_WELL| Lights Wheel well | SWITCH | Off,On|char*|
| 1175|S_OH_LIGHT_WING| Lights Wing | SWITCH | Off,On|char*|
| 1176|S_OH_MACH_WARNING_TEST_1| Mach Airspeed warning test no1 | SWITCH | Off,Pushed|char*|
| 1177|S_OH_MACH_WARNING_TEST_2| Mach Airspeed warning test no2 | SWITCH | Off,Pushed|char*|
| 1178|S_OH_NO_SMOKING| No Smoking | SWITCH | Off,Auto,On|char*|
| 1179|S_OH_OUTFLOW_VALVE| Outflow valve | SWITCH | Off,Open,Close|char*|
| 1180|S_OH_PACK_L| Pack 1 | SWITCH | Off,Auto,High|char*|
| 1181|S_OH_PACK_R| Pack 2 | SWITCH | Off,Auto,High|char*|
| 1182|S_OH_PASS_OXY| Pass oxygen | SWITCH | Normal,On|char*|
| 1183|S_OH_PNEUMATIC_ISOLATION| Pneumatic Isolation switch | SWITCH | Auto,Close,Open|char*|
| 1184|S_OH_PRESS_MODE| Pressurization | SWITCH | Auto,Altn,Man|char*|
| 1185|S_OH_PROBE_HEAT_A| Probe heat A | SWITCH | Off,On|char*|
| 1186|S_OH_PROBE_HEAT_B| Probe heat B | SWITCH | Off,On|char*|
| 1187|S_OH_RECIRC_L| Recirc Fan L | SWITCH | Off,Auto|char*|
| 1188|S_OH_RECIRC_R| Recirc Fan R | SWITCH | Off,Auto|char*|
| 1189|S_OH_SEATBELT| Seatbelt | SWITCH | Off,Auto,On|char*|
| 1190|S_OH_SOURCE_APU1| APU GEN 1 | SWITCH | Center,Off,On|char*|
| 1191|S_OH_SOURCE_APU2| APU GEN 2 | SWITCH | Center,Off,On|char*|
| 1192|S_OH_SOURCE_GEN1| GEN 1 | SWITCH | Center,Off,On|char*|
| 1193|S_OH_SOURCE_GEN2| GEN 2 | SWITCH | Center,Off,On|char*|
| 1194|S_OH_SPOILER_A| Spoiler A | SWITCH | Off,On|char*|
| 1195|S_OH_SPOILER_B| Spoiler B | SWITCH | Off,On|char*|
| 1196|S_OH_STALL_TEST_1| Stall test 1 | SWITCH | Off,Pushed|char*|
| 1197|S_OH_STALL_TEST_2| Stall test 2 | SWITCH | Off,Pushed|char*|
| 1198|S_OH_STANDBY_POWER| Standby power switch | SWITCH | Auto,Off,Bat|char*|
| 1199|S_OH_TAT_TEST| TAT test | SWITCH | Off,Pushed|char*|
| 1200|S_OH_TRIMAIR| Trim air | SWITCH | Off,On|char*|
| 1201|S_OH_TRIP_RESET| Trip reset | SWITCH | Off,On|char*|
| 1202|S_OH_VHF_NAV| VHF NAV | SWITCH | Normal,Both on 1,Both on 2|char*|
| 1203|S_OH_VOICE_RECORDER_TEST| Voice recorder test | SWITCH | Off,Pushed|char*|
| 1204|S_OH_WAI| Wing Anti-Ice | SWITCH | Off,On|char*|
| 1205|S_OH_WINDOW_HEAT_FL| Window heat FWD L | SWITCH | Off,On|char*|
| 1206|S_OH_WINDOW_HEAT_FR| Window heat FWD R | SWITCH | Off,On|char*|
| 1207|S_OH_WINDOW_HEAT_SL| Window heat Side L | SWITCH | Off,On|char*|
| 1208|S_OH_WINDOW_HEAT_SR| Window heat Side R | SWITCH | Off,On|char*|
| 1209|S_OH_WINDOW_HEAT_TEST| Window heat test | SWITCH | Center,OVHT,PWR TEST|char*|
| 1210|S_OH_WIPER_L| Wiper left | SWITCH | Park,Int,Low,High|char*|
| 1211|S_OH_WIPER_R| Wiper right | SWITCH | Park,Int,Low,High|char*|
| 1212|S_OH_YAW_DAMPER| Yaw damper | SWITCH | Off,On|char*|
| 1213|S_PEDESTAL_STAB_TRIM_OVERRIDE| Stab trim override | SWITCH | Normal,Override|char*|
| 1214|S_RADIO_ADF1_MODE| ADF1 mode switch | SWITCH | Off,Antenna,ADF|char*|
| 1215|S_RADIO_ADF2_MODE| ADF2 mode switch | SWITCH | Off,Antenna,ADF|char*|
| 1216|S_RADIO_XPDR_SELECTOR_1| Radio XPDR selector 1 | SWITCH | Off,0,1,2,3,4,5,6,7|char*|
| 1217|S_RADIO_XPDR_SELECTOR_2| Radio XPDR selector 2 | SWITCH | Off,0,1,2,3,4,5,6,7|char*|
| 1218|S_RADIO_XPDR_SELECTOR_3| Radio XPDR selector 3 | SWITCH | Off,0,1,2,3,4,5,6,7|char*|
| 1219|S_RADIO_XPDR_SELECTOR_4| Radio XPDR selector 4 | SWITCH | Off,0,1,2,3,4,5,6,7|char*|
| 1220|S_RECALL_CP| Recall 1 | SWITCH | Off,Pushed|char*|
| 1221|S_RECALL_FO| Recall 2 | SWITCH | Off,Pushed|char*|
| 1222|S_RMP1_ADF| RMP Capt ADF | SWITCH | Normal,Pushed|char*|
| 1223|S_RMP1_AM| RMP Capt AM | SWITCH | Normal,Pushed|char*|
| 1224|S_RMP1_HF1| RMP Capt HF1 | SWITCH | Normal,Pushed|char*|
| 1225|S_RMP1_HF2| RMP Capt HF2 | SWITCH | Normal,Pushed|char*|
| 1226|S_RMP1_NAV_1| RMP Capt NAV1 | SWITCH | Normal,Pushed|char*|
| 1227|S_RMP1_NAV_2| RMP Capt NAV2 | SWITCH | Normal,Pushed|char*|
| 1228|S_RMP1_PANEL_OFF| RMP Capt panel off | SWITCH | Normal,Pushed|char*|
| 1229|S_RMP1_VHF1| RMP Capt VHF1 | SWITCH | Normal,Pushed|char*|
| 1230|S_RMP1_VHF2| RMP Capt VHF2 | SWITCH | Normal,Pushed|char*|
| 1231|S_RMP1_VHF3| RMP Capt VHF3 | SWITCH | Normal,Pushed|char*|
| 1232|S_RMP1_XFER| RMP Capt transfer | SWITCH | Normal,Pushed|char*|
| 1233|S_RMP2_ADF| RMP F/O ADF | SWITCH | Normal,Pushed|char*|
| 1234|S_RMP2_AM| RMP F/O AM | SWITCH | Normal,Pushed|char*|
| 1235|S_RMP2_HF1| RMP F/O HF1 | SWITCH | Normal,Pushed|char*|
| 1236|S_RMP2_HF2| RMP F/O HF2 | SWITCH | Normal,Pushed|char*|
| 1237|S_RMP2_NAV_1| RMP F/O NAV1 | SWITCH | Normal,Pushed|char*|
| 1238|S_RMP2_NAV_2| RMP F/O NAV2 | SWITCH | Normal,Pushed|char*|
| 1239|S_RMP2_PANEL_OFF| RMP F/O panel off | SWITCH | Normal,Pushed|char*|
| 1240|S_RMP2_VHF1| RMP F/O VHF1 | SWITCH | Normal,Pushed|char*|
| 1241|S_RMP2_VHF2| RMP F/O VHF2 | SWITCH | Normal,Pushed|char*|
| 1242|S_RMP2_VHF3| RMP F/O VHF3 | SWITCH | Normal,Pushed|char*|
| 1243|S_RMP2_XFER| RMP F/O transfer | SWITCH | Normal,Pushed|char*|
| 1244|S_RUDDER_TRIM| Rudder trim | SWITCH | Center,Left,Right|char*|
| 1245|S_TCAS_HOR_RANGE| TCAS horizontal range | SWITCH | Max,5,10,20|char*|
| 1246|S_TCAS_VERT_RANGE| TCAS vertical range | SWITCH | Normal,Above,Below|char*|
| 1247|S_THROTTLE_AT_DISENGAGE| AT Disengage | SWITCH | Off,Pushed|char*|
| 1248|S_THROTTLE_AT_DISENGAGE_2| AT Disengage 2nd switch | SWITCH | Off,Pushed|char*|
| 1249|S_THROTTLE_FLAP| Flap | SWITCH | Up,1,2,5,10,15,25,30,40|char*|
| 1250|S_THROTTLE_FUEL_CUTOFF1| Fuel cutoff left | SWITCH | Idle,Cutoff|char*|
| 1251|S_THROTTLE_FUEL_CUTOFF2| Fuel cutoff right | SWITCH | Idle,Cutoff|char*|
| 1252|S_THROTTLE_GEAR_WARNING_CUTOUT| Gear horn cutout | SWITCH | Off,Pushed|char*|
| 1253|S_THROTTLE_STAB_TRIM_AP| Stab trim main auto pilot | SWITCH | Normal,Cutout|char*|
| 1254|S_THROTTLE_STAB_TRIM_ELEC| Stab trim main elec | SWITCH | Normal,Cutout|char*|
| 1255|S_THROTTLE_TOGA| TOGA | SWITCH | Off,Pushed|char*|
| 1256|S_THROTTLE_TOGA_2| TOGA 2nd switch | SWITCH | Off,Pushed|char*|
| 1257|S_WR_MODE| Weather Radar Mode | SWITCH | WX+T,WX,WXR(VAR),MAP,TEST|char*|
| 1258|S_XPDR_IDENT| XPDR Ident | SWITCH | Normal,Pushed|char*|
| 1259|S_XPDR_MODE| TCAS | SWITCH | Stdby,Alt rptg off,XPDR,TA,TA/RA,Test|char*|
| 1260|S_XPDR_OPERATION| XPDR operation | SWITCH | Auto,Standby,On|char*|
| 1261|S_XPDR_TEST| TCAS TEST | SWITCH | Normal,Pushed|char*|
| 1262|S_YOKE_AP_DISCONNECT_CAPT| AP Disconnect Yoke Capt | SWITCH | Normal,Pushed|char*|
| 1263|S_YOKE_AP_DISCONNECT_FO| AP Disconnect Yoke F/O | SWITCH | Normal,Pushed|char*|
| 1264|V_MCP_ALT| MCP ALT VAL | ANALOG | |char|
| 1265|V_MCP_COURSE1| MCP COURSE 1 VAL | ANALOG | |char|
| 1266|V_MCP_COURSE2| MCP COURSE 2 VAL | ANALOG | |char|
| 1267|V_MCP_HEADING| MCP HEADING VAL | ANALOG | |char|
| 1268|V_MCP_SPEED| MCP SPEED VAL | ANALOG | |char|
| 1269|V_MCP_VS| MCP V/S VAL | ANALOG | |char|
| 1270|V_OH_AFTCAB| AFT CAB selector | ANALOG | |char|
| 1271|V_OH_CONTCAB| CONT CAB selector | ANALOG | |char|
| 1272|V_OH_FLTALT| Flight alt in | ANALOG | |char|
| 1273|V_OH_FWDCAB| FWD CAB selector | ANALOG | |char|
| 1274|V_OH_LANDALT| Land alt in | ANALOG | |char|

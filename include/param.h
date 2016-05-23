#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "mavlink.h"

#define PARAMS_NAME_LENGTH MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN

typedef enum {

  /*****************************/
  /*** MAVLINK CONFIGURATION ***/
  /*****************************/

  PARAM_SYSTEM_ID,
  PARAM_STREAM_HEARTBEAT_RATE,
  PARAM_STREAM_IMU_RATE,
  PARAM_STREAM_MAG_RATE,
  PARAM_STREAM_AIRSPEED_RATE,
  PARAM_STREAM_GPS_RATE,
  PARAM_STREAM_SONAR_RATE,

  /****************************/
  /*** SYSTEM CONFIGURATION ***/
  /****************************/

  PARAM_LOOPTIME,

  /*****************/
  /*** PID GAINS ***/
  /*****************/

  PARAM_PID_ROLL_RATE_P,
  PARAM_PID_ROLL_RATE_I,
  PARAM_PID_ROLL_RATE_D,

  PARAM_PID_PITCH_RATE_P,
  PARAM_PID_PITCH_RATE_I,
  PARAM_PID_PITCH_RATE_D,

  PARAM_PID_YAW_RATE_P,
  PARAM_PID_YAW_RATE_I,
  PARAM_PID_YAW_RATE_D,

  PARAM_PID_ROLL_ANGLE_P,
  PARAM_PID_ROLL_ANGLE_I,
  PARAM_PID_ROLL_ANGLE_D,

  PARAM_PID_PITCH_ANGLE_P,
  PARAM_PID_PITCH_ANGLE_I,
  PARAM_PID_PITCH_ANGLE_D,

  PARAM_PID_ALT_P,
  PARAM_PID_ALT_I,
  PARAM_PID_ALT_D,

  /*************************/
  /*** PWM CONFIGURATION ***/
  /*************************/

  PARAM_MOTOR_PWM_SEND_RATE,

  PARAM_RC_ROLL_CHANNEL,
  PARAM_RC_PITCH_CHANNEL,
  PARAM_RC_YAW_CHANNEL,
  PARAM_RC_THROTTLE_CHANNEL,
  PARAM_RC_TYPE, // 0 is PWM, 1 is PPM
  PARAM_IDLE_PWM,

  /*******************************/
  /*** ESTIMATOR CONFIGURATION ***/
  /*******************************/

  PARAM_ESTIMATOR_LPF_ALPHA,
  PARAM_GYRO_LPF_ALPHA,
  PARAM_ACC_LPF_ALPHA,

  // keep track of size of params array
  PARAMS_COUNT
} paramId_t;

// type definitions
typedef struct
{
  uint8_t version;
  uint16_t size;
  uint8_t magic_be;                       // magic number, should be 0xBE

  int32_t values[PARAMS_COUNT];
  char names[PARAMS_COUNT][PARAMS_NAME_LENGTH];

  uint8_t magic_ef;                       // magic number, should be 0xEF
  uint8_t chk;                            // XOR checksum
} params_t;

// global variable declarations
extern params_t _params;

// function declarations

/**
 * @brief Initialize parameter values
 */
void init_params(void);

/**
 * @brief Callback for executing actions that need to be taken when a parameter value changes
 * @param id The ID of the parameter that was changed
 */
void param_change_callback(paramId_t id);

/**
 * @brief Gets the id of a parameter from its name
 * @param name The name of the parameter
 * @returns The ID of the parameter if the name is valid, PARAMS_COUNT otherwise (invalid ID)
 */
paramId_t lookup_param_id(const char name[PARAMS_NAME_LENGTH]);

/**
 * @brief Sets the value of a parameter by ID and calls the parameter change callback
 * @param id The ID of the parameter
 * @param value The new value
 * @returns True if a parameter value was changed, false otherwise
 */
inline bool set_param_by_id(paramId_t id, int32_t value)
{
  if (id < PARAMS_COUNT && value != _params.values[id])
  {
    _params.values[id] = value;
    param_change_callback(id);
    return true;
  }
  return false;
}

/**
 * @brief Sets the value of a parameter by name and calls the parameter change callback
 * @param name The name of the parameter
 * @param value The new value
 * @returns True if a parameter value was changed, false otherwise
 */
inline bool set_param_by_name(const char name[PARAMS_NAME_LENGTH], int32_t value)
{
  uint8_t id = lookup_param_id(name);
  return set_param_by_id(id, value);
}
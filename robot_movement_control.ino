#include <Ultrasonic.h>

/*
Line Follower Robot Program - CIn UFPE | September 2022
*/

#define LEFT_ENGINE_M1A_PIN 6
#define LEFT_ENGINE_M1B_PIN 7
#define LEFT_ENGINE_M1C_PIN 9

#define RIGHT_ENGINE_M2A_PIN 4
#define RIGHT_ENGINE_M2B_PIN 5
#define RIGHT_ENGINE_M2C_PIN 3

#define ULTRASOUND_SENSOR_DIST_ECHO 10
#define ULTRASOUND_SENSOR_DIST_TRIG 8

Ultrasonic ultrasonic(ULTRASOUND_SENSOR_DIST_TRIG, ULTRASOUND_SENSOR_DIST_ECHO);

#define PRINCIPAL_ENGINE_POTENCIAL 60
#define SECUNDARY_ENGINE_POTENCIAL 6
#define ENGINE_POTENCIAL_WALKING_TO_FRONT_MOVEMENT 50

#define LINE_TO_BE_FOLLOWED 500

int robot_distance_from_obstacles;

void setup()
{
  set_pins_configuration();

  Serial.begin(9600);
}

void set_pins_configuration()
{
  pinMode(LEFT_ENGINE_M1A_PIN, OUTPUT);
  pinMode(LEFT_ENGINE_M1B_PIN OUTPUT);
  pinMode(LEFT_ENGINE_M1C_PIN, OUTPUT);
  pinMode(RIGHT_ENGINE_M2A_PIN, OUTPUT);
  pinMode(RIGHT_ENGINE_M2B_PIN, OUTPUT);
  pinMode(RIGHT_ENGINE_M2C_PIN, OUTPUT);
  pinMode(ULTRASOUND_SENSOR_DIST_ECHO, INPUT);
  pinMode(ULTRASOUND_SENSOR_DIST_TRIG, OUTPUT);
}

void loop()
{
  set_robot_distance_from_obstacles_in_path();

  if (is_robot_too_near_to_obstacle())
  {
    move_robot_to_left_side();
  }
  else
  {
    follow_line_path();
  }
}

void follow_line_path()
{
  if (is_robot_in_right_path())
  {
    return move_robot_to_front();
  }

  return move_robot_zig_zag_until_find_line_path();
}

void move_robot_zig_zag_until_find_line_path()
{
  int turn_duration = 10;
  bool robot_found_line_path = false;

  while (!robot_found_line_path)
  {
    move_robot_to_left_side();

    robot_found_line_path = did_robot_find_line_path(turn_duration);

    if (robot_found_line_path)
    {
      break;
    }

    turn_duration += 10;

    move_robot_to_right_side();

    robot_found_line_path = did_robot_find_line_path(turn_duration);

    turn_duration += 10;
  }
}

bool did_robot_find_line_path(int turn_duration)
{
  for (int current_time = 0; current_time < turn_duration; current_time = current_time + 10)
  {
    delay(10);

    if (is_robot_in_right_path())
    {
      return true;
    }
  }

  return false;
}

bool is_robot_in_right_path()
{
  bool is_sensor_ground_vision_black_color = digitalRead(2) == 0;

  return is_sensor_ground_vision_black_color;
}

void set_robot_distance_from_obstacles_in_path()
{
  activate_ultrasound_sensors();

  robot_distance_from_obstacles = (ultrasonic.Ranging(CM));
}

void activate_ultrasound_sensors()
{
  digitalWrite(ULTRASOUND_SENSOR_DIST_TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(ULTRASOUND_SENSOR_DIST_TRIG, HIGH);
  delayMicroseconds(2);

  digitalWrite(ULTRASOUND_SENSOR_DIST_TRIG, LOW);
}

bool is_robot_too_near_from_obstacle()
{
  return robot_distance_from_obstacles < 30;
}

void move_robot_to_left_side()
{
  digitalWrite(LEFT_ENGINE_M1A_PIN, LOW);
  digitalWrite(LEFT_ENGINE_M1B_PIN HIGH);

  analogWrite(LEFT_ENGINE_M1C_PIN, PRINCIPAL_ENGINE_POTENCIAL);
  analogWrite(RIGHT_ENGINE_M2C_PIN, PRINCIPAL_ENGINE_POTENCIAL);

  digitalWrite(RIGHT_ENGINE_M2A_PIN, HIGH);
  digitalWrite(RIGHT_ENGINE_M2B_PIN, LOW);
}

void move_robot_to_right_side()
{
  digitalWrite(LEFT_ENGINE_M1A_PIN, HIGH);
  digitalWrite(LEFT_ENGINE_M1B_PIN LOW);

  analogWrite(LEFT_ENGINE_M1C_PIN, PRINCIPAL_ENGINE_POTENCIAL);
  analogWrite(RIGHT_ENGINE_M2C_PIN, PRINCIPAL_ENGINE_POTENCIAL);

  digitalWrite(RIGHT_ENGINE_M2A_PIN, LOW);
  digitalWrite(RIGHT_ENGINE_M2B_PIN, HIGH);
}

void move_robot_to_front()
{
  digitalWrite(LEFT_ENGINE_M1A_PIN, HIGH);
  digitalWrite(LEFT_ENGINE_M1B_PIN LOW);

  analogWrite(LEFT_ENGINE_M1C_PIN, ENGINE_POTENCIAL_WALKING_TO_FRONT_MOVEMENT);

  digitalWrite(RIGHT_ENGINE_M2A_PIN, HIGH);
  digitalWrite(RIGHT_ENGINE_M2B_PIN, LOW);

  analogWrite(RIGHT_ENGINE_M2C_PIN, ENGINE_POTENCIAL_WALKING_TO_FRONT_MOVEMENT);
}

void move_robot_to_back()
{
  digitalWrite(LEFT_ENGINE_M1A_PIN, LOW);
  digitalWrite(LEFT_ENGINE_M1B_PIN HIGH);

  analogWrite(LEFT_ENGINE_M1C_PIN, ENGINE_POTENCIAL_WALKING_TO_FRONT_MOVEMENT);

  digitalWrite(RIGHT_ENGINE_M2A_PIN, LOW);
  digitalWrite(RIGHT_ENGINE_M2B_PIN, HIGH);

  analogWrite(RIGHT_ENGINE_M2C_PIN, ENGINE_POTENCIAL_WALKING_TO_FRONT_MOVEMENT);
}

void stop_robot_movements()
{
  digitalWrite(LEFT_ENGINE_M1A_PIN, HIGH);
  digitalWrite(LEFT_ENGINE_M1B_PIN HIGH);

  analogWrite(LEFT_ENGINE_M1C_PIN, ENGINE_POTENCIAL_WALKING_TO_FRONT_MOVEMENT);

  digitalWrite(RIGHT_ENGINE_M2A_PIN, HIGH);
  digitalWrite(RIGHT_ENGINE_M2B_PIN, HIGH);

  analogWrite(RIGHT_ENGINE_M2C_PIN, ENGINE_POTENCIAL_WALKING_TO_FRONT_MOVEMENT);
}
#pragma once

#define fwd_cmd              119        //Move forward with PID
#define motor_fwd_cmd        105        //Move forward without PID
#define bwd_cmd              115        //Move back with PID
#define motor_bwd_cmd        107        //Move back without PID
#define left_cmd             97            //Turn Left by turning off one motor
#define left_rot_cmd         98            //Rotate left by running both motors is opposite direction
#define right_cmd            100        //Turn Right by turning off one motor
#define right_rot_cmd        110        //Rotate Right by running both motors is opposite direction
#define stop_cmd             120        //Stop the GoPiGo
#define ispd_cmd             116        //Increase the speed by 10
#define dspd_cmd             103        //Decrease the speed by 10
#define m1_cmd               111         //Control motor1
#define m2_cmd               112         //Control motor2
#define read_motor_speed_cmd 114        //Get motor speed back

#define volt_cmd             118        //Read the voltage of the batteries
#define us_cmd               117        //Read the distance from the ultrasonic sensor
#define led_cmd              108        //Turn On/Off the LED's
#define servo_cmd            101        //Rotate the servo
#define enc_tgt_cmd          50            //Set the encoder targeting
#define fw_ver_cmd           20            //Read the firmware version
#define en_enc_cmd           51            //Enable the encoders
#define dis_enc_cmd          52            //Disable the encoders
#define read_enc_status_cmd  53            //Read encoder status
#define en_servo_cmd         61            //Enable the servo's    
#define dis_servo_cmd        60            //Disable the servo's
#define set_left_speed_cmd   70            //Set the speed of the right motor
#define set_right_speed_cmd  71            //Set the speed of the left motor
#define en_com_timeout_cmd   80            //Enable communication timeout
#define dis_com_timeout_cmd  81            //Disable communication timeout
#define timeout_status_cmd   82            //Read the timeout status
#define enc_read_cmd         53            //Read encoder values
#define trim_test_cmd        30            //Test the trim values
#define trim_write_cmd       31            //Write the trim values
#define trim_read_cmd        32        

#define digital_write_cmd    12          //Digital write on a port
#define digital_read_cmd     13          //Digital read on a port
#define analog_read_cmd      14          //Analog read on a port
#define analog_write_cmd     15          //Analog read on a port
#define pin_mode_cmd         16          //Set up the pin mode on a port

#define ir_read_cmd          21
#define ir_recv_pin_cmd      22
#define cpu_speed_cmd        25

#define boardversioninfo_pin 7
#define writepwm_pin         10

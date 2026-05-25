#include <stdio.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_timer.h"

// =========================
// PID GAINS
// =========================
float Kp = 2.0;
float Ki = 0.2;
float Kd = 1.0;

// =========================
// TARGET
// =========================
float setpoint = 100.0;

// =========================
// SYSTEM STATES
// =========================
float position = 0.0;
float velocity = 0.0;

// =========================
// PID STATES
// =========================
float integral = 0.0;
float previous_error = 0.0;

void app_main(void)
{
    // Time tracking
    int64_t previous_time = esp_timer_get_time();

    while (1)
    {
        // =====================================
        // REAL dt CALCULATION
        // =====================================
        int64_t current_time = esp_timer_get_time();

        float dt =
            (current_time - previous_time) / 1000000.0f;

        previous_time = current_time;

        // Safety check
        if (dt <= 0.0f)
            continue;

        // =====================================
        // ERROR
        // =====================================
        float error = setpoint - position;

        // =====================================
        // INTEGRAL
        // =====================================
        integral += error * dt;

        // -------------------------------------
        // ANTI-WINDUP CLAMP
        // -------------------------------------
        if (integral > 100.0f)
            integral = 100.0f;

        if (integral < -100.0f)
            integral = -100.0f;

        // =====================================
        // DERIVATIVE
        // =====================================
        float derivative =
            (error - previous_error) / dt;

        previous_error = error;

        // =====================================
        // PID OUTPUT
        // =====================================
        float output =
            (Kp * error) +
            (Ki * integral) +
            (Kd * derivative);

        // -------------------------------------
        // OUTPUT SATURATION
        // -------------------------------------
        if (output > 200.0f)
            output = 200.0f;

        if (output < -200.0f)
            output = -200.0f;

        // =====================================
        // SIMULATED PHYSICS
        // =====================================

        // Controller output acts like force
        float acceleration = output;

        // Velocity update
        velocity += acceleration * dt;

        // Damping / friction
        velocity *= 0.95f;

        // Position update
        position += velocity * dt;

        // =====================================
        // SERIAL OUTPUT
        // =====================================
        printf("SP: %.2f  POS: %.2f  ERR: %.2f  "
               "VEL: %.2f  OUT: %.2f\n",
               setpoint,
               position,
               error,
               velocity,
               output);

        // 50 ms loop
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
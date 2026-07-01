#include "AI.h"

// void AI_Logic(void)
// {
//     float my_features[] = {(float)PercentHumi, (float)PercentTemp};

//     signal_t features_signal;
//     numpy::signal_from_buffer(my_features, 2, &features_signal);

//     ei_impulse_result_t result = {0};

//     run_classifier(&features_signal, &result, false);

//     if (strcmp(result.classification[1].label, "tuoi_nuoc") == 0 && result.classification->value > 0.8)
//     {
//         Serial.println("turn off pump");
//         ValuePump = 1;
//         SerialPort.print('1');
//     }
// }
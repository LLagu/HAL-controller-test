#ifndef CONFIGURATION_DEFAULT_H
#define CONFIGURATION_DEFAULT_H

#include "Setting.h"
#include <cmath>
#include <optional>
#include <vector>

namespace config {

const std::vector<Setting> kDefaultConfig = {
    { ConfigurationName::kAngleSensorMaxValue,
        M_PI,
        std::nullopt,
        std::nullopt,
        "rad",
        "Maximum value of sensor's range" },
    { ConfigurationName::kAngleSensorMinValue,
        -M_PI,
        std::nullopt,
        std::nullopt,
        "rad",
        "Minimum value of sensor's range" },
    { ConfigurationName::kControllerProportionalGain,
        1.0,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt },
    { ConfigurationName::kControllerIntegrativeGain,
        0.0,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt },
    { ConfigurationName::kControllerDerivativeGain,
        0.0,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt },
};

} // namespace config

#endif

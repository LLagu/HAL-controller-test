#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ConfigurationInterface.h"
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace config {
class Configuration : public ConfigurationInterface<json> {
public:
    explicit Configuration(std::filesystem::path filepath);
    [[nodiscard]] bool LoadConfigurationFile() override;
    [[nodiscard]] bool WriteConfigurationFile(json& jsonfile) override;
    [[nodiscard]] Setting GetSetting(ConfigurationName config_name) override;
    [[nodiscard]] bool CreateDefaultConfigurationFile();

private:
    std::filesystem::path filepath_;
    json configData_;
};
} // namespace config

NLOHMANN_JSON_NAMESPACE_BEGIN

/**
 * @brief Serializer. Uses Argument-dependent lookup to choose to_json/from_json functions from the types' namespaces.
Overloaded to work with std::optional
 *
 * @tparam T
 */
template <typename T>
struct adl_serializer<std::optional<T>> {
    /**
     * @brief Converts a JSON value to any value type
     *
     * @param j
     * @param opt
     */
    static void from_json(const json& j, std::optional<T>& opt)
    {
        if (j.is_null()) {
            opt = std::nullopt;
        }
        else {
            opt = j.get<T>();
        }
    }
    /**
     * @brief Converts any value type to a JSON value
     *
     * @param json
     * @param t
     */
    static void to_json(json& json, std::optional<T> t)
    {
        if (t) {
            json = *t;
        }
        else {
            json = nullptr;
        }
    }
};

/**
 * @brief
 *
 * @tparam T
 * @tparam Ts
 * @param j
 * @param data
 */
template <typename T, typename... Ts>
void variant_from_json(const nlohmann::json& j, std::variant<Ts...>& data)
{
    try {
        data = j.get<T>();
    }
    catch (...) {
    }
}

/**
 * @brief Serializer. Uses Argument-dependent lookup to choose to_json/from_json functions from the types' namespaces.
Overloaded to work with std::variant
 *
 * @tparam Ts
 */
template <typename... Ts>
struct adl_serializer<std::variant<Ts...>> {
    /**
     * @brief Converts any value type to a JSON value
     *
     * @param json
     * @param t
     */
    static void to_json(nlohmann::json& j, const std::variant<Ts...>& data)
    {
        std::visit([&j](const auto& v) { j = v; }, data);
    }
    /**
     * @brief Converts a JSON value to any value type
     *
     * @param j
     * @param opt
     */
    static void from_json(const nlohmann::json& j, std::variant<Ts...>& data)
    {
        (variant_from_json<Ts>(j, data), ...);
    }
};

NLOHMANN_JSON_NAMESPACE_END

#endif // CONFIGURATION_H
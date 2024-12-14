#ifndef MATTER_INTERFACE_H
#define MATTER_INTERFACE_H

#include <esp_err.h>
#include <esp_matter.h>

/**
 * @brief Callback for handling Matter stack events.
 *
 * This function processes various events triggered by the Matter stack, such as connectivity changes,
 * commissioning progress, and network state updates.
 *
 * @param[in] event Pointer to the Matter device event structure containing event details.
 * @param[in] arg   Optional user-defined argument provided during callback registration.
 */
void matter_event_callback(const ChipDeviceEvent *event, intptr_t arg);

/**
 * @brief Callback for processing identification cluster commands.
 *
 * This function handles identification effects (e.g., blinking lights, sounds) triggered by cluster commands
 * received on a Matter endpoint. The behavior is determined by the effect ID and variant.
 *
 * @param[in] type           Type of the identification callback (e.g., start or stop).
 * @param[in] endpoint_id    ID of the endpoint receiving the identification command.
 * @param[in] effect_id      ID specifying the type of identification effect to execute.
 * @param[in] effect_variant Variant of the identification effect for specific behavior.
 * @param[in] priv_data      Optional user-defined private data passed during callback registration.
 * @return
 *      - ESP_OK on success.
 *      - ESP_ERR_INVALID_ARG if the arguments are invalid.
 *      - Appropriate error codes for other failures.
 */
esp_err_t identification_callback(esp_matter::identification::callback_type_t type, uint16_t endpoint_id,
                                  uint8_t effect_id, uint8_t effect_variant, void *priv_data);

/**
 * @brief Initializes the Matter stack and creates a Matter node.
 *
 * This function sets up the Matter framework, initializes the Matter node, and registers
 * necessary callbacks for attribute updates and identification. It also starts the Matter event
 * handling loop.
 *
 * @param[out] endpoint_id          Pointer to store the endpoint ID created during initialization.
 * @param[in]  attribute_update_cb  Callback function for handling attribute updates.
 * @return
 *      - ESP_OK on successful initialization.
 *      - ESP_FAIL if the initialization or node creation fails.
 *      - Error codes from the Matter framework for other failures.
 */
esp_err_t matter_init(uint16_t *endpoint_id, esp_matter::attribute::callback_t attribute_update_cb);

/**
 * @brief Updates the value of an On/Off attribute for a specified endpoint.
 *
 * This function updates the `OnOff` attribute value for a given Matter endpoint and propagates
 * the change to the Matter framework.
 *
 * @param[in] endpoint_id ID of the Matter endpoint to update.
 * @param[in] new_value   Boolean value to set for the `OnOff` attribute.
 * @return
 *      - ESP_OK if the value is updated successfully.
 *      - ESP_ERR_INVALID_ARG if the arguments are invalid.
 *      - Error codes from the Matter framework for other failures.
 */
esp_err_t matter_update_value(uint16_t endpoint_id, bool new_value);

/**
 * @brief Creates an On/Off endpoint for the Matter node.
 *
 * This function adds an On/Off endpoint to the Matter node, allowing control of a relay or other
 * On/Off device. The endpoint ID is returned to the caller for reference.
 *
 * @param[in]  matter_node Pointer to the Matter node to which the endpoint is added.
 * @param[out] endpoint_id Pointer to store the ID of the created endpoint.
 * @return
 *      - ESP_OK if the endpoint is created successfully.
 *      - ESP_FAIL if the endpoint creation fails.
 */
esp_err_t create_on_off_endpoint(esp_matter::node_t *matter_node, uint16_t *endpoint_id);

#endif // MATTER_INTERFACE_H

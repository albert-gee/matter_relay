#ifndef MATTER_INTERFACE_H
#define MATTER_INTERFACE_H

#include <esp_err.h>
#include <esp_matter.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the Matter stack and creates a Matter node.
 *
 * This function sets up the Matter framework, initializes the Matter node, and registers
 * necessary callbacks for attribute updates and identification. It also starts the Matter event
 * handling loop.
 *
 * @param[out] endpoint_id          Pointer to store the endpoint ID created during initialization.
 * @return
 *      - ESP_OK on successful initialization.
 *      - ESP_FAIL if the initialization or node creation fails.
 *      - Error codes from the Matter framework for other failures.
 */
esp_err_t matter_init(uint16_t *endpoint_id);

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

#ifdef __cplusplus
}
#endif

#endif // MATTER_INTERFACE_H

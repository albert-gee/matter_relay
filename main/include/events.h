#ifndef EVENTS_H
#define EVENTS_H

#include <esp_err.h>
#include <esp_matter.h>
#include <platform/CHIPDeviceEvent.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Callback for handling attribute updates from the Matter stack.
 *
 * This function is invoked when an attribute in the Matter data model is updated. It allows applications
 * to respond to changes in cluster attributes, such as updating hardware states or triggering application logic.
 *
 * @param[in] type         Type of attribute callback (e.g., pre-update or post-update).
 * @param[in] endpoint_id  ID of the endpoint containing the updated attribute.
 * @param[in] cluster_id   ID of the cluster containing the updated attribute.
 * @param[in] attribute_id ID of the attribute being updated.
 * @param[in,out] val      Pointer to the new attribute value. Can be modified during pre-update callbacks.
 * @param[in] priv_data    Optional user-defined data passed during callback registration.
 * @return
 *      - ESP_OK on success.
 *      - ESP_ERR_INVALID_ARG if the arguments are invalid.
 *      - Other error codes depending on application logic.
 */
esp_err_t matter_attribute_update_callback(esp_matter::attribute::callback_type_t type,
                                       uint16_t endpoint_id, uint32_t cluster_id,
                                       uint32_t attribute_id, esp_matter_attr_val_t *val,
                                       void *priv_data);


#ifdef __cplusplus
}
#endif

#endif // EVENTS_H

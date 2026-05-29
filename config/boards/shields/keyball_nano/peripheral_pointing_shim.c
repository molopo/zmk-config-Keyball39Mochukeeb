/*
 * Peripheral-side shim for the PMW3610 trackball in dongle mode.
 *
 * The kumamuk PMW3610 driver does layer-aware mode selection (move / scroll /
 * snipe / ball-action) directly in its report path, calling central-only ZMK
 * APIs: zmk_keymap_highest_layer_active() and zmk_behavior_queue_add(). On a
 * split *peripheral* those subsystems are not built, so the trackball half
 * fails to link (undefined references).
 *
 * In our dongle setup the trackball half only needs to report *raw* motion;
 * the dongle (central) applies scroll / snipe / automouse via input processors
 * (see trackball_split.dtsi). So we provide minimal definitions here:
 *   - no layers exist on a peripheral, so report the base layer (0), which
 *     keeps the driver in plain MOVE mode and forwards raw movement; and
 *   - drop any queued behaviors (ball actions are handled on the central).
 *
 * Compiled only on the split peripheral with the sensor enabled
 * (see CMakeLists.txt), where these symbols are otherwise undefined.
 */

#include <zephyr/kernel.h>
#include <zmk/keymap.h>
#include <zmk/behavior_queue.h>

zmk_keymap_layer_index_t zmk_keymap_highest_layer_active(void) {
    return 0;
}

int zmk_behavior_queue_add(const struct zmk_behavior_binding_event *event,
                           const struct zmk_behavior_binding behavior, bool press,
                           uint32_t wait) {
    ARG_UNUSED(event);
    ARG_UNUSED(behavior);
    ARG_UNUSED(press);
    ARG_UNUSED(wait);
    return 0;
}

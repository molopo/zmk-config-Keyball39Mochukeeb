# The PMW3610 driver references central-only ZMK keymap/behavior APIs in its
# report path, so the trackball-bearing half cannot link as a split peripheral.
# Provide shims for those symbols, but only on the peripheral that actually runs
# the sensor (the central/dongle has the real implementations). See
# peripheral_pointing_shim.c for details.
if(CONFIG_PMW3610 AND CONFIG_ZMK_SPLIT AND NOT CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    zephyr_library()
    zephyr_library_sources(peripheral_pointing_shim.c)
endif()

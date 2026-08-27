# Copyright (c) 2024 The ZMK Contributors
# SPDX-License-Identifier: MIT

if(CONFIG_ZMK_WIDGET_KEYPRESS_ANIM)
  target_include_directories(app PRIVATE include)

  # Central sees every keypress from both halves (peripheral key events are
  # relayed to it), so it is responsible for telling the peripheral to
  # advance the animation.
  target_sources_ifdef(CONFIG_ZMK_SPLIT_ROLE_CENTRAL app PRIVATE src/keypress_anim_trigger.c)

  # Peripheral-side behavior invoked remotely by central; harmless no-op if
  # the devicetree node isn't present (e.g. when compiled for central).
  target_sources(app PRIVATE src/behavior_anim_pulse.c)

  # Peripheral-side widget + custom status screen that shows the animation.
  target_sources_ifdef(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM app PRIVATE
    src/keypress_anim_widget.c
    src/keypress_anim_status_screen.c
  )
endif()

# VK Boards

Mbed OS support for VK mbed boards

:warning: (since v6.0 VK Boards were removed from the official releases, so their maintenance is done through **`custom-targets.json`** )

## Install

VK `Custom Targets` come as library. It can easily be installed with **mbed CLI**

![Package](https://badgen.net/badge/CLI-1/mbed/green)

- Get Mbed OS **>_** `mbed new <Project name>`
- Update to supported Mbed OS version: (**`mbed-os-6.12.0`**)
  - **>_** `cd <Project name>\mbed-os`
  - **>_** `mbed update <mbed-os-x.x.x>`
  - **>_** `cd ..`
- Get Custom Targets lib **>_** `mbed add https://github.com/mbedNoobNinja/mbed-vk-boards`
- Patch Mbed OS **>_** `mbed-vk-boards\patch\patch.py`

![Package](https://badgen.net/badge/CLI-2/mbed-tools/green)

- Get Mbed OS **>_** `mbed-tools new <Project name>`
- Update to supported Mbed OS version: (**`mbed-os-6.12.0`**)
  - **>_** `cd <Project name>`
  - **>_** `git -C mbed-os checkout <mbed-os-x.x.x>`
- Get Custom Targets lib **>_** `mbed-tools import https://github.com/mbedNoobNinja/mbed-vk-boards`
  - Create lib file **>_** `echo https://github.com/mbedNoobNinja/mbed-vk-boards> mbed-vk-boards.lib`
- Patch Mbed OS **>_** `mbed-vk-boards\patch\patch.py`
- Modify the CMakeLists.txt file:
  - Open project's ROOT **`CMakeLists.txt`**
  - Insert `add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mbed-vk-boards)` after the `add_subdirectory(${MBED_PATH})` line
  - Save the `CMakeLists.txt` file.

## Build

Go to the project's DIR **>_** `cd /D <Project path>`

- **CLI 1 >_** `mbed compile --custom-targets mbed_vk_boards -t ARM,GCC_ARM -m VK_RZ_A1H,VK_RZ_A1LU,VK_RZ_A1R3`
- **CLI 2 >_** `mbed-tools compile --custom-targets-json mbed-vk-boards\custom_targets.json -t ARM,GCC_ARM -m VK_RZ_A1H,VK_RZ_A1LU,VK_RZ_A1R3`

## Export

Go to the project's DIR **>_** `cd /D <Project path>`

- **CLI 1 >_** `mbed export --custom-targets mbed_vk_boards -i e2studio -m VK_RZ_A1H,VK_RZ_A1LU,VK_RZ_A1R3`
- **CLI 2 >_** `N/A`
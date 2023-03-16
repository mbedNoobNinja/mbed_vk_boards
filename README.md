# VK Boards

Mbed OS support for VK mbed boards

:warning: (since mbed v6.0, VK Boards were removed from the official releases, so their maintenance is done through **`custom-targets.json`** )

## Install

VK `Custom Targets` come as library. It can easily be installed with **mbed CLI**

![Package](https://badgen.net/badge/CLI-1/mbed/green)

- Get Mbed OS **>_** `mbed new <Project name>`
- Update to supported Mbed OS version: (**`mbed-os-6.12.0`**)
  - **>_** `cd <Project name>\mbed-os`
  - **>_** `mbed update <mbed-os-x.x.x>`
  - **>_** `cd ..`
- Get Custom Targets lib **>_** `mbed add https://github.com/Vekatech/mbed-vk-boards`
- Patch Mbed OS **>_** `mbed-vk-boards\patch\patch.py`

![Package](https://badgen.net/badge/CLI-2/mbed-tools/green)

- Get Mbed OS **>_** `mbed-tools new <Project name>`
- Update to supported Mbed OS version: (**`mbed-os-6.12.0`**)
  - **>_** `cd <Project name>`
  - **>_** `git -C mbed-os checkout <mbed-os-x.x.x>`
- Get Custom Targets lib **>_** `mbed-tools import https://github.com/Vekatech/mbed-vk-boards`
  - Create lib file **>_** `echo https://github.com/Vekatech/mbed-vk-boards> mbed-vk-boards.lib`
- Patch Mbed OS **>_** `mbed-vk-boards\patch\patch.py`
- Modify the CMakeLists.txt file:
  - Open project's ROOT **`CMakeLists.txt`**
  - Insert `add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mbed-vk-boards)` after the `add_subdirectory(${MBED_PATH})` line
  - Save the `CMakeLists.txt` file.

## Build

Go to the project's DIR **>_** `cd /D <Project path>`

- **CLI 1 >_** `mbed compile --custom-targets mbed-vk-boards -t <toolchain> -m <VK board>`[^1][^2]
- **CLI 2 >_** `mbed-tools compile --custom-targets-json mbed-vk-boards\custom_targets.json -t <toolchain> -m <VK board>`[^1][^2]

## Export

Go to the project's DIR **>_** `cd /D <Project path>`

- **CLI 1 >_** `mbed export --custom-targets mbed-vk-boards -i e2studio -m <VK board>`[^2]
- **CLI 2 >_** `N/A`

## Demo

Any `mbed example program` available for a given `<VK board>` is (& will be) uploaded in `demos` folder. If no `<Example name>` is specified, **`Demo`** name will be extraced by deffault. The CLI tool can work with one example program at a time, so you have to specify what demo for which board to be extracted.

[Full](https://vekatech.com/products2.php?id=2) Demo descriptions and more info about Bords manufactured by Vekatech.Ltd can be found on their website.

Go to the project's DIR **>_** `cd /D <Project path>`
- Extract **>_** `mbed-vk-boards\demos\extract.py <VK board> [<Example name>]`[^2]

[^1]: `<toolchain>` can be one of these options [ **`ARM`** / **`GCC_ARM`** ]
[^2]: `<VK board>` can be one of these options [ **`VK_RZ_A1H`** / **`VK_RZ_A1LU`** / **`VK_RZ_A1R3`** ]

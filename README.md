# Eiger - Avionic software
Software and tools used by the Avionic (AV) of the [EPFL Rocket Team](https://epflrocketteam.ch) 2019 Eiger project.

## Hardware description
The AV is composed of multiple custom boards (Host-board) with each a STM32 microcontroller.
Each host-board can have up to two peripheral connected to it, including:
* Sensor board: using a BNO055 IMU and BMP280/BME280 barometer 
* GPS board: using a ublox module
* Telemetry board: using a Xbee (868) SX transciever
* RS232 com board: using a MAX3232 transciever
* and others.
A CAN bus is used for inter-board communications.

Each host-boards has:
* a [STM32F446RE](https://www.st.com/en/microcontrollers-microprocessors/stm32f446re.html)
microcontroller (64-pin, ARM Cortex M4) from ST Microelectronics
* a CAN transciever (SN65HVD234D from Texas Instrument)
* a voltage regulator (TSR 0.5-2433 from Traco Power) with dual input
* a 128 Mb external flash memory ([MT25QL128ABA](https://www.micron.com/-/media/client/global/documents/products/data-sheet/nor-flash/serial-nor/mt25q/die-rev-a/mt25q_qlhs_l_128_aba_0.pdf) from Micron)
* A micro SD card slot
* A RGB LED
* Two sockets for peripheral following the [mikroBus](https://www.mikroe.com/mikrobus) standard (M size, 3.3V), with 4 additionnal pins.
* A D-sub 9 connector for connectivity to the AV spine (backplane PCB interconnecting all the host-boards) with:
  - 2 power inputs
  - CAN bus lines
  - 3 general purpose lines
* Headers with JTAG and UART for debug

More information about the AV system and hardware (HW) architecture can be found on the team's Drive.

# Repository content
* `flight-sw/`: the project of the different flight software codes developed in 2019. Each folder is a project that can be opened and compiled in the Eclipse-based IDE SW4STM32.
  - `template/`: This is not a template but the flight software used in the Eiger.
  By selecting the build type in the IDE, the code running on each different board can be compiled.
  - `matterhorn_3/`: Matterhorn 3 central avionic code, designed in Summer 2018
  (copied from the archived [repo](https://github.com/EPFLRocketTeam/matterhorn_3)
  to take advantage of the codebase developed for Eiger)
  - `Master_board/` and `telemetry-board/` are depecrated
* `library/`: code imported in each of the projects in `flight-sw`
  - `STM32Cube_FW_F4_Vx.xx.x/`: Code library
  [provided by ST](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-mcu-mpu-packages/stm32cubef4.html)
  for STM32F4 through it's [STMCube Ecosystem](https://www.st.com/content/st_com/en/stm32cube-ecosystem.html) ,
  a complete software solution for STM32 microcontrollers.
  - `host-board/`: Library of components and software routine written for specific features and thread that can be run on the host-board:
    - `Sensors/`: interfacing with the Sensor board
    - `Telemetry/`: interfacing the RF transciever
    - CAN communication library
    - Airbrake control (`airbrake/`)
    - Kalman filter (`ekf/`)
    - SD card logging (`sd_card`)
    - Rocket FSM (`Misc/state_estimation`)
* `testing-sw/`: Deprecated. Small code project initially developed to test small features of the host-boards
* `tools/:
  - `CAN-python`: Python scripts for monitoring and uploading data to the CAN bus the using the [PCAN-USB](https://www.peak-system.com/PCAN-USB.199.0.html?L=1).
  The drivers needs to be installed for proper operations.
  Instead of those scripts, the software provided by Peak System (Windows only) can be used for basic CAN bus monitoring.
  For more information on the scripts operation see the files headers.
    - `canMonitor.py`: Example script to display a stream of raw messages on the CAN bus
    - `replayLog.py`: Example script to replay CAN messages logs.
    - `can_console.py`: Display and logs CAN messages with human readable names (see `comm_lib/protocol.txt`). Can also be used to replay CAN logs (by specifying a log file at startup, ex: `python can_console my_log_file`).
    - `comm_lib/`: helper functions and classes for the scripts operation. `protocol.txt` contains the display name of the IDs numbers used in the CAN communication
  - `flight-plot`: Matlab plotting routine to help processing of Matterhorn 3 flight data

# Usage
## Useful tools
- An up to date (3.x) python installation (for support scripts)
- An STM32 compatible IDE (Integrated Development Environment) to develop, debug and flash code, on the Nucleo as well as the host boards.
  The IDE of choice is [System Workbench for STM 32 (SW324STM32)](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-ides/sw4stm32.html) since it is cross plateform (Atollic Studio is Windows only).
  The recent [STM32 CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) might also be a good option but wasn't tested.
- [CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) to generate the initialize a STM32 code project and configure the microcontroller pinout through a handy GUI.
- Peak System drivers to communicate with the PCAN-USB probe ([Linux](https://www.peak-system.com/fileadmin/media/linux/index.htm), [Windows](https://www.peak-system.com/Downloads.76.0.html?&L=1) and [Mac](https://www.peak-system.com/MacCAN.336.0.html?&L=1)).
  The drivers are needed for the python tools (see `tools/CAN-python`) to work properly.
  The [PCAN-View software](https://www.peak-system.com/PCAN-View.242.0.html?&L=1) (Windows only) can also be used for basic CAN bus monitoring
- When working with the telemetry system (which uses a Xbee SX), the Xbee tool [XCTU](https://www.digi.com/products/embedded-systems/digi-xbee-tools/xctu) from Digi might be useful to check and the set the Xbee's configuration

## Flashing embedded software
The main steps are:
1. Open the code project in a IDE.
2. Wire the hardware properly (JTAG probe from ST-LINK programmer connected to the target board, with the wires in the correct order)
3. Make sure the correct build version is selected in the IDE
4. Build and Run on target.

## Developping embedded software
TODO

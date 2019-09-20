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
  Instead of those scripts, the software provided by Peak System (Windows only) can be used for basic CAN bus monitoring
  - `flight-plot`: Matlab plotting routine to help processing of Matterhorn 3 flight data

# Usage
## Requirements
TODO
## Flashing SW
TODO
## Developping SW
TODO

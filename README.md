# Beyond Backscatter Transmitter

This repository contains the code and configurations for implementing a Beyond Backscatter Transmitter. The project is structured to include a variety of source files, libraries, and configuration scripts needed for the transmitter’s functionality. Key modules include 2-FSK modulation, convolutional coding, reed-solomon coding.

## Repository Structure

### Root Directory

| **File/Folder**           | **Description**                                                                                   |
|---------------------------|---------------------------------------------------------------------------------------------------|
| `src`                     | Source files for key functionality, including modulation, encoding, and error correction.         |
| `main.c`                  | Main file to be flashed onto ESP32 for baseband signal generation using 2-FSK.                    |
| `main.h`                  | Header file for main.c.                                                                           |
| `pwmfsk.c`                | PWM (Pulse Width Modulation) functionality for FSK modulation.                                    |
| `sdkconfig.defaults`      | Default SDK configuration settings for ESP-IDF.                                                   |
| `testcodes.c`             | Test code for verifying different functionalities.                                                |
| `traditional_backscatter.c` | Implementations related to traditional backscatter techniques.                                   |

### `src` Directory

Contains primary source files for signal processing, modulation, encoding, and communication:

| **File**                  | **Description**                                                                                   |
|---------------------------|---------------------------------------------------------------------------------------------------|
| `convolutional_encoder.c` | Implements convolutional encoding for error correction.                                           |
| `fsk.c`                   | Frequency Shift Keying (FSK) modulation and demodulation.                                         |
| `hann.c`                  | Hanning window function for signal processing.                                                    |
| `modulator.c`             | Core modulation functions for signal transmission.                                                |
| `packet_gen.c`            | Packet generation for reliable data transmission.                                                 |
| `reedSolomonEncoder.c`    | Reed-Solomon encoding for burst error correction.                                                 |

## Usage

To use the code, flash `main.c` onto the ESP32 module. Ensure all required files are in place and build the project with ESP-IDF.

1. **Set up ESP-IDF**: Follow the [ESP-IDF setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).
2. **Build and Flash**:
   ```bash
   idf.py build
   idf.py -p [PORT] flash

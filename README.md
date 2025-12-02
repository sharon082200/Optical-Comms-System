# Optical Wireless Communication System (FSO) 📡

![Project Status](https://img.shields.io/badge/Status-Completed-success)
![Hardware](https://img.shields.io/badge/Hardware-Arduino%20%7C%20OpAmp-blue)
![Language](https://img.shields.io/badge/Code-C%2B%2B-orange)

## 📖 Overview
This project implements a complete **Free-Space Optical (FSO)** communication link capable of transmitting ASCII text between two microcontrollers using visible light.
Instead of standard hardware modules, this system features a custom-built **Analog Front-End (AFE)** and a specialized software protocol designed to overcome ambient light interference and AC-coupling limitations.

**Key Features:**
* **Noise Immunity:** Active Low-Pass Filtering and Dynamic Thresholding.
* **AC-Coupled Design:** Rejects DC ambient light (sunlight/indoor lighting).
* **Custom Protocol:** RZ-like modulation to maintain signal integrity through capacitors.
* **Low Cost:** Built using standard components (LM358 OpAmp, LED, Photodiode).

---

## 🛠️ Hardware Architecture

### 1. Transmitter
The transmitter encodes ASCII characters into binary pulses. It uses a "Return-to-Zero" style modulation where a logical '1' is a short pulse, preventing capacitor saturation at the receiver.

<img width="744" height="338" alt="transmitter png" src="https://github.com/user-attachments/assets/1bfd24bf-10c4-487c-a02b-1610665daa4e" />

*(Schematic of the LED driver stage)*

### 2. Receiver (Analog Front-End)
The receiver uses a multi-stage OpAmp circuit to recover the weak optical signal:
1.  **Stage A (TIA):** Converts photocurrent to voltage.
2.  **Stage B (Filter):** AC-coupling blocks DC light; Active Low-Pass filter removes high-frequency noise.

<img width="1237" height="903" alt="receiver" src="https://github.com/user-attachments/assets/dfae2ea6-087f-4733-886f-cdc16b13725b" />

*(Schematic of the TIA and Active Filter)*

---

## 💻 Software & Signal Processing

The system does not use standard UART. Instead, a custom **Bit-Banging** protocol is implemented:

* **Synchronization:** A "Start Bit" wakes up the receiver.
* **Adaptive Threshold:** The receiver calculates the noise floor on startup (`avg_val`) and dynamically sets the trigger level:
    ```cpp
    if (ADC > avg_val + THRESHOLD) { /* Bit is '1' */ }
    ```
* **Guard Time:** A 60ms delay between bytes allows capacitors to discharge, preventing Inter-Symbol Interference (ISI).

---

## 🚀 How to Run

1.  **Hardware Setup:**
    * Connect the Transmitter LED circuit to Arduino Pin 12.
    * Connect the Receiver Output to Arduino Pin A0.
    * Align the LED and Photodiode (Line-of-Sight).

2.  **Upload Code:**
    * Upload `Transmitter.ino` to the first Arduino.
    * Upload `Receiver.ino` to the second Arduino.

3.  **Test:**
    * Open the Serial Monitor for both boards (9600 Baud).
    * Type a message in the Transmitter's console.
    * Watch the message appear on the Receiver's console!

---

## 📄 Full Report
For a deep dive into the theory, circuit analysis, and testing results, please refer to the full project report:
[Download Project Report (PDF)](ReportOpticcomms.pdf)

---

## 👥 Credits
**Built by:** Sharon Yerukhimovich & Yonatan Yaron
*Ben-Gurion University, 2025*

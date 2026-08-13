# Error Detection and Optimized Streetlight Management

## Overview

This repository contains the implementation and documentation of an IoT-based smart streetlight management system developed as a B.Tech mini project.

The project focuses on improving streetlight operation through automatic lighting control, continuous current monitoring, fault detection, GSM-based notifications, GPS-based error localization, and cloud-based data storage.

The system combines a photodiode, CT coil, Arduino UNO, GSM/GPS modules, and a solid-state relay to provide automated streetlight management and monitoring.

---

## Project Objectives

The project was developed with three primary objectives:

- Optimize energy use
- Enable swift fault detection
- Improve streetlight management

---

## Problem Addressed

Conventional streetlight systems may rely on fixed-time activation, manual malfunction detection, and limited data management.

These approaches can make it difficult to optimize lighting operation and identify faults quickly.

The proposed system addresses these limitations by introducing automated sensing, electrical monitoring, communication, and cloud-based data handling.

---

## Proposed System

The system uses multiple sensing and communication mechanisms to monitor and manage streetlights.

### Ambient Light Detection

A photodiode is used to assess the surrounding light conditions. The Arduino uses the sensor reading to control the streetlight automatically.

### Power and Current Monitoring

A CT coil is used to monitor the current flowing through the streetlight system. The measured current is used to identify abnormal operating conditions.

### Fault Detection

When the monitored current falls within the defined fault-detection range, the system identifies a possible streetlight fault.

### GSM Notification

The GSM module is used to communicate fault information and send notifications to the operator.

### GPS

GPS is included in the proposed system for locating detected errors and supporting faster corrective action.

### Cloud Monitoring

The system sends monitored sensor and current data to ThingSpeak for cloud-based storage and accessibility.

---

## System Architecture

The overall system can be represented as:

```text
                  ┌──────────────────────┐
                  │      Photodiode      │
                  └──────────┬───────────┘
                             │
                             ▼
                  ┌──────────────────────┐
                  │     Arduino UNO      │
                  │     Controller       │
                  └──────┬───────┬───────┘
                         │       │
             ┌───────────┘       └────────────┐
             ▼                                ▼
   ┌──────────────────┐              ┌────────────────┐
   │ Streetlight      │              │   GSM / GPS    │
   │ Switching        │              │ Communication  │
   └──────────────────┘              └────────────────┘

                  ┌──────────────────────┐
                  │       CT Coil        │
                  └──────────┬───────────┘
                             │
                             ▼
                  ┌──────────────────────┐
                  │ Current Monitoring & │
                  │ Fault Detection      │
                  └──────────────────────┘

                             │
                             ▼
                  ┌──────────────────────┐
                  │   ThingSpeak Cloud   │
                  │   Data Monitoring    │
                  └──────────────────────┘
```

The original project presentation contains the project block diagram showing the photodiode, controller, streetlight switching, CT coil, malfunction detection, and GSM/GPS modules.

---

## Hardware and Software

### Hardware

The project documentation specifies the following hardware:

- Arduino UNO
- Photodiode
- CT Coil
- GSM Module
- GPS Module
- Solid State Relay

### Software

- Arduino IDE
- ThingSpeak

---

## Working Principle

The implementation follows this general sequence:

```text
Ambient Light
     │
     ▼
Photodiode Reading
     │
     ▼
Arduino UNO
     │
     ├──────────────► Relay / Streetlight Control
     │
     ▼
CT Current Measurement
     │
     ▼
Fault Condition Check
     │
     ├──────────────► GSM Call / SMS
     │
     ▼
ThingSpeak Data Upload
```

The Arduino source code reads the photodiode through analog input `A1` and uses a threshold value to control the LED and relay.

The CT sensor is connected to `A0`, and the current is calculated using the `EmonLib` energy-monitoring library.

The source code also uses `SoftwareSerial` for GSM communication.

---

## Source Code

The main implementation is provided in:

```text
smart_street_light.ino
```

The program includes:

- Photodiode sensing
- Relay control
- CT-based RMS current measurement
- Fault-condition detection
- GSM initialization
- GSM call generation
- SMS notification
- ThingSpeak data transmission

The implementation uses:

```cpp
#include <SoftwareSerial.h>
#include <EmonLib.h>
```

### Main Connections

| Function | Arduino Pin |
|---|---|
| CT Sensor | A0 |
| Photodiode | A1 |
| Relay | 7 |
| LED | 6 |
| GSM TX | 2 |
| GSM RX | 3 |

The photodiode threshold used in the provided implementation is:

```text
sensorValue < 15
```

When this condition is met, the LED and relay are switched ON; otherwise, they are switched OFF.

Current monitoring is performed using `EmonLib` with RMS current calculation.

The provided implementation checks the following current range for the fault notification condition:

```text
2.50 A < Irms ≤ 3.30 A
```

When the condition is detected, the GSM module is used to initiate a call and send an SMS notification.

The implementation also uploads the photodiode value and IRMS value to ThingSpeak.

---

## Results

The project presentation reports the following results:

- Reduced energy consumption
- Improved maintenance
- Sustainable solution
- Data-driven decision making

The project also demonstrates:

- Centralized data storage
- Real-time accessibility
- Enhanced analytics

The project presentation contains prototype photographs and ThingSpeak graphs showing photodiode and IRMS data.

---

## Advantages

The project identifies the following advantages:

- Swift fault detection
- Energy efficiency
- Precise error localization
- Effortless enhancement

---

## Limitations

The project documentation identifies the following limitations and challenges:

- Dependency on connectivity
- Adaptation period
- Data security concerns
- Technical complexity
- Sensor dependability
- Incorporation of CT coils

---

## Applications

The documented applications include:

- Smart city initiatives
- Theft current detection
- Public safety enhancement
- Environmental conservation

---

## Project Documents

The original project documents are preserved in the `documents` directory:

```text
documents/
│
├── Project_Abstract.pdf
└── Project_Presentation.pdf
```

### Project Abstract

`Project_Abstract.pdf` contains the formal project description, objectives, tools required, and references.

### Project Presentation

`Project_Presentation.pdf` contains the detailed project material, including:

- Objectives
- Introduction
- Challenges
- Existing method
- Proposed method
- Block diagram
- Source-code presentation
- Results
- Advantages
- Limitations
- Applications
- Hardware and software requirements
- References

The original documents are retained as supporting project material, while this README provides the organized overview of the project.

---

## Repository Structure

```text
SmartStreetLight/
│
├── README.md
│
├── smart_street_light.ino
│
└── documents/
    ├── Project_Abstract.pdf
    └── Project_Presentation.pdf
```

The repository is intentionally kept simple:

- `README.md` provides the complete technical overview.
- `smart_street_light.ino` contains the Arduino implementation.
- `Project_Abstract.pdf` preserves the original project abstract.
- `Project_Presentation.pdf` preserves the original project presentation.

---

## References

The project documents reference:

1. H. H. Hwang et al., *A Comprehensive Review of Intelligent Street Lighting Systems*.
2. José R. Celaya, José M. de la Cruz et al., *Fault Detection and Diagnosis in Industrial Systems*.
3. M. A. Khalaf et al. (2020), *A Review of Smart Street Lighting Control Mechanisms and Standards*.
4. IEEE reference provided in the original project abstract.

The original references are preserved in the project documents.

---

## Authors

**B. Sai Subrahmanya**

**G. Dhanush**

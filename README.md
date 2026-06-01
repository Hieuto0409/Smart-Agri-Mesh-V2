# 🌱 Smart Agri-Mesh v2: Advanced IoT System for Sustainable Farming

## 1. Introduction

**Smart Agri-Mesh v2** is a versatile, scalable, and industrial-grade IoT solution designed to optimize irrigation and monitoring for a wide range of agricultural crops. Building upon the core concepts of v1, this upgraded version shifts from prototyping to a commercially viable product by introducing custom PCB designs, weather-resistant mechanical enclosures (designed in SolidWorks), and a centralized cloud-server architecture serving cross-platform applications.

By utilizing **STM32** and **ESP32**, the system delivers high-precision soil moisture data at multiple depths. Additionally, the system integrates an embedded AI model (**TinyML**) to enable autonomous irrigation decisions based on real-time environmental data, empowering farmers to make data-driven decisions for any farming environment.

## 2. System Architecture

The system follows an advanced Star-Mesh topology integrated with a centralized Cloud architecture:

- **Sensor Nodes (STM32F401RE & Custom PCB):** Collect high-precision soil moisture and temperature data. Housed in custom 3D-printed/molded enclosures.
- **Gateway (ESP32):** Aggregates data from nodes and securely uploads it to the Central Server. Executes the Edge AI model for localized decision-making.
- **Central Cloud Server:** Processes data, manages databases, and hosts RESTful APIs/MQTT brokers.
- **Cross-Platform Monitoring:** Dedicated Mobile App and Web Dashboard for real-time tracking, historical data visualization, and remote control.

```mermaid
graph TD
    A["Soil/Temp Sensors"] -->|ADC| B("STM32 Node (Custom PCB)")
    B -->|"UART/LoRa"| C("ESP32 Gateway")
    C -->|"Wi-Fi/4G"| D{"Central Cloud Server"}
    D -->|"REST API / WebSockets"| E["Web Dashboard"]
    D -->|"REST API / WebSockets"| F["Mobile App"]
    E & F -->|Remote Command| D
    D -->|MQTT| C
    C -->|Trigger (AI or Manual)| G["Relay/Water Pump"]
```

## 3. Technology Stack

**Hardware:** STM32F401RE, ESP32, Capacitive Soil Moisture Sensors.

**Circuit Design:** Custom PCB layout (Altium / KiCad).

**Mechanical Design:** SolidWorks (IP65+ weatherproof enclosures).

**Communication:** UART, LoRa (Mesh communication), Wi-Fi/MQTT (Cloud communication).

**Embedded Software:** C (STM32 HAL), C++ (Arduino/ESP-IDF), TinyML (Edge Impulse).

**Software Platform:** - Backend: Node.js / Python, MongoDB / PostgreSQL.

**Frontend:** ReactJS / VueJS (Web), Flutter / React Native (Mobile).

## 4. Key Features

**High-Precision Monitoring:** Utilizes a 12-bit ADC on the STM32F401RE to accurately measure soil moisture levels.

**AI-Driven Autonomous Irrigation:** Integrates a trained machine learning model via Edge Impulse on the ESP32 to automatically control water pumps based strictly on localized soil and temperature data.

**Industrial-Grade Hardware:** Upgraded to custom PCBs for enhanced durability, noise reduction, and compact form factor.

**Robust Mechanical Enclosure:** Custom-designed using SolidWorks to ensure outdoor reliability, UV resistance, and waterproofing.

**Centralized Cloud Integration:** Real-time data synchronization to a central server, allowing seamless access across multiple devices.

**Cross-Platform Accessibility:** Manage the entire farm via a user-friendly Web Dashboard or on-the-go with the dedicated Mobile App.

**Low-Power & Scalable:** Optimized firmware for battery-powered remote nodes, seamlessly scaling to cover large agricultural estates.

## 5. Repository Structure

📦 Smart-Agri-Mesh-v2
┣ 📂 hardware # Custom PCB schematic and layout files
┣ 📂 mechanical # SolidWorks 3D models (.SLDPRT, .SLDASM) & STL files
┣ 📂 firmware # Embedded C/C++ code for STM32 Nodes and ESP32 Gateway
┣ 📂 server # Backend source code (APIs, MQTT broker, DB models)
┣ 📂 web-app # Source code for the Web Dashboard
┣ 📂 mobile-app # Source code for the Mobile Application
┣ 📂 ai-models # TinyML/Edge Impulse datasets and exported models
┗ 📜 README.md

## 6. Author

**Tô Quang Hiếu**

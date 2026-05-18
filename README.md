<div align="center">

# Remote Health Monitoring System

### IoT-Based Patient Monitoring and Health Risk Prediction using ESP8266 and Machine Learning

![Platform](https://img.shields.io/badge/Hardware-ESP8266%20NodeMCU-blue?style=for-the-badge)
![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak%20%2F%20Blynk-00BFFF?style=for-the-badge)
![ML](https://img.shields.io/badge/ML-SVM%20Classifier-orange?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-Python%20%2F%20C%2B%2B-3776AB?style=for-the-badge&logo=python&logoColor=white)
![IDE](https://img.shields.io/badge/IDE-Arduino%20%2F%20Google%20Colab-darkgreen?style=for-the-badge)

A real-time wireless health monitoring platform that streams patient vitals to cloud dashboards and applies a trained SVM classifier to predict health risks

</div>

---

## Project Overview

Healthcare systems worldwide face a growing demand for continuous, remote patient monitoring — particularly for elderly populations, patients with chronic conditions, and post-hospitalization care. Traditional monitoring requires physical presence in clinical settings, limiting scalability and responsiveness. **IoT-enabled health monitoring** addresses this gap by deploying low-cost sensors and wireless microcontrollers that continuously acquire physiological and environmental data, transmitting it to cloud platforms accessible from anywhere.

This project develops a Remote Health Monitoring System using an ESP8266 NodeMCU as the central processing and communication unit. The system acquires temperature, humidity, and heart rate data in real time, uploads it wirelessly to ThingSpeak for cloud storage and graphical analytics, and streams live readings to a Blynk mobile dashboard for remote observation. Separately, a Support Vector Machine (SVM) model trained on a structured Kaggle healthcare dataset provides a machine learning layer capable of classifying patient data and predicting potential health risks.

The integration of IoT data pipelines and machine learning inference within a single healthcare framework demonstrates a practical, extensible approach to intelligent remote patient care.

---

## Key Features

- Continuous real-time acquisition of temperature, humidity, and heart rate parameters
- Wireless data transmission over Wi-Fi using the ESP8266 NodeMCU
- Live patient dashboard on the Blynk mobile application for remote monitoring from any location
- ThingSpeak cloud integration for persistent data logging, graph plotting, and channel-based IoT analytics
- SVM-based machine learning model for **three independent risk classifiers**: health, hygiene, and environmental
- Google Colab environment for model training, evaluation, and prediction workflow
- LED-based hardware alert indicator triggered on threshold exceedance
- Environmental monitoring alongside physiological parameters for holistic patient context

---

## System Architecture

```
┌──────────────────────────────────────────────────────┐
│                   SENSOR LAYER                       │
│                                                      │
│   [ DHT22 Sensor ]        [ Heart Rate Sensor ]      │
│   Temperature & Humidity   ECG / Pulse Signal        │
└────────────────────────┬─────────────────────────────┘
                         │  Analog & Digital Signals
                         ▼
┌──────────────────────────────────────────────────────┐
│              PROCESSING & COMMUNICATION              │
│                                                      │
│              [ ESP8266 NodeMCU ]                     │
│    Sensor reading, threshold check, LED alerting     │
│    Wi-Fi stack — IEEE 802.11 b/g/n                   │
└────────────────────────┬─────────────────────────────┘
                         │  HTTP / MQTT over Wi-Fi
                         ▼
┌──────────────────────────────────────────────────────┐
│                   CLOUD LAYER                        │
│                                                      │
│   [ ThingSpeak ]              [ Blynk IoT ]          │
│   Data logging & graphs       Real-time dashboard    │
│   REST API access             Mobile app streaming   │
└────────────────────────┬─────────────────────────────┘
                         │  Exported dataset
                         ▼
┌──────────────────────────────────────────────────────┐
│           MACHINE LEARNING PREDICTION                │
│                                                      │
│       [ Google Colab — Python / Scikit-learn ]       │
│   3× SVM Classifiers (Health, Hygiene, Environment)  │
│       Health risk prediction: Low / High             │
└──────────────────────────────────────────────────────┘
```

---

## Hardware Components

| Component | Role | Key Specifications |
|---|---|---|
| **ESP8266 NodeMCU v1.0** | Main microcontroller and Wi-Fi gateway | Operating Voltage: 3.3 V (5 V tolerant via onboard regulator); CPU: Tensilica L106 @ 80/160 MHz; Wi-Fi: IEEE 802.11 b/g/n, 2.4 GHz; Flash: 4 MB; GPIO: 11 digital, 1 ADC (10-bit, 0–1 V); Current: ~80 mA active, ~20 µA deep sleep; Interface: UART, SPI, I2C |
| **DHT22 (AM2302)** | Temperature and humidity sensing | Supply Voltage: 3.3–6 V DC; Temperature Range: −40°C to +80°C, ±0.5°C accuracy; Humidity Range: 0–100% RH, ±2–5% RH accuracy; Sampling Rate: 0.5 Hz (1 reading per 2 seconds); Protocol: Single-wire serial; Response Time: ~2 s |
| **Heart Rate / ECG Sensor** | Pulse and cardiac activity detection | Typical supply: 3.3–5 V; Output: Analog voltage proportional to pulse signal; Measurement: Photoplethysmography (PPG) or electrode-based ECG; Operating range: 30–250 BPM; Interface: Analog output to ESP8266 ADC |
| **LED Indicator** | Visual alert for threshold violations | Forward Voltage: ~2.0–2.2 V (red); Forward Current: 10–20 mA; Controlled via GPIO with current-limiting resistor (220–330 Ω) |

---

## Software and Tools

| Tool / Platform | Purpose |
|---|---|
| Arduino IDE | Firmware development, ESP8266 board support, serial monitoring |
| Blynk IoT (v2.0) | Real-time mobile dashboard; virtual pin streaming; remote monitoring |
| ThingSpeak | Cloud IoT data logging; REST API integration; MATLAB-based analytics and graph visualization |
| Google Colab | Cloud-based Python environment for ML model training and evaluation |
| Python 3.x | Core programming language for data processing and ML pipeline |
| Scikit-learn | SVM classifier implementation, model evaluation, cross-validation |
| Pandas | Dataset loading, cleaning, and feature engineering |
| NumPy | Numerical computation and array operations |
| Kaggle Healthcare Dataset | Labeled training data for health risk classification |

---

## Working Principle

**1. Sensor Data Acquisition**
The DHT22 sensor continuously samples ambient temperature and relative humidity. The heart rate sensor outputs an analog signal representing the patient's pulse, sampled through the ESP8266's onboard ADC. Both datasets are read at regular intervals defined in the firmware.

**2. Local Processing on ESP8266**
The microcontroller reads raw sensor values, applies any necessary calibration or scaling, and checks each parameter against predefined clinical thresholds. If a reading exceeds safe limits, the LED alert is immediately activated at the hardware level without relying on cloud round-trip latency.

**3. Wi-Fi Communication**
The ESP8266 connects to the local Wi-Fi network using stored credentials. Sensor readings are packaged as HTTP GET or POST requests directed at both the ThingSpeak API and the Blynk server. Communication occurs over the standard IEEE 802.11 protocol on the 2.4 GHz band.

**4. Data Upload to ThingSpeak**
Each sensor parameter is mapped to a dedicated ThingSpeak channel field. The platform stores readings with timestamps, enabling historical trend visualization and channel-level analytics. Data is accessible globally via ThingSpeak's REST API.

**5. Real-Time Visualization on Blynk**
Simultaneously, live sensor values are pushed to virtual pins on the Blynk server. The Blynk mobile application renders these as gauge widgets, value displays, or time-series charts, providing caregivers and clinicians with immediate visibility into patient status from any location.

**6. Dataset Export and Preprocessing**
For the machine learning component, sensor feeds are exported from ThingSpeak as `feeds.csv`. The dataset is loaded into Google Colab where missing values across all five feature columns are imputed with realistic random values within expected physiological ranges before label generation and model training.

**7. SVM Model Training and Evaluation**
Three independent SVM classifiers are trained, one each for health risk, hygiene risk, and environmental risk. Each uses a shared pipeline of `StandardScaler` normalization followed by an RBF-kernel SVM. All three models are evaluated on a 25% held-out test split.

**8. Health Risk Prediction and Alert Generation**
Patient parameter values — consistent with those collected by the IoT system — are passed as input features to the trained SVM models. Each classifier independently outputs a binary risk label. High-risk classifications can be configured to trigger additional alert channels, including notifications through Blynk's alert system.

---

## Cloud Integration

### Blynk IoT

Blynk provides a drag-and-drop mobile dashboard that connects directly to the ESP8266 over the internet. Each sensor reading is assigned to a virtual pin, which is polled or pushed by the device firmware at a configurable data rate. Blynk's interface supports multiple widget types — including labeled value displays, historical charts, and threshold-based notification triggers — enabling clinicians or caregivers to monitor patient vitals from any smartphone without any backend infrastructure of their own.

The Blynk platform abstracts Wi-Fi connectivity and data routing, making it particularly well suited for rapid IoT prototyping. Its notification system can be extended to send push alerts to registered mobile devices when monitored values cross clinical thresholds.

### ThingSpeak

ThingSpeak is MathWorks' open IoT analytics platform, designed for logging and visualizing time-series sensor data. Each ESP8266 transmission appends a timestamped record to a ThingSpeak channel via the REST API. The platform automatically generates line graphs for each field, providing a continuous visual record of all monitored parameters.

ThingSpeak's built-in MATLAB analysis environment allows more sophisticated processing — including moving averages, anomaly flagging, and statistical summaries — directly within the cloud dashboard. Channel data is also publicly or privately accessible via API, enabling downstream integration with external analytics tools or database pipelines.

---

## Machine Learning Model

### Algorithm Selection: Support Vector Machine

The Support Vector Machine is a supervised learning algorithm that constructs an optimal hyperplane to separate data points belonging to different classes in a high-dimensional feature space. SVM was selected for this project because of its strong performance on structured, tabular healthcare datasets — particularly in scenarios where the number of features is moderate and the decision boundary between health risk categories is not linearly trivial.

SVM generalizes well with smaller training sets relative to neural networks, requires no assumption about the underlying data distribution, and is robust to outliers when using soft-margin formulations with a regularization parameter C.

### Input Features

The model uses five features derived directly from the IoT sensor feed:

| Feature | Column | Description | Demo Range |
|---|---|---|---|
| Temperature | `field1` | Ambient / body temperature (°C) | 30–42 °C |
| Humidity | `field2` | Relative humidity (%) | 30–90% RH |
| Heart Rate | `field3` | Pulse rate (BPM) | 60–120 BPM |
| Latitude | `latitude` | GPS latitude | 10.0–30.0 |
| Longitude | `longitude` | GPS longitude | 70.0–90.0 |

Missing values in any column are filled with random values sampled uniformly within the ranges above before training.

### Risk Label Definitions

Three binary classification targets are derived from median-based thresholds on the dataset:

| Classifier | Label Logic | Rationale |
|---|---|---|
| **Health Risk** | Temperature > median **OR** Heart Rate > median | Elevated vitals indicate potential physiological stress |
| **Hygiene Risk** | Humidity > median | High ambient humidity signals infection or contamination risk |
| **Environmental Risk** | Temperature > median | High temperature alone flags hazardous ambient conditions |

### Model Pipeline

Each of the three classifiers uses an identical Scikit-learn pipeline:

```python
Pipeline([
    ('scaler', StandardScaler()),
    ('svm', SVC(C=1, kernel='rbf', gamma='scale'))
])
```

- **StandardScaler** normalizes all features to zero mean and unit variance — required for SVM kernel functions to treat all features equally regardless of physical units.
- **RBF kernel** handles nonlinear decision boundaries between risk classes.
- **C=1** provides a balanced soft-margin regularization.
- **gamma='scale'** sets the kernel coefficient automatically as `1 / (n_features × X.var())`.

Data is split 75% training / 25% test using `train_test_split` with `random_state=42` for reproducibility. The same split indices are shared across all three classifiers.

### Classification Results

All three SVM classifiers achieved **96.8% accuracy** on the held-out test set (31 samples).

#### Health Risk Classifier

| | Predicted: No Risk | Predicted: At Risk |
|---|---|---|
| **Actual: No Risk** | 6 | 0 |
| **Actual: At Risk** | 1 | 24 |

| Class | Precision | Recall | F1-Score | Support |
|---|---|---|---|---|
| No Risk (0) | 0.86 | 1.00 | 0.92 | 6 |
| At Risk (1) | 1.00 | 0.96 | 0.98 | 25 |
| **Accuracy** | | | **0.97** | **31** |

#### Hygiene Risk Classifier

| | Predicted: No Risk | Predicted: At Risk |
|---|---|---|
| **Actual: No Risk** | 19 | 1 |
| **Actual: At Risk** | 0 | 11 |

| Class | Precision | Recall | F1-Score | Support |
|---|---|---|---|---|
| No Risk (0) | 1.00 | 0.95 | 0.97 | 20 |
| At Risk (1) | 0.92 | 1.00 | 0.96 | 11 |
| **Accuracy** | | | **0.97** | **31** |

#### Environmental Risk Classifier

| | Predicted: No Risk | Predicted: At Risk |
|---|---|---|
| **Actual: No Risk** | 13 | 0 |
| **Actual: At Risk** | 1 | 17 |

| Class | Precision | Recall | F1-Score | Support |
|---|---|---|---|---|
| No Risk (0) | 0.93 | 1.00 | 0.96 | 13 |
| At Risk (1) | 1.00 | 0.94 | 0.97 | 18 |
| **Accuracy** | | | **0.97** | **31** |

### Prediction Workflow

Once trained, each model accepts a patient's current sensor readings as a five-element input vector `[temperature, humidity, heart_rate, latitude, longitude]`. The SVM pipeline applies the same StandardScaler transformation used during training, then computes the signed distance from the decision hyperplane and returns a binary risk label. All three classifiers run independently, so a single reading can simultaneously flag multiple risk types.

---

## Sensor Details

### DHT22 — Temperature and Humidity Sensor

The DHT22 uses a capacitive polymer element to measure relative humidity and a thermistor for temperature sensing. It communicates over a proprietary single-wire serial protocol, with the ESP8266 reading data via a digital GPIO pin. Temperature and humidity are critical environmental indicators in healthcare settings: elevated ambient temperature combined with high humidity can contribute to heat stress, infection risk, and medication instability. Continuous monitoring of these parameters provides contextual data alongside physiological measurements.

### Heart Rate Sensor

The heart rate sensor measures the patient's pulse through either photoplethysmography (PPG) — using an LED and photodetector to detect blood volume changes in peripheral tissue — or via **ECG electrodes** that capture the cardiac electrical signal directly. The output is an analog voltage waveform whose peaks correspond to heartbeat events. The ESP8266's ADC samples this signal, and the firmware extracts beats-per-minute by detecting peak intervals. Heart rate is one of the primary vital signs in clinical assessment, with normal resting values typically between 60–100 BPM; deviations may indicate arrhythmia, dehydration, fever, or cardiovascular distress.

---

## Results and Observations

| Metric | Outcome |
|---|---|
| Wireless transmission stability | Consistent data upload to both ThingSpeak and Blynk over sustained operation |
| ThingSpeak update frequency | Readings logged at regular intervals with no observed packet loss under stable Wi-Fi |
| Blynk dashboard latency | Near real-time display updates with sub-second visual refresh |
| DHT22 readings | Temperature and humidity values consistent with reference measurements |
| LED alert behavior | Immediate hardware-level activation upon threshold breach, independent of cloud state |
| Health Risk SVM accuracy | **96.8%** — 1 false negative out of 31 test samples |
| Hygiene Risk SVM accuracy | **96.8%** — 1 false positive out of 31 test samples |
| Environmental Risk SVM accuracy | **96.8%** — 1 false negative out of 31 test samples |
| Prediction capability | All three risk classes returned correctly for representative input feature vectors |

---

## Demo and Screenshots

| View | File |
|---|---|
| Setup | <img width="1200" height="1600" alt="WhatsApp Image 2026-05-18 at 15 08 40" src="https://github.com/user-attachments/assets/93ed0e9a-f279-428e-b841-a68b32757793" /> |
| Blynk Dashboard | <img width="1040" height="621" alt="image" src="https://github.com/user-attachments/assets/5348e5f8-b7ee-42a8-994e-330781b00b37" /> |
| ML Prediction Output (Colab) | ![ML](Images/ml_prediction_output.png) |

---

## Applications

- Remote patient monitoring for post-hospitalization recovery and chronic disease management
- Elderly care and assisted living facilities requiring continuous unattended monitoring
- Hospital ward IoT networks for centralized multi-patient vital sign dashboards
- Smart healthcare infrastructure integrated with electronic health record systems
- Wearable health research platforms and clinical trial data collection
- Telemedicine systems where physicians require real-time patient data during consultations

---

## Future Improvements

- Integration of a pulse oximeter (SpO2) sensor for blood oxygen saturation monitoring
- Full ECG waveform acquisition and analysis with arrhythmia detection algorithms
- Replacement of SVM with deep learning models (LSTM or CNN) for time-series vital sign analysis
- Real-time push notification system to registered physician or caregiver mobile devices
- Migration to a wearable form factor using low-power microcontrollers (ESP32 with BLE)
- Integration with a cloud database (Firebase or AWS DynamoDB) for long-term patient record storage
- Development of a dedicated physician web dashboard with patient history, trends, and alerts
- Real-time anomaly detection using statistical process control or unsupervised ML methods
  

---

## Setup Instructions

### Hardware Assembly

Connect the DHT22 data pin to a digital GPIO on the ESP8266, supplying 3.3 V and ground from the NodeMCU's onboard pins. Connect the heart rate sensor's analog output to the ESP8266 ADC pin (A0). Wire the LED indicator through a 220 Ω current-limiting resistor to a spare GPIO. Refer to `Circuit_Diagram/circuit_schematic.png` for the complete connection map.

### Wi-Fi Configuration

In the Arduino firmware file, locate the Wi-Fi credentials section and enter your network SSID and password. The ESP8266 will attempt to connect on boot and retry automatically on disconnection.

### Blynk Setup

Create a new project in the Blynk application, select **ESP8266** as the device, and add widgets mapped to the virtual pins used in the firmware (temperature, humidity, heart rate). Copy the generated authentication token into the firmware before uploading.

### ThingSpeak Setup

Create a free ThingSpeak account and a new channel with fields for each parameter (temperature, humidity, heart rate). Copy the Write API Key into the firmware. The ESP8266 will POST readings to the channel at each sampling interval.

### Uploading Firmware

Install the ESP8266 board package in Arduino IDE via the Boards Manager. Install required libraries (DHT sensor library, BlynkSimpleEsp8266, ThingSpeak). Select the correct board (NodeMCU 1.0) and COM port, then upload the firmware.

### Running the ML Model

Open `ML_Model/electroquest.ipynb` in Google Colab. Upload `feeds.csv` exported from ThingSpeak (or mount Google Drive). Execute the notebook cells sequentially: data loading, missing value imputation, label generation, pipeline training for all three classifiers, evaluation, and prediction. Modify the input feature vector in the prediction cell to test with custom patient readings.

---

## Challenges Faced

| Challenge | Description |
|---|---|
| Sensor noise | The heart rate sensor's analog output is susceptible to motion artifacts and electrical interference, requiring software-level filtering and averaging |
| Wi-Fi stability | ESP8266 connections occasionally drop under congested 2.4 GHz environments; reconnection logic was added to the firmware loop |
| Cloud API latency | ThingSpeak enforces a minimum 15-second update interval on free-tier channels, limiting real-time resolution |
| Data synchronization | Coordinating simultaneous HTTP requests to two cloud platforms (Blynk and ThingSpeak) required careful sequencing to avoid request collisions |
| Dataset preprocessing | The sensor feed contained missing values across all feature columns; random realistic imputation was applied before SVM training could proceed |

---

## Conclusion

This project demonstrates a functional end-to-end remote health monitoring system that integrates embedded IoT hardware, cloud-based data visualization, and applied machine learning within a single cohesive architecture. The ESP8266 NodeMCU reliably acquires patient vitals and environmental parameters, transmitting them wirelessly to ThingSpeak and Blynk platforms that provide persistent logging and real-time mobile access respectively. Three independent SVM classifiers — trained on live IoT sensor feeds and achieving 96.8% accuracy each — add an intelligent prediction layer that simultaneously assesses health, hygiene, and environmental risk from a single set of patient readings.

The system validates the feasibility of deploying low-cost IoT infrastructure alongside conventional machine learning workflows in healthcare monitoring contexts. With additional sensor integration, wearable packaging, and deep learning models, the architecture described here provides a strong foundation for clinically meaningful remote patient care systems.

---

## References

> [1] Espressif Systems, *ESP8266 Technical Reference*, Version 1.7, 2020. [Online]. Available: https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf

> [2] Aosong Electronics Co., *DHT22 / AM2302 Datasheet*, 2022. [Online]. Available: https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf

> [3] Blynk Inc., *Blynk IoT Platform Documentation*, 2023. [Online]. Available: https://docs.blynk.io

> [4] MathWorks, *ThingSpeak IoT Analytics Platform Documentation*, 2023. [Online]. Available: https://www.mathworks.com/help/thingspeak

> [5] C. Cortes and V. Vapnik, "Support-vector networks," *Machine Learning*, vol. 20, no. 3, pp. 273–297, 1995.

> [6] F. Pedregosa et al., "Scikit-learn: Machine learning in Python," *Journal of Machine Learning Research*, vol. 12, pp. 2825–2830, 2011.

> [7] S. M. R. Islam, D. Kwak, M. H. Kabir, M. Hossain, and K.-S. Kwak, "The Internet of Things for health care: A comprehensive survey," *IEEE Access*, vol. 3, pp. 678–708, 2015.

---

<div align="center">

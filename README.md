# SENSE
Repository for the Project SENSE(Smart Environment &amp; Noise Surveillance Ecosystem for Modern Classrooms)
SENSE – Smart Environmental Node for Sustainable Education
Overview
SENSE is an IoT-based smart classroom monitoring system designed to create healthier and distraction-free learning environments. It uses low-cost sensors integrated with an Arduino UNO to track key environmental parameters such as temperature, humidity, air quality, noise levels, and occupancy in real time. The system provides instant alerts via a buzzer when thresholds are crossed, helping maintain optimal classroom conditions.

Key Features
Real-Time Monitoring of temperature, humidity, air quality, noise, and motion.

Instant Alerts via buzzer for high noise levels or poor air quality.
Low-Cost and Scalable design, suitable for classrooms and educational institutions.
Easy Setup using Arduino and basic sensors.
Future Ready – scope for cloud integration, LCD dashboards, and AI-based predictive analytics.

Hardware Components
Arduino UNO
DHT11 Sensor (Temperature & Humidity)
MQ-135 (Air Quality)
LM393 (Sound Level)
PIR Sensor (Motion Detection)
Buzzer, Jumper Wires, Breadboard

How It Works
Sensors continuously collect environmental data.
Arduino processes the readings and compares them with predefined thresholds.
If noise level > 640 or air quality reading > 350, the buzzer is triggered.
All sensor readings are displayed in real time on the Serial Monitor.
Note: Thresholds may vary depending on sensor quality and connections.

Future Improvements
Integration with LCDs or mobile apps for live visualization.
Cloud connectivity for remote monitoring and data logging.


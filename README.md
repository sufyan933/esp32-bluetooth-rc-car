<div align="center">
🚗 ESP32 Bluetooth & Wi-Fi RC Car
<p align="center">
<img src="[https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)" alt="ESP32">
<img src="[https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)" alt="Arduino">
<img src="[https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)" alt="C++">
<img src="[https://img.shields.io/badge/Bluetooth-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white](https://img.shields.io/badge/Bluetooth-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white)" alt="Bluetooth">
<img src="[https://img.shields.io/badge/Wi--Fi-000000?style=for-the-badge&logo=wifi&logoColor=white](https://img.shields.io/badge/Wi--Fi-000000?style=for-the-badge&logo=wifi&logoColor=white)" alt="Wi-Fi">
<img src="[https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)" alt="MIT License">
</p>
A Wi-Fi & Bluetooth controlled RC car built with an ESP32 microcontroller, an L298N dual H-bridge motor driver, and the Dabble app
</div>
<p align="center">
<img src="car.jpg" alt="ESP32 RC Car Build" width="650">


<em>Replace this image placeholder with a photo of your build saved at <code>docs/images/car.jpg</code></em>
</p>
🔎 At a Glance
| Parameter | Specification |
|---|---|
| Platform | ESP32 — Wi-Fi + Bluetooth |
| Language / Framework | C++ (Arduino framework) |
| Control Interfaces | Dabble Mobile App (Bluetooth) or Web Browser (Wi-Fi) |
| Motor Driver | L298N Dual H-Bridge Driver |
| Domain Areas | Embedded Systems · Robotics · Electronics |
📖 Overview
This project turns a standard RC car chassis into a smartphone-controlled robot using an ESP32 board. It features dual control capabilities:
 * Bluetooth Control: Utilizes the Dabble mobile app's interactive GamePad interface for real-time manipulation.
 * Wi-Fi Fallback: The ESP32 hosts an embedded web server, allowing control via any browser without app installation.
Motor direction and speed are regulated using an L298N dual H-bridge motor driver with PWM-based speed adjustment and soft-acceleration ramping to prevent inductive current surges.
✨ Features
 * 📱 Dual-Control Options: Drive via the Dabble app over Bluetooth or through an interactive web browser interface over Wi-Fi.
 * 🎮 Full Directional Movement: Directional control covering forward, backward, and pivot turns.
 * 🐢➡️🐇 Soft Speed Ramping: Gradual acceleration profiles protect hardware from sudden current spikes.
 * 🛑 Failsafe System: Automatic motor cutoff if the connection drops in Wi-Fi mode.
 * 🔌 Accessible Hardware: Built on widely available, beginner-friendly component hardware.
🧰 Hardware Used
| Component | Purpose |
|---|---|
| ESP32 Dev Board | Main microcontroller handling Wi-Fi & Bluetooth communications |
| L298N Motor Driver | Dual H-bridge driver regulating DC motor direction and speed |
| DC Gear Motors + Chassis | Robotic drive chassis and motorized wheels |
| 7.4V–12V Battery Pack | High-current power supply for DC motors |
| USB Power Bank | Independent power supply for the ESP32 |
🔌 Wiring
| ESP32 Pin | L298N Pin | Purpose |
|---|---|---|
| GPIO 27 | IN1 | Left motor direction |
| GPIO 26 | IN2 | Left motor direction |
| GPIO 25 | IN3 | Right motor direction |
| GPIO 33 | IN4 | Right motor direction |
| GPIO 14 | ENA | Left motor speed (PWM) |
| GPIO 32 | ENB | Right motor speed (PWM) |
| GND | GND | Common ground with battery negative |
> ⚠️ Power Separation Warning: Always power the ESP32 using its own USB power source separate from the motor battery pack. Sharing power directly without isolation can cause voltage drops and microcontroller brownout resets during heavy motor loads.
> 
🛠️ Software Setup
 * Download and install the Arduino IDE.
 * Add ESP32 Board Support: Navigate to File > Preferences, add the ESP32 URL, and install the ESP32 board package via Boards Manager.
 * Install the DabbleESP32 library via Sketch > Include Library > Manage Libraries.
 * Install the Dabble App from the Google Play Store or Apple App Store.
 * Open the .ino sketch file from this repository and upload it to your ESP32 board.
🎮 How to Drive
 * Launch the Dabble app on your mobile device and connect to the car over Bluetooth.
 * Select and open the GamePad module.
 * Tap and hold the D-pad controls to drive; release to stop.
🚀 Future Improvements
 * [ ] Integrate ultrasonic sensors for autonomous obstacle avoidance
 * [ ] Upgrade to ESP32-CAM module for live video streaming
 * [ ] Implement virtual joystick controls instead of D-pad for fine steering control
 * [ ] Add onboard battery voltage monitoring
📄 License
This project is licensed under the MIT License — free to use, modify, and share.
🙋 Author
Muhammad Sufyan
Electrical Engineering, Pakistan Institute of Engineering and Applied Sciences (PIEAS)

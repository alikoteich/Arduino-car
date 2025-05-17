# 🚗 Arduino Smart Car

A feature-rich, dual-mode robotic car built on the Arduino platform. Control it manually via Bluetooth or let it drive autonomously with real-time obstacle avoidance!


---

## ✨ Features

- **Dual Control Modes**  
  - 📱 Bluetooth manual control using a mobile app  
  - 🤖 Autonomous obstacle detection and avoidance

- **Extra Functionalities**
  - 🔦 Laser module for visual cues  
  - 🔊 Buzzer for audible alerts  
  - 🛑 Emergency stop and collision prevention  
  - 🕹️ Manual override anytime

---

## 🔧 Hardware Components

| Component               | Quantity | Description                     |
|------------------------|----------|---------------------------------|
| Arduino Uno            | 1        | Microcontroller board           |
| L298N Motor Driver     | 1        | Dual H-Bridge motor driver      |
| HC-05 Bluetooth Module | 1        | Wireless serial communication   |
| HC-SR04 Ultrasonic     | 1        | Distance measurement sensor     |
| SG90 Servo Motor       | 1        | Positions ultrasonic sensor     |
| DC Motors (12V)        | 4        | Car propulsion                  |
| 9V Battery             | 1        | Power source                    |
| Laser Module           | 1        | Visual pointer                  |
| Piezo Buzzer           | 1        | Sound alert system              |

---

## ⚙️ Installation

1. **Open the Project in Arduino IDE**  
   Open `arduino_car.ino` inside the Arduino IDE.

2. **Wire the Components**  
   Refer to the [Wiring Guide](#-wiring-guide) below for pin assignments.

3. **Upload the Sketch**  
   Select the correct port and board (Arduino Uno), then click **Upload (→)**.

---

## 🔌 Wiring Guide

| Component            | Arduino Pin |
|----------------------|-------------|
| Motor Driver IN1     | 5           |
| Motor Driver IN2     | 6           |
| Motor Driver IN3     | 9           |
| Motor Driver IN4     | 10          |
| Ultrasonic Trigger   | 3           |
| Ultrasonic Echo      | 13          |
| Servo Motor (SG90)   | 11          |
| Buzzer               | 2           |
| Laser Module         | 12          |

---

## 🕹️ Usage

### 📲 Bluetooth Control Mode

Use a Bluetooth terminal app and send the following single-letter commands:

| Command | Action             |
|---------|--------------------|
| `F`     | Move Forward        |
| `B`     | Move Backward       |
| `L`     | Turn Left           |
| `R`     | Turn Right          |
| `S`     | Stop                |
| `V` / `v` | Buzzer On / Off   |
| `U` / `u` | Laser On / Off    |

### 🤖 Autonomous Mode

1. Send **`W`** to switch to self-driving mode.  
2. Send **`w`** to return to manual mode.

#### Behavior Sequence:
- Move forward by default  
- If an obstacle is detected within 30 cm:  
  - Pause  
  - Scan surroundings using servo-mounted sensor  
  - Turn toward the direction with more clearance  
  - Resume movement

---



## 🙌 Credits

- Inspired by classic Arduino obstacle avoidance bots  
- Bluetooth control based on HC-05 communication tutorials  

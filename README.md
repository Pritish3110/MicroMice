# 🐭 MicroMice Maze Solver 🚗

An autonomous **Micromouse maze-solving robot** project using **Flood Fill algorithm**, designed for both **Makaron Maze Simulator (MMS)** and **real-world Arduino hardware** on an 8x8 maze.

<div align="center">

![GitHub stars](https://img.shields.io/github/stars/Pritish3110/MicroMice?style=social)
![GitHub forks](https://img.shields.io/github/forks/Pritish3110/MicroMice?style=social)
![GitHub issues](https://img.shields.io/github/issues/Pritish3110/MicroMice)
![GitHub last commit](https://img.shields.io/github/last-commit/Pritish3110/MicroMice)

</div>

---

## 📁 Project Structure

```
MicroMice/
├── main.c           # Flood Fill algorithm for simulator
├── api.c            # Makaron Maze Simulator communication functions
├── api.h            # API declarations for simulator
├── mybot.exe        # Compiled simulator bot
├── mms/             # Makaron Maze Simulator executable files
├── ArduinoCode/     # Final Arduino implementation (8x8 grid logic)
├── assets/          # Project images and documentation
└── README.md        # Project documentation
```

---

## 🧠 Project Summary

This Micromouse robot implements intelligent maze navigation through:

- **Flood Fill algorithm** for efficient pathfinding
- **3-pass solving strategy**:
  1. **Start ➝ Goal**: Explore & record wall positions
  2. **Goal ➝ Start**: Return journey & verify mapping
  3. **Start ➝ Goal**: Execute fastest known path

- **Dual implementation approach**:
  - C-based simulation via Makaron Maze Simulator
  - Arduino Uno-based real hardware for 8x8 physical maze

---

## 🧪 Simulator Instructions (MMS - Micromouse Simulator)

### Prerequisites
- GCC compiler installed (MinGW for Windows users)
- Micromouse simulator downloaded

### Setup Steps

1. **Clone this repository**:
   ```bash
   git clone https://github.com/Pritish3110/MicroMice
   cd MicroMice
   ```

2. **Download the Micromouse simulator**:
   ```bash
   git clone https://github.com/mackorone/mms
   ```

3. **Configure the simulator**:
   - Run the simulator
   - Click the "+" button to configure a new algorithm
   - Enter the config for your algorithm:
     - **Name**: MicroMice Flood Fill
     - **Directory**: Path to your project folder
     - **Build command**: `gcc -o mybot main.c api.c`
     - **Run command**: `./mybot` (Linux) or `mybot.exe` (Windows)

4. **Run the simulation**:
   - Click the "Run" button to start maze solving

### Platform-Specific Examples

#### Windows Configuration:
- **Build command**: `gcc -o mybot.exe main.c api.c`
- **Run command**: `mybot.exe`

#### Linux (Ubuntu) Configuration:
- **Build command**: `gcc -o mybot main.c api.c`
- **Run command**: `./mybot`

### Important Notes
- **Windows users**: May need to download and install [MinGW](https://www.mingw-w64.org/) for GCC compilation
- **Communication**: All simulator communication is done via stdin/stdout - use stderr for debug output
- **API Reference**: Complete descriptions of all available API methods can be found at [mackorone/mms#mouse-api](https://github.com/mackorone/mms#mouse-api)
- **Algorithm**: The implementation uses flood fill algorithm (not simple left wall following)

---

## 🤖 Hardware Implementation (Arduino Version)

### 🧩 Components Required

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino UNO | 1 | Main microcontroller |
| L298N Motor Driver | 1 | Motor control |
| N20 Motors + Wheels | 2 | Mobility |
| IR Sensors (Digital) | 3 | Wall detection (Left, Front, Right) |
| Ultrasonic Sensor | 1 (optional) | Front obstacle detection |
| 18650 Batteries (7.4V) | 2 | Power source |
| LM7805 Regulator | 1 | Regulate 7.4V → 5V |
| Capacitors (100µF, 10µF) | 2 each | Voltage stability |
| Castor Ball | 1 | Balance |
| Slide Switch | 1 | Power toggle |

### ⚡ Wiring Configuration

| Component | Arduino Pin | Description |
|-----------|-------------|-------------|
| IR_LEFT | D2 | Detects left wall |
| IR_FRONT | D3 | Detects front wall |
| IR_RIGHT | D4 | Detects right wall |
| Motor IN1-IN4 | D5–D8 | Motor control signals |
| ENA (Right PWM) | D10 | Enable right motor |
| ENB (Left PWM) | D9 | Enable left motor |
| LM7805 Regulator | - | 7.4V → 5V conversion |
| Capacitors | - | 100µF & 10µF noise smoothing |

⚠️ **Important**: Do NOT connect the L298N's onboard 5V output to Arduino 5V when using external voltage regulation.

### 🔁 Arduino Logic Flow

- Simulates **flood fill** logic in an 8x8 grid system
- Moves **cell-by-cell** with real-time IR sensor decision making
- Stores and dynamically updates wall data for each visited cell
- Computes shortest path using stored flood map data
- Adaptable logic designed for minimal hardware requirements

---

## 🎯 Project Milestones

- [x] Implement flood fill algorithm
- [x] Successfully run simulation in MMS
- [x] Design and build real-world 8x8 maze
- [x] Create hardware layout in Tinkercad
- [x] Flash Arduino with working maze logic
- [x] Achieve 3-pass maze solving capability
- [ ] Optimize speed control and navigation (future enhancement)

---

## 📸 Project Gallery

*Place images in `/assets` folder and reference them here:*

- Circuit diagram and wiring layout
- Physical robot construction
- Maze solving demonstration
- Simulation screenshots

---

## 📚 Technical References

- [mackorone/mms - Micromouse Simulator](https://github.com/mackorone/mms)
- [Mouse API Documentation](https://github.com/mackorone/mms#mouse-api)
- [Flood Fill Algorithm – Wikipedia](https://en.wikipedia.org/wiki/Flood_fill)
- [Arduino + L298N Motor Driver Guide](https://create.arduino.cc/projecthub/robocircuits/how-to-use-l298n-motor-driver-b124ac)
- [Micromouse Competition Rules](https://www.ieee.org/conferences_events/conferences/conferencedetails/index.html?Conf_ID=35815)
- [MinGW Installation Guide](https://www.mingw-w64.org/downloads/)

---

## 🚀 Getting Started

### For Simulation
1. Clone this repository
2. Install GCC compiler
3. Follow simulator instructions above

### For Hardware
1. Assemble components as per wiring diagram
2. Upload Arduino code to microcontroller
3. Build 8x8 physical maze
4. Test and calibrate sensors

---

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

## 📄 License

```
Copyright (c) 2024 Pritish Bhatasana

Licensed under the MIT License (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://opensource.org/licenses/MIT

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```

---

## 🙏 Acknowledgments

<div align="center">

### **Special Thanks**

**Robotics & AI Community**  
*For open-source algorithms and continuous learning resources*

**Arduino & Maker Community**  
*For hardware tutorials, libraries, and troubleshooting support*

**mackorone/mms - Micromouse Simulator Team**  
*For providing an excellent testing platform and comprehensive API documentation*

---

### **Connect With Me**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://linkedin.com/in/pritish-bhatasana)
[![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Pritish3110)
[![Email](https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:pritish.bhatasana@example.com)

---

### **Project Stats**

![Language](https://img.shields.io/badge/Language-C/C++-blue?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Arduino-green?style=for-the-badge)
![Algorithm](https://img.shields.io/badge/Algorithm-Flood_Fill-red?style=for-the-badge)

**Made with ❤️ for autonomous robotics and maze solving**

</div>

---

## 📚 Additional Resources

- [Arduino IDE Documentation](https://www.arduino.cc/en/Guide/Environment)
- [C Programming for Embedded Systems](https://www.embedded.com/c-programming-for-embedded-systems/)
- [Micromouse Tutorials](https://www.youtube.com/playlist?list=PLjzuoBhdtaXOoqkzRdnpFVkdcAfr8VaXv)
- [Robotics Programming Fundamentals](https://www.coursera.org/learn/robotics-programming)
- [Pathfinding Algorithms Visualization](https://www.youtube.com/watch?v=JtiK0DOeI4A)

---

<div align="center">

**🚀 Ready to navigate any maze autonomously!**

*Built with modern flood fill algorithms for competitive robotics*

</div>

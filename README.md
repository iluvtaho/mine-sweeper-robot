# mine-sweeper-robot

**Mine sweeper robot built to strengthen and apply understanding of concepts (Electrical and Control Systems, Autonomous Robotics, and Mechanical Design) and  learned during self-directed study of MITOpenCourseWare's Undergraduate Course: "Introduction to Robotics"**

## Overview
<img src="assets/videos/Demo GIF.GIF" alt="Demo GIF here" width="300"/>

**Goal and Rules:**  The goal of this project to produce a robot capable of searching for hidden metal disks (“mines”) in a open space. Students design and implement a search algorithm that lets the robot hunt autonomously, and when a mine is found to pause on top of it. Identify as many mines as possible within a given time, say 2 minutes. Every time a fake mine is found, the robot must stop at that position and turn the buzzer on. If the mine is a newly found one, a credit point is given to the project team. If the mine has already been found by the robot, no credit is given. The robot resumes searching a mine.

**The Minefield (Modified to suit available resources):** About ~~10~~ 5 metallic fake mines are buried in a ~~12’x12’~~ 90x210cm minefield, as shown in the photo below. The minefield is surrounded by a wall. A start point is marked in the minefield. Each trial, the robot at the start point for mine search. 

<img width="493" height="300" alt="image" src="https://github.com/user-attachments/assets/633eb7ce-4da2-48f5-91c0-7175061764d0" />

## System Overview
**Primary Function:** Executes an autonomous side-to-side sweep pattern, detects metallic/conductive simulated hazards via an inductive proximity switch, triggers visual/audible alarms, and resumes sweep execution.
**Obstacle Avoidance:** Infrared Obstacle Avoidance sensors located on each side of the front detect physical barriers and signal the robot to reposition automatically
**Control Method:** Use of NodeMCU-32S to run a fully autonomous closed loop finite state machine without outside control/influence

### State Machine 

<img width="1567" height="667" alt="image" src="https://github.com/user-attachments/assets/dab829b8-b491-4a50-83df-1718f96e5d18" />

The robot drives in a side-to-side motion to maximize sweep area and to compensate for the inductive proximity switches small (8 mm) sensing radius.

## Bill of Materials

| Component | Model / Type | Function |
| :--- | :--- | :--- |
| **Microcontroller** | NodeMCU-32S | Executes state machine, motor timing, and sensor interrupts |
| **Mine Detection Sensor** | Inductive Proximity Switch LJ18A3-8-Z/BX – NPN NO 8mm Detection | Non-contact detection of metallic target zones / simulated mines |
| **Obstacle Avoidance** | IR Obstacle Avoidance Sensor | Detects obstacles within 6 cm |
| **Alert System** | Active Piezo Buzzer | Audible indicator during mine detection |
| **Motor Driver** | L298N Dual H-Bridge Motor Driver | H-Bridge dual DC motor drive control |
| **Drive Motors** | TT DC Motor 6v | Drive motors |
| **Power** | 4x AA Alkaline Batteries (6v), 9v Alkaline Battery | 4x AA batteries power the microcontroller, 2 obstacle sensors, motor driver, and drive motors |

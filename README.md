# mine-sweeper-robot

**Mine sweeper robot built to strengthen and apply understanding of concepts (Electrical and Control Systems, Autonomous Robotics, and Mechanical Design) learned during self-directed study of MITOpenCourseWare's Undergraduate Course: "2.12 Introduction to Robotics"**

## Overview
<img src="assets/videos/Demo GIF.GIF" alt="Demo GIF here" height="300" width="300"/>

### Course Specification & Objectives

> **Goal and Rules:**  
> *"The goal of this project to produce a robot capable of searching for hidden metal disks (“mines”) in a open space. Students design and implement a search algorithm that lets the robot hunt autonomously, and when a mine is found to pause on top of it. Identify as many mines as possible within a given time, say 2 minutes. Every time a fake mine is found, the robot must stop at that position and turn the buzzer on. If the mine is a newly found one, a credit point is given to the project team. If the mine has already been found by the robot, no credit is given. The robot resumes searching a mine."*
>
> — **Source:** *MIT OpenCourseWare: 2.12 Introduction to Robotics (Lab 3)*

---

### Experiment Environment Adaptations
To adapt the original MIT OCW specification to locally available resources and workspace constraints, the experimental setup was modified as follows:

* **Original Specification:** 10 metallic mines in a 12' x 12' arena enclosed with 6" cushioned walls and rounded corners.
* **Modified Setup:** 5 metallic mines in a 90 cm x 210 cm enclosed minefield bounded by physical walls and sharp corners. 

<img width="493" height="300" alt="image" src="https://github.com/user-attachments/assets/633eb7ce-4da2-48f5-91c0-7175061764d0" /> (Insert photo of used minefield)

## System Overview
**Primary Function:** Executes an autonomous side-to-side sweep pattern, detects metallic/conductive simulated hazards via an inductive proximity switch, triggers audible alarms, and resumes sweep execution. <br>
**Obstacle Avoidance:** Infrared Obstacle Avoidance sensors located on each side of the front to detect physical barriers and signal the robot to reposition automatically <br>
**Control Method:** Use of NodeMCU-32S to run a fully autonomous closed loop finite state machine without outside control/influence

> *Design note: The robot drives in a side-to-side motion to maximize sweep area and to compensate for the inductive proximity switches small (8 mm) sensing radius.*

### State Machine 

<img width="1567" height="667" alt="image" src="https://github.com/user-attachments/assets/dab829b8-b491-4a50-83df-1718f96e5d18" />

## Bill of Materials

| Component | Model / Type | Function |
| :--- | :--- | :--- |
| **Microcontroller** | NodeMCU-32S | Executes state machine, motor timing, and sensor interrupts |
| **Mine Detection Sensor** | Inductive Proximity Switch LJ18A3-8-Z/BX – NPN NO 8mm Detection | Non-contact detection of metallic target zones / simulated mines |
| **Obstacle Avoidance** | IR Obstacle Avoidance Sensor | Detects obstacles within 6 cm |
| **Alert System** | Active Piezo Buzzer | Audible indicator during mine detection |
| **Motor Driver** | L298N Dual H-Bridge Motor Driver | H-Bridge dual DC motor drive control |
| **Drive Motors** | TT DC Motor 6v | Drive motors |
| **Power** | 4x AA Alkaline Batteries (6v), 9v Alkaline Battery | 4x AA batteries power the microcontroller, 2 obstacle sensors, motor driver, and drive motors. 9v Battery powers the inductive proximity switch (6-36v operating voltage)|

## Code Structure

[*View Final C++ Code*](./assets/code/Metal_Detecting_Robot.ino)

## Trials and Iterations

To optimize the search algorithm and minimize the time required to clear all 5 targets, the system underwent five trials before a final sixth run. 

> *Note: Due to hardware constraints (8mm detection radius and compact chassis size), the physical minefield scale was adapted from the original MIT OCW specifications. Trial videos are accelerated 5x for repository optimization. [Unedited real-time footage is available here](https://drive.google.com/drive/folders/1LTC-wA61IuTCIbSAw-TUQX8wArLBp5uN?usp=sharing).*

### 1st Trial:

[*First Trial Video*](./assets/videos/First%20Trial%20(5x%20speed).mp4)

* **Performance:** The robot successfully cleared the minefield in **4 minutes and 34 seconds**.
* **Trial Observation:** While baseline obstacle avoidance functioned, the robot occasionally became trapped in "avoidance loops" in corners. Furthermore, the wheels physically snagged on the raised edges of the metallic targets, inadvertently pulling the robot directly over the mine. These problems caused lots of time to be wasted, especially the loop traps.
* **Root Causes:** 
  1. The alternating `millis()` timer logic for turning randomly selected directions, leading to repetitive corner trapping. 
  2. Target disks were not mounted flush with the arena floor, causing mechanical interference.
* **Engineering Iteration:** 
  * **Software:** Implemented a deterministic escape sequence in the state machine—upon reversing from an obstacle, the robot now forces a turn in the *opposite* direction of its previous approach. Pivot delay times were kept tight to prevent rear-collisions. Lowered the PWM value to the piezo buzzer to reduce acoustic harshness during alerts.
  * **Hardware:** Secured the metallic targets to the arena floor to ensure sensor triggers were based purely on inductive detection, not mechanical snagging.

# Pied-piper-B1

Sound-and-Light-Seeking Robot

This repository contains the code, documentation, and resources for a robot designed to locate a speaker playing music and a bright red LED light fixture. Built for a group project where it will compete against other teams who have built similar robots in an olympiad style competition, this robot uses sound and light detection to navigate and stop as close as possible to its target without touching it.

Project Overview

The robot starts 1 to 1.5 meters away from a speaker, which plays a music track, and a light fixture with a bright red LED positioned in front of it. The robot’s starting orientation is randomly chosen by a judge, adding an exciting twist to the challenge. The goal is to locate and approach the target (speaker + LED) before the song ends, stopping as close as possible to the light fixture without contact. The final distance is measured from a top-down (bird’s-eye) view, and the robot must stay within a ±60° approach angle while avoiding protrusion over the speaker or light fixture.

This project uses an Arduino Uno with a Parallax Boe Shield, integrating sensors and servo motors to achieve reliable sound and light tracking. Additional localization techniques can be implemented for enhanced accuracy.



Features:

- Sound Localization: Detects and follows a music track played through a speaker using the MAX4466 microphone module.

- Light Tracking: Identifies and approaches a bright red LED using the ADPS9960 sensor.

- Dual-Mode Operation: Supports independent detection of sound, light, or both, selectable via a switch.

- Visual Feedback: Onboard indicators (e.g., LEDs) show when the robot is detecting sound, tracking the LED, or stopped.

- Precise Movement: Servo motors ensure smooth navigation within the ±60° approach angle.

- Obstacle Avoidance: Stops without touching the speaker or light fixture, adhering to competition rules.

Hardware Requirements

Microcontroller: Arduino Uno

Shield: Parallax Boe Shield

Sensors:
MAX4466: Electret microphone amplifier for sound detection

ADPS9960: Gesture, proximity, and color sensor for LED tracking

HC-SR04: Ultrasonic sensor for distance measurement and collision avoidance

Actuators: Continuous rotation servo motors (e.g., Parallax servos)

Indicators: LEDs or other visual cues (user-defined)

Power: Battery pack compatible with Arduino and Boe Shield

Chassis: Boe-Bot compatible frame




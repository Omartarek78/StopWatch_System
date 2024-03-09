# StopWatch_System

https://github.com/Omartarek78/StopWatch_System/assets/108580462/763b8fd5-61d6-45ff-a702-6a656bd62267






This project implements a Stop Watch system using the ATmega32 Microcontroller with a 1MHz frequency. The system is designed to provide accurate timekeeping and features a user-friendly interface with six Common Anode 7-segment displays. The project utilizes Timer1 in ATmega32 with CTC mode for precise time measurement.

Specifications
1. Microcontroller: ATmega32 with a frequency of 1MHz.
2. Timer Configuration: Timer1 is configured in CTC mode for accurate timekeeping.
3. Display: Six Common Anode 7-segment displays are used, employing multiplexing for efficient control.
4. Multiplexing Technique: Utilizes one 7447 decoder for all 7-segments, with enable/disable control for each 7-segment using NPN BJT transistors.

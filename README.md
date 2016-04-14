# Sensor to CAN Bus Remote IO PCB
Many wires in, two wires out. 24 input channels on the board interface with analog and digital sensors. Performs analog to digital to CAN protocol conversion.

## PCB Design

- Microcontroller: RM42L432BPZT
- Input Stage: Filtering, Voltage scaling, Circuit Protection
- Output Stage: 2 Isolated CAN transceivers
- Power: 5V board power, LDO supply creates 3.3V and 1.2V

![](/output/photos/pcb.png)
![](/output/photos/pcb_top.png)
![](/output/photos/pcb_bottom.png)

## [Code Repo](https://github.com/alexbhandari/RM42-CAN-Sensor-Code)

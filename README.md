# Sensor-monitored 12vhpwr shutdown

This project adds a killswitch to cut power to a device connected to a Netio 4C PDU, based off values received from DS18B20 temperature sensors and relayed via an Arduino.

I am using this setup to monitor temperatures surrounding the 12vhpwr plug of my 4090 and to shutdown power to the PC in the event of a possible melting connector, preventing further damage.

## Hardware Used
- Arduino Leonardo
- DS18B20 temperature sensors
- Sparkfun mini solderable breadboard
- Netio 4C PDU
 
### Notes on hardware:
There are fake versions of the DS18B20 sensors so buy from a reputable electronics seller. The fakes apparently work individually but do not communicate on the bus the same way and cause problems using multiple sensors.

The Netio 4C is unfortunately a discontinued model. The 4C runs the Lua scripting engine but the new models don't so you can't write your own scripts. They use an in-built GUI with conditions/rules and sell a separate natively-supported temperature sensor that connects straight into the PDU's terminal block so no need to interface with an Arduino. This would probably be easier and less-fidgety but I haven't used it so can't confirm it works, and I don't know how many sensors can be run concurrently. You'll also need an IEC 14 to 13 power plug for this PDU.

The listed breadboard has traces built inside the PCB but they can't easily be seen externally, I've added the manufacturer's schematic. There are no power rails though, consider a bigger/different one with traces for pwr for easier use.

## Wiring schematic for DS18B20 temp sensors on Arduino
I heavily referenced this guide to learn how to use these sensors: https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/

There is a wiring diagram for both single and multiple sensor versions. 

![wiring diagram for arduino](/assets/images/ds18b20_arduino_multiple.webp)

To summarise:
- Wire the breadboard to the arduino on the 5V pin, GND pin and pin 4 as the data line
- You'll need a 4.7k Ohm pull-up resistor, my sensors came with one
- I'd suggest not using parasite mode with four sensors, wiring in the 5V line is more reliable

## Sparkfun solderable breadboard layout
![breadboard layout](/assets/images/breadboard.jpg)


## Wiring between PDU and arduino

- Wire the arduino to the PDU on a GND pin, and pins 0/1 RX/TX.
  -  Cross over the receive/transmit lines, the arduino's TX needs to go to the PDU's RX and vice versa
 
## Netio 4C PDU settings
![pdu settings](/assets/images/pdu_actions.png)

## Demo of real-world application of setup
https://www.youtube.com/watch?v=I-UHbSZBi1A

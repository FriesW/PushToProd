# Assembly Guide

Want your own PushToProd button? This guide will step you through assembly.

Assembling the PushToProd button is relatively easy. The most difficult
part is soldering wires to the LEDs. Only basic soldering skills are needed.
No knowledge of electronics or programming is required. All adhesion is done
with hot glue, and there are no "waiting" steps.

Due to the wide array of laser cutters available, this guide does not go
through the steps of engraving and cutting materials. It is assumed that is
already done. That said, the pdf files in the repository are built to work
with Epilog software, so it should be straightforward with Epilog systems.


## Contents

* [Supplies](#supplies)
    * [Tools needed](#tools-needed)
    * [Parts needed](#parts-needed)
* [Assembly](#assembly)
    * [Overview](#overview)
    * [Detail](#detail)


<br>

---

<br>



# Supplies

## Tools needed

You will need:
1. Soldering iron
1. Hot glue gun
1. Wire strippers
1. Screwdriver
1. Scissors
1. Sandpaper, 220 grit or finer

Recommended to also have:
1. Mini clamps
1. Solder sucker
1. Multimeter

## Parts needed

You will need:
1. Laser cut parts
    * Wood or plywood
        * 5mm thickness. Can use different thickness if drawings are updated.
        * Six box pieces
    * Acrylic
        * About 2.4 mm thick, but doesn't really matter
        * Front panel & two small back pieces
1. Solder & Wire
    * Also flux, if you have it
1. [This button](https://www.amazon.com/Uxcell-a13071000ux0939-Push-Button-Switch/dp/B00EDMIYCW/) or similar (30 mm panel mount hole)
1. [WS2812B LEDs](https://www.amazon.com/BTF-LIGHTING-WS2812B-Heatsink-10mm3mm-WS2811/dp/B01DC0J3UM/) (aka NeoPixels)
1. Teensy LC
    * [From PJRC](https://www.pjrc.com/store/teensylc.html)
    * [From OSH Park](https://store.oshpark.com/products/teensy-lc)
1. Micro-USB cable
1. Bolts & Washers
    * Four 4mm diameter bolts, two no longer than 12 mm
    * Four matching fender washers, per taste of visual appearance
1. Quilt batting
    * Used for light diffusion
1. Non-skid shelf liner
    * Used as feet, provide friction between bottom and table
    * [Example product](https://www.amazon.com/Non-Skid-Drawer-Cabinet-Shelves-Non-Slip/dp/B00IXYIWC8)


<br>

---

<br>


# Assembly

## Overview

1. Program, solder, and mount electronics
1. Treat and place small acrylic backing pieces
1. Build box, except bottom
1. Mount front acrylic, bolts, and button
1. Add diffusion, connect button, mount bottom

## Detailed

### Program, solder, and mount electronics

#### Program

First, lets prepare the microcontroller. Download and install the
[Arduino IDE](https://www.arduino.cc/en/Main/Software) and
[Teensyduino](https://www.pjrc.com/teensy/teensyduino.html)
software. Open the `PushToProd.ino`. In Arduino, go to tools and assure
the following fields are set:
* Board: Teensy LC
* USB Type: Serial + Keyboard + Mouse + Joystick
* CPU Speed: 48 MHz
* Optimize code: smallest *(might not have this field)*

Next, plug the Teensy into your computer with the USB cable. If the Teensy is new,
you should see the on-board LED blink. Click the upload arrow in the
Arduino IDE to load the code onto the Teensy, and follow the on-screen steps.
If all goes well, you should see "Success" in the Teensy loader window.

Unplug the Teensy, and prepare your soldering iron.

#### Solder

First we will prepare the Teensy. The LEDs we are connecting expect 5V, but the Teensy is
a 3.3V microcontroller. However, the Teensy has one built in 5V pin. Unfortunatley, due to
technical reasons, we cannot use this pin directly. The software must use a different pin,
which we will manually wire up to the 5V capabile pin.

Thus, prepare and solder a short piece of (insulated) wire that will jump from
the side breakout of pin 17 to the interior breakout of pin 24.

Next, we will prepare the LEDs.

WS2812 LEDs are digital LEDs, which have a data in and a data out.
The LEDs are chained in series, such that the data output of each LED
passes into the input of the next LED. In this way, the LEDs are "addressed"
by the order they are wired, and thus can each individually be commanded to
display a particular color.

First build up two strings of three LEDs each. The goal is to have three LEDs
bordering each side of the gap on the bottom of the box. They should be as close
to the opening as possible, for clearances needed later in the build.

I recommend soldering the middle data wire first, and then the outside power lines.
The power lines can short together across the LED, but the data line cannot.

Once you build the two strings of three LEDs, check for shorts if you have a multimeter.
Put the meter in "Ohms" mode. If a ranged meter, put it in the most sensitive mode.
The probes should be attached to the LEDs counter to the LED polarity, such that no current
flows through the LEDs (since they are diodes). This means that any resistance seen (versus open circut) is caused by a short.

Thus, place the black probe on the positive rail, and the red probe on the negative
rail. This should read open circuit or a resistance in megaohms. Also try negative rail
to data line, and positive rail to dataline. Additionally, you can check your work
"horizontally" instead of "vertically". Place the probes on each end of the positive
rail. Since this should conduct, the ohm reading should be very low. Repeat with the negative rail.

Once confident all connections are correct, wire the two short strings together with about
4.5" of wire. Then, wire the start of the string (signified by the only LED with no connected
data input) to the Teensy with around 3.5" of wire. You will want the data line wire to be
shorter then the power rail wires, due to where it will connect on the Teensy.

The LED data input should go to the 5V capabile pin 17 on the Teensy, at te bottom of the board.
Wire the ground and 5V rail of the LEDs to the ground and 5V pins of the Teensy, which are
the top most pins by the USB connector.

Finally, check again for shorts. Once confident, plug the Teensy in to USB power. You should
see the LEDs light up and begin to cycle through RGB colors! Watch each LED go through an
entire cycle and make sure they all light up each fundamental color: red, green, and blue.
I had a bogus LED that was missing green!

If all LEDs pass, then pat yourself on the back! You've just completed the most difficult
part of this project. Put the iron away, we're moving on (though you'll need it later)!

#### Mount

Move to the liquid plastic extruder (hot glue gun). We'll be gluing down the LEDs to the bottom panel
with the hot glue gun. Throughout the entire process, keep in mind the constructon of the box: all
of the walls sit on top of the bottom piece. Thus, we must keep the outer 5mm clear on each side of
the bottom.

Start gluing with the first LED in the bottom right corner and work clockwise.
Place a dab of hot glue under each LED, next to the bottom opening, and then press the LED in.
Once you've done one side, we need to carefully bend the wire in a vertical loop. This
loop will sit against the back wall once the enclosure is fully built.

When bending the wire, use your nail and a firm grip to take all the forces of the bend.
Try your best to keep any force off of the solder joints on the LEDs, as this could break the
joint or rip off a PCB pad. Using your nail allows you to gain a very sharp corner in the wire.
Practice and figure out a technique that works for you. You might also plan ahead and pre-emptivley
place bends before gluing.

Once all six LEDs are glued down, we need to deal with the wire between the Teensy and first led.
We want to bend the wire around towards the center, and then apply copious glue. This glue
acts like a strain relief, so movement of the Teensy and its wires doesn't affect the LEDs.

> The extra loops of wire in the photo are to even out the wirelengths coming from the Teensy.
> They have no functional purpose.

Finally, plug in the Teensy, and check that all the LEDs still light up!


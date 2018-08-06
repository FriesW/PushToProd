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
1. Mount front acrylic, bolts, button, and diffusion
1. Connect button, mount bottom, and feet

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
joint or rip off a PCB pad. Using your nail allows you to make a very sharp corner in the wire.
Practice and figure out a technique that works for you. You might also plan ahead and pre-emptivley
place bends before gluing.

Once all six LEDs are glued down, we need to deal with the wire between the Teensy and first led.
We want to bend the wire around towards the center, and then apply copious glue. This glue
acts like a strain relief, so movement of the Teensy and its wires doesn't affect the LEDs.

> The extra loops of wire in the photo are to even out the wirelengths coming from the Teensy.
> They have no functional purpose.

Finally, plug in the Teensy and check that all the LEDs still light up!


### Treat and place small acrylic backing pieces

You'll need the two small acrylic pieces and sandpaper. The goal of this step
is to make the acrylic appear frosted.

Acrylic comes with a protective plastic coating on each side. Peel the coating off of both sides
and then begin sanding. I recommend sanding in a figure eight pattern, to prevent uniform scratches.
For me each piece needed 200 cycles, with a washing in the middle. Your milage may vary.

Once the pieces are frosted to your liking, cleaned, dry, and free of dust, we'll mount them.
The pieces go behind the lettering in the faceplate piece, with the cutout corners of the acrylic
pieces directed towards the bolt holes. Place the acrylic pieces on the back side of the faceplate,
frosted side down, smooth side up. Then place a bead of hot glue around the perimiter.

Placing the smooth side up has a big advantage: unless you are a hot glue ninja, you will drag a
string of hot glue across the top of the acrylic at some point. It is much easier to remove
from the smooth surface (by rubbing it) then to remove it from the scratched surface.


### Build box, except bottom

Gather the remaining wall pieces of the box, hot glue gun, and clamps if you have them.

Clamp the wooden faceplate horizontally, with the majority of the clamp surface pointing
past the back of the faceplate. This provides a flush, right angle surface for the side pieces
to be placed against. Push one of the side pieces into place against the clamp, and then lay down
a bead of hot glue. Keep a margin around each screw hole and corner of the faceplate piece
free of glue. We will need the space later for adding additional walls and the bolts.
Complete both angled side walls.

Remove the clamps and now move to the back of the box. If tolerances are correct, sliding in the
back wall should be a tight fit, but still fit. Note that there will be a visible gap between
the top of the back wall and the bottom of the faceplate. However, you should not be able to see
though this gap.

Once you get it flush with the back and bottomed out against the faceplate,
clamp the two sidewalls through the bottom of the backpiece. Use additional clamps as necessary
to assist with alignment. Glue it up on all three edges, again keeping away from the
corners and bolt holes.

Repeat the same process with the front wall. Note that there should be no visible gap
from the outside, as the void is now on the inside of the box. This means the long joint
for the front wall is very "glue thirsty."


### Mount front acrylic, bolts, button, and diffusion

#### Mount front acrylic and bolts

Place the box bottom down, with the faceplace facing up. Peel off the protective coatings from
the front acrylic piece and place it on top. Be extra careful not to place finger prints on
the side which will be facing the wood. This will be permanently mounted, so impossible to clean.
Insert the four bolts and washers. Use the short bolts on the top end, as it has the
tighest clearances inside.

Now, carefully flip over the box, such that none of the bolts fall out. The box should now
be sitting on the table through the four bolt heads. Without picking up the box, flood each corner
of the box with hot glue. This will hold the bolts in, reinforce the corners of the box, and
keep the faceplate acrylic aligned. Make sure that the glue does not flow on top of the
interior acrylic.

#### Mount button

Prepare the button by attaching around 4" to the normally open (NO) contacts. If unsure, use your
multimeter in ohms or continuity mode and find the pair of contacts which are connected only
when the button is pressed. The normally closed (NC) contacts can also be used, but then you'll
have to update the code.

If you have the Uxcell button from Amazon the NO contacts are the two bottom screw terminals.
You'll also have to remove the two rubber washers, as they add too much thickness.

Pass the button through the hole, screw on the faceplate nut, and reassemble the button.

#### Diffusion

Plug in the box bottom with the electronics and fit it underneath the rest of the box.
We just want to get an idea of how the lighting currently looks. You'll notice that there are
hot spots, and even though the acrylic is frosted, and it is clear where the LEDs are inside
the box.

Cut pieces of the quilt batting to be slightly larger than the small interior acrylic pieces.
Use hot glue to tack these inside the box until you are satisfied with the diffusion. A gluing tactic
is to place glue against the sidewall above the batting, and then let it flow down into the batting. If
you touch the batting with the hot glue gun tip, fibers will stick to it.
You can also place small squares on top of the LEDs, especially the front most LEDs.


### Connect button, mount bottom, and feet

#### Connect button

Unless you've modified the code, the button should be connected to pins 3 and 4 of the Teensy. Solder the
wires to these pins. Once that is complete, we are done with the soldering iron! Plug in the USB cable and test
that everything works: the lights light up, and the button changes the animation.

#### Mount bottom

Now the bottom piece, which has the LEDs and other electronics, can be attached to the rest of the box.
This is a little tricky, as there isn't a lot of room to access the interior. However, hot glue does flow a bit,
and this can be used to our advantage. The general tactic will be to hold the box such that the corner we are 
gluing is pointing down, with the box 45 deg from level. Then flood the edge with hot glue, assuring that the glue
fills the area and pools on the faces we are gluing.

Align the bottom piece with the box, and then clamp at the front of the box, from its left to right side. This
will assure the horizontal alignment of the bottom piece and help keep it in place. Hold the box such that you
can apply vertical force, pressing the bottom against the box. Now, angle the box so the edge between the front
and bottom pieces is horizontal, and the bottom of the box is rotated 45 deg from horizontal.

Place the tip of the glue gun as close to the joint as possible and then pull the trigger a few times, filling the area with glue. Make sure to wait for the glue to cool before moving the box out of this orientation. The glue could
spill out of the box and off of the joint if the orientation is changed. One set, remove the clamp(s) and prepare
for the back of the box.

TODO: BACK OF BOX

#### Feet

Finally, we must put "feet" on the bottom, otherwise the box will slide away every time you try to push the button.
Cut two equal strips of the non-skid shelf liner material. They would be about 0.5" wide and as long as the bottom
opening.

Lay a single bead of hot glue down, next to the bottom opening. Then press the non-skid material into the
glue. Be careful to not use too much hot glue, as we don't want it to squeese out through the gaps in the non-skid
material and prevent even contact with a table top. Additionally, you might press the non-skid material
into the glue with a large metal object, like hefty scissors. Any glue squeeze out will not stick to the
cold metal, and the squeeze out will be flush with the non-stick material due to the flat implement
(this will also save your finger tips).

### Done!

Congrats! You can now increase the ceremony and excitement around prod deployments.


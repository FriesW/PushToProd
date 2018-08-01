// DEPLOY
// Teensy LC
// USB: keyboard + mouse + joystick
// Layout: US english
// CPU 48 Mhz

// Comment & uncomment the following defs to control USB behaviour
#define MOUSE
#define SERIAL

#include <WS2812Serial.h>

#define BOUNCE_LOCK_OUT
#include <Bounce2.h>

#define uint unsigned int
#define ulong unsigned long

const int button = 4;
const int ground = 3;

const int numled = 6;
const int pin = 24;

// Usable pins:
//   Teensy LC:   1, 4, 5, 24
//   Teensy 3.2:  1, 5, 8, 10, 20, 31
//   Teensy 3.5:  1, 5, 8, 10, 20, 26, 32, 33, 48
//   Teensy 3.6:  1, 5, 8, 10, 20, 26, 32, 33

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

Bounce debouncer = Bounce();

void setup() {
    ulong acc = 0;
    for(uint i = 0; i < 4*8; i++)
        acc += (analogRead(0) & 1) << i;
    randomSeed(acc);

    #ifdef SERIAL
        Serial.begin(9600);
    #endif
    
    leds.begin();
    
    pinMode(button, INPUT_PULLUP);
    debouncer.attach(button);
    debouncer.interval(150);
    pinMode(ground, OUTPUT);
    digitalWrite(ground, LOW);
}

void loop() {
    debouncer.update();
    
    update_usb();
    update_leds();
}

void update_usb() {
    #ifdef MOUSE
    if( debouncer.rose() ){
        Mouse.click();
    }
    #endif
    #ifdef SERIAL
    if( debouncer.rose() ){
        Serial.println("P"); //press
    }
    if( debouncer.fell() ){
        Serial.println("R"); //release
    }
    if(Serial.available()) {
        Serial.read();
        Serial.println(debouncer.read() ? "U" : "D" ); //up & down
    }
    #endif
}

void update_leds() {
    if( debouncer.read() )
        fader();
    else
        flasher();
    
    if( debouncer.rose() ) {
        click();
    }
}


void fader() {
    static uint step = random(255*6);
    static ulong brightness = 0;
    static elapsedMillis last;
    
    if(last < 25)
        return;
    if(last > 100)
        brightness = 0;
    last = 0;
    
    brightness += 35;
    brightness = min(brightness, 255*32);
    
    step++;
    step = step % (255*6);
    setAll(step, brightness / 32);
}

void flasher() {
    static elapsedMillis last;
    
    if(last < 35)
        return;
    last = 0;
    
    for(uint i=0; i< leds.numPixels(); i++)
        setPixel(i, random(255*6), 255);
    leds.show();
}

void click() {
    setAll(0, 0);
    delay(400);
    for(uint b=0; b<255; b++) {
        setAll(0, b);
        delay(15);
    }
    for(uint b=0; b<255; b++) {
        setAll(0, 255-b);
        delay(30);
    }
    delay(750);
}




void setAll(int hue, int brightness) {
     for(uint i=0; i < leds.numPixels(); i++)
            setPixel(i, hue, brightness);
    leds.show();
}

// led [0, n]       hue [0,255*6]       brightness [0,255]
void setPixel(uint led_index, int hue, int brightness) {
    leds.setPixel(led_index, calcColor(hue, brightness));
}

// hue [0,255*6]        brightness [0,255]
uint calcColor(int hue, int brightness) {
    byte r = ((long)calcChannel(0, hue)) * brightness / 255;
    byte g = ((long)calcChannel(1, hue)) * brightness / 255;
    byte b = ((long)calcChannel(2, hue)) * brightness / 255;
    uint color = (r << 16) + (g << 8) + b;
    return color;
}

// index [0,2]      step [0,255*6]
byte calcChannel(byte index, int step) {
    int o = (step + index * 255*2) % (255*6);
    o = o < 255*2 ? o : 255*2*2 - o;
    byte r = min(max( o , 0), 255);
    return r;
}
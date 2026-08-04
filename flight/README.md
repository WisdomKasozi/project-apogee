# Project Apogee 

I built a rocket from cardboard tubes and balsa wood, put a flight computer I coded myself inside it, launched it on an Estes D12-5, and got the data back. This is the story of that.

---

## 📊 What It Hit

* **Max Altitude:** 436 feet (132.8 m) vs. 518 feet OpenRocket simulation prediction.
* **Peak Acceleration:** ~6 G (~59.8 m/s² off the pad).
* **Data Integrity:** Over 25,000 samples logged at ~21 Hz on an intact SD card capturing boost, apogee, ejection, and recovery.

That number, 436 feet, is mine. I didn't read it off a kit box. I measured it with a sensor I wired up and code I wrote, on a rocket I built with my own hands.

---

## 🎥 About the Video

The person recording got startled by the sound of the motor and stopped filming before it climbed — so I don't have clean launch footage. I slowed down the little bit I got and pulled what I could out of it, but honestly it doesn't matter as much as I thought it would in the moment. 

Anyone can point a phone at the sky. The data is the part that actually took engineering. The video was going to be the trophy; the CSV file is the proof.

---

## 🛠️ The Parts Where It Almost Didn't Work

Nothing about this went smoothly, and that turned out to be the point:

* **The Wiring:** The first power plan was a LiPo battery with a charging board and a boost converter. Struggling with soldering and stripping wire with no multimeter and no experience was a bad mix. I scrapped it and switched to a USB power bank instead — simpler, safer, and it just worked. Sometimes the smart engineering move is admitting the fancy version isn't worth it.
* **The Power Bank Keep-Alive Issue:** Cheap power banks turn themselves off when the load draws too little current. My Arduino barely draws anything, so it kept dying after 30 seconds. The fix was a single resistor across the power rails to bleed just enough current to trick the bank into staying on. 
* **Fitting Everything in the Tube:** The electronics never fit as cleanly as imagined. I ripped the side rails off a breadboard to make it skinny enough to slide into the body tube, then zip-tied every component down so nothing could shake loose during flight. Not pretty. It works.
* **The Launch Lug Failure:** Right before flight, the launch lug came loose. With no time for glue to cure, I taped it back on with painter's tape and flew it anyway. It held. Field repairs are a real part of this.

---

## 💡 What It Taught Me

I started this summer not knowing how to code an Arduino, how to solder anything beyond a header pin, or how a barometer talks to a microcontroller. I put in a lot of hours — nights of uploading code, watching it fail, changing one thing, uploading again, getting three different sensors to share one data bus, learning what a chip select pin is, and figuring out why the SD card wrote garbage until I matched the SPI configurations.

Every problem on this list was me not knowing something, then knowing it by the end of the night. That's the whole thing. That's what being an engineer actually feels like — not having it work the first time, but refusing to stop until it does.

---

## 🔬 The One Finding I'm Proud Of

When I dug into raw data, the climb looked weird — compressed. I figured out why: **my electronics bay was sealed with no vent holes.** 

As the rocket shot up, the air pressure inside the sealed tube couldn't vent fast enough, causing the barometer to under-read the true altitude until the nose cone popped at ejection and the pressure suddenly equalized. Real flight computers drill tiny static ports in the tube wall to fix exactly this. Nobody told me that was the problem; I found it in my own numbers. 

That's the moment this stopped being a craft project and started being engineering.

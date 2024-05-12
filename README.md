# ESP32-I2C-HD44780-PCF8574-Library

## Making use of the Library

If you wish to use this library in a projects of yours, you can simply clone
the repo and copy the contents of the `components/` directory into the
components directory of your ESP IDF project, and modify the `CMakeLists.txt`
of your `main` directory of your project to include the contents found in
`main/CMakeLists.txt` of this repo. That's it! To make it easier, below
are some example commands you might run to achieve this:

### Example Library Installation

```bash
git clone git@github.com:JSpeedie/ESP32-I2C-HD44780-PCF8574-Library.git ESP32-I2C-HD44780-PCF8574-LibraryGit
mkdir -p ~/esp/esp-idf/[your project name/path here]/components
cp -r ESP32-I2C-HD44780-PCF8574-LibraryGit/components/esp32-i2c-hd44780-pcf8574/ ~/esp/esp-idf/[your project name/path here]/components/esp32-i2c-hd44780-pcf8574/
cd ~/esp/esp-idf/[your project name/path here]
```

Then you need to edit the `main/CMakeLists.txt` file within your project such
that the `idf_component_register` call "priv requires" the components. For
example your `main/CMakeLists.txt` could look like:

```
set(srcs "lcd-test.c")

idf_component_register(SRCS "${srcs}"
                    REQUIRES driver
                    PRIV_REQUIRES esp32-i2c-hd44780-pcf8574
                    INCLUDE_DIRS ".")
```

Finally, to make use of the library, you just need to include the correct header
file from the library in the source file where you want to make use of the library.
Continuing our example, in `main/lcd-test.c`, we may add the following lines:

```
/* Component includes */
#include "esp32-i2c-hd44780-pcf8574.h"
```

And you're done!


## Example Program Setup

If you simply wish to run the example program here on an ESP32, here are the
steps.

### Software setup

I used the ESP IDF for development of this project. In order to recreate
this example project, you will have to install the ESP IDF as explained at
[https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html)

Once you've set it up, all you need to do for development (after making the
necessary hardware connections, of course) is:

```bash
cd ~/esp/esp-idf
get_idf
mkdir projects
cd projects
git clone git@github.com:JSpeedie/ESP32-I2C-HD44780-PCF8574-Library.git lcd-test
cd lcd-test
idf.py -p /dev/ttyUSB0 flash monitor
```

### Hardware connections

(in progress)

<!-- Below is the schematic I used for the example program. -->

<!-- <p align="center"> -->
<!--   <img src="https://raw.githubusercontent.com/wiki/JSpeedie/ESP32-I2C-HD44780-PCF8574-Library/images/ESP32-I2C-16x2LCD.png" width="50%"/> -->
<!-- </p> -->

<!-- Of course you will also need to connect a micro usb to usb cable between the -->
<!-- ESP32 and your development machine in order to flash the program to the ESP32 -->
<!-- and to give it power. -->

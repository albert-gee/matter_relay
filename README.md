# Matter Relay Actuator

This firmware is a Matter relay actuator. It creates one Matter On/Off endpoint, and writes to that endpoint's OnOff attribute control one physical relay GPIO.

---

## Implementation

- Relay GPIO: GPIO22
- Relay default boot state: off
- Relay polarity: active-high
- RGB LED GPIO: GPIO21 on ESP32, GPIO8 on targets where GPIO8 is not reserved for SPI flash
- Matter behavior: one On/Off endpoint controls the relay GPIO

---

## Prerequisites

### Hardware

- ESP32-H2-DevKitM-1
- DFRobot Gravity Digital 16A Relay Module, SKU DFR0251
- Power Supply and wires

### Software

- **Ubuntu 24.04** or **24.10**
- **ESP-IDF 5.3.2**
- **ESP-Matter release/v1.4.2** (`4cedd4ad40821933d6cc237e80ab6604f2953fb0`)

---

## Getting Started

### ESP-IDF Setup

**Step 1. Install Prerequisites for ESP-IDF:**

```bash
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
```

**Step 2. Get ESP-IDF:**

```bash
mkdir -p ~/esp
cd ~/esp
git clone -b v5.3.2 --recursive https://github.com/espressif/esp-idf.git
```

**Step 3. Set up the Tools:**

```bash
cd ~/esp/esp-idf
./install.sh all
```

**Step 4. Configure Environment Variables:**

```bash
alias get_idf='. $HOME/esp/esp-idf/export.sh'
```

Add this line to `~/.bashrc` to persist the alias.

**Step 5. Refresh Configuration:**

```bash
source ~/.bashrc
```

Running `get_idf` will now set up or refresh the esp-idf environment in any terminal session.

### ESP-Matter Setup

**Step 1. Install Prerequisites for Matter:**

```bash
sudo apt-get install git gcc g++ pkg-config libssl-dev libdbus-1-dev libglib2.0-dev libavahi-client-dev ninja-build python3-venv python3-dev python3-pip unzip libgirepository1.0-dev libcairo2-dev libreadline-dev
```

**Step 2. Clone the esp-matter Repository:**

```bash
cd ~/esp/
git clone -b release/v1.4.2 --recursive https://github.com/espressif/esp-matter.git
```

**Step 3. Bootstrap esp-matter:**

```bash
cd esp-matter
./install.sh
```

**Step 4. Configure Environment Variables:**

```bash
alias get_matter='. $HOME/esp/esp-matter/export.sh'
```

Add this line to `~/.bashrc` to persist the alias.

**Step 5. Refresh Configuration:**

```bash
source ~/.bashrc
```

Running `get_matter` will now set up or refresh the esp-matter environment in any terminal session.

---

## Wiring

The supported reference hardware is the **DFRobot Gravity Digital 16A Relay Module (SKU DFR0251)**. It is active-high, accepts a 3.3 V control signal, and accepts a 3.3–5.5 V module supply. These instructions use the ESP32-H2-DevKitM-1 5 V rail for the module/coil supply while GPIO22 supplies only the 3.3 V logic signal.

### Relay Module Pinout

- **+ (Module/coil supply):** Connect to the **5V pin** on the ESP32-H2-DevKitM-1.
- **− (Module ground):** Connect to **GND** on the ESP32-H2-DevKitM-1.
- **D (3.3 V logic input):** Connect to **GPIO22**. Do not connect 5 V to the GPIO.

Do not substitute an arbitrary 5 V relay board. A substitute must explicitly accept a 3.3 V active-high input and must not pull the ESP32-H2 GPIO above 3.3 V. Power its relay coil/module from the voltage specified by that module, not from the ESP32-H2 3.3 V pin.

### Relay Switch Terminals

- **COM (Common Terminal):** Connect to the positive terminal of the separate load power supply. This supply is electrically distinct from the module's 5 V coil supply unless the load itself is 5 V and the supply is adequately rated.
- **NO (Normally Open):** Connect to the red wire of the fan (positive wire). When the relay is activated, it closes the circuit, sending power to the fan.
- **NC (Normally Closed):** Leave this unconnected.

### Controlled Device

- **Black Wire (Negative):** Connect directly to the negative terminal of the power supply (black wire).
- **Red Wire (Positive):** Connect to the NO terminal on the relay.

Use a low-voltage DC load for development. Switching mains voltage requires an appropriately enclosed, fused, code-compliant installation by a qualified person.

---

## Build and Flash

### Step 1. Clone the Repository

```bash
git clone git@github.com:albert-gee/matter_relay.git
cd matter_relay
```

### Step 2. Set up the Environment

```bash
get_idf
get_matter
```

### Step 3. Set ESP32-H2 as the Target Device

This command creates a new `sdkconfig` file in the root directory of the project:

```bash
idf.py set-target esp32h2
```

### Step 4. Build the Project

```bash
idf.py build
```

### Step 5. Determine Serial Port

Connect the ESP32 board to the computer and check under which serial port the board is visible. Serial ports typically follow the `/dev/tty` pattern.

### Step 6. Flash the Project to the Target

```bash
idf.py -p <PORT> flash
```

### Step 7. Launch the IDF Monitor Application

Press `CTRL+]` to exit.

```bash
idf.py -p <PORT> monitor
```

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## References

- [Espressif Matter Documentation](https://docs.espressif.com/projects/esp-matter/en/latest/)
- [DFRobot DFR0251 Relay Module Documentation](https://wiki.dfrobot.com/dfr0251)
- [Matter Protocol Specification](https://csa-iot.org/all-solutions/matter/)

# Matter-based ESP32 Relay Controller

This firmware is for an ESP32 device that uses the Matter standard to control a relay through an On/Off endpoint.

---

## Prerequisites

### Hardware

- ESP32-DevKitM-1 or another board
- 5V 1-Channel Relay Module or another module
- Power Supply and wires

### Software

- **Ubuntu 24.04** or **24.10**
- **ESP-IDF 5.2.3** (newer versions should be tested)
- **ESP-Matter 1.3** (newer versions should be tested)

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
git clone -b v5.2.3 --recursive https://github.com/espressif/esp-idf.git
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
git clone -b release/v1.3 --recursive https://github.com/espressif/esp-matter.git
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

To connect the relay module to the ESP32, use the following wiring instructions:

### Relay Module Pinout

- **DC+ (Power Supply Positive):** Connect to the **3.3V pin** on the ESP32.
- **DC- (Power Supply Negative):** Connect to the **GND pin** on the ESP32.
- **IN (Input Signal):** Connect to the **GPIO21 pin** on the ESP32.

### Relay Switch Terminals

- **COM (Common Terminal):** Connect to the positive terminal of the power supply (red wire from the power source). This is the common connection that feeds power into the relay.
- **NO (Normally Open):** Connect to the red wire of the fan (positive wire). When the relay is activated, it closes the circuit, sending power to the fan.
- **NC (Normally Closed):** Leave this unconnected.

### Controlled Device

- **Black Wire (Negative):** Connect directly to the negative terminal of the power supply (black wire).
- **Red Wire (Positive):** Connect to the NO terminal on the relay.

---

## Build and Flash

### Step 1. Clone the Repository

```bash
git clone https://github.com/<your-repo>/matter-esp32-relay.git
cd matter-esp32-relay
```

### Step 2. Configure the Project (optional)

Use `menuconfig` to configure project-specific settings:

```bash
idf.py menuconfig
```

- Set the relay GPIO to GPIO21 if needed.
- Enable or disable features like CHIP Shell or OTA based on your requirements.

### Step 3. Set ESP32 as the Target Device

This command creates a new `sdkconfig` file in the root directory of the project:

```bash
idf.py set-target esp32
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
- [Matter Protocol Specification](https://csa-iot.org/all-solutions/matter/)


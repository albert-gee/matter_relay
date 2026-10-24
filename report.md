# Matter Relay validation report

Date: 2026-10-24
Target: ESP32-H2 (`/dev/ttyUSB0`)
Toolchain: ESP-IDF 5.3.2; esp-matter `release/v1.4.2` at `4cedd4ad40821933d6cc237e80ab6604f2953fb0`

## Result

The normal image and the OpenThread-CLI/encrypted-OTA optional image build and link successfully. The normal image was erased, flashed, hash-verified by esptool, and booted on the ESP32-H2 revision 0.1. With no relay attached, the erased/default-Off path initialized GPIO22 off and applied Matter's resolved OnOff value (`0`) to the GPIO. Matter, OpenThread, and BLE commissioning started without a panic.

| Configuration | Size | SHA-256 |
|---|---:|---|
| Normal | 1,655,952 bytes (`0x194490`) | `0d507ac01f71fc9c85ffa725a0535394d3e15f9429a051f39fb894bccb1b2a06` |
| OpenThread CLI + encrypted OTA | 1,719,648 bytes (`0x1a3d60`) | `63dd531a4dc5af008576799657e8ab8ac4761d3bb00dd0bdb93b4d2f29d54176` |

## Reproduce

Activate the tested environment in each shell:

```bash
source "$HOME/.espressif/tools/activate_idf_v5.3.2.sh"
export PATH="$HOME/esp-matter/.host-python/bin:$PATH"
source "$HOME/esp-matter/export.sh"
```

Build and flash the normal configuration:

```bash
cd "$HOME/IoT/matter_relay"
idf.py --ccache -B build-default \
  -DSDKCONFIG="$PWD/build-default/sdkconfig" \
  -DSDKCONFIG_DEFAULTS="$PWD/sdkconfig.defaults;$PWD/sdkconfig.defaults.esp32h2" \
  build
idf.py --ccache -B build-default \
  -DSDKCONFIG="$PWD/build-default/sdkconfig" \
  -DSDKCONFIG_DEFAULTS="$PWD/sdkconfig.defaults;$PWD/sdkconfig.defaults.esp32h2" \
  -p /dev/ttyUSB0 erase-flash flash monitor
```

For optional compile coverage, create an external throwaway RSA key, link it only for the build, and remove both afterward:

```bash
test_key="$(mktemp)"
openssl genrsa -out "$test_key" 2048
ln -s "$test_key" esp_image_encryption_key.pem
idf.py --ccache -B build-optional \
  -DSDKCONFIG="$PWD/build-optional/sdkconfig" \
  -DSDKCONFIG_DEFAULTS="$PWD/sdkconfig.defaults;$PWD/sdkconfig.defaults.esp32h2;$PWD/sdkconfig.defaults.optional" \
  build
unlink esp_image_encryption_key.pem
rm -f "$test_key"
```

The key filename is ignored by Git. Never commit a production OTA private key.

## Follow-up documentation correction

The supported reference relay is the DFRobot Gravity Digital 16A Relay Module, SKU DFR0251. Its `+` module/coil supply connects to the DevKit's 5 V rail, `-` to ground, and its 3.3 V-compatible `D` logic input to GPIO22. The load uses the relay's isolated COM/NO contacts and a separate supply. The README now targets `esp32h2`; it no longer names an ESP32 target or tells users to power a named 5 V relay from 3.3 V.

## Limits

No relay or Matter controller was attached. Physical switching, restored-On startup, every `StartUpOnOff` policy, final-fabric removal, and OTA transfer/decryption/rollback still require device-level tests. Encrypted OTA validation here is build coverage only.

Reference: [DFRobot DFR0251 documentation](https://wiki.dfrobot.com/dfr0251).

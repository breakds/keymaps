# Configurations for Geonix Rev 2

## VIA

If the keyboard is running the via-enabled firmware, we can use the [VIA](https://usevia.app/) to configure it. Since this is a customized keyboard, we will first need to enable the "design" tab, and then upload the design file [geonix_via_design.json](geonix_via_design.json) to the design tab.

In [via_keymaps](via_keymaps), I have stored my customized VIA keymap json and the original factory VIA keymap json.

**NOTE**: Use an USB-C to USB-C cable, and make sure the keyboard is in the USB mode.
**IMPORTANT**: Always make sure that you have access to the `TO_USB` key while editting the keymap using the VIA app. Otherwise if you accidentally get out of the USB mode, you will not be able to edit the keymap again with the VIA app because it requires the keyboard being connected with USB cable and in `USB` mode.

## QMK FIRMWARE

We can also use QMK firmware to flash a firmware into keyboard. We can compile and flash a firmware with a good initial default keymap and with via enabled.

Note that this has to be done in the vendor's version (can be found [here](https://drive.google.com/drive/folders/1QNRFeJZBt527T0AZcOdAccgRrbsD4zqa)) of the `qmk_firmware`, which means that I have to do

```bash
qmk config user.qmk_home=/home/breakds/projects/qmk/qmk_firmware_geonix40
```

before running `qmk cd`. 

**NOTE**: `qmk cd` may complain about `appdirs` not installed, but it is not important. Just remove it from `requirements.txt` in the customized qmk firmware repo if it is present.


# Geonix Rev 2 — Configuration Notes

This repo tracks how I configure the **Geonix Rev.2** using either **VIA** (GUI, dynamic keymap) or **QMK** (compiled firmware). It also keeps the design/keymap files I use.

---

## Option A — VIA (recommended for quick edits)

If the keyboard is running **VIA-enabled firmware**, use the web app:

1. Open **VIA**: https://usevia.app/  
2. Enable **Settings → Show Design tab**.  
3. Go to **Design** and **Load** the local file: [`geonix_via_design.json`](geonix_via_design.json).  
4. Switch back to **Configure** and remap keys/layers as needed.

The directory [`via_keymaps`](via_keymaps) contains:
- My customized VIA keymap JSON
- The original factory VIA keymap JSON (for reference/backups)

> **Note (hardware mode):** Use a **USB-C ↔ USB-C** cable and make sure the keyboard is in **USB mode** before using VIA.  
> **Important (safety key):** Always keep a key that can switch back to **USB mode** (e.g., a `TO_USB`/mode key). If you drop into a wireless mode while editing, VIA (which talks over USB) won’t see the board until you switch back.

---

## Option B — QMK firmware (compile + flash)

You can also build/flash the vendor’s QMK tree with a good default keymap and VIA support.

> **Vendor tree**: use the **Geonix-supplied** [qmk_firmware](https://drive.google.com/drive/folders/1QNRFeJZBt527T0AZcOdAccgRrbsD4zqa) (not upstream). I store it at:
> `/home/breakds/projects/qmk/qmk_firmware_geonix40`

### Point the QMK CLI at the vendor tree
```bash
qmk config user.qmk_home=/home/breakds/projects/qmk/qmk_firmware_geonix40
qmk cd
```

> **Note (NixOS)**: If `qmk cd` complains about a missing Python module (e.g., `appdirs`), I just removed it from the vendor repo’s requirements.txt. Alternatively, run the vendor repo’s shell.nix / dev shell so Python deps live in the project, not globally.

### Compile (VIA keymap) and flash

```bash
# build the VIA-enabled firmware
qmk compile -kb geonix40/geonix40 -km via

/home/breakds/projects/qmk/qmk_firmware_geonix40/lib/python/qmk/decorators.py:20: UserWarning: cli._subcommand has been deprecated, please use cli.subcommand_name to get the subcommand name instead.
  if cli.config_source[cli._subcommand.__name__]['keyboard'] != 'argument':
/home/breakds/projects/qmk/qmk_firmware_geonix40/lib/python/qmk/decorators.py:40: UserWarning: cli._subcommand has been deprecated, please use cli.subcommand_name to get the subcommand name instead.
  if cli.config_source[cli._subcommand.__name__]['keymap'] != 'argument':
Ψ Compiling keymap with make -r -R -f builddefs/build_keyboard.mk -s KEYBOARD=geonix40/geonix40 KEYMAP=via KEYBOARD_FILESAFE=geonix40_geonix40 TARGET=geonix40_geonix40_via INTERMEDIATE_OUTPUT=.build/obj_geonix40_geonix40_via VERBOSE=false COLOR=true SILENT=false QMK_BIN="qmk"

⚠ geonix40/geonix40: led_config: geonix40.c: Unable to parse g_led_config matrix data
arm-none-eabi-gcc (Arm GNU Toolchain 14.2.Rel1 (Build arm-14.52)) 14.2.1 20241119
Copyright (C) 2024 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Size before:
   text    data     bss     dec     hex filename
      0   68598       0   68598   10bf6 geonix40_geonix40_via.bin

Compiling: quantum/via.c                                                                            [OK]
Linking: .build/geonix40_geonix40_via.elf                                                           [OK]
Creating binary load file for flashing: .build/geonix40_geonix40_via.bin                            [OK]
Creating load file for flashing: .build/geonix40_geonix40_via.hex                                   [OK]

Size after:
   text    data     bss     dec     hex filename
      0   68598       0   68598   10bf6 geonix40_geonix40_via.bin

Copying geonix40_geonix40_via.bin to qmk_firmware folder                                            [OK]
Copying geonix40_geonix40_via.bin to userspace folder                                              cp: cannot create regular file '/home/breakds/qmk_userspace/geonix40_geonix40_via.bin': No such file or directory
 [OK]

```

I just ignored the the warnings, and I think we do not care about copying the compiled bin file to userspace folder.

We now need to flash the bin file into the keyboard. Note that `qmk flash` command won't work because geonix rev 2 comes with a custom bootloader.

```bash
$ rg -n '"bootloader"\s*:' keyboards/geonix40 -S
keyboards/geonix40/geonix40/info.json
79:    "bootloader": "custom",
```

We should 

1. Enter the bootloader mode by holding the top-left key (Bootmagic) while plugging it in with the USB-C to USB-C cable
2. You will see an USB disk being mounted (mine says 109KB)
3. Copy the generated bin file from the compilation to this disk. The completion of the copy kicks off the flash process.
4. Wait and do nothing until the flash is done. The USB disk will be ejected automatically and the keyboard become usable.

### Troubleshooting

After flashing the VIA keymap firmware to the Geonix40 keyboard, the keyboard exhibits unwanted sleep behavior in Bluetooth mode:
- The keyboard automatically turns off after 3-5 minutes of inactivity
- Keypresses do not wake the keyboard
- The physical power switch must be toggled off and on to restore functionality
- This issue does not occur with the original firmware

#### Solution
Add a periodic reset of the `Usb_Change_Mode_Delay` counter to prevent it from reaching the sleep threshold. This is implemented using the `matrix_scan_user()` callback which runs continuously during the keyboard's main loop.

Please see the updated `keymap.c`  [geonix40/geonix40/keymaps/via/keymap.c](geonix40/geonix40/keymaps/via/keymap.c).

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

I build/flash the vendor’s QMK tree with a good default keymap and VIA support.

> **Vendor tree**: use the **Geonix-supplied** [qmk_firmware](https://drive.google.com/drive/folders/1QNRFeJZBt527T0AZcOdAccgRrbsD4zqa) (not upstream). I store it at:
> `/home/breakds/projects/qmk/qmk_firmware_geonix40`

### Point the QMK CLI at the vendor tree
```bash
qmk config user.qmk_home=/home/breakds/projects/qmk/qmk_firmware_geonix40
qmk cd

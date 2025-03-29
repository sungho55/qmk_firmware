# Keychron Q3 ANSI Encoder – sungho_keymap

This is a custom QMK keymap for the **Keychron Q3 ANSI Encoder** keyboard.

---

## 🔧 Keymap Info

- **Keyboard**: `keychron/q3/ansi_encoder`  
- **Keymap**: `sungho_keymap`  
- **Encoder Behavior**: Volume control by default  
  - Clockwise: Volume Up (`KC_VOLU`)  
  - Counter-clockwise: Volume Down (`KC_VOLD`)  

You can customize this behavior in `keymap.c`.

---

## 🚀 Compile Firmware

Run the following command to compile adn flash your firmware:

```bash
qmk compile -kb keychron/q3/ansi_encoder -km sungho_keymap
qmk flash -kb keychron/q3/ansi_encoder -km sungho_keymap
```

## Update Firmware from qmk/qmk_firmware
```bash
git fetch upstream
git checkout master
git merge upstream/master
git push origin master
```
# Overview

This began as [a sparse checkout](https://git-scm.com/docs/git-sparse-checkout) of just  `rp-rs/rp-hal-boards`; namely, the `rp-pico` portion. I have retained much of the code & text; see [the upstream repo](https://github.com/rp-rs/rp-hal-boards/) for details.

## Status
- `blinky`
    - Does not work; [known issue](https://github.com/rp-rs/rp-hal/issues/376)
        - pico-w led goes through the `cyw43` wifi chip

## Quick notes

Compilation target, helpful tools, necessary minimum crates:

```sh
rustup target add thumbv6m-none-eabi
cargo install elf2uf2-rs --locked
cargo add rp-pico
cargo add cortex-m-rt
cargo add panic-halt
```

Also need the `memory.x` file & some stuff from the `/.cargo/config` file:

```toml .cargo/config

[build]
target = "thumbv6m-none-eabi"

[target.thumbv6m-none-eabi]
rustflags = [
    "-C", "link-arg=--nmagic",
    "-C", "link-arg=-Tlink.x",
    "-C", "inline-threshold=5",
    "-C", "no-vectorize-loops",
]

runner = "elf2uf2-rs -d"

```


```sh
placeholder
```

## [rp-pico] - Board Support for the [Raspberry Pi Pico]

This crate includes the [rp2040-hal], but also configures each pin of the RP2040 chip according to how it is connected up on the Pico.

## Programming

Rust generates standard Arm ELF files, which you can load onto your Raspberry Pi Silicon device with your favourite Arm flashing/debugging tool. In addition, the RP2040 contains a ROM bootloader which appears as a Mass Storage Device over USB that accepts UF2 format images. You can use the `elf2uf2-rs` package to convert the Arm ELF file to a UF2 format image. 

For boards with USB Device support like the Raspberry Pi Pico, we recommend you use the UF2 process.

The RP2040 contains two Cortex-M0+ processors, which execute Thumb-2 encoded ARMv6-M instructions. There are no operating-specific features in the binaries produced - they are for 'bare-metal' systems. For compatibilty with other Arm code (e.g. as produced by GCC), Rust uses the *Arm Embedded-Application Binary Interface* standard or EABI. Therefore, any Rust code for the RP2040 should be compiled with the target *`thumbv6m-none-eabi`*.

### Loading a UF2 over USB

*Step 1* - Install [`elf2uf2-rs`](https://github.com/JoNil/elf2uf2-rs):

```sh
cargo install elf2uf2-rs --locked
```

*Step 2* - Make sure your .cargo/config contains the following (it should by default if you are working in this repository):

```toml
[target.thumbv6m-none-eabi]
runner = "elf2uf2-rs -d"
```

The `thumbv6m-none-eabi` target may be replaced by the all-Arm wildcard `'cfg(all(target_arch = "arm", target_os = "none"))'`.

*Step 3* - Boot your RP2040 into "USB Bootloader mode", typically by rebooting whilst holding some kind of "Boot Select" button. On Linux, you will also need to 'mount' the device, like you would a USB Thumb Drive.

*Step 4* - Use `cargo run`, which will compile the code and started the specified 'runner'. As the 'runner' is the elf2uf2-rs tool, it will build a UF2 file and copy it to your RP2040.

```console
$ cargo run --release --example pico_pwm_blink
```

### Loading with picotool

As ELF files produced by compiling Rust code are completely compatible with ELF files produced by compiling C or C++ code, you can also use the Raspberry Pi tool [picotool](https://github.com/raspberrypi/picotool). The only thing to be aware of is that picotool expects your ELF files to have a `.elf` extension, and by default Rust does not give the ELF files any extension. You can fix this by simply renaming the file.

Also of note is that the special [pico-sdk](https://github.com/raspberrypi/pico-sdk) macros which hide information in the ELF file in a way that `picotool info` can read it out, are not supported in Rust. An alternative is TBC.

## Helpful links
- [rp2040-hal](https://crates.io/crates/rp2040-hal)
- [HAL crate](https://github.com/rp-rs/rp-hal)
- [Embedded HAL](https://github.com/rust-embedded/embedded-hal)
- [picotool](https://github.com/raspberrypi/picotool)
- [elf2uf2-rs](https://github.com/JoNil/elf2uf2-rs):
- [rp2040 Project Template](https://github.com/rp-rs/rp2040-project-template).

SECTIONS {
  .text : {
    *(.text)
  }
  .data : {
    *(.rodata)
    *(.data)
  }
  .bss : {
    __bss_start = .;
    *(.bss)
    *(COMMON)
    __bss_end = .;
  }
  /DISCARD/ : {
    *(.comment)
  }
}

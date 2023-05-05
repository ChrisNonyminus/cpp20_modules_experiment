//
// Created by chris on 5/4/2023.
//
module;

#include <cstdio>

#if defined(__GBA__)
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdlib.h>
#elif defined(__NDS__)
#include <nds.h>
#endif

export module test;

#if defined(_WIN32)
export void hello() { std::printf("Hello, modules!\n"); }
#elif defined(__linux__)
export void hello() { std::printf("Hello, modules!\n"); }
#elif defined(__GBA__)
export void hello() {
  irqInit();
  irqEnable(IRQ_VBLANK);
  consoleDemoInit();
  std::printf("Hello, modules!\n");
  while (true) {
	VBlankIntrWait();
  }
}
#elif defined(__NDS__)
export void hello() {
  consoleDemoInit();
  std::printf("Hello, modules!\n");
  while (true) {
	swiWaitForVBlank();
  }
}
#endif

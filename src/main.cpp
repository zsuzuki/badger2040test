//
// Copyright 2023 Suzuki Yoshinori(wave.suzuki.z@gmail.com)
//
#include <pico/stdlib.h>

#include <array>
#include <string>

// badger2040
#include <badger2040.hpp>
#include <common/pimoroni_common.hpp>

//
#include "font.h"

namespace {
//
pimoroni::Badger2040 badger;

//
void Clear(uint8_t level) {
  badger.pen(level);
  badger.clear();
}

//
void DrawString(int x, int y, int c, const char *msg, Katakori::Font *font) {
  if (msg == nullptr || font == nullptr || font->GetFontSize() > 64) {
    return;
  }

  badger.pen(c);
  //   badger.thickness(2);
  font->GetString(msg, [&](const Katakori::FontBitmap &bitmap) {
    if (bitmap.data == nullptr)
      return;
    int width = bitmap.width;
    int height = bitmap.height;
    int dx = x + bitmap.offsetX;
    int dy = y + bitmap.offsetY;
    x += bitmap.pitch;

    std::array<uint8_t, 32 * 32> fbuff;
    fbuff.fill(15);
    auto drawPixel = [&](int lx, int ly, uint8_t c) {
      if (lx < 0 || ly < 0) {
        return;
      }
      int adrs = ly * 32 + lx;
      if (fbuff[adrs] > c) {
        badger.pixel(dx + lx, dy + ly);
        fbuff[adrs] = c;
      }
    };

    auto *fontdata = bitmap.data;
    for (int ly = 0; ly < height; ly++) {
      uint64_t line = bitmap.GetLine(fontdata);
      uint64_t mask = bitmap.GetMask();
      for (int lx = 0; lx < width; lx++) {
        if (line & mask) {
          badger.pen(c);
          drawPixel(lx, ly, c);
          //   drawPixel(lx + 1, ly, c);
          //   badger.pen(c + 4);
          //   drawPixel(lx + 1, ly, c + 2);
          //   drawPixel(lx - 1, ly, c + 2);
          //   drawPixel(lx, ly + 1, c + 2);
          //   drawPixel(lx, ly - 1, c + 2);
          //   badger.pen(c + 8);
          //   drawPixel(lx + 1, ly + 1, c + 4);
          //   drawPixel(lx + 1, ly - 1, c + 4);
          //   drawPixel(lx - 1, ly + 1, c + 4);
          //   drawPixel(lx - 1, ly - 1, c + 4);
        }
        line <<= 1UL;
      }
    }
  });
}

} // namespace

//
int main() {
  stdio_init_all();

  badger.init();
  badger.update_speed(1);

  Katakori::Font ibml14, ibmm18, kpop20, kpop22, maru20, maru22;
  ibml14.AssignMappedMemory((const void *)(0x10000000 + 0x100000));
  ibmm18.AssignMappedMemory((const void *)(0x10000000 + 0x118000));
  kpop20.AssignMappedMemory((const void *)(0x10000000 + 0x138000));
  kpop22.AssignMappedMemory((const void *)(0x10000000 + 0x160000));
  maru20.AssignMappedMemory((const void *)(0x10000000 + 0x188000));
  maru22.AssignMappedMemory((const void *)(0x10000000 + 0x1B0000));

  int btn = 0;
  while (true) {
    Clear(15);

    switch (btn) {
    case 1:
      DrawString(180, 100, 0, "ボタン A", &ibmm18);
      break;
    case 2:
      DrawString(180, 100, 0, "ボタン B", &ibmm18);
      break;
    case 3:
      DrawString(180, 100, 0, "ボタン C", &ibmm18);
      break;
    }

    DrawString(2, 0, 0, "Badger2040!", &maru20);
    DrawString(16, 22, 0, "テストプログラム", &kpop20);
    DrawString(16, 44, 0, "数種類", &kpop22);
    DrawString(30, 70, 0, "日本語フォント", &ibml14);
    DrawString(2, 100, 0, "実行委員会", &kpop20);

    badger.update();
    badger.wait_for_press();

    if (badger.pressed(badger.A)) {
      btn = 1;
    } else if (badger.pressed(badger.B)) {
      btn = 2;
    } else if (badger.pressed(badger.C)) {
      btn = 3;
    } else {
      btn = 0;
    }
  }

  return 0;
}
//

#include "esp32-hal.h"
/*
   224 bit packet
    | 32 bit header
       | 6 bit WC (Write Command)
       | 5 bit FC (Function Control)
       | 21 bit BC (Brightness Control)
          | 7 bit Blue (0-3)
          | 7 bit Green (0-3)
          | 7 bit Red (0-3)
    | 192 bit GS (GrayScale)
       | 16 bit Blue3   -> channel 1
       | 16 bit Green30 -> channel 2
       | 16 bit Red3    -> channel 3
       | 16 bit Blue2   -> channel 4
        ...
       | 16 bit Red0    -> channel 12
*/
#include <SPI.h>
#include "KHOI_TLC5971.h"
#include "config.h"
#include <SoftSPI.h>
/****************************************************************************
       variable
 ****************************************************************************/
static const int spiClk = 100000;  // 1 MHz// update: 1Mhz -> 0.1Mhz
// SPIClass * vspi = NULL;
SoftSPI mySPI(DATA, 100, CLOCK);
static byte packets[REGISTER_COUNT][PACKET_BYTES];

static byte data_proc[REGISTER_COUNT * 12];
static byte data_proc_inv[REGISTER_COUNT * 12];

static int data_proc_dimming[REGISTER_COUNT * 12];
static int data_proc_inv_dimming[REGISTER_COUNT * 12];

/*****************************************************************************
       code
 *****************************************************************************/
void writeHeaderToPacket(byte packet[], byte brightness) {
  // Dùng 32-bit long làm header 6 bit WC, 5 bit FC, 21 bit BC
  //              |6 WC|
  //                    |5FC|
  long header = 0b10010100010 << (32 - 6 - 5);

  // độ sáng mặc định là max ping
  brightness >>= 1;                     // lấy 7 bit
  header |= brightness;                 // BC red
  header |= (long)brightness << 7;      // BC green
  header |= (long)brightness << 7 * 2;  // BC blue

  // cop vào packet
  packet[0] = header >> 8 * 3;
  packet[1] = header >> 8 * 2;
  packet[2] = header >> 8;
  packet[3] = header;
}

// void updateData() {
//   for (int i = 0; i < BOARD_COUNT; i++) {
//     for (int j = 0; j < 24; j++) {
//       data_proc_inv[(i * 24 + j)] = data_proc[((BOARD_COUNT - 1 - i) * 24 + j)];
//     }
//   }
//   for (int j = 0; j < REGISTER_COUNT; j++) {
//     for (int i = 0; i < 12; i++) {
//       int buff_data = (int)data_proc_inv[PORT_COUNT - 1 - (j * 12 + i)] * 256;
//       packets[j][i * 2 + 4] = buff_data >> 8;
//       packets[j][i * 2 + 5] = buff_data;
//     }
//   }
// }

// void updateDataDimming() {
//   for (int i = 0; i < BOARD_COUNT; i++) {
//     for (int j = 0; j < 24; j++) {
//       data_proc_inv_dimming[(i * 24 + j)] = data_proc_dimming[((BOARD_COUNT - 1 - i) * 24 + j)];
//     }
//   }
//   for (int j = 0; j < REGISTER_COUNT; j++) {
//     for (int i = 0; i < 12; i++) {
//       int buff_data = (int)data_proc_dimming[PORT_COUNT - 1 - (j * 12 + i)];
//       packets[j][i * 2 + 4] = buff_data >> 8;
//       packets[j][i * 2 + 5] = buff_data;
//     }
//   }
// }
//Sua update data va update data dimming, từ 24 --> 12. hàm cũ đã comment ở trên
//Bắt đầu sửa
void updateData() {
  for (int i = 0; i < REGISTER_COUNT; i++) {
    for (int j = 0; j < 12; j++) {
      data_proc_inv[(i * 12 + j)] = data_proc[((REGISTER_COUNT - 1 - i) * 12 + j)];
    }
  }
  for (int j = 0; j < REGISTER_COUNT; j++) {
    for (int i = 0; i < 12; i++) {
      int buff_data = (int)data_proc_inv[PORT_COUNT - 1 - (j * 12 + i)] * 256;
      packets[j][i * 2 + 4] = buff_data >> 8;
      packets[j][i * 2 + 5] = buff_data;
    }
  }
}

void updateDataDimming() {
  for (int i = 0; i < REGISTER_COUNT; i++) {
    for (int j = 0; j < 12; j++) {
      data_proc_inv_dimming[(i * 12 + j)] = data_proc_dimming[((REGISTER_COUNT - 1 - i) * 12 + j)];
    }
  }
  for (int j = 0; j < REGISTER_COUNT; j++) {
    for (int i = 0; i < 12; i++) {
      int buff_data = (int)data_proc_dimming[PORT_COUNT - 1 - (j * 12 + i)];
      packets[j][i * 2 + 4] = buff_data >> 8;
      packets[j][i * 2 + 5] = buff_data;
    }
  }
}
//END


void ghepDataVaoFrame() {
  for (int i = 0; i < REGISTER_COUNT; i++) {
    writeHeaderToPacket(packets[i], 0x33);
  }
  updateData();
}

void guiDuLieuPacket(byte packet[]) {
  for (byte i = 0; i < PACKET_BYTES; i++) {
    //    SPI mềm
    //        shiftOut(DATA, CLOCK, MSBFIRST, packet[i]);
    //    SPI.write(packet[i]);

    // vspi->transfer(packet[i]);
    mySPI.transfer(packet[i]);
  }
}

void guiDuLieu() {
  //  noInterrupts();
  // vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));

  for (int i = 0; i < REGISTER_COUNT; i++) {
    guiDuLieuPacket(packets[i]);
  }

  // vspi->endTransaction();
  //  interrupts();
  delayMicroseconds(200);
  //  delay(10);
}

void batCong(byte packet[], int cong) {
  packet[cong * 2 + 4] = 0xff;
  packet[cong * 2 + 5] = 0xff;
}

void tatCong(byte packet[], int cong) {
  packet[cong * 2 + 4] = 0x00;
  packet[cong * 2 + 5] = 0x00;
}

void resetPacket(byte packet[]) {
  for (int i = 0; i < 12; i++) {
    tatCong(packet, i);
  }
}

void tlc_init() {
  // vspi = new SPIClass(VSPI);
  // vspi->begin();
  Serial.print("Start init");
  mySPI.begin();
  //  vspi->setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  //  vspi->setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  //  vspi->setClockDivider(SPI_CLOCK_DIV64);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  //  pinMode(VSPI_SS, OUTPUT); //VSPI SS
  //  SPI.begin();
  //  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  //  SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  //  SPI.setClockDivider(SPI_CLOCK_DIV64);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  ghepDataVaoFrame();
  guiDuLieu();
}

void set_data_proc(int i, byte value) {
  if ((i >= 0) && (i <= PORT_COUNT - 1))
    data_proc[i] = value;
}

byte get_data_proc(int i) {
  if ((i >= 0) && (i <= PORT_COUNT - 1))
    return data_proc[i];
  else return 0;
}


void tlc_all_on() {
  for (int i = 0; i < (REGISTER_COUNT * 12); i++) {
    set_data_proc(i, 0xff);
  }
  updateData();
  guiDuLieu();
}

void tlc_all_off() {
  for (int i = 0; i < (REGISTER_COUNT * 12); i++) {
    set_data_proc(i, 0);
  }
  updateData();
  guiDuLieu();
}

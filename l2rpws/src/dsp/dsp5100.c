
/* 
 * dsp5.c
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <term.h>
#include <time.h>
#include "fg.h"
#include "rtiu.h"
#include "util.h"
#include "utilf.h"
#include "utilo.h"
#include "utilt.h"

static char *title = { " CASSINI MP data dump  (DSP5) 5.100" };
struct MP_buffer *buffer;
int format_flag = 1;
static int epoch;

static int vsize = 0x7FFFFFFF;

void u_init (void)
{
  if (format_flag) {
    initscr ();
    /*
     * nonl();
     */
    clear ();
    refresh ();
  }
}
void u_refresh (void)
{
  if (format_flag) {
    refresh ();
  } else {
    fflush (stdout);
  }
}
static int iy = 1;
char *u_cr (char *s, int y)
{
  if (format_flag)
    clrtoeol ();
  else if (iy != y) {
    iy = y;
    printf ("\n");
  }
  return s;
}
void u_clear (int y, int x, int flag)
{
  if (format_flag) {
    move (y, x);
    switch (flag) {
     case 0:
       clrtobot ();
       break;
     case 1:
       clrtoeol ();
       break;
    }
  }
}
u_print0 (int y, int x, char *s)
{
  if (format_flag) {
    if (y > vsize)
      return;
    mvprintw (y, x, s);
    clrtoeol ();
  } else
    printf (u_cr (s, y));
}
u_print1 (int y, int x, char *s, int a1)
{
  if (format_flag) {
    if (y > vsize)
      return;
    mvprintw (y, x, s, a1);
    clrtoeol ();
  } else
    printf (u_cr (s, y), a1);
}
u_print2 (int y, int x, char *s, int a1, int a2)
{
  if (format_flag) {
    if (y > vsize)
      return;
    mvprintw (y, x, s, a1, a2);
    clrtoeol ();
  } else
    printf (u_cr (s, y), a1, a2);
}
u_print3 (int y, int x, char *s, int a1, char *s2, int a3)
{
  if (format_flag) {
    if (y > vsize)
      return;
    mvprintw (y, x, s, a1, s2, a3);
    clrtoeol ();
  } else
    printf (u_cr (s, y), a1, s2, a3);
}
u_print4 (int y, int x, char *s, int a1, char *s2, int a3, int a4)
{
  if (format_flag) {
    if (y > vsize)
      return;
    mvprintw (y, x, s, a1, s2, a3, a4);
    clrtoeol ();
  } else
    printf (u_cr (s, y), a1, s2, a3, a4);
}
u_print6 (int y, int x, char *s,
          int a1, int a2, int a3, int a4, int a5, int a6)
{
  if (format_flag) {
    if (y > vsize)
      return;
    mvprintw (y, x, s, a1, a2, a3, a4, a5, a6);
    clrtoeol ();
  } else
    printf (u_cr (s, y), a1, a2, a3, a4, a5, a6);
}
char *st_hfr (int st, int flg)
{
  static char *msg[] = { "OK ", "ERR", "", "",
    /*
     * 1 
     */ "Anal", "Sond", "Cal ", "mSec",
    /*
     * 2 
     */ "OFF", "ON ", "", "",
    /*
     * 3 
     */ "ON ", "OFF", "", "",
    /*
     * 4 
     */ "Ex OFF", "Ex+ ON", "Ex- ON", "Ex+-  ",
    /*
     * 5 
     */ "Ez OFF", "Ez ON ", "", "",
    /*
     * 6 
     */ "off  ", "meand", "err  ", "err  ",
    /*
     * 7 
     */ "err  ", "err  ", "err  ", "err  ",
    /*
     * 8 
     */ "...", "HF2", "", "",
    /*
     * 9 
     */ "...", "HF1", "", "",
    /*
     * 10 
     */ ".", "C", "", "",
    /*
     * 11 
     */ ".", "B", "", "",
    /*
     * 12 
     */ ".", "A", "", "",
    /*
     * 13 
     */ "1/8", "1/4", "1/2", "  1",
    /*
     * 14 
     */ "8 ", "16", "32", "32",
    /*
     * 15 
     */ "10", "20", "40", "80",
    /*
     * 16 
     */ "20", "40", "80", "160",
    /*
     * 17 
     */ "1", "2", "4", "8",
    /*
     * 18 
     */ "open   ", "clamped", "", "",
    /*
     * 19 
     */ "open  ", "closed", "", "",
    /*
     * 20 
     */ "HF1", "HF2", "", "",
    /*
     * 21 
     */ "Ez  ", "Ex+-", "", "",
    /*
     * 22 
     */ "PAA", "AAA", "", "",
    /*
     * 23 
     */ ".5mS", " 1mS", " 2mS", " 4mS",
    /*
     * 24 
     */ " 8mS", "16mS", "32mS", "64mS",
    /*
     * 25 
     */ "  256", "  512", " 1024", " 2048",
    /*
     * 26 
     */ " 4096", " 8192", "16384", "invld"
  };
  return msg[st * 4 + flg];
}
char *frq_hfr_wbr (unsigned char status)
{
  static char text[64];
  float freq;

  if (status & 0x01) {
    sprintf (text, "%4d Khz", status * 25);
  } else {
    freq = status * 50;
    freq /= 1000.;
    freq += 4.025;
    sprintf (text, "%6.3f Mhz", freq);
  }
  return text;
}
char *frq_hfr (unsigned char *mp)
{
  static char text[64];
  float freq;

  if (mp[11] & 0x01) {
    freq = mp[10] * 100 + 25;
    sprintf (text, "%6.3f Mhz", freq / 1000.);
  } else {
    freq = mp[10] * 25 + 0;
    sprintf (text, "%6.0f Khz", freq);
  }
  return text;
}
int status_hfr (unsigned char *mp, int ipos)
{
  char string[128];
  static int vert;
  static int startF, stopF, Nstep, deltaF;

  if (mp[4] & 0x7F)
    return vert;
  vert = ipos;
  sprintf (string, "ST_HFR err-flg:%s type:%s Snd-rly:%s clamp-rly:%s ",
           st_hfr (0, (mp[7] >> 7) & 0x01),
           st_hfr (1, (mp[7] >> 5) & 0x03),
           st_hfr (19, (mp[7] >> 4) & 0x01), st_hfr (18, (mp[7] >> 3) & 0x01)
    );
  u_print0 (vert++, 0, string);

  sprintf (string, "ST_HFR comp:%s  HdrVer:%d MFR-%s MFR-%s ",
           st_hfr (6, (mp[8] >> 4) & 0x07),
           (mp[8] >> 0) & 0x0F,
           st_hfr (4, (mp[7] >> 1) & 0x03), st_hfr (5, (mp[7] >> 0) & 0x01)
    );
  u_print0 (vert++, 0, string);

#define Analysis    0
#define Sounder     1
#define Calibration 2
#define Millisecond 3
  switch ((mp[7] >> 5) & 0x03) {
   case Analysis:
     sprintf (string, "ST_HFR ALL rep:%d attenuator:%s %s %s %s %s %s ",
              mp[13],
              st_hfr (2, (mp[9] >> 7) & 0x01),
              st_hfr (12, (mp[9] >> 0) & 0x01),
              st_hfr (11, (mp[9] >> 1) & 0x01),
              st_hfr (10, (mp[9] >> 2) & 0x01),
              st_hfr (9, (mp[9] >> 3) & 0x01), st_hfr (8, (mp[9] >> 4) & 0x01)
       );
     u_print0 (vert++, 0, string);

     sprintf (string, "ST_HFR %s%s%s %s %s auto:%s cross:%s filt:%s DF:%s",
              st_hfr (12, (mp[9] >> 0) & 0x01),
              st_hfr (11, (mp[9] >> 1) & 0x01),
              st_hfr (10, (mp[9] >> 2) & 0x01),
              st_hfr (5, (mp[14] >> 4) & 0x01),
              st_hfr (4, (mp[14] >> 2) & 0x03),
              st_hfr (2, (mp[23] >> 2) & 0x01),
              st_hfr (2, (mp[23] >> 5) & 0x01),
              st_hfr (14, (mp[14] >> 0) & 0x03),
              st_hfr (2, (mp[14] >> 5) & 0x01)
       );
     u_print0 (vert++, 0, string);
     sprintf (string, "ST_HFR ABC integ:%sS rep:%d",
              st_hfr (13, (mp[14] >> 6) & 0x03), mp[10]);
     u_print0 (vert++, 0, string);


     Nstep = mp[18];
     deltaF = mp[19] * 25;
     startF = mp[17] * 25;
     stopF = startF + ((Nstep - 1) * deltaF);
     sprintf (string, "ST_HFR HF1 %s %s auto:%s cross:%s filt:%s DF:%s",
              st_hfr (5, (mp[15] >> 4) & 0x01),
              st_hfr (4, (mp[15] >> 2) & 0x03),
              st_hfr (2, (mp[23] >> 1) & 0x01),
              st_hfr (2, (mp[23] >> 4) & 0x01),
              st_hfr (17, (mp[15] >> 0) & 0x03),
              st_hfr (2, (mp[15] >> 5) & 0x01));
     u_print0 (vert++, 0, string);
     sprintf (string,
              "ST_HFR HF1 integ:%smS rep:%d Steps:%d  deltaF:%dKhz Freq:%dKhz-%dKhz ",
              st_hfr (16, (mp[15] >> 6) & 0x03), mp[11], Nstep, deltaF,
              startF, stopF);
     u_print0 (vert++, 0, string);


     Nstep = (unsigned int) mp[21] + (unsigned int) ((mp[23] & 0x40) << 2);
     deltaF = mp[22] * 50;
     startF =
       ((unsigned int) mp[20] + (unsigned int) ((mp[23] & 0x80) << 1)) * 50 +
       25;
     stopF = startF + ((Nstep - 1) * deltaF);
     sprintf (string, "ST_HFR HF2 %s %s auto:%s cross:%s filt:%s DF:%s",
              st_hfr (5, (mp[16] >> 4) & 0x01),
              st_hfr (4, (mp[16] >> 2) & 0x03),
              st_hfr (2, (mp[23] >> 0) & 0x01),
              st_hfr (2, (mp[23] >> 3) & 0x01),
              st_hfr (17, (mp[16] >> 0) & 0x03),
              st_hfr (2, (mp[16] >> 5) & 0x01));
     u_print0 (vert++, 0, string);
     sprintf (string,
              "ST_HFR HF2 integ:%smS rep:%d Steps:%d  deltaF:%dKhz Freq:%dKhz-%dKhz ",
              st_hfr (15, (mp[16] >> 6) & 0x03), mp[12], Nstep, deltaF,
              startF, stopF);
     u_print0 (vert++, 0, string);
     break;
   case Sounder:
     sprintf (string, "ST_HFR SND cyc:%d pas:%d act:%d start-f:%d stop-f:%d",
              mp[9], mp[10], mp[11], mp[12], mp[13]
       );

     u_print0 (vert++, 0, string);
     sprintf (string, "ST_HFR SND T1:%d T2:%d T3:%d ant:%s mode:%s",
              mp[14],
              mp[15],
              mp[16],
              st_hfr (21, (mp[17] >> 7) & 0x01),
              st_hfr (22, (mp[17] >> 4) & 0x01)
       );
     u_print0 (vert++, 0, string);
     sprintf (string, "ST_HFR SND Auto:%d AGC:%d",
              (unsigned int) mp[18] + (unsigned int) ((mp[17] & 0x1) << 9),
              (unsigned int) mp[19] + (unsigned int) ((mp[17] & 0x6) << 8)
       );
     u_print0 (vert++, 0, string);
     break;
   case Calibration:
     sprintf (string, "ST_HFR CAL %s %s %s %s %s ",
              st_hfr (12, (mp[9] >> 0) & 0x01),
              st_hfr (11, (mp[9] >> 1) & 0x01),
              st_hfr (10, (mp[9] >> 2) & 0x01),
              st_hfr (9, (mp[9] >> 3) & 0x01), st_hfr (8, (mp[9] >> 4) & 0x01)
       );
     u_print0 (vert++, 0, string);
     sprintf (string, "ST_HFR CAL tones S/C %s %s %s ",
              st_hfr (2, (mp[10] >> 3) & 0x01),
              st_hfr (5, (mp[10] >> 2) & 0x01),
              st_hfr (4, (mp[10] >> 0) & 0x03)
       );
     u_print0 (vert++, 0, string);
     break;
   case Millisecond:
     sprintf (string, "ST_HFR MS rcvr:%s antenna:%s rate:%s samp:%s freq:%s",
              st_hfr (20, (mp[11] >> 0) & 0x01),
              st_hfr (4, (mp[9] >> 6) & 0x03),
              st_hfr (23, (mp[9] >> 3) & 0x07),
              st_hfr (25, (mp[9] >> 0) & 0x07), frq_hfr (mp)
       );
     u_print0 (vert++, 0, string);
     break;
  }
  return vert;
}
char *clk_lp (char msb, char lsb)
{
  int hz;
  int clk = 125000;
  int div;
  static char temp[] = { "                               " };
  div = (unsigned int) (msb << 8) | ((unsigned int) lsb & 0xFF);
  if (div & 0x8000)
    sprintf (temp, "%d RTI   ", lsb);
  else
    sprintf (temp, "%d Hz    ", clk / div);
  return temp;
}
char *st_lp (int st, int flg)
{
  static char *msg[] = { "Sweep  ", "Density", "Anal Swp", "Unknown ",
    "Unpackd", "Packed ", "TBD     ", "DCP Cmp ",
    "TableID", " LP DAC", "BAD BAD ", "BAD BAD "
  };
  static int offset[] = { 0, 4, 8 };
  return msg[offset[st] + flg];
}
char *mne_lp (int st, int flg)
{
  static char *msg[] = { "ADCP2", "ADCP1", "ADSP ", "ADSP ",
    "LPF", "HPF",
    "SPBMR", "SPBMR", "SPBLR", "SPBHR",
    "SPBMR", "SPBMR", "SPBLR", "SPBHR",
    "SPBer", "SPBer", "SPBFR", "SPBer",
    "SPBer", "SPBer", "SPBFR", "SPBer",
    "CYBMR", "CYBFR",
    "Lo Gain", "Hi Gain",
    "EX- Con", "EX- ERR", "EX- ERR", "EX- Dis",
    "EX+ Con", "EX+ ERR", "EX+ ERR", "EX+ Dis",
  };
  static int offset[] = { 0, 4, 6, 22, 24, 26, 30 };
  return msg[offset[st] + flg];
}
int status_lp (unsigned char *mp, int ipos)
{
  char string[128];
  int vert;

  vert = ipos;
  sprintf (string, "ST_LP size:%d, segment:%d, cmp:%s  typ:%s ",
           (mp[4] >> 6) & 0x03,
           (mp[4] >> 4) & 0x03,
           st_lp (1, (mp[4] >> 2) & 0x03), st_lp (0, (mp[4] >> 0) & 0x03));
  u_print0 (vert++, 0, string);

  sprintf (string, "ST_LP %s:%2.2X  "
           "mux:%2.2X  "
           "Relay:%2.2X "
           "clock:%2.2X%2.2X %s",
           st_lp (2, (mp[4] >> 0) & 0x03),
           mp[5], mp[6], mp[7], mp[9], mp[8], clk_lp (mp[9], mp[8])
    );
  u_print0 (vert++, 0, string);

  sprintf (string, "ST_LP %s %s %s %s %s %s %s",
           mne_lp (0, (mp[6] >> 0) & 0x03),
           mne_lp (1, (mp[6] >> 2) & 0x01),
           mne_lp (2, (mp[6] >> 3) & 0x0F),
           mne_lp (3, (mp[6] >> 7) & 0x01),
           mne_lp (4, (mp[7] >> 4) & 0x01),
           mne_lp (5, (mp[7] >> 0) & 0x03), mne_lp (6, (mp[7] >> 2) & 0x03));

  u_print0 (vert++, 0, string);

  return vert;
}
char *st_wfr (int st, int flg)
{
  static char *msg[] = { "LOband", "HIband",    /* 0 -   WFR 0 */
    "(234)", "(012)",                   /* 2 - 1 */
    "raw", "CM-1", "DCC",               /* 4 - 2 */
    "DCC/ext", "raw+1", "CM-5",
    "CM-6", "CM-7", "CM-8",
    "CM-9", "CM-10", "CM-11",
    "CM-12", "CM-13", "CM-14",
    "CM-15",
    "Ant-0", "Ant-1", "Ant-2",          /* 20 - 3 */
    "Ant-3", "Ant-4", "Ant-5",
    "Ant-6", "Ant-7",
    "CH0", "CH1", "CH2",                /* 28 - 4 */
    "CH3", "CH4", "bad-5",
    "bad-6", "COM",
    "CH-0", "CH-1", "CH-2",             /* 36 - 5 */
    "CH-3", "CH-4", "CHx2",
    "CHx3", "CHx5",
    "Nominal", "More STS",              /* 44 - 6 */
    "Ant-0", "Ant-1",                   /* 46 - LFDR 10 */
    "Ant-2", "Ant-3",
    "LOG", "LINEAR",                    /* 50 - 11 */
    "CM-0", "CM-1", "DCC",              /* 52 - WBR 22 */
    "DCC/ext", "DCP", "DCP-5",
    "DCP-6", "DCP-7", "CM-8",
    "CM-9", "CM-10", "CM-11",
    "CM-12", "CM-13", "CM-14",
    "CM-15",
    "ExLo ", "Bx   ", "EzLo ",          /* 68 - 23 */
    "HF   ", "LMR  4", "Ant-5",
    "Ant-6", "Ant-7",
    "Ex", "Ez", "Bx", "Bz",             /* 76 - MFR 33 */
    "Uncompressed", "COMPRESSED",       /* 80 - 32 */
    "0dB", "10dB", "20dB", "30dB"
  };
  static int offset[] = { 0, 2, 4, 20, 28, 36, 44, 82, 0, 0,
    46, 50, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 52, 68, 0, 0, 0, 0, 0, 0,
    0, 0, 80, 76, 0, 0, 0, 0, 0, 0,
    86
  };
  return msg[offset[st] + flg];
}
char *st_wfr_ant (unsigned char *mp)
{
  int chan;
  int ant[5] = { 0, 0, 0, 0, 0 };
  static char *msg[] = { "LMR+", "Ex  ",
    "LMR-", "Ez  ",
    "Bx  ", "LP  ",
    "By  ", "By  ",
    "Bz  ", "Bz  ",
    "Bad ", "Bad ",
    "Bad ", "Bad ",
    "Bad ", "Bad "
  };
  chan = (mp[7] >> 3) & 0x07;
  ant[0] = (mp[6] >> 0) & 0x01;
  ant[1] = (mp[6] >> 1) & 0x01;
  ant[2] = (mp[6] >> 2) & 0x01;
  return msg[(chan * 2) + ant[chan]];
}

int status_wfr (unsigned char *mp, int ipos)
{
  char string[128];
  int vert;

  vert = ipos;
  sprintf (string,
           "ST_WFR size:%d, segment:%d, FB:%s  LP:%s, gains:%s %s %s       ",
           (mp[4] >> 4) & 0x0F,
           (mp[4] >> 0) & 0x0F,
           st_wfr (0, (mp[5] >> 7) & 0x01),
           st_wfr (1, (mp[5] >> 6) & 0x01),
           st_wfr (7, (mp[5] >> 0) & 0x03),
           st_wfr (7, (mp[5] >> 2) & 0x03), st_wfr (7, (mp[5] >> 4) & 0x03));

  u_print0 (vert++, 0, string);
  sprintf (string, "ST_WFR cmprs:%s, MSF:%s, Ant:%X-%s, Chan:%s, Mode:%s        ", st_wfr (2, (mp[6] >> 4) & 0x0F),     /* cmprs */
           st_wfr (6, (mp[6] >> 3) & 0x01),     /* MSF */
           (mp[6] >> 0) & 0x07,         /* antenna */
           st_wfr_ant (mp),             /* antenna (text) */
           st_wfr (4, (mp[7] >> 3) & 0x07),     /* chan */
           st_wfr (5, (mp[7] >> 0) & 0x07));
  u_print0 (vert++, 0, string);
  if (mp[6] & 0x08) {
    sprintf (string, "ST_WFR Sph DAC:%2.2X  Cyl DAC:%2.2X        ",
             mp[8], mp[9]);
    u_print0 (vert++, 0, string);
  }
  return vert;
}
char *st_lfdr (int offset, int flg)
{
  static char *msg[] = { "Ant-0", "Ant-1", "", "", "", "", "", "",
    "256", "512", "1024", "Invalid", "", "", "", "",
    "LOG", "LINEAR", "", "", "", "", "", "",
    "Ch0", "Ch1", "Ch2", "Ch3", "Ch4", "", "", "",
    "", "", "", "", "", "", "", "",
    "0dB", "10dB", "20dB", "30dB", "", "", "", "",
    "OFF", "ON", "", "", "", "", "", "",
    "40Hz", "2.5Khz", "", "", "", "", "", "",
    "LMR+", "Ex",
    "LMR-", "Ez",
    "Bx", "LP",
    "By", "By",
    "Bz", "Bz",
    "Pfft", "Pfft",
    "Pfft", "Pfft",
    "Pfft", "Pfft",
    ""
  };

  return msg[offset * 8 + flg];

}
int status_lfdr (unsigned char *mp, int ipos)
{
  char string[128] = { "LFDR_BULLSHIT" };
  int vert;

  vert = ipos;
  sprintf (string, "ST_LFDR ant:%s, Size:%s, L/L:%s, Chan:%s,        ", st_lfdr (0, (mp[4] >> 1) & 0x01),       /* antenna */
           st_lfdr (1, (mp[4] >> 3) & 0x03),    /* Size */
           st_lfdr (2, (mp[4] >> 0) & 0x01),    /* log/lin */
           st_lfdr (3, (mp[4] >> 5) & 0x07)     /* Channel */
    );
  u_print0 (vert++, 0, string);
  sprintf (string, "ST_LFDR  DPF:%2.2X Gn:%s LP:%s Band:%s Ant:%s      ", (mp[5] >> 0) & 0x0F,  /* dig prescale */
           st_lfdr (5, (mp[5] >> 4) & 0x03),    /* Rcvr Gain */
           st_lfdr (6, (mp[5] >> 6) & 0x01),    /* LP Mode */
           st_lfdr (7, (mp[5] >> 7) & 0x01),    /* Band */
           st_lfdr (8, ((mp[4] >> 4) & 0x0E) + ((mp[4] >> 1) & 0x01))
    );
  u_print0 (vert++, 0, string);
  return vert;
}
int status_wbr (unsigned char *mp, int ipos)
{
  char string[128];
  int vert;

  vert = ipos;
  sprintf (string, "ST_WBR size:%d, segment:%d, FB:%s  gains:%X        ",
           (mp[4] >> 4) & 0x0F,
           (mp[4] >> 0) & 0x0F,
           st_wfr (0, (mp[5] & 0x80) >> 7), mp[5] & 0x07);
  u_print0 (vert++, 0, string);
  sprintf (string, "ST_WBR cmprs:%s, MSF:%s, Ant:%s, AGC:0x%2.2X       ",
           st_wfr (22, (mp[6] >> 4) & 0xF0),
           st_wfr (6, (mp[6] >> 3) & 0x08),
           st_wfr (23, (mp[6] >> 0) & 0x07), mp[7]);
  u_print0 (vert++, 0, string);
  if (mp[6] & 0x08) {
    sprintf (string, "ST_WBR SUB-RTI %d  ", mp[9]);
    if (((mp[6] >> 0) & 0x07) == 4) {
      sprintf (string, "ST_WBR LP DAC-0: %2.2X  SUB-RTI %d  ", mp[8], mp[9]);
    }
    if ((mp[6] & 0x07) == 3) {
      sprintf (string, "ST_WBR HFR XLATE: %s  SUB-RTI %d  ",
               frq_hfr_wbr (mp[8]), mp[9]);
    }
    u_print0 (vert++, 0, string);
  }
  return vert;
}
char *st_mro (int flag)
{
  static char *text[3] = { "low rate",
    "high rte",
    "compress"
  };
  if (flag & 0x02)
    return text[0];
  if (flag & 0x04)
    return text[2];
  if (flag & 0x08)
    return text[1];
}
char *st_bank (int flag)
{
  static char *text[] = { "      ",
    "hi bnk"
  };
  if (flag & 0x10)
    return text[1];
  return text[0];
}
int addr_mro (unsigned char *mp, int len)
{
  int addr;

  addr = mp[4] << 8;
  addr = addr + mp[5];
  if (len > 64) {
    addr = addr & 0xFFE0;
  }
  return addr;
}
int status_mro (unsigned char *mp, int ipos, int len)
{
  char string[128];
  int vert;
  int addr;
  int delta_addr;
  int index;
  static int old_addr[16] = { 16 * 0 };
  vert = ipos;
  index = mp[5] & 0x0E;                 /* which processor */
  addr = addr_mro (mp, len);
  delta_addr = addr - old_addr[index];
  delta_addr &= 0xFFFF;
  if (len > 64) {
    sprintf (string, "ST_MRO address: %4.4X %4X  source: %s %s ",
             addr, delta_addr, st_mro (mp[5] & 0x0F), st_bank (mp[5]));
  } else
    sprintf (string, "ST_MRO address: %4.4X %4X                         ",
             addr, delta_addr);

  u_print0 (vert++, 0, string);
  old_addr[index] = addr;
  return vert;
}
char *st_mfr (int offset, int flg)
{
  static char *msg[] = { "Ex", "Ez", "Bx", "Bz", "", "", "", "",
    "Fixed ", "Fast  ", "", "", "", "", "", "",
    "Fixed ", "Toggle", "", "", "", "", "", "",
    "Compressed  ", "UnCompressed", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "",
  };

  return msg[offset * 8 + flg];

}
int status_mfr (unsigned char *mp, int ipos)
{
  char string[128];
  int vert;

  vert = ipos;
  sprintf (string, "ST_MFR %s  %s Ant:%s 1:%s 2:%s            ",
           st_mfr (3, (mp[4] >> 0) & 0x01),
           st_mfr (2, (mp[4] >> 3) & 0x01),
           st_mfr (0, (mp[4] >> 1) & 0x03),
           st_mfr (0, (mp[4] >> 4) & 0x03), st_mfr (0, (mp[4] >> 6) & 0x03));
  u_print0 (vert++, 0, string);
  return vert;
}
int status_stim (unsigned char *mp, int ipos, int flag)
{
  static char *fmt_stg[] =
    { "ST_STIM %4.4X Init:%4.4X Seq:%3u ID0:%5u ID1:%5u[%4.4X] %3u %3u \n",
    "ST_STIM %4.4X Init:%4.4X Seq:%3u ID0:%5u ID1:%5u[%4.4X] %3u %3u    "
  };
  char string[128];
  int vert;
  static unsigned cur, init;
  static unsigned seq, id0, id1;
  static unsigned id2, id3;

  vert = ipos;
  if (PACKET_TYPE_stim == UTIL_extract_MP_type (buffer)) {
    cur = mp[3] << 8 | mp[2];
    init = mp[5] << 8 | mp[4];
    seq = mp[7] << 8 | mp[6];
    id0 = mp[9] << 8 | mp[8];
    id1 = mp[11] << 8 | mp[10];
    id2 = mp[13] << 8 | mp[12];
    id3 = mp[15] << 8 | mp[14];
  }
  sprintf (string,
           "   Stim:%4.4X Init:%4.4X Seq:%u ID0:%u ID1:%3u[%4.4X] %3u %3u    ",
           cur, init, seq, id0, id1, id1, id2, id3);
  if ((cur | init) && flag)
    u_print0 (vert++, 0, string);
  if (PACKET_TYPE_stim == UTIL_extract_MP_type (buffer)) {
    sprintf (string, fmt_stg[format_flag],
             cur, init, seq, id0, id1, id1, id2, id3);

    if (cur | init)
      u_print0 (vert++, 0, string);
  }

  return vert;
}
int status_ancil (struct MP_buffer *buffer, int ipos)
{
  int vert;
  char text[1024];

  vert = ipos;

  sprintf (text, "data length start(%5d) length(%5d)",
           buffer->packet.index.data_start, buffer->packet.index.data_length);
  u_print0 (vert++, 0, text);

  return vert;
}
int mro_disp (struct MP_buffer *buffer, int width, int ipos, int status,
              int addr)
{
  int index, i, j, vert;
  int hor;
  char text[1024];

  index = UTIL_MP_length (buffer) + 3;
  vert = ipos;
  if (UTIL_extract_MP_type (buffer) <= 0) {
    u_print0 (vert++, 0, "BIU default table in mini packet ???");

/*	    return; /**/
  }
  i = 0;
  if (status >= 0) {
    u_print1 (vert, 0, "      ", i * width);
    for (j = 0; j < 6; j++) {
      u_print1 (vert, j * 3 + 6, "%2.2X ",
                (unsigned char) buffer->packet.mpp.mini_packet[i * width +
                                                               j] & 0xFF);
    }
    vert = vert + 1;
  }
  index = index - abs (status);
  for (i = 0; i < (index / width); i++) {
    u_print1 (vert, 0, "%4.4X: ", i * width + addr);
    for (j = 0; j < width; j++) {
      u_print1 (vert, j * 3 + 6, "%2.2X ",
                (unsigned char) buffer->packet.mpp.mini_packet[i * width + j +
                                                               6] & 0xFF);
    }
    for (j = 0; j < width; j++) {
      char ch;

      ch = buffer->packet.mpp.mini_packet[i * width + j + 6];
      if (ch < 0x20)
        ch = '.';
      if (ch > 0x7E)
        ch = '.';
      u_print1 (vert, j + (width * 3) + 8, "%c", ch);
    }
    vert = vert + 1;
  }

  if (index % width) {
    u_print1 (vert, 0, "%4.4X: ", i * width + addr);
    for (j = 0; j < (index % width); j++) {
      hor = j * 3 + 6;
      u_print1 (vert, hor, "%2.2X ",
                (unsigned char) buffer->packet.mpp.mini_packet[i * width + j +
                                                               6] & 0xFF);
    }
    for (j = 0; j < (index % width); j++) {
      char ch;

      hor = j + (width * 3) + 8;
      ch = buffer->packet.mpp.mini_packet[i * width + j + 6];
      if (ch < 0x20)
        ch = '.';
      if (ch > 0x7E)
        ch = '.';
      u_print1 (vert, hor, "%c", ch);
    }

    u_clear (vert, hor + 3, 1);
    vert = vert + 1;

  }
  if (status >= 0) {
    u_print0 (vert, 1, "      ");
    for (i = 1; i < width * 3; i = i + 3)
      u_print0 (vert, i + 5, "-- ");
    vert = vert + 1;
    u_print0 (vert, 1, " ");
    u_clear (vert, 1, 0);
  }
  return vert;
}
int hfr_disp (struct MP_buffer *buffer, int iwidth, int ipos)
{
  int index, i, j, vert;
  int hor, findex;
  int xor_flag = 0;
  char *format[] = { "%2.2X ",
    "%2.2X ",
    "%2.2X  "
  };
  char *dash[] = { "-- ",
    "-- ",
    "--  "
  };
  int offset = 6;
  int width;

  width = iwidth + 2;
  width = width / 3;
  width = width * 3;

  index = UTIL_MP_length (buffer) + 3 - offset;
  vert = ipos;
  if (UTIL_extract_MP_type (buffer) <= 0) {
    u_print0 (vert++, 0, "BIU default table in mini packet ???");

/*	    return; /**/
  }
  for (i = 0; i < (index / width); i++) {
    u_print1 (vert, 0, "%4.4X: ", i * width / 3);
    for (j = 0; j < width; j++) {
      hor = j * 3 + 6;
      findex = 0;
      if (xor_flag) {
        findex = 1;
        if (j & 1) {
          findex = 2;
          hor -= 1;
        }
      }
      u_print1 (vert, hor, format[j % 3],
                buffer->packet.mpp.mini_packet[i * width + (j ^ xor_flag) +
                                               offset]);
    }
    vert = vert + 1;
  }

  if (index % width) {
    u_print1 (vert, 0, "%4.4X: ", i * width / 3);
    for (j = 0; j < (index % width); j++) {
      hor = j * 3 + 6;
      findex = 0;
      if (xor_flag) {
        findex = 1;
        if (j & 1)
          findex = 2;
        else
          hor -= 1;
      }
      u_print1 (vert, hor, format[j % 3],
                buffer->packet.mpp.mini_packet[i * width + (j ^ xor_flag) +
                                               offset]);
    }
    u_clear (vert, hor + 3, 1);
    vert = vert + 1;
  }
  u_print0 (vert, 1, "      ");
  for (i = 1; i < width * 3; i = i + 3)
    u_print0 (vert, i + 5, dash[(i / 3) % 3]);
  vert = vert + 1;
  u_print0 (vert, 1, " ");
  u_clear (vert, 1, 0);
  return vert;
}
int dump_disp (char *buffer, int width, int ipos)
{
  int index;
  int vert;
  int i, j;
  int hor;
  int xor_flag = 0;
  char format[] = { "%2.2X " };

  index = ((unsigned int) buffer[2] << 8) & 0x00FF00;
  index |= ((unsigned int) buffer[3] << 0) & 0x0000FF;
  index += 4;

  vert = ipos;
  for (i = 0; i < (index / width); i++) {
    u_print1 (vert, 0, "%4.4X: ", i * width);
    for (j = 0; j < width; j++) {
      hor = j * 3 + 6;
      if (xor_flag) {
        if (j & 1) {
          hor -= 1;
        }
      }
      u_print1 (vert, hor, format,
                (unsigned char) buffer[i * width + (j ^ xor_flag)] & 0xFF);
    }
    vert = vert + 1;
  }

  if (index % width) {
    u_print1 (vert, 0, "%4.4X: ", i * width);
    for (j = 0; j < (index % width); j++) {
      hor = j * 3 + 6;
      if (xor_flag) {
        if (j & 1)
          index = 2;
        else
          hor -= 1;
      }
      u_print1 (vert, hor, format,
                (unsigned char) buffer[i * width + (j ^ xor_flag)] & 0xFF);
    }
    u_clear (vert, hor + 3, 1);
    vert = vert + 1;
  }
  u_print0 (vert, 1, "      ");
  for (i = 1; i < width * 3; i = i + 3)
    u_print0 (vert, i + 5, "-- ");
  vert = vert + 1;
  u_print0 (vert, 1, " ");
  u_clear (vert, 1, 0);
  return vert;
}
int raw_disp (struct MP_buffer *buffer, int width, int ipos, int hex_flag)
{
  int index, i, j, vert;
  int hor, findex;
  int xor_flag = 0;
  char *format[] = { "%2.2X ",
    "%2.2X",
    "%2.2X  "
  };

  if (hex_flag == 2)
    xor_flag = 1;

  index = UTIL_MP_length (buffer) + 3;
  vert = ipos;
  if (UTIL_extract_MP_type (buffer) <= 0)
    if (index < 16) {
      u_print0 (vert++, 0, "BIU default table in mini packet ???");

/*	      return; /**/
    };
  for (i = 0; i < (index / width); i++) {
    u_print1 (vert, 0, "%4.4X: ", i * width);
    for (j = 0; j < width; j++) {
      hor = j * 3 + 6;
      findex = 0;
      if (xor_flag) {
        findex = 1;
        if (j & 1) {
          findex = 2;
          hor -= 1;
        }
      }
      u_print1 (vert, hor, format[findex],
                (unsigned char) buffer->packet.mpp.mini_packet[i * width +
                                                               (j ^ xor_flag)]
                & 0xFF);
    }
    vert = vert + 1;
  }

  if (index % width) {
    u_print1 (vert, 0, "%4.4X: ", i * width);
    for (j = 0; j < (index % width); j++) {
      hor = j * 3 + 6;
      findex = 0;
      if (xor_flag) {
        findex = 1;
        if (j & 1)
          findex = 2;
        else
          hor -= 1;
      }
      u_print1 (vert, hor, format[findex],
                buffer->packet.mpp.mini_packet[i * width + (j ^ xor_flag)]);
    }
    u_clear (vert, hor + 3, 1);
    vert = vert + 1;
  }
  u_print0 (vert, 1, "      ");
  for (i = 1; i < width * 3; i = i + 3)
    u_print0 (vert, i + 5, "-- ");
  vert = vert + 1;
  u_print0 (vert, 1, " ");
  u_clear (vert, 1, 0);
  return vert;
}
int _getbuffer_MP (struct MP_buffer *buffer,
                   FILE * input, int iflg, int *rti_start, int *rti_count)
{
  int ilen;
  int rti;

  if (!*rti_count)
    return 0;
  if (*rti_count > 0)
    *rti_count -= 1;
  while (1) {
    ilen = UTIL_getbuffer_MP (buffer, input, iflg);
    rti = UTIL_extract_MP_TIME (buffer);
    if (!*rti_start)
      return ilen;
    if (rti == (long) *rti_start) {
      *rti_start = 0;
      return ilen;
    }
  }
}

main (int argc, char *argv[])
{
  FILE *input = stdin;
  char str0[1024];
  static int type_count[16] = { 16 * 0 };
  char fname[128];
  static int delay = 0;
  static int width = 16;
  int flag, second, icnt;
  int ilen, jlen;
  int ipos;
  int flag_yday = 1;
  int time_offset = 0;
  int rti_start = 0;
  int rti_count = -1;
  int skip_count = 0;
  int hex_flag = 1;

  int len_flag = 1;
  int time_flag = 1;
  int event_flag = 1;
  int evt_flag = 0;
  int evt_delta = 0;
  int seq_flag = 1;
  int hdr_flag = 1;
  int nl_flag = 0;
  int bcd_flag = 0;
  int mp_len;
  long cds[6];
  int i;
  time_t pkt_time, pkt_etime, pkt_epoc;
  struct tm *pkt_tm;
  struct tm *pkt_ev;
  char string[128];
  char wfr, lfdr, wbr, dust, mfr, lp, hfr, dhfr, mro, mrod, stim, ancil;
  char headers = 1;
  int t_mask = -1;
  int eof_flag = 1;
  struct event_time *evt_tim;
  struct event_clock evt_clk;

  buffer = malloc (32768 + 1024);
  fg_flags (argc, argv);
  if (fg_flag ("help") || fg_flag ("h")) {
    fprintf (stdout, "%s   HELP SCREEN\n", title);
    fprintf (stdout, "\n");
    fprintf (stdout, "  TIME\n");
    fprintf (stdout,
             "      When SCLK/SCET information is available it will\n");
    fprintf (stdout,
             "      be used to display the time of the housekeeping\n");
    fprintf (stdout,
             "      record.  The difference between CDS-SCLK adn CHDO-SCLK\n");
    fprintf (stdout,
             "      is applied to the CHDO-SCET and then used to display the\n");
    fprintf (stdout,
             "      time field.  When this 'more or less' accurate time is\n");
    fprintf (stdout,
             "      avaliable, the time field displays as yyyy-dddThh:mm:ss.mmm\n");
    fprintf (stdout, "\n");
    fprintf (stdout, "     +find fn    find archive file\n");
    fprintf (stdout, "     +getmp      get data from current file\n");
    fprintf (stdout, "     +getmpus    un-segmented data set\n");
    fprintf (stdout, "     -width nn   hexdump width (bytes)\n");
    fprintf (stdout, "     -delay nn   nn second delay between update\n");
    fprintf (stdout, "     -rti 0xXX   RTI to start display\n");
    fprintf (stdout, "     -count nn   display nn records\n");
    fprintf (stdout, "     -skip nn    skip nn records\n");
    fprintf (stdout, "     -format     supress screen addressing\n");
    fprintf (stdout, "     -dump       hex dump of entire record\n");
    fprintf (stdout, "     -vsize nn   Limit output to nn lines \n");
    fprintf (stdout, "     -word       hex display 16 bit words\n");
    fprintf (stdout, "     +bcd        display bcd time tags\n");
    fprintf (stdout, "     -len        hex display 16 bit words\n");
    fprintf (stdout, "     -hex        supress hex lines\n");
    fprintf (stdout, "     -time       supress CDS time line\n");
    fprintf (stdout, "     -event      supress event time line\n");
    fprintf (stdout, "     -seq        supress sequence line\n");
    fprintf (stdout, "     -hdr        supress header\n");
    fprintf (stdout, "     -evt        display mp time\n");
    fprintf (stdout, "     -evtx           (delta only)\n");
    fprintf (stdout, "     -evty              adds CDS time tag\n");
    fprintf (stdout, "     -evtz           (delta + packet length)\n");
    fprintf (stdout, "     -evtn nn        (delta other than nn)\n");
    fprintf (stdout, "     -toff nn    offset to apply to time field\n");
    fprintf (stdout, "     -yday       gmtime(tm_yday) display 0 - n-1\n");
    fprintf (stdout, "                   default is now 1 - n\n");
    fprintf (stdout, "     +nl         strategic newline\n");
    fprintf (stdout, "     +eof        quit at eof\n");
    fprintf (stdout, "\n");
    fprintf (stdout, "                 status display enable for:\n");
    fprintf (stdout, "     +all          turn all receiver status on\n");
    fprintf (stdout, "     +wfr\n");
    fprintf (stdout, "     +lfdr\n");
    fprintf (stdout, "     +dust\n");
    fprintf (stdout, "     +wbr\n");
    fprintf (stdout, "     +mfr\n");
    fprintf (stdout, "     +stim\n");
    fprintf (stdout, "     -stim         ST_STIM only\n");
    fprintf (stdout, "     +mro +dmro\n");
    fprintf (stdout, "     +lp\n");
    fprintf (stdout, "     +hfr +dhfr (memory DUMP)\n");
    fprintf (stdout, "     +ancil\n");
    fprintf (stdout, "\n");
    exit (0);
  }
  if (fg_flag ("find")) {
    input = UTIL_find_open (fg_flagc ("find"), "rb");
    if (input)
      fprintf (stderr, "dsp5 find: %s\n", UTIL_find_name ());
    else {
      fprintf (stderr, "dsp5 find: file not found: %s\n", fg_flagc ("find"));
      exit (0);
    }
  }

  if (fg_flag ("yday") == '-')
    flag_yday = 0;
  if (fg_flag ("toff") == '-') {
    time_offset = fg_int ("toff", 0);
  }

  if (fg_flag ("vsize") == '-') {
    vsize = fg_int ("vsize", 0x7FFFFFFF) - 3;
  }

  if ((fg_flag ("evt") == '-') |
      (fg_flag ("evtx") == '-') |
      (fg_flag ("evty") == '-') |
      (fg_flag ("evtz") == '-') | (fg_flag ("evtn") == '-')) {
    evt_flag = 3;
    if (fg_flag ("evtx") == '-')
      evt_flag = 1;
    if (fg_flag ("evtz") == '-')
      evt_flag = 17;
    if (fg_flag ("evty") == '-')
      evt_flag = 9;
    if (fg_flag ("evtn") == '-') {
      evt_flag = 5;
      evt_delta = fg_int ("evtn", 0);
    }

    format_flag = 0;
    hex_flag = 0;
    len_flag = 0;
    time_flag = 0;
    event_flag = 0;
    seq_flag = 0;
    hdr_flag = 0;
  }
  if (fg_flag ("eof") == '+')
    eof_flag = 0;
  if (fg_flag ("nl") == '+')
    nl_flag = 1;
  if (fg_flag ("word"))
    hex_flag = 2;
  if (fg_flag ("hex") == '-')
    hex_flag = 0;
  if (fg_flag ("dump")) {
    hex_flag = 4;
  }
  if (fg_flag ("len") == '-')
    len_flag = 0;
  if (fg_flag ("time") == '-')
    time_flag = 0;
  if (fg_flag ("event") == '-')
    event_flag = 0;
  if (fg_flag ("seq") == '-')
    seq_flag = 0;
  if (fg_flag ("hdr") == '-')
    hdr_flag = 0;
  if (fg_flag ("getmp") == '+') {
    strcpy (fname, UTIL_filename (FILE_MP, FILE_LOCATE_DEFAULT));
    fprintf (stderr, "dsp5 source: %s\n", fname);
    input = fopen (fname, "rb");
    if (!fname)
      exit (0);
  } else if (fg_flag ("getmpus") == '+') {
    strcpy (fname, UTIL_filename (FILE_MPUS, FILE_LOCATE_DEFAULT));
    fprintf (stderr, "dsp5 source: %s\n", fname);
    input = fopen (fname, "rb");
    if (!fname)
      exit (0);
  }
  if (fg_flag ("bcd") == '+')
    bcd_flag = 1;
  width = fg_int ("width", 16);
  delay = fg_int ("delay", 0);
  if (fg_flag ("format") == '-')
    format_flag = 0;

  wfr = fg_flag ("wfr");
  lfdr = fg_flag ("lfdr");
  wbr = fg_flag ("wbr");
  dust = fg_flag ("dust");
  mfr = fg_flag ("mfr");
  stim = fg_flag ("stim");
  lp = fg_flag ("lp");
  hfr = fg_flag ("hfr");
  dhfr = fg_flag ("dhfr");
  mrod = fg_flag ("dmro");
  ancil = fg_flag ("ancil");
  if (fg_flag ("all") == '+') {
    wfr = '+';
    lfdr = '+';
    wbr = '+';
    dust = '+';
    mfr = '+';
    lp = '+';
    hfr = '+';
  }

  if (dhfr) {
    hdr_flag = 0;
    hex_flag = 3;
    len_flag = 0;
    time_flag = 0;
    event_flag = 0;
    seq_flag = 0;
  }
  if (mrod) {
    headers = 0;
    format_flag = 0;
  }
  mro = fg_flag ("mro");
  rti_start = fg_int ("rti", rti_start);
  rti_count = fg_int ("count", rti_count);
  skip_count = fg_int ("skip", skip_count);
  fprintf (stderr, "dsp5 rti_start: %d (%d)\n", rti_start, rti_count);
  if (fg_flag ("time_mask")) {
    t_mask = fg_int ("time_mask", -1);
    fprintf (stderr, "time mask %8.8X\n", t_mask);
  }
  sleep (2);
  u_init ();
  if (hdr_flag) {
    u_print0 (0, 10, " negative length for clear-text");
    u_print0 (1, 10, title);
  }
  for (icnt = -1; icnt < skip_count; icnt++);
  ilen = _getbuffer_MP (buffer, input, eof_flag, &rti_start, &rti_count);
  while (ilen > 0) {
    ipos = 2;
    type_count[UTIL_extract_MP_type (buffer) & 0x0F] += 1;
    epoch = (buffer->packet.cds_tag.epoch[0] << 24) |
      (buffer->packet.cds_tag.epoch[1] << 16) |
      (buffer->packet.cds_tag.epoch[2] << 8) |
      (buffer->packet.cds_tag.epoch[3] << 0);

/*	if(format_flag)
	  u_print1(ipos++,50," Cycle %d", icnt); /**/
    if (headers)
      if (hdr_flag)
        u_print4 (ipos++, 1,
                  " %2.2X %s  (.record_type) %4.4X %4d    ",
                  UTIL_extract_MP_type (buffer) & 0xFF,
                  UTIL_extract_MP_packet_type (buffer),
                  UTIL_MSB_to_long (buffer->record_type), buffer->f_length);

    mp_len = UTIL_MP_length (buffer);
    sprintf (str0, " Len%6.2d   [%d:%d]     Cycle %4d",
             mp_len,
             buffer->packet.index.data_start,
             buffer->packet.index.data_length, icnt);
    if (headers)
      if (len_flag)
        u_print0 (ipos++, 10, str0);
    /*
     *      TIME PROCESSING  ********************************************
     */
    pkt_time = UTIL_extract_PKT_TIME (buffer) & t_mask; /* time from MP */
    pkt_epoc = pkt_time + epoch + time_offset;  /* adjust to UNIX time */
    pkt_tm = gmtime (&pkt_epoc);        /* format conversion */

    if (epoch) {
      pkt_etime = UTIL_event_time (buffer, 0);
      evt_clk.seconds = buffer->packet.cds_tag.begin[0] << 24 |
        buffer->packet.cds_tag.begin[1] << 16 |
        buffer->packet.cds_tag.begin[2] << 8 |
        buffer->packet.cds_tag.begin[3];
      evt_clk.fine = 0;
      evt_tim = UTIL_event_scet (buffer, evt_clk);
      pkt_ev = UTIL_event_scet_tm (*evt_tim, 0);
      sprintf (str0, " CDS Time  %02X%02X%02X%02X %04X %d "
               "(%4d-%03dT%2.2d:%2.2d:%2.2d.%3.3d)",
               buffer->packet.cds_tag.begin[0],
               buffer->packet.cds_tag.begin[1],
               buffer->packet.cds_tag.begin[2],
               buffer->packet.cds_tag.begin[3],
               (pkt_etime & 0x1FFF) << 3,
               (buffer->packet.cds_tag.begin[4] & 0x1E) >> 1,
               pkt_ev->tm_year + 1900,
               pkt_ev->tm_yday + 1,
               pkt_ev->tm_hour,
               pkt_ev->tm_min, pkt_ev->tm_sec, evt_tim->milliseconds % 1000);
    } else {
      sprintf (str0, " Unix Time %8X %4X (%4d-%03dT%2.2d:%2.2d:%2.2d)",
               pkt_epoc,
               (pkt_time & 0x1FFF) << 3,
               pkt_tm->tm_year + 1900,
               pkt_tm->tm_yday + flag_yday,
               pkt_tm->tm_hour, pkt_tm->tm_min, pkt_tm->tm_sec);
    }
    if (headers)
      if (time_flag)
        u_print0 (ipos++, 3, str0);

    pkt_etime = UTIL_event_time (buffer, 0);
    pkt_epoc = pkt_etime + epoch;
    if (epoch) {
      evt_clk.seconds = pkt_etime;
      evt_clk.fine = UTIL_extract_MP_RTI (buffer) << 5;
      evt_tim = UTIL_event_scet (buffer, evt_clk);
      pkt_ev = UTIL_event_scet_tm (*evt_tim, 0);
      sprintf (str0,
               " SC Event  %8X %02X%02X %d (%4d-%03dT%2.2d:%2.2d:%2.2d.%3.3d) new",
               pkt_etime, buffer->packet.mpp.mini_packet[3],
               buffer->packet.mpp.mini_packet[2],
               (buffer->packet.cds_tag.begin[4] & 0x1E) >> 1,
               pkt_ev->tm_year + 1900, pkt_ev->tm_yday + 1, pkt_ev->tm_hour,
               pkt_ev->tm_min, pkt_ev->tm_sec, evt_tim->milliseconds % 1000);
    } else {
      pkt_ev = gmtime (&pkt_epoc);
      sprintf (str0, "SC Event %8X %4X (%2.2d:%2.2d:%2.2d.%3.3d) Epoch %X ",
               pkt_etime,
               (pkt_etime & 0x1FFF) << 3,
               pkt_ev->tm_hour,
               pkt_ev->tm_min,
               pkt_ev->tm_sec, UTIL_extract_MP_RTI (buffer) * 125, epoch);
    }
    if (headers)
      if (event_flag)
        u_print0 (ipos++, 5, str0);

    sprintf (str0,
             "BCD Time Tag %2X%02X %2X%02X %2X %2X %2X -"
             " %2X%02X %2X%02X %2X %2X %2X",
             buffer->packet.ws_tag.A.year[0],
             buffer->packet.ws_tag.A.year[1],
             buffer->packet.ws_tag.A.doy[0],
             buffer->packet.ws_tag.A.doy[1],
             buffer->packet.ws_tag.A.hour,
             buffer->packet.ws_tag.A.minute,
             buffer->packet.ws_tag.A.second,
             buffer->packet.ws_tag.B.year[0],
             buffer->packet.ws_tag.B.year[1],
             buffer->packet.ws_tag.B.doy[0],
             buffer->packet.ws_tag.B.doy[1],
             buffer->packet.ws_tag.B.hour,
             buffer->packet.ws_tag.B.minute, buffer->packet.ws_tag.B.second);
    if (headers)
      if (event_flag)
        if (bcd_flag)
          u_print0 (ipos++, 8, str0);

    pkt_ev = UTIL_event_time_tm (buffer, epoch);
    sprintf (str0,
             "gmtime yr:%4d mth:%2d day:%2d hr:%2d min:%2d sec:%2d do/wk:%d do/yr:%3d dst flg:%d",
             pkt_ev->tm_year,
             pkt_ev->tm_mon,
             pkt_ev->tm_mday,
             pkt_ev->tm_hour,
             pkt_ev->tm_min,
             pkt_ev->tm_sec,
             pkt_ev->tm_wday, pkt_ev->tm_yday, pkt_ev->tm_isdst);
    if (headers)
      if (event_flag)
        if (bcd_flag)
          u_print0 (ipos++, 1, str0);


    string[0] = 0;
    for (i = 0; i < 16; i++) {
      jlen = strlen (string);
      if (type_count[i]) {
        strcat (string, UTIL_get_MP_packet_type (i));
        sprintf (&string[jlen + 5], "%d  ", type_count[i]);
      }
    }
    if (evt_flag) {
      static char stg[16];
      static unsigned long last[16] = { 16 * 0 };
      static unsigned long now;
      static unsigned long delta;
      static int MP_type;
      static int flag;
      static int time_field;

      MP_type = UTIL_extract_MP_type (buffer);

      now = ((unsigned) pkt_etime << 3) | UTIL_extract_MP_TIME (buffer);
      delta = now - last[MP_type];
      last[MP_type] = now;

      strcpy (stg, UTIL_extract_MP_packet_type (buffer));
      strcat (stg, "    ");
      stg[4] = 0;

      flag = evt_flag & 0x02;
      if (evt_flag & 0x04) {
        if (delta)
          if (delta != evt_delta)
            flag = 1;
      } else
        flag = flag | delta;
      if (evt_flag & 0x08)
        time_field = UTIL_extract_PKT_TIME (buffer);
      else
        time_field = UTIL_extract_MP_TIME (buffer);

      if (flag) {
        fprintf (stdout, "%2d %s %4.4X %8.8X.%X",
                 MP_type, stg,
                 time_field, pkt_etime, UTIL_extract_MP_RTI (buffer));
        if (evt_flag & 0x08) {
          fprintf (stdout, " RTI{%4.4X-%4.4X}",
                   (time_field & 0x1FFF) << 3,
                   UTIL_extract_MP_TIME (buffer) & 0xFFF8);
        }
        if (delta)
          fprintf (stdout, " %4X-(%4u)", delta, delta);
        if (evt_flag & 0x10)
          fprintf (stdout, "[%4d]", buffer->packet.index.data_length);
        fprintf (stdout, "\n");
      }
    }

    if (headers)
      if (seq_flag)
        u_print0 (ipos++, 1, string);
    if (UTIL_MP_length (buffer)) {
      int do_raw = 0;
      unsigned int addr = 0;

      if (stim == '+')
        ipos = status_stim (buffer->packet.mpp.mini_packet, ipos, 1);
      if (stim == '-')
        ipos = status_stim (buffer->packet.mpp.mini_packet, ipos, 0);
      if (hfr == '+')
        if (PACKET_TYPE_hfr == UTIL_extract_MP_type (buffer))
          ipos = status_hfr (buffer->packet.mpp.mini_packet, ipos);
      if (lp == '+')
        if (PACKET_TYPE_lp == UTIL_extract_MP_type (buffer))
          ipos = status_lp (buffer->packet.mpp.mini_packet, ipos);
      if (wfr == '+')
        if (PACKET_TYPE_wfr == UTIL_extract_MP_type (buffer))
          ipos = status_wfr (buffer->packet.mpp.mini_packet, ipos);
      if (lfdr == '+')
        if (PACKET_TYPE_lfdr == UTIL_extract_MP_type (buffer))
          ipos = status_lfdr (buffer->packet.mpp.mini_packet, ipos);
      if (wbr == '+')
        if (PACKET_TYPE_wbr == UTIL_extract_MP_type (buffer))
          ipos = status_wbr (buffer->packet.mpp.mini_packet, ipos);
      if (mro == '+')
        if (PACKET_TYPE_mro == UTIL_extract_MP_type (buffer)) {
          do_raw = 6;
          ipos = status_mro (buffer->packet.mpp.mini_packet, ipos, mp_len);
        }
      if (mrod == '+')
        if (PACKET_TYPE_mro == UTIL_extract_MP_type (buffer)) {
          do_raw = -6;
          ipos = addr_mro (buffer->packet.mpp.mini_packet, mp_len);
        }
      if (mfr == '+')
        if (PACKET_TYPE_mfr == UTIL_extract_MP_type (buffer))
          ipos = status_mfr (buffer->packet.mpp.mini_packet, ipos);
      if (ancil == '+')
        ipos = status_ancil (buffer, ipos);
      switch (do_raw) {
       default:
         ipos = mro_disp (buffer, width,
                          ipos, do_raw,
                          addr_mro (buffer->packet.mpp.mini_packet, mp_len));
         break;
       case 0:
         switch (hex_flag) {
          case 1:
          case 2:
            ipos = raw_disp (buffer, width, ipos, hex_flag);
            break;
          case 3:
            ipos = hfr_disp (buffer, width, ipos);
            break;
          case 4:
            ipos = dump_disp ((char *) buffer, width, ipos);
            break;
          default:
            break;
         }
      }
    }
    if (nl_flag)
      putchar (0x0A);
    u_refresh ();
    if (delay)
      sleep (delay);
    icnt += 1;
    ilen = _getbuffer_MP (buffer, input, eof_flag, &rti_start, &rti_count);
  }
  return (0);
}

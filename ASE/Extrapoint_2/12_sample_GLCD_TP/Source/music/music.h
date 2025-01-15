#ifndef MUSIC_H
#define MUSIC_H


//Default: 1.65
#define SPEEDUP 1.6

#define TIMERSCALER 1

#define SECOND 0x17D7840 * TIMERSCALER


typedef char BOOL;
#define TRUE 1
#define FALSE 0

typedef enum note_durations
{
	time_semibiscroma = (unsigned int)(SECOND * SPEEDUP / 64.0f + 0.5), // 1/128
	time_biscroma = (unsigned int)(SECOND * SPEEDUP / 32.0f + 0.5), // 1/64
	time_semicroma = (unsigned int)(SECOND * SPEEDUP / 16.0f + 0.5), // 1/32
	time_croma = (unsigned int)(SECOND * SPEEDUP / 8.0f + 0.5), // 1/16
	time_semiminima = (unsigned int)(SECOND * SPEEDUP / 4.0f + 0.5), // 1/4
	time_minima = (unsigned int)(SECOND * SPEEDUP / 2.0f + 0.5), // 1/2
	time_semibreve = (unsigned int)(SECOND * SPEEDUP + 0.5), // 1
} NOTE_DURATION;

typedef enum frequencies
{
		c1 = 16920,    // 33Hz    k=16920 c1
    c1b = 15900,   // 35Hz    k=15900 b0b / c1b
		c2 = 8500,     // 65Hz    k=8500  c2
    c2b = 8000,    // 69Hz    k=8000  c2b / d1b
    a2b = 5351,    // 103Hz   k=5351 a2b / b2b
    b2 = 4500,     // 123Hz   k=4500 b2
    c3b = 4370,    // 127Hz   k=4370 c3b / d2b
    c3 = 4240,     // 131Hz   k=4240 c3
    d3b = 4005,    // 138Hz   k=4005 d3b / e2b
    d3 = 3779,     // 147Hz   k=3779 d3
    e3b = 3560,    // 155Hz   k=3560 e3b / f2b
    e3 = 3367,     // 165Hz   k=3367 e3
    f3 = 3175,     // 175Hz   k=3175 f3
    g3b = 3005,    // 185Hz   k=3005 g3b / a2b
    g3 = 2834,     // 196Hz   k=2834 g3
    a3b = 2670,    // 208Hz   k=2670 a3b / b2b
    a3 = 2525,     // 220Hz   k=2525 a3
    b3b = 2380,    // 233Hz   k=2380 b3b / c3b
    b3 = 2249,     // 247Hz   k=2249 b3
    c4 = 2120,     // 262Hz   k=2120 c4
    d4b = 2000,    // 277Hz   k=2000 c4b / d4b
    d4 = 1890,     // 294Hz   k=1890 d4
    e4b = 1780,    // 311Hz   k=1780 d4b / e4b
    e4 = 1684,     // 330Hz   k=1684 e4
    f4 = 1592,     // 349Hz   k=1592 f4
    g4b = 1500,    // 370Hz   k=1500 f4b / g4b
    g4 = 1417,     // 392Hz   k=1417 g4
    a4b = 1330,    // 415Hz   k=1330 g4b / a4b
    a4 = 1263,     // 440Hz   k=1263 a4
    b4b = 1190,    // 466Hz   k=1190 a4b / b4b
    b4 = 1125,     // 494Hz   k=1125 b4
    c5 = 1062,     // 523Hz   k=1062 c5
    d5b = 1000,    // 554Hz   k=1000 c5b / d5b
    d5 = 945,      // 587Hz   k=945   d5
    e5b = 890,     // 622Hz   k=890   d5b / e5b
    e5 = 842,      // 659Hz   k=842   e5
    f5 = 796,      // 698Hz   k=796   f5
    g5b = 755,     // 740Hz   k=755   f5b / g5b
    g5 = 708,      // 784Hz   k=708   g5
    a5b = 665,     // 831Hz   k=665   g5b / a5b
    a5 = 632,      // 880Hz   k=632   a5
    b5b = 595,     // 932Hz   k=595   a5b / b5b
    b5 = 563,      // 988Hz   k=563   b5
    c6 = 531,      // 1047Hz  k=531   c6
    d6b = 500,     // 1109Hz  k=500   c6b / d6b
    d6 = 472,      // 1175Hz  k=472   d6
    e6b = 445,     // 1245Hz  k=445   d6b / e6b
    e6 = 420,      // 1319Hz  k=420   e6
    f6 = 396,      // 1397Hz  k=396   f6
    g6b = 373,     // 1480Hz  k=373   f6b / g6b
    g6 = 351,      // 1568Hz  k=351   g6
    a6b = 331,     // 1661Hz  k=331   g6b / a6b
    a6 = 316,      // 1760Hz  k=316   a6
    b6b = 298,     // 1865Hz  k=298   a6b / b6b
    b6 = 281,      // 1976Hz  k=281   b6
    c7 = 265,      // 2093Hz  k=265   c7
    pause = 0      // DO NOT SOUND
} FREQUENCY;



typedef struct 
{
	FREQUENCY freq;
	NOTE_DURATION duration;
} NOTE;

void playNote(NOTE note);
BOOL isNotePlaying(void);

#endif
/* EOF */

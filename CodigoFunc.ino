#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <arduinoFFT.h>
#include <iostream>
using namespace std;
#define AMOSTRAS        2048
#define FREQ_AMOSTRAGEM 4000
#define botao 4
#define botao2 23
#define pinom1 32
#define pinom2 33
int arredondamento1, arredondamento2, arredondamento3, arredondamento4, arredondamento5, arredondamento6;

int valorbotao = 0,valorbotao2 = 0, i = 1, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0;
float c1, c2, c3, c4, c5, c6;

float cordaEg[43][2] = {
        {22.0, 18000.0},{21.0, 17000.0},{20.0, 16000.0},{19.0, 15000.0},{18.0, 14000.0},{17.0, 13000.0},{16.0, 12250.0},
        {15.0, 11500.0},{14.0, 11000.0},{13.0, 10500.0},{12.0, 9000.0},{11.0, 8000.0},{10.0, 7500.0},{9.0, 6000.0},{8.0, 5250.0},{7.0, 4750.0},
        {6.0, 4200.0},{5.0, 3700.0},{4.0, 3350.0},{3.0, 3000.0},{2.0, 2400.0},{0.0, 0},{-2.0, 2400},{-3.0, 3000},{-4.0, 3350},{-5.0, 3700},{-6.0, 4200},
        {-8.0, 5250},{-9.0, 6000},{-10.0, 7500},{-11.0, 8000},{-12.0, 9000},{-13.0, 10500},{-14.0, 11000},{-15.0, 11500},{-16.0, 12250},
        {-17.0, 13000},{-18.0, 14000},{-19.0, 15000}, {-20.0, 16000}, {-21.0, 17000}, {-22.0, 18000}
    };
float cordaA[59][2] = {
        {30, 18000},{29, 17000},{28.0, 16500.0},{27.0, 15500.0},
        {26.0, 15000.0},{25.0, 14000.0},{24.0, 13000.0},{23.0, 12700.0},{22.0, 12000.0},{21.0, 11250.0},{20, 10250},{19.0, 9750.0},{18.0, 9200.0},
        {17.0, 8700.0},{16.0, 8400.0},{15.0, 8100.0},{14.0, 7900.0},{13.0, 7600.0},{12.0, 7000.0},{11.0, 6500.0},{10.0, 6000.0},{9.0, 5500.0},
        {8.0, 5000.0},{7.0, 4500.0},{6.0, 4000.0},{5.0, 3500.0},{4.0, 3000.0},{3.0, 2500.0},{2.0, 2000.0},{0.0, 0.0},{-2.0, 2000.0},{-3.0, 2500.0},
        {-4.0, 3000.0},{-5.0, 3500.0},{-6.0, 4000.0},{-7.0, 4500.0},{-8.0, 5000.0},{-9.0, 5500.0},{-10.0, 6000.0},{-11.0, 6500.0},{-12.0, 7000.0},
        {-13.0, 7600.0},{-14.0, 7900.0},{-15.0, 8100.0},{-16.0, 8400.0},{-17.0, 8700.0},{-18.0, 9200.0},{-19.0, 9750.0},{-20.0, 10250.0},{-21.0, 11250.0},
        {-22.0, 12000.0},{-23.0, 12700.0},{-24.0, 13000.0},{-25.0, 14000.0},{-26.0, 15000.0},{-27.0, 15500.0},{-28.0, 16500.0},{-29.0, 17000.0},{-30.0, 18000.0}
    };
float cordaD[91][2] = {
        {46.0, 22250.0},{45.0, 21750.0},{44.0, 21100.0},{43.0, 20600.0},{42.0, 20100.0},{41.0, 19600.0},{40.0, 19000.0},
        {39.0, 18500.0},{38.0, 18000.0},{37.0, 17500.0},{36.0, 17000.0},{35.0, 16600.0},{34.0, 16200.0},{33.0, 15700.0},{32.0, 15250.0},{31.0, 15000.0},
        {30.0, 14600.0},{29.0, 14200.0},{28.0, 13700.0},{27.0, 13250.0},{26.0, 13000.0},{25.0, 12600.0},{24.0, 12250.0},{23.0, 11900.0},{22.0, 11500.0},
        {21.0, 11000.0},{20.0, 10600.0},{19.0, 10250.0},{18.0, 10000.0},{17.0, 9500.0},{16.0, 9000.0},{15.0, 8500.0},{14.0, 7750.0},{13.0, 7000.0},
        {12.0, 6500.0},{11.0, 5750.0},{10.0, 5000.0},{9.0, 4650.0},{8.0, 4300.0},{7.0, 3900.0},{6.0, 3650.0},{5.0, 3300.0},{4.0, 2950.0},{3.0, 2600.0},
        {2.0, 2250.0},{0.0, 0.0},{-2.0, 2250.0},{-3.0, 2600.0},{-4.0, 2950.0},{-5.0, 3300.0},{-6.0, 3650.0},{-7.0, 3900.0},{-8.0, 4300.0},{-9.0, 4650.0},{-10.0, 5000.0},
        {-11.0, 5750.0},{-12.0, 6500.0},{-13.0, 7000.0},{-14.0, 7750.0},{-15.0, 8500.0},{-16.0, 9000.0},{-17.0, 9500.0},{-18.0, 10000.0},{-19.0, 10250.0},
        {-20.0, 10600.0},{-21.0, 11000.0},{-22.0, 11500.0},{-23.0, 11900.0},{-24.0, 12250.0},{-25.0, 12600.0},{-26.0, 13000.0},{-27.0, 13250.0},{-28.0, 13700.0},
        {-29.0, 14200.0},{-30.0, 14600.0},{-31.0, 15000.0},{-32.0, 15250.0},{-33.0, 15700.0},{-34.0, 16200.0},{-35.0, 16600.0},{-36.0, 17000.0},{-37.0, 17500.0}
    };
float cordaG[139][2] = {
        {70.0, 18500.0},{69.0, 18100.0},{68.0, 17750.0},{67.0, 17500.0},
        {66.0, 17250.0},{65.0, 17000.0},{64.0, 16750.0},{63.0, 16500.0},{62.0, 16250.0},{61.0, 16000.0},{60.0, 15750.0},{59.0, 15500.0},{58.0, 15250.0},{57.0, 15000.0},
        {56.0, 14750.0},{55.0, 14300.0},{54.0, 14000.0},{53.0, 13600.0},{52.0, 13200.0},{51.0, 12800.0},{50.0, 12400.0},{49.0, 12000.0},{48.0, 11600.0},{47.0, 11200.0},
        {46.0, 10800.0},{45.0, 10400.0},{44.0, 10000.0},{43.0, 9750.0},{42.0, 9500.0},{41.0, 9400.0},{40.0, 9300.0},{39.0, 9000.0},{38.0, 8700.0},{37.0, 8550.0},
        {36.0, 8400.0},{35.0, 8200.0},{34.0, 8000.0},{33.0, 7800.0},{32.0, 7625.0},{31.0, 7450.0},{30.0, 7150.0},{29.0, 7075.0},{28.0, 6900.0},{27.0, 6700.0},
        {26.0, 4500.0},{25.0, 6350.0},{24.0, 6050.0},{23.0, 5825.0},{22.0, 5600.0},{21.0, 5400.0},{20.0, 5200.0},{19.0, 5000.0},{18.0, 4750.0},{17.0, 4600.0},
        {16.0, 4300.0},{15.0, 4100.0},{14.0, 3850.0},{13.0, 3500.0},{12.0, 3200.0},{11.0, 3100.0},{10.0, 2950.0},{9.0, 2825.0},{8.0, 2600.0},{7.0, 2350.0},{6.0, 2275.0},
        {5.0, 2125.0},{4.0, 1950.0},{3.0, 1725.0},{2.0, 1600.0},{0.0, 0.0},{-2.0, 1600.0},{-3.0, 1725.0},{-4.0, 1950.0},{-5.0, 2125.0},{-6.0, 2275.0},{-7.0, 2350.0},
        {-8.0, 2600.0},{-9.0, 2825.0},{-10.0, 2950.0},{-11.0, 3100.0},{-12.0, 3200.0},{-13.0, 3500.0},{-14.0, 3850.0},{-15.0, 4100.0},{-16.0, 4300.0},{-17.0, 4600.0},
        {-18.0, 4750.0},{-19.0, 5000.0},{-20.0, 5200.0},{-21.0, 5400.0},{-22.0, 5600.0},{-23.0, 5825.0},{-24.0, 6050.0},{-25.0, 6350.0},{-26.0, 4500.0},{-27.0, 6700.0},
        {-28.0, 6900.0},{-29.0, 7075.0},{-30.0, 7150.0},{-31.0, 7450.0},{-32.0, 7625.0},{-33.0, 7800.0},{-34.0, 8000.0},{-35.0, 8200.0},{-36.0, 8400.0},{-37.0, 8550.0}
    };
float cordaB[139][2] = {
        {70, 18250},{69, 18000},{68, 17750},{67, 17500},{66, 17250},{65, 17000},{64, 16675},{63, 16300},{62, 16100},{61, 15900},{60, 15700},
        {59, 15450},{58, 15100},{57, 14775},{56, 14450},{55, 14125},{54, 13800},{53, 13475},{52, 13150},{51, 12825},{50, 12500},{49, 12175},{48, 11850},{47, 11525},{46, 11200},
        {45, 10875},{44, 10550},{43, 10225},{42, 9900},{41, 9575},{40, 9250},{39, 9010},{38, 8770},{37, 8530},{36, 8290},{35, 8050},{34, 7810},{33, 7570},{32, 7330},{31, 7090},
        {30, 6850},{29, 6610},{28, 6370},{27, 6130},{26, 5890},{25, 5750},{24, 5530},{23, 5310},{22, 5090},{21, 4870},{20, 4650},{19, 4430},{18, 4210},{17, 3990},{16, 3770},
        {15, 3550},{14, 3330},{13, 3110},{12, 2890},{11, 2670},{10, 2500},{9, 2375},{8, 2250},{7, 2125},{6, 2000},{5, 1875},{4, 1750},{3, 1625},{2, 1400},{0, 0},{-2, 1400},
        {-3, 1625},{-4, 1750},{-5, 1875},{-6, 2000},{-7, 2125},{-8, 2250},{-9, 2375},{-10, 2500},{-11, 2670},{-12, 2890},{-13, 3110},{-14, 3330},{-15, 3550},{-16, 3770},
        {-17, 3990},{-18, 4210},{-19, 4430},{-20, 4650},{-21, 4870},{-22, 5090},{-23, 5310},{-24, 5530},{-25, 5750},{-26, 5890},{-27, 6130},{-28, 6370},{-29, 6610},{-30, 6850},
        {-31, 7090},{-32, 7330},{-33, 7570},{-34, 7810},{-35, 8050},{-36, 8290},{-37, 8530},{-38, 8770},{-39, 9010},{-40, 9250},{-41, 9575},{-42, 9900},{-43, 10225},{-44, 10550},
        {-45, 10875},{-46, 11200},{-47, 11525},{-48, 11850},{-49, 12175},{-50, 12500},{-51, 12825},{-52, 13150},{-53, 13475},{-54, 13800},{-55, 14125},{-56, 14450},{-57, 14775},
        {-58, 15100},{-59, 15450},{-60, 15700},{-61, 15900},{-62, 16100},{-63, 16300},{-64, 16675},{-65, 17000},{-66, 17250},{-67, 17500},{-68, 17750},{-69, 18000},{-70, 18250}
    };
float cordaEa[199][2] = {
        {100, 21800},{99, 21675},{98, 21550},{97, 21425},{96, 21300},{95, 21175},{94, 21050},{93, 20925},{92, 20800},
        {91, 20675},{90, 20550},{89, 20425},{88, 20275},{87, 20137},{86, 19999},{85, 19861},{84, 19723},{83, 19585},{82, 19520},{81, 19400},{80, 19280},{79, 19160},
        {78, 19040},{77, 18920},{76, 18800},{75, 18750},{74, 18400},{73, 18050},{72, 17700},{71, 17350},{70, 1700},{69, 16650},{68, 16300},{67, 15950},{66, 15600},
        {65, 15250},{64, 14900},{63, 14625},{62, 14300},{61, 13975},{60, 13650},{59, 13325},{58, 13000},{57, 12675},{56, 12350},{55, 12025},{54, 11700},{53, 11375},
        {52, 11050},{51, 10725},{50, 10500},{49, 10325},{48, 10150},{47, 9975},{46, 9800},{45, 9625},{44, 9450},{43, 9275},{42, 9100},{41, 8925},{40, 8750},{39, 8575},
        {38, 8400},{37, 8225},{36, 8050},{35, 7875},{34, 7700},{33, 7525},{32, 7350},{31, 7175},{30, 7000},{29, 6825},{28, 6650},{27, 6475},{26, 6300},{25, 6000},{24, 5750},
        {23, 5500},{22, 5250},{21, 5000},{20, 4750},{19, 4500},{18, 4250},{17, 4000},{16, 3750},{15, 3500},{14, 3250},{13, 3000},{12, 2750},{11, 2500},{10, 2200},{9, 2050},
        {8, 1900},{7, 1750},{6, 1600},{5, 1450},{4, 1300},{3, 1150},{2, 1000},{0, 0},{-2, 1000},{-3, 1150},{-4, 1300},{-5, 1450},{-6, 1600},{-7, 1750},{-8, 1900},{-9, 2050},
        {-10, 2200},{-11, 2500},{-12, 2750},{-13, 3000},{-14, 3250},{-15, 3500},{-16, 3750},{-17, 4000},{-18, 4250},{-19, 4500},{-20, 4750},{-21, 5000},{-22, 5250},{-23, 5500},
        {-24, 5750},{-25, 6000},{-26, 6300},{-27, 6475},{-28, 6650},{-29, 6825},{-30, 7000},{-31, 7175},{-32, 7350},{-33, 7525},{-34, 7700},{-35, 7875},{-36, 8050},
        {-37, 8225},{-38, 8400},{-39, 8575},{-40, 8750},{-41, 8925},{-42, 9100},{-43, 9275},{-44, 9450},{-45, 9625},{-46, 9800},{-47, 9975},{-48, 10150},{-49, 10325},
        {-50, 10500},{-51, 10725},{-52, 11050},{-53, 11375},{-54, 11700},{-55, 12025},{-56, 12350},{-57, 12675},{-58, 13000},{-59, 13325},{-60, 13650},{-61, 13975},{-62, 14300},
        {-63, 14625},{-64, 14900},{-65, 15250},{-66, 15600},{-67, 15950},{-68, 16300},{-69, 16650},{-70, 17000},{-71, 17350},{-72, 17700},{-73, 18050},{-74, 18400},{-75, 18750},
        {-76, 18800},{-77, 18920},{-78, 19040},{-79, 19160},{-80, 19280},{-81, 19400},{-82, 19520},{-83, 19585},{-84, 19723},{-85, 19861},{-86, 19999},{-87, 20137},{-88, 20275},
        {-89, 20425},{-90, 20550},{-91, 20675},{-92, 20800},{-93, 20925},{-94, 21050},{-95, 21175},{-96, 21300},{-97, 21425},{-98, 21550},{-99, 21675},{-100, 21800}
    };

void leitura();

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned int periodo_amostragem_us;
double amplitude_pico;
unsigned int indice_freq_pico;
double freq_fundamental;
double freq_pico;
double dados_real[AMOSTRAS];
double dados_imag[AMOSTRAS];
unsigned long tempo_corrido;
const uint16_t samples = 64; //This value MUST ALWAYS be a power of 2
const double signalFrequency = 1000;
const double samplingFrequency = 5000;

arduinoFFT FFT = arduinoFFT(dados_real,dados_imag,AMOSTRAS,FREQ_AMOSTRAGEM);


void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  double cycles = (((samples-1) * signalFrequency) / samplingFrequency);
  analogSetAttenuation(ADC_6db);
  pinMode(botao, INPUT);
  pinMode(botao2, INPUT);
  pinMode(pinom1, OUTPUT);
  pinMode(pinom2, OUTPUT);

  periodo_amostragem_us = round(1000000.0 / FREQ_AMOSTRAGEM);
  freq_fundamental = (double)FREQ_AMOSTRAGEM / (double)AMOSTRAS;
}

  void loop()
  {
    while(i <= 6)
    { 

      while(i == 1)
      {
        leitura();
        lcd.setCursor(0,0);
        lcd.print(i);
        lcd.setCursor(2,0);
        lcd.print("- E4 - 330 Hz");
        lcd.setCursor(0,1);
        lcd.print(freq_pico);
        delay(500);
        while(digitalRead(botao2) != 0)
        {
          leitura();
          lcd.setCursor(0,1);
          lcd.print(freq_pico);
          arredondamento1 = freq_pico;
          lcd.setCursor(11,1);
          lcd.print(arredondamento1);

          if(arredondamento1 < 330 && arredondamento1 > 230)    //pinom2 HIGH pinom1 LOW     aperta
          {
            for( j = 0 ; cordaEa[j][0] >= (330 - arredondamento1) ; j++)
            {
              if(cordaEa[j][0] == (330 - arredondamento1)){
                c1 = cordaEa[j][1];}

            }
            
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, HIGH);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);

          }
          if(freq_pico > 330 && freq_pico <=430)
          {
            for( j = 0 ; cordaEa[j][0] >= (330 - arredondamento1) ; j++)
            {
              if(cordaEa[j][0] == (330 - arredondamento1))
              {
                c1 = cordaEa[j][1];
              }
            }

            digitalWrite(pinom1, HIGH);
            digitalWrite(pinom2, LOW);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
         } 
          valorbotao = digitalRead(botao);
          if(valorbotao != 0)
          i++;
      }
     
      while(i == 2)
      {
        leitura();
        lcd.setCursor(0,0);
        lcd.print(i);
        lcd.setCursor(2,0);
        lcd.print("- B3 - 246 Hz");
        lcd.setCursor(0,1);
        lcd.print(freq_pico);
        delay(500);
        while(digitalRead(botao2) != 0)
        {
          leitura();
          lcd.setCursor(0,1);
          lcd.print(freq_pico);
          arredondamento2 = freq_pico;
          lcd.setCursor(11,1);
          lcd.print(arredondamento2);

          if(freq_pico < 246 && freq_pico > 176)    //pinom2 HIGH pinom1 LOW     aperta
          {
             for( k = 0 ; cordaEa[k][0] >= (250 - arredondamento2) ; k++)
            {
              if(cordaEa[k][0] == (250 - arredondamento2))
              {
                c1 = cordaEa[k][1];
              }
            }

            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, HIGH);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
          if(freq_pico > 250 && freq_pico <= 320)
          {
            for( k = 0 ; cordaEa[k][0] >= (250 - arredondamento2) ; k++)
            {
              if(cordaEa[k][0] == (250 - arredondamento2))
              {
                c1 = cordaEa[k][1];
              }
            }

            digitalWrite(pinom1, HIGH);
            digitalWrite(pinom2, LOW);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
        }
        valorbotao = digitalRead(botao);
        if(valorbotao != 0)
        i++;
      }
      while(i == 3)
      {
        leitura();
        lcd.setCursor(0,0);
        lcd.print(i);
        lcd.setCursor(2,0);
        lcd.print("- G3 - 195 Hz");
        lcd.setCursor(0,1);
        lcd.print(freq_pico);
        arredondamento3 = freq_pico;
        delay(500);
        while(digitalRead(botao2) != 0)
        {
          leitura();
          lcd.setCursor(0,1);
          lcd.print(freq_pico);
          lcd.setCursor(11,1);
          lcd.print(arredondamento3);

          if(freq_pico < 195 && freq_pico > 125)    //pinom2 HIGH pinom1 LOW     aperta
          {
            for( l = 0 ; cordaEa[l][0] >= (195 - arredondamento3) ; l++)
            {
              if(cordaEa[l][0] == (195 - arredondamento3))
              {
                c1 = cordaEa[l][1];
              }
            }

            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, HIGH);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
          if(freq_pico > 195 && freq_pico <= 265)
          {
            for( l = 0 ; cordaEa[l][0] >= (195 - arredondamento3) ; l++)
            {
              if(cordaEa[l][0] == (195 - arredondamento3))
              {
                c1 = cordaEa[l][1];
              }
            }
            digitalWrite(pinom1, HIGH);
            digitalWrite(pinom2, LOW);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
        }
        valorbotao = digitalRead(botao);
        if(valorbotao != 0)
        i++;
      }
      while(i == 4)
      {
        leitura();
        lcd.setCursor(0,0);
        lcd.print(i);
        lcd.setCursor(2,0);
        lcd.print("- D3 - 148 Hz");
        lcd.setCursor(0,1);
        lcd.print(freq_pico);
        arredondamento4 = freq_pico;
        delay(500);
        while(digitalRead(botao2) != 0)
        {
          leitura();
          lcd.setCursor(0,1);
          lcd.print(freq_pico);
          lcd.setCursor(11,1);
          lcd.print(arredondamento4);

          if(freq_pico < 148 && freq_pico > 102)    //pinom2 HIGH pinom1 LOW     aperta
          {
            for( m = 0 ; cordaEa[m][0] >= (148 - arredondamento4) ; m++)
            {
              if(cordaEa[m][0] == (148 - arredondamento4))
              {
                c1 = cordaEa[m][1];
              }
            }
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, HIGH);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
          if(freq_pico > 148 && freq_pico <= 194)
          {
            for( m = 0 ; cordaEa[m][0] >= (148 - arredondamento4) ; m++)
            {
              if(cordaEa[m][0] == (148 - arredondamento4))
              {
                c1 = cordaEa[m][1];
              }
            }
            digitalWrite(pinom1, HIGH);
            digitalWrite(pinom2, LOW);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
        }
        valorbotao = digitalRead(botao);
        if(valorbotao != 0)
        i++;
      }

      while(i == 5)
      {
        leitura();
        lcd.setCursor(0,0);
        lcd.print(i);
        lcd.setCursor(2,0);
        lcd.print("- A2 - 110 Hz");
        lcd.setCursor(0,1);
        lcd.print(freq_pico);
        arredondamento5 = freq_pico;
        delay(500);
        while(digitalRead(botao2) != 0)
        {
          leitura();
          lcd.setCursor(0,1);
          lcd.print(freq_pico);
          lcd.setCursor(11,1);
          lcd.print(arredondamento5);

          if(freq_pico < 110 && freq_pico > 80)    //pinom2 HIGH pinom1 LOW     aperta
          {
            for( n = 0 ; cordaEa[n][0] >= (110 - arredondamento5) ; n++)
            {
              if(cordaEa[n][0] == (110 - arredondamento5))
              {
                c1 = cordaEa[n][1];
              }
            }
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, HIGH);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
          if(freq_pico > 110 && freq_pico <= 140)
          {
            for( n = 0 ; cordaEa[n][0] >= (110 - arredondamento5) ; n++)
            {
              if(cordaEa[n][0] == (110 - arredondamento5))
              {
                c1 = cordaEa[n][1];
              }
            }
            digitalWrite(pinom1, HIGH);
            digitalWrite(pinom2, LOW);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
        }
        valorbotao = digitalRead(botao);
        if(valorbotao != 0)
        i++;
      }
      while(i == 6)
      {
        leitura();
        lcd.setCursor(0,0);
        lcd.print(i);
        lcd.setCursor(2,0);
        lcd.print("- E2 - 84 Hz");
        lcd.setCursor(0,1);
        lcd.print(freq_pico);
        arredondamento6 = freq_pico;
        delay(500);
        while(digitalRead(botao2) != 0)
        {
          leitura();
          lcd.setCursor(0,1);
          lcd.print(freq_pico);
          lcd.setCursor(11,1);
          lcd.print(arredondamento6);

          if(freq_pico < 84 && freq_pico > 62)    //pinom2 HIGH pinom1 LOW     aperta
          {
            for( o = 0 ; cordaEa[o][0] >= (84 - arredondamento6) ; o++)
            {
              if(cordaEa[o][0] == (84 - arredondamento6))
              {
                c1 = cordaEa[o][1];
              }
            }
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, HIGH);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
          if(freq_pico > 84 && freq_pico <= 106)
          {
            for( o = 0 ; cordaEa[o][0] >= (84 - arredondamento6) ; o++)
            {
              if(cordaEa[o][0] == (84 - arredondamento6))
              {
                c1 = cordaEa[o][1];
              }
            }
            digitalWrite(pinom1, HIGH);
            digitalWrite(pinom2, LOW);
            delay(c1);
            digitalWrite(pinom1, LOW);
            digitalWrite(pinom2, LOW);
          }
        }
        valorbotao = digitalRead(botao);
        if(valorbotao != 0)
        i++;
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("a afinacao acabou");
      lcd.setCursor(0,1);
      lcd.print("obg pela atencao");
      delay(1000);
    }
  }

  void leitura()
  {
    amplitude_pico = 0;
    indice_freq_pico = 0;


    for(int i = 0; i < AMOSTRAS; i++)
    {
      tempo_corrido = micros();
      dados_real[i] = analogRead(35);
      dados_imag[i] = 0;
      while ((micros() - tempo_corrido) < periodo_amostragem_us)  {}


    }

    FFT.DCRemoval();

    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();

    for(int i =2 ; i < (AMOSTRAS/2) ; i++)
    {
      if(dados_real[i] > amplitude_pico)
      {
        indice_freq_pico = i;
        amplitude_pico = dados_real[i];
      }
      freq_pico = (indice_freq_pico)*freq_fundamental;
    }
  }  
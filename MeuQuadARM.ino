//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//									MEUQUAD.UNI.ME
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//%%%%%%%%%%%%%%%%%%%%%%% FUNÇÕES DE DEBUG DISPONÍVEIS NO ARM %%%%%%%%%%%%%%%%%%%%%%%%

#define DEBUG_ANGULO
//#define DEBUG_OUT_PID
//#define DEBUG_SETPOINTS
//#define DEBUG_VELOCIDADES

//%%%%%%%%%%%%%%%%%%%%%% DEFINIÇÕES GERAIS DO QUADRICOPTERO %%%%%%%%%%%%%%%%%%%%%%%%%%

#define MIN_ESC 1000
#define MAX_ESC 2000

#define MAX_INFLUENCIA_PID 800
#define MAX_INFLUENCIA_PID_Z 800

//PID X
#define KPX 4
#define KIX 0
#define KDX 1
#define CENTROX -0.75

//PID Y
#define KPY 4
#define KIY 0
#define KDY 1
#define CENTROY -0.48

//PID Z
#define KPZ 8
#define KIZ 0
#define KDZ 1

//Definição de pinos
#define M0_PIN 3
#define M1_PIN 5
#define M2_PIN 6
#define M3_PIN 9

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Bibliotecas necessárias
#include "I2Cdev.h"
#include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>
#include <MS5611.h>
#include <Servo.h>
#include "HMC5883L.h"
#include <SPI.h>
#include "PID_v1.h"
#include <SD.h>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Controle
int V_MEDIA;
byte dados[21];
double angleY,angleX,angleZ;
double OutputY, OutputX, OutputZ;
double SetpointX = CENTROX;
double SetpointY = CENTROY;
double SetpointZ = 0;
double CENTROZ = 0;
double MeiodoX = CENTROX;
double MeiodoY = CENTROY;
int modY,modX,modZ;
PID ControleY(&angleY, &OutputY, &SetpointY, KPY, KIY, KDY, DIRECT);
PID ControleX(&angleX, &OutputX, &SetpointX, KPX, KIX, KDX, DIRECT);
PID ControleZ(&angleZ, &OutputZ, &SetpointZ, KPZ, KIZ, KDZ, DIRECT);

//Motores
Servo motor[4];
int v[4];

//Relacionados ao MPU6050
MPU6050 mpu;
int16_t gx, gy, gz;
bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

Quaternion q;
VectorFloat gravity;
float ypr[3];

uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0,
0,0, 0,0, 0x00, 0x00, '\r', '\n' };

volatile bool mpuInterrupt = false;
void dmpDataReady() {
    mpuInterrupt = true;
}

//para o Magnetometro
HMC5883L mag;
int16_t mx, my, mz;
float direcao = 0;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void setup(){
    iniMPU();
    iniMotores();
    iniControle();
    iniDebugMode();
    iniMag();
}

void loop(){
	if (!dmpReady) return;
    while (!mpuInterrupt && fifoCount < packetSize) {
    	//Enquanto não temos interrupção do MPU podemos fazer outras coisas...
        debugMode();

    }
    pegaXYZ();
    pegaMag();
    controlar();
    debugMode();
}

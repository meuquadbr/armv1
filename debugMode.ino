void iniDebugMode(){
	#ifdef DEBUG_ANGULO
		Serial.begin(115200);
		Serial.println("iniciou angulos");
	#endif
	#ifdef DEBUG_OUT_PID
		Serial.begin(115200);
		Serial.println("iniciou saida pid");
	#endif
	#ifdef DEBUG_VELOCIDADES
		Serial.begin(115200);
		Serial.println("iniciou as velocidades");
	#endif
	#ifdef DEBUG_RECEPTOR
		Serial.begin(115200);
		Serial.println("iniciou o receptor");
	#endif
	#ifdef DEBUG_YAW
		Serial.begin(115200);
		Serial.println("iniciou o YAW");
	#endif
	#ifdef DEBUG_EEPROM
		Serial.begin(115200);
		Serial.println("iniciou a EEPROM");
	#endif
	#ifdef DEBUG_CONTROLE
		Serial.begin(115200);
		Serial.println("iniciou o CONTROLE");
	#endif
}

void debugMode(){

	   #ifdef DEBUG_ANGULO
	  Serial.print(angleX);
	  Serial.print(" ");
	  Serial.print(angleY);
	  Serial.print(" ");
	  Serial.print(angleZ);
	  Serial.print(" ");
	  Serial.print(gx);
	  Serial.print(" ");
	  Serial.print(gy);
	  Serial.print(" ");
	  Serial.print(gz);
		Serial.print(" ");
		Serial.print(direcao);
	  Serial.println();
	  #endif

	  #ifdef DEBUG_OUT_PID
	  Serial.print(OutputX);
	  Serial.print(", ");
	  Serial.print(OutputY);
	  Serial.print(", ");
	  Serial.print(OutputZ);
	  Serial.println();
	  #endif
	  #ifdef DEBUG_VELOCIDADES
	  Serial.print(v[0]);
	  Serial.print(",");
	  Serial.print(v[1]);
	  Serial.print(",");
	  Serial.print(v[2]);
	  Serial.print(",");
	  Serial.print(v[3]);
	  Serial.println();
	  #endif
	  #ifdef DEBUG_SETPOINTS
	  Serial.print(SetpointX);
	  Serial.print (" ");
	  Serial.print(SetpointY);
	  Serial.print (" ");
	  Serial.print(SetpointZ);
	  Serial.println();
	  #endif
	}

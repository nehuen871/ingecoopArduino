#include <EEPROM.h>
 
struct Configuracion{
  int TempMax;
  int TempMin;
  int HuMax;
  int HuMin;
  int Thora;
  int Tmin;
};
 
void setup()
{
  /*Configuracion CustomV;
  Configuracion CustomV1;
  Configuracion CustomV2;
  Configuracion CustomV3;
  inicializarConfig(CustomV);
  inicializarConfig(CustomV1);
  inicializarConfig(CustomV2);
  inicializarConfig(CustomV3);
  SetConfig(CustomV,0,300,300,300,300,300,300);
  SetConfig(CustomV1,1,300,300,300,300,300,300);
  SetConfig(CustomV2,2,300,300,300,300,300,300);
  SetConfig(CustomV3,3,300,300,300,300,300,300);*/
  Serial.begin(9600);
  Configuracion customVarTest;
  Configuracion customVarTest1;
  Configuracion customVarTest2;
  Configuracion customVarTest3;
  customVarTest = GetConfiguracion(0);
  customVarTest1 = GetConfiguracion(1);
  customVarTest2 = GetConfiguracion(2);
  customVarTest3 = GetConfiguracion(3);
  Serial.println( "Estructura leida: " );
  Serial.println( customVarTest.TempMax );
  Serial.println( customVarTest.TempMin );
  Serial.println( customVarTest.HuMax );
  Serial.println( customVarTest.HuMin );
  Serial.println( customVarTest.Thora );
  Serial.println( customVarTest.Tmin );
  
  Serial.println( "Estructura1 leida: " );
  Serial.println( customVarTest1.TempMax );
  Serial.println( customVarTest1.TempMin );
  Serial.println( customVarTest1.HuMax );
  Serial.println( customVarTest1.HuMin );
  Serial.println( customVarTest1.Thora );
  Serial.println( customVarTest1.Tmin );
  
  Serial.println( "Estructura2 leida: " );
  Serial.println( customVarTest2.TempMax );
  Serial.println( customVarTest2.TempMin );
  Serial.println( customVarTest2.HuMax );
  Serial.println( customVarTest2.HuMin );
  Serial.println( customVarTest2.Thora );
  Serial.println( customVarTest2.Tmin );
  
  Serial.println( "Estructura3 leida: " );
  Serial.println( customVarTest3.TempMax );
  Serial.println( customVarTest3.TempMin );
  Serial.println( customVarTest3.HuMax );
  Serial.println( customVarTest3.HuMin );
  Serial.println( customVarTest3.Thora );
  Serial.println( customVarTest3.Tmin );
}
void loop()
{
}

void SetConfig(Configuracion vDat,int addres,int TempMaxS,int TempMinS,int HuMaxS,int HuMinS,int ThoraS,int TminS){
    int eeAddress = addres * sizeof(Configuracion);
    vDat.TempMax = TempMaxS;
    vDat.TempMin = TempMinS;
    vDat.HuMax = HuMaxS;
    vDat.HuMin = HuMinS;
    vDat.Thora = ThoraS;
    vDat.Tmin = TminS;
    EEPROM.put( eeAddress, vDat );   
}

Configuracion GetConfiguracion(int addres){
    Configuracion customVar;
    int eeAddress = addres * sizeof(Configuracion);
    EEPROM.get( eeAddress, customVar );  
    return customVar;
}
void inicializarConfig(Configuracion vDat){
    vDat.TempMax = 0;
    vDat.TempMin = 0;
    vDat.HuMax = 0;
    vDat.HuMin = 0;
    vDat.Thora = 0;
    vDat.Tmin = 0;
}

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
  inicializarConfig(CustomV);
  SetConfig(CustomV,0,111,111,111,111,111,111);*/

  Serial.begin(9600);
  Configuracion customVarTest;
  customVarTest = GetConfiguracion(0);
  Serial.println( "Estructura leida: " );
  Serial.println( customVarTest.TempMax );
  Serial.println( customVarTest.TempMin );
  Serial.println( customVarTest.HuMax );
  Serial.println( customVarTest.HuMin );
  Serial.println( customVarTest.Thora );
  Serial.println( customVarTest.Tmin );
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

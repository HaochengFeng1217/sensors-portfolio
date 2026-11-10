#include <Arduino.h>
constexpr int PIN=34, N=2000;
constexpr uint32_t PERIOD=20000;
uint16_t raw[N]; uint32_t stamp[N];
int lowThreshold=0, highThreshold=0, midpoint=0;
bool ready=false, captured=false;
void baseline(){
  long sum=0; int lo=4095,hi=0;
  for(int i=0;i<32;i++){analogRead(PIN);delay(10);}
  for(int i=0;i<200;i++){int v=analogRead(PIN);sum+=v;lo=min(lo,v);hi=max(hi,v);delay(10);}
  int b=(sum+100)/200;
  lowThreshold=b+50;highThreshold=b+110;midpoint=b+80;
  ready=highThreshold<4000;
  Serial.printf("BASELINE mean=%.3f,min=%d,max=%d,lower=%d,midpoint=%d,upper=%d\n",sum/200.0,lo,hi,lowThreshold,midpoint,highThreshold);
  Serial.println(ready?"READY. S captures 40 s. Slowly shade then uncover. B repeats baseline.":"NOT_READY: baseline too close to upper rail. Increase illumination, then B.");
}
void printData(){
  if(!captured)return;
  Serial.println("BEGIN_TASK5_5_LDR_HYSTERESIS");
  Serial.printf("CONFIG lower=%d,midpoint=%d,upper=%d,initial_state=0,period_us=%lu\n",lowThreshold,midpoint,highThreshold,(unsigned long)PERIOD);
  Serial.println("sample,elapsed_us,raw_adc,single_threshold,hysteresis");
  bool h=false;int singleChanges=0,hystChanges=0,prev=0;
  for(int i=0;i<N;i++){
    bool single=raw[i]>=midpoint;bool old=h;
    if(raw[i]>=highThreshold)h=true;else if(raw[i]<=lowThreshold)h=false;
    if(single!=prev)singleChanges++;if(h!=old)hystChanges++;prev=single;
    Serial.printf("%d,%lu,%u,%d,%d\n",i+1,(unsigned long)stamp[i],raw[i],single,h);
  }
  Serial.printf("SUMMARY N=%d,single_switches=%d,hysteresis_switches=%d\n",N,singleChanges,hystChanges);
  Serial.println("END_TASK5_5_LDR_HYSTERESIS");Serial.println("DONE. P reprints stored data. Export before a new capture or baseline.");
}
void capture(){
  if(!ready){Serial.println("Run B for a valid baseline first.");return;}
  Serial.println("START: slowly shade over 15 seconds, pause near partial shade, then slowly uncover. Keep wiring still.");Serial.flush();
  uint32_t start=micros();
  for(int i=0;i<N;i++){
    uint32_t target=start+(uint32_t)i*PERIOD;
    while((int32_t)(micros()-target)<0)delayMicroseconds(50);
    stamp[i]=micros()-start;raw[i]=analogRead(PIN);delay(1);
  }
  captured=true;printData();
}
void setup(){Serial.begin(115200);analogReadResolution(12);analogSetPinAttenuation(PIN,ADC_11db);delay(2000);Serial.println("TASK5_5: GPIO34 LDR; B measures baseline, S starts, P reprints. No automatic capture.");}
void loop(){while(Serial.available()){char c=Serial.read();if(c=='B'||c=='b'){if(captured)Serial.println("Export existing capture before baseline changes.");else baseline();}if(c=='S'||c=='s')capture();if(c=='P'||c=='p')printData();}delay(10);}

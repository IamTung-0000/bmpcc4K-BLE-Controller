#include <Arduino.h>
#include <BlueMagic32.h>

String CilentName;
bool isConnectionAvaiable = false;
bool getCameraInfo = false;
bool isCreateConnection = false;

void setup() {

  Serial.begin(115200);
  Serial.println("---> PLEASE ENTER Cilent Name (7 character) : ");

}

void createBMDConnection()

  {
    
    while(Serial.available())
    {
      //read the input
        vTaskDelay(1);
        char c=Serial.read();
        CilentName+=c;
    }
      if(CilentName.length()>6) {
        
        isConnectionAvaiable = true;
        isCreateConnection = true;
      

      }

  }

void loop() {

  if (isCreateConnection == false) {
    createBMDConnection();
  }

  if (isConnectionAvaiable == true) {
    Serial.println(CilentName);
    BMDConnection.begin(CilentName);
    // BMDConnection.clearPairing();
    BMDControl = BMDConnection.connect();
    isConnectionAvaiable = false;
    getCameraInfo = true;
  }

  if (getCameraInfo == true ) {

    if(BMDControl->changed()) {

      // Get recording state
      bool recording = BMDControl->isRecording();
      // Get the current shutter setting ( as shutter angle )
      int shutter = BMDControl->getShutter();
      // Get the current frame rate setting
      int frameRate = BMDControl->getFrameRate();
      // Get the current iso setting
      int iso = BMDControl->getIso();

      float focusInfo = BMDControl->getFocus();
      float Aperture = BMDControl->getAperture();

      if (iso == 800) { 
        for (float i = 0; i < 100; i++) {
          BMDControl->focus(i/100); 
          delay(100);
        }



        }
      

      Serial.println(iso);
      Serial.println(shutter);
      Serial.println(focusInfo);
      Serial.println(Aperture);
      Serial.println("-------------------");

    }


  }
 

}
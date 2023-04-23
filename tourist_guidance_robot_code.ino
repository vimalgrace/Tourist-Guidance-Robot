
#include<SD.h>
#include<SPI.h>
#include<TMRpcm.h>


#define M1_1 10
#define M1_2 5
#define M2_1 7
#define M2_2 8
#define M1_en 3
#define M2_en 6

int music_delay = 10000;

File myFile;

TMRpcm audio;

//File route1_file;
//File route2_file;
//File route3_file;
//File route4_file;


int motor_speed = 100;




unsigned long time_begin;
unsigned long time_end;

unsigned long tb;
unsigned long te;

double delay_time;


char input_command;

bool record = false;
bool file_opened = true;


void turn_left();
void turn_right();
void go_forward();
void go_backward();
void stop_motor();
void stop_temp();
double convert_micro_to_milli(long,long);

void playback();

//void copy_to_route1();
//void copy_to_route2();
//void copy_to_route3();
//void copy_to_route4();



void play_audio1();
void play_audio2();
void play_audio3();
void play_audio4();

bool audio_playing = false;










class Command{
  public:
  void Execute_Command(char data){

    
    

     
  switch(data){
      case 'A':
          go_forward();
          break;
      
      case 'B':
          go_backward();
          break;
      
      case 'C':
          turn_left();
          break;
      
      case 'D':
          turn_right();
          break;
      
      case 'S':
          stop_temp();
          break;

      case 'E':
        if((motor_speed + 10) > 255){
            motor_speed = 255;
          }

        else{
            motor_speed = motor_speed + 10;
            }
        break;

      case 'F':
        if((motor_speed - 10) < 0){
            motor_speed = 0;
          }

        else{
              motor_speed = motor_speed - 10;
            }
        break;

      
      case 'R':
          record = true;
          Serial.println("recording start....");
          break;
      
      case 'r':
          record = false;
          Serial.println("recording end....");
          break;
      
      case 'P':
          Serial.println("play back started");
          playback();
          break;

     


      case 'K':
          play_audio1();
          break;

      case 'L':
         play_audio2();
         break;

      case 'M':
         play_audio3();
         break;

      case 'N':
         play_audio4();
         break;

      case 'k':
         delay(music_delay);
         audio.disable();
         Serial.println("Audio finished..");
         myFile = SD.open("data1.txt",FILE_WRITE);
         myFile.println(music_delay);
         break;

      case 'l':
         delay(music_delay);
         audio.disable();
         Serial.println("Audio finished..");
         myFile = SD.open("data1.txt",FILE_WRITE);
         myFile.println(music_delay);
         break;

      case 'm':
        delay(music_delay);
        audio.disable();
        Serial.println("Audio finished..");
        myFile = SD.open("data1.txt",FILE_WRITE);
        myFile.println(music_delay);
        break;

      case 'n':
       delay(music_delay);
       audio.disable();
       Serial.println("Audio finished..");
       myFile = SD.open("data1.txt",FILE_WRITE);
       myFile.println(music_delay);
       break;

//      case 'W':
//        //copy the files to route 1
//        copy_to_route1();
//        break;
//        
//      case 'w':
//          break;
//
//      case 'X':
//        //copy the files to route 2
//        copy_to_route2();
//        break;
//
//      case 'x':
//         break;
//
//      case 'Y':
//         //copy the files to route 3
//         copy_to_route3();
//         break;
//        
//      case 'y':
//         break;
//
//      case 'Z':
//        //copy the files to route 4
//        copy_to_route4();
//        break;
//
//      case 'z':
//         break;

      
      
      
      default:
          Serial.println("Default block is executed...");
          stop_motor();
          if(record){
            
            time_end = micros();
            te = time_end;
            Serial.print("Time end = ");
            Serial.println(te);
            double res = convert_micro_to_milli(tb,te);
            delay_time = res;
            myFile.println(delay_time);
            Serial.print("Result= ");
            Serial.println(delay_time);
           
          }
        
          
      
          
    }
  }
  
};



Command cm;



void setup(){
  
  
 
  Serial.begin(9600);
  while(!Serial){
    
  }

  if(!SD.begin(4)){
    Serial.println("SD card failed...");  
  }

  else{
    Serial.println("SD card connected...");
  }
  
  
  
  pinMode(M1_1,OUTPUT);
  pinMode(M1_2,OUTPUT);
  pinMode(M2_1,OUTPUT);
  pinMode(M2_2,OUTPUT);
  pinMode(M1_en,OUTPUT);
  pinMode(M2_en,OUTPUT);

  audio.speakerPin = 9;

  audio.volume(1);

  audio.setVolume(6);

  audio.quality(1);

  
  

  
  
  
 
  
}



void loop(){

  if(record && file_opened){
    myFile = SD.open("data1.txt",FILE_WRITE | O_TRUNC);

    if(SD.exists("data1.txt")){
      Serial.println("data1 file created and present");
      
    }
    else{
      Serial.println("data1 file not created and not present");
    }
    
    file_opened = false;
  }

  if(!record){
    file_opened = true;
    myFile.close();
  }

  if(Serial.available()>0){
    Serial.print("Serial available = ");
    Serial.println(Serial.available());
    char data = Serial.read();
    Serial.println(data);
    Serial.println("Data printed...");

    cm.Execute_Command(data);
    
    
    
  }
}




void turn_left(){
  
  if(record){
          input_command = 'C';
          myFile.println(input_command);
          
          time_begin = micros();
          tb = time_begin;
          
          Serial.print("Time start = ");
          Serial.println(tb);
      }
      
  analogWrite(M1_en,motor_speed);
  analogWrite(M2_en,motor_speed);
  
  digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,HIGH);
  

  digitalWrite(M2_1,HIGH);
  digitalWrite(M2_2,LOW);
 
}



void turn_right(){
  if(record){
          input_command = 'D';
          myFile.println(input_command);
          
          time_begin = micros();
          tb = time_begin;
          
          Serial.print("Time start = ");
          Serial.println(tb);
      }
  analogWrite(M1_en,motor_speed);
  analogWrite(M2_en,motor_speed);
  
  digitalWrite(M1_1,HIGH);
  digitalWrite(M1_2,LOW);
  

  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,HIGH);
 
}


void go_forward(){
   Serial.println("Going forward...");
   if(record){
        input_command = 'A';
        myFile.println(input_command);
        
        time_begin = micros();
        
        tb = time_begin;
        
        Serial.print("Time start = ");
        Serial.println(tb);
    }
  
  
  analogWrite(M1_en,motor_speed);
  analogWrite(M2_en,motor_speed);
  
  digitalWrite(M1_1,HIGH);
  digitalWrite(M1_2,LOW);
  

  digitalWrite(M2_1,HIGH);
  digitalWrite(M2_2,LOW);
}



void go_backward(){
  Serial.println("Going backward...");
  
    if(record){
        input_command = 'B';
        myFile.println(input_command);
        
        time_begin = micros();
        tb = time_begin;
        
        Serial.print("Time start = ");
        Serial.println(tb);
    }
  
  analogWrite(M1_en,motor_speed);
  analogWrite(M2_en,motor_speed);
  
  digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,HIGH);
  

  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,HIGH);
}




void stop_temp(){
  if(record){
          input_command = 'S';
          myFile.println(input_command);
          
          time_begin = micros();
          tb = time_begin;
          
          Serial.print("Time start = ");
          Serial.println(tb);
      }
      
  analogWrite(M1_en,0);
  analogWrite(M2_en,0);
  
  digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,LOW);
  

  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,LOW);
  
}



void stop_motor(){
  
  analogWrite(M1_en,0);
  analogWrite(M2_en,0);
  
  digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,LOW);
  

  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,LOW);
  
}


void playback(){

  
  int count = 0;
  int closing_count = 0;
  
  record = false;
  
  myFile.close();

  myFile = SD.open("data1.txt");

 
  
  while(myFile.available()){
    String a1 = myFile.readStringUntil('\n');
    String a2 = myFile.readStringUntil('\n');

    char b1 = a1.c_str()[0];
    double b2 = a2.toDouble();
    count = count + 2;
    
    Serial.println(b1);
    Serial.println(b2);

    stop_motor();

    if(b1 == 'K' || b1 == 'L' || b1 == 'M' || b1 == 'N'){
      myFile.close();
      
      closing_count = count;
      
      cm.Execute_Command(b1);
      delay(b2);
      
      audio.disable();
      
      myFile = SD.open("data1.txt");

      int recount = 0;
      while(myFile.available() && recount<closing_count){
        myFile.readStringUntil('\n');
        myFile.readStringUntil('\n');
        recount += 2;
      }
    }

    else{
      cm.Execute_Command(b1);
      delay(b2);
      stop_motor();
    }
    

    

    }
   
   myFile.close();
   Serial.println("Playback ended....");
  
  
}


double convert_micro_to_milli(long a, long b){
  Serial.println(a);
  Serial.println(b);
  long result = b-a;
  return (double)result*0.001;
  
}


//void copy_to_route1(){
//
// if(record){
//   myFile.close();
//  route1_file = SD.open("route1.txt",FILE_WRITE | O_TRUNC);
//  
//   myFile = SD.open("data1.txt");
//
//  while(myFile.available()){
//    String a = myFile.readStringUntil("\n");
//    route1_file.println(a);
//  }
//
//  route1_file.close();
//  file_opened = true;
//  Serial.println("Route 1 Saved...");
//  }
//  
//  
//}
//
//
//void copy_to_route2(){
//
// if(record){
//   myFile.close();
//  route2_file = SD.open("route2.txt",FILE_WRITE | O_TRUNC);
//  
//   myFile = SD.open("data1.txt");
//
//  while(myFile.available()){
//    String a = myFile.readStringUntil("\n");
//    route2_file.println(a);
//  }
//
//  route2_file.close();
//  file_opened = true;
//  Serial.println("Route 2 Saved...");
//  }
//  
//  
//}
//
//void copy_to_route3(){
//
// if(record){
//   myFile.close();
//  route3_file = SD.open("route3.txt",FILE_WRITE | O_TRUNC);
//  
//  myFile = SD.open("data1.txt");
//
//  while(myFile.available()){
//    String a = myFile.readStringUntil("\n");
//    route3_file.println(a);
//  }
//
//  route3_file.close();
//  file_opened = true;
//  Serial.println("Route 3 Saved...");
//  }
//  
//  
//}
//
//void copy_to_route4(){
//
// if(record){
//   myFile.close();
//  route4_file = SD.open("route4.txt",FILE_WRITE | O_TRUNC);
//  
//  myFile = SD.open("data1.txt");
//
//  while(myFile.available()){
//    String a = myFile.readStringUntil("\n");
//    route4_file.println(a);
//  }
//
//  route4_file.close();
//  file_opened = true;
//  Serial.println("Route 4 Saved...");
//  }
//  
//  
//}


void play_audio1(){
  Serial.println("Audio started..");

  if(record){
        input_command = 'K';
        myFile.println(input_command);
        myFile.close();
        
     }
  
  
  audio.play("place1.wav");
  
  
 
  
  Serial.println("place1 attached");
}


void play_audio2(){
  Serial.println("Audio started..");
  if(record){
         input_command = 'L';

        myFile.println(input_command);

        myFile.close();
        
        
    }
  
  
  Serial.println("I am audio 2...");

  audio.disable();
  
  audio.play("place2.wav");
  
  
 
  Serial.println("place2 attached");
}


void play_audio3(){
  Serial.println("Audio started..");
 
  if(record){
          input_command = 'M';

        myFile.println(input_command);
        myFile.close();
        
    }
  
 
  audio.play("place3.wav");
  
  
  Serial.println("place3 attached");
}


void play_audio4(){
  Serial.println("Audio started..");
  
  if(record){
        input_command = 'N';

        myFile.println(input_command);
        
        myFile.close();
    }
  
  
  audio.play("1.wav");

  

  Serial.println("place4 attached");
}



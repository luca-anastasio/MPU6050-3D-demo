import toxi.geom.*;
import toxi.geom.mesh.*;
import toxi.processing.*;
import processing.serial.*;
import processing.opengl.*;

//variabili globali

ToxiclibsSupport gfx;
TriangleMesh mesh;

Serial port;                         // The serial port
char[] teapotPacket = new char[14];  // InvenSense Teapot packet
int serialCount = 0;                 // current packet byte position
int synced = 0;
int interval = 0;

float[] q = new float[4];
Quaternion quat = new Quaternion(1, 0, 0, 0);

float[] gravity = new float[3];
float[] euler = new float[3];
float[] ypr = new float[3];

void setup(){
  size(600, 600, OPENGL);
  mesh=(TriangleMesh)new STLReader().loadBinary(sketchPath("person.stl"),STLReader.TRIANGLEMESH);
  mesh.scale(10);
  
  
    
  smooth();
  
  gfx=new ToxiclibsSupport(this);
  println(Serial.list());
  //String portName = "COM6";
  String portName = "/dev/ttyUSB0";
  port = new Serial(this, portName, 115200);
  port.write('r');
}


void draw(){
   if (millis() - interval > 1000) {
        // resend single character to trigger DMP init/start
        // in case the MPU is halted/reset while applet is running
        port.write('r');
        interval = millis();
    }
  background(0);
  lights();
  
  translate(width/2,height/2,0);
  float[] axis = quat.toAxisAngle();
  rotate(axis[0], -axis[1], axis[3], axis[2]);
  //gfx.origin(new Vec3D(),200);
  noStroke();
  fill(0, 0, 255, 255);
  gfx.mesh(mesh,true,0);
 
  
}

void serialEvent(Serial port) {
    interval = millis();
    while (port.available() > 0) {
        int ch = port.read();

        if (synced == 0 && ch != '$') return;   // initial synchronization - also used to resync/realign if needed
        synced = 1;
        print ((char)ch);

        if ((serialCount == 1 && ch != 2)
            || (serialCount == 12 && ch != '\r')
            || (serialCount == 13 && ch != '\n'))  {
            serialCount = 0;
            synced = 0;
            return;
        }

        if (serialCount > 0 || ch == '$') {
            teapotPacket[serialCount++] = (char)ch;
            if (serialCount == 14) {
                serialCount = 0; // restart packet byte position
                
                // get quaternion from data packet
                q[0] = ((teapotPacket[2] << 8) | teapotPacket[3]) / 16384.0f;
                q[1] = ((teapotPacket[4] << 8) | teapotPacket[5]) / 16384.0f;
                q[2] = ((teapotPacket[6] << 8) | teapotPacket[7]) / 16384.0f;
                q[3] = ((teapotPacket[8] << 8) | teapotPacket[9]) / 16384.0f;
                for (int i = 0; i < 4; i++) if (q[i] >= 2) q[i] = -4 + q[i];
                
                // set our toxilibs quaternion to new data
                quat.set(q[0], q[1], q[2], q[3]);
                            }
        }
    }
}
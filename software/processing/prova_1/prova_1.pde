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
  mesh.scale(5);
  
  
    
  smooth();
  
  gfx=new ToxiclibsSupport(this);
  println(Serial.list());
  String portName = "COM10";
  //String portName = "/dev/ttyUSB4";
  port = new Serial(this, portName, 115200);
  port.write('r');
}


void draw(){
  
      while (port.available() > 0) {
      float pitch =Integer.parseInt(port.readStringUntil(' ').trim());
      print(pitch);
      float roll =Integer.parseInt(port.readStringUntil(' ').trim());
      print(roll);
      float yaw= Integer.parseInt(port.readStringUntil('\n').trim());
      println(yaw);
      pitch=pitch*3.14/(180*67);
      roll=roll*3.14/(180*67);
      yaw=yaw*3.14/(180*67);
      quat = Quaternion.createFromEuler(roll,yaw,pitch);
     
      
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
import processing.serial.*;
Serial serial_port;  
int serial_port_value;    

float y;

// The statements in the setup() function 
// run once when the program begins
void setup() {
  size(640, 360);  // Size should be the first statement
  stroke(255);     // Set stroke color to white
  
  y = height * 0.5;
  
  String portName = Serial.list()[0]; //com3, same as arduino
  serial_port = new Serial(this, portName, 9600);
  
  println(Serial.list());
}

// The statements in draw() are run until the 
// program is stopped. Each statement is run in 
// sequence and after the last line is read, the first 
// line is run again.
void draw() { 
  background(0);   // Set the background to black
  line(0, y, width, y);

  if ( serial_port.available() > 0)  // If data is available,
  { 
    serial_port_value = serial_port.read();         // read it and store it in val
    println(serial_port_value);
  }
  else {
    println("Serial port data not available");
  }  
}

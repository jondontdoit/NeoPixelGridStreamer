import processing.video.*;

//////////////////////////////////
// GLOBAL SETTINGS
//////////////////////////////////

static int xSize =        28; // Pixels in the horizontal direction
static int ySize =        28; // Pixels in the vertical direction
static boolean zigzag = true; // Are the strips wired in a zig-zag pattern?

static String filename = "circle_animation_small.mov";

//////////////////////////////////
// INTERNAL VARIABLES
//////////////////////////////////
Movie video;
int frame_count = 0;
float videoDuration;
static int pixelSize =    10; // Display 
long startTime;
PrintWriter output;

//////////////////////////////////
// SETUP
//////////////////////////////////
void setup() {
  size(280, 280);
  background(0);
  stroke(0,0);
  
  output = createWriter("output.txt"); 
      
  println("Opening Video...");
  video = new Movie(this, filename);  
  video.play();
  
  videoDuration = video.duration();
  print("Duration: ");
  println(videoDuration);
  
  if (videoDuration == 0.0) exit();
  
  println("Processing...");
  startTime = millis();
}

//////////////////////////////////
// LOOP
//////////////////////////////////
void draw() {
  
  if (video.available()) {
    video.read();
    
    //Load video frame into image container
    PImage frame = createImage(xSize, ySize, RGB);
    frame.copy(video, 0, 0, video.width, video.height, 0, 0, xSize, ySize);
  
    // Display frame
    image(frame, 0, 0);
  
    frame_count++;

    for (int x=0; x<frame.width; x++) {
      for (int y=0; y<frame.height; y++) {
        
        color c;
        if (zigzag && x%2==0) {
          c = frame.get(x, y);
        } else {
          c = frame.get(x, ySize-y-1);
        }
       
        //print(red(c));
        //print("\t");
        //print(green(c));
        //print("\t");
        //print(blue(c));
        //println();
        
        fill(c);
        rect(x*pixelSize, y*pixelSize, pixelSize, pixelSize);
        
        output.print((int(red(c))));
        output.print(",");
        output.print((int(green(c))));
        output.print(",");
        output.print((int(blue(c))));
        output.print(",");
        
      }
    }
    
  } 
  
  float videoTime = video.time();
  
  print(nf(videoTime, 0, 1));
  print("/");
  print(nf(videoDuration, 0, 1));
  print(" (");
  print(frame_count);
  print(")");  
  println();
  
  if (videoTime >= videoDuration) wrapUp();

}

//////////////////////////////////
// FUNCTIONS
//////////////////////////////////
void keyPressed() {
  wrapUp();
}   

void wrapUp() {
  print(frame_count);
  println(" frames processed");
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
  //launch(sketchPath("")+"anmBuilder.py");
  println("File saved");
  exit();
}  
  

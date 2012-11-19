int number_of_boxes = 30;
float width_of_box = 20;
float theta;

void setup() {
  size(400, 400);
}

void draw() {
  background(255);

  float circumference = number_of_boxes*width_of_box;
  float radius = circumference/TWO_PI;
  float step = TWO_PI/number_of_boxes;
  // everything is drawn from the center
  translate(width/2,height/2);
  
  noFill();
  
  ellipse(0,0, radius*2, radius*2);
  
  fill(170,40);
  
  for (float x = 0; x < TWO_PI; x += step) {
    pushMatrix();
    rotate(x);
    translate(0, radius);
    rectMode(CENTER);
    rect(0,0,width_of_box,width_of_box);
    popMatrix();
  }
}

void mousePressed() {
  if (mouseX < width/2) {
    number_of_boxes+=1;
  }
  else {
    number_of_boxes-=1;
  }
}

int x_size = 400;
int y_size = 400;

void setup() {
  size(x_size,y_size);
}

void draw(){
    for (int i=0; i < x_size; i+=10) {
      for (int j=0; j < y_size; j+=10) {
        if ( (pow(i,2)*pow(j,2))%2 == 0)
        rect(i,j,10,10);
      }
    }

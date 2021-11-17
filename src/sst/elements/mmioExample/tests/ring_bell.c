int main(){
  volatile unsigned char* bell = (unsigned char*)(0xFFFFFFF0);
  for(int i = 0; i < 10; ++i){
    bell[0] = 1;
  }

  volatile int* dumb = (int*) malloc(sizeof(int));
  while(1){
    dumb[0] += 1;
    if(dumb[0] == 1000){
      break;
    }
  }
}

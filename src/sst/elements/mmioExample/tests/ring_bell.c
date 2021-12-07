int main(){
  volatile unsigned char* bell = (unsigned char*)(0xFFFFFFF0);
  for(int i = 0; i < 100; ++i){
    bell[0] = 1;
  }
}

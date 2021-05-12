#include<stdio.h>

int main(){
  char numberPlate[2][7];
  _Bool act=0;
  int i;
  while (scanf("%s",numberPlate[act])!=EOF){
    act=1-act;
    printf("%d\n",act);
    if(act==0){
        for(i=0;i<7;i++){
            if(numberPlate[0][i]>numberPlate[1][i]){
                printf("0\n");
                break;
            }
            else if(numberPlate[0][i]<numberPlate[1][i]){
                printf("1\n");
                break;
            }
        }
    }
}
return(0);
}

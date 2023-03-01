#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 256

void printMatrix(int **matris,int N)
{
	int i,j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%2d ", matris[i][j]);
        printf("\n");
    }
}
void printRenkler(int **matris,char renkler[11][20],int N)
{
	int i,j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++){
        	if(j!=N-1){
        		 printf("%s -", renkler[matris[i][j]]);
			}else{
				 printf("%s ", renkler[matris[i][j]]);
			}
		}      	
           
        printf("\n");
    }
}
int findRenk(char *renk,char renkler[20][20]){
	int i,n=10;
	for(i=0;i<n;i++){
		if(strcmp(renk,renkler[i])==0){
			return i;
		}
	}	
}
void print(int **matris,char renkler[11][20],int no,int N){
	if(no==0){
		printf("----------------Matrisin Ilk Hali /Sayilarla Ifade --------------------\n");
		printMatrix(matris,N);
		printf("----------------Matrisin Ilk Hali /Renklerle Ifade --------------------\n");
		printRenkler(matris,renkler,N);
		printf("\n");
	}else{
		printf("----------------Matrisin Son Hali /Sayilarla Ifade --------------------\n");
		printMatrix(matris,N);
		printf("----------------Matrisin Son Hali /Renklerle Ifade --------------------\n");
		printRenkler(matris,renkler,N);
	}
	
}
int **shift(int**matris,int row,int sh_num,int sh_arr[11],int N){
	int i,j,tmp;
	sh_arr[row]++;

	while(sh_num !=0 )
	{
	       
		tmp = matris[row][N - 1];  
	    for(i = N - 1; i > 0; i--)
		{
			matris[row][i] = matris[row][i - 1];  
	    	
		} 
	    	matris[row][0] = tmp;
	    	sh_num--;		
	}	
	return matris;
}

int ustSatirKiyas(int **matris,int row,int sh_arr[11],int secim,int N)
{
	int i,j,flag=0,kontrol,anlik=0;
	kontrol=row-1;
	if(secim==2){
		printf("--------------------------%d. Satirda Islem Yapilmaktadir / %d.SHIFT ISLEMI---------------------------",row+1,sh_arr[row]);
		printf("\n");
		printMatrix(matris,N);
	}
	
	
	
   	while(flag==0 && kontrol>=0)
	   {
	   	anlik=0;
	   	while(flag==0 && anlik<N)
		   {
		   	if(matris[row][anlik]==matris[kontrol][anlik]){
		   		flag=1;
			   }
			   anlik++;
		   }
		   kontrol--;
	   }
	   if(flag==0){
	   	return 1;
	   }else{
	   	return 0;
	   }
}
int uniqueMatrix(int**matris, int row,int sh_arr[11],int secim,int N)
{
	int i,x,flag=0,count=0;
    if (row == N){
    	return 1;
	}
	else if(row==0 ){
		return 0;
	}
	else{
		if(ustSatirKiyas(matris,row,sh_arr,secim,N)==1){
			uniqueMatrix(matris,row+1,sh_arr,secim,N);
		}else{
			count=sh_arr[row];
			while(sh_arr[row]!=N-1 &&ustSatirKiyas(shift(matris,row,1,sh_arr,N),row,sh_arr,secim,N)!=1){
				count++;
			}
			if(count!= N-1 ){
				uniqueMatrix(matris,row+1,sh_arr,secim,N);
			}else{
				if(sh_arr[row-1]==N-1){
				return 0;
				}
				matris=shift(matris,row,1,sh_arr,N);
				matris=shift(matris,row-1,1,sh_arr,N);
				sh_arr[row]=0;
				return uniqueMatrix(matris,row-1,sh_arr,secim,N);
			}				
			}		
			
		}
	}
    
    

int main()
{
	int** matris;
	int sh_arr[11]={0};
	int i,j=0,sh_num,z,secim,N;
	char *next_field;
	char line[LINESIZE];
	FILE *input_file = fopen ("matris3.txt", "r" );
	char renkler[11][20]={"Kirmizi","Turuncu","Sari","Yesil","Mavi","Mor","Siyah","Kahverengi","Gri","Beyaz","\0"};
	matris=malloc(sizeof(int*)*11);
	for(i=0;i<11;i++){
		matris[i]=malloc(sizeof(int)*11);
	}
	i=-1;
	while (1) {
    	fgets(line, sizeof(line), input_file); 
  	 	if (feof(input_file))  
     		 break;
     	i++;
     	j=0;
   		next_field = strtok(line, " \n");
   		

     	while (next_field != NULL){
     		z=findRenk(next_field,renkler);
     		matris[i][j]=z;
     		j++;
     		next_field = strtok(NULL, " \n");	
	 }
	 
  }
  	N=j;
  	//matris=shift(matris,3,sh_num,sh_arr); //0
  	printf("----------------------------------ALGORITMA ANALIZI PROJE ODEVI / BACKTRACKING --------------------------------------\n\n");
  	printf("1-- NORMAL MODDA CALISTIR \n");
	printf("2-- DETAY MODDA CALISTIR \n");
	printf("\nSECIMINIZI YAPINIZ [1-2] \n");
	scanf("%d",&secim);	
	if(secim==1)
	{
		print(matris,renkler,0,N);
		if (uniqueMatrix(matris, 1,sh_arr,secim,N)){
    		print(matris,renkler,1,N);
		}else
		{
			printf("\n----------------Matrisin Son Hali --------------------\n \n");
			printf("HIC BIR SEKILDE COZUM URETILEMEMISTIR !");
		}
	}
	if(secim==2)
	{
		print(matris,renkler,0,N);
		if (uniqueMatrix(matris, 1,sh_arr,secim,N)){
    		print(matris,renkler,1,N);
		}else
		{	
		printf("\n----------------Matrisin Son Hali --------------------\n \n");
			printf("HIC BIR SEKILDE COZUM URETILEMEMISTIR !");
		}
	}
		
	return 0;
}

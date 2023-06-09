#include<stdio.h>
#include<omp.h>


int main(){
	
	int n;
	printf("Enter  the value of  N: \n");
	scanf("%d",&n);
	
	int A[n][n],B[n][n];
	int C[n][n],D[n][n];
	
	
	#pragma omp parallel private(A,B) num_threads(10)
	{
		#pragma omp single copyprivate(A,B)
		{
			//Matrix A
			printf("Enter values of Matrix A: \n");
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					scanf("%d",&A[i][j]);
				}
			}
			
			//B
			printf("Enter values of Matrix B: \n");
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					scanf("%d",&B[i][j]);
				}
			}
			
			printf("matrixes are red by thread id : %d\n",omp_get_thread_num());
		}
		
		
		#pragma omp sections
		{
			// C - multiplication
			#pragma omp section
			{
				#pragma omp parallel for num_threads(5)
				for(int i=0;i<n;i++){
					for(int j=0;j<n;j++){
						int temp =0;
						for(int k=0;k<n;k++){
							temp+= A[i][k]*B[k][j];
						}
						C[i][j] = temp;
					}
				}
				
				printf("Multiplication by thread id : %d\n",omp_get_thread_num());
				
			}
			
			
			// D - addition
			#pragma omp section
			{
				#pragma omp parallel for num_threads(5)
				for(int i=0;i<n;i++){
					for(int j=0;j<n;j++){
						D[i][j] = A[i][j] + B[i][j];
					}
				}
				printf("Addition by thread id : %d\n",omp_get_thread_num());
				
			}
			
			
		}
		
		#pragma omp barrier
		if(omp_get_thread_num()==0){
			printf("Printing Elements of Matrix C: \n");
			#pragma omp parallel for num_threads(5)
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					printf("%d ",C[i][j]);
				}
				printf("\n");
			}
			
			printf("Printing Elements of Matrix D: \n");
			#pragma omp parallel for num_threads(5)
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					printf("%d ",D[i][j]);
				}
				printf("\n");
			}
			
			printf("Printing by thread id : %d\n",omp_get_thread_num());
		}
		
	}
	
	
	return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include "learn.h"

void print(double** xinput, double** yinput, int row, int col){	
	int i = 0;
	int j = 0;
	printf("xinput: \n");
	while(i<row){
		while (j<col){
			printf("%lf\t", xinput[i][j]);
			j++;	
		}
		printf("\n");
		i++;
		j=0;
	}
	i=0;
	printf("yinput: \n");
	while(i<row){
		printf("%lf\n", yinput[i][0]);
		i++;
	}
}

double ** x1(double** xinput, int row, int col){
	double** newx;
	int i= 0;
	int j =0;
	newx = (double**)malloc(row*sizeof(double*));
	int newcol = col+1;
	while(i<row){
		newx[i] = (double*)malloc((newcol)*sizeof(double));
		while (j<newcol){
			if (j ==0){
				newx[i][j] = 1;
			}else {
				newx[i][j] = xinput[i][j-1];
			}
			j++;
		}
		i++;
		j=0;
	
	}
	return newx;
}



double ** transpose(double** xinput, int row, int col){
	int i= 0;
	int j =0;

	double** trans;
	trans = (double**)malloc(col*sizeof(double*));
	while(i<col){
		trans[i] = (double*)malloc(row*sizeof(double));
		while(j<row){
			trans[i][j] = xinput[j][i];
			j++;
		}
		i++;
		j=0;
	}
	return trans;


}
void testprint(double** test, int row, int col){

	int i = 0;
	int j = 0;
	printf("test: \n");
	while(i<row){
		while (j<col){
			printf("%lf\t", test[i][j]);
			j++;	
		}
		printf("\n");
		i++;
		j=0;
	}

}
void printfinal(double** final, int row){
	int i = 0;
	double value;
	while( i< row){
		value = final[i][0];
		printf("%0.0lf\n",value);
		i++;

	}

}
double** inverse(double** matrix, int newcol){

	double** augment;
	double** inverse;
	int i = 0;
	int j = 0;
	augment = (double**)malloc(newcol*sizeof(double*));
	
	while(i < newcol){
		augment[i] = (double*)malloc((newcol*2)*sizeof(double));
		while(j<newcol*2){
			if(j>=newcol){
				if(j-newcol-i == 0){
					augment[i][j] =1;
				}else {
					augment[i][j] =0;	
				}
			}else {
				augment[i][j] = matrix [i][j];
			}
			j++;
		
		}
		i++;
		j=0;
	}
	i = 0;
	j = i;
	int x= i+1;
	int y=i;
	double temp;
	double factor;
	while(i<newcol){
		if(augment[i][j] != 1){
		temp = augment[i][j];
			while(j<newcol*2){
				augment[i][j] = augment[i][j]/temp;
				j++;
			}
		}
		while(x<newcol){
			if(augment[x][y] != 0){
				factor = augment[x][y]/augment[i][y];
				while(y<newcol*2){ 
					augment[x][y] = augment[x][y] - (factor*augment[i][y]);
					y++;
				}
			}
			x++;
			y=i;		
		}
		i++;
		y=i;
		j=i;
		x=i+1;
	
	}
	i = newcol-1; //at the bottom row
	j = i; // at the bottom corner 
	x = i-1; //one right above i
	y = i;
	while(i>-1){
		while(x>-1){
			if(augment[x][y] != 0){
				factor = augment[x][y]/augment[i][y];
				while(y<newcol*2){
					augment[x][y] = augment[x][y] - (factor*augment[i][y]);
					y++;
				}
			}
			x--;
			y=i;
		}
		i--;
		y=i;
		j=i;
		x=i-1;
	}
	
	inverse = (double**)malloc(newcol*sizeof(double*));
	i = 0;
	j = newcol;
	x=0;
	while(i < newcol){
		inverse[i] = (double*)malloc(newcol*sizeof(double));
		while(j<newcol*2){
			inverse[i][x] = augment[i][j];
			x++;
			j++;
		}
		i++;
		x=0;
		j=newcol;
	
	}
	
	return inverse;

}
double** multiply(double** m1, double** m2, int row1, int col1, int col2){
	double** result;
	result = (double**)malloc(row1*sizeof(double*));
	
	int j = 0;
	int L = 0;
	int R = 0;

	while(L<row1){
		result[L] = (double*)malloc(col2*sizeof(double));
		while(R<col2){
			while(j<col1){
				result[L][R] += m1[L][j]*m2[j][R];
				j++;
			}
			R++;
			j=0;
		}
		L++;
		R = 0;
		j = 0;
	
	}
	return result;


}

void freematrix(double** matrix, int row){
	int i = 0;
	while (i<row){
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int main(int argc, char** argv){
	
	char* filename1 = NULL;
	char* filename2 = NULL;
	FILE* fp = NULL;
	double value;
	int val;
	double** xinput;
	double** yinput;
	double** test;
	int row,col;
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	int count = 0;
	char op;
	int testrow;
	filename1 = argv[1];
	filename2 = argv[2];
	
	fp = fopen(filename1, "r");

	while(i<2){
		fscanf(fp, "%d", &val);
		if(i == 0){
			col = val;
		}else {
			row = val;
		}
		i++;
	}
	i = 0;
	xinput = (double**)malloc(row*sizeof(double));
	yinput = (double**)malloc(row*sizeof(double));

	while (!feof(fp)){
 
		if (count < col){
			fscanf(fp, "%lf %c", &value, &op);
			count++;
		}else{
			fscanf(fp, "%lf", &value);
			count = 0;
			
		}
		
		if(j==0){
			xinput[k] = (double*)malloc(col*sizeof(double));
		}
		if(j < col){
			xinput[k][j] = value;
			j++;
			continue;
		}else {
			k++;
		}
		if(j == col){
			yinput[m] = (double*)malloc(1*sizeof(double));
			yinput[m][0] = value;
			m++;
			if(k==row && m==row && j ==col){
				break;
			}
			j=0;
		}
	}
	i=0;
	fp = fopen(filename2, "r");
	while(i<1){
		fscanf(fp, "%d", &val);
		testrow = val;
		i++;
	}
	count=0;
	k=0;
	j=0;
	i=0;
	test = (double**)malloc(testrow*sizeof(double));

	while(!feof(fp)){
		if (count < col -1){
			fscanf(fp, "%lf %c", &value, &op);
			count++;
		}else {
			fscanf(fp, "%lf", &value);
			count = 0;
		}
		if(j==0){
			test[k] = (double*)malloc(col*sizeof(double));
		}
		if(j < col){
			test[k][j] = value;
			j++;
			continue;
		}else {
			k++;
			if(k==testrow && j==col){
				break;
			}
			j=0;
			test[k] = (double*)malloc(col*sizeof(double));
			test[k][j] = value;
			j++;
			
		}
	
	}
	int xcol = col + 1;
	xinput = x1(xinput,row,col); //xinputs new col size is xcol and xrow
	double** trans = transpose(xinput,row,xcol);//trans- row = xcol col = xrow
	double** mult = multiply(trans, xinput, xcol,row, xcol); //row1by col2
	
	double** inv = inverse(mult,xcol);
		
	double** W;
	double** M;
	M = multiply(inv, trans, xcol, xcol, row);
	W = multiply(M,yinput, xcol, row, 1); 
	test = x1(test,testrow,col);
	
	double** final;
	final = multiply(test,W,testrow, col+1, 1);
	printfinal(final, testrow);				
	return 0;
	
	freematrix(xinput, row);
	freematrix(yinput, row);
	freematrix(test, testrow);
	freematrix(trans, xcol);
	freematrix(mult, xcol);
	freematrix(inv, xcol);
	freematrix(W, xcol);
	freematrix(M,xcol);
	freematrix(final,testrow);
	
}


#include<stdlib.h>
#include<math.h> 
#include<stdbool.h>
#include<stdio.h>
#include<malloc.h>
#define VECT_ARR_SIZE 6
#define TYP float

int const numPts=12;
/*the user inputs four points.  that equals 3 coords/pt=12 coords (A,B,C,D)*/
TYP* isCollinear( TYP a[],TYP b[] );
/*declaring the function (c makes you do this if you want to put functions after
the main method. */
TYP *eq_of_plane(TYP *ijk, TYP *a);
TYP pt_plane_distance(TYP *point, TYP *plane);
TYP *cross_product(TYP *a, TYP *b);
TYP *pts_to_vectors( TYP (*p)[3]);
/*same thing as above*/
int main(void)
{
 char input[20];//input buffer, this is where the user input is stored.
 TYP pointArr[4][3];
/*
 2-d array to store 4 x,y,z points.*/
 int i,j;
 for(i=0; i<4; i++)
 {
 // int i increases after every 3 coords entered in the j loop (below)		
  printf("Enter x,y,z values for %c dimension:\n", 
	 //prompting user for coords
  (i==0) ? 'A' : (i==1) ? 'B' : (i==2) ? 'C' : 'D');
  		
  for(j=0; j<3; j++)
  {
   printf("%c-value:", (j==0) ? 'X' : (j==1) ? 'Y' : 'Z');
   if(fgets(input, sizeof input, stdin))
   {
    
    sscanf(input, "%f",*(pointArr+i)+j); 
   }			
  }
 }
	//testing that values have been assigned to array
   TYP *p=pts_to_vectors(pointArr);
   TYP *s=isCollinear(p, p+3);
 if(!(s[0]&&s[1]&&s[2]))
 {
	printf("is  collinear\n");
 }
 else 
 {
	TYP *r=eq_of_plane(s, *pointArr);
	printf("equation of the plane is %fx + %fy +%fz= %f\n", *r, *(r+1), *(r+2), *(r+3));
	printf("distance from point D to plane is %f\n", pt_plane_distance(pointArr[3],r));	
 }

 return 0;
}

TYP *cross_product(TYP* a, TYP* b)
{
    TYP i,j,k; 
    i=a[1]*b[2]-a[2]*b[1];
    j=a[0]*b[2]-a[2]*b[0];
    k=a[0]*b[1]-a[1]*b[0];
    TYP *xp=malloc(sizeof(a));
    *(xp)=i;
    *(xp+1)=-j;
    *(xp+2)=k;
    return xp;
}
TYP *eq_of_plane( TYP* ijk, TYP a[] )
{
    TYP d=*(ijk)*a[0]+*(ijk+1)*a[1]+*(ijk+2)*a[2];
    *(ijk+3)=d;
    return ijk;
}
TYP* isCollinear( TYP a[], TYP b[])
{
    TYP *c = cross_product(a, b);
    //TYP t=(*(c)+*(c+1)+*(c+2));
    //*(c+3)=t;
    return c;
}
TYP pt_plane_distance(TYP *point, TYP *plane)
{

  	double t=abs((point[0]*plane[0])+(point[1]*plane[1])+(point[2]*plane[2])		-plane[3]); 
  	t=t/sqrt((plane[0]*plane[0])+(plane[1]*plane[1])+(plane[2]*plane[2]));
	 return t; 
}
TYP *pts_to_vectors(TYP (*p)[3])
{
//
/*this function turns 3 points into two vectors*/
//	
	TYP a[3]={(*(*p+3)-*(*p)),( *(*p+4)-*(*p+1)),(*(*p+5)-*(*p+2))};
	TYP b[3]={(*(*p+6)-*(*p)),( *(*p+7)-*(*p+1)),(*(*p+8)-*(*p+2))};
	int i=0;
	
	 TYP *a_=malloc(sizeof(a)*2);
	i=0;
	while(i<6)
	{
	 *(a_+i)=i<3 ? a[i]: b[i%3] ;  
 	 i++;
	}	
	
	  
	  return a_;	
	 
}

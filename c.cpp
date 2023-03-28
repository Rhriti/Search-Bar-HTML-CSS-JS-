
&nbsp;
 
#include<stdio.h>
#include<openGL/gl.h>
#include<openGL/glu.h>
#include<GLUT/glut.h>
 
typedef struct ed
{
int x1,x2,y1,y2,flag;
};
 
struct ed edge[10],temp;
/*
int x[]={10,50,60,20};
int y[]={10,10,50,50};
int n=4; //No of vertices
*/
 
int x[]={10,50,50,10};
int y[]={10,10,50,50};
int n=4; //No of vertices
float dx,dy,m[10],x_inter[10],x_int[10],xx[300],xxx[300];
 
void scan()
{
int i,j,k; //Iterators
int y_max=0,y_min=9999,y_max_t,kk;
 
/*Step 1*/
for(i=0;i<n;i++)
{
/*FIND Y-MAX AND Y-MIN*/
if(y[i]>y_max)
y_max=y[i];
if(y[i]<y_min)
y_min = y[i];
 
/*STORE THE EDGE VERTICES IN STRUCTURE*/
edge[i].x1 = x[i];
edge[i].y1 = y[i];
edge[i].flag = 0;
}
 
/*Step 2: Store edge info again*/
for(i=0;i<n-1;i++)
{
edge[i].x2 = edge[i+1].x1;
edge[i].y2 = edge[i+1].y1;
}
edge[i].x2 = edge[0].x1;
edge[i].y2 = edge[0].y1;
 
/*Step 3: Check y1>y2 if not then swap the two*/
/*y1 = Max co-ord and y2 = Min co-ord*/
int temps;
for(i=0;i<n;i++)
{
if(edge[i].y1<edge[i].y2)
{
temps = edge[i].y1;
edge[i].y1 = edge[i].y2;
edge[i].y2 = temps;
temps = edge[i].x1;
edge[i].x1 = edge[i].x2;
edge[i].x2 = temps;
}
}
 
/* Debug code
for(i=0;i<n;i++)
{
printf("%d\t%d\t%d\t%d\n",edge[i].x1,edge[i].y1,edge[i].x2,edge[i].y2);
}*/
 
/*Step 4: Sorting edge such that y1 is desc., y2 is desc. and x2 is asc.*/
for(i=0;i<n-1;i++) //n-1 as we are checking the next value i+1 below
{
for(j=0;j<n-1;j++)
{
/*Attempting to sort y1 in desc order*/
if(edge[j].y1<edge[j+1].y1)
{
temp = edge[j];
edge[j] = edge[j+1];
edge[j+1] = temp;
}
/*Now if y1==y1 then sort y2 in desc. order*/
if(edge[j].y1==edge[j+1].y1)
{
if(edge[j].y2<edge[j+1].y2)
{
temp = edge[j];
edge[j] = edge[j+1];
edge[j+1] = temp;
}
 
/*Now if again unfortunately for human kind if y2==y2 then*/
if(edge[j].y2==edge[j+1].y2)
{
/*Sort in descending order of x1*/
if(edge[j].x1<edge[j+1].x1)
{
temp = edge[j];
edge[j] = edge[j+1];
edge[j+1] = temp;
}
}
}
}
}
 
/* Debug code
for(i=0;i<n;i++)
{
printf("%d\t%d\t%d\t%d\n",edge[i].x1,edge[i].y1,edge[i].x2,edge[i].y2);
}*/
 
/*Step 5: Calculating 1/slope for each edge and storing top x co-ord of the edge*/
for(i=0;i<n;i++)
{
dx = edge[i].x2 - edge[i].x1;
dy = edge[i].y2 - edge[i].y1;
 
if(dy==0)
m[i]=0;
else
m[i]=dx/dy;
x_inter[i]=edge[i].x1;
}
 
/* Debug Code
for(i=0;i<n;i++)
printf("%f\t%f\n",m[i],x_inter[i]);
*/
 
y_max_t = y_max;
kk = 0;
 
while(y_max_t > y_min)
{
/*Marking active edge's*/
for(i=0;i<n;i++)
{
if(y_max_t > edge[i].y2 && y_max_t <= edge[i].y1)
{
//printf("yy=%d\ty1=%d\ty2=%d\n",y_max_t,edge[i].y1,edge[i].y2);
edge[i].flag = 1;
}
else
edge[i].flag = 0;
}
 
/*Finding x intersections*/
int j=0;
for(i=0;i<n;i++)
{
if(edge[i].flag==1)
{
if(y_max_t==edge[i].y1)
{
x_int[j] = edge[i].x1;
j++;
if((edge[i-1].y1==y_max_t)&&(edge[i-1].y1<y_max_t))
{
x_int[j] = edge[i].x1;
j++;
}
if(edge[i+1].y1==y_max_t && edge[i+1].y1<y_max_t)
{
x_int[j] = edge[i].x1;
j++;
}
}
else
{
x_int[j] = x_inter[i] - m[i];
x_inter[i] = x_int[j];
j++;
}
}
}
 
float tempss;
/*Step 6: Sorting the x intersection in asc order*/
for(i=0;i<j;i++)
{
for(k=0;k<j-1;k++)
{
if(x_int[k] > x_int[k+1])
{
tempss = x_int[k];
x_int[k] = x_int[k+1];
x_int[k+1] = tempss;
}
}
}
 
/*Extracting pairs of x values to draw lines*/
for(i=0;i<j;i+=2)
{
xx[kk] = x_int[i];
xxx[kk] = x_int[i+1];
}
 
y_max_t--;
kk++;
}
 
i=0;
y_max_t=y_max;
glColor3f(0,0,1);
while(y_max_t>y_min)
{
glBegin(GL_LINES);
glVertex2f(xx[i],y_max_t);
glVertex2f(xxx[i],y_max_t);
glEnd();
y_max_t--;
i++;
}
 
/**/
 
}
 
void disp()
{
glClearColor(0,0,0,0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,1,1);
scan();
glFlush();
}
 
int main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitWindowSize(100,100);
glutCreateWindow("ScanLine");
gluOrtho2D(0,100,0,100);
glutDisplayFunc(disp);
glutMainLoop();
return 0;
}
#include <iostream>
#include <complex>
#include <algorithm>
#define pi 3.141592654
using namespace std;
void yesman(char,double,double,double,double,double,double,double,double,double,double,double,FILE * pFile);
double deg(double i){
       if(i>=0){while(i>360){
       i-=360;}
       return i;}
       else{while(i<=-360){
       i+=360;}
       return i;}
       }
main(){
    double r[4];
    r[0]=99999;
    cout<<"Input the length of linkages."<<endl;
    cout<<"r1(frame)=   ";cin>>r[1];double r1=r[1];
    cout<<"r2(driver)=  ";cin>>r[2];double r2=r[2];
    cout<<"r3=          ";cin>>r[3];double r3=r[3];
    cout<<"r4=          ";cin>>r[4];double r4=r[4];
    cout<<endl;
    cout<<"Enter \"o\" for an open-type, or \"c\" for a crossed-type configuration."<<endl;//  Configuration
    char c;
    cin>>c;
    cout<<"Enter \"c\" for coupler point analyzing, \"o\" for r4(output linkage) analyzing, or \"b\" for both."<<endl;//耦點(x,y)....或輸出桿...或both
    char anl;
    cin>>anl;
    double r5;
    double t5;
    if(anl=='c'||anl=='b'){
      cout<<"Input the coordinate of the coupler poit."<<endl;//  耦點初始位置 
      cout<<"r5=";cin>>r5;
      cout<<"Theta5=";cin>>t5;
    }
    cout<<"Input the step increment.(DEGREE)"<<endl;//step increment
    double st;
    cin>>st;
    FILE * pFile;
    pFile = fopen ("四連桿組運動分析.txt","w");
    /*   Grashof type : typ   */
    sort(r,r+5);//比大小
    reverse(r,r+5);//小到大
    int j;
    for(int i=1;i<5;i++){
            if(r1==r[i])
            j=i;
    }
    double t3,t4;
    if(c=='c'){
    fprintf (pFile,"Configuration: Crossed-type configuration\n");
    t3=305*pi/180;
    t4=275*pi/180;
    }
    else{
    fprintf (pFile,"Configuration: Open-type configuration\n");
    t3=70*pi/180;
    t4=120*pi/180;
    }
    double t2i,t2f,t2pp,t2p;
    t2pp=acos((r2*r2+r1*r1-((r3+r4)*(r3+r4)))/(2*r2*r1))*180/pi;
    t2p=acos((r2*r2+r1*r1-((r3-r4)*(r3-r4)))/(2*r2*r1))*180/pi;
    if(r[1]+r[4]<r[2]+r[3]){
      if(j==1||j==3){
        t2i=0;t2f=360;
        fprintf (pFile,"Grashof type: Crank-rocker\n\n\n\n\n");}//(i)  若最短桿4與固定桿3or1連接：crank and rocker
        else if(j==4){
        t2i=0;t2f=360;
        fprintf (pFile,"Grashof type: Drag-link(double-crank)\n\n\n\n\n");}//(ii) 若最短桿4為固定桿4：double crank (雙曲桿)或稱為drag linkage(牽桿連桿組)
        else{
        fprintf (pFile,"Grashof type: Double-rocker of first kind\n\n\n\n\n");
        if(c=='c'){t2i=t2p;t2f=t2pp;}
        else{t2i=-t2pp;t2f=-t2p;}}//(iii)  若最短桿為耦桿：double rocker of first kind (第一類雙搖桿)................else
    }
    else if(r[1]+r[4]==r[2]+r[3]){
    fprintf (pFile,"Grashof type: Folding linkage\n\n\n\n\n");
    if(j==1||j==3){t2i=0;t2f=360;}
    else if(j==4){t2i=0;t2f=360;}
    else{if(c=='c'){t2i=t2p;t2f=t2pp;}
     else{t2i=-t2pp;t2f=-t2p;}}}//   folding linkage(疊合連桿組)
    else if(r[1]+r[4]>r[2]+r[3]){
    fprintf (pFile,"Grashof type: Double rocker of second kind(triple rocker)\n\n\n\n\n");
    if(r2+r1>=r3+r4){t2i=-t2pp;t2f=t2pp;}
    else{t2i=t2p;t2f=-t2p;}
    }//   double rocker of second kind (第二類雙搖桿) 或稱為 triple rocker(參搖桿)
    yesman(anl,r5,t5,r2,st,t3,t4,t2i,t2f,r1,r3,r4,pFile);
    if(anl=='b'){
    anl='o';
    yesman(anl,r5,t5,r2,st,t3,t4,t2i,t2f,r1,r3,r4,pFile);
    }
    //cout<<endl<<endl<<endl<<endl<<endl;
    //system("PAUSE");
    return 0;
}
void yesman(char anl,double r5,double t5,double r2,double st,double t3,double t4,double t2i,double t2f,double r1,double r3,double r4,FILE * pFile){
    double e1,e2,dt3,dt4,t2;
    double e=0.01*pi/180;
    double w2,w3,w4;
    double a3,a4;
    double x,y,vx,vy,ax,ay;
    w2=10;//........rad/s
    switch(anl){
    case 'o':
      fprintf (pFile," Theta2    Theta4     Omega4    Alpha4\n");
      fprintf (pFile," =====================================\n");
      break;
    default:
      fprintf (pFile,"*represented by (absolute value, phase angle)\n\n\n\n");
      fprintf (pFile," Theta2    Theta3    P(x,y)            V of P*           A of P*\n");
      fprintf (pFile," ========================================================================\n");
      break;
    }
    for(double i=t2i;i<=t2f;i+=st){
            t2=i*pi/180;
            int flag=0;
            do{
              e1=r2*cos(t2)+r3*cos(t3)-r4*cos(t4)-r1;
              e2=r2*sin(t2)+r3*sin(t3)-r4*sin(t4);
              dt3=(e1*cos(t4)+e2*sin(t4))/(r3*sin(t3-t4));
              dt4=(e1*cos(t3)+e2*sin(t3))/(r4*sin(t3-t4));
              t3+=dt3;
              t4+=dt4;
              if(fabs(dt3)<e&&fabs(dt4)<e)
              flag=1;
              }while(flag==0);
            w3=-(w2*r2*sin(t2-t4))/(r3*sin(t3-t4));
            w4=-(w2*r2*sin(t2-t3))/(r4*sin(t3-t4));
            a3=(r2*(w2*w2*cos(t2-t4))+w3*w3*r3*cos(t3-t4)-r4*w4*w4)/(r3*sin(t4-t3));
            a4=(r2*(w2*w2*cos(t2-t3))-w4*w4*r4*cos(t3-t4)+r3*w3*w3)/(r4*sin(t4-t3));
            x=r2*cos(t2)+r5*cos(t3+t5);
            y=r2*sin(t2)+r5*sin(t3+t5);
            vx=-r2*w2*sin(t2)-r5*w3*sin(t3+t5);
            vy=r2*w2*cos(t2)+r5*w3*cos(t3+t5);
            ax=-r2*w2*w2*cos(t2)-r5*a3*sin(t3+t5)-r5*w3*w3*cos(t3+t5);
            ay=-r2*w2*w2*sin(t2)+r5*a3*cos(t3+t5)-r5*w3*w3*sin(t3+t5);
            switch(anl){
              case 'o':
                fprintf (pFile,"%6.1f     %7.3f  %8.3f  %9.3f\n",t2*180/pi,deg(t4*180/pi),w4,a4);
                break;
              default:
                fprintf (pFile,"%6.1f    %7.3f    (%6.3f,%6.3f)   (%6.3f,%6.3f)   (%6.3f,%6.3f)\n",t2*180/pi,deg(t3*180/pi),x,y,sqrt(vx*vx+vy*vy),atan(vy/vx),sqrt(ax*ax+ay*ay),atan(ay/ax));
                break;
            }
     }
     fprintf (pFile,"\n\n\n\n\n");
}

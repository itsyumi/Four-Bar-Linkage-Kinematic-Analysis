#include <iostream>
#include <complex>
#include <algorithm>
#define pi 3.141592654
using namespace std;
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
    cout<<"Input the initial angle of the driver.(DEGREE)"<<endl;//  輸入桿r2運動範圍
    double t2,t2i,t2f;
    cin>>t2i;
    cout<<"Input the final angle of the driver.(DEGREE)"<<endl;
    cin>>t2f;
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
    /*   Grashof type : typ   */
    sort(r,r+5);//比大小
    reverse(r,r+5);//小到大
    int j;
    for(int i=1;i<5;i++){
            if(r1==r[i])
            j=i;
    }
    string typ; 
    if(r[1]+r[4]<r[2]+r[3]){
      if(j==1||j==3)
      typ="crank-rocker";//(i)  若最短桿4與固定桿3or1連接：crank and rocker
      else if(j==4)
      typ="drag-link(double-crank)";//(ii) 若最短桿4為固定桿4：double crank (雙曲桿)或稱為drag linkage(牽桿連桿組)
      else
      typ="double-rocker of first kind";//(iii)  若最短桿為耦桿：double rocker of first kind (第一類雙搖桿)................else
    }
    else if(r[1]+r[4]==r[2]+r[3]){
    typ="folding linkage";
    }//   folding linkage(疊合連桿組)
    else if(r[1]+r[4]>r[2]+r[3]){
    typ="double rocker of second kind(triple rocker)";
    }//   double rocker of second kind (第二類雙搖桿) 或稱為 triple rocker(參搖桿)
    double e1,e2,dt3,dt4;
    double e=0.01*pi/180;
    double t3,t4;
    double w2,w3,w4;
    double c1,c2,a3,a4;
    double x,y,vx,vy,ax,ay;
    w2=10;//........rad/s
    string confg;
    if(c=='c'){
    confg="crossed-type configuration";
    t3=305*pi/180;
    t4=275*pi/180;
    }
    else{
    confg="open-type configuration";
    t3=70*pi/180;
    t4=120*pi/180;
    }
    cout<<endl<<endl<<endl<<endl;
    cout<<"Configuration:"<<confg<<endl;
    cout<<"Grashof type:"<<typ<<endl<<endl<<endl<<endl<<endl;
    switch(anl){
    case 'c':
      cout<<"*indicate by (absolute value,phase angle)"<<endl<<endl<<endl<<endl;
      cout<<" Theta2    Theta3    P(x,y)            V of P*           A of P*"<<endl;
      cout<<" ========================================================================"<<endl;
      break;
    case 'o':
      cout<<" Theta2    Theta4     Omega4    Alpha4"<<endl;
      cout<<" ====================================="<<endl;
      break;
    default:
      cout<<" Theta2    Theta3    Theta4     Omega3    Omega4    Alpha3     Alpha4     P(x,y)            V of P*           A of P*"<<endl;
      cout<<" ============================================================================================================================="<<endl;
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
              if(fabs(dt3)>e||fabs(dt4)>e)
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
              case 'c':
                printf("%6.1f    %7.3f    (%6.3f,%6.3f)   (%6.3f,%6.3f)   (%6.3f,%6.3f)\n",t2*180/pi,deg(t3*180/pi),x,y,sqrt(vx*vx+vy*vy),atan(vy/vx),sqrt(ax*ax+ay*ay),atan(ay/ax));
                break;
              case 'o':
                printf("%6.1f     %7.3f  %8.3f  %9.3f\n",t2*180/pi,deg(t4*180/pi),w4,a4);
                break;
              default:
                printf("%6.1f    %7.3f    %7.3f  %8.3f  %8.3f  %9.3f %9.3f (%6.3f,%6.3f)   (%6.3f,%6.3f)   (%6.3f,%6.3f)\n",t2*180/pi,deg(t3*180/pi),deg(t4*180/pi),w3,w4,a3,a4,x,y,sqrt(vx*vx+vy*vy),atan(vy/vx),sqrt(ax*ax+ay*ay),atan(ay/ax));
                break;
            }
    }
    cout<<endl<<endl<<endl<<endl;
    system("PAUSE");
    return 0;
}

#include <bits/stdc++.h> 

using namespace std;

double Convertyears(int year, int month, int day, int hour, int minute){
  int days=0;
  for(int i=1;i<month;i++){
    if( i==1 || i==3 || i==5 || i==7 || i==8 || i==10 || i==12){
      days+=31;
      //cout<<"added 31 ";
    }
    else if(i==4 || i==6 || i==9 || i==11){
      days+=30;
      //cout<<"added 30 ";
    }
    else if(i==2){
      if(year%4==0){
        days+=29;
        //cout<<"added 29 ";
      }
      else {
        days+=28;
        //cout<<"added 28 ";
    }
  }
  }
  days+=day-1;
  int hours=days*24+hour;
  int minutes=hours*60+minute;
  int leaps=((year-2020))/4;
  int minutetrue= minutes+(365*24*60*(year-2020)+24*60*leaps);
  double trueyears=(double)minutetrue/(365*24*60+5*60+49);
  return trueyears;
  

}

double findClosest(double arr1[], double arr2[], double given, int size){
  int i=0, j=size, mid=0;
  while(i<j){
    mid=(i+j)/2;
    if(arr1[mid]==given){
      return arr2[mid];
    }

    else if(arr1[mid]>given){
      if(mid>0 && arr1[mid-1]<given){
          if (given - arr1[mid] >= arr1[mid-1] - given)
            return arr2[mid-1];
          else
            return arr2[mid];
      }

      j=mid;
    }

    else{
        if(mid<size-1 && arr1[mid+1]>given){
          if (given - arr1[mid] >= arr1[mid+1] - given)
            return arr2[mid+1];
          else
            return arr2[mid];
      }

      i=mid+1;
    }
  }

  return 0;
}

double toRad(double angle){
  return M_PI*angle/180;
}

double toDeg(double angle){
  return angle*180/M_PI;
}

double Mod_1(double y){
  int x=y;
  double yy=y-x;
  return yy;
}


using namespace std;

int main(int argc, char *argv[])
{

  ifstream ifile, i1file, i2file, i3file, i4file, i5file, i6file, i7file, tempfile;
  ofstream ofile, o1file, o2file, o3file;

  ifile.open("Time.txt");


  int size=36001;
  double Time[size];
  double Angle[size];

  double data;

  int i=0;
  while(ifile>>data){
    Time[i]=data;
    i++;
  }

  i1file.open("Angle.txt");
  tempfile.open("Angle.txt");

  i=0;
  while(i1file>>data){
    Angle[i]=data;
    i++;
  }

 
  int equinox[14][5];

  int year, month, date, hour, minute;

  i2file.open("Equinox.txt");

  int it=0;

  while(i2file>>year>>month>>date>>hour>>minute){
    equinox[it][0]=year;
    equinox[it][1]=month;
    equinox[it][2]=date;
    equinox[it][3]=hour;
    equinox[it][4]=minute;
    it++;
  }
  cout<<setprecision(11);
  double firstaphelion=Convertyears(2020, 7, 4, 11, 34);
  double timediff_E[14];
    for(int i=0;i<14;i++){
      double x=Convertyears(equinox[i][0],equinox[i][1],equinox[i][2],equinox[i][3],equinox[i][4])-firstaphelion;
      int y=x;
      x-=y;
      timediff_E[i]=x;
  }

  ofile.open("Theta_E.txt");
 
  for(int i=0;i<14;i++){
   
      ofile<<findClosest(Time, Angle, timediff_E[i], size)<<endl;
  
  }
  
  int solstice[14][5];

  i3file.open("Solstice.txt");

  it=0;

  while(i3file>>year>>month>>date>>hour>>minute){
    solstice[it][0]=year;
    solstice[it][1]=month;
    solstice[it][2]=date;
    solstice[it][3]=hour;
    solstice[it][4]=minute;
    it++;
  }

  double timediff_S[14];
    for(int i=0;i<14;i++){
      double x=Convertyears(solstice[i][0],solstice[i][1],solstice[i][2],solstice[i][3],solstice[i][4])-firstaphelion;
      int y=x;
      x-=y;
      timediff_E[i]=x;
  }

  o1file.open("Theta_S.txt");
 
  for(int i=0;i<14;i++){
    
      o1file<<findClosest(Time, Angle, timediff_E[i], size)<<endl;
    
  }

  o2file.open("Chi_E.txt");
  i4file.open("Theta_E.txt");
  double pre_chi;
  int i1=0;
  while(i4file>>pre_chi){
    if(i1%2==0){
      o2file<<abs(pre_chi-270)<<endl;
    }
    else o2file<<abs(pre_chi-90)<<endl;
    i1++;
  }

  i5file.open("Theta_S.txt");
  o3file.open("Chi_S.txt");
  int j=0;
  while(i5file>>pre_chi){
    if(j%2==0){
      o3file<<abs(pre_chi-360)<<endl;
    }
    else o3file<<abs(pre_chi-180)<<endl;
    j++;
  }

  ofile.close();
  o1file.close();
  o2file.close();
  o3file.close();

  i6file.open("Chi_E.txt");
  i7file.open("Chi_S.txt");

  double chii;
  double chi_f=0;
  int count=0;

  while(i6file>>chii){
    chi_f+=chii;
    count++;  
  }

  while(i7file>>chii){
    chi_f+=chii;
    count++;
  }

  chi_f/=count;

  double phi, epsilon;
  epsilon= 23+26/60;
  double phirad=toRad(phi);
  double eprad=toRad(epsilon);

  // Zero Shadow code (make function later)
  double befchi=acos(sin(phirad)/sin(eprad));
  double befchid=toDeg(befchi);
  double theta_1=chi_f+befchid;
  double theta_2=-chi_f+befchid;

  // RA 

  double first_veq=Mod_1(Convertyears(2020, 3, 20, 3, 37));
  double angle_firstveq=findClosest(Time, Angle, first_veq, size);
  int yyyy,mm,dd;
  cin>>yyyy>>mm>>dd;
  double entry=Mod_1(Convertyears(yyyy,mm,dd,0,0));
  double angle_entry=findClosest(Time, Angle, entry, size);

  double lambda;
  if(angle_firstveq<angle_entry) lambda=angle_entry-angle_firstveq;
  else lambda=angle_entry-angle_firstveq+360;
  cout<<"lambda:"<<lambda<<endl;
  double RA;
  RA=toDeg(atan(tan(toRad(lambda))*cos(eprad)));
  cout<<"RA:"<<RA<<endl;

  // Declination

  double declination = toDeg(asin(sin(toRad(RA))*sin(eprad)));
  if(declination>90){
    declination-=360;
  }

  double decrad=toRad(declination);
  cout<<"Declination:"<<declination<<' ';

  // Hour Angle at Sunrise
  double latitude;
  cin>>latitude;
  double latrad=toRad(latitude);

  double HA=acos(-tan(toRad(latitude))*tan(toRad(declination)));
  int Hour=toDeg(HA)/360*24;
  int minutes = (toDeg(HA)/360*24-Hour)*60;
  

  // Sunrise time
  double a=atan(tan(decrad)*tan(latrad));
  double RAprime=RA-toDeg(a);
 // cout<<RA<<endl;
 // cout<<RAprime;
  double eqrise=236*RAprime;

}





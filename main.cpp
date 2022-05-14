#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<bits/stdc++.h>
#include<sstream>

using namespace std;
int n2=-1;


void sizeofcsv(){
    ifstream fin1;
    string line1;
    fin1.open("data.csv");
    while(!fin1.eof()){
        fin1>>line1;
        n2++;
    }
}

int main()
{
    sizeofcsv();
    string row[n2][4];
    ifstream fin;
    string line;
    fin.open("hello.csv");
    int n=0;
    while(!fin.eof()){
    		fin>>line;
            vector<string> v;
            stringstream ss(line);
            while(ss.good()){
                string substr;
                getline(ss, substr, ',');
                v.push_back(substr);
            }
            for (size_t i = 0; i < v.size(); i++){
                //cout << v[i] << endl;
                string a=v[i];
                row[n][i]=a;
            }
            n++;
            if(n2==n){
            	break;
			}
		}
    fin.close();
    // CONVERTING STRING INTO DOUBLE
    double data[n2][4];
    stringstream ss;
    string str;
    double f1=0.0;
    double d1;
    for(int z=0;z<n2;z++){
    	for(int z1=0;z1<4;z1++){
    		str=row[z][z1];
    		ss<<str;
    		ss>>f1;
    		stringstream(str)>>d1;
    		data[z][z1]=d1;
    		ss.clear();
    		ss.str();
		}
	}
	// DISPLAYING MAIN ARRAY
	cout << "\n \n \n \n \n" << endl;
    cout << "---------------MAIN ARRAY VALUES ----------------" << endl;
    cout << endl;
    for(int z=0; z<n2 ; z++){
    	cout << "Row # " << z+1 << endl;
    	cout << "Values: \t" << " x = "<< data[z][0] << " y = "<< data[z][1] << " xX = "<< data[z][2] << " yY = "<< data[z][3] << endl;  
	}
    //CONVERTING MAIN 2D ARRAY INTO SINGLE 1D ARRAY's
    float X[n2];
    float xX[n2];
    float Y[n2];
    float yY[n2];
    for(int z=0;z<n2;z++){
        // 1D ARRAY ASSIGNEMNT 
        X[z]=data[z][0];
        Y[z]=data[z][1];
        xX[z]=data[z][2];
        yY[z]=data[z][3];
    }
	// APPLICATION OF NAVIER TROKES EQUATION 
	// DECLEARING VARIABLES - VALUE COULD BE CHANGED
	double g = 9.81;
	double rho = 1.225;
	double v=12.1;
	// BOUNDARY CONDITIONS
    // CALCULATING THE DELTA P over Delta x
    // Defining Their Array
    int n3=n2-1;
    float DeltaP_Deltax[n3];
    for(int z=1;z<n2;z++){
        // CALCULATION
        float Deltax=0;
        float Deltay=0;
        // CALCULATING DELTA_X AND DELTA_Y
        Deltax=X[z]-X[z-1];
        Deltay=Y[z]-Y[z-1];
        float var1=0;
        float var2=0;
        float var3=0;    
        float var4=0;
        var1=xX[z+1]-(2*xX[z])+xX[z+1];
        var2=xX[z]*(xX[z+1]-xX[z-1]);
        var3=(var1/(Deltax*Deltax))+(var1/(Deltay*Deltay));
        var4=(var2/(2*Deltax))+(var2/(2*Deltay));
        DeltaP_Deltax[z-1]=rho*(v*(var3)-var4);
    }
    // CALCULATING THE DELTA P over Delta y
    // Defining their Array
	float DeltaP_Deltay[n3];
    for(int z=1;z<n2;z++){
        // CALCULATION
        float Deltax=0;
        float Deltay=0;
        // CALCULATING DELTA_X AND DELTA_Y
        Deltax=X[z]-X[z-1];
        Deltay=Y[z]-Y[z-1];
        float var1=0;
        float var2=0;
        float var3=0;    
        float var4=0;
        var1=yY[z+1]-(2*yY[z])+yY[z+1];
        var2=yY[z]*(yY[z+1]-yY[z-1]);
        var3=(var1/(Deltax*Deltax))+(var1/(Deltay*Deltay));
        var4=(var2/(2*Deltax))+(var2/(2*Deltay));
        DeltaP_Deltay[z-1]=rho*(g+v*(var3)-var4);
    }
    
    // PRINTING VALUES OF ARRAY
    cout << "\n \n \n \n \n" << endl;
    cout << "---------------CHANGE IN PRESSURE VALUES ----------------" << endl;
    cout << endl;
	for(int z=0;z<n2-1;z++){
        //PRINTING ARRAY -1
        cout << "Value of Delta P over Delta x for Element " << z+1 <<" is: " << DeltaP_Deltax[z] << endl;
        //PRINTING ARRAY -2
        cout << "Value of Delta P over Delta y for Element " << z+1 <<" is: " << DeltaP_Deltay[z] << endl;
    }

    // CALCULATING PRESSURE 
    float array1[n3];
    float array2[n3];
    for(int z=1;z<n2;z++){
        // DECLEARING LOOP VARIABLES
        float var1=0;
        float var2=0;
        float Deltax=0;
        float Deltay=0;
        // CALCULATING DELTA_X AND DELTA_Y
        Deltax=X[z]-X[z-1];
        Deltay=Y[z]-Y[z-1];
        // CALUALTING VALUES
        var1=(Deltax/8)*(DeltaP_Deltax[z+1]-DeltaP_Deltax[z-1]);
        var2=(Deltay/8)*(DeltaP_Deltay[z+1]-DeltaP_Deltay[z-1]);
        array2[z]=var1+var2;
        array1[z]=array1[z]+1;
        array1[z+1]=array1[z+1]+0.5;
        array1[z-1]=array1[z-1]-0.5;
    }
    // SHOWING VALUES OF PRESSURE USING SIMPLE ARRAY DIVISION TECHNIQUE 
    cout << "\n \n \n \n \n" << endl;
    cout << "---------------PRESSURE VALUES ----------------" << endl;
    cout << endl;
    for(int z=0;z<n2-1;z++){
        cout << "Value of Pressure at Element " << z+1 << " is: " << array2[z]/array1[z] << endl;
    }
}

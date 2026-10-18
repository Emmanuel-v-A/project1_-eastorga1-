#include "capacitor.h"
#include <iostream>
int main()
{
    double Deltat = 1e-10; 
    double Final_time = 5e-6; 
    int  Number_of_timesteps = Final_time/Deltat;//int because double would give me an error when allocating memeory
    double R = 1000;
    double C = 100e-12;
    double I_t = 1e-2;
    double V_0 = 10.0;

    Capacitor const_current;
    Capacitor const_voltage;

    const_current.time = new double[Number_of_timesteps + 1];//+1 because we start at zero and need + 1 to be able to go through the full 50000
    const_current.voltage= new double[Number_of_timesteps + 1];
    const_current.current= new double[Number_of_timesteps + 1];
    const_current.C = C;

    const_voltage.time= new double[Number_of_timesteps + 1];
    const_voltage.voltage = new double[Number_of_timesteps + 1];
    const_voltage.current = new double[Number_of_timesteps + 1];
    const_voltage.C = C;

    const_current.time[0]=0;//0s because its the begining
    const_current.voltage[0]=0;
    const_current.current[0]= I_t;//not 0 becausse it should be constant

    const_voltage.time[0]=0;
    const_voltage.voltage[0] = 0;
    const_voltage.current[0] = V_0/R;

    for(int i = 0; i < Number_of_timesteps; ++i)
    {
        const_current.time[i+1]=const_current.time[i] + Deltat;
        const_current.current[i+1] = I_t;
	const_current.voltage[i+1] = const_current.voltage[i]+(const_current.current[i] * Deltat/const_current.C);
    }
    
    for(int i = 0; i < Number_of_timesteps; i++)
    {
        const_voltage.time[i+1]= const_voltage.time[i]+Deltat;
	const_voltage.current[i+1] = const_voltage.current[i-1] - (const_voltage.current[i] / (R * const_voltage.C)) * Deltat;
        const_voltage.voltage[i+1] = V_0 - (const_voltage.current[i+1] * R);
    }

    for(int i = 0; i <= Number_of_timesteps; i += 200)
    {
	std::cout<< i <<"    ";//blanks to make it look neater
        std::cout<< const_current.time[i] <<"    ";
        std::cout<< const_current.voltage[i] <<"    ";
        std::cout<< const_current.current[i] <<"    ";
        std::cout<< const_voltage.voltage[i] <<"    ";
	std::cout<< const_voltage.current[i] <<"\n";	
    }
    //free memory
    delete[] const_current.time;
    delete[] const_current.voltage;
    delete[] const_current.current;
    delete[] const_voltage.time;
    delete[] const_voltage.voltage;
    delete[] const_voltage.current;

    return 0;
}

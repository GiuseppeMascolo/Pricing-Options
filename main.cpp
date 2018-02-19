//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  MC_plain
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "utility.h"
#include "rv_library.h"

#include <iostream>
#include <cmath>
#include <ctime>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  declarations
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double Next_S(double, double, double);
double my_max(double, double);

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int main(int argc, char** argv)
{
    double S0 = 100;    //intial stock price
    double r = 0.05;    //risk-free rate
    double sig = 0.2;   //volatility
    
    double X = 100;     //option strike
    double T = 1;       //time to maturity
    double B = 130;     //border price (for border options)
    
    long N = 52;        //time steps
    long M = 1000000;   //Monte Carlo repetitions
    
    double s_time = std::clock();
    
    double dt = T/N;    //time step       
    double drift_dt = (r - 0.5*sig*sig)*dt;    
    double sig_rt = sig*std::sqrt(dt);
    
    double discount = std::exp(-r*T);  //discount factor to discount the option
    
    double sum_v = 0.0;    //to add on the option payoffs
    double sum_v_2 = 0.0;
    
    for(long j = 0; j != M; ++j)    //for each repetition
    {
        if(0 == j % 50000) ut::OutputLine("...", j);
        
        bool knocked_out = false;
        double path_S = S0;

        for(long i = 1; i <= N; ++i)    //for each time step
        {
            path_S = Next_S(path_S, drift_dt, sig_rt);    //update the next value of S
            if(path_S >= B)
            {
                knocked_out = true;
                break;
            }            
        }

        double v = knocked_out ? 0.0 : my_max(path_S - X, 0.0);  //payoff
        
        sum_v += v;
        sum_v_2 += v*v;
    }
    
    //outputs
    double c = discount*sum_v/M;    //option value
    double se = discount*std::sqrt(sum_v_2 - sum_v*sum_v/M)/M;    //standard error
    
    double e_time = (std::clock() - s_time)/CLOCKS_PER_SEC;
    
    ut::OutputLine("Option value:  ", c);
    ut::OutputLine("se:            ", se);
    ut::OutputLine("time taken:    ", e_time);
    
	return ut::PauseAndReturn();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Next_S()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double Next_S(double S, double drift, double sig)
{
    double w = rv::GetNormalVariate();    //a random number from out normal distribution
    return S*std::exp(drift + sig*w);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  my_max()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double my_max(double a, double b)
{
    return (a < b) ? b : a;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX




















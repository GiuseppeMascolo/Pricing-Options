//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  MC_plain
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "Input.h"
#include "OptionEuro.h"

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
    Input inp;
    OptionEuro opt(inp);
    
    double S0 = 100;    //intial stock price
    double r = 0.05;    //risk-free rate
    double sig = 0.2;   //volatility
    
    double T = opt.getT();       //time to maturity
    
    //char o_type = 'b';  // c for plain call, p for plain put
                        // a for average rate call, b for average rate put
    
    long N = 100;        //time steps
    long M = 1000000;   //Monte Carlo repetitions
    
    double s_time = std::clock();
    
    double dt = T/N;                           //time step       
    double drift_dt = (r - 0.5*sig*sig)*dt;    //drift
    double sig_rt = sig*std::sqrt(dt);         //vol term
    
    double discount = std::exp(-r*T);  //discount factor to discount the option
    
    double sum_payoff = 0.0;    //to add on the option payoffs
    double sum_payoff_2 = 0.0;
    
    
    for(long j = 0; j != M; ++j)    //for each path
    {
        ut::OutputCounter(j, M, 50000);
        
        double path_S = S0;
        double sum = S0;           //to add values of path_S

        for(long i = 1; i <= N; ++i)    //for each time step
        {
            
            path_S = Next_S(path_S, drift_dt, sig_rt);    //update the next value of S
            sum += path_S;
                    
        }
        
        sum /= N;
        
        double payoff = opt.Payoff(path_S);
        
        /*
        switch(o_type)
        {
            case 'c': payoff = my_max(0.0, path_S - X);    // plain call
                      break;
                      
            case 'p': payoff = my_max(0.0, X - path_S);    // plain put
                      break;
            
            case 'a': payoff = my_max(0.0, sum - X);       // average rate call
                      break;
            
            case 'b': payoff = my_max(0.0, X - sum);       // average rate put
                      break;
                      
            default:  ut::OutputLine("Unrecognized option character code");
                      return ut::PauseAndReturn();      
        }
        */
        
        sum_payoff += payoff;
        sum_payoff_2 += payoff*payoff;
    }
    
    //outputs
    double c = discount*sum_payoff/M;    //option value
    double se = discount*std::sqrt(sum_payoff_2 - sum_payoff*sum_payoff/M)/M;    //standard error
    
    double e_time = (std::clock() - s_time)/CLOCKS_PER_SEC;
    
    ut::OutputLine("\nOption value:  ", c);
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
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX




















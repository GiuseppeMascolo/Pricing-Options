//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Input.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef InputH
#define InputH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class Input
{
    public:
        Input();
        
        double GetS0() const {return S0_;}
        double GetR() const {return r_;}
        double GetSig() const {return sig_;}
        
        double GetT() const {return T_;}
        double GetX() const {return X_;}
        
        double GetN() const {return N_;}
        double GetM() const {return M_;}
        
    private:
        double S0_;    //intial stock price
        double r_;     //risk-free rate
        double sig_;   //volatility
        
        double X_;     //option strike
        double T_;     //time to maturity
        
        //char o_type_;  // option type
        
        long N_;      //time steps
        long M_;      //Monte Carlo repetitions
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

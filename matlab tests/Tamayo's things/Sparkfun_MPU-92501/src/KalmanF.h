class KalmanF{
    
    public: 

    float Q_angle = 0.001;
    float Q_bias = 0.003;
    float R_measure = 0.03;
    float angle = 0.0; 
    float bias = 0.0; 

    float P00 = 0.0;  
    float P01 = 0.0;
    float P10 = 0.0;
    float P11 = 0.0;
    float rate = 0.0;

    float S=0.0;
    float y=0.0;

    float K0=0.0;
    float K1=0.0;
    
    float P00_temp = 0.0;
    float P01_temp = 0.0;
    public: 
    //El angulo ha de estar en grados, el valor del gyro en grados/s y el dt en segundos
    float getAngle(float newAngle, float  newRate, float  dt);
    void setAngle(float newAngle); 
    float getRate();
    void setQangle(float newQ_angle);
    void setQbias(float  newQ_bias);
    void setRmeasure(float newR_measure);
    float getQangle();
    float getQbias();
    float getRmeasure();
};
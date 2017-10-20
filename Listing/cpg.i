#line 1 "..\\..\\User\\Alogrisem\\src\\CPG.c"
#line 1 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int __ARM_vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int __ARM_vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int __ARM_vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));
   








 

extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 1021 "D:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"



 

#line 2 "..\\..\\User\\Alogrisem\\src\\CPG.c"
#line 1 "..\\..\\User\\Alogrisem\\inc\\cpg.h"




#line 15 "..\\..\\User\\Alogrisem\\inc\\cpg.h"

void cpg_run();
void CPG_Configuration();
void CPG_caculate();
void Pectoral_CPG_Calculate();

#line 3 "..\\..\\User\\Alogrisem\\src\\CPG.c"












float theta[3];
int Joint_Angle_value[3]; 	

float Motor_Speed = 1; 
float Motor_Log_degree_12 = 45;
float Motor_Log_degree_13 = 0;
float Motor_Amplitude_degree[3]= {30,30,0};    
float Motor_Dynamic_Offset_degree[3] ={0,0,0};
float Motor_Static_Offset_degree[3]={0,0,0};
float vol[6];


float Coupling_Weight[3][3]={{0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,0.5}};
float Log_Angle[3][3]={{0,0,0},{0,0,0},{0,0,0}};
int Gain_R=10;
int Gain_X=5;

float dr_previous[4]={0,0,0,0};
float dr_present[4]={0,0,0,0};
float r_previous[4]={0,0,0,0};
float r_present[4];

float dx_previous[3]={0,0,0};
float dx_present[3]={0,0,0};
float x_previous[3]={0,0,0};
float x_present[3];

float dfai_previous[3]={0,0,0};
float dfai[3]={0,0,0};
float fai_previous[3]={0,0,0};
float fai[3]={0,0,0};

float T = 0.001;

char cpg_A = 0;
char cpg_F = 0;
char cpg_P = 0;
char cpg_or_not = 0;
float record_data[9];
float clear_data[9]={0};
int record_data_sign=0;
int clear_data_sign=0;
int flag=0; 

float TaylorCos(float x);
float TaylorSin(float x);



void CPG_calculate(void)
{               
	float omega[3];
	float Amplitude_R[3];
	float Offset_T[3];

	omega[0]=Motor_Speed; 
	omega[1]=Motor_Speed; 
	omega[2]=Motor_Speed;

	Amplitude_R[0]=Motor_Amplitude_degree[0]*3.14159/180;		
	Amplitude_R[1]=Motor_Amplitude_degree[1]*3.14159/180;
	Amplitude_R[2]=Motor_Amplitude_degree[2]*3.14159/180;
    
	Offset_T[0]=Motor_Dynamic_Offset_degree[0]*3.14159/180;	
	Offset_T[1]=Motor_Dynamic_Offset_degree[1]*3.14159/180;
	Offset_T[2]=Motor_Dynamic_Offset_degree[2]*3.14159/180;
    
	Log_Angle[0][1]=Motor_Log_degree_12*3.14159/180;					
	Log_Angle[0][2]=Motor_Log_degree_13*3.14159/180;					
	Log_Angle[1][2]=Log_Angle[0][2]-Log_Angle[0][1];		
	Log_Angle[1][0]=-Log_Angle[0][1];
	Log_Angle[2][1]=-Log_Angle[1][2];
	Log_Angle[2][0]=-Log_Angle[0][2];
	Log_Angle[0][0]=0;
	Log_Angle[1][1]=0;
	Log_Angle[2][2]=0;

	dr_present[0]=dr_previous[0]+T*((-Gain_R*Gain_R)*(r_previous[0]-Amplitude_R[0])-2*Gain_R*dr_previous[0]);
	r_present[0]=r_previous[0]+T*dr_present[0];

	dr_present[1]=dr_previous[1]+T*((-Gain_R*Gain_R)*(r_previous[1]-Amplitude_R[1])-2*Gain_R*dr_previous[1]);
	r_present[1]=r_previous[1]+T*dr_present[1];

	dr_present[2]=dr_previous[2]+T*((-Gain_R*Gain_R)*(r_previous[2]-Amplitude_R[2])-2*Gain_R*dr_previous[2]);
	r_present[2]=r_previous[2]+T*dr_present[2];


	dx_present[0]=dx_previous[0]+T*((-Gain_X*Gain_X)*(x_previous[0]-Offset_T[0])-2*Gain_X*dx_previous[0]);
	x_present[0]=x_previous[0]+T*dx_present[0];

	dx_present[1]=dx_previous[1]+T*((-Gain_X*Gain_X)*(x_previous[1]-Offset_T[1])-2*Gain_X*dx_previous[1]);
	x_present[1]=x_previous[1]+T*dx_present[1];

	dx_present[2]=dx_previous[2]+T*((-Gain_X*Gain_X)*(x_previous[2]-Offset_T[2])-2*Gain_X*dx_previous[2]);
	x_present[2]=x_previous[2]+T*dx_present[2];

	dfai[0]=dfai_previous[0]+T*(Coupling_Weight[0][1]*Coupling_Weight[0][1]*(fai_previous[1]-fai_previous[0]-Log_Angle[0][1])-2*(Coupling_Weight[0][1]+Coupling_Weight[0][2])*(dfai_previous[0]-2*3.14159*omega[0])+Coupling_Weight[0][2]*Coupling_Weight[0][2]*(fai_previous[2]-fai_previous[0]-Log_Angle[0][2]));
	fai[0]=fai_previous[0]+T*dfai[0];
	dfai[1]=dfai_previous[1]+T*(Coupling_Weight[1][0]*Coupling_Weight[1][0]*(fai_previous[0]-fai_previous[1]-Log_Angle[1][0])-2*(Coupling_Weight[1][0]+Coupling_Weight[1][2])*(dfai_previous[1]-2*3.14159*omega[1])+Coupling_Weight[1][2]*Coupling_Weight[1][2]*(fai_previous[2]-fai_previous[1]-Log_Angle[1][2]));
	fai[1]=fai_previous[1]+T*dfai[1];
	dfai[2]=dfai_previous[2]+T*(Coupling_Weight[2][0]*Coupling_Weight[2][0]*(fai_previous[0]-fai_previous[2]-Log_Angle[2][0])-2*(Coupling_Weight[2][0]+Coupling_Weight[2][1])*(dfai_previous[2]-2*3.14159*omega[2])+Coupling_Weight[2][1]*Coupling_Weight[2][1]*(fai_previous[1]-fai_previous[2]-Log_Angle[2][1]));
	fai[2]=fai_previous[2]+T*dfai[2];

	theta[0]=x_present[0]+r_present[0]*TaylorSin(fai[0]);  
	theta[1]=x_present[1]+r_present[1]*TaylorSin(fai[1]);
	theta[2]=x_present[2]+r_present[2]*TaylorSin(fai[2]);













	dr_previous[0] = dr_present[0];
	r_previous[0] = r_present[0];
	dr_previous[1] = dr_present[1];
	r_previous[1]= r_present[1];
	dr_previous[2] = dr_present[2];
	r_previous[2]= r_present[2];

	dx_previous[0] = dx_present[0];
	x_previous[0] = x_present[0];
	dx_previous[1] = dx_present[1];
	x_previous[1]= x_present[1];
	dx_previous[2] = dx_present[2];
	x_previous[2]= x_present[2];

	if(((((fai[0]) < (fai[1]) ? fai[0] : fai[1])) < (((fai[1]) < (fai[2]) ? fai[1] : fai[2])) ? ((fai[0]) < (fai[1]) ? fai[0] : fai[1]) : ((fai[1]) < (fai[2]) ? fai[1] : fai[2]))>2*3.14159)
	{
		fai[0]=fai[0]-2*3.14159;
		fai[1]=fai[1]-2*3.14159;
		fai[2]=fai[2]-2*3.14159;
	}

	dfai_previous[0]=dfai[0];
	fai_previous[0]=fai[0];
	dfai_previous[1]=dfai[1];
	fai_previous[1]=fai[1];
	dfai_previous[2]=dfai[2];
	fai_previous[2]=fai[2];	
	
	vol[3]=theta[0];
	vol[4]=theta[1];
	vol[5]=theta[2];
}

 


  
 
float Pectoral_Theta[2] = {0, 0};
 
float Pectoral_Volcety = 1.0;                 
float Pectoral_Phase_Dif  = 90;             
float Pectoral_Amplitude[2] = {50, 70};     
float Pectoral_Dynamic_Offset[2] = {0, 0};  
 
float Pectoral_Coupling_Weight[3][3] = {{0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,0.5}};     
float Pectoral_Log_Angle[3][3] = {{0,0,0},{0,0,0},{0,0,0}};                             
 
float d_amp_previous[2] = {0, 0};
float d_amp_present[2] = {0, 0};
float amp_previous[2] = {0, 0};
float amp_present[2] = {0, 0};
 
float d_frq_previous[2] = {0, 0};
float d_frq_present[2] = {0, 0};
float frq_previous[2] = {0, 0};
float frq_present[2] = {0, 0};
 
float d_phi_previous[3] = {0, 0, 0};
float d_phi_present[3] = {0, 0, 0};
float phi_previous[3] = {0, 0, 0};
float phi_present[3] = {0, 0, 0};

void Pectoral_CPG_Calculate(void)
{
    float amp_pec[2];
    float offest_pec[2]; 

    amp_pec[0] = Pectoral_Amplitude[0] * 0.01745f;
    amp_pec[1] = Pectoral_Amplitude[1] * 0.01745f;

    offest_pec[0] = Pectoral_Dynamic_Offset[0] * 0.01745f;
    offest_pec[1] = Pectoral_Dynamic_Offset[1] * 0.01745f;
       
    Pectoral_Log_Angle[0][1] = Pectoral_Phase_Dif * 0.01745f;
    Pectoral_Log_Angle[1][2] = -Pectoral_Log_Angle[0][1];
    Pectoral_Log_Angle[1][0] =  Pectoral_Log_Angle[1][2];
    Pectoral_Log_Angle[2][1] = -Pectoral_Log_Angle[1][0];

    d_amp_present[0] = d_amp_previous[0] + T * ((-Gain_R^2) * (amp_previous[0] - amp_pec[0]) - 2 * Gain_R * d_amp_previous[0]);
    amp_present[0] = amp_previous[0] + T * d_amp_present[0];
    
    d_amp_present[1] = d_amp_previous[1] + T * ((-Gain_R^2) * (amp_previous[1] - amp_pec[1]) - 2 * Gain_R * d_amp_previous[1]);
    amp_present[1] = amp_previous[1] + T * d_amp_present[1];
    
    d_frq_present[0] = d_frq_previous[0] + T * ((-Gain_X^2) * (frq_previous[0] - offest_pec[0]) - 2 * Gain_X * d_frq_previous[0]);
    frq_present[0] = frq_previous[0] + T * d_frq_present[0];
    
    d_frq_present[1] = d_frq_previous[1] + T * ((-Gain_X^2) * (frq_previous[1] - offest_pec[1]) - 2 * Gain_X * d_frq_previous[1]);
    frq_present[1] = frq_previous[1] + T * d_frq_present[1];
    
	d_phi_present[0]=d_phi_previous[0]+T*(Pectoral_Coupling_Weight[0][1]*Pectoral_Coupling_Weight[0][1]*(phi_previous[1]-phi_previous[0]-Pectoral_Log_Angle[0][1])-2*(Pectoral_Coupling_Weight[0][1]+Pectoral_Coupling_Weight[0][2])*(d_phi_previous[0]-2*3.14159*Pectoral_Volcety)+Pectoral_Coupling_Weight[0][2]*Pectoral_Coupling_Weight[0][2]*(phi_previous[2]-phi_previous[0]-Pectoral_Log_Angle[0][2]));
	phi_present[0]=phi_previous[0]+T*d_phi_present[0];
    
	d_phi_present[1]=d_phi_previous[1]+T*(Pectoral_Coupling_Weight[1][0]*Pectoral_Coupling_Weight[1][0]*(phi_previous[0]-phi_previous[1]-Pectoral_Log_Angle[1][0])-2*(Pectoral_Coupling_Weight[1][0]+Pectoral_Coupling_Weight[1][2])*(d_phi_previous[1]-2*3.14159*Pectoral_Volcety)+Pectoral_Coupling_Weight[1][2]*Pectoral_Coupling_Weight[1][2]*(phi_previous[2]-phi_previous[1]-Pectoral_Log_Angle[1][2]));
	phi_present[1]=phi_previous[1]+T*d_phi_present[1];
    
	d_phi_present[2]=d_phi_previous[2]+T*(Pectoral_Coupling_Weight[2][0]*Pectoral_Coupling_Weight[2][0]*(phi_previous[0]-phi_previous[2]-Pectoral_Log_Angle[2][0])-2*(Pectoral_Coupling_Weight[2][0]+Pectoral_Coupling_Weight[2][1])*(d_phi_previous[2]-2*3.14159*Pectoral_Volcety)+Pectoral_Coupling_Weight[2][1]*Pectoral_Coupling_Weight[2][1]*(phi_previous[1]-phi_previous[2]-Pectoral_Log_Angle[2][1]));
	phi_present[2]=phi_previous[2]+T*d_phi_present[2];
    
     
	Pectoral_Theta[0]=frq_present[0]+amp_present[0]*TaylorSin(phi_present[0]);  
	Pectoral_Theta[1]=frq_present[1]+amp_present[1]*TaylorSin(phi_present[1]);
	
	d_amp_previous[0] = d_amp_present[0];
	amp_previous[0] = amp_present[0];
	d_amp_previous[1] = d_amp_present[1];
	amp_previous[1]= amp_present[1];

	d_frq_previous[0] = d_frq_present[0];
	frq_previous[0] = frq_present[0];
	d_frq_previous[1] = d_frq_present[1];
	frq_previous[1]= frq_present[1];
    
	if(((((phi_present[0]) < (phi_present[1]) ? phi_present[0] : phi_present[1])) < (((phi_present[1]) < (phi_present[2]) ? phi_present[1] : phi_present[2])) ? ((phi_present[0]) < (phi_present[1]) ? phi_present[0] : phi_present[1]) : ((phi_present[1]) < (phi_present[2]) ? phi_present[1] : phi_present[2]))>2*3.14159)
	{
		phi_present[0]=phi_present[0]-2*3.14159;
		phi_present[1]=phi_present[1]-2*3.14159;
		phi_present[2]=phi_present[2]-2*3.14159;
	}
    
	d_phi_previous[0]=d_phi_present[0];
	phi_previous[0]=phi_present[0];
	d_phi_previous[1]=d_phi_present[1];
	phi_previous[1]=phi_present[1];
	d_phi_previous[2]=d_phi_present[2];
	phi_previous[2]=phi_present[2];
}
 												   
void cpg_run()
{
	CPG_calculate();
}

float TaylorSin(float x)
{
	float y=0.0;
	float temp;

        while(x>(2*3.14159))
            x=x-2*3.14159;
        while(x<0)
            x=x+2*3.14159;

        if(x<=(3.14159/2))
		y=x-x*x*x/6;

        if(x>(3.14159/2)&&x<=3.14159)
	   {
		temp=3.14159-x;
		y=temp-temp*temp*temp/6;
	   }

        if(x>3.14159&&x<=(3.14159*3/2))
	   {
		temp=x-3.14159;
		y=temp*temp*temp/6-temp;
	   }

		if(x>(3.14159*3/2))
	   {
	        temp=2*3.14159-x;
	        y=temp*temp*temp/6-temp;
	   }
	 return y;
}

float TaylorCos(float x)
{
	float y=0.0;
	float temp;

        while(x>(3.14159))
            x=x-2*3.14159;
        while(x<(-3.14159))
            x=x+2*3.14159;
        if(x>0&&x<=(3.14159/2))
		y=1-x*x/2+x*x*x*x/24;

        if(x>(-3.14159/2)&&x<=0)
	   {
		temp=3.14159-x;
		y=1-temp*temp/2+temp*temp*temp*temp/24;
	   }

        if(x>(3.14159/2)&&x<=3.14159)
	   {
		temp=x-3.14159;
		y=temp*temp/2-temp*temp*temp*temp/24-1;
	   }

		if(x>=(-3.14159)&&x<=(-3.14159/2))
	   {
	        temp=2*3.14159-x;
	        y=temp*temp/2-temp*temp*temp*temp/24-1;
	   }
	 return y;
}




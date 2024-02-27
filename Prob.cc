#include <iostream>
#include <cmath>
#include <string.h>
#include <float.h>
#include <complex.h>
#include <vector>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <globes/globes.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <filesystem>
#define GLB_SIGMA_E 6

const int GLB_AEE = 51;
const int GLB_ABS_AEMU = 52;
const int GLB_ARG_AEMU = 53;
const int GLB_ABS_AETAU = 54;
const int GLB_ARG_AETAU = 55;
const int GLB_AMUMU = 56;
const int GLB_ABS_AMUTAU = 57;
const int GLB_ARG_AMUTAU = 58;
const int GLB_ATAUTAU = 59;

const int GLB_CEE = 60;
const int GLB_ABS_CEMU = 61;
const int GLB_ARG_CEMU = 62;
const int GLB_ABS_CETAU = 63;
const int GLB_ARG_CETAU = 64;
const int GLB_CMUMU = 65;
const int GLB_ABS_CMUTAU = 66;
const int GLB_ARG_CMUTAU = 67;
const int GLB_CTAUTAU = 68;

extern "C"
{
    #include "bsm.h"
}
using namespace std;

char AEDLFILE[] = "./lib/DUNE_GLoBES.glb";
int main(int argc, char * argv[])
{
    glbInit(argv[0]);
    glbInitExperiment(AEDLFILE, &glb_experiment_list[0], &glb_num_of_exps);
    
    ofstream outBackup;
    ofstream outBSM;
    ofstream outBSMn;
    ofstream outBSM_co;
    ofstream outchi;

    /*Arquivo de entrada chi2*/
    outchi.open("chi2_co.dat");
    outBSM.open("betachi2.dat");
    outBSM_co.open("parametros.dat");
    outBSMn.open("BSMprobability_a_mue.dat");
    
    
    /*nome base para criação de todos arquivos e pastas
    o restante nome_novo etc. para os especificos*/
    ifstream in;

    double dm21 = 7.55e-5;
    double dm31 = 2.50e-3;
    double theta12 = 33.45*M_PI/180.0;/*asin(sqrt(0.304));*/
    double theta23 = 42.1*M_PI/180.0;/*asin(sqrt(0.573));*/
    double theta13 = 8.62*M_PI/180.0;/*asin(sqrt(0.0222));*/
    double deltacp = 230*M_PI/180.0;/*-0.68 * M_PI*/; 

    /*ERRORS*/
    //double theta12error = /*0.14*/0*theta12;
    //double theta13error = /*0.09*/0*theta13;
	//double theta23error = /*0.27*/0*theta23;
	//double deltacperror = /*1.0*/0*deltacp;
    //double dm21error    = /*0.16*/0*dm21;
	//double dm31error    = /*0.07*/0*dm31;   

    
    bsm_init_probability_engine_3();
    glbRegisterProbabilityEngine(8 * 9 - 3,
                               &bsm_probability_matrix,
                               &bsm_set_oscillation_parameters,
                               &bsm_get_oscillation_parameters,
                               NULL);

    /* Define "true" oscillation parameter vector */
    glb_params true_values = glbAllocParams();
    glb_params test_values = glbAllocParams();
    glb_params input_errors = glbAllocParams();
    glb_projection myprojection = glbAllocProjection();
    glb_params minimum = glbAllocParams();

    for(unsigned int i=0; i < 69; i++)
    {
    glbSetOscParams(true_values, 0.0, i);
    glbSetOscParams(test_values, 0.0, i);
    glbSetOscParams(input_errors, 0.0, i);
    }
    

    for(unsigned int i=0; i < 69; i++)
	{
	glbSetProjectionFlag(myprojection, GLB_FIXED, i);
	}

    glbSetDensityProjectionFlag(myprojection,GLB_FIXED,GLB_ALL);
    glbSetProjection(myprojection);

    glbDefineParams(true_values,theta12,theta13,theta23,deltacp,dm21,dm31);
    glbSetDensityParams(true_values,1.0,GLB_ALL);

    glbDefineParams(test_values,theta12,theta13,theta23,deltacp,dm21,dm31);
    glbSetDensityParams(test_values,1.0,GLB_ALL);

    glbSetOscillationParameters(true_values);
    glbSetRates();
   
    /*Termos para Matriz a*/
    double abs_a_ee = 0;
    double abs_a_mue = 0;//-2.0e-23 / 1.0e-9;
    double arg_a_mue =  0;
    double abs_a_etau = 0;
    double arg_a_etau = 0;
    double abs_a_mumu = 0;
    double abs_a_mutau = 0;
    double arg_a_mutau = 0;
    double abs_a_tautau = 0;

    /*Termos para Matriz c*/
    double abs_c_ee = 0;
    double abs_c_mue = 0;//-2.0e-32 / 1.0e-9;
    double arg_c_mue = 0;
    double abs_c_etau = 0;
    double arg_c_etau = 0;
    double abs_c_mumu = 0;
    double abs_c_mutau = 0;
    double arg_c_mutau = 0;
    double abs_c_tautau = 0;


    //############ LIV Parameter #################################//

    /*A*/
    glbSetOscParams(test_values, abs_a_ee, GLB_AEE);  // a_ee
    glbSetOscParams(test_values, abs_a_mue, GLB_ABS_AEMU);  // a_mue magnitude
    glbSetOscParams(test_values, arg_a_mue, GLB_ARG_AEMU);  // a_mue phase
    glbSetOscParams(test_values, abs_a_etau, GLB_ABS_AETAU);  // a_etau
    glbSetOscParams(test_values, arg_a_etau, GLB_ARG_AETAU);  // a_etau phase
    glbSetOscParams(test_values, abs_a_mumu, GLB_AMUMU);  // a_mumu
    glbSetOscParams(test_values, abs_a_mutau, GLB_ABS_AMUTAU);  // a_mutau
    glbSetOscParams(test_values, arg_a_mutau, GLB_ARG_AMUTAU);  // a_mutau phase
    glbSetOscParams(test_values, abs_a_tautau, GLB_ATAUTAU);  //a_tautau

    /*C*/
    glbSetOscParams(test_values, abs_c_ee, GLB_CEE);  // c_ee
    glbSetOscParams(test_values, abs_c_mue, GLB_ABS_CEMU);  // c_mue magnitude
    glbSetOscParams(test_values, arg_c_mue, GLB_ARG_CEMU);  // c_mue phase
    glbSetOscParams(test_values, abs_c_etau, GLB_ABS_CETAU);  // c_etau
    glbSetOscParams(test_values, arg_c_etau, GLB_ARG_CETAU);  // c_etau phase
    glbSetOscParams(test_values, abs_c_mumu, GLB_CMUMU);  // c_mumu
    glbSetOscParams(test_values, abs_c_mutau, GLB_ABS_CMUTAU);  // c_mutau
    glbSetOscParams(test_values, arg_c_mutau, GLB_ARG_CMUTAU);  // c_mutau phase
    glbSetOscParams(test_values, abs_c_tautau, GLB_CTAUTAU);// c_tautest

   
    
   


    /*Correlações*/
    
    //glbSetOscParams(input_errors,theta23error, GLB_THETA_23);
    //glbSetOscParams(input_errors,deltacperror, GLB_DELTA_CP);
    //glbSetOscParams(input_errors,M_PI, GLB_ARG_AEMU);

	//glbDefineParams(input_errors,theta12error,theta13error,theta23error,deltacperror,dm21error,dm31error);
	glbSetDensityParams(input_errors,0.,GLB_ALL);
	glbSetCentralValues(true_values);
	glbSetInputErrors(input_errors);

    /* Define my own two-parameter projection for glbChiNP */
	glbDefineProjection(myprojection,GLB_FIXED,GLB_FIXED,GLB_FIXED,
    GLB_FIXED,GLB_FIXED,GLB_FIXED);


    for(unsigned int i=0; i < 69; i++){
	    glbSetProjectionFlag(myprojection, GLB_FIXED, i);
	}

    //glbSetProjectionFlag(myprojection, GLB_FREE, GLB_THETA_13);
    glbSetProjectionFlag(myprojection, GLB_FREE, GLB_THETA_23);
    glbSetProjectionFlag(myprojection, GLB_FREE, GLB_DELTA_CP);
    glbSetProjectionFlag(myprojection, GLB_FREE, GLB_ARG_AEMU);
    //glbSetProjectionFlag(myprojection, GLB_FREE, GLB_ABS_AEMU);		
    
    glbSetDensityProjectionFlag(myprojection,GLB_FIXED,GLB_ALL);
    glbSetProjection(myprojection);  

    /*
    double energy, prob_BSM;
    double emin= 0.25 ; //GeV
    double emax= 8 ; //GeV
    double step= 1000;
    //double L = 1300; // km
    for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
    {
    glbSetOscillationParameters(true_values);
    //prob_BSM=glbVacuumProbability(2,1,+1,energy,L);
    prob_BSM=glbProfileProbability(0,2,1,+1,energy);
    outBSMn<<energy<<"  "<<prob_BSM<<endl;
    }
    */

    /* Compute chi^2 sem as correlações */
    double chi, chi2;
    double a;
    double ai = 0; 
    double af = 5.0;
    int points = 200;


    for(a=ai;a<af;a+=(af-ai)/points)
    {
  
		glbSetOscParams(test_values,a*2.0e-23/1.0e-9,GLB_ABS_AEMU);

	    /* Seta o vetor dos valores que vão filtrar os test_values */
        //glbSetOscParams(test_values,47.1*M_PI/180,GLB_THETA_23);
        //glbSetOscParams(test_values,230*M_PI/180,GLB_DELTA_CP);
        glbSetOscParams(test_values,4.02124,GLB_ARG_AEMU); 
        //chi2=glbChiNP(test_values,minimum,GLB_ALL);
        
        glbSetOscParams(test_values,42.5*M_PI/180,GLB_THETA_23);
        //glbSetOscParams(test_values,230*M_PI/180,GLB_DELTA_CP);
        //glbSetOscParams(test_values,1.31947,GLB_ARG_AEMU); 
        
	    chi=glbChiNP(test_values,minimum,GLB_ALL);
        //chi2=glbChiTheta23(test_values,minimum,GLB_ALL);

        //if(chi2<chi) chi=chi2;

        //glbGetCentralValues(test_values);
        //glbGetInputErrors(input_errors);

        outchi<<a<<" "<<chi<<endl;
    }

    //glbPrintProjection(FILE* "parametros.dat",test_values);

    outchi.close();
    outBSM_co.close();
    outBSMn.close();
    outBSM.close();

    glbFreeParams(true_values);
    glbFreeParams(test_values);
    glbFreeParams(input_errors);
    glbFreeParams(minimum); 
    glbFreeProjection(myprojection);
    return 0;
}
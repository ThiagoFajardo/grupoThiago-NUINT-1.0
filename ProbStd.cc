#include <iostream>
#include <cmath>
#include <string.h>
#include<float.h>
#include<complex.h>
#include <vector>
#include<gsl/gsl_complex.h>
#include<gsl/gsl_complex_math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include <globes/globes.h>
#include<fstream>

using namespace std;

char AEDLFILE[] = "./lib/DUNE_GLoBES.glb";


int main(int argc, char * argv[])
{

	glbInit(argv[0]);
	glbInitExperiment(AEDLFILE, &glb_experiment_list[0], &glb_num_of_exps);

	ofstream outstd;
	ofstream outstdchi2;
	ofstream outstdchi2_correlations;

	outstd.open("probability_DUNE.dat");
    outstdchi2.open("stdchi2.dat");
	outstdchi2_correlations.open("chi2_co.dat");


    //char* MYFILE="log.dat";
    //FILE* stream;
    //if(strlen(MYFILE)>0) stream=fopen(MYFILE, "w");
    //    else stream = stdout;
	
	double dm21 = 7.42e-5;
	double dm31 = 2.515e-3;
	double theta12 = asin(sqrt(0.304));
	double theta23 = asin(sqrt(0.573));
	double theta13 = asin(sqrt(0.0222));
	double deltacp = -0.68 * M_PI;

    cout << "dm21 = " << dm21 << endl;
    cout << "dm31 = " << dm31 << endl;
    cout << "theta12 = " << theta12 << " (" << pow(sin(theta12),2) << ")" << endl;
    cout << "theta23 = " << theta23 << " (" << pow(sin(theta23),2) << ")" << endl;
    cout << "theta13 = " << theta13 << " (" << pow(sin(theta13),2) << ")" << endl;
    cout << "deltacp = " << deltacp << endl;
    cout << "Pi = " << M_PI << endl;

	/* Define "true" oscillation parameter vector */
	glb_params true_values = glbAllocParams();
	glb_params test_values = glbAllocParams();
	glb_params input_errors = glbAllocParams();
	glb_projection theta13_projection = glbAllocProjection();
	

    glbDefineParams(true_values,theta12,theta13,theta23,deltacp,dm21,dm31);
	glbDefineParams(test_values,theta12,theta13,theta23,deltacp,dm21,dm31);

    glbPrintParams(stdout,true_values);
	
	glbSetDensityParams(true_values, 1.0, GLB_ALL);
    glbSetDensityParams(test_values,1.0,GLB_ALL);

	glbSetOscillationParameters(true_values);
    glbSetOscillationParameters(test_values);

	glbCopyParams(true_values,test_values);

	/*Correlações*/
	glbDefineParams(input_errors, 0.1*theta12, 0.1*theta13, 0.15*theta23,
                                0.0, 0.05*dm21, 0.05*dm31);
	glbSetDensityParams(input_errors,0.05,GLB_ALL);
	glbSetCentralValues(true_values);
	glbSetInputErrors(input_errors);
    
	/* Define my own two-parameter projection for glbChiNP: Only deltacp is free! */
	glbDefineProjection(theta13_projection,GLB_FIXED,GLB_FIXED,GLB_FIXED,GLB_FREE,GLB_FIXED,GLB_FIXED);
	glbSetDensityProjectionFlag(theta13_projection,GLB_FIXED,GLB_ALL);
	glbSetProjection(theta13_projection);	

	glbSetRates();

	double energy, prob;
	double emin= 0.25 ; //GeV
	double emax=8 ; //GeV
	double step= 1000;
	//double L = 1300; // km

/* Compute chi^2 sem as correlações */
    double x, y, chi, chi2;
    int i,j;
    /*x numero total de eventos*/

    for(i=1; i<101; i++)        /* th13 loop */
    //for(j=1; j<51; j++)  /*loop */
    {
        /*É preciso definir o parametro de espaço, utilizando 100 steps
        o alcance do theta13 é 0.122-0.175 e do deltacp é 0-2pi*/

        //x=0.13+i*(0.17-0.13)/50;
        //y=0+j*(-2*M_PI)/50;
		x=0+i*(2*M_PI)/100;

	    /* Seta o vetor dos valores que vão filtrar os test_values */
	    //glbSetOscParams(test_values,x,GLB_THETA_13);
	    //glbSetOscParams(test_values,y,GLB_DELTA_CP);
		glbSetOscParams(test_values,x,GLB_DELTA_CP);
	
	    /* Compute Chi^2 com os sistematicos apenas, para todos os experimentos e regras*/
	    chi=glbChiSys(test_values,GLB_ALL,GLB_ALL);
	    //outstdchi2<<x<<" "<<y<<" "<<chi<<endl;
		outstdchi2<<x<<" "<<chi<<endl;
    }

	/*COM AS CORRELAÇÕES*/

	for(i=1; i<51; i++)        /* th13 loop */
    for(j=1; j<51; j++)  /*loop */
    {
        /*É preciso definir o parametro de espaço, utilizando 100 steps
        o alcance do theta13 é 0.122-0.175 e do deltacp é 0-2pi*/

        x=0.13+i*(0.17-0.13)/50;
        y=0+j*(-2*M_PI)/50;
		//x=0+i*(-2*M_PI)/50;

	    /* Seta o vetor dos valores que vão filtrar os test_values */
	    glbSetOscParams(test_values,x,GLB_THETA_13);
	    glbSetOscParams(test_values,y,GLB_DELTA_CP);
		glbSetOscParams(test_values,x,GLB_DELTA_CP);
	
	    /* Compute Chi^2 com os sistematicos apenas, para todos os experimentos e regras*/
	    chi=glbChiNP(test_values,NULL,GLB_ALL);
		chi2=glbChiTheta13(test_values,NULL,GLB_ALL);
	    outstdchi2_correlations<<x<<" "<<y<<" "<<chi<<endl;
    }

	for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
	{
	  glbSetOscillationParameters(true_values);
	  //prob=glbVacuumProbability(2,1,+1,energy,L); 
	  prob=glbProfileProbability(0,2,1,+1,energy);
	  outstd<<energy<<"  "<<prob<<endl;
	}

	outstdchi2_correlations.close();
	outstdchi2.close();
	outstd.close();
    glbFreeParams(test_values);
	glbFreeParams(true_values);
 	return 0;

}
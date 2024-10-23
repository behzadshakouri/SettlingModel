#include "System.h"
#include "Script.h"
#include "qfileinfo.h"
#include "modelcreator.h"
#include "resultgrid.h"
#include "vtk.h"


int main(int argc, char *argv[])
{

    /*CTimeSeries<double> OUEx1, OUEx2;
    OUEx1.CreateOUProcess(0,10,0.05,0.2);
    OUEx2.CreateOUProcess(0,10,0.05,5);
    vector<double> logparams; logparams.push_back(1); logparams.push_back(0.5);
    vector<double> expparams; expparams.push_back(3);
    CTimeSeries<double> OUEx1Log = OUEx1.MapfromNormalScoreToDistribution("lognormal", logparams);
    CTimeSeries<double> OUEx2Log = OUEx2.MapfromNormalScoreToDistribution("lognormal", logparams);

    CTimeSeries<double> OUEx1Exp = OUEx1.MapfromNormalScoreToDistribution("exp", expparams);
    CTimeSeries<double> OUEx2Exp = OUEx2.MapfromNormalScoreToDistribution("exp", expparams);

    OUEx1Log.writefile("/home/behzad/Projects/Settling_Models/OUEx1Log.txt");
    OUEx2Log.writefile("/home/behzad/Projects/Settling_Models/OUEx2Log.txt");

    OUEx1Exp.writefile("/home/behzad/Projects/Settling_Models/OUEx1Exp.txt");
    OUEx2Exp.writefile("/home/behzad/Projects/Settling_Models/OUEx2Exp.txt");
*/

    model_parameters mp;
    mp.nr = 6;
    mp.nz = 6;
    mp.K_sat = 1;
    mp.alpha = 20;
    mp.n = 1.8;
    mp.rw = 0.1;
    mp.theta_sat = 0.4;
    mp.theta_r = 0.05;
    mp.initial_theta = 0.2;

    System *system=new System();
    ModelCreator ModCreate;
    cout<<"Creating model ..." <<endl;
    ModCreate.Create(mp,system);
    cout<<"Creating model done..." <<endl;

    system->SetWorkingFolder("/home/behzad/Projects/Settling_Models/");
    system->SetSilent(false);
    cout<<"Saving"<<endl;
    system->SavetoScriptFile("/home/behzad/Projects/Settling_Models/CreatedModel.ohq");

    cout<<"Solving ..."<<endl;
    system->Solve();
    cout<<"Writing outputs in '"<< system->GetWorkingFolder() + system->OutputFileName() +"'"<<endl;
    CTimeSeriesSet<double> output = system->GetOutputs();
    output.writetofile(system->GetWorkingFolder() + system->OutputFileName());
    cout<<"Getting results into grid"<<endl;
    ResultGrid resgrid(output,"theta",system);
    //cout<<"Writing VTPs"<<endl;
    //resgrid.WriteToVTP("Moisture_content",system->GetWorkingFolder()+"moisture.vtp");

    return 0;

}

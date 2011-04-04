#include "genreportctrl.h"
#include "mapwinctrl.h"

GenReportCtrl* GenReportCtrl::anInstance = NULL;

GenReportCtrl::GenReportCtrl(){}

GenReportCtrl* GenReportCtrl::getInstance()
{
    if(!anInstance) //If it is doesn't already exist
        anInstance = new GenReportCtrl; //Create a new instance, new for the heap.

    return anInstance;//Return the instance.
}

void GenReportCtrl::invalid(){

    invalidWin = new InvalidWindow();

    invalidWin->setLabelText("You must select a facility.");
    invalidWin->show();

    genCTRL::center(*invalidWin);
}

QList<Facility*> GenReportCtrl::getFacilities(){

    facilitiesList = MapWinCtrl::getInstance()->listOfFacility;

return facilitiesList;
}


//As the next following function are the same, we will use instead the following idea.
// from UI : Send a string, that will decide what if we will take.
// Stay like this for now, but unless xml is enormous we'll use what was proposed ^^.


void GenReportCtrl::occRateAC(QString start,QString end,QString AC,QString CCC,QString LTC)
{
    //Ask protocol
    //Get Answer
    //In this example, we will try with 3 facilities, so 3 answers from protocol
    //Answer #1 for facility id = 1 : 350
    //Answer #2 for facility id = 2 :200
    //Answer #3 for facility id = 3 : 40
    //Same than Mismatch but protocol will be different

    //NOT TESTED but assumed it would be the same


    QList<QString> listResponse;
    QList<QString> listFacilityDemanded;
    QList<QString> listIdBed;
    QList<QString> listDivised; //To hold the split from the protocol
    listFacilityDemanded.append("7");

    QDateTime aDateA = QDateTime::fromString(start,"yyyy-MM-d");
//    QString aDateA =to.toString("yyyy-MM-dThh:mm:ss");
    qDebug() <<aDateA;

    QDateTime aDateB = QDateTime::fromString("2002-05-30T09:00:00","yyyy-MM-dThh:mm:ss");

    listResponse = MessageController::getInstance()->setGetData(listFacilityDemanded,AC,CCC,LTC,aDateA,aDateB);
    //qDebug() <<XMLReader::getInstance()->requestAmountOfBeds(listFacilityDemanded,"1","1","1",aDateA,aDateB);
 //   qDebug() << listResponse.at(0).;
    for (int i =0; i<listResponse.size();i++)
    {
         listIdBed.append(XMLReader::getInstance()->readRequestAmountOfBedsSUM(listResponse.at(i))); //WAIT FOR AARON, UNTILL THEN ASSUME (ID,TOTAL)
    }

 //   listIdBed <<"3,40" <<"4,60";  //Fake answer from ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    for (int k =0; k<listIdBed.size();k++)
    {
         listDivised.append(listIdBed.at(k).split(","));

    }

    //0,2,4 Even will be only the ID name
    //1,3,5 Odd will be data
    for (int z =0; z<listDivised.size();z=z+2)
    {
        listId.append(listDivised.at(z));
        listData.append(listDivised.at(z+1).toDouble()); //Set to double value
    }

  /*  listId.append("Phi");listId.append("Tau");listId.append("Pi"); //Add to lists , list O(1) to add and O(n) to read, good choice.
    listData.append(350);listData.append(175);listData.append(87);*/

    aHistogramReport = new Histogram();
    aHistogramReport->setWindowTitle("Histogram");
    aHistogramReport->setGeneralData(listId,listData); //Pass by reference
    aHistogramReport->show();
    center(*aHistogramReport);


}

void GenReportCtrl::occRateCCC()
{
    //Ask protocol
    //Get Answer
    //In this example, we will try with 3 facilities, so 3 answers from protocol
    //Answer #1 for facility id = 1 : 350
    //Answer #2 for facility id = 2 :200
    //Answer #3 for facility id = 3 : 40
    //Same than Mismatch but protocol will be different

    //NOT TESTED but assumed it would be the same

    listId.append("Phi");listId.append("Tau");listId.append("Pi"); //Add to lists , list O(1) to add and O(n) to read, good choice.
    listData.append(350);listData.append(175);listData.append(87);

    aHistogramReport = new Histogram();
    aHistogramReport->setWindowTitle("Histogram");
    aHistogramReport->setGeneralData(listId,listData); //Pass by reference
    aHistogramReport->show();
    center(*aHistogramReport);
}

void GenReportCtrl::occRateLTC()
{
    //Ask protocol
    //Get Answer
    //In this example, we will try with 3 facilities, so 3 answers from protocol
    //Answer #1 for facility id = 1 : 350
    //Answer #2 for facility id = 2 :200
    //Answer #3 for facility id = 3 : 40
    //Same than Mismatch but protocol will be different

    //NOT TESTED but assumed it would be the same

    listId.append("Phi");listId.append("Tau");listId.append("Pi"); //Add to lists , list O(1) to add and O(n) to read, good choice.
    listData.append(350);listData.append(175);listData.append(87);

    aHistogramReport = new Histogram();
    aHistogramReport->setWindowTitle("Histogram");
    aHistogramReport->setGeneralData(listId,listData); //Pass by reference
    aHistogramReport->show();
    center(*aHistogramReport);
}


//void GenReportCtrl::mismatchCCCLTC(QList<Facility *> *aFacilityList)
void GenReportCtrl::mismatchCCCLTC()
{
    //If we want our facility then use our data.
    //And/or
    //Ask protocol
    //Get Answer
    //In this example, we will try with 3 facilities, so 3 answers from protocol
    //Answer #1 for facility id = 1 : 350
    //Answer #2 for facility id = 2 :200
    //Answer #3 for facility id = 3 : 40

    //if (facilityWanted.constains(aFacilityList.first())
        //listId.append(our); listData.append(ourData);

 //   aFacilityList->first()->

    QList<QString> listFacilityDemanded;
    listFacilityDemanded.append("7");
    QList<QString> listResponse;
    QList<QString> listMismatch;
    QList<QString> listDivised;
    listId.clear();
    listData.clear();

    QDateTime aDateA = QDateTime::fromString("1994-05-30T09:00:00","yyyy-MM-dThh:mm:ss");


    QDateTime aDateB = QDateTime::fromString("2002-05-30T09:00:00","yyyy-MM-dThh:mm:ss");


    listResponse = MessageController::getInstance()->setgetMismatchOccLTC(listFacilityDemanded,aDateA,aDateB,"CCC","LTC");

    for (int i =0; i<listResponse.size();i++)
    {
        //listMismatch.append(XMLReader::getInstance()->readRequestAmountOfBeds(listResponse.at(i))); //WAIT FOR AARON, UNTILL THEN ASSUME (ID,TOTAL)
    }

    listMismatch <<"3,40" <<"4,60";  //Fake answer from ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


 //   listIdBed <<"3,40" <<"4,60";  //Fake answer from ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    for (int k =0; k<listMismatch.size();k++)
    {
         listDivised.append(listMismatch.at(k).split(","));

    }

    //0,2,4 Even will be only the ID name
    //1,3,5 Odd will be data
    for (int z =0; z<listDivised.size();z=z+2)
    {
        listId.append(listDivised.at(z));
        listData.append(listDivised.at(z+1).toDouble()); //Set to double value
    }

    listId.append("Phi");listId.append("Tau");listId.append("Pi"); //Add to lists , list O(1) to add and O(n) to read, good choice.
    listData.append(350);listData.append(175);listData.append(87);

    aHistogramReport = new Histogram();
    aHistogramReport->setWindowTitle("Histogram");
    aHistogramReport->setGeneralData(listId,listData); //Pass by reference
    aHistogramReport->show();
    center(*aHistogramReport);
}

void GenReportCtrl::sizeWL()
{
    //Ask protocol
    //Get Answer
    //In this example, we will try with 3 facilities, so 3 answers from protocol
    //Answer #1 for facility id = 1 : 350
    //Answer #2 for facility id = 2 :200
    //Answer #3 for facility id = 3 : 40

    //NOT TESTED But assumed to be correct
    QList<QString> listFacilityDemanded;
    listFacilityDemanded.append("7");
    QList<QString> listResponse;
    QList<QString> listMismatch;
    QList<QString> listDivised;
    listId.clear();
    listData.clear();

    QDateTime aDateA = QDateTime::fromString("1994-05-30T09:00:00","yyyy-MM-dThh:mm:ss");
    QDateTime aDateB = QDateTime::fromString("2002-05-30T09:00:00","yyyy-MM-dThh:mm:ss");


    listResponse = MessageController::getInstance()->setgetMismatchOccLTC(listFacilityDemanded,aDateA,aDateB,"CCC","LTC");

    for (int i =0; i<listResponse.size();i++)
    {
        //listMismatch.append(XMLReader::getInstance()->readRequestAmountOfBeds(listResponse.at(i))); //WAIT FOR AARON, UNTILL THEN ASSUME (ID,TOTAL)
    }

    listMismatch <<"3,40" <<"4,60";  //Fake answer from ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


 //   listIdBed <<"3,40" <<"4,60";  //Fake answer from ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    for (int k =0; k<listMismatch.size();k++)
    {
         listDivised.append(listMismatch.at(k).split(","));

    }

    //0,2,4 Even will be only the ID name
    //1,3,5 Odd will be data
    for (int z =0; z<listDivised.size();z=z+2)
    {
        listId.append(listDivised.at(z));
        listData.append(listDivised.at(z+1).toDouble()); //Set to double value
    }

    listId.append("Phi");listId.append("Tau");listId.append("Pi"); //Add to lists , list O(1) to add and O(n) to read, good choice.
    listData.append(350);listData.append(175);listData.append(87);

    aHistogramReport = new Histogram();
    aHistogramReport->setWindowTitle("Histogram");
    aHistogramReport->setGeneralData(listId,listData); //Pass by reference
    aHistogramReport->show();
    center(*aHistogramReport);
}

void GenReportCtrl::waitingTime()
{
    //Ask protocol
    //Get Answer
    //In this example, we will try with 3 facilities, so 3 answers from protocol
    //Answer #1 for facility id = 1 : 350
    //Answer #2 for facility id = 2 :200
    //Answer #3 for facility id = 3 : 40

    //NOT TESTED But assumed to be correct

    listId.append("Phi");listId.append("Tau");listId.append("Pi"); //Add to lists , list O(1) to add and O(n) to read, good choice.
    listData.append(350);listData.append(175);listData.append(87);

    aHistogramReport = new Histogram();
    aHistogramReport->setWindowTitle("Histogram");
    aHistogramReport->setGeneralData(listId,listData); //Pass by reference
    aHistogramReport->show();
    center(*aHistogramReport);
}


void GenReportCtrl::center(QWidget &widget)
{
  int x, y;
  int screenWidth;
  int screenHeight;

  int WIDTH = 900;
  int HEIGHT = 900;


  QDesktopWidget *desktop = QApplication::desktop();

  screenWidth = desktop->width();
  screenHeight = desktop->height();

  x = (screenWidth - WIDTH) / 2;
  y = (screenHeight - HEIGHT) / 2;

  widget.setGeometry(x, y, WIDTH, HEIGHT);
}


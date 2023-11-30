#include "signalanalyser.h"
#include <QtDebug>

SignalAnalyser::SignalAnalyser(){}

//a call for a treatable condition
int SignalAnalyser::defaultTreatable(){
    return 0;
}

//a call for a non-treatable condition
int SignalAnalyser::defaultNonTreatable(){
    return 3;
}


//takes in a data set of size 100, then compares this dataset to the existing known cardiograph datasets.
int SignalAnalyser::analyseHeartbeat(int* dataset){
    int tachycardiaCount = 0;
    int fibrillationCount = 0;
    int normalCount = 0;


    //iterate through the dataset, checking against each known dataset for matches within the tolerance.
    //when a match is found, increment the counter for that particular condition.
    for(int i = 0; i < 100; i++){

        if(dataset[i] <= (datasetTachy[i] * (1.0 + TOLERANCE)) && dataset[i] >= (datasetTachy[i] * (1.0 - TOLERANCE))){
            tachycardiaCount++;
            //qDebug() << "tachy";
        }
        if(dataset[i] <= (datasetFibri[i] * (1.0 + TOLERANCE)) && dataset[i] >= (datasetFibri[i] * (1.0 - TOLERANCE))){
            fibrillationCount++;
            //qDebug() << "fibri";
        }
        if(dataset[i] <= (datasetNormal[i] * (1.0 + TOLERANCE)) && dataset[i] >= (datasetNormal[i] * (1.0 - TOLERANCE))){
            normalCount++;
            //qDebug() << "normal";
        }
    }



    qDebug() << "Counts: " << normalCount << ", " << fibrillationCount << ", " << tachycardiaCount;

    //Check to see if all of the conditions fall beneath the minimum match threshold.
    if(tachycardiaCount <= MINIMUM_MATCH && fibrillationCount <= MINIMUM_MATCH && normalCount <= MINIMUM_MATCH){
        return NONTREATABLE;
    }
    //If so, then return the greatest of the listed conditions.
    else if(tachycardiaCount > fibrillationCount && tachycardiaCount > normalCount){
        return TACHYCARDIA;
    }
    else if(fibrillationCount > tachycardiaCount && fibrillationCount > normalCount){
        return FIBRILLATION;
    }
    else if(normalCount > tachycardiaCount && normalCount > fibrillationCount){
        return NORMAL;
    }

    return ANOMALOUS;
}

//analyses the signal of compression depth using the same method as the signal analyser.
int SignalAnalyser::analyseCompressions(int* dataset){
    int goodCompression = 0;

    for(int i = 0; i < 100; i++){
        if(dataset[i] <= (compressionDataset[i] * (1.0 + TOLERANCE)) && dataset[i] >= (compressionDataset[i] * (1.0 - TOLERANCE))){
            goodCompression++;
        }
    }

    if(goodCompression < MINIMUM_MATCH){
        return COMPRESSIONS_BAD;
    }

    return COMPRESSIONS_GOOD;
}

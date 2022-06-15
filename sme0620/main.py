import pandas as pd
from utils import checkFiles, checkFilesEnd

def ReadDataCSV(pathToData: str) -> pd.DataFrame:
    rawDataFrame = pd.read_csv(pathToData, low_memory=False)

    # rawDataFrame has 40 columns, but only 29 of them have data
    amountOfColumnsWithContent = 29

    rawColumnsNames = rawDataFrame.columns
    columnsToDrop = rawColumnsNames[amountOfColumnsWithContent:]

    parsedDataFrame = rawDataFrame.drop(columns=columnsToDrop)

    return parsedDataFrame



if __name__ == '__main__':

    pathToData = checkFiles()

    dataframe = ReadDataCSV(pathToData)
    print(dataframe.head())

    checkFilesEnd()

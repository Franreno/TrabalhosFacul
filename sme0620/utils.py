import os
import errno
import zipfile

def checkFiles() -> str:
    '''
        The data file is over 100 MB, therefore it cannot be stored in github
        To resolve this problem the file was compressed
        To be able to use the data we need to uncompress the file and return a valid path to the data.
    '''
    absolutePath = os.path.abspath(os.getcwd())

    dataFolder = 'data'
    compressedDataName = 'compressedData.zip'
    uncompressedDataName = 'dados-pi.csv'

    pathToDataFolder = absolutePath + '/' + dataFolder + '/'
    pathToUncompressedFile = absolutePath + '/' + dataFolder + '/' + uncompressedDataName
    pathToCompressedFile = absolutePath + '/' + dataFolder + '/' + compressedDataName

    # Check if uncompressedData exists
    if( os.path.exists(pathToUncompressedFile) == False):
        # It doesn't exists. 
        # Check if compressedFile exists:
        if( os.path.exists(pathToCompressedFile) == False):
            # Compressed file doesn't exists... Abort
            raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), 'Compressed file .zip does not exists')
        
        # unzip the compressed file
        with zipfile.ZipFile( pathToCompressedFile, 'r') as zip_ref:
            zip_ref.extractall(pathToDataFolder)

        # Check if extraction was sucesseful
        if( os.path.exists(pathToUncompressedFile) == False):
            # Extraction didn't work
            raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), 'Uncompreessed file "dados-pi.csv" does not exists')
        
    # Return path to uncompressed file
    return pathToUncompressedFile


def checkFilesEnd():
    absolutePath = os.path.abspath(os.getcwd())

    dataFolder = 'data'
    uncompressedDataName = 'dados-pi.csv'

    pathToUncompressedFile = absolutePath + '/' + dataFolder + '/' + uncompressedDataName


    if( os.path.exists(pathToUncompressedFile) == True ):
        os.remove(pathToUncompressedFile)
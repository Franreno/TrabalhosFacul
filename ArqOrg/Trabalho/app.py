import re
import numpy
import argparse
from matplotlib import pyplot

def read_pgm(filename, byteorder='>'):
    """Return image data from a raw PGM file as numpy array.

    Format specification: http://netpbm.sourceforge.net/doc/pgm.html

    """
    with open(filename, 'rb') as f:
        buffer = f.read()
    try:
        header, width, height, maxval = re.search(
            b"(^P5\s(?:\s*#.*[\r\n])*"
            b"(\d+)\s(?:\s*#.*[\r\n])*"
            b"(\d+)\s(?:\s*#.*[\r\n])*"
            b"(\d+)\s(?:\s*#.*[\r\n]\s)*)", buffer).groups()
    except AttributeError:
        raise ValueError("Not a raw PGM file: '%s'" % filename)
    return numpy.frombuffer(buffer,
                            dtype='u1' if int(maxval) < 256 else byteorder+'u2',
                            count=int(width)*int(height),
                            offset=len(header)
                            ).reshape((int(height), int(width)))


def create_histogram(image):
    arr = numpy.zeros(256)
    for byte in image.flatten():
        arr[byte] += 1
        
    return arr

def compare_histograms(py, mipsFile):
    mipsArr = []
    with open(mipsFile, 'r') as mips:
        mipsContent = mips.read()

    mipsContent = mipsContent.split(")")
    for e in mipsContent:
        if(e == ""):
            continue

        mipsArr.append(int(e.split(":")[1].replace(" ", "")))

    #Compare two arrays
    for i in range(256):
        if( py[i] != mipsArr[i]):
            print(f"i: {i} -> py[i]: {py[i]} | mips[i]: {mipsArr[i]}")
            return False

    return True
    

if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("-i", "--image", required=True, help="Path to the image")
    ap.add_argument("-f", "--file", required=False, help="Text Source for histogram")
    args = vars(ap.parse_args())
    
    image = read_pgm(args["image"], byteorder='<')
    pyHistogram = create_histogram(image)

    if(args["file"] != None):
        print(f"Comparacao dos dois histogramas:  {compare_histograms(pyHistogram, args['file'])} ")
    pyplot.imshow(image, pyplot.cm.gray)
    pyplot.show()
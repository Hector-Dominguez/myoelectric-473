# Import libraries
from numpy import *
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import serial
import keyboard
# Create object serial port
portName = "COM4"                      # replace this port name by yours!
baudrate = 9600
ser = serial.Serial(portName,baudrate)

### START QtApp #####
app = QtGui.QApplication([])            # you MUST do this once (initialize things)
##################
win = pg.GraphicsWindow(title="Signal from serialcom 4") # creates a window
p = win.addPlot(title="Realtime plot")  # creates empty space for the plot in the window
p.showButtons()
curve = p.plot()                        # create an empty "plot" (a curve to plot)

windowWidth = 1500                       # width of the window displaying the curve
Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr = -windowWidth                      # set first x position


win2 = pg.GraphicsWindow(title="Signal from serialcom 5") # creates a window
p2 = win.addPlot(title="Realtime plot")  # creates empty space for the plot in the window
p2.showButtons()
curve2 = p2.plot()                        # create an empty "plot" (a curve to plot)

windowWidth2 = 1500                       # width of the window displaying the curve
Xm2 = linspace(0,0,windowWidth2)          # create array that will contain the relevant time series     
ptr2 = -windowWidth2     





# Realtime data plot. Each time this function is called, the data display is updated
def update():
    global curve, ptr, Xm
    global curve2, ptr2, Xm2   

    input_byte = ser.readline()                # read line (single value) from the serial port1
    input_byte2 = ser.readline()                # read line (single value) from the serial port2
    
    test = input_byte.hex()
    #print(test[0])
    if test[0] == '3':
        value = int(input_byte)
        #print("number")
    else:
        return
    

    test2 = input_byte2.hex()
    #print(test[0])
    if test2[0] == '3':
        value2 = int(input_byte2)
        #print("number")
    else:
        return
    #print(value)

    Xm[:-1] = Xm[1:]                      # shift data in the temporal mean 1 sample left
    Xm2[:-1] = Xm2[1:]                  # shift data in the temporal mean 1 sample left
    
    Xm2[-1]= value2    
    Xm[-1] = (value)                 # vector containing the instantaneous values

    ptr += 1                              # update x position for displaying the curve
    curve.setData(Xm)                     # set the curve with this data
    curve.setPos(ptr,0)                   # set x position in the graph to 0

    ptr2 += 1                              # update x position for displaying the curve
    curve2.setData(Xm2)                     # set the curve with this data
    curve2.setPos(ptr,0)                   # set x position in the graph to 0
    
    QtGui.QApplication.processEvents()    # you MUST process the plot now

    

### MAIN PROGRAM #####    
# this is a brutal infinite loop calling your realtime data plot
while True:
    update()
    if keyboard.is_pressed('q'):
            pg.QtGui.QApplication.exec_() # you MUST put this at the end
            exit()


### END QtApp ####
pg.QtGui.QApplication.exec_() # you MUST put this at the end
##################

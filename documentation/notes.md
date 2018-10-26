##10/18/18
I had a really frustrating time with python :( . Now I have everything I need installed in order to use the python we had to plot, but it is really slow. Even with changing windowwidth there is a fuckton on latency. Gonna try and use the arduino Serial Plotter.  
##10/20/18
###Agenda:

1. Find questions to get good understanding of what I'm looking for
	* Hand Muscles
		* The signal properties
		* Where do I put the sensors 	
	* Signal processing methods and what exactly I need to calculate in the signal processing algorithms to implement the Linear/Bayes paper algo  	
2. Get enough info to start coding Link #2 filtering/signal processing stuff
3. Get some proportional demonstration!  

##Questions:

* **What muscles correspond to each finger?**
	* FDS and EDC tendons
	* **FDS**
		* Flexor digitorum superficialis tendons help bend the index, middle, ring, and small fingers at the middle finger joint. 
	* **EDC**
		* Extensor digitorum communis tendons straighten the index, middle, ring and small fingers.  	 
		 	

* **How do these muscles work?**
	*	What is the difference in EMG magnitude when muscles are contracted(clenched fist, resting in some position etc) as opposed to at rest?
		* From supp. videos for the paper, when a position is reached, the EMG waveform tends to oscillate during hold periods and at rest the signal goes to a baseline 0 or something 	
	*  	

##10/21/18
###Agenda:

1. Figure out muscle(s) to measure for index finger
2. Implement Linear filtering algo from paper
	* Implement InitializeChannels and get Yc & Yr (Done?)
	* Implement samplingTask ()
	* Implement processingTask()

##10/24/18
###Agenda:

1. Design classes for Myosensors and MyoHand
2. Work on filtering algorithm for myoinput
3. Work on sensor initialization function (getting Yc,Yr) for each sensor
4. Start algorithm on getting YVALi - the muscle activation value

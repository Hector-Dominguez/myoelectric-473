#Myoelectric Research Notes
Links to papers and websites -  

1. [Continuous and simultaneous estimation of finger kinematics using inputs from an EMG-to-muscle activation model](https://jneuroengrehab.biomedcentral.com/articles/10.1186/1743-0003-11-122)  
2. [Abstract and Proportional Myoelectric Control for Multi-Fingered Hand Prostheses](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3825263/)  
3. [Design and Development of EMG Controlled Prosthetics Limb](https://www.sciencedirect.com/science/article/pii/S1877705812023223)

##Myoelectric Sensor Info
* Adafruit Myoware Sensor:
	* Outputs the envelope of the EMG signal 
		* (0v - Vsupply)
	* Placement Requirements:
		*   "The electrodes should be place in the middle of the muscle body and should be
aligned with the orientation of the muscle fibers. Placing the sensor in other locations will
reduce the strength and quality of the sensor’s signal due to a reduction of the number of
motor units measured and interference attributed to crosstalk."

##Signal Processing & Control
1. Link #3
	* Muscle Contraction: Dominant EMG signals between  
	  20Hz - 500Hz should be used.
	* Powerline interference in US is 60Hz so we could notch 60Hz out to eliminate some noise
2. Link #2 
	* Abstract, proof of concept
	* Typical control algorithm consists of:
		1. Muscle activation estimator/observer
		2. Mapping of muscle activation to actuation commands
	* **Muscle Activation Estimation**	
		* "For each subject, we initially recorded calibration data to assess resting levels yr and comfortable contraction levels yc for each EMG channel. Comfortable contractions reflected muscle activation that could easily be repeated hundreds of times. Offline verification in our earlier studies showed that comfortable contraction levels fall typically between 10% to 15% of maximum voluntary contraction." 
		* EMG was recorded from four intrinsic hand muscles of the left hand: the abductor pollicis brevis (APB, abducts the thumb in the direction of the palm), the first dorsal interosseous (1DI, abducts the index finger towards the thumb), the third dorsal interosseus (3DI, abducts the middle finger towards the ring finger) and the abductor digiti minimi (ADM, abducts the little finger away from the other fingers). Subjects controlled the myoelectric interface with isometric muscle contractions.
		* Linear Filter
			* 
		*  Bayesian Filter
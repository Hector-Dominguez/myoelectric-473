#Myoelectric Research Notes
Links to papers and websites -  

1. [Continuous and simultaneous estimation of finger kinematics using inputs from an EMG-to-muscle activation model](https://jneuroengrehab.biomedcentral.com/articles/10.1186/1743-0003-11-122)  
2. [Abstract and Proportional Myoelectric Control for Multi-Fingered Hand Prostheses](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3825263/)  
3. [Design and Development of EMG Controlled Prosthetics Limb](https://www.sciencedirect.com/science/article/pii/S1877705812023223)
4. [Learning a Novel Myoelectric-Controlled Interface Task](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2576223/)
5. [Myoelectric Prosthetic hand video](https://www.youtube.com/watch?v=U-ROKIqaH08)
6. https://www.collectionscanada.gc.ca/obj/thesescanada/vol2/OKQ/TC-OKQ-1574.pdf

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
1. According to this [link](https://www.sciencedirect.com/science/article/pii/S1050641104000926), the highest frequency components of EMG signals are in the 400-500Hz range. **A sampling frequency of ~1kHz should be sufficient.**

##Link 3
* Muscle Contraction: Dominant EMG signals between  
	  20Hz - 500Hz should be used.
* Powerline interference in US is 60Hz so we could notch 60Hz out to eliminate some noise
	
##Abstract & Proportional Control Paper
* Abstract, proof of concept
* Typical control algorithm consists of:
	1. Muscle activation estimator/observer
	2. Mapping of muscle activation to actuation commands
* **Muscle Activation Estimation**	
	* "For each subject, we initially recorded calibration data to assess resting levels yr and comfortable contraction levels yc for each EMG channel. Comfortable contractions reflected muscle activation that could easily be repeated hundreds of times. Offline verification in our earlier studies showed that comfortable contraction levels fall typically between 10% to 15% of maximum voluntary contraction." 
		* Mean and standard deviation were calculated from the recorded calibration data of each channel (5 s rest and 5 s comfortable contraction) to estimate measurement offset and typical signal amplitudes, respectively.
			* `YVALi = (Y - Yr)/(Yc-Yr)` 
	* EMG was recorded from four intrinsic hand muscles of the left hand: the abductor pollicis brevis (APB, abducts the thumb in the direction of the palm), the first dorsal interosseous (1DI, abducts the index finger towards the thumb), the third dorsal interosseus (3DI, abducts the middle finger towards the ring finger) and the abductor digiti minimi (ADM, abducts the little finger away from the other fingers). Subjects controlled the myoelectric interface with isometric muscle contractions.
	* **Linear Filter**
		* For each channel, the linear filter averaged the rectified EMG signal of the preceding 750 ms. 
	*  **Bayesian Filter**
* **Mapping of Activation to Actuation**  
	* Each one of these parameters was individually controlled by the normalized activation **YVALi** level  of each muscle and the four-dimensional posture vector **X** determined as `X=yVal`, with **yVal** being the vector of muscle activation levels `[YVAL1,YVAL2,YVAL3,YVAL4]`
		* Only 4 signals for this part because the ring and pinky fingers were coupled to move together 
	* New set-points for the robotic hand’s position controllers were provided at an average rate of 63 Hz, which well saturated the effective update capabilities of the prosthesis’ motors.   
	
##Learning a Novel Myoelectric-Controlled Interface Task
* **Myoelectric Control Algorithm**
	*	
	
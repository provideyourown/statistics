# Statistics Library (version: 1.0b)

> &copy; 2012-2012 Scott Daniels <provideyourown.com>
> under GNU General Public License

The Statistics Library permits you to easily perform statistical analysis 
on data collected. This information can be useful for determining data
quality as well as smoothing jittery readings such as those from touch
sensors.


## Methods


**Construction & Configuration**

Statistics(numSamples) - specify the number of samples to be collected

void setNewSampleSize(numSamples) - change the sample size (will reset any data collected)

void reset() - reset the collected data

**Adding data**
void addData(val) - add a data point to the collection

**Data Analysis**
<type> mean() - the arthemetic mean of the data collected
<type> variance() - the variance of the data
<type> stdDeviation() - the standard deviation
<type> maxVal() - the maximum data point
<type> minVal() - the minimum data point

## Usage example

    Statistics stats(10);
    
    void setup()
    {
      Serial.begin(9600);
    }
    
    void loop()
    {
      int data = analogRead(A0);
      stats.addData(data);
      
      Serial.print("Mean: ");
      Serial.print(stats.mean());
      Serial.print(" Std Dev: ");
      Serial.println(stats.stdDeviation());
    }

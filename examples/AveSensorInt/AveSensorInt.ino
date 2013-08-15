#include <IntStatistics.h>

IntStatistics stats(10);

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
  Serial.print(" Variance: ");
  Serial.println(stats.variance());
}

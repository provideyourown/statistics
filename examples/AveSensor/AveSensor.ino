#include <Statistics.h>

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

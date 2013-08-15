/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */


/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Statistics Library
 Author: Scott Daniels
 Website: http://provideyourown.com
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
This library uses some 'tricks' in order to perform statistical
analysis without storing each data point - thus making it micro-
friendly. To save even more memory there are two versions - a floating
point and an integer version. The integer version saves about 200
bytes of SRAM if you don't require floating point in your code.

In order to avoid storing individual data points, a running total
is stored instead. When creating the Statistics object, the sample
size is chosen. When data overruns this sample size, older values are
sloughed off the total. The way this is done is by sloughing off the
average of all the points collected.

In a similar way, the variance is stored (from which std deviation
is calculated). Normally, the variance is the sum of the squares of
the difference between the data points and the mean. Since the mean
is not yet known, the square of the actual data point is used instead.
Then, when it is time to calculate the variance, the mean squared times
the number of data points is subtracted from the variance total. This
turns out to be the true variance by virtue of associative principle.
*/


#ifndef Statistics_h
#define Statistics_h

#include <float.h>
#include <math.h>

#define sqr(x) ((x)*(x))

class Statistics {
  public:
    Statistics(int numSamples) : mNumSamples(numSamples), mCurrNumSamples(0), mTotal(0), mRefVariance(0), mMin(FLT_MAX), mMax(-FLT_MAX) {}

    void setNewSampleSize(int numSamples)
    {
      mNumSamples = numSamples;
      reset();
    }

    void reset()
    {
      mCurrNumSamples = 0;
      mTotal = 0;
      mRefVariance = 0;
      mMin = FLT_MAX;
      mMax = -FLT_MAX;
    }

    void addData(float val)
    {
      if (mCurrNumSamples >= mNumSamples) // reduce samples total by one sample value
      {
        mTotal = mTotal * (mNumSamples - 1) / mNumSamples;
        mRefVariance = mRefVariance * (mNumSamples - 1) / mNumSamples;
      }
      else
        mCurrNumSamples++; // increment the current number
      mTotal += val;
      mRefVariance += val*val; // add the square of val (referenced to zero)
      if (val > mMax)
        mMax = val;
      if (val < mMin)
        mMin = val;
    }

    float mean() const { return mTotal / mCurrNumSamples; }
    float variance() const { return (mRefVariance - (mCurrNumSamples * sqr(mean()))) / mCurrNumSamples; }
    float stdDeviation() const { return sqrt(variance()); }
    float maxVal() const { return mMax; }
    float minVal() const { return mMin; }

    float total() const { return mTotal; }
    unsigned int samples() const { return mCurrNumSamples; }
    unsigned int sampleSize() const { return mNumSamples; }


  protected:
    unsigned int mNumSamples;
    unsigned int mCurrNumSamples;
    float mTotal;
    float mRefVariance; // not true variance - it must be calculated
    float mMin;
    float mMax;
};

#endif // #define statistics_h


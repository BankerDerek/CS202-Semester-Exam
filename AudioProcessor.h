//Connor Riche
//AudioProcessor.h

#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H
#include "Echo.h"
#include "GainAdjustment.h"
#include "Normalization.h"
#include "Compression.h"
#include "LowPassFilter.h"

///Processor for wave file data
///
/** Process class acts as the processor for all the data. The class inherets all the properties of the classes that declare and define the functions for
 * filtering or modifying the given data. To use, create an object assigned to the "Process" class and then you are free to use any function in any of the
 * data modifying classes.*/
class Process : public Echo, public GainAdjustment, public Normalization, public Compression, public LowPassFilter{};

#endif